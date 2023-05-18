#include "piint.h"

s32 osEPiRawWriteIo(OSPiHandle *pihandle, u32 devAddr, u32 data) {
    register u32 stat;
#if LIBULTRA_VERSION > OS_VER_H
    register u32 domain;
#endif

#if LIBULTRA_VERSION > OS_VER_H
    EPI_SYNC(pihandle, stat, domain);
#else
    WAIT_ON_IO_BUSY(stat);
#endif
    IO_WRITE(pihandle->baseAddress | devAddr, data);

    return 0;
}
