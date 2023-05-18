#include <ultra64.h>

#include "buffers.h"
#include "audio/data.h"
#include "config.h"
#include "audio/synthesis.h"

ALIGNED16 u8 gAudioHeap[DOUBLE_SIZE_ON_64_BIT(AUDIO_HEAP_SIZE)];

ALIGNED8 u8 gIdleThreadStack[IDLE_STACKSIZE];
ALIGNED8 u8 gThread3Stack[STACKSIZE];
ALIGNED8 u8 gThread4Stack[STACKSIZE];
ALIGNED8 u8 gThread5Stack[STACKSIZE];

#ifdef RUMBLE_FEEDBACK
ALIGNED8 u8 gThread6Stack[STACKSIZE];
#endif

ALIGNED32 u8 gGfxSPTaskStack[SP_DRAM_STACK_SIZE8];

ALIGNED32 u8 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE];

ALIGNED8 struct SaveBuffer gSaveBuffer; // EEPROM size

struct GfxPool gGfxPools[GFX_NUM_POOLS];
