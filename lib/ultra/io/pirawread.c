#include "piint.h"

s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    register u32 stat;

    WAIT_ON_IO_BUSY(stat);
    *data = IO_READ((uintptr_t) osRomBase | devAddr);

    return 0;
}
