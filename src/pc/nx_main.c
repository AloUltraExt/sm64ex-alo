#ifdef TARGET_SWITCH

#include <switch.h>

#include "nx_main.h"

void initNX(){
    //appletInitializeGamePlayRecording();
    //socketInitializeDefault();
    //nxlinkStdio();    
    //appletSetGamePlayRecordingState(1);

    //Result rc = psmInitialize();
    //if (R_FAILED(rc)) psmExit();
}

void exitNX(){
    //socketExit();
    //appletSetGamePlayRecordingState(0);
}

void enableBoostMode(){
    appletSetCpuBoostMode(ApmCpuBoostMode_FastLoad);
}

void disableBoostMode(){
    appletSetCpuBoostMode(ApmCpuBoostMode_Normal);
}

#endif
