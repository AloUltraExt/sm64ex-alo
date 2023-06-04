#include "internal.h"
#include "data.h"

#ifdef VERSION_SH
struct ReverbSettingsEU sReverbSettings[8] = {
    { /*Downsample Rate*/ 1, /*Window Size*/ 64, /*Gain*/ 0x2FFF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 },
    { /*Downsample Rate*/ 1, /*Window Size*/ 40, /*Gain*/ 0x47FF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 },
    { /*Downsample Rate*/ 1, /*Window Size*/ 64, /*Gain*/ 0x2FFF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 },
    { /*Downsample Rate*/ 1, /*Window Size*/ 60, /*Gain*/ 0x3FFF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 },
    { /*Downsample Rate*/ 1, /*Window Size*/ 48, /*Gain*/ 0x4FFF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 },
    { /*Downsample Rate*/ 1, /*Window Size*/ 64, /*Gain*/ 0x2FFF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 }, // Duplicate of the first index
    { /*Downsample Rate*/ 1, /*Window Size*/ 40, /*Gain*/ 0x47FF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 }, // Duplicate of the second index
    { /*Downsample Rate*/ 1, /*Window Size*/ 40, /*Gain*/ 0x37FF, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000 },
};

struct AudioSessionSettingsEU gAudioSessionPresets[] = {
    { 32000, 1, MAX_SIMULTANEOUS_NOTES, 1, 0, &sReverbSettings[0], 0x7FFF, 0, PERSISTENT_SEQ_MEM, PERSISTENT_BANK_MEM, 0, TEMPORARY_SEQ_MEM, TEMPORARY_BANK_MEM, 0, 0, 0 },
};

s16 gTatumsPerBeat = TATUMS_PER_BEAT;
s32 gAudioHeapSize = DOUBLE_SIZE_ON_64_BIT(AUDIO_HEAP_SIZE);
s32 gAudioInitPoolSize = DOUBLE_SIZE_ON_64_BIT(AUDIO_INIT_POOL_SIZE);

// Used in audio_init:
u32 D_SH_80315EF0 = 0;
u16 D_SH_80315EF4 = 0;
u16 D_SH_80315EF8 = 0;
u16 D_SH_80315EFC = 0;

#endif
