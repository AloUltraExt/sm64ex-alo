#include "piint.h"

s32 osPiStartDma(OSIoMesg *mb, s32 priority, s32 direction, uintptr_t devAddr, void *dramAddr, size_t size, OSMesgQueue *mq) {
    register s32 ret;

    if (!__osPiDevMgr.active) {
        return -1;
    }

    if (direction == OS_READ) {
        mb->hdr.type = OS_MESG_TYPE_DMAREAD;
    } else {
        mb->hdr.type = OS_MESG_TYPE_DMAWRITE;
    }

    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = devAddr;
    mb->size = size;
#if LIBULTRA_VERSION > OS_VER_D
    mb->piHandle = NULL;
#endif

    if (priority == OS_MESG_PRI_HIGH) {
        ret = osJamMesg(osPiGetCmdQueue(), mb, OS_MESG_NOBLOCK);
    } else {
        ret = osSendMesg(osPiGetCmdQueue(), mb, OS_MESG_NOBLOCK);
    }

    return ret;
}
