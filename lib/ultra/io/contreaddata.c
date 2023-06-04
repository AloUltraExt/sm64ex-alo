#include "PR/os_internal.h"
#include "controller.h"
#include "macros.h"
#ifdef BBPLAYER
#include "PR/bcp.h"
#endif

void __osPackReadData(void);

s32 osContStartReadData(OSMesgQueue *mesg) {
    s32 ret = 0;
#if LIBULTRA_VERSION < OS_VER_I
    s32 i;
#endif

    __osSiGetAccess();

    if (__osContLastCmd != CONT_CMD_READ_BUTTON) {
        __osPackReadData();
        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mesg, NULL, OS_MESG_BLOCK);
    }

#if LIBULTRA_VERSION < OS_VER_I
    CONT_PIFRAM_SET(__osContPifRam, CONT_CMD_NOP, 0);
#endif

    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
#ifdef BBPLAYER
    __osContLastCmd = CONT_CMD_CHANNEL_RESET;
#else
    __osContLastCmd = CONT_CMD_READ_BUTTON;
#endif

    __osSiRelAccess();

    return ret;
}

void osContGetReadData(OSContPad *data) {
    u8 *ptr = (u8 *) __osContPifRam.ramarray;
    __OSContReadFormat readformat;
    s32 i;

    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(readformat), data++) {
        readformat = * (__OSContReadFormat *) ptr;
        data->errnum = CHNL_ERR(readformat);

        if (data->errnum != 0) {
            continue;
        }

        data->button = readformat.button;
        data->stick_x = readformat.stick_x;
        data->stick_y = readformat.stick_y;
    }

#ifdef BBPLAYER
    if (__osBbIsBb && __osBbHackFlags != 0) {
        OSContPad tmp;
        data -= __osMaxControllers;

        tmp = *data;
        *data = data[__osBbHackFlags];
        data[__osBbHackFlags] = tmp;
    }
#endif
}

void __osPackReadData() {
    u8 *ptr = (u8 *) __osContPifRam.ramarray;
    __OSContReadFormat readformat;
    s32 i;

    CONT_PIFRAM_SET(__osContPifRam, 0, CONT_CMD_EXE);

    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;

    for (i = 0; i < __osMaxControllers; i++) {
        * (__OSContReadFormat *) ptr = readformat;
        ptr += sizeof(readformat);
    }
    *ptr = CONT_CMD_END;
}
