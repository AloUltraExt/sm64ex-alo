#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"

/**
 * Shadow types. Shadows are circles, squares, or hardcoded rectangles, and
 * can be composed of either 4 or 9 vertices.
 */
enum ShadowType {
#if 1 // LEGACY_SHADOW_IDS, will be enforced until Fast64 support name values
    SHADOW_CIRCLE           = 5,
    SHADOW_CIRCLE_PLAYER    = SHADOW_CIRCLE,
    SHADOW_CIRCLE_4_VERTS   = SHADOW_CIRCLE,
    SHADOW_CIRCLE_9_VERTS   = SHADOW_CIRCLE,
    SHADOW_SQUARE           = 6,
    SHADOW_SQUARE_PERMANENT = 7,
    SHADOW_SQUARE_SCALABLE  = SHADOW_SQUARE,
    SHADOW_SQUARE_TOGGLABLE = SHADOW_SQUARE,
#else
    SHADOW_CIRCLE           = 0,
    SHADOW_CIRCLE_PLAYER    = SHADOW_CIRCLE,
    SHADOW_CIRCLE_4_VERTS   = SHADOW_CIRCLE,
    SHADOW_CIRCLE_9_VERTS   = SHADOW_CIRCLE,
    SHADOW_SQUARE           = 1,
    SHADOW_SQUARE_PERMANENT = 2,
    SHADOW_SQUARE_SCALABLE  = SHADOW_SQUARE,
    SHADOW_SQUARE_TOGGLABLE = SHADOW_SQUARE,
#endif
#if PROPER_TREE_SHADOWS
    SHADOW_SPIKE            = 8,
#endif
    /**
     * This defines an offset after which rectangular shadows with custom
     * widths and heights can be defined.
     */
    SHADOW_RECTANGLE_HARDCODED_OFFSET = 50,
    SHADOW_RECTANGLE_SPINDEL          = (0 + SHADOW_RECTANGLE_HARDCODED_OFFSET),
    SHADOW_RECTANGLE_WHOMP            = (1 + SHADOW_RECTANGLE_HARDCODED_OFFSET),
};

enum ShadowSolidity {
    /**
     * Constant to indicate that a shadow should not be drawn.
     * This is used to disable shadows during specific frames of Mario's
     * animations.
     */
    SHADOW_SOLIDITY_NO_SHADOW,
    /**
     * Constant to indicate that a shadow's solidity has been pre-set by a previous
     * function and should not be overwritten.
     */
    SHADOW_SOILDITY_ALREADY_SET,
    /**
     * Constant to indicate that a shadow's solidity has not yet been set.
     */
    SHADOW_SOLIDITY_NOT_YET_SET,
};

/**
 * A struct containing info about hardcoded rectangle shadows.
 */
typedef struct {
    /* X scale of the rectangle. */
    f32 scaleX;
    /* Z scale of the rectangle. */
    f32 scaleZ;
    /* Flag for if this shadow be smaller when its object is further away. */
    u8 scaleWithDistance : 1;
} ShadowRectangle;

/**
 * Given the (x, y, z) location of an object, create a shadow below that object
 * with the given initial solidity and "shadowType" (described above).
 */
Gfx *create_shadow_below_xyz(Vec3f pos, Vec3f floorNormal, Vec3f scaleVec, s16 shadowScale, u8 shadowSolidity, s8 shadowType, s8 shifted, s8 *isDecal);
