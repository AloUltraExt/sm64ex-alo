#ifndef CONTROLLER_MOUSE_H
#define CONTROLLER_MOUSE_H

#include "controller_api.h"
#include "pc/gfx/gfx_pc.h"
#include <stdbool.h>

extern bool mouse_init_ok;

extern u32 mouse_buttons;
extern s32 mouse_x;
extern s32 mouse_y;

extern u32 mouse_window_buttons;
extern s32 mouse_window_x;
extern s32 mouse_window_y;

extern bool mouse_relative_enabled;

extern int mouse_prev_window_x;
extern int mouse_prev_window_y;
extern int mouse_has_current_control;
extern int mouse_has_center_control;

void controller_mouse_set_visible(void);
int controller_mouse_set_position(void *cursorX, void *cursorY, f32 mPosX, f32 mPosY, int hasControlCondition, int isInteger);
void controller_mouse_read_window(void);
void controller_mouse_read_relative(void);

void controller_mouse_enter_relative(void);
void controller_mouse_leave_relative(void);


extern struct ControllerAPI controller_mouse;

#endif
