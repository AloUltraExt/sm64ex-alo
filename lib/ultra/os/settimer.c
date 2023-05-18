#include "PR/os_internal.h"
#include "osint.h"
#include "macros.h"

u32 osSetTimer(OSTimer *t, OSTime countdown, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
#if LIBULTRA_VERSION >= OS_VER_K
    UNUSED OSTime time;
    OSTimer *next;
    u32 count;
    u32 value;
    u32 saveMask;
#else
    OSTime time; 
#endif

    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    t->value = (countdown != 0) ? countdown : interval;
    t->mq = mq;
    t->msg = msg;

#if LIBULTRA_VERSION >= OS_VER_K
    saveMask = __osDisableInt();
    if (__osTimerList->next == __osTimerList) {
    } else {
        next = __osTimerList->next;
        count = osGetCount();
        value = count - __osTimerCounter;

        if (value < next->value) {
            next->value -= value;
        } else {
            next->value = 1;
        }
    }

    time = __osInsertTimer(t);
    __osSetTimerIntr(__osTimerList->next->value);

    __osRestoreInt(saveMask);
#else
    time = __osInsertTimer(t);
    if (__osTimerList->next == t) {
        __osSetTimerIntr(time);
    }
#endif

    return 0;
}
