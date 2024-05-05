#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"
#include "../io/piint.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

typedef struct {
    u32 inst1;
    u32 inst2;
    u32 inst3;
    u32 inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble;

u64 osClockRate = OS_CLOCK_RATE;
#if LIBULTRA_VERSION >= OS_VER_H
u32 osViClock = VI_NTSC_CLOCK;
#endif
u32 __osShutdown = 0;
#if LIBULTRA_VERSION >= OS_VER_F
u32 __OSGlobalIntMask = OS_IM_ALL;
u32 __osLeoPresent = 0;
#endif
#ifdef _FINALROM
u32 __osFinalrom;
#endif

#if LIBULTRA_VERSION >= OS_VER_J
// This function is static only in 2.0J
void __createSpeedParam(void) {
    __Dom1SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom1SpeedParam.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    __Dom1SpeedParam.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    __Dom1SpeedParam.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    __Dom1SpeedParam.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);

    __Dom2SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom2SpeedParam.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    __Dom2SpeedParam.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    __Dom2SpeedParam.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    __Dom2SpeedParam.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
}
#endif

void __osInitialize_common(void) {
    u32 pifdata;
#if LIBULTRA_VERSION < OS_VER_J
    u32 clock = 0;
#endif

#ifdef _FINALROM
    __osFinalrom = TRUE;
#endif
    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);
#if LIBULTRA_VERSION >= OS_VER_K
    __osSetWatchLo(0x4900000);
#endif
#ifdef BBPLAYER
    {
        u32 x = IO_WRITE(MI_3C_REG, 0x22000);
        u32 y = IO_WRITE(MI_3C_REG, 0x11000);
        __osBbIsBb = ((x & 0x140) == 0x140) && ((y & 0x140) == 0);
    }

    if (__osBbIsBb && (IO_READ(PI_60_REG) & 0xC0000000)) {
        __osBbIsBb = 2;
    }

    if (__osBbIsBb) {
        osTvType = OS_TV_NTSC;
        osRomType = DEVICE_TYPE_CART;
        osResetType = 0;
        osVersion = 1;
        osMemSize = 4 * 1024 * 1024; // 4MB RAM
    }

    if (__osBbIsBb == 0) {
#endif
    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) { //last byte of joychannel ram
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) { //todo: magic constant
    }
#ifdef BBPLAYER
    }
#endif

    *(__osExceptionVector *) UT_VEC = __osExceptionPreamble; // TLB miss
    *(__osExceptionVector *) XUT_VEC = __osExceptionPreamble; // XTLB miss
    *(__osExceptionVector *) ECC_VEC = __osExceptionPreamble; // cache errors
    *(__osExceptionVector *) E_VEC = __osExceptionPreamble; // general exceptions

    osWritebackDCache((void *) UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *) UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
#if LIBULTRA_VERSION >= OS_VER_J
    __createSpeedParam();
    osUnmapTLBAll();
#endif
    osMapTLBRdb();

#if LIBULTRA_VERSION < OS_VER_J
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock) {
        osClockRate = clock;
    }
#endif
    osClockRate = osClockRate * 3 / 4;

    if (osResetType == 0) { // cold reset
        bzero(osAppNMIBuffer, OS_APP_NMI_BUFSIZE);
    }

#if LIBULTRA_VERSION >= OS_VER_H
    if (osTvType == OS_TV_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }
#elif LIBULTRA_VERSION == OS_VER_F
    {
        u32 leoStatus, status;
        WAIT_ON_IO_BUSY(status);

        if (!((leoStatus = IO_READ(LEO_STATUS)) & LEO_STATUS_PRESENCE_MASK)) {
            __osLeoPresent = 1;
            __osSetHWIntrRoutine(1, __osLeoInterrupt);
        } else {
            __osLeoPresent = 0;
        }
    }
#endif
#if LIBULTRA_VERSION >= OS_VER_J
    // Wait until there are no RCP interrupts
    if (__osGetCause() & CAUSE_IP5) {
        while (TRUE) {
        }
    }
#endif
#ifdef BBPLAYER
    if (!__osBbIsBb) { // On iQue these are set before the game runs
        __osBbEepromSize = 0x200; // 4K EEPROM size
        __osBbPakSize = 0x8000; // SRAM size
        __osBbFlashSize = 0x20000; // FlashRAM size
        // iQue doesn't have a physical save chip, so store them in RAM
        __osBbEepromAddress = (u8 *) (0x80400000 - 0x200);
        __osBbPakAddress[0] = (u32 *)(0x80400000 - 0x8000 - 0x200);
        __osBbPakAddress[1] = NULL;
        __osBbPakAddress[2] = NULL;
        __osBbPakAddress[3] = NULL;
        __osBbFlashAddress = 0x80400000 - 0x20000;
        __osBbSramSize = __osBbFlashSize; // 0x20000
        __osBbSramAddress = __osBbFlashAddress; // 0x80400000 - 0x20000
    }
    if (__osBbIsBb) {
        IO_WRITE(PI_64_REG, IO_READ(PI_64_REG) & 0x7FFFFFFF);
        IO_WRITE(MI_3C_REG, 0x20000);
        IO_WRITE(SI_0C_REG, 0);
        IO_WRITE(SI_1C_REG, (IO_READ(SI_1C_REG) & 0x80FFFFFF) | 0x2F400000);
    }
#endif
#if LIBULTRA_VERSION >= OS_VER_J
    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    IO_WRITE(AI_DACRATE_REG, AI_MAX_DAC_RATE - 1);
    IO_WRITE(AI_BITRATE_REG, AI_MAX_BIT_RATE - 1);
#endif
}

#if LIBULTRA_VERSION >= OS_VER_K
void __osInitialize_autodetect(void) {
#ifndef _FINALROM
    if (__checkHardware_msp()) {
        __osInitialize_msp();
    } else if (__checkHardware_kmc()) {
        __osInitialize_kmc();
    } else if (__checkHardware_isv()) {
        __osInitialize_isv();
    } else {
        __osInitialize_emu();
    }
#endif
}
#endif
