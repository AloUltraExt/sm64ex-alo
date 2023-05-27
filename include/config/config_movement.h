#pragma once

/*********************
 * MOVEMENT SETTINGS *
 *********************/

/// Fixes limited jumping on non slippery surfaces.
#define FIX_JUMP_KICK_NOT_SLIPPERY (0 || QOL_FIXES)

/// Fixes slide action so they have short hitbox.
#define FIX_SHORT_HITBOX_SLIDE_ACTS (0 || QOL_FIXES)

/// Fixes undefined anim return in the hit wall code, more info in the fix itself.
#define FIX_HIT_WALL_ACTION (0 || QOL_FIXES)

/// Fixes bonks when ground pounding next to a wall.
#define FIX_GROUND_POUND_WALL (0 || QOL_FIXES)

/// Fixes several stationary bugs by perform ground steps while standing still.
#define FIX_STATIONARY_GROUND_STEPS (0 || QOL_FIXES)

/// Fixes bonks when walking into a wall.
#define FIX_LESS_GROUND_BONKS (0 || QOL_FIXES)

/// Fixes input polling by setting an initial min walking speed.
#define FIX_INITIAL_WALKING_SPEED (0 || QOL_FIXES)

/// Fixes slideVel position being slightly off/asymmetric.
#define FIX_SLIDE_VEL_UPDATE_SLIDING (0 || QOL_FIXES)

/// Fixes cutscenes where Mario goes out of camera view on moving platforms (PD2 already has this).
#define FIX_CAMERA_CUTSCENE_MOVING_PLATFORMS (0 || QOL_FIXES)

/// Fixes find_floor_slope so it handles OOB slopes.
#define FIX_FLOOR_SLOPE_OOB (0 || QOL_FIXES || COLLISION_FIXES)

/// Fixes water upwarp, enables with collision fixes due to water surfaces.
#define FIX_WATER_PLUNGE_UPWARP (0 || QOL_FIXES || COLLISION_FIXES)

/// Fixes fake ledge grab on steep slopes.
#define FIX_LEDGE_GRAB_STEEP_SLOPES (0 || QOL_FIXES)

/// Fixes eating inputs on landing actions.
#define FIX_ACTION_LAND_EAT_INPUT (0 || QOL_FIXES)

/// Adds more air steps to special triple jump such as wallkick and grabbing.
#define SPECIAL_TRIPLE_JUMP_AIR_STEPS (0 || QOL_FEATURES)

/// Makes Mario grab hangable ceilings while in the air more freely.
#define HANGABLE_SURFACE_AIR_FREELY (0 || QOL_FEATURES)

/// Improves hanging so you don't need to hold A to stay on the ceiling.
#define BETTER_HANGING (0 || QOL_FEATURES)

/// Improves flying so it's more responsive and smoother.
#define BETTER_FLYING (0 || QOL_FEATURES)

/// Makes turning walking speed based of velocity.
#define VELOCITY_BASED_TURN_SPEED (0 || QOL_FEATURES)

// If A and Z are pressed on the same frame while running, Mario will long jump instead of ground pound.
#define EASIER_LONG_JUMPS (0 || QOL_FEATURES)

// Makes Mario be able to jump kick when you hold the opposite direction of where you go.
#define EASIER_JUMP_KICKS (0 || QOL_FEATURES)

// Allows Mario to grab a ledge after a triple jump and a rollout.
#define LEDGE_GRAB_MORE_ACTIONS (0 || QOL_FEATURES)

// Allows Mario to walking after a dive at lower speed and a rollout.
#define WALL_KICK_MORE_ACTIONS (0 || QOL_FEATURES)

// Allows Mario to still held an object while twirling.
#define TWIRL_WITH_OBJECT (0 || QOL_FEATURES)

// Allows Mario to use the B button to rollout while on a kick slide.
#define SLIDE_KICK_SLIDE_BUTTON (0 || QOL_FEATURES)

/// Makes rollout possible on a dive slide while going forward.
#define DIVE_SLIDE_ROLLOUT (0 || QOL_FEATURES)

/*******************
 * ACTION SETTINGS *
 *******************/

/// Fixes open door key cutscene on 90-270 degrees.
#define FIX_DOOR_KEY_CUTSCENE (0 || QOL_FIXES)

/// Fixes surface wind detection (avoid grabbed star wind softlock).
#define FIX_SURFACE_WIND_DETECTION (0 || QOL_FIXES)

/// Fixes Mario's interaction with lava so it detects regardless of action.
#define FIX_LAVA_INTERACTION (0 || QOL_FIXES)

/// Makes Mario's squish scale smooth rather than being instantly set.
#define SMOOTH_SQUISH (0 || QOL_FEATURES)

/// When Mario hits a floor underwater, his pitch approaches the floor pitch instead of instantly snapping to it.
#define SMOOTH_PITCH_WHEN_HITTING_FLOOR_UNDERWATER (0 || QOL_FEATURES)

/// Makes it slightly easier to stay on narrow platforms.
#define LEDGE_CLIMB_PROTECTION (0 || QOL_FEATURES)

/// Improves exit airborne by setting an animation and smooth scale at the start of it.
#define BETTER_EXIT_AIRBORNE (0 || QOL_FEATURES)
