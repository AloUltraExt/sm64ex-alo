#include <macros.h>
#include <PR/os_internal.h>
#include <PR/rcp.h>
#include "../os/osint.h"

OSDevMgr __osViDevMgr = { 0 };
#if LIBULTRA_VERSION >= OS_VER_J
u32 __additional_scanline = 0;
#endif
static OSThread viThread;
static ALIGNED16 u8 viMgrStack[OS_VIM_STACKSIZE];
static OSMesgQueue viEventQueue;
static ALIGNED8 OSMesg viMgrMesgBuff[5];
static ALIGNED8 OSIoMesg viRetraceMsg;
static ALIGNED8 OSIoMesg viCounterMsg;

static void viMgrMain(void *arg);

void osCreateViManager(OSPri pri) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!__osViDevMgr.active) {
        __osTimerServicesInit();
#if LIBULTRA_VERSION >= OS_VER_J
        __additional_scanline = 0;
#endif
        osCreateMesgQueue(&viEventQueue, &viMgrMesgBuff[0], ARRAY_COUNT(viMgrMesgBuff));
        viRetraceMsg.hdr.type = OS_MESG_TYPE_VRETRACE;
        viRetraceMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viRetraceMsg.hdr.retQueue = NULL;
        viCounterMsg.hdr.type = OS_MESG_TYPE_COUNTER;
        viCounterMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viCounterMsg.hdr.retQueue = NULL;
        osSetEventMesg(OS_EVENT_VI, &viEventQueue, &viRetraceMsg);
        osSetEventMesg(OS_EVENT_COUNTER, &viEventQueue, &viCounterMsg);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);

        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }

        savedMask = __osDisableInt();
        __osViDevMgr.active = TRUE;
        __osViDevMgr.thread = &viThread;
        __osViDevMgr.cmdQueue = &viEventQueue;
        __osViDevMgr.evtQueue = &viEventQueue;
        __osViDevMgr.acsQueue = NULL;
        __osViDevMgr.dma = NULL;
#if LIBULTRA_VERSION > OS_VER_D
        __osViDevMgr.edma = NULL;
#endif
        osCreateThread(&viThread, 0, viMgrMain, (void *) &__osViDevMgr, &viMgrStack[OS_VIM_STACKSIZE], pri);
        __osViInit();
        osStartThread(&viThread);
        __osRestoreInt(savedMask);

        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}

static void viMgrMain(void *arg) {
    __OSViContext *vc;
    OSDevMgr *dm;
    OSIoMesg *mb;
    static u16 retrace;
    u32 first;
    u32 count;

    mb = NULL;
    first = FALSE;
    vc = __osViGetCurrentContext();
    retrace = vc->retraceCount;
    if (retrace == 0) {
        retrace = 1;
    }
    dm = (OSDevMgr *) arg;

    while (TRUE) {
        osRecvMesg(dm->evtQueue, (OSMesg)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                retrace--;

                if (retrace == 0) {
                    vc = __osViGetCurrentContext();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    retrace = vc->retraceCount;
                }

                __osViIntrCount++;

                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = 0;
                }

                count = __osBaseCounter;
                __osBaseCounter = osGetCount();
                count = __osBaseCounter - count;
                __osCurrentTime = __osCurrentTime + count;
                break;

            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
