#include "libultra_internal.h"
#include "PR/rcp.h"
#include "piint.h"

s32 __osEPiRawReadIo(OSPiHandle *pihandle, u32 devAddr, u32 *data) {
    register s32 stat;

    WAIT_ON_IO_BUSY(stat);
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}
