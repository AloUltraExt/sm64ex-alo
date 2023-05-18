#include "PR/os_internal.h"

__OSViContext *__osViGetCurrentContext(void) {
    return __osViCurr;
}
