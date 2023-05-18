#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#if LIBULTRA_VERSION > OS_VER_D
#define CONT_CMD_REQ CONT_CMD_REQUEST_STATUS
#else
#define CONT_CMD_REQ CONT_CMD_RESET
#endif

u32 _osContInitialized = 0;

ALIGNED16 OSPifRam __osContPifRam;
u8 __osContLastCmd;
u8 __osMaxControllers;

OSTimer __osEepromTimer;
ALIGNED8 OSMesgQueue __osEepromTimerQ;
OSMesg __osEepromTimerMsg;

s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSMesg dummy;
    u32 ret = 0;
    OSTime t;
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;

    if (_osContInitialized) {
        return 0;
    }
    _osContInitialized = 1;

    t = osGetTime();
    if (t < OS_USEC_TO_CYCLES(500000)) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, OS_USEC_TO_CYCLES(500000) - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }

    __osMaxControllers = MAXCONTROLLERS;

    __osPackRequestData(CONT_CMD_REQ);

    ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

    __osContGetInitData(bitpattern, data);
#ifdef BBPLAYER
    __osContLastCmd = CONT_CMD_CHANNEL_RESET;
#else
    __osContLastCmd = CONT_CMD_REQ;
#endif
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&__osEepromTimerQ, &__osEepromTimerMsg, 1);

    return ret;
}

void __osContGetInitData(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat response;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8 *) __osContPifRam.ramarray;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(response), data++) {
        response = *REQFORMAT(ptr);
        data->errnum = CHNL_ERR(response);
        if (data->errnum == 0) {
            data->type = response.typel << 8 | response.typeh;
#ifdef BBPLAYER
            data->status = __osBbPakAddress[i] != NULL;
#else
            data->status = response.status;
#endif

            bits |= 1 << i;
        }
    }
#ifdef BBPLAYER
    if (__osBbIsBb && __osBbHackFlags != 0) {
        OSContStatus tmp;
        bits = (bits & ~((1 << __osBbHackFlags) | 1)) |
                ((bits & 1) << __osBbHackFlags) |
                ((bits & (1 << __osBbHackFlags)) >> __osBbHackFlags);
        data -= __osMaxControllers;
        tmp = *data;
        *data = data[__osBbHackFlags];
        data[__osBbHackFlags] = tmp;
    }
#endif

    *pattern = bits;
}

void __osPackRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestHeader;
    s32 i;

    CONT_PIFRAM_SET(__osContPifRam, 0, CONT_CMD_EXE);

    ptr = (u8 *) __osContPifRam.ramarray;
    requestHeader.dummy = CONT_CMD_NOP;
    requestHeader.txsize = CONT_CMD_RESET_TX;
    requestHeader.rxsize = CONT_CMD_RESET_RX;
    requestHeader.cmd = cmd;
    requestHeader.typeh = CONT_CMD_NOP;
    requestHeader.typel = CONT_CMD_NOP;
    requestHeader.status = CONT_CMD_NOP;
    requestHeader.dummy1 = CONT_CMD_NOP;

    for (i = 0; i < __osMaxControllers; i++) {
        *REQFORMAT(ptr) = requestHeader;
        ptr += sizeof(requestHeader);
    }
    *ptr = CONT_CMD_END;
}
