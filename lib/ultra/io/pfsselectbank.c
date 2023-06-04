#include "PR/os_internal.h"
#include "controller.h"

#if LIBULTRA_VERSION >= OS_VER_K
s32 __osPfsSelectBank(OSPfs* pfs, u8 bank)
#else
s32 __osPfsSelectBank(OSPfs *pfs)
#endif
{
    u8 temp[BLOCKSIZE];
    int i;
    s32 ret = 0;

    for (i = 0; i < BLOCKSIZE; i++) {
#if LIBULTRA_VERSION >= OS_VER_K
        temp[i] = bank;
#else
        temp[i] = pfs->activebank;
#endif
    }

    ret = __osContRamWrite(pfs->queue, pfs->channel, CONT_BLOCK_DETECT, temp, FALSE);

#if LIBULTRA_VERSION >= OS_VER_K
    if (ret == 0) {
        pfs->activebank = bank;
    }
#endif

    return ret;
}
