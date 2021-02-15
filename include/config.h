#ifndef CONFIG_H

#define CONFIG_H

/**
 * @file config.h
 * A catch-all file for configuring various bugfixes and other settings
 * (maybe eventually) in SM64
 */

// Qol Defines
#include "qol_defines.h"

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
