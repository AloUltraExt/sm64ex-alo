#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#ifdef BBPLAYER
s32 __osContRamRead(UNUSED OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret;

    __osSiGetAccess();

    ret = 0;
    if (__osBbPakAddress[channel] != 0) {
        if (__osBbPakSize - 0x20 >= address * 0x20) {
            int i;

            for (i = 0; i < 0x20; i++) {
                buffer[i] = (__osBbPakAddress[channel] + address * 0x20)[i];
            }
        }
    } else {
        ret = 1;
    }

    __osSiRelAccess();

    return ret;
}
#else

#if LIBULTRA_VERSION > OS_VER_I
s32 __osPfsLastChannel = -1;

s32 __osContRamRead(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret;
    s32 i;
    u8* ptr;
    s32 retry = 2;

    __osSiGetAccess();

    do {
        ptr = (u8*)&__osPfsPifRam;

        if (__osContLastCmd != CONT_CMD_READ_PAK || __osPfsLastChannel != channel) {
            __osContLastCmd = CONT_CMD_READ_PAK;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) {
                *ptr++ = CONT_CMD_REQUEST_STATUS;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READFORMAT(ptr)->dummy = CONT_CMD_NOP;
            READFORMAT(ptr)->txsize = CONT_CMD_READ_PAK_TX;
            READFORMAT(ptr)->rxsize = CONT_CMD_READ_PAK_RX;
            READFORMAT(ptr)->cmd = CONT_CMD_READ_PAK;
            READFORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

        CONT_READFORMAT_ADDR(READFORMAT(ptr), address);

        __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READFORMAT(ptr));

        if (!ret) {
            if (__osContDataCrc(READFORMAT(ptr)->data) != READFORMAT(ptr)->datacrc) {
                ret = __osPfsGetStatus(mq, channel);

                if (ret) {
                    break;
                }

                ret = PFS_ERR_CONTRFAIL;
            } else {
                bcopy(&READFORMAT(ptr)->data, buffer, BLOCKSIZE);
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
        if (ret != PFS_ERR_CONTRFAIL) {
            break;
        }
    } while (0 <= retry--);
    __osSiRelAccess();

    return ret;
}
#else
void __osPackRamReadData(int channel, u16 address);

s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address, u8 *buffer) {
    s32 ret;
    int i;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int retry;
    ret = 0;
    ptr = (u8 *)&__osPfsPifRam;
    retry = 2;

    __osSiGetAccess();

    __osContLastCmd = CONT_CMD_READ_PAK;
    __osPackRamReadData(channel, address);

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
            u8 c;
            c = __osContDataCrc((u8*)&ramreadformat.data);
            if (c != ramreadformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }
                ret = PFS_ERR_CONTRFAIL;
            } else {
                for (i = 0; i < ARRAY_COUNT(ramreadformat.data); i++) {
                    *buffer++ = ramreadformat.data[i];
                }
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
        if (ret != PFS_ERR_CONTRFAIL) {
            break;
        }
    } while (retry-- >= 0);

    __osSiRelAccess();
    return ret;
}

void __osPackRamReadData(int channel, u16 address) {
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *)__osPfsPifRam.ramarray;

    CONT_PIFRAM_SET(__osPfsPifRam, 0, CONT_CMD_EXE);

    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_READ_PAK_TX;
    ramreadformat.rxsize = CONT_CMD_READ_PAK_RX;
    ramreadformat.cmd = CONT_CMD_READ_PAK;
    CONT_READFORMAT_ADDR(ramreadformat, address);
    ramreadformat.datacrc = CONT_CMD_NOP;
    for (i = 0; i < ARRAY_COUNT(ramreadformat.data); i++) {
        ramreadformat.data[i] = CONT_CMD_NOP;
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
