#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#if LIBULTRA_VERSION > OS_VER_H
ALIGNED16 OSPifRam __osEepPifRam;
#if LIBULTRA_VERSION >= OS_VER_L
s32 __osEepromRead16K;
#endif
#endif

#ifdef BBPLAYER

s32 osEepromRead(UNUSED OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;

    __osSiGetAccess();

    if (__osBbEepromSize == EEPROM_SIZE) {
        if (address >= EEPROM_MAXBLOCKS) {
            ret = CONT_RANGE_ERROR;
        }
    } else if (__osBbEepromSize != EEP16K_SIZE) {
        ret = CONT_NO_RESPONSE_ERROR;
    }

    if (ret == 0) {
        int i;
        for (i = 0; i < EEPROM_BLOCK_SIZE; i++) {
            buffer[i] = (__osBbEepromAddress + address * EEPROM_BLOCK_SIZE)[i];
        }
    }

    __osSiRelAccess();
    return ret;
}

#else
static void __osPackEepReadData(u8);

s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    s32 i = 0;
#if LIBULTRA_VERSION > OS_VER_H
    u16 type;
#endif
    u8 *ptr = (u8 *) &__osEepPifRam.ramarray;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

#if LIBULTRA_VERSION < OS_VER_I
    if (address > EEPROM_MAXBLOCKS) {
        return CONT_RANGE_ERROR;
    }
#endif

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);

#if LIBULTRA_VERSION > OS_VER_H
    type = sdata.type & (CONT_EEPROM | CONT_EEP16K);

#if LIBULTRA_VERSION < OS_VER_J
    if (ret != 0) {
        __osSiRelAccess();
        return CONT_NO_RESPONSE_ERROR;
    }
#else
    if (ret == 0) {
#endif
        switch (type) {
            case CONT_EEPROM:
                CONT_CHECK_BLOCK(address, EEPROM_MAXBLOCKS, CONT_RANGE_ERROR);
                break;
            case CONT_EEPROM | CONT_EEP16K:
                // error not technically possible
                CONT_CHECK_BLOCK(address, EEP16K_MAXBLOCKS, CONT_RANGE_ERROR)
#if LIBULTRA_VERSION >= OS_VER_L
                else {
                    __osEepromRead16K = 1;
                }
#endif
                break;
            default:
#if LIBULTRA_VERSION < OS_VER_J
                __osSiRelAccess();
                return CONT_NO_RESPONSE_ERROR;
#else
                ret = CONT_NO_RESPONSE_ERROR;
#endif
        }
#if LIBULTRA_VERSION >= OS_VER_J
    }

    if (ret != 0) {
        __osSiRelAccess();
        return ret;
    }
#endif

#else
    if (ret != 0 || sdata.type != CONT_EEPROM) {
        return CONT_NO_RESPONSE_ERROR;
    }
#endif

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }
    __osPackEepReadData(address);

    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam); // send command to pif
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

#if LIBULTRA_VERSION < OS_VER_I
    CONT_PIFRAM_SET(__osEepPifRam, CONT_CMD_NOP, 0);
#endif

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam); //recv response
    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        ptr++;
    }

    eepromformat = *(__OSContEepromFormat *) ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < ARRAY_COUNT(eepromformat.data); i++) {
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

#if LIBULTRA_VERSION >= OS_VER_J
    __osEepPifRam.pifstatus = CONT_CMD_EXE;
#else
    CONT_PIFRAM_SET(__osEepPifRam, CONT_CMD_NOP, CONT_CMD_EXE);
#endif

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;

#if LIBULTRA_VERSION < OS_VER_J
    for (i = 0; i < ARRAY_COUNT(eepromformat.data); i++) {
        eepromformat.data[i] = 0;
    }
#endif

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat *) ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    *ptr = CONT_CMD_END;
}

#endif
