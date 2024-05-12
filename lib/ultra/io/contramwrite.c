#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#ifdef BBPLAYER
s32 __osContRamWrite(UNUSED OSMesgQueue *mq, int channel, u16 address, u8 *buffer, s32 force) {
    s32 ret = 0;

    if ((force != TRUE) && (address < PFS_LABEL_AREA) && (address != 0)) {
        return 0;
    }

    __osSiGetAccess();

    if (__osBbPakAddress[channel] != 0) {
        if (__osBbPakSize - 0x20 >= address * 0x20) {
            int i = 0;

            for (i = 0; i < 0x20; i++) {
                (__osBbPakAddress[channel] + address * 0x20)[i] = buffer[i];
            }
        }
    } else {
        ret = 1;
    }

    __osSiRelAccess();
    return ret;
}
#else

#if LIBULTRA_VERSION >= OS_VER_J
s32 __osContRamWrite(OSMesgQueue* mq, int channel, u16 address, u8* buffer, int force) {
    s32 ret = 0;
    s32 i;
    u8* ptr;
    s32 retry = 2;
    u8 crc;

    if ((force != TRUE) && (address < PFS_LABEL_AREA) && (address != 0)) {
        return 0;
    }

    __osSiGetAccess();

    do {
        ptr = (u8 *) __osPfsPifRam.ramarray;

        if (__osContLastCmd != CONT_CMD_WRITE_PAK || __osPfsLastChannel != channel) {
            __osContLastCmd = CONT_CMD_WRITE_PAK;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) {
                *ptr++ = CONT_CMD_REQUEST_STATUS;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READFORMAT(ptr)->dummy = CONT_CMD_NOP;
            READFORMAT(ptr)->txsize = CONT_CMD_WRITE_PAK_TX;
            READFORMAT(ptr)->rxsize = CONT_CMD_WRITE_PAK_RX;
            READFORMAT(ptr)->cmd = CONT_CMD_WRITE_PAK;
            READFORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        CONT_READFORMAT_ADDR(READFORMAT(ptr), address);

        bcopy(buffer, READFORMAT(ptr)->data, BLOCKSIZE);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        crc = __osContDataCrc(buffer);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READFORMAT(ptr));

        if (!ret) {
            if (crc != READFORMAT(ptr)->datacrc) {
                if ((ret = __osPfsGetStatus(mq, channel))) {
                    break;
                } else {
                    ret = PFS_ERR_CONTRFAIL;
                }
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && (retry-- >= 0));

    __osSiRelAccess();

    return ret;
}
#else
extern s32 __osPfsGetStatus(OSMesgQueue *, s32);
void __osPackRamWriteData(s32 channel, u16 address, u8 *buffer);

s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, s32 force) {
    s32 ret = 0;
    s32 i;
    u8* ptr = (u8*)&__osPfsPifRam;
    __OSContRamReadFormat ramreadformat;
    s32 retry = 2;

    if (force != TRUE && address < PFS_LABEL_AREA && address != 0) {
        return 0;
    }
    __osSiGetAccess();
    __osContLastCmd = CONT_CMD_WRITE_PAK;
    __osPackRamWriteData(channel, address, buffer);
    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    do {
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ptr = (u8 *)&__osPfsPifRam;

        if (channel != 0) {
            for (i = 0; i < channel; i++) {
                ptr++;
            }
        }

        ramreadformat = *READFORMAT(ptr);

        ret = CHNL_ERR(ramreadformat);
        if (ret == 0) {
            if (__osContDataCrc(buffer) != ramreadformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);

                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }

                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && retry-- >= 0);

    __osSiRelAccess();
    return ret;
}

void __osPackRamWriteData(int channel, u16 address, u8 *buffer) {
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *) __osPfsPifRam.ramarray;

    CONT_PIFRAM_SET(__osPfsPifRam, 0, CONT_CMD_EXE);

    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_WRITE_PAK_TX;
    ramreadformat.rxsize = CONT_CMD_WRITE_PAK_RX;
    ramreadformat.cmd = CONT_CMD_WRITE_PAK;
    CONT_READFORMAT_ADDR(ramreadformat, address);
    ramreadformat.datacrc = CONT_CMD_NOP;
    for (i = 0; i < ARRAY_COUNT(ramreadformat.data); i++) {
        ramreadformat.data[i] = *buffer++;
    }

    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }

    *READFORMAT(ptr) = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}
#endif

#endif
