#ifndef RUMBLE_INIT_H
#define RUMBLE_INIT_H

#include <PR/ultratypes.h>
#include "config.h"

#ifdef RUMBLE_FEEDBACK

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
