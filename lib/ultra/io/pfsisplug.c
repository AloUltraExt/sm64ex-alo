#include "PR/os_pi.h"
#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"

ALIGNED16 OSPifRam __osPfsPifRam;

s32 osPfsIsPlug(OSMesgQueue *mq, u8 *pattern) {
    s32 ret = 0;
    OSMesg dummy;
    u8 bitpattern;
    OSContStatus contData[MAXCONTROLLERS];
    int channel;
    u8 bits = 0;
    int crcErrorCount = 3;

    __osSiGetAccess();

    do {
        __osPfsRequestData(CONT_CMD_REQUEST_STATUS);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

        __osPfsGetInitData(&bitpattern, contData);
        for (channel = 0; channel < __osMaxControllers; channel++) {
            if ((contData[channel].status & CONT_ADDR_CRC_ER) == 0) {
                crcErrorCount--;
                break;
            }
        }

        if (__osMaxControllers == channel) {
            crcErrorCount = 0;
        }
    } while (crcErrorCount > 0);

    for (channel = 0; channel < __osMaxControllers; channel++) {
        if ((contData[channel].errnum == 0) && ((contData[channel].status & CONT_CARD_ON) != 0)) {
            bits |= 1 << channel;
        }
    }
    __osSiRelAccess();
    *pattern = bits;
    return ret;
}

void __osPfsRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;

#if LIBULTRA_VERSION > OS_VER_H
    ptr = (u8 *)&__osPfsPifRam;
#endif
    __osContLastCmd = cmd;
#if LIBULTRA_VERSION < OS_VER_I
    CONT_PIFRAM_SET(__osPfsPifRam, 0, CONT_CMD_EXE);
#else
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
#endif
#if LIBULTRA_VERSION < OS_VER_I
    ptr = (u8 *)&__osPfsPifRam;
#endif

    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;

    for (i = 0; i < __osMaxControllers; i++) {
        *REQFORMAT(ptr) = requestformat;
        ptr += sizeof(requestformat);
    }

    *ptr = CONT_CMD_END;
}

void __osPfsGetInitData(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits = 0;

    ptr = (u8 *)&__osPfsPifRam;

    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *REQFORMAT(ptr);
        data->errnum = CHNL_ERR(requestformat);

        if (data->errnum != 0) {
            continue;
        }

        data->type = (requestformat.typel << 8) | (requestformat.typeh);
        data->status = requestformat.status;
        bits |= 1 << i;
    }
    *pattern = bits;
}
