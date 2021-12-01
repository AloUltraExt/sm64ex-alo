#include "libultra_internal.h"
#include "PR/rcp.h"
#include "osint.h"
#include "macros.h"

s32 osAiSetFrequency(u32 freq) {
    register u32 dacRate;
    register s32 bitRate;
    register float ftmp;
    ftmp = osViClock / (float) freq + .5f;

    dacRate = ftmp;

    if (dacRate < AI_MIN_DAC_RATE) {
        return -1;
    }

    bitRate = (dacRate / 66) & 0xff;
    if (bitRate > AI_MAX_BIT_RATE) {
        bitRate = AI_MAX_BIT_RATE;
    }

    IO_WRITE(AI_DACRATE_REG, dacRate - 1);
    IO_WRITE(AI_BITRATE_REG, bitRate - 1);
    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    return osViClock / (s32) dacRate;
}

#ifndef VERSION_SH
UNUSED static void filler1(void) {
}

UNUSED static void filler2(void) {
}
#endif
