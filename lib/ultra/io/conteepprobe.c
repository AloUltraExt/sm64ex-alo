#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

#ifdef BBPLAYER
s32 osEepromProbe(UNUSED OSMesgQueue *mq) {
    s32 ret = 0;

    __osSiGetAccess();

    if (__osBbEepromSize == EEPROM_SIZE) {
        ret = EEPROM_TYPE_4K;
    } else if (__osBbEepromSize == EEP16K_SIZE) {
        ret = EEPROM_TYPE_16K;
    }

    __osSiRelAccess();
    return ret;
}

#else
s32 osEepromProbe(OSMesgQueue *mq) {
    s32 ret = 0;
#if LIBULTRA_VERSION > OS_VER_H
    u16 type;
#endif
    OSContStatus sdata;

    __osSiGetAccess();

#if LIBULTRA_VERSION > OS_VER_H
    ret = __osEepStatus(mq, &sdata);
    type = sdata.type & (CONT_EEPROM | CONT_EEP16K);

    if (ret != 0) {
        ret = 0;
    } else {
        switch (type) {
            case CONT_EEPROM:
                ret = EEPROM_TYPE_4K;
                break;
            case CONT_EEPROM | CONT_EEP16K:
                ret = EEPROM_TYPE_16K;
                break;
            default:
                ret = 0;
                break;
        }
    }

#if BUILD_VERSION >= OS_VER_L
    __osEepromRead16K = 0;
#endif
#else
    ret = __osEepStatus(mq, &sdata);
    ret = (ret == 0 && (sdata.type & CONT_EEPROM)) ? EEPROM_TYPE_4K : 0;
#endif

    __osSiRelAccess();
    return ret;
}
#endif
