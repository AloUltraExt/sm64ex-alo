#ifdef CAPI_SWITCH

#include <switch.h>
#include <ultra64.h>

#include <sm64.h>
#include "../../game/level_update.h"

#include "controller_api.h"

// silent deprecated functions
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

static HidControllerID joyConId;

static bool isSixAxis = false;
static HidSixAxisSensorHandle sixAxisHandles[4];
static struct SixAxisSensorValues sixAxis;

PadState pad;
u32 target_device = -1;
HidVibrationValue VibrationValue;
HidVibrationValue VibrationValue_stop;
HidVibrationValue VibrationValues[2];
HidVibrationDeviceHandle VibrationDeviceHandles[2][2];

s32 last = 0;
s32 vlength = 0;

static void start_six_axis() {
    isSixAxis = true;
    //Initiating the SixAxis, needs to be done for all options; Obviously no GC Controller.
    hidGetSixAxisSensorHandles(&sixAxisHandles[0], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);
    hidGetSixAxisSensorHandles(&sixAxisHandles[2], 1, HidNpadIdType_No1, HidNpadStyleTag_NpadFullKey);
    hidGetSixAxisSensorHandles(&sixAxisHandles[3], 1, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    for(int i = 0; i < 4; i++)
        hidStartSixAxisSensor(sixAxisHandles[i]);
    hidScanInput();
    hidSixAxisSensorValuesRead(&sixAxis, joyConId, 1);
}

static void stop_six_axis() {
    isSixAxis = false;
    for(int i = 0; i < 4; i++)
        hidStopSixAxisSensor(sixAxisHandles[i]);
}

static s8 gyro_to_sbyte(float f) {
    return (s8)(f * 0xFF);
}

static void controller_switch_nx_init(void) {
    joyConId = CONTROLLER_P1_AUTO;
    
    padInitializeDefault(&pad);
    
    hidInitializeVibrationDevices(VibrationDeviceHandles[0], 2, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    hidInitializeVibrationDevices(VibrationDeviceHandles[1], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);
}

static void controller_switch_nx_read(OSContPad *pad) {
    hidScanInput();

    switch(gMarioState->action) {
        case ACT_IN_CANNON:
        case ACT_FIRST_PERSON:
            if(!isSixAxis) start_six_axis();
            break;
        default:
            if(isSixAxis) stop_six_axis();    
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
        s8 gyroX = gyro_to_sbyte(sixAxis.gyroscope.x); //Gyroscope X-Axis (Controller Y)
        s8 gyroY = gyro_to_sbyte(sixAxis.gyroscope.y); //Gyroscope Y-Axis (Controller X)
        if(anaInput[0] == 0 && anaInput[1] == 0) {
            anaInput[0] = -gyroY;
            anaInput[1] = -gyroX;
        }
    }

    pad->stick_x = anaInput[0];
    pad->stick_y = anaInput[1];
}

static u32 controller_switch_nx_rawkey(void)  {
    return VK_INVALID;
}

static void controller_switch_nx_rumble_play(f32 strength, f32 length) {
    memset(VibrationValues, 0, sizeof(VibrationValues));

    VibrationValue.freq_low  = 160.0f;
    VibrationValue.freq_high = 320.0f;
    VibrationValue.amp_low   = strength;
    VibrationValue.amp_high  = strength;

    memcpy(&VibrationValues[0], &VibrationValue, sizeof(HidVibrationValue));
    memcpy(&VibrationValues[1], &VibrationValue, sizeof(HidVibrationValue));
    last = 0;
    vlength = (length / 1000);
}

static void controller_switch_nx_rumble_stop(void) {
    memset(&VibrationValue_stop, 0, sizeof(HidVibrationValue));

    VibrationValue_stop.freq_low  = 160.0f;
    VibrationValue_stop.freq_high = 320.0f;

    memcpy(&VibrationValues[0], &VibrationValue_stop, sizeof(HidVibrationValue));
    memcpy(&VibrationValues[1], &VibrationValue_stop, sizeof(HidVibrationValue));

    hidSendVibrationValues(VibrationDeviceHandles[target_device], VibrationValues, 2);        
    hidSendVibrationValues(VibrationDeviceHandles[1-target_device], VibrationValues, 2);
    vlength = -1;
}

static void controller_switch_nx_shutdown(void) {
}

void controller_nx_rumble_loop(void){
    padUpdate(&pad);
    target_device = padIsHandheld(&pad) ? 0 : 1;
    if(vlength != -1 && last <= vlength){
        hidSendVibrationValues(VibrationDeviceHandles[target_device], VibrationValues, 2);        
        last++;
    } else vlength = -1;
}

#pragma GCC diagnostic pop

struct ControllerAPI controller_switch = {
    VK_INVALID,
    controller_switch_nx_init,
    controller_switch_nx_read,
    controller_switch_nx_rawkey,
    controller_switch_nx_rumble_play,
    controller_switch_nx_rumble_stop,
    NULL, // no rebinding
    controller_switch_nx_shutdown
};

#endif
