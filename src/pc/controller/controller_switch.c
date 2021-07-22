#ifdef CAPI_SWITCH

#include <switch.h>
#include <ultra64.h>

#include <sm64.h>
#include "../../game/level_update.h"

#include "controller_api.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

static bool isSixAxis = false;
static HidVibrationDeviceHandle VibrationDeviceHandles[2][2];
static HidSixAxisSensorHandle sixAxisHandles[4];
static PadState padState;

static void start_six_axis() {
    isSixAxis = true;
    for(int i = 0; i < 4; i++)
        hidStartSixAxisSensor(sixAxisHandles[i]);
}

static void stop_six_axis() {
    isSixAxis = false;
    for(int i = 0; i < 4; i++)
        hidStopSixAxisSensor(sixAxisHandles[i]);
}

static s32 gyro_to_stick(float f) {
    s32 tmp = f * -255;
    if(tmp < -80) tmp = -80;
    else if(tmp > 80) tmp = 80;
    return tmp;
}

static void controller_switch_nx_init(void) {
    padConfigureInput(1, HidNpadStyleSet_NpadFullCtrl);
    padInitializeDefault(&padState);

    hidInitializeVibrationDevices(VibrationDeviceHandles[0], 2, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    hidInitializeVibrationDevices(VibrationDeviceHandles[1], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);
    //Initiating the SixAxis, needs to be done for all options; Obviously no GC Controller.
    hidGetSixAxisSensorHandles(&sixAxisHandles[0], 1, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    hidGetSixAxisSensorHandles(&sixAxisHandles[1], 1, HidNpadIdType_No1,      HidNpadStyleTag_NpadFullKey);
    hidGetSixAxisSensorHandles(&sixAxisHandles[2], 2, HidNpadIdType_No1,      HidNpadStyleTag_NpadJoyDual);
}

static void controller_switch_nx_read(OSContPad *pad) {
    padUpdate(&padState);

    switch(gMarioState->action) {
        case ACT_IN_CANNON:
        case ACT_FIRST_PERSON:
            if(!isSixAxis) start_six_axis();
            break;
        default:
            if(isSixAxis) stop_six_axis();    
    }

    u64 pressed = padGetButtons(&padState);
    
    HidAnalogStickState sticks[2];
    sticks[0] = padGetStickPos(&padState, 0);
    sticks[1] = padGetStickPos(&padState, 1);

    if(pressed & HidNpadButton_Plus)       pad->button |= START_BUTTON;
    if(pressed & HidNpadButton_Minus)     pad->button |= START_BUTTON;

    if(pressed & HidNpadButton_B)             pad->button |= A_BUTTON;
    if(pressed & HidNpadButton_A)             pad->button |= A_BUTTON;
    if(pressed & HidNpadButton_Y)             pad->button |= B_BUTTON;
    if(pressed & HidNpadButton_X)             pad->button |= B_BUTTON;

    if(pressed & HidNpadButton_L)            pad->button |= L_TRIG;
    if(pressed & HidNpadButton_ZL)           pad->button |= Z_TRIG;
    if(pressed & HidNpadButton_R)            pad->button |= R_TRIG;
    if(pressed & HidNpadButton_ZR)           pad->button |= R_TRIG;

    if(pressed & HidNpadButton_Up)      pad->button |= U_JPAD;
    if(pressed & HidNpadButton_Left)    pad->button |= L_JPAD;
    if(pressed & HidNpadButton_Down)    pad->button |= D_JPAD;
    if(pressed & HidNpadButton_Right)   pad->button |= R_JPAD;

    if(sticks[1].x > 0x4000)   pad->button |= R_CBUTTONS;
    if(sticks[1].x < -0x4000)  pad->button |= L_CBUTTONS;
    if(sticks[1].y > 0x4000)   pad->button |= U_CBUTTONS;
    if(sticks[1].y < -0x4000)  pad->button |= D_CBUTTONS;

    s32 leftX = sticks[0].x / 409;
    s32 leftY = sticks[0].y / 409;
    s32 rightX = sticks[1].x / 409;
    s32 rightY = sticks[1].y / 409;

    if(isSixAxis && ABS(leftX) < 20 && ABS(leftY) < 20) {
        HidSixAxisSensorState sixAxis;

        u64 style_set = padGetStyleSet(&padState);
        if (style_set & HidNpadStyleTag_NpadHandheld)
            hidGetSixAxisSensorStates(sixAxisHandles[0], &sixAxis, 1);
        else if (style_set & HidNpadStyleTag_NpadFullKey)
            hidGetSixAxisSensorStates(sixAxisHandles[1], &sixAxis, 1);
        else if (style_set & HidNpadStyleTag_NpadJoyDual) {
            // For JoyDual, read from either the Left or Right Joy-Con depending on which is/are connected
            u64 attrib = padGetAttributes(&padState);
            if (attrib & HidNpadAttribute_IsRightConnected)
                hidGetSixAxisSensorStates(sixAxisHandles[3], &sixAxis, 1);
            else if (attrib & HidNpadAttribute_IsLeftConnected)
                hidGetSixAxisSensorStates(sixAxisHandles[2], &sixAxis, 1);
        }

        leftX = gyro_to_stick(sixAxis.angular_velocity.y); //Gyroscope Y-Axis (Controller X)
        leftY = gyro_to_stick(sixAxis.angular_velocity.x); //Gyroscope X-Axis (Controller Y)
    }

    pad->stick_x = leftX;
    pad->stick_y = leftY;
    pad->ext_stick_x = rightX;
    pad->ext_stick_y = rightY;
}

static u32 controller_switch_nx_rawkey(void)  {
    return VK_INVALID;
}

static void controller_switch_nx_rumble_play(f32 strength, UNUSED f32 length) {
    HidVibrationValue VibrationValues[2];
    HidVibrationValue VibrationValue = {0};

    VibrationValue.freq_high = VibrationValue.freq_low = strength * 1.26f;
    VibrationValue.amp_high = VibrationValue.amp_low = 1.0f;

    memcpy(&VibrationValues[0], &VibrationValue, sizeof(HidVibrationValue));
    memcpy(&VibrationValues[1], &VibrationValue, sizeof(HidVibrationValue));

    padUpdate(&padState);
    u32 target_device = padIsHandheld(&padState) ? 0 : 1;
    hidSendVibrationValues(VibrationDeviceHandles[target_device], VibrationValues, 2);
}

static void controller_switch_nx_rumble_stop(void) {
    HidVibrationValue VibrationValues[2];
    HidVibrationValue VibrationValue_stop = {0};

    VibrationValue_stop.freq_low  = 160.0f;
    VibrationValue_stop.freq_high = 320.0f;

    memcpy(&VibrationValues[0], &VibrationValue_stop, sizeof(HidVibrationValue));
    memcpy(&VibrationValues[1], &VibrationValue_stop, sizeof(HidVibrationValue));

    hidSendVibrationValues(VibrationDeviceHandles[0], VibrationValues, 2);        
    hidSendVibrationValues(VibrationDeviceHandles[1], VibrationValues, 2);
}

static void controller_switch_nx_shutdown(void) {
}

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
