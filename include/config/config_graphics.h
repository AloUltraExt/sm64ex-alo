#pragma once

/*********************
 * GRAPHICS SETTINGS *
 *********************/
/// Fixes Koopa's pink shorts caused by a miscalled light color value.
#define FIX_KOOPA_SHORTS (0 || QOL_FIXES)

/// Fixes Burn smoke texture graphic and adds fading.
#define FIX_BURN_SMOKE (0 || QOL_FIXES)

/// Restores ukiki blinking eyes.
#define UKIKI_BLINK_EYES (0 || QOL_FEATURES)

/// Restores King Bob-omb blinking eyes by creating display lists for it.
#define KING_BOBOMB_BLINK_EYES (0 || QOL_FEATURES)

/// Restores unused sad eyes for the penguin mother when its baby is lost.
#define TUXIES_MOTHER_SAD_EYES (0 || QOL_FEATURES)

/// Adds japanese text at the bottom of the logo like in modern games.
#define INTRO_JAPANESE_GAME_TEXT (0 || ((VERSION_JP || VERSION_SH) && QOL_FEATURES))

/// Changes credit text font to the one used by generic strings.
#define CREDITS_TEXT_STRING_FONT (0 || QOL_FEATURES)

// Makes certain objects (mainly trees) transparent when the camera gets close.
#define OBJ_OPACITY_BY_CAM_DIST (0 || QOL_FEATURES)

/// Makes trees use actual shadows, recommended to use with optimized shadows.
#define PROPER_TREE_SHADOWS (0 || QOL_FEATURES)

/// Makes Mario show a proper graphic of a special collectable (Transparent stars are now properly shown).
#define SHOW_INTERACT_OBJ_COLLECTABLE (0 || QOL_FEATURES)

/// Correctly changes star model to be transparent when (Klepto and Unagi) stars are collected.
#define OBJ_HOLD_TRANSPARENT_STAR (0 || QOL_FEATURES)

/// Makes snow particles slowly disappear when the camera is in a ceiling.
#define NO_ENV_SNOW_CEILING (0 || QOL_FEATURES)
