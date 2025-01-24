#ifndef SURFACE_COLLISION_H
#define SURFACE_COLLISION_H

#include <PR/ultratypes.h>

#include "types.h"
#include "config.h"
#include "config/config_world.h"

#include "surface_load.h"

#define CELL_HEIGHT_LIMIT           20000
#define FLOOR_LOWER_LIMIT           -11000
#define FLOOR_LOWER_LIMIT_MISC      (FLOOR_LOWER_LIMIT + 1000)

#if !COLLISION_IMPROVEMENTS
#define FIND_SURFACE_BUFFER 78
#define FIND_FLOOR_BUFFER   FIND_SURFACE_BUFFER
#define FIND_CEIL_BUFFER    FIND_SURFACE_BUFFER
#endif

#if !CUSTOM_SURFACE_VALUES
#define MAX_REFERENCED_WALLS 4
#endif

#if !EXTENDED_BOUNDS
// Range level area is 16384x16384 (-8192 to +8192 in x and z)
#define LEVEL_BOUNDARY_MAX  0x2000 // 8192

#define CELL_SIZE           ((LEVEL_BOUNDARY_MAX * 2) / NUM_CELLS)
#endif

enum RaycastFlags {
    RAYCAST_FIND_FLOOR = (1 << SPATIAL_PARTITION_FLOORS),
    RAYCAST_FIND_CEIL  = (1 << SPATIAL_PARTITION_CEILS),
    RAYCAST_FIND_WALL  = (1 << SPATIAL_PARTITION_WALLS),
#if WATER_SURFACES
    RAYCAST_FIND_WATER = (1 << SPATIAL_PARTITION_WATER),
#endif
    RAYCAST_FIND_SOLID = (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL),
    RAYCAST_FIND_ALL   = (0xFFFFFFFF)
};

struct WallCollisionData {
    /*0x00*/ f32 x, y, z;
    /*0x0C*/ f32 offsetY;
    /*0x10*/ f32 radius;
    /*0x14*/ s32 numWalls;
    /*0x18*/ struct Surface *walls[MAX_REFERENCED_WALLS];
};

/**************************************************
 *                     GENERAL                    *
 **************************************************/

/**
 * Checks whether the coords are within level boundaries laterally.
 */
ALWAYS_INLINE s32 is_outside_level_bounds(s32 xPos, s32 zPos) {
    return ((xPos <= -LEVEL_BOUNDARY_MAX)
         || (xPos >=  LEVEL_BOUNDARY_MAX)
         || (zPos <= -LEVEL_BOUNDARY_MAX)
         || (zPos >=  LEVEL_BOUNDARY_MAX));
}

/**
 * Converts a single coordinate value into the corresponding cell coordinate value on the same axis.
 */
ALWAYS_INLINE s32 get_cell_coord(s32 coord) {
    return (((coord + LEVEL_BOUNDARY_MAX) / CELL_SIZE) % NUM_CELLS);
}

/**
 * Gets the height of a point at 'xPos' and 'zPos' coplanar to the triangle of 'surf'.
 */
ALWAYS_INLINE f32 get_surface_height_at_location(f32 xPos, f32 zPos, struct Surface *surf) {
    f32 nx = surf->normal.x;
    f32 ny = surf->normal.y;
    f32 nz = surf->normal.z;
    f32 oo = surf->originOffset;
    return -((xPos * nx) + (zPos * nz) + oo) / ny;
}

s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius);
s32 find_wall_collisions(struct WallCollisionData *colData);
struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);
void resolve_and_return_wall_collisions_data(Vec3f pos, f32 offset, f32 radius, struct WallCollisionData *collisionData);
f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil);

/**
 * Finds the ceiling from a vec3f horizontally and a height with the ceil buffer plus 2 
 *(78 + 2 on vanilla, 0 + 2 with exposed ceilings fix).
 */
ALWAYS_INLINE f32 find_mario_ceil(Vec3f pos, f32 height, struct Surface **ceil) {
#if EXPOSED_CEILINGS_FIX
    return find_ceil(pos[0], MAX(height, pos[1]) + FIND_CEIL_BUFFER + 2.0f, pos[2], ceil);
#else
    return find_ceil(pos[0], height + FIND_CEIL_BUFFER + 2.0f, pos[2], ceil);
#endif
}

f32 find_floor_height(f32 x, f32 y, f32 z);
f32 find_static_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);
f32 find_dynamic_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);
f32 find_room_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);
s32 get_room_at_pos(f32 x, f32 y, f32 z);
#if WATER_SURFACES
s32 find_water_level_and_floor(s32 x, s32 z, struct Surface **pfloor);
#endif
f32 find_water_level(f32 x, f32 z);
f32 find_poison_gas_level(f32 x, f32 z);
void debug_surface_list_info(f32 xPos, f32 zPos);
f32 find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, s32 flags);
void find_surface_on_ray_between_points(Vec3f pos1, Vec3f pos2, struct Surface **hit_surface, Vec3f hit_pos, s32 flags);
void raycast_collision_walls(Vec3f pos, Vec3f intendedPos, f32 yOffset);

#endif // SURFACE_COLLISION_H
