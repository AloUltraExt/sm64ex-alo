#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"
#include "PR/os.h"
#include "piint.h"
#include "macros.h"

#if LIBULTRA_VERSION >= OS_VER_J
ALIGNED8 OSPiHandle __CartRomHandle;

OSPiHandle* osCartRomInit(void) {
    u32 value = 0;
    u32 saveMask;
    static int first = 1;
    register u32 stat;
    u32 latency;
    u32 pulse;
    u32 pageSize;
    u32 relDuration;

    __osPiGetAccess();

    if (!first) {
        __osPiRelAccess();
        return &__CartRomHandle;
    }

    first = 0;
    __CartRomHandle.type = DEVICE_TYPE_CART;
    __CartRomHandle.baseAddress = PHYS_TO_K1(PI_DOM1_ADDR2);
    __CartRomHandle.domain = 0;
    __CartRomHandle.speed = 0;
    bzero(&__CartRomHandle.transferInfo, sizeof(__OSTranxInfo));

    WAIT_ON_IO_BUSY(stat);

    latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);
    pulse = IO_READ(PI_BSD_DOM1_PWD_REG);

    IO_WRITE(PI_BSD_DOM1_LAT_REG, 0xFF);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, 0);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, 3);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, 0xFF);

    value = IO_READ(__CartRomHandle.baseAddress);
    __CartRomHandle.latency = value & 0xFF;
    __CartRomHandle.pageSize = (value >> 0x10) & 0xF;
    __CartRomHandle.relDuration = (value >> 0x14) & 0xF;
    __CartRomHandle.pulse = (value >> 8) & 0xFF;

    IO_WRITE(PI_BSD_DOM1_LAT_REG, latency);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, pageSize);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, relDuration);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, pulse);

    saveMask = __osDisableInt();
    __CartRomHandle.next = __osPiTable;
    __osPiTable = &__CartRomHandle;
    __osRestoreInt(saveMask);
    __osPiRelAccess();

    return &__CartRomHandle;
}

#else
ALIGNED8 OSPiHandle CartRomHandle;

OSPiHandle *osCartRomInit(void) {
    u32 domain = 0;
    u32 saveMask;

    if (CartRomHandle.baseAddress == PHYS_TO_K1(PI_DOM1_ADDR2)) {
        return &CartRomHandle;
    }

    CartRomHandle.type = DEVICE_TYPE_CART;
    CartRomHandle.baseAddress = PHYS_TO_K1(PI_DOM1_ADDR2);
    osPiRawReadIo(0, &domain);
    CartRomHandle.latency = domain & 0xff;
    CartRomHandle.pulse = (domain >> 8) & 0xff;
    CartRomHandle.pageSize = (domain >> 0x10) & 0xf;
    CartRomHandle.relDuration = (domain >> 0x14) & 0xf;
    CartRomHandle.domain = PI_DOMAIN1;
#if LIBULTRA_VERSION >= OS_VER_I
    CartRomHandle.speed = 0;
#endif

    bzero(&CartRomHandle.transferInfo, sizeof(__OSTranxInfo));

    saveMask = __osDisableInt();
    CartRomHandle.next = __osPiTable;
    __osPiTable = &CartRomHandle;
    __osRestoreInt(saveMask);

    return &CartRomHandle;
}

#endif
