#include "libultra_internal.h"
#include "controller.h"

s32 osEepromLongWrite(OSMesgQueue *mq, u8 address, u8 *buffer, int nbytes) {
    s32 result = 0;
    if (address > 0x40) {
        return -1;
    }

    while (nbytes > 0) {
        result = osEepromWrite(mq, address, buffer);
        if (result != 0) {
            return result;
        }

        nbytes -= EEPROM_BLOCK_SIZE;
        address++;
        buffer += EEPROM_BLOCK_SIZE;
        osSetTimer(&__osEepromTimer, 12000 * osClockRate / 1000000, 0, &__osEepromTimerQ, __osEepromTimerMsg);
        osRecvMesg(&__osEepromTimerQ, NULL, OS_MESG_BLOCK);
    }

    return result;
}
