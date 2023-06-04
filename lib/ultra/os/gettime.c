#include "PR/os_internal.h"
#include "osint.h"

OSTime osGetTime() {
    u32 tmpTime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;

    saveMask = __osDisableInt();
    tmpTime = osGetCount();
    elapseCount = tmpTime - __osBaseCounter;
    currentCount = __osCurrentTime;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
