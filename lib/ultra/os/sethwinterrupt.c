#include "PR/os_internal.h"

// A stack frame was added to hardware interrupt handlers in 2.0J
#if LIBULTRA_VERSION >= OS_VER_J
struct __osHwInt {
    s32 (*handler)(void);
    void* stackEnd;
};

extern struct __osHwInt __osHwIntTable[];
#else
extern s32 (*__osHwIntTable[])(void);
#endif

#if LIBULTRA_VERSION >= OS_VER_J
void __osSetHWIntrRoutine(OSHWIntr interrupt, s32 (*handler)(void), void* stackEnd)
#else
void __osSetHWIntrRoutine(OSHWIntr interrupt, s32 (*handler)(void))
#endif
{
    register u32 saveMask = __osDisableInt();

#if LIBULTRA_VERSION >= OS_VER_J
    __osHwIntTable[interrupt].handler = handler;
    __osHwIntTable[interrupt].stackEnd = stackEnd;
#else
    __osHwIntTable[interrupt] = handler;
#endif
    __osRestoreInt(saveMask);
}
