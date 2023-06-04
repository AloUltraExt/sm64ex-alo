#include "PR/os_internal.h"

s32 __osAtomicDec(u32 *p) {
    s32 mask;
    s32 result;

    mask = __osDisableInt();
    if (*p != 0) {
        (*p)--;
        result = 1;
    } else {
        result = 0;
    }
    __osRestoreInt(mask);
    return result;
}
