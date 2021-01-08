#ifdef TARGET_SWITCH

#include <switch.h>

#include "nx_main.h"

void initNX(){
    appletInitializeGamePlayRecording();
    socketInitializeDefault();
    nxlinkStdio();    
    appletSetGamePlayRecordingState(1);

    Result rc = psmInitialize();
    if (R_FAILED(rc)) psmExit();
}

void exitNX(){
    socketExit();
    appletSetGamePlayRecordingState(0);
}

float getBatteryPercentage(){
    u32 charge;
    psmGetBatteryChargePercentage(&charge);
    return (charge / 100.0f);
}

#endif
