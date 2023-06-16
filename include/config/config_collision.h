#pragma once

/**********************
 * COLLISION SETTINGS *
 **********************/

// Sets custom and recommended values surfaces (higher than vanilla).
#define CUSTOM_SURFACE_VALUES (0 || COLLISION_FIXES)

// Fixes most collision bugs and adds extra checks for performance.
#define COLLISION_IMPROVEMENTS (0 || COLLISION_FIXES)

// Checks for ceilings from Mario's actual height instead of from the floor height.
#define EXPOSED_CEILINGS_FIX (0 || COLLISION_FIXES)

// Fixes cell buffer by checking extra cells in corners.
#define CELL_BUFFER_FIX (0 || COLLISION_FIXES)

// Fixes landing on a floor vertically aligned and within 160 units of a ceiling
#define PEDRO_SPOT_FIX (0 || COLLISION_FIXES)

// Push Mario out of sloped ceilings instead of stopping or knocking.
#define BETTER_CEILING_HANDLING (0 || COLLISION_FIXES)

// Adds margins to celling surfaces (except hangable ones).
#define CEILING_MARGINS (0 || COLLISION_FIXES)

// Adds rounded corners on edge walls along with some extra checks.
#define BETTER_FIND_WALL_COLLISION (0 || COLLISION_FIXES)

// Improves resolve and return wall checks, along with some fixes.
#define BETTER_RESOLVE_WALL_COLLISION (0 || COLLISION_FIXES)

// Adds water collision surfaces.
#define WATER_SURFACES (0 || COLLISION_FIXES)

// Saves a lot of CPU over silliness, by cleaning only used dynamic cells.
#define BETTER_DYNAMIC_CELLS (0 || COLLISION_FIXES)

// Removes surface priority ordering to save processing time.
#define NO_SURFACE_PRIORITY_REORDER (0 || COLLISION_FIXES)

// Automatically calculates the optimal collision distance for an object based on it's vertices.
#define AUTO_COLLISION_DISTANCE (0 || QOL_FEATURES)

// Allows objects to use camera distance to determine whether to load collision if the camera is closer than Mario.
#define LOAD_OBJECT_COLLISION_NEAR_CAMERA (0 || QOL_FEATURES)

/// Use the floor's normal instead of a triangle of find_floor if the floor isn't steep
#define FAST_FLOOR_ALIGN (0 || QOL_FEATURES)

#if FAST_FLOOR_ALIGN
#define FAST_FLOOR_ALIGN_VALUE  10
#endif
