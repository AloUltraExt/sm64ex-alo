#include "piint.h"

s32 osEPiRawReadIo(OSPiHandle *pihandle, u32 devAddr, u32 *data) {
    register s32 stat;
#if LIBULTRA_VERSION > OS_VER_H
    register u32 domain;
#endif

#if LIBULTRA_VERSION > OS_VER_H
    EPI_SYNC(pihandle, stat, domain);
#else
    WAIT_ON_IO_BUSY(stat);
#endif
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}
