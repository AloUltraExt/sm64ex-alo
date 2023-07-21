#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/debug.h"
#include "game/game_init.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "math_util.h"
#include "surface_collision.h"
#include "surface_load.h"
#ifdef CHEATS_ACTIONS
#include "extras/cheats.h"
#endif

// ex-alo change
// Adds extended bounds defines and code via defines
// Separating some code into it's own functions
// Adds gCollisionFlags for easier checks
// Without defines it returns to vanilla behavior

/**************************************************
 *                   GENERAL USE                  *
 **************************************************/

/**
 * Checks whether the coords are within level boundaries laterally.
 */
s32 is_outside_level_bounds(s32 xPos, s32 zPos) {
    return ((xPos <= -LEVEL_BOUNDARY_MAX)
         || (xPos >=  LEVEL_BOUNDARY_MAX)
         || (zPos <= -LEVEL_BOUNDARY_MAX)
         || (zPos >=  LEVEL_BOUNDARY_MAX));
}

/**
 * Converts a single coordinate value into the corresponding cell coordinate value on the same axis.
 */
s32 get_cell_coord(s32 coord) {
    return (((coord + LEVEL_BOUNDARY_MAX) / CELL_SIZE) % NUM_CELLS);
}

/**
 * Gets the height of a point at 'xPos' and 'zPos' coplanar to the triangle of 'surf'.
 */
f32 get_surface_height_at_pos(f32 xPos, f32 zPos, struct Surface *surf) {
    f32 nx = surf->normal.x;
    f32 ny = surf->normal.y;
    f32 nz = surf->normal.z;
    f32 oo = surf->originOffset;
    return -((xPos * nx) + (zPos * nz) + oo) / ny;
}

/**************************************************
 *                      WALLS                     *
 **************************************************/

#if BETTER_FIND_WALL_COLLISION
s32 check_wall_triangle_vw(f32 d00, f32 d01, f32 d11, f32 d20, f32 d21, f32 invDenom) {
    f32 v = ((d11 * d20) - (d01 * d21)) * invDenom;
    if (v < 0.0f || v > 1.0f) {
        return TRUE;
    }

    f32 w = ((d00 * d21) - (d01 * d20)) * invDenom;
    if (w < 0.0f || w > 1.0f || (v + w) > 1.0f) {
        return TRUE;
    }

    return FALSE;
}

s32 check_wall_triangle_edge(Vec3f vert, Vec3f v2, f32 *d00, f32 *d01, f32 *invDenom, f32 *offset, f32 margin_radius) {
    f32 y = vert[1];

    if (F32_IS_NONZERO(y)) {
        f32 v = (v2[1] / y);
        if (v < 0.0f || v > 1.0f) {
            return TRUE;
        }

        *d00 = ((vert[0] * v) - v2[0]);
        *d01 = ((vert[2] * v) - v2[2]);
        *invDenom = sqrtf(sqr(*d00) + sqr(*d01));
        *offset = (*invDenom - margin_radius);

        return (*offset > 0.0f);
    }

    return TRUE;
}
#else
s32 check_wall_x_projection(struct Surface *surf, f32 y, f32 z) {
    f32 w1, w2, w3, y1, y2, y3;

    w1 = -surf->vertex1[2];     w2 = -surf->vertex2[2];     w3 = -surf->vertex3[2];
    y1 =  surf->vertex1[1];     y2 =  surf->vertex2[1];     y3 =  surf->vertex3[1];

    if (surf->normal.x > 0.0f) {
        if ((y1 - y) * (w2 - w1) - (w1 - -z) * (y2 - y1) > 0.0f) return TRUE;
        if ((y2 - y) * (w3 - w2) - (w2 - -z) * (y3 - y2) > 0.0f) return TRUE;
        if ((y3 - y) * (w1 - w3) - (w3 - -z) * (y1 - y3) > 0.0f) return TRUE;
    } else {
        if ((y1 - y) * (w2 - w1) - (w1 - -z) * (y2 - y1) < 0.0f) return TRUE;
        if ((y2 - y) * (w3 - w2) - (w2 - -z) * (y3 - y2) < 0.0f) return TRUE;
        if ((y3 - y) * (w1 - w3) - (w3 - -z) * (y1 - y3) < 0.0f) return TRUE;
    }
    return FALSE;
}

s32 check_wall_z_projection(struct Surface *surf, f32 y, f32 x) {
    f32 w1, w2, w3, y1, y2, y3;

    w1 = surf->vertex1[0];      w2 = surf->vertex2[0];      w3 = surf->vertex3[0];
    y1 = surf->vertex1[1];      y2 = surf->vertex2[1];      y3 = surf->vertex3[1];

    if (surf->normal.z > 0.0f) {
        if ((y1 - y) * (w2 - w1) - (w1 - x) * (y2 - y1) > 0.0f) return TRUE;
        if ((y2 - y) * (w3 - w2) - (w2 - x) * (y3 - y2) > 0.0f) return TRUE;
        if ((y3 - y) * (w1 - w3) - (w3 - x) * (y1 - y3) > 0.0f) return TRUE;
    } else {
        if ((y1 - y) * (w2 - w1) - (w1 - x) * (y2 - y1) < 0.0f) return TRUE;
        if ((y2 - y) * (w3 - w2) - (w2 - x) * (y3 - y2) < 0.0f) return TRUE;
        if ((y3 - y) * (w1 - w3) - (w3 - x) * (y1 - y3) < 0.0f) return TRUE;
    }
    return FALSE;
}
#endif

/**
 * Iterate through the list of walls until all walls are checked and
 * have given their wall push.
 */
static s32 find_wall_collisions_from_list(struct SurfaceNode *surfaceNode, struct WallCollisionData *data) {
#if BETTER_FIND_WALL_COLLISION
    const f32 corner_threshold = -0.9f;
#endif
    struct Surface *surf;
    f32 offset;
    f32 radius = data->radius;
    Vec3f pos = { data->x, (data->y + data->offsetY), data->z };
    f32 nx, ny, nz, oo;
#if BETTER_FIND_WALL_COLLISION
    Vec3f v0, v1, v2;
    f32 d00, d01, d11, d20, d21;
    f32 invDenom;
#endif
    s32 numCols = 0;

    if (radius > MAX_COLLISION_RADIUS) {
        radius = MAX_COLLISION_RADIUS;
    }

#if BETTER_FIND_WALL_COLLISION
    f32 margin_radius = radius - 1.0f;
#endif

    // Stay in this loop until out of walls.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        // Exclude a large number of walls immediately to optimize.
        if (pos[1] < surf->lowerY || pos[1] > surf->upperY) {
            continue;
        }


        // Determine if checking for the camera or not.
        if (gCollisionFlags & COLLISION_FLAG_CAMERA) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) {
                continue;
            }
        } else {
            // Ignore camera only surfaces.
            if (surf->type == SURFACE_CAMERA_BOUNDARY) {
                continue;
            }

            // If an object can pass through a vanish cap wall, pass through.
            if (surf->type == SURFACE_VANISH_CAP_WALLS && gCurrentObject != NULL) {
                // If an object can pass through a vanish cap wall, pass through.
                if (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE) {
                    continue;
                }

                // If Mario has a vanish cap, pass through the vanish cap wall.
                if (gCurrentObject == gMarioObject && (gMarioState->flags & MARIO_VANISH_CAP)) {
                    continue;
                }
            }
        }

        // Read surface data
        nx = surf->normal.x;
        ny = surf->normal.y;
        nz = surf->normal.z;
        oo = surf->originOffset;

        // Dot of normal and pos, + origin offset.
        //! TODO: Is 'offset' just the distance from 'pos' to the triangle?
        offset = (nx * pos[0]) + (ny * pos[1]) + (nz * pos[2]) + oo;

        if (offset < -radius || offset > radius) {
            continue;
        }

#if BETTER_FIND_WALL_COLLISION
        // Edge 1 vector.
        vec3_diff(v0, surf->vertex2, surf->vertex1);
        // Edge 2 vector.
        vec3_diff(v1, surf->vertex3, surf->vertex1);
        // Vector from vertex 1 to pos.
        vec3_diff(v2, pos, surf->vertex1);

        // Face dot products.
        d00 = vec3_dot(v0, v0);
        d01 = vec3_dot(v0, v1);
        d11 = vec3_dot(v1, v1);
        d20 = vec3_dot(v2, v0);
        d21 = vec3_dot(v2, v1);

        // Inverse denom.
        invDenom = (d00 * d11) - (d01 * d01);
        invDenom = F32_IS_NONZERO(invDenom) ? (1.0f / invDenom) : 1.0f;

        if (check_wall_triangle_vw(d00, d01, d11, d20, d21, invDenom)) {
            // Skip if behind surface.
            if (offset < 0) {
                continue;
            }

            // Edge 1-2
            if (check_wall_triangle_edge(v0, v2, &d00, &d01, &invDenom, &offset, margin_radius)) {
                // Edge 1-3
                if (check_wall_triangle_edge(v1, v2, &d00, &d01, &invDenom, &offset, margin_radius)) {
                    // Edge 3 vector.
                    vec3_diff(v1, surf->vertex3, surf->vertex2);
                    // Vector from vertex 2 to pos.
                    vec3_diff(v2, pos, surf->vertex2);
                    // Edge 2-3.
                    if (check_wall_triangle_edge(v1, v2, &d00, &d01, &invDenom, &offset, margin_radius)) {
                        continue;
                    }
                }
            }

            // Check collision
            invDenom = F32_IS_NONZERO(invDenom) ? (offset / invDenom) : offset;

            // Update pos
            pos[0] += (d00 *= invDenom);
            pos[2] += (d01 *= invDenom);

            if ((d00 * nx) + (d01 * nz) < (corner_threshold * offset)) {
                continue;
            }
        } else {
            // Update pos
            pos[0] += nx * (radius - offset);
            pos[2] += nz * (radius - offset);
        }
#else
        //! (Quantum Tunneling) Due to issues with the vertices walls choose and
        //  the fact they are floating point, certain floating point positions
        //  along the seam of two walls may collide with neither wall or both walls.
        if (surf->flags & SURFACE_FLAG_X_PROJECTION) {
            if (check_wall_x_projection(surf, pos[1], pos[2])) {
                continue;
            }
        } else {
            if (check_wall_z_projection(surf, pos[1], pos[0])) {
                continue;
            }
        }
    #if COLLISION_IMPROVEMENTS
        data->x = pos[0] += (nx * (radius - offset));
        data->z = pos[2] += (nz * (radius - offset));
    #else
        //! (Wall Overlaps) Because this doesn't update the x and z local variables,
        //  multiple walls can push mario more than is required.
        data->x += nx * (radius - offset);
        data->z += nz * (radius - offset);
    #endif
#endif
        //! (Unreferenced Walls) Since this only returns the first four walls,
        //  this can lead to wall interaction being missed. Typically unreferenced walls
        //  come from only using one wall, however.
        //  Vanilla uses 4 walls, with CUSTOM_SURFACE_VALUES it uses 16 (by default)
        if (data->numWalls < MAX_REFERENCED_WALLS) {
            data->walls[data->numWalls++] = surf;
        }

        numCols++;
    }
#if BETTER_FIND_WALL_COLLISION
    data->x = pos[0];
    data->z = pos[2];
#endif

    return numCols;
}

/**
 * Formats the position and wall search for find_wall_collisions.
 */
s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius) {
    struct WallCollisionData collision;
    s32 numCollisions = 0;

    collision.offsetY = offsetY;
    collision.radius = radius;

    collision.x = *xPtr;
    collision.y = *yPtr;
    collision.z = *zPtr;

    collision.numWalls = 0;

    numCollisions = find_wall_collisions(&collision);

    *xPtr = collision.x;
    *yPtr = collision.y;
    *zPtr = collision.z;

    return numCollisions;
}

/**
 * Find wall collisions and receive their push.
 */
s32 find_wall_collisions(struct WallCollisionData *colData) {
    struct SurfaceNode *node;
    s32 numCollisions = 0;
    s32 x = colData->x;
    s32 z = colData->z;

    colData->numWalls = 0;

    if (is_outside_level_bounds(x, z)) {
        return numCollisions;
    }

    // World (level) consists of a 16x16 grid. Find where the collision is on
    // the grid (round toward -inf)
#if CELL_BUFFER_FIX
    s32 cellX, cellZ;
    s32 radius = colData->radius;
    s32 minCellX = get_cell_coord(x - radius);
    s32 maxCellX = get_cell_coord(x + radius);
    s32 minCellZ = get_cell_coord(z - radius);
    s32 maxCellZ = get_cell_coord(z + radius);

    for (cellZ = minCellZ; cellZ <= maxCellZ; cellZ++) {
        for (cellX = minCellX; cellX <= maxCellX; cellX++) {
            // Check for surfaces belonging to objects.
            node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
            numCollisions += find_wall_collisions_from_list(node, colData);
            // Check for surfaces that are a part of level geometry.
            node = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
            numCollisions += find_wall_collisions_from_list(node, colData);
        }
    }
#else
    s32 cellX = get_cell_coord(x);
    s32 cellZ = get_cell_coord(z);

    // Check for surfaces belonging to objects.
    node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);

    // Check for surfaces that are a part of level geometry.
    node = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);
#endif

    gCollisionFlags &= ~COLLISION_FLAG_INCLUDE_INTANGIBLE;

    // Increment the debug tracker.
    gNumCalls.wall++;

    return numCollisions;
}

/**************************************************
 *                     CEILINGS                   *
 **************************************************/

#if CEILING_MARGINS
void add_ceil_margin(f32 *x, f32 *z, Vec3s target1, Vec3s target2, f32 margin) {
    f32 dx = ((target1[0] - *x) + (target2[0] - *x));
    f32 dz = ((target1[2] - *z) + (target2[2] - *z));
    f32 invDenom = (sqr(dx) + sqr(dz));

    if (F32_IS_NONZERO(invDenom)) {
        invDenom = (margin / sqrtf(invDenom));

        *x += (dx * invDenom);
        *z += (dz * invDenom);
    }
}
#endif

#if CEILING_MARGINS
#define MARGIN_CHECK(cond, set) if (cond) { set; }
#else
#define check_within_ceil_triangle_bounds(x, z, surf, margin) check_within_ceil_triangle_bounds(x, z, surf)
#define MARGIN_CHECK(cond, set)
#endif
static s32 check_within_ceil_triangle_bounds(s32 x, s32 z, struct Surface *surf, const f32 margin) {
#if CEILING_MARGINS
    s32 addMargin = (F32_IS_NONZERO(margin) && (surf->type != SURFACE_HANGABLE));
#endif

    f32 x1 = surf->vertex1[0];
    f32 z1 = surf->vertex1[2];
    MARGIN_CHECK(addMargin, add_ceil_margin(&x1, &z1, surf->vertex2, surf->vertex3, margin));

    f32 z2 = surf->vertex2[2];
    f32 x2 = surf->vertex2[0];
    MARGIN_CHECK(addMargin, add_ceil_margin(&x2, &z2, surf->vertex3, surf->vertex1, margin));

    // Checking if point is in bounds of the triangle laterally.
    if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) > 0) return FALSE;
    // Slight optimization by checking these later.
    f32 x3 = surf->vertex3[0];
    f32 z3 = surf->vertex3[2];
    MARGIN_CHECK(addMargin, add_ceil_margin(&x3, &z3, surf->vertex1, surf->vertex2, margin));

    if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) > 0) return FALSE;
    if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) > 0) return FALSE;
    return TRUE;
}
#undef MARGIN_CHECK

/**
 * Iterate through the list of ceilings and find the first ceiling over a given point.
 */
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
    struct Surface *surf, *ceil = NULL;
    f32 height;

    // Stay in this loop until out of ceilings.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        // Determine if checking for the camera or not.
        if (gCollisionFlags & COLLISION_FLAG_CAMERA) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) {
                continue;
            }
        }
        // Ignore camera only surfaces.
        else if (surf->type == SURFACE_CAMERA_BOUNDARY) {
            continue;
        }

#if COLLISION_IMPROVEMENTS
        // Exclude all ceilings below the point.
        if (y > surf->upperY) continue;
#endif

        // Check that the point is within the triangle bounds.
        // Margin value (1.5f) gets ignored if CEILING_MARGINS is undefined
        if (!check_within_ceil_triangle_bounds(x, z, surf, 1.5f)) continue;

        // Find the ceil height at the specific point.
        height = get_surface_height_at_pos(x, z, surf);

#if COLLISION_IMPROVEMENTS
        // Checks for ceiling interaction.
        if (height < y) continue;
        
        // Exclude ceilings above the previous lowest ceiling.
        if (height >= *pheight) continue;
#else
        // Checks for ceiling interaction with a 78 (FIND_CEIL_BUFFER) unit buffer.
        //! (Exposed Ceilings) Because any point above a ceiling counts
        //  as interacting with a ceiling, ceilings far below can cause
        // "invisible walls" that are really just exposed ceilings.
        if (y - (height + FIND_CEIL_BUFFER) > 0.0f) continue;
#endif

        // Use the current ceiling
        *pheight = height;
        ceil = surf;
#if COLLISION_IMPROVEMENTS
        // Exit the loop if it's not possible for another ceiling to be closer
        // to the original point.
        if (height == y) break;
#else
        //! Immediately exit the loop.
        break;
#endif
    }

    //! (Surface Cucking) Since only the first ceil is returned and not the lowest,
    //  lower ceilings can be "cucked" by higher ceilings.
    //  (Only applies if collision improvements are off)
    return ceil;
}

/**
 * Find the lowest ceiling above a given position and return the height.
 */
f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil) {
    struct Surface *ceil, *dynamicCeil;
    struct SurfaceNode *surfaceList;

    f32 height = CELL_HEIGHT_LIMIT;
    f32 dynamicHeight = CELL_HEIGHT_LIMIT;

    s32 x = posX;
    s32 y = posY;
    s32 z = posZ;
    *pceil = NULL;

    if (is_outside_level_bounds(x, z)) {
        return height;
    }

    // Each level is split into cells to limit load, find the appropriate cell.
    s32 cellX = get_cell_coord(x);
    s32 cellZ = get_cell_coord(z);

    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, x, y, z, &dynamicHeight);

    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil = find_ceil_from_list(surfaceList, x, y, z, &height);

    if (dynamicHeight < height) {
        ceil = dynamicCeil;
        height = dynamicHeight;
    }

    gCollisionFlags &= ~COLLISION_FLAG_INCLUDE_INTANGIBLE;

    *pceil = ceil;

    // Increment the debug tracker.
    gNumCalls.ceil++;

    return height;
}

/**************************************************
 *                     FLOORS                     *
 **************************************************/

/**
 * Find the height of the highest floor below an object.
 */
f32 obj_find_floor_height(struct Object *obj) {
    struct Surface *floor;
    f32 floorHeight = find_floor(obj->oPosX, obj->oPosY, obj->oPosZ, &floor);
    return floorHeight;
}

static s32 check_within_floor_triangle_bounds(s32 x, s32 z, struct Surface *surf) {
    f32 x1 = surf->vertex1[0];
    f32 z1 = surf->vertex1[2];
    f32 x2 = surf->vertex2[0];
    f32 z2 = surf->vertex2[2];
    // Checking if point is in bounds of the triangle laterally.
    if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) < 0.0f) return FALSE; // 12
    // Slight optimization by checking these later.
    f32 x3 = surf->vertex3[0];
    f32 z3 = surf->vertex3[2];
    if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) < 0.0f) return FALSE; // 23
    if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) < 0.0f) return FALSE; // 31
    return TRUE;
}

/**
 * Iterate through the list of floors and find the first floor under a given point.
 */
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
    struct Surface *surf;
    f32 height;
    struct Surface *floor = NULL;
#if COLLISION_IMPROVEMENTS
    s32 bufferY = y + FIND_FLOOR_BUFFER;
#endif

    // Iterate through the list of floors until there are no more floors.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
        // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
        // Mario to pass through.
        if (!(gCollisionFlags & COLLISION_FLAG_INCLUDE_INTANGIBLE) && (surf->type == SURFACE_INTANGIBLE)) {
            continue;
        }

        // Determine if we are checking for the camera or not.
        if (gCollisionFlags & COLLISION_FLAG_CAMERA) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) {
                continue;
            }
        }
        // If we are not checking for the camera, ignore camera only floors.
        else if (surf->type == SURFACE_CAMERA_BOUNDARY) {
            continue;
        }

#if COLLISION_IMPROVEMENTS
        // Exclude all floors above the point.
        if (bufferY < surf->lowerY) continue;
#endif
        // Check that the point is within the triangle bounds.
        if (!check_within_floor_triangle_bounds(x, z, surf)) continue;

        // Find the height of the floor at a given location.
        height = get_surface_height_at_pos(x, z, surf);

#if COLLISION_IMPROVEMENTS
        // Checks for floor interaction with a FIND_FLOOR_BUFFER unit buffer.
        if (height > bufferY) continue;
        
        // Exclude floors lower than the previous highest floor.
        if (height <= *pheight) continue;
#else
        // Checks for floor interaction with a 78 (FIND_FLOOR_BUFFER) unit buffer.
        if (y - (height - FIND_FLOOR_BUFFER) < 0.0f) continue;
#endif

#ifdef CHEATS_ACTIONS
        // Set floor height cheats for Mario.
        height = cheats_walk_on_environment(height, x, z);
#endif

        // Use the current floor
        *pheight = height;
        floor = surf;
#if COLLISION_IMPROVEMENTS
        // Exit the loop if it's not possible for another floor to be closer
        // to the original point.
        if (height == bufferY) break;
#else
        //! Immediately exit the loop.
        break;
#endif
    }

    //! (Surface Cucking) Since only the first floor is returned and not the highest,
    //  higher floors can be "cucked" by lower floors.
    //  (Only applies if collision improvements are off)
    return floor;
}

#if WATER_SURFACES
/**
 * Generic triangle bounds function.
 */
ALWAYS_INLINE static s32 check_within_bounds_y_norm(s32 x, s32 z, struct Surface *surf) {
    if (surf->normal.y >= NORMAL_FLOOR_THRESHOLD) {
        return check_within_floor_triangle_bounds(x, z, surf);
    } else {
        return check_within_ceil_triangle_bounds(x, z, surf, 0);
    }
}

/**
 * Iterate through the list of water surfaces and find the first water bottom above a given point.
 */
struct Surface *find_water_bottom_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
    struct SurfaceNode *currSurfaceNode = surfaceNode;
    struct Surface *surf, *waterBottom = NULL;
    f32 height, lowest = *pheight;
    f32 bufferY = (y + 160.0f); // Mario's hitbox height

    while (currSurfaceNode != NULL) {
        surf = currSurfaceNode->surface;
        currSurfaceNode = currSurfaceNode->next;

        // Only check water bottoms.
        if (surf->type != SURFACE_NEW_WATER_BOTTOM) continue;

        // Skip wall angled surfaces.
        if (absf(surf->normal.y) < NORMAL_FLOOR_THRESHOLD) continue;

        // Check that the point is within the triangle bounds.
        if (!check_within_bounds_y_norm(x, z, surf)) continue;

        // Get the exact height of the water under the current location.
        height = get_surface_height_at_pos(x, z, surf);

        // Skip surfaces below the point.
        if (height < bufferY) continue;

        // Skip surfaces above the previous lowest.
        if (height > lowest) continue;

        lowest = height;
        waterBottom = surf;
    }

    *pheight = lowest;

    return waterBottom;
}

/**
 * Iterate through the list of water surfaces and find the highest water top at a given point, unless there is a water bottom under it.
 */
struct Surface *find_water_top_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 bottomHeight, s32 z, f32 *pheight) {
    struct SurfaceNode *currSurfaceNode = surfaceNode;
    struct Surface *surf, *waterTop = NULL;
    f32 height, highest = *pheight;

    s32 hasBottom = (bottomHeight != CELL_HEIGHT_LIMIT);

    while (currSurfaceNode != NULL) {
        surf = currSurfaceNode->surface;
        currSurfaceNode = currSurfaceNode->next;

        // Only check water tops.
        if (surf->type != SURFACE_NEW_WATER) continue;

        // Skip wall angled surfaces.
        if (absf(surf->normal.y) < NORMAL_FLOOR_THRESHOLD) continue;

        // Check that the point is within the triangle bounds.
        if (!check_within_bounds_y_norm(x, z, surf)) continue;

        // Get the exact height of the surface under the current location.
        height = get_surface_height_at_pos(x, z, surf);

        // If the water has a bottom, skip water tops higher than it.
        if (hasBottom && height > bottomHeight) continue;

        // Skip surfaces lower than the previous highest.
        if (height < highest) continue;

        highest = height;
        waterTop = surf;
    }

    *pheight = highest;

    return waterTop;
}
#endif

/**
 * Find the height of the highest floor below a point.
 */
f32 find_floor_height(f32 x, f32 y, f32 z) {
    struct Surface *floor;

    f32 floorHeight = find_floor(x, y, z, &floor);

    return floorHeight;
}

/**
 * Find the highest static floor under a given position.
 */
f32 find_static_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    struct SurfaceNode *surfaceList;
    struct Surface *floor;
    f32 floorHeight = FLOOR_LOWER_LIMIT;

    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;

    // Each level is split into cells to limit load, find the appropriate cell.
    s32 cellX = get_cell_coord(x);
    s32 cellZ = get_cell_coord(z);

    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor = find_floor_from_list(surfaceList, x, y, z, &floorHeight);

    gCollisionFlags &= ~COLLISION_FLAG_INCLUDE_INTANGIBLE;

    *pfloor = floor;

    return floorHeight;
}

/**
 * Find the highest dynamic floor under a given position.
 */
f32 find_dynamic_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    struct SurfaceNode *surfaceList;
    struct Surface *floor;
    f32 floorHeight = FLOOR_LOWER_LIMIT;

    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;

    // Each level is split into cells to limit load, find the appropriate cell.
    s32 cellX = get_cell_coord(x);
    s32 cellZ = get_cell_coord(z);

    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor = find_floor_from_list(surfaceList, x, y, z, &floorHeight);

    gCollisionFlags &= ~COLLISION_FLAG_INCLUDE_INTANGIBLE;

    *pfloor = floor;

    return floorHeight;
}

/**
 * Find the highest floor under a given position and return the height.
 */
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    struct Surface *floor, *dynamicFloor;
    struct SurfaceNode *surfaceList;

    f32 height = FLOOR_LOWER_LIMIT;
    f32 dynamicHeight = FLOOR_LOWER_LIMIT;

    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;

    *pfloor = NULL;

    if (is_outside_level_bounds(x, z)) {
        return height;
    }

    // Each level is split into cells to limit load, find the appropriate cell.
    s32 cellX = get_cell_coord(x);
    s32 cellZ = get_cell_coord(z);

    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    dynamicFloor = find_floor_from_list(surfaceList, x, y, z, &dynamicHeight);

    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor = find_floor_from_list(surfaceList, x, y, z, &height);

    // To prevent accidentally leaving the floor tangible, stop checking for it.
    gCollisionFlags &= ~COLLISION_FLAG_INCLUDE_INTANGIBLE;

    // If a floor was missed, increment the debug counter.
    if (floor == NULL) {
        gNumFindFloorMisses++;
    }

    if (dynamicHeight > height) {
        floor = dynamicFloor;
        height = dynamicHeight;
    }

    *pfloor = floor;

    // Increment the debug tracker.
    gNumCalls.floor++;

    return height;
}

/**
 * Find the highest static floor including intangible surfaces under a given position.
 */
f32 find_room_floor(f32 x, f32 y, f32 z, struct Surface **pfloor) {
    gCollisionFlags |= COLLISION_FLAG_INCLUDE_INTANGIBLE;
    return find_static_floor(x, y, z, pfloor);
}

/**
 * Get the room index at a given position.
 */
s32 get_room_at_pos(f32 x, f32 y, f32 z) {
    if (gCurrentArea->surfaceRooms != NULL) {
        struct Surface *floor;

        find_room_floor(x, y, z, &floor);

        if (floor != NULL) {
            return floor->room;
        }
    }

    return -1;
}

#if WATER_SURFACES
/**
 * Find the highest water floor under a given position and return the height.
 */
f32 find_water_floor(s32 xPos, s32 yPos, s32 zPos, struct Surface **pfloor) {
    const f32 floorLowerLimit = FLOOR_LOWER_LIMIT;
    const f32 cellHeightLimit = CELL_HEIGHT_LIMIT;
    f32 height = floorLowerLimit;

    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;

    if (is_outside_level_bounds(x, z)) {
        return height;
    }

    // Each level is split into cells to limit load, find the appropriate cell.
    s32 cellX = get_cell_coord(x);
    s32 cellZ = get_cell_coord(z);

    struct SurfaceNode *dynamicWater = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next;
    struct SurfaceNode *staticWater = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next;

    struct SurfaceNode *surfaceList;
    struct Surface *floor = NULL;

    f32 dynamicBottomHeight = cellHeightLimit;
    f32 staticBottomHeight = cellHeightLimit;

    surfaceList = dynamicWater;
    find_water_bottom_from_list(surfaceList, x, y, z, &dynamicBottomHeight);

    surfaceList = staticWater;
    find_water_bottom_from_list(surfaceList, x, y, z, &staticBottomHeight);

    // Use the lower bottom.
    f32 bottomHeight = MIN(staticBottomHeight, dynamicBottomHeight);

    f32 dynamicTopHeight = floorLowerLimit;
    f32 staticTopHeight = floorLowerLimit;

    surfaceList = dynamicWater;
    struct Surface *dynamicTop = find_water_top_from_list(surfaceList, x, bottomHeight, z, &dynamicTopHeight);

    surfaceList = staticWater;
    struct Surface *staticTop = find_water_top_from_list(surfaceList, x, bottomHeight, z, &staticTopHeight);

    // Use the higher top.
    if (staticTopHeight > dynamicTopHeight) {
        height = staticTopHeight;
        floor = staticTop;
    } else {
        height = dynamicTopHeight;
        floor = dynamicTop;
    }

    if (floor == NULL) {
        height = FLOOR_LOWER_LIMIT;
    } else {
        *pfloor = floor;
    }

    // Increment the debug tracker.
    gNumCalls.floor++;

    return height;
}
#endif

/**************************************************
 *               ENVIRONMENTAL BOXES              *
 **************************************************/

#if WATER_SURFACES
s32 find_water_level_and_floor(s32 x, s32 z, struct Surface **pfloor) {
    s32 i;
    s32 val;
    s32 loX, hiX, loZ, hiZ;
    TerrainData *p = gEnvironmentRegions;
    struct Surface *floor = NULL;
    s32 waterLevel = find_water_floor(x, ((gCollisionFlags & COLLISION_FLAG_CAMERA) ? gLakituState.pos[1] : gMarioState->pos[1]), z, &floor);

    if (p != NULL && waterLevel == FLOOR_LOWER_LIMIT) {
        s32 numRegions = *p++;

        for (i = 0; i < numRegions; i++) {
            val = *p++;
            loX = *p++;
            loZ = *p++;
            hiX = *p++;
            hiZ = *p++;

            // If the location is within a water box and it is a water box.
            // Water is less than 50 val only, while above is gas and such.
            if (loX < x && x < hiX && loZ < z && z < hiZ && val < 50) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    } else {
        *pfloor = floor;
    }

    return waterLevel;
}
#endif

/**
 * Finds the height of water at a given location.
 */
f32 find_water_level(f32 x, f32 z) {
    s32 i;
    s32 numRegions;
    TerrainData val;
    f32 loX, hiX, loZ, hiZ;
    TerrainData *p = gEnvironmentRegions;

#if WATER_SURFACES
    struct Surface *floor;
    f32 waterLevel = find_water_floor(x, ((gCollisionFlags & COLLISION_FLAG_CAMERA) ? gLakituState.pos[1] : gMarioState->pos[1]), z, &floor);
    if (p != NULL && waterLevel == FLOOR_LOWER_LIMIT)
#else
    f32 waterLevel = FLOOR_LOWER_LIMIT;
    if (p != NULL)
#endif
    {
        numRegions = *p++;

        for (i = 0; i < numRegions; i++) {
            val = *p++;
            loX = *p++;
            loZ = *p++;
            hiX = *p++;
            hiZ = *p++;

            // If the location is within a water box and it is a water box.
            // Water is less than 50 val only, while above is gas and such.
            if (loX < x && x < hiX && loZ < z && z < hiZ && val < 50) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    }

    return waterLevel;
}

/**
 * Finds the height of the poison gas (used only in HMC) at a given location.
 */
f32 find_poison_gas_level(f32 x, f32 z) {
    s32 i;
    s32 numRegions;
    UNUSED u8 filler[4];
    TerrainData val;
    f32 loX, hiX, loZ, hiZ;
    f32 gasLevel = FLOOR_LOWER_LIMIT;
    TerrainData *p = gEnvironmentRegions;

    if (p != NULL) {
        numRegions = *p++;

        for (i = 0; i < numRegions; i++) {
            val = *p;

            if (val >= 50) {
                loX = p[1];
                loZ = p[2];
                hiX = p[3];
                hiZ = p[4];

                // If the location is within a gas's box and it is a gas box.
                // Gas has a value of 50, 60, etc.
                if (loX < x && x < hiX && loZ < z && z < hiZ && val % 10 == 0) {
                    // Set the gas height. Since this breaks, only return the first height.
                    gasLevel = p[5];
                    break;
                }
            }

            p += 6;
        }
    }

    return gasLevel;
}

/**************************************************
 *                      DEBUG                     *
 **************************************************/

/**
 * Finds the length of a surface list for debug purposes.
 */
static s32 surface_list_length(struct SurfaceNode *list) {
    s32 count = 0;

    while (list != NULL) {
        list = list->next;
        count++;
    }

    return count;
}

/**
 * Print the area,number of walls, how many times they were called,
 * and some allocation information.
 */
void debug_surface_list_info(f32 xPos, f32 zPos) {
    struct SurfaceNode *list;
    s32 numFloors = 0;
    s32 numWalls = 0;
    s32 numCeils = 0;

    s32 cellX = get_cell_coord(xPos);
    s32 cellZ = get_cell_coord(zPos);

    list = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    numFloors += surface_list_length(list);

    list = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    numFloors += surface_list_length(list);

    list = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numWalls += surface_list_length(list);

    list = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numWalls += surface_list_length(list);

    list = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    numCeils += surface_list_length(list);

    list = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    numCeils += surface_list_length(list);

    print_debug_top_down_mapinfo("area   %x", cellZ * NUM_CELLS + cellX);

    // Names represent ground, walls, and roofs as found in SMS.
    print_debug_top_down_mapinfo("dg %d", numFloors);
    print_debug_top_down_mapinfo("dw %d", numWalls);
    print_debug_top_down_mapinfo("dr %d", numCeils);

    set_text_array_x_y(80, -3);

    print_debug_top_down_mapinfo("%d", gNumCalls.floor);
    print_debug_top_down_mapinfo("%d", gNumCalls.wall);
    print_debug_top_down_mapinfo("%d", gNumCalls.ceil);

    set_text_array_x_y(-80, 0);

    // listal- List Allocated?, statbg- Static Background?, movebg- Moving Background?
    print_debug_top_down_mapinfo("listal %d", gSurfaceNodesAllocated);
    print_debug_top_down_mapinfo("statbg %d", gNumStaticSurfaces);
    print_debug_top_down_mapinfo("movebg %d", gSurfacesAllocated - gNumStaticSurfaces);

    gNumCalls.floor = 0;
    gNumCalls.ceil = 0;
    gNumCalls.wall = 0;
}

/**************************************************
 *                    RAYCASTING                  *
 **************************************************/

#define RAY_STEPS      4 /* How many steps to do when casting rays, default to quartersteps.  */

s32 ray_surface_intersect(Vec3f orig, Vec3f dir, f32 dir_length, struct Surface *surface, Vec3f hit_pos, f32 *length)
{
    //Ignore certain surface types.
    if (surface->type == SURFACE_INTANGIBLE || surface->type == SURFACE_WALL_MISC
        || surface->type == SURFACE_VANISH_CAP_WALLS || surface->flags & SURFACE_FLAG_NO_CAM_COLLISION)
        return FALSE;

    //Ignore hangable surface if Mario is hanging
    if (surface->type == SURFACE_HANGABLE && gMarioState->action & ACT_FLAG_HANGING)
        return FALSE;

    // Convert the vertices to Vec3f.
    Vec3f v0, v1, v2;
    vec3s_to_vec3f(v0, surface->vertex1);
    vec3s_to_vec3f(v1, surface->vertex2);
    vec3s_to_vec3f(v2, surface->vertex3);

    // Make 'e1' (edge 1) the vector from vertex 0 to vertex 1.
    Vec3f e1;
    vec3f_diff(e1, v1, v0);
    // Make 'e2' (edge 2) the vector from vertex 0 to vertex 2.
    Vec3f e2;
    vec3f_diff(e2, v2, v0);
    // Make 'h' the cross product of 'dir' and edge 2.
    Vec3f h;
    vec3f_cross(h, dir, e2);

    // Determine the cos(angle) difference between ray and surface normals.
    f32 det = vec3f_dot(e1, h);
    // Check if we're perpendicular or pointing away from the surface.
    if (det < NEAR_ZERO) return FALSE;
    // Check if we're making contact with the surface.
    // Make f the inverse of the cos(angle) between ray and surface normals.
    f32 f = 1.0f / det; // invDet
    // Make 's' the vector from vertex 0 to 'orig'.
    Vec3f s;
    vec3f_diff(s, orig, v0);
    // Make 'u' the cos(angle) between vectors 's' and normals, divided by 'det'.
    f32 u = f * vec3f_dot(s, h);
    // Check if 'u' is within bounds.
    if ((u < 0.0f) || (u > 1.0f)) return FALSE;

    // Make 'q' the cross product of 's' and edge 1.
    Vec3f q;
    vec3f_cross(q, s, e1);
    // Make 'v' the cos(angle) between the ray and 'q', divided by 'det'.
    f32 v = f * vec3f_dot(dir, q);
    // Check if 'v' is within bounds.
    if ((v < 0.0f) || ((u + v) > 1.0f)) return FALSE;

    // Get the length between our origin and the surface contact point.
    // Make '*length' the cos(angle) betqwwn edge 2 and 'q', divided by 'det'.
    *length = f * vec3f_dot(e2, q);
    // Check if the length to the hit point is shorter than the ray length.
    if ((*length <= NEAR_ZERO) || (*length > dir_length)) return FALSE;

    // Successful contact
    // Make 'add_dir' into 'dir' scaled by 'length'.
    Vec3f add_dir;
    vec3_prod_val(add_dir, dir, *length);
    // Make 'hit_pos' into the sum of 'orig' and 'add_dir'.
    vec3f_sum(hit_pos, orig, add_dir);

    return TRUE;
}

void find_surface_on_ray_list(struct SurfaceNode *list, Vec3f orig, Vec3f dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length) {
    s32 hit;
    f32 length;
    Vec3f chk_hit_pos;
    f32 top, bottom;

    // Get upper and lower bounds of ray
    if (dir[1] >= 0.0f) {
        // Ray is upwards.
        top    = orig[1] + (dir[1] * dir_length);
        bottom = orig[1];
    } else {
        // Ray is downwards.
        top    = orig[1];
        bottom = orig[1] + (dir[1] * dir_length);
    }

    // Iterate through every surface of the list
    for (; list != NULL; list = list->next) {
        // Reject surface if out of vertical bounds
        if ((list->surface->lowerY > top) || (list->surface->upperY < bottom)) continue;
        // Check intersection between the ray and this surface
        hit = ray_surface_intersect(orig, dir, dir_length, list->surface, chk_hit_pos, &length);
        if (hit && (length <= *max_length)) {
            *hit_surface = list->surface;
            vec3f_copy(hit_pos, chk_hit_pos);
            *max_length = length;
        }
    }
}

void find_surface_on_ray_cell(s32 cellX, s32 cellZ, Vec3f orig, Vec3f normalized_dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length, s32 flags) {
    s32 i;
    // Skip if OOB
    if ((cellX >= 0) && (cellX <= (NUM_CELLS - 1)) && (cellZ >= 0) && (cellZ <= (NUM_CELLS - 1))) {
        f32 ny = normalized_dir[1];
        s32 rayUp   = (ny >  NEAR_ONE);
        s32 rayDown = (ny < -NEAR_ONE);

        for (i = 0; i < NUM_SPATIAL_PARTITIONS; i++) {
            if ((rayDown && (i == SPATIAL_PARTITION_CEILS ))
             || (rayUp   && (i == SPATIAL_PARTITION_FLOORS))) {
                continue;
            }

            if (flags & (1 << i)) {
                // Iterate through each surface in this partition
                find_surface_on_ray_list( gStaticSurfacePartition[cellZ][cellX][i].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
                find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][i].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            }
        }
    }
}

f32 find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, s32 flags) {
    Vec3f normalized_dir;
    f32 step;
    s32 i;
    const f32 invcell = 1.0f / CELL_SIZE;

    // Set that no surface has been hit
    *hit_surface = NULL;
    vec3f_sum(hit_pos, orig, dir);

    // Get normalized direction
    f32 dir_length = vec3_mag(dir);
    f32 max_length = dir_length;
    vec3f_copy(normalized_dir, dir);
    vec3f_normalize(normalized_dir);

    // Get our cell coordinate
    f32 fCellX    = (orig[0] + LEVEL_BOUNDARY_MAX) * invcell;
    f32 fCellZ    = (orig[2] + LEVEL_BOUNDARY_MAX) * invcell;
    s32 cellX     = fCellX;
    s32 cellZ     = fCellZ;
    s32 cellPrevX = cellX;
    s32 cellPrevZ = cellZ;

    // Don't do DDA if straight down
    if ((normalized_dir[1] >= NEAR_ONE) || (normalized_dir[1] <= -NEAR_ONE)) {
        find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
        return max_length;
    }

    // Get cells we cross using DDA
    f32 absDir0 = absf(dir[0]);
    f32 absDir2 = absf(dir[2]);
    if (absDir0 >= absDir2) {
        step = (RAY_STEPS * absDir0) * invcell;
    } else {
        step = (RAY_STEPS * absDir2) * invcell;
    }

    f32 dx = (dir[0] / step) * invcell;
    f32 dz = (dir[2] / step) * invcell;

    for (i = 0; i < step && *hit_surface == NULL; i++) {
        find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);

        // Move cell coordinate
        fCellX   += dx;
        fCellZ   += dz;
        cellPrevX = cellX;
        cellPrevZ = cellZ;
        cellX     = fCellX;
        cellZ     = fCellZ;

        if ((cellPrevX != cellX) && (cellPrevZ != cellZ)) {
            find_surface_on_ray_cell(cellX, cellPrevZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
            find_surface_on_ray_cell(cellPrevX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
        }
    }
    return max_length;
}

void find_surface_on_ray_between_points(Vec3f pos1, Vec3f pos2, struct Surface **hit_surface, Vec3f hit_pos, s32 flags) {
    Vec3f dir;
    vec3f_diff(dir, pos2, pos1);
    find_surface_on_ray(pos1, dir, hit_surface, hit_pos, flags);
}

/**
 * Send a raycast from pos to intendedPos shifted upward by yOffset,
 * and set intendedPos to the collided point if the ray reaches a wall.
 */
void raycast_collision_walls(Vec3f pos, Vec3f intendedPos, f32 yOffset) {
    UNUSED struct Surface *surf;
    Vec3f dir;

    // Get the vector from pos to the original intendedPos.
    vec3f_diff(dir, intendedPos, pos);

    // Shift the source pos upward by yOffset.
    pos[1] += yOffset;

    // Send the raycast and find the new pos.
    find_surface_on_ray(pos, dir, &surf, intendedPos, RAYCAST_FIND_WALL);

    // Shift pos and intendedPos back down.
    pos[1]         -= yOffset;
    intendedPos[1] -= yOffset;
}

/**************************************************
 *                     UNUSED                     *
 **************************************************/

/**
 * An unused function that finds and interacts with any type of surface.
 * Perhaps an original implementation of surfaces before they were more specialized.
 */
UNUSED static s32 unused_resolve_floor_or_ceil_collisions(s32 checkCeil, f32 *px, f32 *py, f32 *pz, f32 radius,
                                            struct Surface **psurface, f32 *surfaceHeight) {
    f32 nx, ny, nz, oo;
    f32 x = *px;
    f32 y = *py;
    f32 z = *pz;
    f32 offset, distance;

    *psurface = NULL;

    if (checkCeil) {
        *surfaceHeight = find_ceil(x, y, z, psurface);
    } else {
        *surfaceHeight = find_floor(x, y, z, psurface);
    }

    if (*psurface == NULL) {
        return -1;
    }

    nx = (*psurface)->normal.x;
    ny = (*psurface)->normal.y;
    nz = (*psurface)->normal.z;
    oo = (*psurface)->originOffset;

    offset = nx * x + ny * y + nz * z + oo;
    distance = offset >= 0 ? offset : -offset;

    // Interesting surface interaction that should be surf type independent.
    if (distance < radius) {
        *px += nx * (radius - offset);
        *py += ny * (radius - offset);
        *pz += nz * (radius - offset);

        return 1;
    }

    return 0;
}
