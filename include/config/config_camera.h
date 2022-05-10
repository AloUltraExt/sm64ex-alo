#pragma once

/*******************
 * CAMERA SETTINGS *
 *******************/

// Makes the camera approach Mario's height much more quickly.
#define FAST_VERTICAL_CAMERA_MOVEMENT (0 || QOL_FIXES)

// Fixes up checks when vanilla camera rotates to a wall 
#define CORRECT_ROTATE_CAMERA_AROUND_WALLS (0 || QOL_FIXES)

// Fixes up checks when vanilla camera collides to a wall 
#define CORRECT_COLLIDE_WITH_WALLS (0 || QOL_FIXES)

// Changes C-Up vanilla camera similar to the DS version
#define DS_CAM_MOVEMENT_C_UP (0 || QOL_FEATURES)

// The number of steps between Mario and the camera to check for walls obstructing Mario. Vanilla is 8.
#define CAMERA_NUM_OBSTRUCTION_CHECKS   8