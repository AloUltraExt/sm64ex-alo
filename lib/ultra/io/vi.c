#include <macros.h>
#include <PR/os_internal.h>
#include <PR/R4300.h>
#include <PR/rcp.h>

ALIGNED8 __OSViContext vi[2] = { 0 };
__OSViContext *__osViCurr = &vi[0];
__OSViContext *__osViNext = &vi[1];

#if LIBULTRA_VERSION == OS_VER_E || LIBULTRA_VERSION == OS_VER_F
u32 osViClock = VI_NTSC_CLOCK;
u32 osIsNtscEnabled = FALSE; // OS_TV_PAL
#elif LIBULTRA_VERSION == OS_VER_D
u32 osIsNtscEnabled = TRUE; // OS_TV_NTSC
u32 osViClock = VI_NTSC_CLOCK;
#endif

void __osViInit(void) {
#if LIBULTRA_VERSION == OS_VER_D && LIBULTRA_REVISION >= 1
    osIsNtscEnabled = osTvType;
#endif

    bzero(vi, sizeof(vi));
    __osViCurr = &vi[0];
    __osViNext = &vi[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;

#if LIBULTRA_VERSION == OS_VER_D && LIBULTRA_REVISION == 0
    if (osIsNtscEnabled != FALSE) {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
    } else {
        __osViNext->modep = &osViModePalLan1;
        osViClock = VI_PAL_CLOCK;
    }
#elif LIBULTRA_VERSION == OS_VER_D && LIBULTRA_REVISION >= 1
    if (osIsNtscEnabled == TRUE) {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
    } else {
        __osViNext->modep = &osViModePalLan1;
        osViClock = VI_MPAL_CLOCK;
    }
#elif LIBULTRA_VERSION == OS_VER_E || LIBULTRA_VERSION == OS_VER_F
    if (osTvType == OS_TV_PAL) {
        __osViNext->modep = &osViModePalLan1;
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
        osViClock = VI_MPAL_CLOCK;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
    }
#else
    __osViNext->framep = (void *) K0BASE;
    __osViCurr->framep = (void *) K0BASE;
    if (osTvType == OS_TV_PAL) {
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == OS_TV_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
    }
#endif
    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;

#if LIBULTRA_VERSION > OS_VER_D || (LIBULTRA_VERSION == OS_VER_D && LIBULTRA_REVISION >= 1)
    while (IO_READ(VI_CURRENT_REG) > 10) { //wait for vsync?
    }

    IO_WRITE(VI_STATUS_REG, 0); //pixel size blank (no data, no sync)
#endif
    __osViSwapContext();
}
