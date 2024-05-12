#include "PR/os.h"
#include "PR/rcp.h"

OSViMode osViModeTable[] = {
    {
        OS_VI_NTSC_LPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                             // width
            OS_VI_BURST(57, 34, 5, 62),                   // burst
            OS_VI_VSYNC(525),                             // vSync
            OS_VI_HSYNC(3093, 0),                         // hSync
            OS_VI_LEAP(3093, 3093),                       // leap
            OS_VI_HSTART(108, 748),                       // hStart
            OS_VI_SCALE(2, 0),                            // xScale
            OS_VI_VCURRENT(0),                            // vCurrent
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
    },
    {
        OS_VI_NTSC_LPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                  // width
            OS_VI_BURST(57, 34, 5, 62),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3093, 0),                                              // hSync
            OS_VI_LEAP(3093, 3093),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(2, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                // width
            OS_VI_BURST(57, 34, 5, 62),                                      // burst
            OS_VI_VSYNC(525),                                                // vSync
            OS_VI_HSYNC(3093, 0),                                            // hSync
            OS_VI_LEAP(3093, 3093),                                          // leap
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
    },
    {
        OS_VI_NTSC_LAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                          // width
            OS_VI_BURST(57, 34, 5, 62),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3093, 0),                                      // hSync
            OS_VI_LEAP(3093, 3093),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(2, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                             // width
            OS_VI_BURST(57, 34, 5, 62),                   // burst
            OS_VI_VSYNC(525),                             // vSync
            OS_VI_HSYNC(3093, 0),                         // hSync
            OS_VI_LEAP(3093, 3093),                       // leap
            OS_VI_HSTART(108, 748),                       // hStart
            OS_VI_SCALE(2, 0),                            // xScale
            OS_VI_VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                  // width
            OS_VI_BURST(57, 34, 5, 62),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3093, 0),                                              // hSync
            OS_VI_LEAP(3093, 3093),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(2, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                     // width
            OS_VI_BURST(57, 34, 5, 62),           // burst
            OS_VI_VSYNC(525),                     // vSync
            OS_VI_HSYNC(3093, 0),                 // hSync
            OS_VI_LEAP(3093, 3093),               // leap
            OS_VI_HSTART(108, 748),               // hStart
            OS_VI_SCALE(2, 0),                    // xScale
            OS_VI_VCURRENT(0),                    // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_LAF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                          // width
            OS_VI_BURST(57, 34, 5, 62),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3093, 0),                                      // hSync
            OS_VI_LEAP(3093, 3093),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(2, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                                 // width
            OS_VI_BURST(57, 34, 5, 62),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3093, 0),                                              // hSync
            OS_VI_LEAP(3093, 3093),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                                  // width
            OS_VI_BURST(57, 34, 5, 62),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3093, 0),                                              // hSync
            OS_VI_LEAP(3093, 3093),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                         // width
            OS_VI_BURST(57, 34, 5, 62),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3093, 0),                                      // hSync
            OS_VI_LEAP(3093, 3093),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(1, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                          // width
            OS_VI_BURST(57, 34, 5, 62),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3093, 0),                                      // hSync
            OS_VI_LEAP(3093, 3093),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(1, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                                 // width
            OS_VI_BURST(57, 34, 5, 62),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3093, 0),                                              // hSync
            OS_VI_LEAP(3093, 3093),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_NTSC_HPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                                  // width
            OS_VI_BURST(57, 34, 5, 62),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3093, 0),                                              // hSync
            OS_VI_LEAP(3093, 3093),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },

#if LIBULTRA_VERSION > OS_VER_D || (LIBULTRA_VERSION == OS_VER_D && LIBULTRA_REVISION == 0)
    {
        OS_VI_PAL_LPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(625),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
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
    },
    {
        OS_VI_PAL_LPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),           // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_LAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(625),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
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
    },
    {
        OS_VI_PAL_LAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),           // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_LPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(625),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(95, 569),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(95, 569),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            }
        }
    },
    {
        OS_VI_PAL_LPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),          // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_LAN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(625),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(95, 569),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(95, 569),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            }
        }
    },
    {
        OS_VI_PAL_LAF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(2, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),          // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_HPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                          // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(1, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(1, 0),           // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_HPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(1, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(0.5, 0.5),      // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(0.5, 0.5),       // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_HAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                          // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(1, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(1, 0),           // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_HAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(1, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(0.5, 0.5),      // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(0.5, 0.5),       // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_HPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                          // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(1, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),          // origin
                OS_VI_SCALE(1, 0),           // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_PAL_HPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                           // width
            OS_VI_BURST(58, OS_VI_BURST_CW_PAL, 4, OS_VI_BURST_CS_PAL), // burst
            OS_VI_VSYNC(624),                                           // vSync
            OS_VI_HSYNC(3177, OS_VI_HSYNC_LEAP_PAL),                    // hSync
            OS_VI_LEAP(3183, OS_VI_LEAP_LOWER_PAL),                     // leap
            OS_VI_HSTART(128, 768),                                     // hStart
            OS_VI_SCALE(1, 0),                                          // xScale
            OS_VI_VCURRENT(0),                                          // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),         // origin
                OS_VI_SCALE(0.5, 0.5),      // yScale
                OS_VI_HSTART(93, 567),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),          // origin
                OS_VI_SCALE(0.5, 0.5),       // yScale
                OS_VI_HSTART(95, 569),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
#endif

#if LIBULTRA_VERSION > OS_VER_D || (LIBULTRA_VERSION == OS_VER_D && LIBULTRA_REVISION >= 1)
    {
        OS_VI_MPAL_LPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                             // width
            OS_VI_BURST(57, 30, 5, 70),                   // burst
            OS_VI_VSYNC(525),                             // vSync
            OS_VI_HSYNC(3089, 4),                         // hSync
            OS_VI_LEAP(3097, 3098),                       // leap
            OS_VI_HSTART(108, 748),                       // hStart
            OS_VI_SCALE(2, 0),                            // xScale
            OS_VI_VCURRENT(0),                            // vCurrent
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
    },
    {
        OS_VI_MPAL_LPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                  // width
            OS_VI_BURST(57, 30, 5, 70),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3088, 0),                                              // hSync
            OS_VI_LEAP(3100, 3100),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(2, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
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
    },
    {
        OS_VI_MPAL_LAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                          // width
            OS_VI_BURST(57, 30, 5, 70),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3088, 0),                                      // hSync
            OS_VI_LEAP(3100, 3100),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(2, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),         // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                             // width
            OS_VI_BURST(57, 30, 5, 70),                   // burst
            OS_VI_VSYNC(525),                             // vSync
            OS_VI_HSYNC(3089, 4),                         // hSync
            OS_VI_LEAP(3097, 3098),                       // leap
            OS_VI_HSTART(108, 748),                       // hStart
            OS_VI_SCALE(2, 0),                            // xScale
            OS_VI_VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                  // width
            OS_VI_BURST(57, 30, 5, 70),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3088, 0),                                              // hSync
            OS_VI_LEAP(3100, 3100),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(2, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LAN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                     // width
            OS_VI_BURST(57, 30, 5, 70),           // burst
            OS_VI_VSYNC(525),                     // vSync
            OS_VI_HSYNC(3089, 4),                 // hSync
            OS_VI_LEAP(3097, 3098),               // leap
            OS_VI_HSTART(108, 748),               // hStart
            OS_VI_SCALE(2, 0),                    // xScale
            OS_VI_VCURRENT(0),                    // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_LAF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                          // width
            OS_VI_BURST(57, 30, 5, 70),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3088, 0),                                      // hSync
            OS_VI_LEAP(3100, 3100),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(2, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.25),      // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0.75),      // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                                 // width
            OS_VI_BURST(57, 30, 5, 70),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3088, 0),                                              // hSync
            OS_VI_LEAP(3100, 3100),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                                  // width
            OS_VI_BURST(57, 30, 5, 70),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3088, 0),                                              // hSync
            OS_VI_LEAP(3100, 3100),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                         // width
            OS_VI_BURST(57, 30, 5, 70),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3088, 0),                                      // hSync
            OS_VI_LEAP(3100, 3100),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(1, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                          // width
            OS_VI_BURST(57, 30, 5, 70),                                // burst
            OS_VI_VSYNC(524),                                          // vSync
            OS_VI_HSYNC(3088, 0),                                      // hSync
            OS_VI_LEAP(3100, 3100),                                    // leap
            OS_VI_HSTART(108, 748),                                    // hStart
            OS_VI_SCALE(1, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { //[0]
                OS_VI_ORIGIN(1280),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { //[1]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                                 // width
            OS_VI_BURST(57, 30, 5, 70),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3088, 0),                                              // hSync
            OS_VI_LEAP(3100, 3100),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),        // origin
                OS_VI_SCALE(1, 0),         // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
    {
        OS_VI_MPAL_HPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                                  // width
            OS_VI_BURST(57, 30, 5, 70),                                        // burst
            OS_VI_VSYNC(524),                                                  // vSync
            OS_VI_HSYNC(3088, 0),                                              // hSync
            OS_VI_LEAP(3100, 3100),                                            // leap
            OS_VI_HSTART(108, 748),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(35, 509),     // vStart
                OS_VI_BURST(2, 2, 11, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),        // origin
                OS_VI_SCALE(0.5, 0.5),     // yScale
                OS_VI_HSTART(37, 511),     // vStart
                OS_VI_BURST(4, 2, 14, 0),  // vBurst
                OS_VI_VINTR(2),            // vIntr
            }
        }
    },
#endif

#if LIBULTRA_VERSION >= OS_VER_J
    {
        OS_VI_FPAL_LPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                             // width
            OS_VI_BURST(58, 30, 4, 69),                   // burst
            OS_VI_VSYNC(625),                             // vSync
            OS_VI_HSYNC(3177, 23),                        // hSync
            OS_VI_LEAP(3183, 3181),                       // leap
            OS_VI_HSTART(128, 768),                       // hStart
            OS_VI_SCALE(2, 0),                            // xScale
            OS_VI_VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                  // width
            OS_VI_BURST(58, 30, 4, 69),                                        // burst
            OS_VI_VSYNC(624),                                                  // vSync
            OS_VI_HSYNC(3177, 23),                                             // hSync
            OS_VI_LEAP(3183, 3181),                                            // leap
            OS_VI_HSTART(128, 768),                                            // hStart
            OS_VI_SCALE(2, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),           // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                // width
            OS_VI_BURST(58, 30, 4, 69),                                      // burst
            OS_VI_VSYNC(625),                                                // vSync
            OS_VI_HSYNC(3177, 23),                                           // hSync
            OS_VI_LEAP(3183, 3181),                                          // leap
            OS_VI_HSTART(128, 768),                                          // hStart
            OS_VI_SCALE(2, 0),                                               // xScale
            OS_VI_VCURRENT(0),                                               // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                          // width
            OS_VI_BURST(58, 30, 4, 69),                                // burst
            OS_VI_VSYNC(624),                                          // vSync
            OS_VI_HSYNC(3177, 23),                                     // hSync
            OS_VI_LEAP(3183, 3181),                                    // leap
            OS_VI_HSTART(128, 768),                                    // hStart
            OS_VI_SCALE(2, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(640),          // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(640),           // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                             // width
            OS_VI_BURST(58, 30, 4, 69),                   // burst
            OS_VI_VSYNC(625),                             // vSync
            OS_VI_HSYNC(3177, 23),                        // hSync
            OS_VI_LEAP(3183, 3181),                       // leap
            OS_VI_HSTART(128, 768),                       // hStart
            OS_VI_SCALE(2, 0),                            // xScale
            OS_VI_VCURRENT(0),                            // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                                  // width
            OS_VI_BURST(58, 30, 4, 69),                                        // burst
            OS_VI_VSYNC(624),                                                  // vSync
            OS_VI_HSYNC(3177, 23),                                             // hSync
            OS_VI_LEAP(3183, 3181),                                            // leap
            OS_VI_HSTART(128, 768),                                            // hStart
            OS_VI_SCALE(2, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),          // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LAN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                     // width
            OS_VI_BURST(58, 30, 4, 69),           // burst
            OS_VI_VSYNC(625),                     // vSync
            OS_VI_HSYNC(3177, 23),                // hSync
            OS_VI_LEAP(3183, 3181),               // leap
            OS_VI_HSTART(128, 768),               // hStart
            OS_VI_SCALE(2, 0),                    // xScale
            OS_VI_VCURRENT(0),                    // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(47, 617),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_LAF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(320),                                          // width
            OS_VI_BURST(58, 30, 4, 69),                                // burst
            OS_VI_VSYNC(624),                                          // vSync
            OS_VI_HSYNC(3177, 23),                                     // hSync
            OS_VI_LEAP(3183, 3181),                                    // leap
            OS_VI_HSTART(128, 768),                                    // hStart
            OS_VI_SCALE(2, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0.25),       // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(1280),          // origin
                OS_VI_SCALE(1, 0.75),        // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_HPN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                                 // width
            OS_VI_BURST(58, 30, 4, 69),                                        // burst
            OS_VI_VSYNC(624),                                                  // vSync
            OS_VI_HSYNC(3177, 23),                                             // hSync
            OS_VI_LEAP(3183, 3181),                                            // leap
            OS_VI_HSTART(128, 768),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(1, 0),           // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_HPF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                                  // width
            OS_VI_BURST(58, 30, 4, 69),                                        // burst
            OS_VI_VSYNC(624),                                                  // vSync
            OS_VI_HSYNC(3177, 23),                                             // hSync
            OS_VI_LEAP(3183, 3181),                                            // leap
            OS_VI_HSTART(128, 768),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(0.5, 0.5),      // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(0.5, 0.5),       // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_HAN1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                         // width
            OS_VI_BURST(58, 30, 4, 69),                                // burst
            OS_VI_VSYNC(624),                                          // vSync
            OS_VI_HSYNC(3177, 23),                                     // hSync
            OS_VI_LEAP(3183, 3181),                                    // leap
            OS_VI_HSTART(128, 768),                                    // hStart
            OS_VI_SCALE(1, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(1, 0),           // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_HAF1,  // type
        { // comRegs
            VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_DIVOT_ON | VI_CTRL_SERRATE_ON | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                          // width
            OS_VI_BURST(58, 30, 4, 69),                                // burst
            OS_VI_VSYNC(624),                                          // vSync
            OS_VI_HSYNC(3177, 23),                                     // hSync
            OS_VI_LEAP(3183, 3181),                                    // leap
            OS_VI_HSTART(128, 768),                                    // hStart
            OS_VI_SCALE(1, 0),                                         // xScale
            OS_VI_VCURRENT(0),                                         // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(1280),         // origin
                OS_VI_SCALE(0.5, 0.5),      // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(2560),          // origin
                OS_VI_SCALE(0.5, 0.5),       // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_HPN2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_3 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(1280),                                                 // width
            OS_VI_BURST(58, 30, 4, 69),                                        // burst
            OS_VI_VSYNC(624),                                                  // vSync
            OS_VI_HSYNC(3177, 23),                                             // hSync
            OS_VI_LEAP(3183, 3181),                                            // leap
            OS_VI_HSTART(128, 768),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),         // origin
                OS_VI_SCALE(1, 0),          // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),          // origin
                OS_VI_SCALE(1, 0),           // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    },
    {
        OS_VI_FPAL_HPF2,  // type
        { // comRegs
            VI_CTRL_TYPE_32 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
                VI_CTRL_SERRATE_ON | VI_CTRL_ANTIALIAS_MODE_2 | VI_CTRL_PIXEL_ADV_3,  // ctrl
            OS_VI_WIDTH(640),                                                  // width
            OS_VI_BURST(58, 30, 4, 69),                                        // burst
            OS_VI_VSYNC(624),                                                  // vSync
            OS_VI_HSYNC(3177, 23),                                             // hSync
            OS_VI_LEAP(3183, 3181),                                            // leap
            OS_VI_HSTART(128, 768),                                            // hStart
            OS_VI_SCALE(1, 0),                                                 // xScale
            OS_VI_VCURRENT(0),                                                 // vCurrent
        },
        { // fldRegs
            { // [0]
                OS_VI_ORIGIN(2560),         // origin
                OS_VI_SCALE(0.5, 0.5),      // yScale
                OS_VI_HSTART(45, 615),      // vStart
                OS_VI_BURST(107, 2, 9, 0),  // vBurst
                OS_VI_VINTR(2),             // vIntr
            },
            { // [1]
                OS_VI_ORIGIN(5120),          // origin
                OS_VI_SCALE(0.5, 0.5),       // yScale
                OS_VI_HSTART(47, 617),       // vStart
                OS_VI_BURST(105, 2, 13, 0),  // vBurst
                OS_VI_VINTR(2),              // vIntr
            }
        }
    }
#endif
};
