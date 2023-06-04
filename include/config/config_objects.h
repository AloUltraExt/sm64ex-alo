#pragma once

/************************
 * INTERACTION SETTINGS *
 ***********************/

/// Fixes cap cloning when Mario takes a fade warp
#define FIX_HAT_CLONE_FADE (0 || QOL_FIXES)

/// Fixes fake pole grab on the bottom of it, allowing to be properly grabbed
#define FIX_POLE_BOTTOM_GRAB (0 || QOL_FIXES)

/// Fixes missing surface wind in obj_check_floor_death
#define FIX_OBJ_FLOOR_WIND_DEATH (0 || QOL_FIXES)

/// Fixes Mario interact shell start action while in air
#define FIX_MARIO_KOOPA_SHELL_ACTION (0 || QOL_FIXES)

/// Hold A when bouncing on an enemy to go higher like in classic games.
#define JUMP_ENEMY_BOUNCE_BOOST (0 || QOL_FEATURES)

/// Changes obj_resolve_object_collisions to work consistently
#define BETTER_RESOLVE_OBJ_COLLISIONS (0 || QOL_FEATURES)

/// Fixes missing floor update in push_mario_out_of_object
#define FIX_PUSH_MARIO_OUT_OF_OBJECT_FLOOR (0 || QOL_FIXES || COLLISION_FIXES)

/// Makes rooms code use find_room_floor, and improves bhv_init_room
#define BETTER_ROOM_CHECKS (0 || QOL_FEATURES || COLLISION_FIXES)

/*******************
 * OBJECT SETTINGS *
 *******************/

/// Fixes bug where the castle trap sound in the entrance of BITDW doesn't play
#define FIX_CASTLE_TRAP_SOUND (0 || QOL_FIXES)

/// Fixes manta's water rings to match where it looks
#define FIX_WATER_RING_POSITION (0 || QOL_FIXES)

/// Fixes Bully minion knockback timer by reseting it, more info in the fix itself
#define FIX_BULLY_KNOCKBACK_TIMER (0 || QOL_FIXES)

/// Fixes King Bob-omb music still playing while you go away after throwing him off
#define FIX_KING_BOBOMB_MUSIC_THROWN_OFF (0 || QOL_FIXES)

/// Fixes monty mole hide in hole check
#define FIX_HIDE_IN_HOLE_NULL_CHECK (0 || QOL_FIXES)

/// Fixes boo hit velocity so they actually oscillate up then down
#define FIX_BOO_MOVE_HIT_VELOCITY (0 || QOL_FIXES)

/// Fixes Bowser being invisible in BITFS after grabbing him
#define FIX_BOWSER_TRANSPARENT_HELD (0 || QOL_FIXES)

/// Fixes one frame timer when bully backs up
#define FIX_BULLY_BACK_UP_TIMER (0 || QOL_FIXES)

/// Properly adjusts Mario's head to look at bosses
#define FIX_MARIO_LOOK_HEAD_BOSSES (0 || QOL_FIXES)

/// Fixes mist and purple particles not being spawned after specific objects are deleted
#define FIX_PARTICLES_CALL_DELETED (0 || QOL_FIXES)

/// Fixes platform on track checkered detection
#define FIX_PLATFORM_TRACK_CHECKERED (0 || QOL_FIXES)

/// Fixes spawnable star softlock when a cutscene is already playing
#define FIX_SPAWNED_STAR_SOFTLOCK (0 || QOL_FIXES)

/// Fixes goomba jump in midair when it falls
#define FIX_GOOMBA_JUMP_AIR (0 || QOL_FIXES)

/// Fixes big goombas marked as dead in a triplet mark
#define FIX_GOOMBA_DEAD_ATTACKED_MARIO (0 || QOL_FIXES)

/// Fixes possible weird behavior when spiny didn't have a proper parent object
#define FIX_SPINY_CHECK_ACTIVE_PARENT (0 || QOL_FIXES)

/// Fixes Mr L eyeball billboard position
#define FIX_MR_I_EYEBALL_POSITION (0 || QOL_FIXES)

/// Fixes Mr L iris parent object when it deactivates
#define FIX_MR_I_DELETED_PARENT (0 || QOL_FIXES)

/// Fixes star door room rendering
#define FIX_STAR_DOOR_ROOM_RENDER (0 || QOL_FIXES)

/// Fixes castle metal door not playing it's proper sounds
#define FIX_METAL_DOOR_CASTLE_SOUND (0 || QOL_FIXES)

/// Fixes unreachable stars if they close to a ceiling
#define FIX_STARS_ON_CEILINGS (0 || QOL_FIXES)

/// Fixes NPC interaction button so it's like the japanese version
#define FIX_INTERACT_READING_BUTTON (0 || QOL_FIXES)

/// Fixes hardcoded snow tree leaf particles
#define FIX_HARDCODED_TREE_PARTICLES (0 || QOL_FIXES || !VANILLA_CHECKS)

/// Fixes palm height hardcoded course check and height when climbing up/down
#define FIX_PALM_TREE_LEAF_HEIGHT (0 || QOL_FIXES || !VANILLA_CHECKS)

/// Adds unused cracked ice object back in Snowman's Land
#define SNOWMAN_LAND_CRACKED_ICE_ACT (0 || QOL_FEATURES)

/// Changes WF breakable wall by safely landing back if the proper wall is broken
#define BETTER_WF_BREAKEABLE_WALL (0 || QOL_FEATURES)

/// Changes blue coin switch to respawn instead of disappearing
#define RESPAWN_BLUE_COIN_SWITCH (0 || QOL_FEATURES)

/// Makes leaf particles occasionally fall from trees which contain Hoot 
#define HOOT_TREE_PARTICLES (0 || QOL_FEATURES)

/// Makes Tiny Goombas (from THI) always drop their coin
#define TINY_GOOMBA_DROP_COIN (0 || QOL_FEATURES)

/// Clams don't hurt Mario unless they are moving (opening/closing)
#define CLAMS_ONLY_HURT_WHEN_MOVING (0 || QOL_FEATURES)

/// Makes speed of a platform on a track be controlled by standing near the front or back of it
#define CONTROLLABLE_PLATFORM_SPEED (0 || QOL_FEATURES)

/// Use intendedYaw to control Hoot instead of raw left and right inputs
#define BETTER_HOOT_YAW_CONTROL (0 || QOL_FEATURES)

/// Makes Koopa Shell respawn on exclamation boxes like caps
#define KOOPA_SHELL_BOXES_RESPAWN (0 || QOL_FEATURES)

/// Makes Mr I being able to shoot his particle in any direction.
#define MR_I_PITCH_SHOOTING (0 || QOL_FEATURES)

/// Makes coin formation on ground have better coin position, fixes misaligned coins
#define BETTER_COIN_FORMATION_GROUND (0 || QOL_FEATURES || COLLISION_FIXES)

/// Makes red coin star marker correctly be in dynamic floors and water
#define BETTER_REDS_STAR_MARKER (0 || QOL_FEATURES || !VANILLA_CHECKS)
