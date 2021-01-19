#ifndef CONFIG_H

#define CONFIG_H

/**
 * @file config.h
 * A catch-all file for configuring various bugfixes and other settings
 * (maybe eventually) in SM64
 */

// Bug Fixes
// --| Post-JP Version Nintendo Bug Fixes
/// Fixes bug where obtaining over 999 coins sets the number of lives to 999 (or -25)
#define BUGFIX_MAX_LIVES (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where the Boss music won't fade out after defeating King Bob-omb
#define BUGFIX_KING_BOB_OMB_FADE_MUSIC (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug in Bob-Omb Battlefield where entering a warp stops the Koopa race music
#define BUGFIX_KOOPA_RACE_MUSIC (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where Piranha Plants do not reset their action state when the
/// player exits their activation radius.
#define BUGFIX_PIRANHA_PLANT_STATE_RESET (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where sleeping Piranha Plants damage players that bump into them
#define BUGFIX_PIRANHA_PLANT_SLEEP_DAMAGE (0 || VERSION_US || VERSION_SH || QOL_FIXES)
/// Fixes bug where it shows a star when you grab a key in bowser battle stages
#define BUGFIX_STAR_BOWSER_KEY (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug in KTQ win dialog which makes it sounds like a penguin instead of a Koopa
#define BUGFIX_DIALOG_SOUND_KTQ_WIN (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug that causes Wiggle to read a garbage health value when it gets loaded
#define BUGFIX_WIGGLER_HEALTH (0 || VERSION_EU || AVOID_UB || QOL_FIXES)
// --| Shindou Version Nintendo Bug Fixes
/// Fixes bug where bully could still be interacted while he dies 
#define BUGFIX_BULLY_NO_INTERACT_DEATH (0 || VERSION_SH || QOL_FIXES)
/// Fixes bug where standing a controllable platform in HMC be invisible while it blinks
#define BUGFIX_HMC_VISIBLE_CONTROL_PLATFORM (0 || VERSION_SH || QOL_FIXES)
/// Fixes bug where the angle speed isn't preserved while in a pole
#define BUGFIX_PRESERVE_VEL_POLE (0 || VERSION_SH || QOL_FIXES)

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
/// Corrects UV value of the US IA font, slightly noticeable in Non-N64 targets
#define QOL_FIX_US_FONT_TEXTURE_UV (0 || QOL_FIXES)
/// Corrects hud texture fillter, only noticeable on N64 old plugins
#define QOL_FIX_HUD_TEXTURE_FILTER (0 || QOL_FIXES)
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
/// Fixes fall damage height when grounpounding
#define QOL_FIX_FALL_DAMAGE_HEIGHT (0 || QOL_FIXES)

// Debug Defines
// Skip Intro Cutscene (N64)
#define SKIP_PEACH_CUTSCENE 0
// Test End Cutscene without beating Bowser 3
#define DEBUG_TEST_ENDCUTSCENE 0
// Test Credits without beating Bowser 3 (Recommended to use with TEST_ENDCUTSCENE)
#define DEBUG_TEST_CREDITS 0

// Screen Size Defines
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// What's the point of having a border if we're not an N64?
#define BORDER_HEIGHT 0 // Never use a border as not-N64

#endif // CONFIG_H
