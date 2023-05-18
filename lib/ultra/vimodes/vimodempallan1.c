#include "PR/os.h"
#include "PR/rcp.h"

OSViMode osViModeMpalLan1 = {
    OS_VI_MPAL_LAN1,  // type
    { // comRegs
        VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
            VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
        OS_VI_WIDTH(320),                                                // width
        OS_VI_BURST(57, 30, 5, 70),                                      // burst
        OS_VI_VSYNC(525),                                                // vSync
        OS_VI_HSYNC(3089, 4),                                            // hSync
        OS_VI_LEAP(3097, 3098),                                          // leap
        OS_VI_HSTART(108, 748),                                          // hStart
        OS_VI_SCALE(2, 0),                                               // xScale
        OS_VI_VCURRENT(0),                                               // vCurrent
    },
    { // fldRegs
        { // [0]
            OS_VI_ORIGIN(640),         // origin
            OS_VI_SCALE(1, 0),         // yScale
            OS_VI_HSTART(37, 511),     // vStart
            OS_VI_BURST(4, 2, 14, 0),  // vBurst
            OS_VI_VINTR(2),            // vIntr
        },
        { // [1]
            OS_VI_ORIGIN(640),         // origin
            OS_VI_SCALE(1, 0),         // yScale
            OS_VI_HSTART(37, 511),     // vStart
            OS_VI_BURST(4, 2, 14, 0),  // vBurst
            OS_VI_VINTR(2),            // vIntr
        }
    }
};
