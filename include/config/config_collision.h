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

// Adds rounded corners on edge walls along with some extra checks.
#define ROUNDED_WALL_CORNERS (0 || COLLISION_FIXES)

// Improves resolve and return wall checks, along with some fixes.
#define BETTER_RESOLVE_WALL_COLLISION (0 || COLLISION_FIXES)

// Adds water collision surfaces.
#define WATER_SURFACES (0 || COLLISION_FIXES)

// Saves a lot of CPU over silliness, by cleaning only used dynamic cells.
#define BETTER_DYNAMIC_CELLS (0 || COLLISION_FIXES)

// Makes abnormal walls have floor properties, fixes OOB invisible walls.
#define ABNORMAL_WALLS_AS_FLOORS (0 || COLLISION_FIXES)

// Automatically calculates the optimal collision distance for an object based on it's vertices.
#define AUTO_COLLISION_DISTANCE (0 || QOL_FEATURES)

/// Uses a simple yet effective optimized result using normals with simplified math checks.
#define BETTER_FIND_FLOOR_SLOPE (0 || QOL_FEATURES)
