#include "PR/os_internal.h"
#include "controller.h"

s32 osEepromLongRead(OSMesgQueue *mq, u8 address, u8 *buffer, s32 length) {
    s32 ret = 0;
#if LIBULTRA_VERSION < OS_VER_I
    if (address > EEPROM_MAXBLOCKS) {
        return CONT_RANGE_ERROR;
    }
#endif

    while (length > 0) {
        ERRCK(osEepromRead(mq, address, buffer));
        length -= EEPROM_BLOCK_SIZE;
        address++;
        buffer += EEPROM_BLOCK_SIZE;
#if LIBULTRA_VERSION < OS_VER_I
        osSetTimer(&__osEepromTimer, OS_USEC_TO_CYCLES(12000), 0, &__osEepromTimerQ, &__osEepromTimerMsg);
        osRecvMesg(&__osEepromTimerQ, NULL, OS_MESG_BLOCK);
#endif
    }

    return ret;
}
