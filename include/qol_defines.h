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

// --| Quality of life features
/// Adds an extra Z button trig for some menu files (Originally defined in EU)
/// Credits: (Original Devs)
#define QOL_FEATURE_Z_BUTTON_EXTRA_OPTION (0 || VERSION_EU || QOL_FEATURES)
/// Adds Mario's Face Easter Egg (Originally defined in SH)
/// Credits: (Original Devs)
#define QOL_FEATURE_MARIO_HEAD_EASTER_EGG (0 || VERSION_SH || (QOL_FEATURES && GODDARD_MFACE && HAS_FRAMEBUFFER))
/// Adds more air steps to special triple jump such as wallkick and grabbing
/// Credits: (Vatuu)
#define QOL_FEATURE_SPECIAL_TRIPLE_JUMP_AIR_STEPS (0 || QOL_FEATURES)
/// Changes how Mario grabs a star so a transparent star is properly shown after being collected
/// Credits: (Vatuu, AloXado320)
#define QOL_FEATURE_PROPER_SHOW_COLLECTABLE (0 || QOL_FEATURES)
/// Correctly changes star model to be transparent when (Klepto and Unagi) stars are collected
/// Credits: (Vatuu, AloXado320, SunlitSpace542)
#define QOL_FEATURE_BEH_HELD_TRANSPARENT_STAR (0 || QOL_FEATURES)
/// Properly adds unused SSL Pyramid cutscene after standing on the 4 pillars
/// Credits: (Vatuu, AloXado320, SunlitSpace542, Arceveti)
#define QOL_FEATURE_SSL_PYRAMID_CUTSCENE (0 || QOL_FEATURES)
/// Adds unused sad eyes for the penguin mother when he lost it's baby
/// Credits: (Vatuu, Arceveti)
#define QOL_FEATURE_TUXIES_MOTHER_SAD_EYES (0 || QOL_FEATURES)
/// Adds unused cracked ice object in Snowman Land
/// Credits: (Original Devs, SunlitSpace542, Arceveti)
#define QOL_FEATURE_SSL_CRACKED_ICE (0 || QOL_FEATURES)
/// Adds blinking to King Bob-omb, reusing it's unused blinking texture
/// Credits: (AloXado320)
#define QOL_FEATURE_KING_BOBOMB_BLINK (0 || QOL_FEATURES)
/// Changes WF breakable wall by no taking damage and returning safely if the proper wall is broken
/// Credits: (AloXado320)
#define QOL_FEATURE_BETTER_WF_BREAKEABLE_WALL (0 || QOL_FEATURES)
/// Changes C-Up vanilla camera similar to the DS version
/// Credits: (AloXado320)
#define QOL_FEATURE_C_UP_DS (0 || QOL_FEATURES)
/// Adds "new" star grab action that uses floating star dance if on a lethal floor
/// Credits: (AloXado320)
#define QOL_FEATURE_STAR_GRAB_NO_FALL_DEATH (0 || QOL_FEATURES)
/// Makes Mario grab hangable ceilings in any air actions
/// Credits: (AloXado320)
#define QOL_FEATURE_HANG_AIR_ANYWHERE (0 || QOL_FEATURES)
/// Automatically calculate the optimal collision distance for an object based on its vertices.
/// Credits: (Kaze)
#define QOL_FEATURE_AUTO_COLLISION_DISTANCE (0 || QOL_FEATURES)
/// Changes blue coin switch to respawn instead of disappearing
/// Credits: (Arceveti)
#define QOL_FEATURE_RESPAWN_BLUE_COIN_SWITCH (0 || QOL_FEATURES)
/// Changes hanging so you don't need to hold A to stay hanging, adjusts speed and position
/// Credits: (Arceveti)
#define QOL_FEATURE_BETTER_HANGING (0 || QOL_FEATURES)
/// Makes Mario not fall after star grab if the floor is too far below
/// Credits: (Arceveti)
#define QOL_FEATURE_STAR_GRAB_NO_FALL_HEIGHT (0 || QOL_FEATURES)
/// Changes obj_resolve_object_collisions to work consistently
/// Credits: (Arceveti)
#define QOL_FEATURE_BETTER_OBJ_COLLISIONS (0 || QOL_FEATURES)
/// Use the floor's normal instead of a triangle of find_floor if the floor isn't steep
/// Credits: (Arceveti)
#define QOL_FEATURE_FAST_FLOOR_ALIGN (0 || QOL_FEATURES)
/// Makes Mario's squish scale smooth rather than being instantly set
/// Credits: (Arceveti)
#define QOL_FEATURE_SMOOTH_SQUISH (0 || QOL_FEATURES)
/// Makes the pitch change when hitting the floor underwater smooth instead of instant
/// Credits: (Arceveti)
#define QOL_FEATURE_SMOOTH_WATER_FLOOR_PITCH (0 || QOL_FEATURES)
/// Hold A when bouncing on an enemy to go higher
/// Credits: (Arceveti)
#define QOL_FEATURE_BOUNCE_BOOST (0 || QOL_FEATURES)
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
/// Makes it slightly easier to stay on narrow platforms
/// Credits: (Arceveti)
#define QOL_FEATURE_LEDGE_PROTECTION (0 || QOL_FEATURES)
/// Makes Koopa Shell boxes respawn
/// Credits: (Arceveti)
#define QOL_FEATURE_KOOPA_SHELL_BOXES_RESPAWN (0 || QOL_FEATURES)
// --| Quality of life fixes
// --| Code Fixes
/// Fixes bug where the castle trap sound in the entrance of Bowser 1 doesn't play
/// Credits: (Easy Fix)
#define QOL_FIX_CASTLE_TRAP_SOUND (0 || QOL_FIXES)
/// Fixes manta's water rings to match where it looks
/// Credits: (Kaze Emanuar)
#define QOL_FIX_WATER_RING (0 || QOL_FIXES)
/// Fixes object counter so it correctly gets proper value when updating objects
/// Credits: (Easy Fix)
#define QOL_FIX_OBJ_COUNT_LIST (0 || QOL_FIXES)
/// Fixes missing sounds in key exit cutscene caused by missing "breaks" in code
/// Credits: (Easy Fix)
#define QOL_FIX_MISSING_SOUNDS_KEY_EXIT (0 || QOL_FIXES)
/// Fixes fake pole grab on the bottom of it, allowing to be properly grabbed
/// Credits: (Reonu, Arceveti)
#define QOL_FIX_POLE_BOTTOM_GRAB (0 || QOL_FIXES)
/// Fixes an oddly defined interaction sub type in penguin mother behavior
/// Credits: (Easy Fix)
#define QOL_FIX_TUXIE_HELD_STATE (0 || QOL_FIXES)
/// Fixes Bully minion knockback timer by reseting it, more info in the fix itself
/// Credits: (Easy Fix)
#define QOL_FIX_BULLY_KNOCKBACK_TIMER (0 || QOL_FIXES)
/// Fixes camera height in water while being Metal
/// Credits: (Easy Fix)
#define QOL_FIX_CAMERA_WATER_HEIGHT (0 || QOL_FIXES)
/// Fixes camera height in BOB and adds missing breaks in code
/// Credits: (Easy Fix)
#define QOL_FIX_CAMERA_BOSS_FIGHT_HEIGHT (0 || QOL_FIXES)
/// Fixes audio code preload sequence so it checks sequences instead of banks
/// Credits: (Easy Fix)
#define QOL_FIX_AUDIO_LOAD_BANK_NOT_SEQUENCE (0 || QOL_FIXES)
/// Fixes drowing sound continously playing while Metal
/// Credits: (AdyaGD)
#define QOL_FIX_DROWING_SOUND_METAL (0 || QOL_FIXES)
/// Fixes complete coins not giving lives every 50 coins after 150 coins
/// Credits: (coltongit)
#define QOL_FIX_COMPLETE_COURSE_50_COINS (0 || QOL_FIXES)
/// Fixes cap cloning when Mario takes a fade warp
/// Credits: (AloXado320)
#define QOL_FIX_HAT_CLONE_FADE (0 || QOL_FIXES)
/// Fixes open door key cutscene on 90-270 degrees
/// Credits: (AloXado320)
#define QOL_FIX_DOOR_KEY_CUTSCENE (0 || QOL_FIXES)
/// Fixes cutscene loop code (see comment in the fix)
/// Credits: (Easy Fix)
#define QOL_FIX_CUTSCENE_LOOP (0 || QOL_FIXES)
/// Fixes (or rather changes) an oversight if Mario is in a room
/// Credits: (AloXado320)
#define QOL_FIX_MARIO_IS_IN_ROOM (0 || QOL_FIXES)
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
/// Fixes huge score course list in file select
/// Credits: (Easy Fix)
#define QOL_FIX_FILE_SELECT_SCORE_COURSE_LIST (0 || QOL_FIXES)
/// Fixes surface wind detection (avoid grabbed star wind softlock)
/// Credits: (AloXado320)
#define QOL_FIX_SURFACE_WIND_DETECTION (0 || QOL_FIXES)
/// Fixes King Bob-omb music still playing while you go away after throwing him off
/// Credits: (AloXado320)
#define QOL_FIX_KING_BOBOMB_MUSIC_THROWN_OFF (0 || QOL_FIXES)
/// Fixes instant warp offset not working when warping across different areas
/// Credits: (Reonu)
#define QOL_FIX_INSTANT_WARP_OFFSET (0 || QOL_FIXES)
/// Fixes handle menu scrolling weird index positions
/// Credits: (coltongit)
#define QOL_FIX_MENU_SCROLLING (0 || QOL_FIXES)
/// Fixes missing surface wind in obj_check_floor_death
/// Credits: (Easy Fix)
#define QOL_FIX_OBJ_FLOOR_WIND_DEATH (0 || QOL_FIXES)
/// Fixes hardcoded snow tree leaf particles
/// Credits: (Easy Fix)
#define QOL_FIX_HARDCODED_TREE_PARTICLES (0 || QOL_FIXES)
/// Fixes red coin star marker floor position if more than 2000 units
/// Credits: (AloXado320)
#define QOL_FIX_RED_COIN_STAR_MARKER_POSITION (0 || QOL_FIXES)
/// Fixes monty mole hide in hole check
/// Credits: (Easy Fix)
#define QOL_FIX_HIDE_IN_HOLE_NULL_CHECK (0 || QOL_FIXES)
/// Fixes cutscene door Mario action check
/// Credits: (Easy Fix)
#define QOL_FIX_CUTSCENE_DOOR_CHECK (0 || QOL_FIXES)
/// Credits: (Easy Fix)
/// Fixes Z rotation when spawning an object with rotation
#define QOL_FIX_SPAWN_OBJECT_ANGLE_ROLL (0 || QOL_FIXES)
/// Fixes math util bogus return values
/// Credits: (Easy Fix)
#define QOL_FIX_MATH_UTIL_RETURN_VALUES (0 || QOL_FIXES)
/// Fixes boo hit velocity so they actually oscillate up then down
/// Credits: (nim)
#define QOL_FIX_BOO_MOVE_HIT_VELOCITY (0 || QOL_FIXES)
/// Fixes Bowser being invisible in BITFS after grabbing him
/// Credits: (AloXado320)
#define QOL_FIX_BOWSER_TRANSPARENT_HELD (0 || QOL_FIXES)
/// Fixes input off check order in common_landing_cancels
/// Credits: (Easy Fix)
#define QOL_FIX_LANDING_CANCEL_OFF_FLOOR (0 || QOL_FIXES)
/// Fixes vanilla camera vertical height so it follows Mario faster
/// Credits: (Reonu)
#define QOL_FIX_CAMERA_VERTICAL_MOVEMENT (0 || QOL_FIXES)
/// Fixes non slippery surfaces, so Mario can jump kick them, instead of being forced to dive
/// Credits: (Reonu)
#define QOL_FIX_JUMP_KICK_NOT_SLIPPERY (0 || QOL_FIXES)
/// Fixes one frame timer when bully backs up
/// Credits: (coltongit)
#define QOL_FIX_BULLY_BACK_UP_TIMER (0 || QOL_FIXES)
/// Fixes possible softlock with object cutscene focus
/// Credits: (MysterD)
#define QOL_FIX_OBJ_CUTSCENE_FOCUS_SOFTLOCK (0 || QOL_FIXES)
/// Fixes (or rather, adjusts) Mario's head look at bosses
/// Credits: (coltongit)
#define QOL_FIX_MARIO_LOOK_HEAD_BOSSES (0 || QOL_FIXES)
/// Fixes slide action so they have short hitbox
/// Credits: (AloXado320)
#define QOL_FIX_SHORT_HITBOX_SLIDE_ACTS (0 || QOL_FIXES)
/// Fixes pss slide value not being reset on exit
/// Credits: (AloXado320)
#define QOL_FIX_RESET_PSS_SLIDE_STARTED (0 || QOL_FIXES)
/// Fixes mist particles not spawning with an underwater shell
/// Credits: (PyroJay4)
#define QOL_FIX_DROPPED_UNDERWATER_SHELL (0 || QOL_FIXES)
/// Fixes platform on track checkered detection
/// Credits: (AloXado320)
#define QOL_FIX_PLATFORM_TRACK_CHECKERED (0 || QOL_FIXES)
/// Fixes cutscenes where Mario goes out of camera view on moving platforms
/// Credits: (AloXado320)
#define QOL_FIX_CAMERA_CUTSCENE_MOVING_PLATFORMS (0 || QOL_FIXES)
/// Fixes lower horizontal wind speed value
/// Credits: (Easy Fix)
#define QOL_FIX_HORIZONTAL_WIND_SPEED (0 || QOL_FIXES)
/// Fixes undefined anim return in the hit wall code, more info in the fix itself
/// Credits: (Arceveti)
#define QOL_FIX_HIT_WALL_ACTION (0 || QOL_FIXES)
/// Fixes Mario floor height in the peach ending cutscene
/// Credits: (Arceveti)
#define QOL_FIX_END_CUTSCENE_MARIO_FLOOR (0 || QOL_FIXES)
/// Fixes bonks when ground pounding next to a wall
/// Credits: (Arceveti)
#define QOL_FIX_GROUND_POUND_WALL (0 || QOL_FIXES)
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
/// Fixes missing not grabbable check in water
/// Credits: (Arceveti)
#define QOL_FIX_WATER_GRAB_NOT_GRABBABLE (0 || QOL_FIXES)
/// Fixes turning around on the ground
/// Credits: (Arceveti)
#define QOL_FIX_GROUND_TURN_RADIUS (0 || QOL_FIXES)
/// Fixes several stationary bugs by perform ground steps while standing still
/// Credits: (Arceveti)
#define QOL_FIX_STATIONARY_GROUND_STEPS (0 || QOL_FIXES)
/// Fixes Mario's collision with lava so it detects regardless of action
/// Credits: (Arceveti)
#define QOL_FIX_LAVA_INTERACTION (0 || QOL_FIXES)
/// Fixes palm height hardcoded course check and height when climbing up/down
/// Credits: (Arceveti)
#define QOL_FIX_PALM_TREE_LEAF_HEIGHT (0 || QOL_FIXES)
/// Fixes crash if there's no referenced ceiling
/// Credits: (Arceveti)
#define QOL_FIX_CEILING_NULL_CRASH (0 || QOL_FIXES)
/// Fixes shell speed water level origin offset
/// Credits: (Arceveti)
#define QOL_FIX_SHELL_SPEED_NEGATIVE_OFFSET (0 || QOL_FIXES)
/// Fixes bonks when walking into a wall
/// Credits: (Arceveti)
#define QOL_FIX_LESS_GROUND_BONKS (0 || QOL_FIXES)
/// Fixes possible weird behavior when spiny didn't have a proper parent object
/// Credits: (Arceveti)
#define QOL_FIX_SPINY_CHECK_ACTIVE_PARENT (0 || QOL_FIXES)
/// Fixes side flip ground pound visual bug
/// Credits: (Arceveti)
#define QOL_FIX_SIDE_FLIP_VISUAL_LOOK (0 || QOL_FIXES)
/// Fixes Mario disappearance when squished with no health (originally intentional but causes some bugs)
/// Credits: (Arceveti)
#define QOL_FIX_NO_DISAPPEARANCE_SQUISH (0 || QOL_FIXES)
/// Fixes Mr L eyeball billboard position
/// Credits: (Arceveti)
#define QOL_FIX_MR_I_EYEBALL_POSITION (0 || QOL_FIXES)
/// Fixes Mr L iris parent object when it deactivates
/// Credits: (Arceveti)
#define QOL_FIX_MR_I_DELETED_PARENT (0 || QOL_FIXES)
// --| Unused Code Fixes (for convenience)
/// Fixes code error in func_eu_802e27e4_unused
/// Credits: (Easy Fix)
#define QOL_FIX_UNUSED_LOOP_AUDIO_EU_SH (0 || QOL_FIXES)
/// Fixes (or rather removes) 0 yaw code in Beta Chest object
/// Credits: (Easy Fix)
#define QOL_FIX_UNUSED_BETA_CHEST_YAW (0 || QOL_FIXES)
/// Fixes collision flags checks for free bowling ball behavior
/// Credits: (Easy Fix)
#define QOL_FIX_UNUSED_FREE_BOWLING_BALL_COL_FLAGS (0 || QOL_FIXES)
/// Fixes play_mode_unused inclusion so it's "used" as a default "invalid" play mode switch
/// Credits: (Arceveti)
#define QOL_FIX_UNUSED_PLAY_MODE (0 || QOL_FIXES)
// --| Assets Fixes
/// Fixes duplicated red/white display list in Goddard and properly uses the next ones
/// Credits: (Easy Fix)
#define QOL_FIX_ASSET_DUP_STAR_GD (0 || (QOL_FIXES && GODDARD_MFACE))
/// Fixes Burn Smoke texture so it properly displays it
/// Credits: (Easy Fix)
#define QOL_FIX_ASSET_BURN_SMOKE (0 || QOL_FIXES)
/// Fixes Koopa's pink shorts caused by a miscalled light color value
/// Credits: (Easy Fix)
#define QOL_FIX_ASSET_KOOPA_SHORTS (0 || QOL_FIXES)
/// Fixes Yoshi "it" typo dialog (English)
/// Credits: (Easy Fix)
#define QOL_FIX_ASSET_YOSHI_DIALOG (0 || QOL_FIXES)
/// Fixes impossible coins (also fixes impossible Goomba since it's related)
/// Credits: (AloXado320)
#define QOL_FIX_ASSET_IMPOSSIBLE_COINS (0 || QOL_FIXES)
/// Fixes 1up locations in CCM slide
/// Credits: (Arceveti)
#define QOL_FIX_ASSET_CCM_SLIDE_1UPS (0 || QOL_FIXES)

#endif // QOL_DEFINES_H
