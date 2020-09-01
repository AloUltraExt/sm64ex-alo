#ifdef CAPI_WII_U

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include <ultra64.h>

#include <vpad/input.h>
#include <padscore/wpad.h>
#include <padscore/kpad.h>

#include "controller_api.h"
#include "../configfile.h"

#ifdef BETTERCAMERA
int mouse_x = 0;
int mouse_y = 0;

extern u8 newcam_mouse;
#endif

struct WiiUKeymap {
    uint32_t n64Button;
    uint32_t vpadButton;
    uint32_t classicButton;
    uint32_t proButton;
};

// Button shortcuts
#define VB(btn) VPAD_BUTTON_##btn
#define CB(btn) WPAD_CLASSIC_BUTTON_##btn
#define PB(btn) WPAD_PRO_BUTTON_##btn
#define PT(btn) WPAD_PRO_TRIGGER_##btn

// Stick emulation
#define SE(dir) VPAD_STICK_R_EMULATION_##dir, WPAD_CLASSIC_STICK_R_EMULATION_##dir, WPAD_PRO_STICK_R_EMULATION_##dir

struct WiiUKeymap map[] = {
    { B_BUTTON, VB(B) | VB(Y), CB(B) | CB(Y), PB(B) | PB(Y) },
    { A_BUTTON, VB(A) | VB(X), CB(A) | CB(X), PB(A) | PB(X) },
    { START_BUTTON, VB(PLUS), CB(PLUS), PB(PLUS) },
    { Z_TRIG, VB(L) | VB(ZL), CB(L) | CB(ZL), PT(L) | PT(ZL) },
    { L_TRIG, VB(MINUS), CB(MINUS), PB(MINUS) },
    { R_TRIG, VB(R) | VB(ZR), CB(R) | CB(ZR), PT(R) | PT(ZR) },
    { U_CBUTTONS, SE(UP) },
    { D_CBUTTONS, SE(DOWN) },
    { L_CBUTTONS, SE(LEFT) },
    { R_CBUTTONS, SE(RIGHT) }
};

size_t num_buttons = sizeof(map) / sizeof(map[0]);
KPADStatus last_kpad = {0};
int kpad_timeout = 10;

static void controller_wiiu_init(void) {
    VPADInit();
    KPADInit();
    WPADEnableURCC(1);
    WPADEnableWiiRemote(1);

    if (configN64FaceButtons) {
        map[0] = (struct WiiUKeymap) { B_BUTTON, VB(Y) | VB(X), CB(Y) | CB(X), PB(Y) | PB(X) };
        map[1] = (struct WiiUKeymap) { A_BUTTON, VB(B) | VB(A), CB(B) | CB(A), PB(B) | PB(A) };
    }
}

static void read_vpad(OSContPad *pad) {
    VPADStatus status;
    VPADReadError err;
    uint32_t v;

    VPADRead(VPAD_CHAN_0, &status, 1, &err);

    if (err != 0) {
        return;
    }

    v = status.hold;

    for (size_t i = 0; i < num_buttons; i++) {
        if (v & map[i].vpadButton) {
            pad->button |= map[i].n64Button;
        }
    }

    if (v & VPAD_BUTTON_LEFT) pad->stick_x = -80;
    if (v & VPAD_BUTTON_RIGHT) pad->stick_x = 80;
    if (v & VPAD_BUTTON_DOWN) pad->stick_y = -80;
    if (v & VPAD_BUTTON_UP) pad->stick_y = 80;

    if (status.leftStick.x != 0) {
        pad->stick_x = (s8) round(status.leftStick.x * 80);
    }
    if (status.leftStick.y != 0) {
        pad->stick_y = (s8) round(status.leftStick.y * 80);
    }
}

static void read_wpad(OSContPad* pad) {
    // Disconnect any extra controllers
    WPADExtensionType ext;
    for (int i = 1; i < 4; i++) {
        int res = WPADProbe(i, &ext);
        if (res == 0) {
            WPADDisconnect(i);
        }
    }

    int res = WPADProbe(WPAD_CHAN_0, &ext);
    if (res != 0) {
        return;
    }

    KPADStatus status;
    int err;
    int read = KPADReadEx(WPAD_CHAN_0, &status, 1, &err);
    if (read == 0) {
        kpad_timeout--;

        if (kpad_timeout == 0) {
            WPADDisconnect(WPAD_CHAN_0);
            memset(&last_kpad, 0, sizeof(KPADStatus));
            return;
        }
        status = last_kpad;
    } else {
        kpad_timeout = 10;
        last_kpad = status;
    }

    uint32_t wm = status.hold;
    KPADVec2D stick;

    bool gamepadStickNotSet = pad->stick_x == 0 && pad->stick_y == 0;

    if (status.extensionType == WPAD_EXT_NUNCHUK || status.extensionType == WPAD_EXT_MPLUS_NUNCHUK) {
        uint32_t ext = status.nunchuck.hold;
        stick = status.nunchuck.stick;

        if (wm & WPAD_BUTTON_A) pad->button |= A_BUTTON;
        if (wm & WPAD_BUTTON_B) pad->button |= B_BUTTON;
        if (wm & WPAD_BUTTON_PLUS) pad->button |= START_BUTTON;
        if (wm & WPAD_BUTTON_UP) pad->button |= U_CBUTTONS;
        if (wm & WPAD_BUTTON_DOWN) pad->button |= D_CBUTTONS;
        if (wm & WPAD_BUTTON_LEFT) pad->button |= L_CBUTTONS;
        if (wm & WPAD_BUTTON_RIGHT) pad->button |= R_CBUTTONS;
        if (ext & WPAD_NUNCHUK_BUTTON_C) pad->button |= R_TRIG;
        if (ext & WPAD_NUNCHUK_BUTTON_Z) pad->button |= Z_TRIG;
    } else if (status.extensionType == WPAD_EXT_CLASSIC || status.extensionType == WPAD_EXT_MPLUS_CLASSIC) {
        uint32_t ext = status.classic.hold;
        stick = status.classic.leftStick;
        for (size_t i = 0; i < num_buttons; i++) {
            if (ext & map[i].classicButton) {
                pad->button |= map[i].n64Button;
            }
        }
        if (ext & WPAD_CLASSIC_BUTTON_LEFT) pad->stick_x = -80;
        if (ext & WPAD_CLASSIC_BUTTON_RIGHT) pad->stick_x = 80;
        if (ext & WPAD_CLASSIC_BUTTON_DOWN) pad->stick_y = -80;
        if (ext & WPAD_CLASSIC_BUTTON_UP) pad->stick_y = 80;
    } else if (status.extensionType == WPAD_EXT_PRO_CONTROLLER) {
        uint32_t ext = status.pro.hold;
        stick = status.pro.leftStick;
        for (size_t i = 0; i < num_buttons; i++) {
            if (ext & map[i].proButton) {
                pad->button |= map[i].n64Button;
            }
        }
        if (ext & WPAD_PRO_BUTTON_LEFT) pad->stick_x = -80;
        if (ext & WPAD_PRO_BUTTON_RIGHT) pad->stick_x = 80;
        if (ext & WPAD_PRO_BUTTON_DOWN) pad->stick_y = -80;
        if (ext & WPAD_PRO_BUTTON_UP) pad->stick_y = 80;
    }

    // If we didn't already get stick input from the gamepad
    if (gamepadStickNotSet) {
        if (stick.x != 0) {
            pad->stick_x = (s8) round(stick.x * 80);
        }
        if (stick.y != 0) {
            pad->stick_y = (s8) round(stick.y * 80);
        }
    }
}

static void controller_wiiu_read(OSContPad* pad) {
    pad->stick_x = 0;
    pad->stick_y = 0;

    read_vpad(pad);
    read_wpad(pad);
}

static u32 controller_wiiu_rawkey(void) {
    return VK_INVALID;
}

static void controller_wiiu_shutdown(void) {
}

struct ControllerAPI controller_wiiu = {
    VK_INVALID,
    controller_wiiu_init,
    controller_wiiu_read,
    controller_wiiu_rawkey,
    NULL, // no rumble_play
    NULL, // no rumble_stop
    NULL, // no rebinding
    controller_wiiu_shutdown
};

#endif
