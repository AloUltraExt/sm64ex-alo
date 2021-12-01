#include "libultra_internal.h"
#include "PR/rcp.h"
#include "new_func.h"
#include "PR/R4300.h"
#include "piint.h"

// TODO: This define is from os.h, but including that causes problems...
#define PI_DOMAIN1 0

#ifdef VERSION_SH
extern OSPiHandle *__osCurrentHandle[2];
#endif

s32 osEPiRawStartDma(OSPiHandle *pihandle, s32 dir, u32 devAddr, void *dram_addr, u32 size) {
#ifdef VERSION_SH
    u32 status;
    u32 domain;
#else
    register u32 status;
#endif

#ifdef VERSION_SH
    EPI_SYNC(pihandle, status, domain);
#else
    WAIT_ON_IO_BUSY(status);
#endif

    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram_addr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS(pihandle->baseAddress | devAddr));

    switch (dir) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
    }
    return 0;
}
