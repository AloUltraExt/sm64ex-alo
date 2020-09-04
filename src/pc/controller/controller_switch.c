#ifdef CAPI_SWITCH

#include <switch.h>
#include <ultra64.h>

#include <sm64.h>
#include "../../game/level_update.h"

#include "controller_api.h"

static HidControllerID joyConId;

static bool isSixAxis = false;
static u32 sixAxisHandles[4];
static struct SixAxisSensorValues sixAxis;

static void startSixAxis() {
    isSixAxis = true;
    //Initiating the SixAxis, needs to be done for all options; Obviously no GC Controller.
    hidGetSixAxisSensorHandles(&sixAxisHandles[0], 2, CONTROLLER_PLAYER_1, TYPE_JOYCON_PAIR);
    hidGetSixAxisSensorHandles(&sixAxisHandles[2], 1, CONTROLLER_PLAYER_1, TYPE_PROCONTROLLER);
    hidGetSixAxisSensorHandles(&sixAxisHandles[3], 1, CONTROLLER_HANDHELD, TYPE_HANDHELD);
    for(int i = 0; i < 4; i++)
        hidStartSixAxisSensor(sixAxisHandles[i]);
    hidScanInput();
    hidSixAxisSensorValuesRead(&sixAxis, joyConId, 1);
}

static void stopSixAxis() {
    isSixAxis = false;
    for(int i = 0; i < 4; i++)
        hidStopSixAxisSensor(sixAxisHandles[i]);
}

static s8 gyroToSByte(float f) {
    return (s8)(f * 0xFF);
}

static void joycon_init(void) {
    joyConId = CONTROLLER_P1_AUTO;
}

static void joycon_read(OSContPad *pad) {
    hidScanInput();

    switch(gMarioState->action) {
        case ACT_IN_CANNON:
        case ACT_FIRST_PERSON:
            if(!isSixAxis) startSixAxis();
            break;
        default:
            if(isSixAxis) stopSixAxis();    
    }

    u64 pressed = hidKeysDown(joyConId);
    u64 held = hidKeysHeld(joyConId);
    
    JoystickPosition sticks[2];
    hidJoystickRead(&sticks[0], joyConId, JOYSTICK_LEFT);
    hidJoystickRead(&sticks[1], joyConId, JOYSTICK_RIGHT);

    if(pressed & KEY_PLUS || held & KEY_PLUS)       pad->button |= START_BUTTON;
    if(pressed & KEY_MINUS || held & KEY_MINUS)     pad->button |= START_BUTTON;

    if(pressed & KEY_B || held & KEY_B)             pad->button |= A_BUTTON;
    if(pressed & KEY_A || held & KEY_A)             pad->button |= A_BUTTON;
    if(pressed & KEY_Y || held & KEY_Y)             pad->button |= B_BUTTON;
    if(pressed & KEY_X || held & KEY_X)             pad->button |= B_BUTTON;

    if(pressed & KEY_L  || held & KEY_L)            pad->button |= L_TRIG;
    if(pressed & KEY_ZL || held & KEY_ZL)           pad->button |= Z_TRIG;
    if(pressed & KEY_R  || held & KEY_R)            pad->button |= R_TRIG;
    if(pressed & KEY_ZR || held & KEY_ZR)           pad->button |= R_TRIG;

    if(pressed & KEY_DUP    || held & KEY_DUP)      pad->button |= U_JPAD;
    if(pressed & KEY_DLEFT  || held & KEY_DLEFT)    pad->button |= L_JPAD;
    if(pressed & KEY_DDOWN  || held & KEY_DDOWN)    pad->button |= D_JPAD;
    if(pressed & KEY_DRIGHT || held & KEY_DRIGHT)   pad->button |= R_JPAD;

    if(sticks[1].dx > 0x4000)   pad->button |= R_CBUTTONS;
    if(sticks[1].dx < -0x4000)  pad->button |= L_CBUTTONS;
    if(sticks[1].dy > 0x4000)   pad->button |= U_CBUTTONS;
    if(sticks[1].dy < -0x4000)  pad->button |= D_CBUTTONS;


    s8 anaInput[2];
    anaInput[0] = sticks[0].dx / 0x100; //Stick X
    anaInput[1] = sticks[0].dy / 0x100; //Stick Y

    if(isSixAxis) {
        hidSixAxisSensorValuesRead(&sixAxis, joyConId, 1);
        s8 gyroX = gyroToSByte(sixAxis.gyroscope.x); //Gyroscope X-Axis (Controller Y)
        s8 gyroY = gyroToSByte(sixAxis.gyroscope.y); //Gyroscope Y-Axis (Controller X)
        if(anaInput[0] == 0 && anaInput[1] == 0) {
            anaInput[0] = -gyroY;
            anaInput[1] = -gyroX;
        }
    }

    pad->stick_x = anaInput[0];
    pad->stick_y = anaInput[1];
}

static void joycon_rawkey(void)  {
    return VK_INVALID;
}

static void joycon_shutdown(void) {
}

struct ControllerAPI controller_switch = {
    VK_INVALID,
    joycon_init,
    joycon_read,
    joycon_rawkey,
    NULL, // no rumble_play
    NULL, // no rumble_stop
    NULL, // no rebinding
    joycon_shutdown
};

#endif
