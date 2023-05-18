#include "PR/os.h"
#include "PR/rcp.h"

OSViMode osViModePalLan1 = {
    OS_VI_PAL_LAN1,  // type
    { // comRegs
        VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
            VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
        OS_VI_WIDTH(320),                                                // width
        OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL),      // burst
        OS_VI_VSYNC(625),                                                // vSync
        OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                         // hSync
        OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                          // leap
        OS_VI_HSTART(128, 768),                                          // hStart
        OS_VI_SCALE(2, 0),                                               // xScale
        OS_VI_VCURRENT(0),                                               // vCurrent
    },
    { // fldRegs
        { // [0]
            OS_VI_ORIGIN(640),          // origin
            OS_VI_SCALE(1, 0),          // yScale
            OS_VI_HSTART(95, 569),      // vStart
            OS_VI_BURST(107, 2, 9, 0),  // vBurst
            OS_VI_VINTR(2),             // vIntr
        },
        { // [1]
            OS_VI_ORIGIN(640),          // origin
            OS_VI_SCALE(1, 0),          // yScale
            OS_VI_HSTART(95, 569),      // vStart
            OS_VI_BURST(107, 2, 9, 0),  // vBurst
            OS_VI_VINTR(2),             // vIntr
        }
    }
};
