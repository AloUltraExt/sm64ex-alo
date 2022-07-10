#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/ingame_menu.h"
#include "graph_node.h"
#include "behavior_script.h"
#include "behavior_data.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/macro_special_objects.h"
#include "surface_collision.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_load.h"
#include "game/game_init.h"
#include "engine/math_util.h"

/**
 * Partitions for course and object surfaces. The arrays represent
 * the 16x16 cells that each level is split into.
 */
SpatialPartitionCell gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];
#if BETTER_DYNAMIC_CELLS
struct CellCoords {
    u8 z;
    u8 x;
};
struct CellCoords sCellsUsed[NUM_CELLS];
u16 sNumCellsUsed;
u8 sClearAllCells;
#endif

/**
 * Pools of data that can contain either surface nodes or surfaces.
 * The static surface pool is resized to be exactly the amount of memory needed for the level geometry.
 * The dynamic surface pool is set at a fixed length and cleared every frame.
 */
#ifdef USE_SYSTEM_MALLOC
static struct AllocOnlyPool *sStaticSurfaceNodePool;
static struct AllocOnlyPool *sStaticSurfacePool;
static struct AllocOnlyPool *sDynamicSurfaceNodePool;
static struct AllocOnlyPool *sDynamicSurfacePool;
#else
void *gCurrStaticSurfacePool;
void *gDynamicSurfacePool;

/**
 * The end of the data currently allocated to the surface pools.
 */
void *gCurrStaticSurfacePoolEnd;
void *gDynamicSurfacePoolEnd;

/**
 * The amount of data currently allocated to static surfaces.
 */
u32 gTotalStaticSurfaceData;
#endif

/**
 * Allocate the part of the surface node pool to contain a surface node.
 */
static struct SurfaceNode *alloc_surface_node(u32 dynamic) {
#ifdef USE_SYSTEM_MALLOC
    struct AllocOnlyPool *pool = dynamic ? sDynamicSurfaceNodePool : sStaticSurfaceNodePool;
    struct SurfaceNode *node = alloc_only_pool_alloc(pool, sizeof(struct SurfaceNode));
#else
    struct SurfaceNode **poolEnd = (struct SurfaceNode **)(dynamic ? &gDynamicSurfacePoolEnd : &gCurrStaticSurfacePoolEnd);
    struct SurfaceNode *node = *poolEnd;
    (*poolEnd)++;
#endif
    gSurfaceNodesAllocated++;

    node->next = NULL;

    return node;
}

/**
 * Allocate the part of the surface pool to contain a surface and
 * initialize the surface.
 */
static struct Surface *alloc_surface(u32 dynamic) {
#ifdef USE_SYSTEM_MALLOC
    struct AllocOnlyPool *pool = dynamic ? sDynamicSurfacePool : sStaticSurfacePool;
    struct Surface *surface = alloc_only_pool_alloc(pool, sizeof(struct Surface));
#else
    struct Surface **poolEnd = (struct Surface **)(dynamic ? &gDynamicSurfacePoolEnd : &gCurrStaticSurfacePoolEnd);
    struct Surface *surface = *poolEnd;
    (*poolEnd)++;
#endif
    gSurfacesAllocated++;

    surface->type = 0;
    surface->force = 0;
    surface->flags = 0;
    surface->room = 0;
    surface->object = NULL;

    return surface;
}

/**
 * Iterates through the entire partition, clearing the surfaces.
 */
static void clear_spatial_partition(SpatialPartitionCell *cells) {
    register s32 i = NUM_CELLS * NUM_CELLS;

    while (i--) {
        (*cells)[SPATIAL_PARTITION_FLOORS].next = NULL;
        (*cells)[SPATIAL_PARTITION_CEILS].next = NULL;
        (*cells)[SPATIAL_PARTITION_WALLS].next = NULL;
#if WATER_SURFACES
        (*cells)[SPATIAL_PARTITION_WATER].next = NULL;
#endif

        cells++;
    }
}

/**
 * Clears the static (level) surface partitions for new use.
 */
static void clear_static_surfaces(void) {
#ifndef USE_SYSTEM_MALLOC
    gTotalStaticSurfaceData = 0;
#endif
    clear_spatial_partition(&gStaticSurfacePartition[0][0]);
}

/**
 * Add a surface to the correct cell list of surfaces.
 * @param dynamic Determines whether the surface is static or dynamic
 * @param cellX The X position of the cell in which the surface resides
 * @param cellZ The Z position of the cell in which the surface resides
 * @param surface The surface to add
 */
static void add_surface_to_cell(s32 dynamic, s32 cellX, s32 cellZ, struct Surface *surface) {
    struct SurfaceNode *newNode = alloc_surface_node(dynamic);
    struct SurfaceNode *list;
    s32 surfacePriority;
    s32 priority;
    s32 sortDir = 1; // highest to lowest, then insertion order (water and floors)
    s32 listIndex;

    if (surface->normal.y > NORMAL_FLOOR_THRESHOLD) {
        listIndex = SPATIAL_PARTITION_FLOORS;
#if WATER_SURFACES
    } else if (SURFACE_IS_NEW_WATER(surface->type)) {
        listIndex = SPATIAL_PARTITION_WATER;
#endif
    } else if (surface->normal.y < NORMAL_CEIL_THRESHOLD) {
        listIndex = SPATIAL_PARTITION_CEILS;
        sortDir = -1; // lowest to highest, then insertion order
    } else {
        listIndex = SPATIAL_PARTITION_WALLS;
        sortDir = 0; // insertion order

#if !BETTER_FIND_WALL_COLLISION
        if (surface->normal.x < -0.707 || surface->normal.x > 0.707) {
            surface->flags |= SURFACE_FLAG_X_PROJECTION;
        }
#endif
    }

#if COLLISION_IMPROVEMENTS
    surfacePriority = surface->upperY * sortDir;
#else
    //! (Surface Cucking) Surfaces are sorted by the height of their first
    //  vertex. Since vertices aren't ordered by height, this causes many
    //  lower triangles to be sorted higher. This worsens surface cucking since
    //  many functions only use the first triangle in surface order that fits,
    //  missing higher surfaces.
    //  upperY would be a better sort method.
    surfacePriority = surface->vertex1[1] * sortDir;
#endif

    newNode->surface = surface;

    if (dynamic) {
        list = &gDynamicSurfacePartition[cellZ][cellX][listIndex];
#if BETTER_DYNAMIC_CELLS
        if (sNumCellsUsed >= sizeof(sCellsUsed) / sizeof(struct CellCoords)) {
            sClearAllCells = TRUE;
        } else {
            u32 addNew = TRUE;
            for (u32 i = 0; i < NUM_SPATIAL_PARTITIONS; i++) {
                if (gDynamicSurfacePartition[cellZ][cellX][i].next != NULL) {
                    addNew = FALSE;
                    break;
                }
            }
            if (addNew) {
                sCellsUsed[sNumCellsUsed].x = cellX;
                sCellsUsed[sNumCellsUsed].z = cellZ;
                sNumCellsUsed++;
            }
        }
#endif
    } else {
        list = &gStaticSurfacePartition[cellZ][cellX][listIndex];
    }

    // Loop until we find the appropriate place for the surface in the list.
    while (list->next != NULL) {
#if COLLISION_IMPROVEMENTS
        priority = list->next->surface->upperY * sortDir;
#else
        priority = list->next->surface->vertex1[1] * sortDir;
#endif

        if (surfacePriority > priority) {
            break;
        }

        list = list->next;
    }

    newNode->next = list->next;
    list->next = newNode;
}

/**
 * Every level is split into 16 * 16 cells of surfaces (to limit computing
 * time). This function determines the lower cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s32 lower_cell_index(s32 coord) {
    s32 index;

    // Move from range [-0x2000, 0x2000) to [0, 0x4000)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) {
        coord = 0;
    }

    // [0, 16)
    index = coord / CELL_SIZE;

#if !CELL_BUFFER_FIX
    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE < 50) {
        index--;
    }
#endif

    if (index < 0) {
        index = 0;
    }

    // Potentially > NUM_CELLS - 1, but since the upper index is <= NUM_CELLS - 1, not exploitable
    return index;
}

/**
 * Every level is split into CELL_SIZE * CELL_SIZE cells of surfaces (to limit computing
 * time). This function determines the upper cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s32 upper_cell_index(s32 coord) {
    s32 index;

    // Move from range [-0x2000, 0x2000) to [0, 0x4000)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) {
        coord = 0;
    }

    // [0, 16)
    index = coord / CELL_SIZE;

#if !CELL_BUFFER_FIX
    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE > CELL_SIZE - 50) {
        index++;
    }
#endif

    if (index > (NUM_CELLS - 1)) {
        index = (NUM_CELLS - 1);
    }

    // Potentially < 0, but since lower index is >= 0, not exploitable
    return index;
}

/**
 * Every level is split into 16x16 cells, this takes a surface, finds
 * the appropriate cells (with a buffer), and adds the surface to those
 * cells.
 * @param surface The surface to check
 * @param dynamic Boolean determining whether the surface is static or dynamic
 */
static void add_surface(struct Surface *surface, s32 dynamic) {
    s32 cellZ, cellX;
    s32 minX, minZ, maxX, maxZ;

    min_max_3i(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0], &minX, &maxX);
    min_max_3i(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2], &minZ, &maxZ);    

    s32 minCellX = lower_cell_index(minX);
    s32 maxCellX = upper_cell_index(maxX);
    s32 minCellZ = lower_cell_index(minZ);
    s32 maxCellZ = upper_cell_index(maxZ);

    for (cellZ = minCellZ; cellZ <= maxCellZ; cellZ++) {
        for (cellX = minCellX; cellX <= maxCellX; cellX++) {
            add_surface_to_cell(dynamic, cellX, cellZ, surface);
        }
    }
}

/**
 * Initializes a Surface struct using the given vertex data
 * @param vertexData The raw data containing vertex positions
 * @param vertexIndices Helper which tells positions in vertexData to start reading vertices
 * @param dynamic If the surface belongs to an object or not
 */
static struct Surface *read_surface_data(TerrainData *vertexData, TerrainData **vertexIndices, u32 dynamic) {
    Vec3Terrain v[3];
    Vec3f n;
    Vec3Terrain offset;
    s16 min, max;

    vec3_prod_val(offset, (*vertexIndices), 3);

    vec3s_copy(v[0], (vertexData + offset[0]));
    vec3s_copy(v[1], (vertexData + offset[1]));
    vec3s_copy(v[2], (vertexData + offset[2]));

    find_vector_perpendicular_to_plane(n, v[0], v[1], v[2]);

    vec3f_normalize(n);

    struct Surface *surface = alloc_surface(dynamic);

    vec3s_copy(surface->vertex1, v[0]);
    vec3s_copy(surface->vertex2, v[1]);
    vec3s_copy(surface->vertex3, v[2]);

    surface->normal.x = n[0];
    surface->normal.y = n[1];
    surface->normal.z = n[2];

    surface->originOffset = -vec3_dot(n, v[0]);

    min_max_3s(v[0][1], v[1][1], v[2][1], &min, &max);
    surface->lowerY = (min - SURFACE_VERTICAL_BUFFER);
    surface->upperY = (max + SURFACE_VERTICAL_BUFFER);

    return surface;
}

/**
 * Returns whether a surface has exertion/moves Mario
 * based on the surface type.
 */
static s32 surface_has_force(TerrainData surfaceType) {
    s32 hasForce = FALSE;

    switch (surfaceType) {
        case SURFACE_0004: // Unused
        case SURFACE_FLOWING_WATER:
        case SURFACE_DEEP_MOVING_QUICKSAND:
        case SURFACE_SHALLOW_MOVING_QUICKSAND:
        case SURFACE_MOVING_QUICKSAND:
        case SURFACE_HORIZONTAL_WIND:
        case SURFACE_INSTANT_MOVING_QUICKSAND:
            hasForce = TRUE;
            break;

        default:
            break;
    }
    return hasForce;
}

/**
 * Returns whether a surface should have the
 * SURFACE_FLAG_NO_CAM_COLLISION flag.
 */
static s32 surf_has_no_cam_collision(TerrainData surfaceType) {
    s32 flags = 0;

    switch (surfaceType) {
        case SURFACE_NO_CAM_COLLISION:
        case SURFACE_NO_CAM_COLLISION_77: // Unused
        case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
        case SURFACE_SWITCH:
            flags = SURFACE_FLAG_NO_CAM_COLLISION;
            break;

        default:
            break;
    }

    return flags;
}

/**
 * Load in the surfaces for a given surface type. This includes setting the flags,
 * exertion, and room.
 */
static void load_static_surfaces(TerrainData **data, TerrainData *vertexData, TerrainData surfaceType, RoomData **surfaceRooms) {
    s32 i;
    s32 numSurfaces;
    struct Surface *surface;
    RoomData room = 0;
    s16 hasForce = surface_has_force(surfaceType);
    s16 flags = surf_has_no_cam_collision(surfaceType);

    numSurfaces = *(*data);
    (*data)++;

    for (i = 0; i < numSurfaces; i++) {
        if (*surfaceRooms != NULL) {
            room = *(*surfaceRooms);
            (*surfaceRooms)++;
        }

        surface = read_surface_data(vertexData, data, FALSE);
        if (surface != NULL) {
            surface->room = room;
            surface->type = surfaceType;
            surface->flags = (s8) flags;

            if (hasForce) {
                surface->force = *(*data + 3);
            } else {
                surface->force = 0;
            }

            add_surface(surface, FALSE);
        }

        *data += 3;
        if (hasForce) {
            (*data)++;
        }
    }
}

/**
 * Read the data for vertices for reference by triangles.
 */
static TerrainData *read_vertex_data(TerrainData **data) {
    s32 numVertices;
    UNUSED u8 filler[16];
    TerrainData *vertexData;

    numVertices = *(*data);
    (*data)++;

    vertexData = *data;
    *data += 3 * numVertices;

    return vertexData;
}

/**
 * Loads in special environmental regions, such as water, poison gas, and JRB fog.
 */
static void load_environmental_regions(TerrainData **data) {
    s32 numRegions;
    s32 i;

    gEnvironmentRegions = *data;
    numRegions = *(*data)++;

    if (numRegions > 20) {
    }

    for (i = 0; i < numRegions; i++) {
        UNUSED TerrainData val, loX, loZ, hiX, hiZ;
        TerrainData height;

        val = *(*data)++;

        loX = *(*data)++;
        hiX = *(*data)++;
        loZ = *(*data)++;
        hiZ = *(*data)++;

        height = *(*data)++;

        gEnvironmentLevels[i] = height;
    }
}

/**
 * Allocate the dynamic surface pool for object collision.
 */
void alloc_surface_pools(void) {
#ifdef USE_SYSTEM_MALLOC
    sStaticSurfaceNodePool = alloc_only_pool_init();
    sStaticSurfacePool = alloc_only_pool_init();
    sDynamicSurfaceNodePool = alloc_only_pool_init();
    sDynamicSurfacePool = alloc_only_pool_init();
#else
    gDynamicSurfacePool = main_pool_alloc(DYNAMIC_SURFACE_POOL_SIZE, MEMORY_POOL_LEFT);
    gDynamicSurfacePoolEnd = gDynamicSurfacePool;
#endif
}

#ifdef NO_SEGMENTED_MEMORY
/**
 * Get the size of the terrain data, to get the correct size when copying later.
 */
u32 get_area_terrain_size(TerrainData *data) {
    TerrainData *startPos = data;
    s32 end = FALSE;
    TerrainData terrainLoadType;
    s32 numVertices;
    s32 numRegions;
    s32 numSurfaces;
    TerrainData hasForce;

    while (!end) {
        terrainLoadType = *data++;

        switch (terrainLoadType) {
            case TERRAIN_LOAD_VERTICES:
                numVertices = *data++;
                data += 3 * numVertices;
                break;

            case TERRAIN_LOAD_OBJECTS:
                data += get_special_objects_size(data);
                break;

            case TERRAIN_LOAD_ENVIRONMENT:
                numRegions = *data++;
                data += 6 * numRegions;
                break;

            case TERRAIN_LOAD_CONTINUE:
                continue;

            case TERRAIN_LOAD_END:
                end = TRUE;
                break;

            default:
                numSurfaces = *data++;
                hasForce = surface_has_force(terrainLoadType);
                data += (3 + hasForce) * numSurfaces;
                break;
        }
    }

    return data - startPos;
}
#endif

/**
 * Process the level file, loading in vertices, surfaces, some objects, and environmental
 * boxes (water, gas, JRB fog).
 */
void load_area_terrain(s16 index, TerrainData *data, RoomData *surfaceRooms, s16 *macroObjects) {
    TerrainData terrainLoadType;
    TerrainData *vertexData = NULL;
#ifndef USE_SYSTEM_MALLOC
    u32 surfacePoolData;
#endif

    // Initialize the data for this.
    gEnvironmentRegions = NULL;
    gSurfaceNodesAllocated = 0;
    gSurfacesAllocated = 0;
#if BETTER_DYNAMIC_CELLS
    bzero(&sCellsUsed, sizeof(sCellsUsed));
    sNumCellsUsed = 0;
    sClearAllCells = TRUE;
#endif
#ifdef USE_SYSTEM_MALLOC
    alloc_only_pool_clear(sStaticSurfaceNodePool);
    alloc_only_pool_clear(sStaticSurfacePool);
    alloc_only_pool_clear(sDynamicSurfaceNodePool);
    alloc_only_pool_clear(sDynamicSurfacePool);

    // Originally they forgot to clear this matrix,
    // results in segfaults if this is not done.
    clear_dynamic_surfaces();
#endif

    clear_static_surfaces();

#ifndef USE_SYSTEM_MALLOC
    // Initialise a new surface pool for this block of static surface data
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
#endif

    // A while loop iterating through each section of the level data. Sections of data
    // are prefixed by a terrain "type." This type is reused for surfaces as the surface
    // type.
    while (TRUE) {
        terrainLoadType = *data;
        data++;

        if (TERRAIN_LOAD_IS_SURFACE_TYPE_LOW(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
        } else if (terrainLoadType == TERRAIN_LOAD_VERTICES) {
            vertexData = read_vertex_data(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_OBJECTS) {
            spawn_special_objects(index, &data);
        } else if (terrainLoadType == TERRAIN_LOAD_ENVIRONMENT) {
            load_environmental_regions(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_CONTINUE) {
            continue;
        } else if (terrainLoadType == TERRAIN_LOAD_END) {
            break;
        } else if (TERRAIN_LOAD_IS_SURFACE_TYPE_HIGH(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
            continue;
        }
    }

    if (macroObjects != NULL && *macroObjects != -1) {
        // If the first macro object presetID is within the range [0, 29].
        // Generally an early spawning method, every object is in BBH (the first level).
        if (0 <= *macroObjects && *macroObjects < 30) {
            spawn_macro_objects_hardcoded(index, macroObjects);
        }
        // A more general version that can spawn more objects.
        else {
            spawn_macro_objects(index, macroObjects);
        }
    }

#ifndef USE_SYSTEM_MALLOC
    surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);
#endif
    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
}

/**
 * If not in time stop, clear the surface partitions.
 */
void clear_dynamic_surfaces(void) {
    if (!(gTimeStopState & TIME_STOP_ACTIVE)) {
#ifdef USE_SYSTEM_MALLOC
        if (gSurfacesAllocated > gNumStaticSurfaces) {
            alloc_only_pool_clear(sDynamicSurfacePool);
        }
        if (gSurfaceNodesAllocated > gNumStaticSurfaceNodes) {
            alloc_only_pool_clear(sDynamicSurfaceNodePool);
        }
#endif

        gSurfacesAllocated = gNumStaticSurfaces;
        gSurfaceNodesAllocated = gNumStaticSurfaceNodes;

#ifndef USE_SYSTEM_MALLOC
        gDynamicSurfacePoolEnd = gDynamicSurfacePool;
#endif
#if BETTER_DYNAMIC_CELLS
        if (sClearAllCells) {
            clear_spatial_partition(&gDynamicSurfacePartition[0][0]);
        } else {
            for (u32 i = 0; i < sNumCellsUsed; i++) {
                for (u32 j = 0; j < NUM_SPATIAL_PARTITIONS; j++) {
                    gDynamicSurfacePartition[sCellsUsed[i].z][sCellsUsed[i].x][j].next = NULL;
                }
            }
        }
        sNumCellsUsed = 0;
        sClearAllCells = FALSE;
#else
        clear_spatial_partition(&gDynamicSurfacePartition[0][0]);
#endif
    }
}

UNUSED static void unused_80383604(void) {
}

/**
 * Applies an object's transformation to the object's vertices.
 */
void transform_object_vertices(TerrainData **data, TerrainData *vertexData) {
    register TerrainData *vertices;
    register f32 vx, vy, vz;
    register s32 numVertices;

    Mat4 *objectTransform;
    Mat4 m;

    objectTransform = &gCurrentObject->transform;

    numVertices = *(*data);
    (*data)++;

    vertices = *data;

    if (gCurrentObject->header.gfx.throwMatrix == NULL) {
        gCurrentObject->header.gfx.throwMatrix = objectTransform;
        obj_build_transform_from_pos_and_angle(gCurrentObject, O_POS_INDEX, O_FACE_ANGLE_INDEX);
    }

    obj_apply_scale_to_matrix(gCurrentObject, m, *objectTransform);

    // Go through all vertices, rotating and translating them to transform the object.
    while (numVertices--) {
        vx = *(vertices++);
        vy = *(vertices++);
        vz = *(vertices++);

        //! No bounds check on vertex data
        *vertexData++ = (TerrainData)(vx * m[0][0] + vy * m[1][0] + vz * m[2][0] + m[3][0]);
        *vertexData++ = (TerrainData)(vx * m[0][1] + vy * m[1][1] + vz * m[2][1] + m[3][1]);
        *vertexData++ = (TerrainData)(vx * m[0][2] + vy * m[1][2] + vz * m[2][2] + m[3][2]);
    }

    *data = vertices;
}

/**
 * Load in the surfaces for the gCurrentObject. This includes setting the flags, exertion, and room.
 */
void load_object_surfaces(TerrainData **data, TerrainData *vertexData, u32 dynamic) {
    s32 surfaceType;
    s32 i;
    s32 numSurfaces;
    TerrainData hasForce;
    TerrainData flags;
    s16 room;

    surfaceType = *(*data);
    (*data)++;

    numSurfaces = *(*data);
    (*data)++;

    hasForce = surface_has_force(surfaceType);

    flags = surf_has_no_cam_collision(surfaceType) | (dynamic ? SURFACE_FLAG_DYNAMIC : 0);

    // The DDD warp is initially loaded at the origin and moved to the proper
    // position in paintings.c and doesn't update its room, so set it here.
    if (gCurrentObject->behavior == segmented_to_virtual(bhvDDDWarp)) {
        room = 5;
    } else {
        room = 0;
    }

    for (i = 0; i < numSurfaces; i++) {
        struct Surface *surface = read_surface_data(vertexData, data, dynamic);

        if (surface != NULL) {
            surface->object = gCurrentObject;
            surface->type = surfaceType;

            if (hasForce) {
                surface->force = *(*data + 3);
            } else {
                surface->force = 0;
            }

            surface->flags |= flags;
            surface->room = (s8) room;
            add_surface(surface, dynamic);
        }

        if (hasForce) {
            *data += 4;
        } else {
            *data += 3;
        }
    }
}

#if AUTO_COLLISION_DISTANCE
// From Kaze
static f32 get_optimal_collision_distance(struct Object *obj) {
    f32 thisVertDist, maxDist = 0.0f;
    Vec3f thisVertPos, scale;
    TerrainData *collisionData = obj->collisionData;
    collisionData++;
    u32 vertsLeft = *(collisionData)++;

    vec3_copy(scale, obj->header.gfx.scale);

    // Loop through the collision vertices to find the vertex
    // with the furthest distance from the model's origin.
    while (vertsLeft) {
        // Apply scale to the position
        vec3_prod(thisVertPos, collisionData, scale);

        // Get the distance to the model's origin.
        thisVertDist = vec3_sumsq(thisVertPos);

        // Check if it's further than the previous furthest vertex.
        if (maxDist < thisVertDist) {
            maxDist = thisVertDist;
        }

        // Move to the next vertex.
        //! No bounds check on vertex data
        collisionData += 3;
        vertsLeft--;
    }

    // Only run sqrtf once.
    return (sqrtf(maxDist) + 100.0f);
}
#endif

/**
 * Transform an object's vertices, reload them, and render the object.
 */
void load_object_collision_model(void) {
    TerrainData vertexData[600];

    TerrainData *collisionData = gCurrentObject->collisionData;
    f32 marioDist = gCurrentObject->oDistanceToMario;


    // On an object's first frame, the distance is set to F32_MAX.
    // If the distance hasn't been updated, update it now.
    if (gCurrentObject->oDistanceToMario == F32_MAX) {
        marioDist = dist_between_objects(gCurrentObject, gMarioObject);
    }

#if LOAD_OBJECT_COLLISION_NEAR_CAMERA
    f32 camDist = vec3_mag(gCurrentObject->header.gfx.cameraToObject);
    marioDist = MIN(marioDist, camDist);
#endif

#if AUTO_COLLISION_DISTANCE
    f32 colDist;
    if (collisionData == NULL) {
        // No collision data, so no collision distance.
        colDist = 0.0f;
    } else if (!(gCurrentObject->oFlags & OBJ_FLAG_DONT_CALC_COLL_DIST)) {
        gCurrentObject->oFlags |= OBJ_FLAG_DONT_CALC_COLL_DIST;
        // Calculate a new collision distance based on the collision data.
        colDist = get_optimal_collision_distance(gCurrentObject);
    } else {
        // Use existing collision distance.
        colDist = gCurrentObject->oCollisionDistance;
    }
#else
    f32 colDist = gCurrentObject->oCollisionDistance;
#endif

    f32 drawDist = gCurrentObject->oDrawingDistance;

    // ex-alo change
    // Ensure the object is allocated to set default collision and drawing distance
    if (gCurrentObject->activeFlags & ACTIVE_FLAG_ALLOCATED && collisionData != NULL) {
        if (colDist  == 0.0f) colDist = 1000.0f;
        if (drawDist == 0.0f) drawDist = 4000.0f;
    }

    // If the object collision is supposed to be loaded more than the
    // drawing distance, extend the drawing range.
    if (drawDist < colDist) {
        drawDist = colDist;
    }

    // Update if no Time Stop, in range, and in the current room.
    if (!(gTimeStopState & TIME_STOP_ACTIVE) && marioDist < colDist
        && !(gCurrentObject->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        collisionData++;
        transform_object_vertices(&collisionData, vertexData);

        // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
        while (*collisionData != TERRAIN_LOAD_CONTINUE) {
            load_object_surfaces(&collisionData, vertexData, TRUE);
        }
    }

#ifndef NODRAWINGDISTANCE
    if (marioDist < drawDist) {
        gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
    } else {
        gCurrentObject->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    }
#else
    gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
#endif

    gCurrentObject->oCollisionDistance = colDist;
    gCurrentObject->oDrawingDistance = drawDist;
}

/**
 * Transform an object's vertices and add them to the static surface pool.
 */
void load_object_static_model(void) {
    TerrainData vertexData[600];
    TerrainData *collisionData = gCurrentObject->collisionData;
#ifndef USE_SYSTEM_MALLOC
    u32 surfacePoolData;

    // Initialise a new surface pool for this block of surface data
    gCurrStaticSurfacePool = main_pool_alloc(main_pool_available() - 0x10, MEMORY_POOL_LEFT);
    gCurrStaticSurfacePoolEnd = gCurrStaticSurfacePool;
#endif
    gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
    gSurfacesAllocated = gNumStaticSurfaces;

    collisionData++;
    transform_object_vertices(&collisionData, vertexData);

    // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
    while (*collisionData != TERRAIN_LOAD_CONTINUE) {
        load_object_surfaces(&collisionData, vertexData, FALSE);
    }
#ifndef USE_SYSTEM_MALLOC
    surfacePoolData = (uintptr_t)gCurrStaticSurfacePoolEnd - (uintptr_t)gCurrStaticSurfacePool;
    gTotalStaticSurfaceData += surfacePoolData;
    main_pool_realloc(gCurrStaticSurfacePool, surfacePoolData);
#endif
    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
}
