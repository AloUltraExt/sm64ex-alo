#include "libultra_internal.h"
#include "PR/os.h"
#include "piint.h"

#define OS_PI_MGR_MESG_BUFF_SIZE 1

OSDevMgr __osPiDevMgr = { 0 };
#if defined(VERSION_EU) || defined(VERSION_SH)
OSPiHandle *__osPiTable = NULL;
#endif
#ifdef VERSION_SH
OSPiHandle *__osCurrentHandle[2] = { &CartRomHandle, &LeoDiskHandle };
#endif
OSThread piMgrThread;
u32 piMgrStack[0x400]; // stack bottom
OSMesgQueue piEventQueue;
OSMesg piEventBuf[OS_PI_MGR_MESG_BUFF_SIZE + 1];

extern u32 gOsPiAccessQueueCreated;
extern OSMesgQueue gOsPiMessageQueue;
void __osDevMgrMain(void *);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 int_disabled;
    OSPri newPri;
    OSPri currentPri;

    if (!__osPiDevMgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&piEventQueue, &piEventBuf[0], OS_PI_MGR_MESG_BUFF_SIZE);
        if (!gOsPiAccessQueueCreated) {
            __osPiCreateAccessQueue();
        } // what is this constant geez
        osSetEventMesg(OS_EVENT_PI, &piEventQueue, (void *) 0x22222222);
        newPri = -1;
        currentPri = osGetThreadPri(NULL);
        if (currentPri < pri) {
            newPri = currentPri;
            osSetThreadPri(NULL, pri);
        }
        int_disabled = __osDisableInt();
        __osPiDevMgr.active = TRUE;
        __osPiDevMgr.thread = &piMgrThread;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.evtQueue = &piEventQueue;
        __osPiDevMgr.acsQueue = &gOsPiMessageQueue;
        __osPiDevMgr.dma = osPiRawStartDma;
#if defined(VERSION_EU) || defined(VERSION_SH)
        __osPiDevMgr.edma = osEPiRawStartDma;
#endif
        osCreateThread(&piMgrThread, 0, __osDevMgrMain, (void *) &__osPiDevMgr, &piMgrStack[0x400], pri);
        osStartThread(&piMgrThread);
        __osRestoreInt(int_disabled);
        if (newPri != -1) {
            osSetThreadPri(NULL, newPri);
        }
    }
}
