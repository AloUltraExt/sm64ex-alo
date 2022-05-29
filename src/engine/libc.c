#include <ultra64.h>

#include "sm64.h"

#if defined(TARGET_N64) && defined(__GNUC__)
extern void bcopy(const void *, void *, size_t);

/*
 * Due to GCC's freestanding requirements, memset, memcmp, and memmove
 * are required to be implemented here. (memcpy is already implemented
 * in libultra.)
 */

void *memset(void *dest, int c, size_t n) {
    u8 *local_dest = dest;
    int i;

    for(i = 0; i < n; i++) {
        local_dest[i] = c;
    }
    return dest;
}

int memcmp(const void *str1, const void *str2, size_t n) {
    u8 *local_str1 = str1;
    u8 *local_str2 = str2;

    while (n --> 0) {
        if (*local_str1++ != *local_str2++) {
            return local_str1[-1] < local_str2[-1] ? -1 : 1;
        }
    }
    return 0;
}

void *memmove(void *str1, const void *str2, size_t n) {
    bcopy(str2, str1, n);
    return str1;
}

int strcmp(char *s, char *t) {
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

#endif

#ifdef TARGET_WII_U

#include <coreinit/cache.h>
#include <coreinit/memory.h>
#include <dmae/mem.h>

void* memcpy(void* _dst, const void* _src, u32 size)
{
    if (size > 5120)
    {
        u8*       dst =       (u8*)_dst;
        const u8* src = (const u8*)_src;

        const u32 srcMisalignment = (uintptr_t)src & 7U;
        const u32 dstMisalignment = (uintptr_t)dst & 7U;
        if (srcMisalignment != dstMisalignment)
            return OSBlockMove(dst, src, size, FALSE);

        if (srcMisalignment)
        {
            const u32 misalignmentInv = 8U - srcMisalignment;
            OSBlockMove(dst, src, misalignmentInv, FALSE);
            src += misalignmentInv;
            dst += misalignmentInv;
        }

        const u32 sizeAligned   = size & ~3U;
        const u32 sizeRemainder = size & 3U;

        DCFlushRange((void*)src, sizeAligned);
        DCFlushRange((void*)dst, sizeAligned);
        while (!DMAEWaitDone(DMAECopyMem(dst, src, sizeAligned >> 2, DMAE_SWAP_NONE)))
        {
        }

        if (sizeRemainder)
            OSBlockMove(dst + sizeAligned, src + sizeAligned, sizeRemainder, FALSE);

        DCFlushRange(_dst, size);
        return _dst;
    }

    return OSBlockMove(_dst, _src, size, FALSE);
}

void* memmove(void* dst, const void* src, u32 size)
{
    if (src + size < dst || dst + size < src)
        return memcpy(dst, src, size);

    return OSBlockMove(dst, src, size, FALSE);
}

void* memset(void* _dst, int val, u32 size)
{
    if (size > 5120)
    {
        u8* dst = (u8*)_dst;

        const u32 dstMisalignment = (uintptr_t)dst & 7U;
        if (dstMisalignment)
        {
            const u32 misalignmentInv = 8U - dstMisalignment;
            OSBlockSet(dst, val, misalignmentInv);
            dst += misalignmentInv;
        }

        const u32 sizeAligned   = size & ~3U;
        const u32 sizeRemainder = size & 3U;

        DCFlushRange((void*)dst, sizeAligned);
        while (!DMAEWaitDone(DMAEFillMem(dst, val, sizeAligned >> 2)))
        {
        }

        if (sizeRemainder)
            OSBlockSet(dst + sizeAligned, val, sizeRemainder);

        DCFlushRange(_dst, size);
        return _dst;
    }

    return OSBlockSet(_dst, val, size);
}

#endif
