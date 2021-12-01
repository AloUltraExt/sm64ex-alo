#include "libultra_internal.h"
#include "PR/rcp.h"

s32 __osSiRawStartDma(s32 dir, void *addr) {
    if (__osSiDeviceBusy()) {
        return -1;
    }

    if (dir == OS_WRITE) {
        osWritebackDCache(addr, 64);
    }

    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(addr));

    if (dir == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, 0x1FC007C0);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, 0x1FC007C0);
    }

    if (dir == OS_READ) {
        osInvalDCache(addr, 64);
    }
    return 0;
}
