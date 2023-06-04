#include "PR/os_internal.h"

#if LIBULTRA_VERSION >= OS_VER_K
u8 __osContAddressCrc(u16 addr) {
    u32 temp = 0;
    u32 i = 0x400;

    do {
        temp <<= 1;

        if (addr & i) {
            if (temp & 0x20) {
                temp ^= 0x14;
            } else {
                ++temp;
            }
        } else if (temp & 0x20) {
            temp ^= 0x15;
        }

        i >>= 1;
    } while (i != 0);

    i = 5;

    do {
        temp <<= 1;
        if (temp & 0x20) {
            temp ^= 0x15;
        }
    } while (--i != 0);

    return temp & 0x1F;
}

u8 __osContDataCrc(u8* data) {
    u32 temp = 0;
    u32 i;
    u32 j;

    for (i = 0x20; i; --i) {
        for (j = 0x80; j; j >>= 1) {
            temp <<= 1;

            if ((*data & j) != 0) {
                if ((temp & 0x100) != 0) {
                    temp ^= 0x84;
                } else {
                    ++temp;
                }
            } else if (temp & 0x100) {
                temp ^= 0x85;
            }
        }

        data++;
    }
    do {
        temp <<= 1;

        if (temp & 0x100) {
            temp ^= 0x85;
        }
    } while (++i < 8U);

    return temp;
}

#else
u8 __osContAddressCrc(u16 addr) {
    u8 temp;
    u8 temp2;
    int i;
    temp = 0;
    for (i = 0; i < 16; i++) {
        if (temp & 0x10) {
            temp2 = 21;
        } else {
            temp2 = 0;
        }

        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    return temp & 0x1f;
}

u8 __osContDataCrc(u8 *data) {
    u8 temp;
    u8 temp2;
    int i;
    int j;
    temp = 0;
    for (i = 0; i <= 32; i++, data++) {
        for (j = 7; j >= 0; j--) {
            if (temp & 0x80) {
                temp2 = 133;
            } else {
                temp2 = 0;
            }
            temp <<= 1;
            if (i == 32) {
                temp &= -1;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }
            temp ^= temp2;
        }
    }
    return temp;
}
#endif
