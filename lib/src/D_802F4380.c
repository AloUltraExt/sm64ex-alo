#include "libultra_internal.h"
#include "piint.h"
#include "PR/rcp.h"
#include "new_func.h"
#include "macros.h"

#if defined(VERSION_EU)
s32 __osLeoInterrupt(void) {
    u32 sp3c;
    u32 sp38;
    u32 sp34;
    __OSTranxInfo *sp30;
    __OSBlockInfo *sp2c;
    u32 sp28;
    UNUSED __OSBlockInfo *sp24;
    if (!osDDActive) {
        return 0;
    }
    sp30 = &__osDiskHandle->transferInfo;
    sp2c = &sp30->block[sp30->blockNum];
    sp38 = IO_READ(PI_STATUS_REG);
    if (sp38 & PI_STATUS_DMA_BUSY) {
        IO_WRITE(PI_STATUS_REG, PI_STATUS_RESET | PI_STATUS_CLR_INTR);
        WAIT_ON_LEO_IO_BUSY(sp38);
        sp3c = IO_READ(LEO_STATUS);
        if (sp3c & LEO_STATUS_MECHANIC_INTERRUPT) {
            WAIT_ON_LEO_IO_BUSY(sp38);
            IO_WRITE(LEO_BM_CTL, sp30->bmCtlShadow | LEO_BM_CTL_CLR_MECHANIC_INTR);
        }
        sp30->errStatus = 75;
        func_802F4A20();
        return 1;
    }
    WAIT_ON_LEO_IO_BUSY(sp38);
    sp3c = IO_READ(LEO_STATUS);
    if (sp3c & LEO_STATUS_MECHANIC_INTERRUPT) {
        WAIT_ON_LEO_IO_BUSY(sp38);
        IO_WRITE(LEO_BM_CTL, sp30->bmCtlShadow | LEO_BM_CTL_CLR_MECHANIC_INTR);
        sp30->errStatus = 0;
        return 0;
    }
    if (sp3c & LEO_STATUS_BUFFER_MANAGER_ERROR) {
        sp30->errStatus = 3;
        func_802F4A20();
        return 1;
    }
    if (sp30->cmdType == 1) {
        if ((sp3c & LEO_STATUS_DATA_REQUEST) == 0) {
            if (sp30->sectorNum + 1 != sp30->transferMode * 85) {
                sp30->errStatus = 6;
                func_802F4A20();
                return 1;
            }
            IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
            __OSGlobalIntMask |= 0x00100401;
            sp30->errStatus = 0;
            func_802F4B08();
            return 1;
        }
        sp2c->dramAddr = (void *) ((u32) sp2c->dramAddr + sp2c->sectorSize);
        sp30->sectorNum++;
        osEPiRawStartDma(__osDiskHandle, 1, 0x05000400, sp2c->dramAddr, sp2c->sectorSize);
        return 1;
    }
    if (sp30->cmdType == 0) {
        if (sp30->transferMode == 3) {
            if ((s32)(sp2c->C1ErrNum + 17) < sp30->sectorNum) {
                sp30->errStatus = 0;
                func_802F4A20();
                return 1;
            }
            if ((sp3c & LEO_STATUS_DATA_REQUEST) == 0) {
                sp30->errStatus = 17;
                func_802F4A20();
                return 1;
            }
        } else {
            sp2c->dramAddr = (void *) ((u32) sp2c->dramAddr + sp2c->sectorSize);
        }
        sp34 = IO_READ(LEO_BM_STATUS);
        if (((LEO_BM_STATUS_C1SINGLE & sp34) && (LEO_BM_STATUS_C1DOUBLE & sp34)) || (sp34 & LEO_BM_STATUS_MICRO)) {
            if (sp2c->C1ErrNum > 3) {
                if (sp30->transferMode != 3 || sp30->sectorNum > 0x52) {
                    sp30->errStatus = 17;
                    func_802F4A20();
                    return 1;
                }
            } else {
                sp28 = sp2c->C1ErrNum;
                sp2c->C1ErrSector[sp28] = sp30->sectorNum + 1;
            }
            sp2c->C1ErrNum++;
        }
        if (sp3c & LEO_STATUS_C2_TRANSFER) {
            if (sp30->sectorNum != 87) {
                sp30->errStatus = 6;
                func_802F4A20();
            }
            if (sp30->transferMode == 2 && sp30->blockNum == 0) {
                sp30->blockNum = 1;
                sp30->sectorNum = -1;
                sp30->block[1].dramAddr =
                    (void *) ((u32) sp30->block[1].dramAddr - sp30->block[1].sectorSize);
            } else {
                IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
                __OSGlobalIntMask |= 0x00100401;
            }
            osEPiRawStartDma(__osDiskHandle, 0, 0x5000000, sp2c->C2Addr, sp2c->sectorSize * 4);
            sp30->errStatus = 0;
            return 1;
        }
        
        if (sp30->sectorNum == -1 && sp30->transferMode == 2 && sp30->blockNum == 1) {
            sp24 = &sp30->block[0];
            if (sp30->block[0].C1ErrNum == 0) {
                if (((u32 *) sp30->block[0].C2Addr)[0] | ((u32 *) sp30->block[0].C2Addr)[1]
                    | ((u32 *) sp30->block[0].C2Addr)[2] | ((u32 *) sp30->block[0].C2Addr)[3]) {
                    sp30->errStatus = 6;
                    func_802F4A20();
                    return 1;
                }
            }
            sp30->errStatus = 0;
            func_802F4B08();
        }
        sp30->sectorNum++;
        if (sp3c & LEO_STATUS_DATA_REQUEST) {
            if (sp30->sectorNum > 0x54) {
                sp30->errStatus = 6;
                func_802F4A20();
                return 1;
            }
            osEPiRawStartDma(__osDiskHandle, 0, 0x05000400, sp2c->dramAddr, sp2c->sectorSize);
            sp30->errStatus = 0;
            return 1;
        }
        if (sp30->sectorNum <= 0x54) {
            sp30->errStatus = 6;
            func_802F4A20();
            return 1;
        }
        return 1;
    }
    sp30->errStatus = 75;
    func_802F4A20();
    return 1;
}
#endif
