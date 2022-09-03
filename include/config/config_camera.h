#pragma once

/*******************
 * CAMERA SETTINGS *
 *******************/

/// Makes the camera approach Mario's height much more quickly.
#define FAST_VERTICAL_CAMERA_MOVEMENT (0 || QOL_FIXES)

/// Fixes up checks when vanilla camera rotates to a wall 
#define CORRECT_ROTATE_CAMERA_AROUND_WALLS (0 || QOL_FIXES)

/// Fixes up checks when vanilla camera collides to a wall 
#define CORRECT_COLLIDE_WITH_WALLS (0 || QOL_FIXES)

/// Fixes camera boss fight y position to be more dynamic
#define FIX_CAMERA_BOSS_FIGHT_POS (0 || QOL_FIXES || !VANILLA_CHECKS)

/// Changes C-Up vanilla camera similar to the DS version
#define DS_CAM_MOVEMENT_C_UP (0 || QOL_FEATURES)

/// The number of steps between Mario and the camera to check for walls obstructing Mario. Vanilla is 8.
#define CAMERA_NUM_OBSTRUCTION_CHECKS   8

/*********************
 * CUTSCENE SETTINGS *
 *********************/

/// Fixes possible softlock with object cutscene focus
#define FIX_CUTSCENE_FOCUS_DEACTIVE (0 || QOL_FIXES)

/// Properly adds unused SSL Pyramid cutscene after standing on the 4 pillars
#define SSL_PYRAMID_CUTSCENE (0 || QOL_FEATURES)

/// If Mario is high enough above the ground or above an unsafe floor, he will perform the star dance in midair instead of falling.
#define MIDAIR_STAR_DANCE (0 || QOL_FEATURES)
