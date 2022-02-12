#pragma once

// Collision Settings

// Sets extended bounds for larger levels.
//#define EXTENDED_BOUNDS

// Sets custom and recommended vanilla surfaces.
#define CUSTOM_SURFACE_VALUES (0 || EXTENDED_BOUNDS)

// Fixes most collision bugs and adds extra checks for performance.
#define COLLISION_IMPROVEMENTS (0 || EXTENDED_BOUNDS)

// Checks for ceilings from Mario's actual height instead of from the floor height.
#define EXPOSED_CEILINGS_FIX (0 || EXTENDED_BOUNDS)

// Fixes cell buffer by checking extra cells in corners
#define CELL_BUFFER_FIX (0 || EXTENDED_BOUNDS)

// Fixes landing on a floor vertically aligned and within 160 units of a ceiling
#define PEDRO_SPOT_FIX (0 || EXTENDED_BOUNDS)

// Push Mario out of sloped ceilings instead of stopping or bonking
#define BETTER_CEILING_HANDLING (0 || EXTENDED_BOUNDS)

// Adds margins to celling surfaces (except hangable ones).
#define CEILING_MARGINS (0 || EXTENDED_BOUNDS)

// Adds rounded corners on edge walls along with some extra checks.
#define BETTER_FIND_WALL_COLLISION (0 || EXTENDED_BOUNDS)

// Improves resolve and return wall checks, alonng with some fixes
#define BETTER_RESOLVE_WALL_COLLISION (0 || EXTENDED_BOUNDS)

// Adds water collision surfaces
#define WATER_SURFACES (0 || EXTENDED_BOUNDS)
