#ifndef MAIN_H
#define MAIN_H

#include "config.h"

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
#endif

extern OSThread D_80339210;
extern OSThread gIdleThread;
extern OSThread gMainThread;
extern OSThread gGameLoopThread;
extern OSThread gSoundThread;

extern OSMesgQueue gPIMesgQueue;
extern OSMesgQueue gIntrMesgQueue;
extern OSMesgQueue gSPTaskMesgQueue;

extern OSMesg gDmaMesgBuf[1];
extern OSMesg gPIMesgBuf[32];
extern OSMesg gSIEventMesgBuf[1];
extern OSMesg gIntrMesgBuf[16];
extern OSMesg gUnknownMesgBuf[16];
extern OSIoMesg gDmaIoMesg;
extern OSMesg gMainReceivedMesg;
extern OSMesgQueue gDmaMesgQueue;
extern OSMesgQueue gSIEventMesgQueue;

extern struct VblankHandler *gVblankHandler1;
extern struct VblankHandler *gVblankHandler2;
extern struct SPTask *gActiveSPTask;
extern u32 gNumVblanks;
extern s8 gResetTimer;
extern s8 gNmiResetBarsTimer;
extern s8 D_8032C650;

extern bool gDebugLevelSelect;
extern bool gShowProfiler;
extern bool gShowDebugText;

void set_vblank_handler(s32 index, struct VblankHandler *handler, OSMesgQueue *queue, OSMesg *msg);
void dispatch_audio_sptask(struct SPTask *spTask);
void exec_display_list(struct SPTask *spTask);

#endif // MAIN_H
