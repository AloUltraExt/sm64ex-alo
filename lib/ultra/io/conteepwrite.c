#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#if LIBULTRA_VERSION < OS_VER_I
ALIGNED16 OSPifRam __osEepPifRam;
#endif

#ifdef BBPLAYER

s32 osEepromWrite(UNUSED OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    s32 i;

    __osSiGetAccess();

    if (__osBbEepromSize == EEPROM_SIZE) {
        if (address >= EEPROM_MAXBLOCKS) {
            ret = CONT_RANGE_ERROR;
        }
    } else if (__osBbEepromSize != EEP16K_SIZE) {
        ret = CONT_NO_RESPONSE_ERROR;
    }

    if (ret == 0) {
        for (i = 0; i < EEPROM_BLOCK_SIZE; i++) {
            (__osBbEepromAddress + address * EEPROM_BLOCK_SIZE)[i] = buffer[i];
        }
    }

    __osSiRelAccess();
    return ret;
}

#else
void __osPackEepWriteData(u8, u8 *);

s32 osEepromWrite(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
#if LIBULTRA_VERSION < OS_VER_J
    s32 i;
#endif
#if LIBULTRA_VERSION > OS_VER_H
    u16 type;
#endif
    u8 *ptr = (u8 *) &__osEepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    OSContStatus sdata;
#if LIBULTRA_VERSION > OS_VER_K
    u8 temp[EEPROM_BLOCK_SIZE];
#endif

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
                else if (__osEepromRead16K) {
                    __osEepromRead16K = 0;
                    __osSiRelAccess();
                    osEepromRead(mq, (address ^ 1), temp);
                    __osSiGetAccess();
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

    __osPackEepWriteData(address, buffer);

    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam); // send command to pif
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

#if LIBULTRA_VERSION < OS_VER_I
    CONT_PIFRAM_SET(__osEepPifRam, CONT_CMD_NOP, 0);
#endif

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam); //recv response
    __osContLastCmd = CONT_CMD_WRITE_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

#if LIBULTRA_VERSION >= OS_VER_J
    ptr += MAXCONTROLLERS;
#else
    for (i = 0; i < MAXCONTROLLERS; i++) {
        ptr++;
    }
#endif

    eepromformat = *(__OSContEepromFormat *) ptr;
    ret = CHNL_ERR(eepromformat);

    __osSiRelAccess();
    return ret;
}

void __osPackEepWriteData(u8 address, u8 *buffer) {
    u8 *ptr = (u8 *) &__osEepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    s32 i;

#if LIBULTRA_VERSION >= OS_VER_J
    __osEepPifRam.pifstatus = CONT_CMD_EXE;
#else
    CONT_PIFRAM_SET(__osEepPifRam, CONT_CMD_NOP, CONT_CMD_EXE);
#endif

    eepromformat.txsize = CONT_CMD_WRITE_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_WRITE_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_WRITE_EEPROM;
    eepromformat.address = address;

    for (i = 0; i < ARRAY_COUNT(eepromformat.data); i++) {
        eepromformat.data[i] = *buffer++;
    }

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat *) ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    *ptr = CONT_CMD_END;
}

s32 __osEepStatus(OSMesgQueue *mq, OSContStatus *data) {
    u32 ret = 0;
    s32 i;
    u8 *ptr = (u8 *) __osEepPifRam.ramarray;
    __OSContRequesFormat requestformat;

    CONT_PIFRAM_SET(__osEepPifRam, 0, CONT_CMD_EXE);

    ptr = (u8 *) __osEepPifRam.ramarray;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = CONT_CMD_REQUEST_STATUS;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;

    *REQFORMAT(ptr) = requestformat;
    ptr += sizeof(__OSContRequesFormat);
    *ptr = CONT_CMD_END;

    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

#if LIBULTRA_VERSION >= OS_VER_J
    __osContLastCmd = CONT_CMD_END;
#elif LIBULTRA_VERSION >= OS_VER_I
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
#else
    __osContLastCmd = CONT_CMD_WRITE_EEPROM;
#endif

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    if (ret != 0) {
        return ret;
    }

    ptr = (u8 *) &__osEepPifRam;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    requestformat = *REQFORMAT(ptr);

    data->errnum = CHNL_ERR(requestformat);
    data->type = (requestformat.typel << 8) | requestformat.typeh;
    data->status = requestformat.status;

    if (data->errnum != 0) {
        return data->errnum;
    }

    return 0;
}

#endif
