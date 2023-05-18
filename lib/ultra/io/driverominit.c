#include "PR/os_internal.h"
#include "PR/os.h"
#include "PR/rcp.h"
#include "macros.h"

extern OSPiHandle DriveRomHandle;

OSPiHandle *osDriveRomInit(void) {
    UNUSED s32 dummy = 0;
    u32 saveMask;

    DriveRomHandle.type = DEVICE_TYPE_BULK;
    DriveRomHandle.baseAddress = PHYS_TO_K1(PI_DOM1_ADDR1);
    DriveRomHandle.latency = 64;
    DriveRomHandle.pulse = 7;
    DriveRomHandle.pageSize = 7;
    DriveRomHandle.relDuration = 2;

    IO_WRITE(PI_BSD_DOM1_LAT_REG, DriveRomHandle.latency);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, DriveRomHandle.pulse);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, DriveRomHandle.pageSize);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, DriveRomHandle.relDuration);

    bzero(&DriveRomHandle.transferInfo, sizeof(__OSTranxInfo));

    saveMask = __osDisableInt();
    DriveRomHandle.next = __osPiTable;
    __osPiTable = &DriveRomHandle;
    __osRestoreInt(saveMask);

    return &DriveRomHandle;
}
