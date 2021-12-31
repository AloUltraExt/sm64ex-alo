#include "libultra_internal.h"
#include "controller.h"
#include "macros.h"

void __osPackEepReadData(u8);

s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret= 0;
    s32 i = 0;
    u8 *ptr = (u8 *) &__osEepPifRam.ramarray;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    if (address > EEPROM_MAXBLOCKS) {
        return -1;
    }

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if (ret != 0 || sdata.type != CONT_EEPROM) {

        return CONT_NO_RESPONSE_ERROR;
    }

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }
    __osPackEepReadData(address);

    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < ARRAY_COUNT(__osEepPifRam.ramarray); i++) {
        __osEepPifRam.ramarray[i] = CONT_CMD_NOP;
    }
    __osEepPifRam.s.pifstatus = 0;

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < 4; i++) {
        ptr++;
    }

    eepromformat = *(__OSContEepromFormat *) ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < 8; i++) {
            *buffer++ = eepromformat.data[i];
        }
    }

    __osSiRelAccess();
    return ret;
}

void __osPackEepReadData(u8 address) {
    u8 *ptr = (u8 *) &__osEepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    s32 i;
    
    for (i = 0; i < ARRAY_COUNT(__osEepPifRam.ramarray); i++) {
        __osEepPifRam.ramarray[i] = CONT_CMD_NOP;
    }
    __osEepPifRam.s.pifstatus = CONT_CMD_EXE;

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;
    for (i = 0; i < ARRAY_COUNT(eepromformat.data); i++) {
        eepromformat.data[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat *) ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    *ptr = CONT_CMD_END;
}
