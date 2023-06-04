#include "PR/os_internal.h"
#include "macros.h"

OSMesg osSiMesgBuff[1];
ALIGNED8 OSMesgQueue __osSiAccessQueue;
u32 __osSiAccessQueueEnabled = FALSE;

void __osSiCreateAccessQueue() {
    __osSiAccessQueueEnabled = TRUE;
    osCreateMesgQueue(&__osSiAccessQueue, &osSiMesgBuff[0], 1);
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osSiAccessQueueEnabled) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&__osSiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
