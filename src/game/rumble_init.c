#include <ultra64.h>
#include "macros.h"

#include "buffers/buffers.h"
#include "main.h"
#include "rumble_init.h"
#include "config.h"

#ifdef RUMBLE_FEEDBACK

OSThread gRumblePakThread;

s32 gRumblePakPfs; // Actually an OSPfs but we don't have that header yet

s8 D_SH_8031D8F8[0x60];

OSMesg gRumblePakSchedulerMesgBuf[1];
OSMesgQueue gRumblePakSchedulerMesgQueue;
OSMesg gRumbleThreadVIMesgBuf[1];
OSMesgQueue gRumbleThreadVIMesgQueue;

struct RumbleData gRumbleDataQueue[3];
struct RumbleSettings gCurrRumbleSettings;

s32 sRumblePakThreadActive = FALSE;
s32 sRumblePakActive = FALSE;
s32 sRumblePakErrorCount = 0;
s32 gRumblePakTimer = 0;

// These void* are OSPfs* but we don't have that header
extern s32 osMotorStop(void *);
extern s32 osMotorStart(void *);
extern u32 osMotorInit(OSMesgQueue *, void *, s32);

#define	RUMBLE_EVENT_NOMESG	    0
#define	RUMBLE_EVENT_CONSTON	1
#define	RUMBLE_EVENT_LEVELON	2

void init_rumble_pak_scheduler_queue(void) {
#ifdef TARGET_N64
    osCreateMesgQueue(&gRumblePakSchedulerMesgQueue, gRumblePakSchedulerMesgBuf, 1);
    osSendMesg(&gRumblePakSchedulerMesgQueue, (OSMesg) 0, OS_MESG_NOBLOCK);
#endif
}

void block_until_rumble_pak_free(void) {
#ifdef TARGET_N64
    OSMesg msg;
    osRecvMesg(&gRumblePakSchedulerMesgQueue, &msg, OS_MESG_BLOCK);
#endif
}

void release_rumble_pak_control(void) {
#ifdef TARGET_N64
    osSendMesg(&gRumblePakSchedulerMesgQueue, (OSMesg) 0, OS_MESG_NOBLOCK);
#endif
}

static void start_rumble(void) {
    if (!sRumblePakActive) {
        return;
    }

    block_until_rumble_pak_free();

    if (!osMotorStart(&gRumblePakPfs)) {
        sRumblePakErrorCount = 0;
    } else {
        sRumblePakErrorCount++;
    }

    release_rumble_pak_control();
}

static void stop_rumble(void) {
    if (!sRumblePakActive) {
        return;
    }

    block_until_rumble_pak_free();

    if (!osMotorStop(&gRumblePakPfs)) {
        sRumblePakErrorCount = 0;
    } else {
        sRumblePakErrorCount++;
    }

    release_rumble_pak_control();
}

static void update_rumble_pak(void) {
#ifdef TARGET_N64
    if (gResetTimer > 0) {
        stop_rumble();
        return;
    }
#endif

    if (gCurrRumbleSettings.start > 0) {
        gCurrRumbleSettings.start--;
        start_rumble();
    } else if (gCurrRumbleSettings.timer > 0) {
        gCurrRumbleSettings.timer--;

        gCurrRumbleSettings.level -= gCurrRumbleSettings.decay;
        if (gCurrRumbleSettings.level < 0) {
            gCurrRumbleSettings.level = 0;
        }

        if (gCurrRumbleSettings.event == RUMBLE_EVENT_CONSTON) {
            start_rumble();
        } else if (gCurrRumbleSettings.count >= 0x100) {
            gCurrRumbleSettings.count -= 0x100;
            start_rumble();
        } else {
            gCurrRumbleSettings.count +=
                ((gCurrRumbleSettings.level * gCurrRumbleSettings.level * gCurrRumbleSettings.level) / (1 << 9)) + 4;

            stop_rumble();
        }
    } else {
        gCurrRumbleSettings.timer = 0;

        if (gCurrRumbleSettings.slip >= 5) {
            start_rumble();
        } else if ((gCurrRumbleSettings.slip >= 2) && (gGlobalTimer % gCurrRumbleSettings.viblate == 0)) {
            start_rumble();
        } else {
            stop_rumble();
        }
    }

    if (gCurrRumbleSettings.slip > 0) {
        gCurrRumbleSettings.slip--;
    }
}

static void update_rumble_data_queue(void) {
    if (gRumbleDataQueue[0].comm) {
        gCurrRumbleSettings.count = 0;
        gCurrRumbleSettings.start = 4;
        gCurrRumbleSettings.event = gRumbleDataQueue[0].comm;
        gCurrRumbleSettings.timer = gRumbleDataQueue[0].time;
        gCurrRumbleSettings.level = gRumbleDataQueue[0].level;
        gCurrRumbleSettings.decay = gRumbleDataQueue[0].decay;
    }

    gRumbleDataQueue[0] = gRumbleDataQueue[1];
    gRumbleDataQueue[1] = gRumbleDataQueue[2];

    gRumbleDataQueue[2].comm = 0;
}

void queue_rumble_data(s16 time, s16 level) {
    if (gCurrDemoInput != NULL) {
        return;
    }

    if (level > 70) {
        gRumbleDataQueue[2].comm = RUMBLE_EVENT_CONSTON;
    } else {
        gRumbleDataQueue[2].comm = RUMBLE_EVENT_LEVELON;
    }

    gRumbleDataQueue[2].level = level;
    gRumbleDataQueue[2].time = time;
    gRumbleDataQueue[2].decay = 0;
}

void queue_rumble_decay(s16 level) {
    gRumbleDataQueue[2].decay = level;
}

u8 is_rumble_finished_and_queue_empty(void) {
    if (gCurrRumbleSettings.start + gCurrRumbleSettings.timer >= 4) {
        return FALSE;
    }

    if (gRumbleDataQueue[0].comm != RUMBLE_EVENT_NOMESG) {
        return FALSE;
    }

    if (gRumbleDataQueue[1].comm != RUMBLE_EVENT_NOMESG) {
        return FALSE;
    }

    if (gRumbleDataQueue[2].comm != RUMBLE_EVENT_NOMESG) {
        return FALSE;
    }

    return TRUE;
}

void reset_rumble_timers_slip(void) {
    if (gCurrDemoInput != NULL) {
        return;
    }

    if (gCurrRumbleSettings.slip == 0) {
        gCurrRumbleSettings.slip = 7;
    }

    if (gCurrRumbleSettings.slip < 4) {
        gCurrRumbleSettings.slip = 4;
    }

    gCurrRumbleSettings.viblate = 7;
}

void reset_rumble_timers_viblate(s32 level) {
    if (gCurrDemoInput != NULL) {
        return;
    }

    if (gCurrRumbleSettings.slip == 0) {
        gCurrRumbleSettings.slip = 7;
    }

    if (gCurrRumbleSettings.slip < 4) {
        gCurrRumbleSettings.slip = 4;
    }

    if (level == 4) {
        gCurrRumbleSettings.viblate = 1;
    }

    if (level == 3) {
        gCurrRumbleSettings.viblate = 2;
    }

    if (level == 2) {
        gCurrRumbleSettings.viblate = 3;
    }

    if (level == 1) {
        gCurrRumbleSettings.viblate = 4;
    }

    if (level == 0) {
        gCurrRumbleSettings.viblate = 5;
    }
}

void queue_rumble_submerged(void) {
    if (gCurrDemoInput != NULL) {
        return;
    }

    gCurrRumbleSettings.slip = 4;
    gCurrRumbleSettings.viblate = 4;
}

void thread6_rumble_loop(UNUSED void *a0) {
#ifdef TARGET_N64
    OSMesg msg;

    cancel_rumble();

    sRumblePakThreadActive = TRUE;
#endif

#ifdef TARGET_N64
    while (TRUE) {
#endif
        // Block until VI
        #ifdef TARGET_N64
        osRecvMesg(&gRumbleThreadVIMesgQueue, &msg, OS_MESG_BLOCK);
        #endif
        
        update_rumble_data_queue();
        update_rumble_pak();

        if (sRumblePakActive) {
            if (sRumblePakErrorCount >= 30) {
                sRumblePakActive = FALSE;
            }
        } 

        else if (gGlobalTimer % 60 == 0) {
            sRumblePakActive = osMotorInit(&gSIEventMesgQueue, &gRumblePakPfs, gPlayer1Controller->port) < 1;
            sRumblePakErrorCount = 0;
        }


        if (gRumblePakTimer > 0) {
            gRumblePakTimer--;
        }
#ifdef TARGET_N64
    }
#endif
}

void cancel_rumble(void) {
    sRumblePakActive = osMotorInit(&gSIEventMesgQueue, &gRumblePakPfs, gPlayer1Controller->port) < 1;

    if (sRumblePakActive) {
        osMotorStop(&gRumblePakPfs);
    }

    gRumbleDataQueue[0].comm = 0;
    gRumbleDataQueue[1].comm = 0;
    gRumbleDataQueue[2].comm = 0;

    gCurrRumbleSettings.timer = 0;
    gCurrRumbleSettings.slip = 0;

    gRumblePakTimer = 0;
}

void create_thread_6(void) {
#ifdef TARGET_N64
    osCreateMesgQueue(&gRumbleThreadVIMesgQueue, gRumbleThreadVIMesgBuf, 1);
    osCreateThread(&gRumblePakThread, 6, thread6_rumble_loop, NULL, gThread6Stack + 0x2000, 30);
    osStartThread(&gRumblePakThread);
#endif
}

void rumble_thread_update_vi(void) {
    if (!sRumblePakThreadActive) {
        return;
    }

#ifdef TARGET_N64
    // 0x56525443 = 'VRTC'
    osSendMesg(&gRumbleThreadVIMesgQueue, (OSMesg) 0x56525443, OS_MESG_NOBLOCK);
#endif
}

#endif
