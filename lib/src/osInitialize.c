#include "libultra_internal.h"
#include "PR/R4300.h"
#include "piint.h"
#include "PR/rcp.h"
#include <macros.h>

typedef struct {
    u32 inst1;
    u32 inst2;
    u32 inst3;
    u32 inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble;

#if defined(VERSION_EU) || defined(VERSION_SH)
extern u32 __osSetHWintrRoutine(OSHWIntr, s32 (*));
extern s32 __osLeoInterrupt(void);
#endif

u32 __osFinalrom; // maybe initialized?
u64 osClockRate = OS_CLOCK_RATE;

#ifdef VERSION_SH
u32 osViClock = VI_NTSC_CLOCK;
#endif

u32 D_80334808 = 0; // used in __osException

#if defined(VERSION_EU) || defined(VERSION_SH)
u32 EU_D_80336C40;
u32 EU_D_80336C44;

u32 __OSGlobalIntMask = OS_IM_ALL;
u32 osDDActive = 0;
u8 EU_unusedZeroes[8] = { 0 };
#endif


void osInitialize(void) {
    u32 pifdata;
    u32 clock = 0;

#if defined(VERSION_EU)
    u32 leoStatus;
    u32 status;
#endif

    UNUSED u32 sp2c;

    __osFinalrom = TRUE;
    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);
    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) {
        ;
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ;
    }
    *(__osExceptionVector *) UT_VEC = __osExceptionPreamble;
    *(__osExceptionVector *) XUT_VEC = __osExceptionPreamble;
    *(__osExceptionVector *) ECC_VEC = __osExceptionPreamble;
    *(__osExceptionVector *) E_VEC = __osExceptionPreamble;
    osWritebackDCache((void *) UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *) UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osMapTLBRdb();
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock) {
        osClockRate = clock;
    }
    osClockRate = osClockRate * 3 / 4;
    if (osResetType == RESET_TYPE_COLD_RESET) {
        bzero(osAppNmiBuffer, sizeof(osAppNmiBuffer));
    }

#if defined(VERSION_SH)
    if (osTvType == TV_TYPE_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == TV_TYPE_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }
#elif defined(VERSION_EU)
    WAIT_ON_IO_BUSY(status);

    if (!((leoStatus = IO_READ(LEO_STATUS)) & LEO_STATUS_PRESENCE_MASK)) {
        osDDActive = 1;
        __osSetHWIntrRoutine(1, __osLeoInterrupt);
    } else {
        osDDActive = 0;
    }
#endif
}
