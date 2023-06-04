#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "../os/osint.h"

s32 __osSpRawStartDma(s32 dir, u32 devAddr, void *dramAddr, size_t size) {
    if (__osSpDeviceBusy()) {
        return -1;
    }

    IO_WRITE(SP_MEM_ADDR_REG, devAddr);
    IO_WRITE(SP_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));

    if (dir == 0) {
        IO_WRITE(SP_WR_LEN_REG, size - 1);
    } else {
        IO_WRITE(SP_RD_LEN_REG, size - 1);
    }

    return 0;
}
