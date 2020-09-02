#ifdef CAPI_3DS

//hack for redefinition of types in libctru
#define u64 __u64
#define s64 __s64
#define u32 __u32
#define vu32 __vu32
#define vs32 __vs32
#define s32 __s32
#define u16 __u16
#define s16 __s16
#define u8 __u8
#define s8 __s8
#include <3ds/types.h>
#undef u64
#undef s64
#undef u32
#undef vu32
#undef vs32
#undef s32
#undef u16
#undef s16
#undef u8
#undef s8

#include <ultra64.h>

#include <3ds.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "controller_api.h"

#define DEADZONE 4960

#ifdef BETTERCAMERA
int mouse_x = 0;
int mouse_y = 0;

extern u8 newcam_mouse;
#endif

static bool init_ok;

static void controller_3ds_init(void)
{
}

static void controller_3ds_read(OSContPad *pad)
{
    hidScanInput();
    u32 kDown = keysHeld();
    if (kDown & KEY_START)
        pad->button |= START_BUTTON;
    if (kDown & KEY_R)
        pad->button |= Z_TRIG;
    if (kDown & KEY_L)
        pad->button |= R_TRIG;
    if (kDown & KEY_A)
        pad->button |= A_BUTTON;
    if (kDown & KEY_X)
        pad->button |= L_TRIG;
    if (kDown & KEY_B)
        pad->button |= B_BUTTON;
    if (kDown & (KEY_DLEFT | KEY_CSTICK_LEFT))
        pad->button |= L_CBUTTONS;
    if (kDown & (KEY_DRIGHT | KEY_CSTICK_RIGHT))
        pad->button |= R_CBUTTONS;
    if (kDown & (KEY_DUP | KEY_CSTICK_UP))
        pad->button |= U_CBUTTONS;
    if (kDown & (KEY_DDOWN | KEY_CSTICK_DOWN))
        pad->button |= D_CBUTTONS;

    circlePosition pos;
    hidCircleRead(&pos);
    pad->stick_x = pos.dx / 2;
    pad->stick_y = pos.dy / 2;
}

static void controller_3ds_rawkey(void)
{
    return VK_INVALID;
}

static void controller_3ds_shutdown(void)
{
}

struct ControllerAPI controller_3ds = {
    VK_INVALID,
    controller_3ds_init,
    controller_3ds_read,
    controller_3ds_rawkey,
    NULL, // no rumble_play
    NULL, // no rumble_stop
    NULL, // no rebinding
    controller_3ds_shutdown
};

#endif
