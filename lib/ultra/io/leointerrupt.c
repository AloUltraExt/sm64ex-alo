#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "../os/osint.h"
#include "piint.h"
#include "macros.h"

extern u32 __osLeoPresent;
static void __osLeoResume(void);
static void __osLeoAbnormalResume(void);

u8 leoDiskStack[OS_LEO_STACKSIZE];

s32 __osLeoInterrupt(void) {
    u32 stat;
#if LIBULTRA_VERSION == OS_VER_F
    u32 pistat;
#else
    volatile u32 pistat;
#endif
    u32 bmstat;
    __OSTranxInfo *info;
    __OSBlockInfo *blockInfo;

#if LIBULTRA_VERSION == OS_VER_F
    if (!__osLeoPresent) {
        return 0;
    }
#else
    stat = 0;
#endif

    info = &__osDiskHandle->transferInfo;
    blockInfo = &info->block[info->blockNum];

    pistat = IO_READ(PI_STATUS_REG);
    if (pistat & PI_STATUS_DMA_BUSY) {
#if LIBULTRA_VERSION == OS_VER_F
        IO_WRITE(PI_STATUS_REG, PI_STATUS_RESET | PI_STATUS_CLR_INTR);
        WAIT_ON_LEO_IO_BUSY(pistat);
        stat = IO_READ(LEO_STATUS);
        if (stat & LEO_STATUS_MECHANIC_INTERRUPT) {
            WAIT_ON_LEO_IO_BUSY(pistat);
            IO_WRITE(LEO_BM_CTL, info->bmCtlShadow | LEO_BM_CTL_CLR_MECHANIC_INTR);
        }
        info->errStatus = LEO_ERROR_75;
        __osLeoAbnormalResume();
#else
        __OSGlobalIntMask = __OSGlobalIntMask & ~SR_IBIT4; //cartridge interrupt
        blockInfo->errStatus = LEO_ERROR_29;
        __osLeoResume();
#endif
        return 1;
    }
    WAIT_ON_LEO_IO_BUSY(pistat);

    stat = IO_READ(LEO_STATUS);
    if (stat & LEO_STATUS_MECHANIC_INTERRUPT) {
        WAIT_ON_LEO_IO_BUSY(pistat);
        IO_WRITE(LEO_BM_CTL, info->bmCtlShadow | LEO_BM_CTL_CLR_MECHANIC_INTR);
#if LIBULTRA_VERSION == OS_VER_F
        info->errStatus = LEO_ERROR_GOOD;
#else
        blockInfo->errStatus = LEO_ERROR_GOOD;
#endif
        return 0;
    }

#if LIBULTRA_VERSION > OS_VER_F
    if (info->cmdType == LEO_CMD_TYPE_2) {
        return 1;
    }
#endif

    if (stat & LEO_STATUS_BUFFER_MANAGER_ERROR) {
#if LIBULTRA_VERSION == OS_VER_F
        info->errStatus = LEO_ERROR_3;
        __osLeoAbnormalResume();
#else
        WAIT_ON_LEO_IO_BUSY(pistat);
        stat = IO_READ(LEO_STATUS);
        blockInfo->errStatus = LEO_ERROR_22;
        __osLeoResume();
        IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
        __OSGlobalIntMask |= OS_IM_PI;
#endif
        return 1;
    }

    if (info->cmdType == LEO_CMD_TYPE_1) {
        if ((stat & LEO_STATUS_DATA_REQUEST) == 0) {
            if (info->sectorNum + 1 != info->transferMode * 85) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_6;
#else
                blockInfo->errStatus = LEO_ERROR_24;
#endif
                __osLeoAbnormalResume();
                return 1;
            }
            IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
            __OSGlobalIntMask |= OS_IM_PI;
#if LIBULTRA_VERSION == OS_VER_F
            info->errStatus = LEO_ERROR_GOOD;
#else
            blockInfo->errStatus = LEO_ERROR_GOOD;
#endif
            __osLeoResume();
            return 1;
        }

        blockInfo->dramAddr = (void *) ((u32)blockInfo->dramAddr + blockInfo->sectorSize);
        info->sectorNum++;
        osEPiRawStartDma(__osDiskHandle, OS_WRITE, LEO_SECTOR_BUFF, blockInfo->dramAddr, blockInfo->sectorSize);
        return 1;
    }

    if (info->cmdType == LEO_CMD_TYPE_0) {
        if (info->transferMode == LEO_SECTOR_MODE) {
            if ((s32)blockInfo->C1ErrNum + 17 < info->sectorNum) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_GOOD;
#else
                blockInfo->errStatus = LEO_ERROR_GOOD;
#endif
                __osLeoAbnormalResume();
                return 1;
            }
            if ((stat & LEO_STATUS_DATA_REQUEST) == 0) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_17;
#else
                blockInfo->errStatus = LEO_ERROR_23;
#endif
                __osLeoAbnormalResume();
                return 1;
            }
        } else {
            blockInfo->dramAddr = (void *)((u32)blockInfo->dramAddr + blockInfo->sectorSize);
        }
        bmstat = IO_READ(LEO_BM_STATUS);
        if ((bmstat & LEO_BM_STATUS_C1SINGLE && bmstat & LEO_BM_STATUS_C1DOUBLE) || bmstat & LEO_BM_STATUS_MICRO) {
            if (blockInfo->C1ErrNum > 3) {
                if (info->transferMode != LEO_SECTOR_MODE || info->sectorNum > 0x52) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_17;
#else
                blockInfo->errStatus = LEO_ERROR_23;
#endif
                    __osLeoAbnormalResume();
                    return 1;
                }
            } else {
                s32 errNum = blockInfo->C1ErrNum;
                blockInfo->C1ErrSector[errNum] = info->sectorNum + 1;
            }
            blockInfo->C1ErrNum++;
        }

        if (stat & LEO_STATUS_C2_TRANSFER) {
            if (info->sectorNum != 87) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_6;
#else
                blockInfo->errStatus = LEO_ERROR_24;
#endif
                __osLeoAbnormalResume();
            }
            if (info->transferMode == LEO_TRACK_MODE && info->blockNum == 0) {
                info->blockNum = 1;
                info->sectorNum = -1;
                info->block[1].dramAddr = (void *)((u32)info->block[1].dramAddr - info->block[1].sectorSize);
#if LIBULTRA_VERSION > OS_VER_F
                blockInfo->errStatus = LEO_ERROR_22;
#endif
            } else {
                IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
                __OSGlobalIntMask |= OS_IM_PI;
#if LIBULTRA_VERSION > OS_VER_F
                info->cmdType = LEO_CMD_TYPE_2;
                blockInfo->errStatus = LEO_ERROR_GOOD;
#endif
            }
            osEPiRawStartDma(__osDiskHandle, OS_READ, LEO_C2_BUFF, blockInfo->C2Addr, blockInfo->sectorSize * 4);
#if LIBULTRA_VERSION == OS_VER_F
            info->errStatus = LEO_ERROR_GOOD;
#endif
            return 1;
        }
        if (info->sectorNum == -1 && info->transferMode == LEO_TRACK_MODE && info->blockNum == 1) {
            __OSBlockInfo *bptr = &info->block[0];
            if (bptr->C1ErrNum == 0) {
                if (((u32 *)bptr->C2Addr)[0] | ((u32 *)bptr->C2Addr)[1] | ((u32 *)bptr->C2Addr)[2] | ((u32 *)bptr->C2Addr)[3]) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_6;
#else
                bptr->errStatus = LEO_ERROR_24;
#endif
                    __osLeoAbnormalResume();
                    return 1;
                }
            }
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_GOOD;
#else
                bptr->errStatus = LEO_ERROR_GOOD;
#endif
            __osLeoResume();
        }
        info->sectorNum++;
        if (stat & LEO_STATUS_DATA_REQUEST) {
            if (info->sectorNum > 0x54) {
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_6;
#else
                blockInfo->errStatus = LEO_ERROR_24;
#endif
                __osLeoAbnormalResume();
                return 1;
            }
            osEPiRawStartDma(__osDiskHandle, 0, LEO_SECTOR_BUFF, blockInfo->dramAddr, blockInfo->sectorSize);
#if LIBULTRA_VERSION == OS_VER_F
                info->errStatus = LEO_ERROR_GOOD;
#else
                blockInfo->errStatus = LEO_ERROR_GOOD;
#endif
            return 1;
        }
        if (info->sectorNum <= 0x54) {
#if LIBULTRA_VERSION == OS_VER_F
            info->errStatus = LEO_ERROR_6;
#else
            blockInfo->errStatus = LEO_ERROR_24;
#endif
            __osLeoAbnormalResume();
            return 1;
        }
        return 1;
    }

#if LIBULTRA_VERSION == OS_VER_F
    info->errStatus = LEO_ERROR_75;
#else
    blockInfo->errStatus = LEO_ERROR_4;
#endif

    __osLeoAbnormalResume();
    return 1;
}

static void __osLeoAbnormalResume(void) {
    __OSTranxInfo *info;
    u32 pistat;
    info = &__osDiskHandle->transferInfo;
    WAIT_ON_LEO_IO_BUSY(pistat);
    IO_WRITE(LEO_BM_CTL, info->bmCtlShadow | LEO_BM_CTL_RESET);
    WAIT_ON_LEO_IO_BUSY(pistat);
    IO_WRITE(LEO_BM_CTL, info->bmCtlShadow);
    __osLeoResume();
    IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
    __OSGlobalIntMask |= OS_IM_PI;
}

static void __osLeoResume(void) {
    __OSEventState *es;
    OSMesgQueue *mq;
    s32 last;
    es = &__osEventStateTab[OS_EVENT_PI];
    mq = es->messageQueue;
    if (mq == NULL || MQ_IS_FULL(mq)) {
        return;
    }
    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = es->message;
    mq->validCount++;
    if (mq->mtqueue->next != NULL) {
        __osEnqueueThread(&__osRunQueue, __osPopThread(&mq->mtqueue));
    }
}
