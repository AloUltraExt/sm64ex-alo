#include "PR/os_internal.h"
#include "piint.h"
#include "macros.h"

#if LIBULTRA_VERSION > OS_VER_D
#include "PR/rcp.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

void __osDevMgrMain(void *args) {
    OSIoMesg *mb;
    OSMesg em;
    OSMesg dummy;
    s32 ret;
    OSDevMgr *dm = (OSDevMgr *) args;
#if LIBULTRA_VERSION == OS_VER_F
    UNUSED u32 sm = 0;
#endif
    u32 messageSend = 0;
#ifdef BBPLAYER
    s32 check = FALSE;
#endif

    mb = NULL;
    ret = 0;

    while (TRUE) {
        osRecvMesg(dm->cmdQueue, (OSMesg) &mb, OS_MESG_BLOCK);

        if (mb->piHandle != NULL &&
            mb->piHandle->type == DEVICE_TYPE_64DD &&
            (mb->piHandle->transferInfo.cmdType == LEO_CMD_TYPE_0 ||
             mb->piHandle->transferInfo.cmdType == LEO_CMD_TYPE_1)) {
            __OSBlockInfo *blockInfo;
            __OSTranxInfo *info;
            info = &mb->piHandle->transferInfo;
            blockInfo = &info->block[info->blockNum];
            info->sectorNum = -1;

            if (info->transferMode != LEO_SECTOR_MODE) {
                blockInfo->dramAddr = (void *) ((u32) blockInfo->dramAddr - blockInfo->sectorSize);
            }

            if (info->transferMode == LEO_TRACK_MODE && mb->piHandle->transferInfo.cmdType == LEO_CMD_TYPE_0) {
                messageSend = 1;
            } else {
                messageSend = 0;
            }

            osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
            __osResetGlobalIntMask(OS_IM_PI);
            osEPiRawWriteIo(mb->piHandle, LEO_BM_CTL, (info->bmCtlShadow | 0x80000000));

readblock1:
            osRecvMesg(dm->evtQueue, &em, OS_MESG_BLOCK);
#if LIBULTRA_VERSION >= OS_VER_H
            info = &mb->piHandle->transferInfo;
            blockInfo = &info->block[info->blockNum];

            if (blockInfo->errStatus == LEO_ERROR_29) {
                u32 stat;
                osEPiRawWriteIo(mb->piHandle, LEO_BM_CTL, info->bmCtlShadow | LEO_BM_CTL_RESET);
                osEPiRawWriteIo(mb->piHandle, LEO_BM_CTL, info->bmCtlShadow);
                osEPiRawReadIo(mb->piHandle, LEO_STATUS, &stat);

                if (stat & LEO_STATUS_MECHANIC_INTERRUPT) {
                    osEPiRawWriteIo(mb->piHandle, LEO_BM_CTL, info->bmCtlShadow | LEO_BM_CTL_CLR_MECHANIC_INTR);
                }

                blockInfo->errStatus = LEO_ERROR_4;
                IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
                __osSetGlobalIntMask(OS_IM_PI | SR_IBIT4);
            }

            osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);

            if (messageSend == 1 && mb->piHandle->transferInfo.block[0].errStatus == LEO_ERROR_GOOD) {
                messageSend = 0;
                goto readblock1;
            }
#else
            sm = osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);

            if (messageSend == 1 && mb->piHandle->transferInfo.errStatus == LEO_ERROR_GOOD) {
                messageSend = 0;
                goto readblock1;
            }
#endif
            osSendMesg(dm->acsQueue, NULL, OS_MESG_NOBLOCK);

            if (mb->piHandle->transferInfo.blockNum == 1) {
                osYieldThread();
            }
        } else {
            switch (mb->hdr.type) {
                case OS_MESG_TYPE_DMAREAD:
                    osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
#ifdef BBPLAYER
                    if (__osBbIsBb == TRUE && ((uintptr_t) mb->dramAddr & 0x7f) >= 0x60) {
                        check = TRUE;
                        ret = dm->dma(OS_READ, mb->devAddr, (void *) 0x80600000, mb->size);
                        break;
                    }
#endif
                    ret = dm->dma(OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                    break;
                case OS_MESG_TYPE_DMAWRITE:
                    osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                    ret = dm->dma(OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
                    break;
                case OS_MESG_TYPE_EDMAREAD:
                    osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
#ifdef BBPLAYER
                    if (__osBbIsBb == TRUE && ((uintptr_t) mb->dramAddr & 0x7f) >= 0x60) {
                        check = TRUE;
                        ret = dm->edma(mb->piHandle, OS_READ, mb->devAddr, (void *) 0x80600000, mb->size);
                        break;
                    }
#endif
                    ret = dm->edma(mb->piHandle, OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                    break;
                case OS_MESG_TYPE_EDMAWRITE:
                    osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                    ret = dm->edma(mb->piHandle, OS_WRITE, mb->devAddr, mb->dramAddr,
                                           mb->size);
                    break;
                case OS_MESG_TYPE_LOOPBACK:
                    osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
                    ret = -1;
                    break;
                    break;
                default:
                    ret = -1;
                    break;
            }

            if (ret == 0) {
                osRecvMesg(dm->evtQueue, &em, OS_MESG_BLOCK);
#ifdef BBPLAYER
                if (__osBbIsBb == TRUE && check) {
                    osInvalDCache((void *) 0x80600000, (mb->size + DCACHE_LINEMASK) & ~DCACHE_LINEMASK);
                    bcopy((void *) 0x80600000, mb->dramAddr, mb->size);
                    check = FALSE;
                    osWritebackDCache(mb->dramAddr, mb->size);
                }
#endif
#if LIBULTRA_VERSION == OS_VER_F
                sm =
#endif
                osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
                osSendMesg(dm->acsQueue, NULL, OS_MESG_NOBLOCK);
            }
        }
    }
}
#else
void __osDevMgrMain(void *args) {
    OSIoMesg *mb;
    OSMesg em;
    OSMesg messageSend;
    s32 ret;
    OSDevMgr *dm = (OSDevMgr *) args;

    mb = NULL;
    ret = 0;

    while (TRUE) {
        osRecvMesg(dm->cmdQueue, (OSMesg) &mb, OS_MESG_BLOCK);

        switch (mb->hdr.type) {
            case OS_MESG_TYPE_DMAREAD:
                osRecvMesg(dm->acsQueue, &messageSend, OS_MESG_BLOCK);
                ret = dm->dma(OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_DMAWRITE:
                osRecvMesg(dm->acsQueue, &messageSend, OS_MESG_BLOCK);
                ret = dm->dma(OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_LOOPBACK:
                osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
                ret = -1;
                break;
            default:
                ret = -1;
                break;
        }

        if (ret == 0) {
            osRecvMesg(dm->evtQueue, &em, OS_MESG_BLOCK);
            osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
            osSendMesg(dm->acsQueue, NULL, OS_MESG_NOBLOCK);
        }
    }
}
#endif
