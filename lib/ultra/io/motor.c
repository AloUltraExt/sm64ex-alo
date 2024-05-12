#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"

#ifdef BBPLAYER

s32 __osMotorAccess(UNUSED OSPfs *pfs, UNUSED s32 action) {
    return PFS_ERR_INVALID;
}

s32 osMotorInit(UNUSED OSMesgQueue *mq, UNUSED OSPfs *pfs, UNUSED int channel) {
    return PFS_ERR_DEVICE;
}

#else

#if LIBULTRA_VERSION >= OS_VER_J
static OSPifRam __MotorDataBuf[MAXCONTROLLERS];
#else
void __osMakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata);
u32 __osMotorinitialized[MAXCONTROLLERS] = { 0, 0, 0, 0 };
OSPifRam _MotorStopData[MAXCONTROLLERS];
OSPifRam _MotorStartData[MAXCONTROLLERS];
ALIGNED8 u8 _motorstopbuf[32];
ALIGNED8 u8 _motorstartbuf[32];
#endif

#if LIBULTRA_VERSION >= OS_VER_J
s32 __osMotorAccess(OSPfs* pfs, s32 flag) {
    int i;
    s32 ret;
    u8* ptr = (u8*)&__MotorDataBuf[pfs->channel];

    if (!(pfs->status & PFS_MOTOR_INITIALIZED)) {
        return 5;
    }

    __osSiGetAccess();
    __MotorDataBuf[pfs->channel].pifstatus = CONT_CMD_EXE;
    ptr += pfs->channel;

    for (i = 0; i < BLOCKSIZE; i++) {
        READFORMAT(ptr)->data[i] = flag;
    }

    __osContLastCmd = CONT_CMD_END;
    __osSiRawStartDma(OS_WRITE, &__MotorDataBuf[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    __osSiRawStartDma(OS_READ, &__MotorDataBuf[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);

    ret = READFORMAT(ptr)->rxsize & CHNL_ERR_MASK;
    if (!ret) {
        if (!flag) {
            if (READFORMAT(ptr)->datacrc != 0) {
                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            if (READFORMAT(ptr)->datacrc != 0xEB) {
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    }

    __osSiRelAccess();

    return ret;
}

#else

s32 osMotorStop(OSPfs *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    ptr = (u8 *) &__osPfsPifRam;

    if (!__osMotorinitialized[pfs->channel]) {
        return PFS_ERR_INVALID;
    }

    __osSiGetAccess();

    __osContLastCmd = CONT_CMD_WRITE_PAK;
    __osSiRawStartDma(OS_WRITE, &_MotorStopData[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ptr = (u8 *) &__osPfsPifRam;

    if (pfs->channel != 0) {
        for (i = 0; i < pfs->channel; i++) {
            ptr++;
        }
    }

    ramreadformat = *READFORMAT(ptr);
    ret = CHNL_ERR(ramreadformat);
    if (ret == 0 && ramreadformat.datacrc != __osContDataCrc((u8 *) &_motorstopbuf)) {
        ret = PFS_ERR_CONTRFAIL;
    }

    __osSiRelAccess();
    return ret;
}

s32 osMotorStart(OSPfs *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    ptr = (u8 *) &__osPfsPifRam;

    if (!__osMotorinitialized[pfs->channel]) {
        return PFS_ERR_INVALID;
    }

    __osSiGetAccess();

    __osContLastCmd = CONT_CMD_WRITE_PAK;
    __osSiRawStartDma(OS_WRITE, &_MotorStartData[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ptr = (u8 *) &__osPfsPifRam;

    if (pfs->channel != 0) {
        for (i = 0; i < pfs->channel; i++) {
            ptr++;
        }
    }

    ramreadformat = *READFORMAT(ptr);
    ret = CHNL_ERR(ramreadformat);
    if (ret == 0 && ramreadformat.datacrc != __osContDataCrc((u8 *) &_motorstartbuf)) {
        ret = PFS_ERR_CONTRFAIL;
    }
    __osSiRelAccess();
    return ret;
}
#endif

#if LIBULTRA_VERSION >= OS_VER_J
void __osMakeMotorData(int channel, OSPifRam* mdata)
#else // _MakeMotorData
void __osMakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata)
#endif
{
    u8 *ptr = (u8 *) mdata->ramarray;
    __OSContRamReadFormat ramreadformat;
    int i;

#if LIBULTRA_VERSION < OS_VER_J
    for (i = 0; i < ARRAY_COUNT(mdata->ramarray); i++) {
        mdata->ramarray[i] = 0;
    }
    mdata->pifstatus = CONT_CMD_EXE;
#endif

    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_WRITE_PAK_TX;
    ramreadformat.rxsize = CONT_CMD_WRITE_PAK_RX;
    ramreadformat.cmd = CONT_CMD_WRITE_PAK;

#if LIBULTRA_VERSION >= OS_VER_J
    ramreadformat.addrh = CONT_BLOCK_RUMBLE >> 3;
    ramreadformat.addrl = (u8)(__osContAddressCrc(CONT_BLOCK_RUMBLE) | (CONT_BLOCK_RUMBLE << 5));
#else
    ramreadformat.address = (address << 0x5) | __osContAddressCrc(address);
    ramreadformat.datacrc = CONT_CMD_NOP;

    for (i = 0; i < ARRAY_COUNT(ramreadformat.data); i++) {
        ramreadformat.data[i] = *buffer++;
    }
#endif

    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }

    *READFORMAT(ptr) = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}

s32 osMotorInit(OSMesgQueue *mq, OSPfs *pfs, int channel) {
#if LIBULTRA_VERSION < OS_VER_J
    int i;
#endif
    s32 ret;
    u8 temp[32];

    pfs->queue = mq;
    pfs->channel = channel;
#if LIBULTRA_VERSION >= OS_VER_J
    pfs->activebank = 0xFF;
    pfs->status = 0;

    ret = SELECT_BANK(pfs, 0xFE);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = SELECT_BANK(pfs, 0x80);
    }
#else
    pfs->status = 0;
    pfs->activebank = 0x80;

    for (i = 0; i < ARRAY_COUNT(temp); i++) {
        temp[i] = 254;
    }

    ret = __osContRamWrite(mq, channel, CONT_BLOCK_DETECT, temp, FALSE);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = __osContRamWrite(mq, channel, CONT_BLOCK_DETECT, temp, FALSE);
    }
#endif

    if (ret != 0) {
        return ret;
    }

    ret = __osContRamRead(mq, channel, CONT_BLOCK_DETECT, temp);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }

    if (ret != 0) {
        return ret;
    }

    if (temp[31] == 254) {
        return PFS_ERR_DEVICE;
    }

#if LIBULTRA_VERSION >= OS_VER_J
    ret = __osPfsSelectBank(pfs, 0x80);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }
#else
    for (i = 0; i < ARRAY_COUNT(temp); i++) {
        temp[i] = 128;
    }

    ret = __osContRamWrite(mq, channel, CONT_BLOCK_DETECT, temp, FALSE);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = __osContRamWrite(mq, channel, CONT_BLOCK_DETECT, temp, FALSE);
    }

    if (ret != 0) {
        return ret;
    }
#endif
    ret = __osContRamRead(mq, channel, CONT_BLOCK_DETECT, temp);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }

    if (ret != 0) {
        return ret;
    }

    if (temp[31] != 0x80) {
        return PFS_ERR_DEVICE;
    }

#if LIBULTRA_VERSION >= OS_VER_J
    if (!(pfs->status & PFS_MOTOR_INITIALIZED)) {
        __osMakeMotorData(channel, &__MotorDataBuf[channel]);
    }

    pfs->status = PFS_MOTOR_INITIALIZED;
#else
    if (!__osMotorinitialized[channel]) {
        for (i = 0; i < ARRAY_COUNT(_motorstartbuf); i++) {
            _motorstartbuf[i] = 1;
            _motorstopbuf[i] = 0;
        }
        __osMakeMotorData(channel, CONT_BLOCK_RUMBLE, _motorstartbuf, &_MotorStartData[channel]);
        __osMakeMotorData(channel, CONT_BLOCK_RUMBLE, _motorstopbuf, &_MotorStopData[channel]);
        __osMotorinitialized[channel] = TRUE;
    }
#endif

    return 0;
}

#endif
