#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#if LIBULTRA_VERSION > OS_VER_H

#if LIBULTRA_VERSION >= OS_VER_J
void __osPfsRequestOneChannel(int channel, u8 cmd);
#else
void __osPfsRequestOneChannel(int channel);
#endif

void __osPfsGetOneChannelData(int channel, OSContStatus* data);
#endif

#ifdef BBPLAYER
s32 __osPfsGetStatus(UNUSED OSMesgQueue *queue, s32 channel) {
    if (__osBbPakAddress[channel] != 0) {
        return 0;
    }
    return PFS_ERR_NOPACK;
}
#else
s32 __osPfsGetStatus(OSMesgQueue *queue, s32 channel) {
    s32 ret = 0;
    OSMesg dummy;
#if LIBULTRA_VERSION > OS_VER_H
    OSContStatus data;
#define DATA(c) data
#else
    u8 pattern;
    OSContStatus data[MAXCONTROLLERS];
#define DATA(c) data[c]
#endif

#if LIBULTRA_VERSION >= OS_VER_J
    __osPfsRequestOneChannel(channel, CONT_CMD_REQUEST_STATUS);
#elif LIBULTRA_VERSION > OS_VER_H
    __osPfsRequestOneChannel(channel);
#else
    __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
#endif
    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
#if LIBULTRA_VERSION > OS_VER_H
    __osPfsGetOneChannelData(channel, &data);
#else
    __osPfsGetInitData(&pattern, data);
#endif

    if (DATA(channel).status & CONT_CARD_ON && DATA(channel).status & CONT_CARD_PULL) {
        return PFS_ERR_NEW_PACK;
    } else if (DATA(channel).errnum || !(DATA(channel).status & CONT_CARD_ON)) {
        return PFS_ERR_NOPACK;
    } else if (DATA(channel).status & CONT_ADDR_CRC_ER) {
        return PFS_ERR_CONTRFAIL;
    }

    return ret;
}
#endif

#if LIBULTRA_VERSION > OS_VER_H

#if LIBULTRA_VERSION >= OS_VER_J
void __osPfsRequestOneChannel(int channel, u8 cmd)
#else
void __osPfsRequestOneChannel(int channel)
#endif
{
    u8* ptr;
    __OSContRequesFormat requestformat;
    int i;

#if LIBULTRA_VERSION >= OS_VER_J
    __osContLastCmd = CONT_CMD_END;
#else
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
#endif
#if LIBULTRA_VERSION > OS_VER_H
    __osPfsPifRam.pifstatus = CONT_CMD_READ_BUTTON;
#else
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
#endif

    ptr = (u8*)&__osPfsPifRam;

    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
#if LIBULTRA_VERSION >= OS_VER_J
    requestformat.cmd = cmd;
#else
    requestformat.cmd = CONT_CMD_REQUEST_STATUS;
#endif
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;

    for (i = 0; i < channel; i++) {
        *ptr++ = CONT_CMD_REQUEST_STATUS;
    }

    *REQFORMAT(ptr) = requestformat;
    ptr += sizeof(requestformat);
    *ptr = CONT_CMD_END;
}

void __osPfsGetOneChannelData(int channel, OSContStatus* data) {
    u8* ptr = (u8*)&__osPfsPifRam;
    __OSContRequesFormat requestformat;
    int i;

    for (i = 0; i < channel; i++) {
        ptr++;
    }

    requestformat = *REQFORMAT(ptr);
    data->errnum = CHNL_ERR(requestformat);

    if (data->errnum != 0) {
        return;
    }

    data->type = (requestformat.typel << 8) | (requestformat.typeh);
    data->status = requestformat.status;
}
#endif
