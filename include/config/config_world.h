#pragma once

#include "config/config_collision.h"

#if CUSTOM_SURFACE_VALUES

/*****************************
 * CUSTOM SURF VALUES CONFIG *
 *****************************/

// Minimum Y normal for floors (vanilla is 0.01f)
#define NORMAL_FLOOR_THRESHOLD  0.035f

// Minimum Y normal for ceilings (vanilla is -0.01)
#define NORMAL_CEIL_THRESHOLD  -0.02f

// Maximum number of walls to check (vanilla is 4, higher is recommended)
#define MAX_REFERENCED_WALLS    16

#endif

#if COLLISION_IMPROVEMENTS

// Floor buffer value, used on every floor check (vanilla is 78)
#define FIND_FLOOR_BUFFER   78

// Ceil buffer value, used on ceil check (stubbed) (vanilla is 78)
#define FIND_CEIL_BUFFER    0

#endif

#if EXTENDED_BOUNDS

/**************************
 * EXTENDED BOUNDS CONFIG *
 **************************/

// -- General Config --

/**
 * The distance the level boundary is from the origin.
 * For best performance results, this should be a power of 2.
 * Values lower than vanilla are not recommended.
 * Vanilla: 0x2000 (8192)
 */
#define LEVEL_BOUNDARY_MAX (8192 * EXTENDED_BOUNDS)

/**
 * The number of cells along each axis in an area.
 * Higher numbers = smaller cells = higher performance + higher RAM usage.
 * Lower numbers = larger cells = lower performance + lower RAM usage.
 * For best performance results, this should be a power of 2,
 * since that allows for get_cell_coord to be optimized.
 * Vanilla: 16
 */
#define NUM_CELLS 32


// -- Don't touch the stuff past this point unless you know what you're doing! --


// -- Precomputed constants --

/**
 * World scale value. This allows you to scale down geometry by the given amount,
 * which allows for larger levels without the distortion you would otherwise get.
 * Larger world scale comes at a cost of precision, which can increase Z-fighting.
 * Values above 4 should not be necessary.
 * Vanilla: 1
 */
#define WORLD_SCALE (LEVEL_BOUNDARY_MAX / 8192)

/**
 * The size of one collision cell.
 * Vanilla: 0x400 (1024)
 */
#define CELL_SIZE ((LEVEL_BOUNDARY_MAX * 2) / NUM_CELLS)

#endif
