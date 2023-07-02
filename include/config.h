#ifndef CONFIG_H

#define CONFIG_H

/**
 * @file config.h
 * A catch-all file for configuring various bugfixes and other settings
 * (maybe eventually) in SM64
 */

// QOL Defines
#include "qol_defines.h"

// Bug Fixes
// --| Post-JP Version Nintendo Bug Fixes
/// Fixes bug where obtaining over 999 coins sets the number of lives to 999 (or -25)
#define BUGFIX_MAX_LIVES (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where the Boss music won't fade out after defeating King Bob-omb
#define BUGFIX_KING_BOB_OMB_FADE_MUSIC (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where entering a warp on the same area overrides any non background music on a course
#define BUGFIX_SAME_AREA_WARP_MUSIC ((0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES) && VANILLA_CHECKS)
/// Fixes bug where Piranha Plants do not reset their action state when the
/// player exits their activation radius.
#define BUGFIX_PIRANHA_PLANT_STATE_RESET (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where sleeping Piranha Plants damage players that bump into them
#define BUGFIX_PIRANHA_PLANT_SLEEP_DAMAGE (0 || VERSION_US || VERSION_SH || QOL_FIXES)
/// Fixes bug where it shows a star when you grab a key in bowser battle stages
#define BUGFIX_STAR_BOWSER_KEY (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug that enables Mario in time stop even if is not ready to speak
#define BUGFIX_DIALOG_TIME_STOP (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug that causes Mario to still collide with Bowser in BitS after his defeat
#define BUGFIX_BOWSER_COLLIDE_BITS_DEAD (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where Bowser wouldn't reset his speed when fallen off (and adds missing checks)
#define BUGFIX_BOWSER_FALLEN_OFF_STAGE (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
/// Fixes bug where Bowser would look weird while fading out
#define BUGFIX_BOWSER_FADING_OUT (0 || VERSION_US || VERSION_EU || VERSION_SH || QOL_FIXES)
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

// Other Settings
#include "config/config_camera.h"
#include "config/config_collision.h"
#include "config/config_graphics.h"
#include "config/config_keycombo.h"
#include "config/config_movement.h"
#include "config/config_n64.h"
#include "config/config_objects.h"
#include "config/config_sounds.h"

// Screen Size Defines
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define BORDER_HEIGHT 0

// Stack Size Defines
#define IDLE_STACKSIZE 0x800
#define STACKSIZE 0x2000

#endif // CONFIG_H
