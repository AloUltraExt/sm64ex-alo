/*
 * system_checks.c
 *
 * Adds specific checks whenever the game is running on console or emulator.
 * If it runs on emulator, there are more checks depending on which one is used.
 */

#include <ultra64.h>
#include "PR/os_internal.h"
#include "PR/rcp.h"

#include "buffers/framebuffers.h"
#include "game/game_init.h"
#include "game/main.h"
#include "game/print.h"

#include "system_checks.h"

u8 gIsConsole = TRUE; // Needs to be initialized before audio_reset_session is called
u8 gIsWiiVC = TRUE;
u8 gCacheEmulated = TRUE;

void check_cache_emulation() {
    // Disable interrupts to ensure that nothing evicts the variable from cache while we're using it.
    u32 saved = __osDisableInt();
    // Create a variable with an initial value of 1. This value will remain cached.
    volatile u8 sCachedValue = 1;
    // Overwrite the variable directly in RDRAM without going through cache.
    // This should preserve its value of 1 in dcache if dcache is emulated correctly.
    *(u8*)(K0_TO_K1(&sCachedValue)) = 0;
    // Read the variable back from dcache, if it's still 1 then cache is emulated correctly.
    // If it's zero, then dcache is not emulated correctly.
    gCacheEmulated = sCachedValue;
    // Restore interrupts
    __osRestoreInt(saved);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

// literally return what was passed
NO_INLINE f32 round_double_to_float(f64 v) {
   return v;
}

#pragma GCC diagnostic pop

void n64_system_device_checks(void) {
    if (IO_READ(DPC_PIPEBUSY_REG) == 0) {
        gIsConsole = FALSE;
        gIsWiiVC = IS_WII_VC();
        if (!gIsWiiVC) {
            check_cache_emulation();
        } else {
            gCacheEmulated = FALSE;
        }
    } else {
        gIsConsole = TRUE;
    }
}
