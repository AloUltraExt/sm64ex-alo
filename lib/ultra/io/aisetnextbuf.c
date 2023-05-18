#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "../os/osint.h"

/**
 * It is worth noting that a previous hardware bug has been fixed by a software
 * patch in osAiSetNextBuffer. This bug occurred when the address of the end of the
 * buffer specified by osAiSetNextBuffer was at a specific value. This value
 * occurred when the following was true:
 *
 * Prior 2.0I: (vaddr + nbytes) & 0x00003FFF == 0x2000
 * After 2.0I: (vaddr + nbytes) & 0x00001FFF == 0x0000
 *
 * In this case, the DMA transfer does not complete successfully. This can cause
 * clicks and pops in the audio output. This bug no longer requires special handling
 * by the application because it is now patched by osAiSetNextBuffer.
 */

s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
    static u8 hdwrBugFlag = FALSE;
    char *bptr;

#if LIBULTRA_VERSION >= OS_VER_K
    if (__osAiDeviceBusy()) {
        return -1;
    }
#endif

    bptr = bufPtr;

    if (hdwrBugFlag) {
        bptr -= 0x2000;
    }

#if LIBULTRA_VERSION >= OS_VER_I
    if ((((uintptr_t) bufPtr + size) & 0x1fff) == 0)
#else
    if ((((uintptr_t) bufPtr + size) & 0x3fff) == 0x2000)
#endif
    {
        hdwrBugFlag = TRUE;
    } else {
        hdwrBugFlag = FALSE;
    }

#if LIBULTRA_VERSION < OS_VER_K
    if (__osAiDeviceBusy()) {
        return -1;
    }
#endif

    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);
    return 0;
}
