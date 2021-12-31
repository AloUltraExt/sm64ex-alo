#include "libultra_internal.h"
#include "osContInternal.h"
#include "PR/os.h"
#include "controller.h"

void __osPackRequestData(u8);
void __osContGetInitData(u8 *, OSContStatus *);

u32 _osContInitialized = 0; // probably initialized

// these probably belong in EEPROMlongread or something
u8 __osContLastCmd;
u8 __osMaxControllers;
OSTimer __osEepromTimer;
OSMesgQueue __osEepromTimerQ;
OSMesg __osEepromTimerMsg[4];
s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *status) {
    OSMesg mesg;
    u32 ret = 0;
    OSTime currentTime;
    OSTimer timer;
    OSMesgQueue timerMesgQueue;

    if (_osContInitialized) {
        return 0;
    }
    _osContInitialized = 1;
    currentTime = osGetTime();
    if (500000 * osClockRate / 1000000 > currentTime) {
        osCreateMesgQueue(&timerMesgQueue, &mesg, 1);
        osSetTimer(&timer, 500000 * osClockRate / 1000000 - currentTime, 0, &timerMesgQueue, &mesg);
        osRecvMesg(&timerMesgQueue, &mesg, OS_MESG_BLOCK);
    }
    __osMaxControllers = MAXCONTROLLERS;
#if defined(VERSION_EU) || defined(VERSION_SH)
    __osPackRequestData(0);
#else
    __osPackRequestData(255);
#endif
    ret = __osSiRawStartDma(OS_WRITE, _osContCmdBuf);
    osRecvMesg(mq, &mesg, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, _osContCmdBuf);
    osRecvMesg(mq, &mesg, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, status);
#if defined(VERSION_EU) || defined(VERSION_SH)
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
#else
    __osContLastCmd = CONT_CMD_RESET;
#endif
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&__osEepromTimerQ, __osEepromTimerMsg, 1);
    return ret;
}
void __osContGetInitData(u8 *bitpattern, OSContStatus *status) {
    OSContPackedRequest *cmdBufPtr;
    OSContPackedRequest response;
    s32 i;
    u8 sp7;

    sp7 = 0;
    cmdBufPtr = &(_osContCmdBuf[0].request);
    for (i = 0; i < __osMaxControllers; i++, cmdBufPtr++, status++) {
        response = *(OSContPackedRequest *) cmdBufPtr;
        status->errnum = (response.rxLen & 0xc0) >> 4;
        if (status->errnum == 0) {
            status->type = response.data2 << 8 | response.data1;
            status->status = response.data3;

            sp7 |= 1 << i;
        }
    }
    *bitpattern = sp7;
}
void __osPackRequestData(u8 command) {
    OSContPackedRequest *cmdBufPtr;
    OSContPackedRequest request;
    s32 i;

    // some kind of weird zeroing code
    for (i = 0; i < 0x10; i++) {
        *((u32 *) &_osContCmdBuf + i) = 0;
    }

    _osContPifCtrl = 1;
    cmdBufPtr = &_osContCmdBuf[0].request;
    request.padOrEnd = 255;
    request.txLen = 1;
    request.rxLen = 3;
    request.command = command;
    request.data1 = 255;
    request.data2 = 255;
    request.data3 = 255;
    request.data4 = 255;

    for (i = 0; i < __osMaxControllers; i++) {
        *cmdBufPtr++ = request;
    }
    cmdBufPtr->padOrEnd = 254;
}
