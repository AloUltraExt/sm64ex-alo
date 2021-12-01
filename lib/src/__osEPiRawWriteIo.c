#include "libultra_internal.h"
#include "PR/rcp.h"
#include "piint.h"

s32 __osEPiRawWriteIo(OSPiHandle *pihandle, u32 devAddr, u32 data) {
    register u32 stat;

    WAIT_ON_IO_BUSY(stat);
    IO_WRITE(pihandle->baseAddress | devAddr, data);

    return 0;
}
