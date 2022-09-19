#ifndef QOL_DEFINES_H
#define QOL_DEFINES_H

// Quality of life defines
// Mostly a compilation of code provided by various people

// Credits are provided as how I (AloXado320) remember
// Note: If credits says "Easy fix", it means that by
// looking at the code with "//!" anyone can fix it (not always the case)

// You can also stub the defines if you don't want them to be applied

// Framebuffer Detection
#ifdef TARGET_N64
#define HAS_FRAMEBUFFER 1
#elif defined(RAPI_GL) || defined(RAPI_D3D11)
#define HAS_FRAMEBUFFER 1
#else
#define HAS_FRAMEBUFFER 0
#endif

// --| Quality of life redone files
/// Adds Zelda level select used on OOT, MM and Animal Forest
/// Credits: (AloXado320)
#define ZELDA_STYLE_LEVEL_SELECT (0 || QOL_REDONE)
/// Adds improved platform displacement with intertia
#define PLATFORM_DISPLACEMENT_2 (0 || QOL_REDONE)
/// Uses optimized shadows which are faster than vanilla
#define OPTIMIZED_SHADOWS (0 || QOL_REDONE)

// --| Quality of life features
/// Adds an extra Z button trig for some menu files (Originally defined in EU)
/// Credits: (Original Devs)
#define QOL_FEATURE_Z_BUTTON_EXTRA_OPTION (0 || VERSION_EU || QOL_FEATURES)
/// Adds Mario's Face Easter Egg (Originally defined in SH)
/// Credits: (Original Devs)
#define QOL_FEATURE_MARIO_HEAD_EASTER_EGG (0 || VERSION_SH || (QOL_FEATURES && GODDARD_MFACE && HAS_FRAMEBUFFER))
/// Adds unused cracked ice object in Snowman Land
/// Credits: (Original Devs, SunlitSpace542, Arceveti)
#define QOL_FEATURE_SSL_CRACKED_ICE (0 || QOL_FEATURES)
/// Changes WF breakable wall by no taking damage and returning safely if the proper wall is broken
/// Credits: (AloXado320)
#define QOL_FEATURE_BETTER_WF_BREAKEABLE_WALL (0 || QOL_FEATURES)
/// Makes cutscene object camera correctly focus an object in a room
/// Credits: (AloXado320)
#define QOL_FEATURE_ROOM_OBJECT_CAMERA_FOCUS (0 || QOL_FEATURES || !VANILLA_CHECKS)
/// Makes red coin star marker correctly be in dynamic floors and water
/// Credits: (AloXado320)
#define QOL_FEATURE_BETTER_REDS_STAR_MARKER (0 || QOL_FEATURES || !VANILLA_CHECKS)
/// Changes blue coin switch to respawn instead of disappearing
/// Credits: (Arceveti)
#define QOL_FEATURE_RESPAWN_BLUE_COIN_SWITCH (0 || QOL_FEATURES)
/// Changes obj_resolve_object_collisions to work consistently
/// Credits: (Arceveti)
#define QOL_FEATURE_BETTER_OBJ_COLLISIONS (0 || QOL_FEATURES)
/// Makes leaf particles occasionally fall from trees which contain Hoot 
/// Credits: (Arceveti)
#define QOL_FEATURE_HOOT_TREE_PARTICLES (0 || QOL_FEATURES)
/// Makes Tiny Goombas (from THI) always drop their coin
/// Credits: (Arceveti)
#define QOL_FEATURE_TINY_GOOMBA_DROP_COIN (0 || QOL_FEATURES)
/// Clams don't hurt Mario unless they are moving (opening/closing)
/// Credits: (Arceveti)
#define QOL_FEATURE_CLAMS_ONLY_HURT_WHEN_MOVING (0 || QOL_FEATURES)
/// Makes speed of a platform on a track be controlled by standing near the front or back of it
/// Credits: (Arceveti)
#define QOL_FEATURE_CONTROLLABLE_PLATFORM_SPEED (0 || QOL_FEATURES)
/// Use intendedYaw to control Hoot instead of raw left and right inputs
/// Credits: (Arceveti)
#define QOL_FEATURE_BETTER_HOOT_YAW_CONTROL (0 || QOL_FEATURES)
/// Makes Koopa Shell boxes respawn
/// Credits: (Arceveti)
#define QOL_FEATURE_KOOPA_SHELL_BOXES_RESPAWN (0 || QOL_FEATURES)
/// Makes rooms code use find_room_floor, and improves bhv_init_room
/// Credits: (Arceveti)
#define QOL_FEATURE_BETTER_ROOM_CHECKS (0 || QOL_FEATURES)

// --| Quality of life fixes
// --| Code Fixes
/// Fixes bug where the castle trap sound in the entrance of Bowser 1 doesn't play
/// Credits: (Easy Fix)
#define QOL_FIX_CASTLE_TRAP_SOUND (0 || QOL_FIXES)
/// Fixes manta's water rings to match where it looks
/// Credits: (Kaze Emanuar)
#define QOL_FIX_WATER_RING (0 || QOL_FIXES)
/// Fixes an oddly defined interaction sub type in penguin mother behavior
/// Credits: (Easy Fix)
#define QOL_FIX_TUXIE_HELD_STATE (0 || QOL_FIXES)
/// Fixes Bully minion knockback timer by reseting it, more info in the fix itself
/// Credits: (Easy Fix)
#define QOL_FIX_BULLY_KNOCKBACK_TIMER (0 || QOL_FIXES)
/// Fixes camera height in BOB and adds missing breaks in code
/// Credits: (Easy Fix)
#define QOL_FIX_CAMERA_BOSS_FIGHT_HEIGHT (0 || QOL_FIXES)
/// Fixes complete coins not giving lives every 50 coins after 150 coins
/// Credits: (coltongit)
#define QOL_FIX_COMPLETE_COURSE_50_COINS (0 || QOL_FIXES)
/// Fixes cap cloning when Mario takes a fade warp
/// Credits: (AloXado320)
#define QOL_FIX_HAT_CLONE_FADE (0 || QOL_FIXES)
/// Fixes incorrect yellow sparkle offset positions
/// Credits: (Easy Fix)
#define QOL_FIX_YELLOW_SPARKLES_OFFSET (0 || QOL_FIXES)
/// Fixes weird overflow when object is in oob away from steep floor
/// Credits: (Easy Fix)
#define QOL_FIX_OOB_OBJ_CRASH_OVERFLOW (0 || QOL_FIXES)
/// Fixes Seaweed missing first anim frame
/// Credits: (Easy Fix)
#define QOL_FIX_MISSING_SEAWEED_ANIMFRAME (0 || QOL_FIXES)
/// Fixes BITS tilting pyramid y distance
/// Credits: (Easy Fix)
#define QOL_FIX_TILTING_PYRAMID_Y_DISTANCE (0 || QOL_FIXES)
/// Fixes King Bob-omb music still playing while you go away after throwing him off
/// Credits: (AloXado320)
#define QOL_FIX_KING_BOBOMB_MUSIC_THROWN_OFF (0 || QOL_FIXES)
/// Fixes instant warp offset not working when warping across different areas
/// Credits: (Reonu)
#define QOL_FIX_INSTANT_WARP_OFFSET (0 || QOL_FIXES)
/// Fixes missing surface wind in obj_check_floor_death
/// Credits: (Easy Fix)
#define QOL_FIX_OBJ_FLOOR_WIND_DEATH (0 || QOL_FIXES)
/// Fixes hardcoded snow tree leaf particles
/// Credits: (Easy Fix)
#define QOL_FIX_HARDCODED_TREE_PARTICLES (0 || QOL_FIXES || !VANILLA_CHECKS)
/// Fixes monty mole hide in hole check
/// Credits: (Easy Fix)
#define QOL_FIX_HIDE_IN_HOLE_NULL_CHECK (0 || QOL_FIXES)
/// Credits: (Easy Fix)
/// Fixes Z rotation when spawning an object with rotation
#define QOL_FIX_SPAWN_OBJECT_ANGLE_ROLL (0 || QOL_FIXES)
/// Fixes boo hit velocity so they actually oscillate up then down
/// Credits: (nim)
#define QOL_FIX_BOO_MOVE_HIT_VELOCITY (0 || QOL_FIXES)
/// Fixes Bowser being invisible in BITFS after grabbing him
/// Credits: (AloXado320)
#define QOL_FIX_BOWSER_TRANSPARENT_HELD (0 || QOL_FIXES)
/// Fixes one frame timer when bully backs up
/// Credits: (coltongit)
#define QOL_FIX_BULLY_BACK_UP_TIMER (0 || QOL_FIXES)
/// Fixes (or rather, adjusts) Mario's head look at bosses
/// Credits: (coltongit)
#define QOL_FIX_MARIO_LOOK_HEAD_BOSSES (0 || QOL_FIXES)
/// Fixes pss slide value not being reset on exit
/// Credits: (AloXado320)
#define QOL_FIX_RESET_PSS_SLIDE_STARTED (0 || QOL_FIXES)
/// Fixes mist particles not spawning with an underwater shell
/// Credits: (PyroJay4)
#define QOL_FIX_DROPPED_UNDERWATER_SHELL (0 || QOL_FIXES)
/// Fixes platform on track checkered detection
/// Credits: (AloXado320)
#define QOL_FIX_PLATFORM_TRACK_CHECKERED (0 || QOL_FIXES)
/// Fixes cutscenes where Mario goes out of camera view on moving platforms (PD2 already has this)
/// Credits: (AloXado320)
#define QOL_FIX_CAMERA_CUTSCENE_MOVING_PLATFORMS (0 || QOL_FIXES)
/// Fixes lower horizontal wind speed value
/// Credits: (Easy Fix)
#define QOL_FIX_HORIZONTAL_WIND_SPEED (0 || QOL_FIXES)
/// Fixes fake pole grab on the bottom of it, allowing to be properly grabbed
/// Credits: (Arceveti)
#define QOL_FIX_POLE_BOTTOM_GRAB (0 || QOL_FIXES)
/// Fixes spawnable star softlock when a cutscene is already playing
/// Credits: (Arceveti)
#define QOL_FIX_SPAWNED_STAR_SOFTLOCK (0 || QOL_FIXES)
/// Fixes goomba jump in midair if it falls
/// Credits: (Arceveti)
#define QOL_FIX_GOOMBA_JUMP_AIR (0 || QOL_FIXES)
/// Fixes big goombas marked as dead in a triplet mark
/// Credits: (Arceveti)
#define QOL_FIX_GOOMBA_DEAD_ATTACKED_MARIO (0 || QOL_FIXES)
/// Fixes missing floor update in push_mario_out_of_object
/// Credits: (Arceveti)
#define QOL_FIX_PUSH_MARIO_OUT_OF_OBJECT_FLOOR (0 || QOL_FIXES)
/// Fixes Mario interact shell start action while in air
/// Credits: (Arceveti)
#define QOL_FIX_MARIO_KOOPA_SHELL_ACTION (0 || QOL_FIXES)
/// Fixes palm height hardcoded course check and height when climbing up/down
/// Credits: (Arceveti)
#define QOL_FIX_PALM_TREE_LEAF_HEIGHT (0 || QOL_FIXES || !VANILLA_CHECKS)
/// Fixes shell speed water level origin offset
/// Credits: (Arceveti)
#define QOL_FIX_SHELL_SPEED_NEGATIVE_OFFSET (0 || QOL_FIXES)
/// Fixes possible weird behavior when spiny didn't have a proper parent object
/// Credits: (Arceveti)
#define QOL_FIX_SPINY_CHECK_ACTIVE_PARENT (0 || QOL_FIXES)
/// Fixes Mr L eyeball billboard position
/// Credits: (Arceveti)
#define QOL_FIX_MR_I_EYEBALL_POSITION (0 || QOL_FIXES)
/// Fixes Mr L iris parent object when it deactivates
/// Credits: (Arceveti)
#define QOL_FIX_MR_I_DELETED_PARENT (0 || QOL_FIXES)
/// Fixes find_floor_slope so it handles OOB slopes
/// Credits: (Arceveti)
#define QOL_FIX_FLOOR_SLOPE_OOB (0 || QOL_FIXES)
/// Fixes star door room rendering
/// Credits: (Arceveti)
#define QOL_FIX_STAR_DOOR_ROOM_RENDER (0 || QOL_FIXES)

// --| Unused Code Fixes (for convenience)
/// Fixes (or rather removes) 0 yaw code in Beta Chest object
/// Credits: (Easy Fix)
#define QOL_FIX_UNUSED_BETA_CHEST_YAW (0 || QOL_FIXES)
/// Fixes play_mode_unused inclusion so it's "used" as a default "invalid" play mode switch
/// Credits: (Arceveti)
#define QOL_FIX_UNUSED_PLAY_MODE (0 || QOL_FIXES)

// --| Assets Fixes (Mostly on vanilla levels)
/// Fixes impossible coins (also fixes impossible Goomba since it's related)
/// Credits: (AloXado320)
#define QOL_FIX_ASSET_IMPOSSIBLE_COINS (0 || QOL_FIXES)
/// Fixes 1up locations in CCM slide
/// Credits: (Arceveti)
#define QOL_FIX_ASSET_CCM_SLIDE_1UPS (0 || QOL_FIXES)

#endif // QOL_DEFINES_H
