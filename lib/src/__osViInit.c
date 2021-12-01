#include "libultra_internal.h"
#include "hardware.h"

OSViContext sViContexts[2] = { 0 };
OSViContext *__osViCurr = &sViContexts[0];
OSViContext *__osViNext = &sViContexts[1];
#ifdef VERSION_EU
u32 osViClock = 0x02E6D354; // used for audio frequency calculations
u32 sTvType = TV_TYPE_PAL;
#elif !defined(VERSION_SH)
u32 sTvType = TV_TYPE_NTSC;
u32 osViClock = 0x02E6D354;
#endif

extern OSViMode osViModePalLan1;
extern OSViMode osViModeMpalLan1;
#if defined(VERSION_EU) || defined(VERSION_SH)
extern OSViMode osViModeNtscLan1;
#endif

void __osViInit(void) {
//#ifdef VERSION_JP
#ifdef VERSION_US
    sTvType = osTvType;
#endif
    bzero(sViContexts, sizeof(sViContexts));
    __osViCurr = &sViContexts[0];
    __osViNext = &sViContexts[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;

#if defined(VERSION_EU)

    if (osTvType == TV_TYPE_PAL) {
        __osViNext->modep = &osViModePalLan1;
        osViClock = 0x02F5B2D2;
    } else if (osTvType == TV_TYPE_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
        osViClock = 0x02E6025C;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = 0x02E6D354;
    }

#elif defined(VERSION_SH)

    __osViNext->buffer = (void *) 0x80000000;
    __osViCurr->buffer = (void *) 0x80000000;
    if (osTvType == TV_TYPE_PAL) {
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == TV_TYPE_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
    }

#else

#ifdef VERSION_JP
    if (sTvType != TV_TYPE_PAL)
#else
    if (sTvType == TV_TYPE_NTSC)
#endif
    {
        __osViNext->modep = &osViModePalLan1;
        osViClock = 0x02E6D354;
    } else {
        __osViNext->modep = &osViModeMpalLan1;
#if defined(VERSION_JP)
        osViClock = 0x02F5B2D2;
#elif defined(VERSION_US)
        osViClock = 0x02E6025C;
#endif
    }

#endif

    __osViNext->unk00 = 0x20;
    __osViNext->features = __osViNext->modep->comRegs.ctrl;
#ifndef VERSION_JP
    while (HW_REG(VI_CURRENT_REG, u32) > 0xa) {
        ;
    }
    HW_REG(VI_STATUS_REG, u32) = 0;
#endif
    __osViSwapContext();
}
