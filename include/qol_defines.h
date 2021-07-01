#ifndef QOL_DEFINES_H
#define QOL_DEFINES_H

// Quality of life defines
// Mostly a compilation of code provided by various people

// --| Quality of life features
/// Adds an extra Z button trig for some menu files (Originally defined in EU)
#define QOL_FEATURE_Z_BUTTON_EXTRA_OPTION (0 || VERSION_EU || QOL_FEATURES)
/// Changes how Mario grabs a star/key by calling his interactObj define
/// This also makes it so a blue star is shown when grabbing it
#define QOL_FEATURE_PROPER_SHOW_COLLECTABLE (0 || QOL_FEATURES)
/// Correctly changes blue star model when Klepto is holding it (First star in SSL)
#define QOL_FEATURE_KLEPTO_HOLDING_BLUE_STAR (0 || QOL_FEATURES)
/// Properly adds unused SSL Pyramid cutscene after standing on the 4 pillars
#define QOL_FEATURE_SSL_PYRAMID_CUTSCENE (0 || QOL_FEATURES)
/// Adds unused sad eyes for the penguin mother when he lost it's baby
#define QOL_FEATURE_TUXIES_MOTHER_SAD_EYES (0 || QOL_FEATURES)
/// Adds more actions to the special triple jump such as wallkick and grabbing
#define QOL_FEATURE_MORE_SPECIAL_TRIPLE_JUMP_ACTIONS (0 || QOL_FEATURES)
/// Adds unused cracked ice object in SL
/// More information in 'unused_poundable_platform.inc.c' comment
#define QOL_FEATURE_SSL_CRACKED_ICE (0 || QOL_FEATURES)
/// Adds blinking to King Bob-omb, reusing it's unused blinking texture
#define QOL_FEATURE_KING_BOBOMB_BLINK (0 || QOL_FEATURES)
/// Changes hanging actions so that you don't need to hold A anymore
#define QOL_FEATURE_HANGING_ACTION (0 || QOL_FEATURES)
/// Changes blue coin switch to respawn instead of dissapearing
#define QOL_FEATURE_RESPAWN_BLUE_COIN_SWITCH (0 || QOL_FEATURES)
/// Changes WF breakable wall interaction by no taking damage and returning safely
#define QOL_FEATURE_BETTER_WF_BREAKEABLE_WALL (0 || QOL_FEATURES)
/// Changes C-Up vanilla camera similar to the DS version
#define QOL_FEATURE_C_UP_DS (0 || QOL_FEATURES)
/// Adds "new" star grab action that uses floating star dance if on a lethal floor
#define QOL_FEATURE_STAR_GRAB_NO_FALL_DEATH (0 || QOL_FEATURES)

// --| Quality of life fixes
/// Fixes bug where the castle trap sound in the entrance of Bowser 1 doesn't play
#define QOL_FIX_CASTLE_TRAP_SOUND (0 || QOL_FIXES)
/// Fixes undefined anim return in the hit wall code, more info in the fix itself
#define QOL_FIX_HIT_WALL_ANIMATION (0 || QOL_FIXES)
/// Fixes manta's water rings to match where it looks
#define QOL_FIX_WATER_RING (0 || QOL_FIXES)
/// Fixes object counter so it correctly gets proper value when updating objects
#define QOL_FIX_OBJ_COUNT_LIST (0 || QOL_FIXES)
/// Fixes duplicated red/white display list in goddard and properly uses the next ones
#define QOL_FIX_DUP_RED_YELLOW_GD_DLS (0 || QOL_FIXES)
/// Fixes Burn Smoke texture so it properly displays it
#define QOL_FIX_BURN_SMOKE_TEXTURE (0 || QOL_FIXES)
/// Fixes Koopa's pink shorts caused by a miscalled light value
#define QOL_FIX_KOOPA_SHORTS_COLORS (0 || QOL_FIXES)
/// Fixes missing sounds in key exit cutscene caused by missing "breaks" in code
#define QOL_FIX_MISSING_SOUNDS_KEY_EXIT (0 || QOL_FIXES)
/// Fixes fake pole grab on the bottom of it, allowing to be properly grabbed
#define QOL_FIX_POLE_BOTTOM_GRAB (0 || QOL_FIXES)
/// Fixes an oddly defined interaction sub type in penguin mother behavior 
#define QOL_FIX_TUXIE_HELD_STATE (0 || QOL_FIXES)
/// Fixes Bully minion knockback timer by reseting it, more info in the fix itself
#define QOL_FIX_BULLY_KNOCKBACK_TIMER (0 || QOL_FIXES)
/// Fixes Shadow water height level return code
#define QOL_FIX_SHADOW_WATER_LEVEL (0 || QOL_FIXES)
/// Fixes last missing return in hitbox/hurtbox overlap detection code
#define QOL_FIX_HITBOX_HURTBOX_OVERLAP_RETURN (0 || QOL_FIXES)
/// Fixes camera height in water while being Metal
#define QOL_FIX_CAMERA_WATER_HEIGHT (0 || QOL_FIXES)
/// Fixes camera height in BOB and adds missing breaks in code
#define QOL_FIX_CAMERA_BOSS_FIGHT_HEIGHT (0 || QOL_FIXES)
/// Fixes audio code preload sequence so it checks sequences instead of banks
#define QOL_FIX_AUDIO_LOAD_BANK_NOT_SEQUENCE (0 || QOL_FIXES)
/// Fixes halfcircle when starting to move
#define QOL_FIX_TURN_AROUND_CIRCLE (0 || QOL_FIXES)
/// Fixes drowing sound continously playing while Metal
#define QOL_FIX_DROWING_SOUND_METAL (0 || QOL_FIXES)
/// Fixes complete coins not giving lives every 50 coins after 150 coins
#define QOL_FIX_COMPLETE_COURSE_50_COINS (0 || QOL_FIXES)
/// Fixes impossible coins (also fixes impossible goomba since it's related)
#define QOL_FIX_IMPOSSIBLE_COINS (0 || QOL_FIXES)
/// Fixes cap cloning when Mario takes a fade warp
#define QOL_FIX_HAT_CLONE_FADE (0 || QOL_FIXES)
/// Fixes open door key cutscene on 90-270 degrees
#define QOL_FIX_DOOR_KEY_CUTSCENE (0 || QOL_FIXES)
/// Fixes cutscene loop code (see comment in the fix)
#define QOL_FIX_CUTSCENE_LOOP (0 || QOL_FIXES)
/// Fixes yoshi "it" typo dialog (english)
#define QOL_FIX_YOSHI_DIALOG_TYPO (0 || QOL_FIXES)
/// Fixes (or rather changes) an oversight if Mario is in a room
#define QOL_FIX_MARIO_IS_IN_ROOM (0 || QOL_FIXES)
/// Fixes incorrect yellow sparkle offset positions
#define QOL_FIX_YELLOW_SPARKLES_OFFSET (0 || QOL_FIXES)
/// Fixes weird overflow when object is in oob away from steep floor
#define QOL_FIX_OOB_OBJ_CRASH_OVERFLOW (0 || QOL_FIXES)
/// Fixes Seaweed missing first anim frame
#define QOL_FIX_MISSING_SEAWEED_ANIMFRAME (0 || QOL_FIXES)
/// Fixes BITS tilting pyramid y distance
#define QOL_FIX_TILTING_PYRAMID_Y_DISTANCE (0 || QOL_FIXES)
/// Fixes huge score course list in file select
#define QOL_FIX_FILE_SELECT_SCORE_COURSE_LIST (0 || QOL_FIXES)
/// Fixes surface wind detection (avoid grabbed star wind softlock)
#define QOL_FIX_SURFACE_WIND_DETECTION (0 || QOL_FIXES)
/// Fixes King Bob-omb music still playing while you go away after throwing him off
#define QOL_FIX_KING_BOBOMB_MUSIC_THROWN_OFF (0 || QOL_FIXES)
/// Fixes instant warp offset not working when warping across different areas
#define QOL_FIX_INSTANT_WARP_OFFSET (0 || QOL_FIXES)
/// Fixes handle menu scrolling weird index positions
#define QOL_FIX_MENU_SCROLLING (0 || QOL_FIXES)
/// Fixes missing surface wind in obj_check_floor_death
#define QOL_FIX_OBJ_FLOOR_WIND_DEATH (0 || QOL_FIXES)
/// Fixes hardcoded snow tree leaf particles
#define QOL_FIX_HARDCODED_TREE_PARTICLES (0 || QOL_FIXES)
/// Fixes red coin star marker floor position if more than 2000 units
#define QOL_FIX_RED_COIN_STAR_MARKER_POSITION (0 || QOL_FIXES)
/// Fixes monty mole hide in hole check
#define QOL_FIX_HIDE_IN_HOLE_NULL_CHECK (0 || QOL_FIXES)

#endif // QOL_DEFINES_H
