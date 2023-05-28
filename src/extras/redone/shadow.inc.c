/**
 * Redone description:
 * This is an optimized version of the original shadow code, from HackerSM64.
 * Made by Arceveti.
 */

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "behavior_data.h"
#include "game/level_update.h"
#include "game/mario_misc.h"

/**
 * An array consisting of all the hardcoded rectangle shadows in the game.
 */
static const ShadowRectangle sShadowRectangles[2] = {
    { 7.2f, 4.6f, TRUE }, // Spindel
    { 4.0f, 3.6f, TRUE }, // Whomp
};

/**
 * Shrink a shadow when its parent object is further from the floor, given the
 * initial size of the shadow and the current distance.
 */
static f32 scale_shadow_with_distance(f32 initial, f32 distFromFloor) {
    f32 half = 0.5f;
    f32 dist = 600.0f;

    if (distFromFloor <= 0.0f) {
        return initial;
    } else if (distFromFloor >= dist) {
        return initial * half;
    } else {
        return initial * (1.0f - ((distFromFloor * half) / dist));
    }
}

/**
 * Dim a shadow when its parent object is further from the ground.
 */
static s32 dim_shadow_with_distance(u8 solidity, f32 distFromFloor) {
    f32 dist = 600.0f;

    if (solidity < 121) {
        return solidity;
    } else if (distFromFloor <= 0.0f) {
        return solidity;
    } else if (distFromFloor >= dist) {
        return 120;
    } else {
        return (((120 - solidity) * distFromFloor) / dist) + (f32) solidity;
    }
}

/**
 * Linearly interpolate a shadow's solidity between zero and finalSolidity
 * depending on curr's relation to start and end.
 */
static s32 linearly_interpolate_positive(u8 finalSolidity, s16 curr, s16 start, s16 end) {
    if (curr < start) {
        return 0;
    } else if (end < curr) {
        return finalSolidity;
    } else {
        return (f32) finalSolidity * (curr - start) / (end - start);
    }
}

/**
 * Linearly interpolate a shadow's solidity between initialSolidity and zero
 * depending on curr's relation to start and end.
 */
static s32 linearly_interpolate_negative(u8 initialSolidity, s16 curr, s16 start, s16 end) {
    if (curr < start) {
        return initialSolidity;
    } else if (curr > end) {
        return 0;
    } else {
        return ((f32) initialSolidity * (1.0f - (f32)(curr - start) / (end - start)));
    }
}

/**
 * Change a player shadow's solidity based on the current animation frame.
 */
s32 set_player_shadow_scale_solidity(Vec3f scaleVec, f32 distToShadow, s16 shadowScale, u8 solidity) {
    // Set the shadow solidity manually for certain Mario animations.
    struct AnimInfo *animInfo = &gMarioObject->header.gfx.animInfo;
    s16 animFrame = animInfo->animFrame;

    shadowScale = scale_shadow_with_distance(shadowScale, distToShadow);
    vec3f_set(scaleVec, shadowScale, shadowScale, shadowScale);

    switch (animInfo->animID) {
        case MARIO_ANIM_IDLE_ON_LEDGE:
            return 0;
        case MARIO_ANIM_FAST_LEDGE_GRAB:
            return linearly_interpolate_positive(solidity, animFrame,  5, 14); // fade in
        case MARIO_ANIM_SLOW_LEDGE_GRAB:
            return linearly_interpolate_positive(solidity, animFrame, 21, 33); // fade in
        case MARIO_ANIM_CLIMB_DOWN_LEDGE:
            return linearly_interpolate_negative(solidity, animFrame,  0,  5); // fade out
        default:
            // Set solidity and scale based on distance.
            return dim_shadow_with_distance(solidity, distToShadow);
    }
}

/**
 * Change an object shadow's solidity and scale
 */
s32 set_object_shadow_scale_solidity(Vec3f scaleVec, f32 distToShadow, s16 shadowScale, s8 shadowType, u8 solidity) {
    // No shadow if the non-Mario object is too high.
    if (distToShadow > 1024) {
        return 0;
    }

    u8 finalSolidity = 0;

    // Get the scaling modifiers for rectangular shadows (Whomp and Spindel).
    if (shadowType >= SHADOW_RECTANGLE_HARDCODED_OFFSET) {
        s8 idx = shadowType - SHADOW_RECTANGLE_HARDCODED_OFFSET;
        if (sShadowRectangles[idx].scaleWithDistance) {
            scale_shadow_with_distance(shadowScale, distToShadow);
        }
        scaleVec[0] = shadowScale * sShadowRectangles[idx].scaleX;
        scaleVec[1] = shadowScale;
        scaleVec[2] = shadowScale * sShadowRectangles[idx].scaleZ;
        finalSolidity = dim_shadow_with_distance(solidity, distToShadow);
    } else {
        if (shadowType != SHADOW_SQUARE_PERMANENT) {
            // Set solidity and scale based on distance.
            shadowScale = scale_shadow_with_distance(shadowScale, distToShadow);
            finalSolidity = dim_shadow_with_distance(solidity, distToShadow);
        } else {
            finalSolidity = solidity;
        }
        vec3f_set(scaleVec, shadowScale, shadowScale, shadowScale);
    }

    return finalSolidity;
}

#ifdef VANILLA_CHECKS
/**
 * Slightly change the height of a shadow in levels with lava.
 */
s32 correct_lava_shadow_height(f32 *floorHeight) {
    if (gCurrLevelNum == LEVEL_BITFS) {
        if (*floorHeight < -3000) {
            *floorHeight = -3062;
            return FALSE;
        } else if (*floorHeight > 3400) {
            *floorHeight = 3492;
            return FALSE;
        }
    } else if (gCurrLevelNum == LEVEL_LLL && gCurrAreaIndex == 1) {
        *floorHeight = 5;
        return FALSE;
    }
    return TRUE;
}
#endif

/**
 * Add a shadow to the given display list.
 * shadowType 0 uses a circle texture, the rest use a square texture.
 * Uses environment u8 for shadow solidity.
 */
static Gfx *shadow_display_list(s8 shadowType, u8 solidity, s8 isDecal) {
    Gfx *gfxHead = alloc_display_list(5 * sizeof(Gfx));
    if (gfxHead == NULL) {
        return NULL;
    }
    Gfx *gfx = gfxHead;

    Gfx *dl_shadow_begin = isDecal ? dl_shadow_begin_decal : dl_shadow_begin_non_decal;
    Gfx *dl_shadow_shape;
    switch (shadowType) {
        case SHADOW_CIRCLE:
            dl_shadow_shape = dl_shadow_circle;
            break;
#if PROPER_TREE_SHADOWS
        case SHADOW_SPIKE:
            dl_shadow_shape = dl_shadow_spike;
            break;
#endif
        default:
            dl_shadow_shape = dl_shadow_square;
            break;
    }

    gSPDisplayList(gfx++, dl_shadow_begin);
    gSPDisplayList(gfx++, dl_shadow_shape);
    gDPSetEnvColor(gfx++, 255, 255, 255, solidity);
    gSPDisplayList(gfx++, dl_shadow_end);
    gSPEndDisplayList(gfx);

    return gfxHead;
}

f32 get_shadow_floor(f32 x, f32 y, f32 z, struct Surface** floor, struct Object* obj, s8 isPlayer, s8* shifted) {
    struct MarioState *m = gMarioState;
    f32 floorHeight = FLOOR_LOWER_LIMIT_MISC;
    s8 notHeldObj = (gCurGraphNodeHeldObject == NULL);

    // Attempt to use existing floors before finding a new one.
    if (notHeldObj && isPlayer && m->floor) {
        // The object is Mario and has a referenced floor.
        *floor      = m->floor;
        floorHeight = m->floorHeight;
    } else if (notHeldObj && (gCurGraphNodeObject != &gMirrorMario) && obj->oFloor) {
        // The object is not Mario but has a referenced floor.
        //! Some objects only get their oFloor from bhv_init_room, which skips dynamic floors.
        *floor      = obj->oFloor;
        floorHeight = obj->oFloorHeight;
    } else {
        // The object has no referenced floor, so find a new one.
        floorHeight = find_floor(x, y, z, floor);
        // Skip shifting the shadow height later, since the find_floor call above uses the already shifted position.
        *shifted = FALSE;
    }

    return floorHeight;
}

static s8 obj_is_flying_carpet(struct Object* obj) {
    return (
        obj != NULL &&
        obj->behavior == segmented_to_virtual(bhvPlatformOnTrack) &&
        obj->oPlatformOnTrackType == PLATFORM_ON_TRACK_TYPE_CARPET
    );
}

//! TODO: Split create_shadow_below_xyz into multiple functions
/**
 * Create a shadow at the absolute position given, with the given parameters.
 * Return a pointer to the display list representing the shadow.
 */
Gfx *create_shadow_below_xyz(Vec3f pos, Vec3f floorNormal, Vec3f scaleVec, s16 shadowScale, u8 solidity, s8 shadowType, s8 shifted, s8 *isDecal) {
    struct Object *obj = ((struct Object *)gCurGraphNodeObject);

    // Check if the object exists.
    if (obj == NULL) {
        return NULL;
    }

    // The floor underneath the object.
    struct Surface *floor = NULL;

    // -- Check for floors --

    f32 x = pos[0];
    f32 y = pos[1];
    f32 z = pos[2];
    s8 isPlayer = (obj == gMarioObject);

    // The y-position of the floor (or water or lava) underneath the object.
    f32 floorHeight = get_shadow_floor(x, y, z, &floor, obj, isPlayer, &shifted);

    // No shadow if the position is OOB.
    if (floor == NULL) {
        return NULL;
    }

    // -- Handle water and other translucent surfaces --

    // The shadow is a decal by default.
    *isDecal = TRUE;

    // Check for water under the shadow.
#if WATER_SURFACES
    struct Surface *waterFloor = NULL;
    f32 waterLevel = find_water_level_and_floor(x, z, &waterFloor);
#else
    f32 waterLevel = find_water_level(x, z);
#endif

    // Whether the floor is an environment box rather than an actual surface.
    s8 isEnvBox = FALSE;

    // An offset to apply to the shadow's height at the end.
    f32 heightOffset = 0.0f;

    if (waterLevel > FLOOR_LOWER_LIMIT_MISC
        && y >= waterLevel
        && floorHeight <= waterLevel) {
        // Skip shifting the shadow height later, since the find_water_level_and_floor call above uses the already shifted position.
        shifted = FALSE;

        // If there is water under the shadow, put the shadow on the water.
        floorHeight = waterLevel;

        // Don't use the decal layer, since water is transparent.
        *isDecal = FALSE;

#if WATER_SURFACES
        // Check whether the water is an environment box or a water surface.
        if (waterFloor != NULL) { // Water surfaces:
            floor = waterFloor;
        } else { // Environment boxes:
            isEnvBox = TRUE;
        }
#else
        isEnvBox = TRUE;
#endif
    } else { // Normal surfaces:
        TerrainData type = floor->type;
        if (type == SURFACE_ICE) {
            // Ice floors are usually transparent.
            *isDecal = FALSE;
#ifdef VANILLA_CHECKS
        } else if (type == SURFACE_BURNING) {
            // Set the shadow height to the lava height in specific areas.
            *isDecal = correct_lava_shadow_height(&floorHeight);
#endif
        } else {
            // Check if the shadow is on the flying carpet.
            if (obj_is_flying_carpet(floor->object)) {
                // Raise the shadow 5 units on the flying carpet to avoid clipping issues.
                heightOffset += 5;
                // The flying carpet is transparent.
                *isDecal = FALSE;
            }
        }
    }

    // -- Floor normals --

    f32 nx, ny, nz;
    if (isEnvBox) {
        // Assume the floor is flat.
        nx = 0.0f;
        ny = 1.0f;
        nz = 0.0f;
    } else {
        // Read the floor's normals.
        nx = floor->normal.x;
        ny = floor->normal.y;
        nz = floor->normal.z;

        // No shadow if the y-normal is negative (downward facing surface).
        if (!F32_IS_NONZERO(ny)) {
            return NULL;
        }

        // If the animation changes the shadow position, move its height to the new position.
        if (shifted) {
            floorHeight = -((x * nx) + (z * nz) + floor->originOffset) / ny;
        }
    }

    // Set the floor normals in the shadow struct.
    vec3f_set(floorNormal, nx, ny, nz);

    // -- Height checks --

    // Apply y offset.
    floorHeight += heightOffset;

    // No shadow if the floor is lower than expected possible,
    if (floorHeight < FLOOR_LOWER_LIMIT_MISC) {
        return NULL;
    }

    // Get the vertical distance to the shadow, now that the final shadow height is set.
    f32 distToShadow = (y - floorHeight);

    // No shadow if the object is below it.
    if (distToShadow < -80) {
        return NULL;
    }

    // -- Scale & solidity --

    if (isPlayer) {
        solidity = set_player_shadow_scale_solidity(scaleVec, distToShadow, shadowScale, solidity);
    } else {
        solidity = set_object_shadow_scale_solidity(scaleVec, distToShadow, shadowScale, shadowType, solidity);
    }

    if (solidity == 0) {
        return NULL;
    }

    // Move the shadow position to the floor height.
    pos[1] = floorHeight;

    // Generate the shadow display list with type and solidity.
    return shadow_display_list(shadowType, solidity, *isDecal);
}
