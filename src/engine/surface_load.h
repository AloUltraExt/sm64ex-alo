#ifndef SURFACE_LOAD_H
#define SURFACE_LOAD_H

#include <PR/ultratypes.h>

#include "types.h"
#include "config.h"
#include "config/config_world.h"

#if !EXTENDED_BOUNDS
#define SURFACE_POOL_SIZE       2300
#define SURFACE_NODE_POOL_SIZE  7000

#define NUM_CELLS   16
#endif

#if !CUSTOM_SURFACE_VALUES
#define NORMAL_FLOOR_THRESHOLD 0.01f
#define NORMAL_CEIL_THRESHOLD -NORMAL_FLOOR_THRESHOLD
#endif

#define SURFACE_VERTICAL_BUFFER 5

struct SurfaceNode {
    struct SurfaceNode *next;
    struct Surface *surface;
};

enum {
    SPATIAL_PARTITION_FLOORS,
    SPATIAL_PARTITION_CEILS,
    SPATIAL_PARTITION_WALLS,
#if WATER_SURFACES
    SPATIAL_PARTITION_WATER,
#endif
    NUM_SPATIAL_PARTITIONS
};

typedef struct SurfaceNode SpatialPartitionCell[NUM_SPATIAL_PARTITIONS];

extern SpatialPartitionCell gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
extern SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];
extern struct SurfaceNode *sSurfaceNodePool;
extern struct Surface *sSurfacePool;
extern s32 sSurfaceNodePoolSize;
extern s32 sSurfacePoolSize;

void alloc_surface_pools(void);
#ifdef NO_SEGMENTED_MEMORY
u32 get_area_terrain_size(TerrainData *data);
#endif
void load_area_terrain(s16 index, TerrainData *data, RoomData *surfaceRooms, s16 *macroObjects);
void clear_dynamic_surfaces(void);
void load_object_collision_model(void);

#endif // SURFACE_LOAD_H
