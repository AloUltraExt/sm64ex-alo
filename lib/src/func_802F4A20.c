#include "PR/rcp.h"
#include "piint.h"
#include "new_func.h"

void func_802F4A20(void) {
    __OSTranxInfo *sp1c;
    volatile u32 sp18;
    sp1c = &__osDiskHandle->transferInfo;
    WAIT_ON_LEO_IO_BUSY(sp18);
    IO_WRITE(LEO_BM_CTL, (LEO_BM_CTL_RESET | sp1c->bmCtlShadow));
    WAIT_ON_LEO_IO_BUSY(sp18);
    IO_WRITE(LEO_BM_CTL, sp1c->bmCtlShadow);
    func_802F4B08();
    IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
    __OSGlobalIntMask |= 0x00100401; // TODO: fix magic numbers
}

typedef struct OSEventMessageStruct_0_s {
    OSMesgQueue *queue;
    OSMesg msg;
} OSEventMessageStruct_0;

extern OSEventMessageStruct_0 __osEventStateTab[16]; // should be OS_NUM_EVENTS + 1 I think

void func_802F4B08(void) {
    OSEventMessageStruct_0 *sp2c;
    OSMesgQueue *sp28;
    u32 sp24;
    register OSThread *s0;
    sp2c = &__osEventStateTab[OS_EVENT_PI];
    sp28 = sp2c->queue;
    if (!sp28 || sp28->validCount >= sp28->msgCount) {
        return;
    }
    sp24 = (sp28->first + sp28->validCount) % sp28->msgCount;
    sp28->msg[sp24] = sp2c->msg;
    sp28->validCount++;
    if (sp28->mtqueue->next != NULL) {
        s0 = __osPopThread(&sp28->mtqueue);
        __osEnqueueThread(&__osRunQueue, s0);
    }
}
