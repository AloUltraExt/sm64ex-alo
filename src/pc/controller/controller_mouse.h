#ifndef CONTROLLER_MOUSE_H
#define CONTROLLER_MOUSE_H

#include "controller_api.h"
#include "pc/gfx/gfx_pc.h"

extern int gMouseXPos;
extern int gMouseYPos;
extern int gOldMouseXPos;
extern int gOldMouseYPos;
extern int gMouseHasFreeControl;
extern int gMouseHasCenterControl;

#define VK_BASE_MOUSE 0x2000

extern struct ControllerAPI controller_mouse;

#endif
