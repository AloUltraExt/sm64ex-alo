#include "PR/os_internal.h"
#include "PR/rdb.h"
#include "piint.h"
#include "macros.h"

ALIGNED8 OSThread piThread;
ALIGNED16 u8 piMgrStack[OS_PIM_STACKSIZE];
ALIGNED8 OSMesgQueue piEventQueue;
OSMesg piEventBuf[1];

OSDevMgr __osPiDevMgr = { 0 };
#if LIBULTRA_VERSION >= OS_VER_F
OSPiHandle *__osPiTable = NULL;
#endif
#if LIBULTRA_VERSION >= OS_VER_H
OSPiHandle *__osCurrentHandle[2] = { &__Dom1SpeedParam, &__Dom2SpeedParam };
#endif

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 saveMask;
    OSPri oldPri;
    OSPri newPri;

    if (__osPiDevMgr.active) {
        return;
    }

    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&piEventQueue, (OSMesg*) piEventBuf, 1);
    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }

    osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg) 0x22222222);
    oldPri = -1;
    newPri = osGetThreadPri(NULL);

    if (newPri < pri) {
        oldPri = newPri;
        osSetThreadPri(NULL, pri);
    }

    saveMask = __osDisableInt();
    __osPiDevMgr.active = TRUE;
    __osPiDevMgr.thread = &piThread;
    __osPiDevMgr.cmdQueue = cmdQ;
    __osPiDevMgr.evtQueue = &piEventQueue;
    __osPiDevMgr.acsQueue = &__osPiAccessQueue;
    __osPiDevMgr.dma = osPiRawStartDma;
#if LIBULTRA_VERSION >= OS_VER_F
    __osPiDevMgr.edma = osEPiRawStartDma;
#endif
    osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piMgrStack[OS_PIM_STACKSIZE], pri);
    osStartThread(&piThread);

    __osRestoreInt(saveMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}
