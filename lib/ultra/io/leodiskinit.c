#include "PR/os_internal.h"
#include "PR/os.h"
#include "PR/rcp.h"
#include "macros.h"

// This file was removed in 2.0J
ALIGNED8 OSPiHandle LeoDiskHandle;
OSPiHandle *__osDiskHandle;

OSPiHandle *osLeoDiskInit(void) {
    u32 saveMask;

    LeoDiskHandle.type = DEVICE_TYPE_64DD;
    LeoDiskHandle.baseAddress = PHYS_TO_K1(PI_DOM2_ADDR1);
    LeoDiskHandle.latency = 3;
    LeoDiskHandle.pulse = 6;
    LeoDiskHandle.pageSize = 6;
    LeoDiskHandle.relDuration = 2;
#if LIBULTRA_VERSION >= OS_VER_H
    LeoDiskHandle.domain = PI_DOMAIN2;
#endif

    IO_WRITE(PI_BSD_DOM2_LAT_REG, LeoDiskHandle.latency);
    IO_WRITE(PI_BSD_DOM2_PWD_REG, LeoDiskHandle.pulse);
    IO_WRITE(PI_BSD_DOM2_PGS_REG, LeoDiskHandle.pageSize);
    IO_WRITE(PI_BSD_DOM2_RLS_REG, LeoDiskHandle.relDuration);
#if LIBULTRA_VERSION >= OS_VER_I
    LeoDiskHandle.speed = 0;
#endif

    bzero(&LeoDiskHandle.transferInfo, sizeof(__OSTranxInfo));
    saveMask = __osDisableInt();
    LeoDiskHandle.next = __osPiTable;
    __osPiTable = &LeoDiskHandle;
    __osDiskHandle = &LeoDiskHandle;
    __osRestoreInt(saveMask);

    return &LeoDiskHandle;
}
