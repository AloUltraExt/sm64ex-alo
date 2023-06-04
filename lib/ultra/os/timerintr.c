#include "PR/os_internal.h"
#include "osint.h"

OSTimer __osBaseTimer;
OSTime __osCurrentTime;
u32 __osBaseCounter;
u32 __osViIntrCount;
u32 __osTimerCounter;
OSTimer *__osTimerList = &__osBaseTimer;

void __osTimerServicesInit(void) {
    __osCurrentTime = 0;
    __osBaseCounter = 0;
    __osViIntrCount = 0;
    __osTimerList->next = __osTimerList->prev = __osTimerList;
    __osTimerList->interval = __osTimerList->value = 0;
    __osTimerList->mq = NULL;
    __osTimerList->msg = 0;
}

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsedCycles;

    if (__osTimerList->next == __osTimerList) {
        return;
    }

    for (;;) {
        t = __osTimerList->next;

        if (t == __osTimerList) {
            __osSetCompare(0);
            __osTimerCounter = 0;
            break;
        }

        count = osGetCount();
        elapsedCycles = count - __osTimerCounter;
        __osTimerCounter = count;

        if (elapsedCycles < t->value) {
            t->value -= elapsedCycles;
            __osSetTimerIntr(t->value);
            break;
        }

        t->prev->next = t->next;
        t->next->prev = t->prev;
        t->next = NULL;
        t->prev = NULL;

        if (t->mq != NULL) {
            osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
        }

        if (t->interval != 0) {
            t->value = t->interval;
            __osInsertTimer(t);
        }
    }
}

void __osSetTimerIntr(OSTime tim) {
    OSTime newTime;
    u32 savedMask;

#if LIBULTRA_VERSION >= OS_VER_K
    if (tim < 468) {
        tim = 468;
    }
#endif

    savedMask = __osDisableInt();
    __osTimerCounter = osGetCount();
    newTime = __osTimerCounter + tim;
    __osSetCompare(newTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask = __osDisableInt();

    timep = __osTimerList->next;
    tim = t->value;
    for (; timep != __osTimerList && tim > timep->value; timep = timep->next) {
        tim -= timep->value;
    }

    t->value = tim;

    if (timep != __osTimerList) {
        timep->value -= tim;
    }

    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
