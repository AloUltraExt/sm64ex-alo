#include <stdio.h>
#include <string.h>
#include <sys/time.h>
//#include "PR/os_internal.h"
#include "macros.h"
#include "platform.h"
#include "fs/fs.h"

#include "game/save_file.h"

#ifdef TARGET_WEB
#include <emscripten.h>
#endif

s32 gNumVblanks;
u64 osClockRate = 62500000;

s32 osPiStartDma(UNUSED OSIoMesg *mb, UNUSED s32 priority, UNUSED s32 direction,
                 uintptr_t devAddr, void *vAddr, size_t nbytes,
                 UNUSED OSMesgQueue *mq) {
    memcpy(vAddr, (const void *) devAddr, nbytes);
    return 0;
}

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msgBuf, s32 count) {
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = count;
    mq->msg = msgBuf;
    return;
}

void osSetEventMesg(UNUSED OSEvent e, UNUSED OSMesgQueue *mq, UNUSED OSMesg msg) {
}
s32 osJamMesg(UNUSED OSMesgQueue *mq, UNUSED OSMesg msg, UNUSED s32 flag) {
    return 0;
}
s32 osSendMesg(UNUSED OSMesgQueue *mq, UNUSED OSMesg msg, UNUSED s32 flag) {
#if defined(VERSION_EU) || defined(VERSION_SH)
    s32 index;
    if (mq->validCount >= mq->msgCount) {
        return -1;
    }
    index = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[index] = msg;
    mq->validCount++;
#endif
    return 0;
}
s32 osRecvMesg(UNUSED OSMesgQueue *mq, UNUSED OSMesg *msg, UNUSED s32 flag) {
#if defined(VERSION_EU) || defined(VERSION_SH)
    if (mq->validCount == 0) {
        return -1;
    }
    if (msg != NULL) {
        *msg = *(mq->first + mq->msg);
    }
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
#endif
    return 0;
}

uintptr_t osVirtualToPhysical(void *addr) {
    return (uintptr_t) addr;
}

void osCreateViManager(UNUSED OSPri pri) {
}
void osViSetMode(UNUSED OSViMode *mode) {
}
void osViSetEvent(UNUSED OSMesgQueue *mq, UNUSED OSMesg msg, UNUSED u32 retraceCount) {
}
void osViBlack(UNUSED u8 active) {
}
void osViSetSpecialFeatures(UNUSED u32 func) {
}
void osViSwapBuffer(UNUSED void *vaddr) {
}

OSTime osGetTime(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)tv.tv_sec * 1000000 + tv.tv_usec;
}

void osWritebackDCacheAll(void) {
}

void osWritebackDCache(UNUSED void *a, UNUSED size_t b) {
}

void osInvalDCache(UNUSED void *a, UNUSED size_t b) {
}

u32 osGetCount(void) {
    static u32 counter;
    return counter++;
}

s32 osAiSetFrequency(u32 freq) {
    u32 a1;
    s32 a2;
    u32 D_8033491C;

#ifdef VERSION_EU
    D_8033491C = 0x02E6025C;
#else
    D_8033491C = 0x02E6D354;
#endif

    a1 = D_8033491C / (float) freq + .5f;

    if (a1 < 0x84) {
        return -1;
    }

    a2 = (a1 / 66) & 0xff;
    if (a2 > 16) {
        a2 = 16;
    }

    return D_8033491C / (s32) a1;
}

s32 osEepromProbe(UNUSED OSMesgQueue *mq) {
    return 1;
}

s32 osEepromLongRead(UNUSED OSMesgQueue *mq, u8 address, u8 *buffer, int nbytes) {
    u8 content[EEPROM_SIZE];
    s32 ret = -1;

#ifdef TARGET_WEB
    if (EM_ASM_INT({
        var s = localStorage.sm64_save_file;
        if (s && s.length === 684) {
            try {
                var binary = atob(s);
                if (binary.length === EEPROM_SIZE) {
                    for (var i = 0; i < EEPROM_SIZE; i++) {
                        HEAPU8[$0 + i] = binary.charCodeAt(i);
                    }
                    return 1;
                }
            } catch (e) {
            }
        }
        return 0;
    }, content)) {
        memcpy(buffer, content + address * 8, nbytes);
        ret = 0;
    }
#else
    fs_file_t *fp = fs_open(SAVE_FILENAME);
    if (fp == NULL) {
        return -1;
    }
    if (fs_read(fp, content, EEPROM_SIZE) == EEPROM_SIZE) {
        memcpy(buffer, content + address * 8, nbytes);
        ret = 0;
    }
    fs_close(fp);
#endif
    return ret;
}

s32 osEepromLongWrite(UNUSED OSMesgQueue *mq, u8 address, u8 *buffer, int nbytes) {
    u8 content[EEPROM_SIZE] = {0};
    if (address != 0 || nbytes != EEPROM_SIZE) {
        osEepromLongRead(mq, 0, content, EEPROM_SIZE);
    }
    memcpy(content + address * 8, buffer, nbytes);

#ifdef TARGET_WEB
    EM_ASM({
        var str = "";
        for (var i = 0; i < EEPROM_SIZE; i++) {
            str += String.fromCharCode(HEAPU8[$0 + i]);
        }
        localStorage.sm64_save_file = btoa(str);
    }, content);
    s32 ret = 0;
#else
    FILE *fp = fopen(fs_get_write_path(SAVE_FILENAME), "wb");
    if (fp == NULL) {
        return -1;
    }
    s32 ret = fwrite(content, 1, EEPROM_SIZE, fp) == EEPROM_SIZE ? 0 : -1;
    fclose(fp);
#endif
    return ret;
}

OSPiHandle *osCartRomInit(void) {
    static OSPiHandle handle;
    return &handle;
}

OSPiHandle *osDriveRomInit(void) {
    static OSPiHandle handle;
    return &handle;
}

s32 osEPiStartDma(UNUSED OSPiHandle *pihandle, OSIoMesg *mb, UNUSED s32 direction) {
    memcpy(mb->dramAddr, (const void *) mb->devAddr, mb->size);
    osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
    return 1;
}
