#ifndef RUMBLE_INIT_H
#define RUMBLE_INIT_H

#include "config.h"

#ifdef RUMBLE_FEEDBACK

struct RumbleData {
    u8 comm;
    u8 level;
    s16 time;
    s16 decay;
};

struct RumbleSettings {
    s16 event;
    s16 level;
    s16 timer;
    s16 count;
    s16 start;
    s16 slip;
    s16 viblate;
    s16 decay;
};

extern OSThread gRumblePakThread;

extern OSPfs gRumblePakPfs;

extern OSMesg gRumblePakSchedulerMesgBuf[1];
extern OSMesgQueue gRumblePakSchedulerMesgQueue;
extern OSMesg gRumbleThreadVIMesgBuf[1];
extern OSMesgQueue gRumbleThreadVIMesgQueue;

extern struct RumbleData gRumbleDataQueue[3];
extern struct RumbleSettings gCurrRumbleSettings;

extern s32 gRumblePakTimer;

void init_rumble_pak_scheduler_queue(void);
void block_until_rumble_pak_free(void);
void release_rumble_pak_control(void);
void queue_rumble_data(s16 time, s16 level);
void queue_rumble_decay(s16 level);
u8 is_rumble_finished_and_queue_empty(void);
void reset_rumble_timers_slip(void);
void reset_rumble_timers_viblate(s32 level);
void queue_rumble_submerged(void);
void cancel_rumble(void);
void create_thread_6(void);
void rumble_thread_update_vi(void);
void thread6_rumble_loop(void *a0);

#endif // RUMBLE_FEEDBACK

#endif // RUMBLE_INIT_H
