#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/R4300.h"
#include "piint.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

s32 osEPiRawStartDma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size) {
#ifdef BBPLAYER
    u64 dummyBuf[2];
    u32 stat;
    u32 domain;
    u32 buffer;
    u32 pgsize;
    u16 *adr;
    u32 i;
#elif LIBULTRA_VERSION >= OS_VER_H
    u32 stat;
    u32 domain;
#else
    register u32 stat;
#endif

#if LIBULTRA_VERSION >= OS_VER_H
    EPI_SYNC(pihandle, stat, domain);
#else
    WAIT_ON_IO_BUSY(stat);
#endif

#ifdef BBPLAYER
    if (direction == OS_READ) {
        pgsize = 1;

        for (i = 1; i <= (u32) (pihandle->pageSize + 2); i++) {
            pgsize *= 2;
        }

        if ((devAddr & (pgsize - 1)) == pgsize - 2) {
            osEPiRawReadIo(pihandle, devAddr - 2, &buffer);

            adr = (u16 *) PHYS_TO_K1(dramAddr);
            *(adr++) = (u16) buffer;

            devAddr += 2;
            dramAddr = adr;
            size -= 2;

            if (size >= 4) {
                osEPiRawReadIo(pihandle, devAddr, &buffer);

                adr = (u16 *) dramAddr;
                *(adr++) = buffer >> 16;
                *(adr++) = (u16) buffer;

                devAddr += 4;
                dramAddr = adr;
                size -= 4;

                if (size != 0) {
                    osEPiRawReadIo(pihandle, devAddr, &buffer);

                    adr = (u16 *) PHYS_TO_K1(dramAddr);
                    *(adr++) = buffer >> 16;

                    devAddr += 2;
                    dramAddr = adr;
                    size -= 2;
                }
            }
        }

        if ((((devAddr + size) & (pgsize - 1)) == 2) | (size == 2)) {
            if ((devAddr + size) & 2) {
                osEPiRawReadIo(pihandle, devAddr + size - 2, &buffer);
                adr = (u16 *) PHYS_TO_K1(dramAddr) + (size - 2) / 2;
                *adr = buffer >> 16;
            } else {
                osEPiRawReadIo(pihandle, devAddr + size - 4, &buffer);
                adr = (u16 *) PHYS_TO_K1(dramAddr) + (size - 2) / 2;
                *adr = (u16) buffer;
            }
            size -= 2;
        }

        if (size == 0) {
            size = 8;
            dramAddr = dummyBuf;
            devAddr = 0;
        }
    }
#endif

    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS(pihandle->baseAddress | devAddr));

#ifdef BBPLAYER
    if ((u32) direction >= 2U) {
        return -1;
    }

    if ((pihandle->baseAddress | devAddr) <= 0x400) {
        IO_WRITE(direction == OS_READ ? PI_5C_REG : PI_58_REG, size - 1);
    } else {
        IO_WRITE(direction == OS_READ ? PI_WR_LEN_REG : PI_RD_LEN_REG, size - 1);
    }
#else
    switch (direction) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
    }
#endif
    return 0;
}
