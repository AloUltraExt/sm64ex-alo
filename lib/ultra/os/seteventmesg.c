#include "PR/os_internal.h"
#include "osint.h"
#include "macros.h"

ALIGNED8 __OSEventState __osEventStateTab[OS_NUM_EVENTS];
#if LIBULTRA_VERSION >= OS_VER_J
u32 __osPreNMI = FALSE;
#endif

void osSetEventMesg(OSEvent event, OSMesgQueue *mq, OSMesg msg) {
    register u32 saveMask;
    __OSEventState *es;

    saveMask = __osDisableInt();

    es = &__osEventStateTab[event];

    es->messageQueue = mq;
    es->message = msg;

#if LIBULTRA_VERSION >= OS_VER_J
    if (event == OS_EVENT_PRENMI) {
        if (__osShutdown && !__osPreNMI) {
            osSendMesg(mq, msg, OS_MESG_NOBLOCK);
        }
        __osPreNMI = TRUE;
    }
#endif

    __osRestoreInt(saveMask);
}
