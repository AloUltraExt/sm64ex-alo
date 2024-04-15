/*
 * ext_mem_screen.c
 *
 * This file is used when 8 MB (Expansion Pak) is set.
 * If the game doesn't have it, then it shows the screen telling the user to
 * insert one, or set the emulator to 8 MB (most recent ones sets it automatically).
 *
 */

#include <types.h>
#include "segments.h"
#include "text_strings.h"
#include "game/game_init.h"
#include "game/main.h"
#include "game/print.h"
#include "game/ingame_menu.h"
#include "game/segment2.h"
#include "engine/level_script.h"

#ifdef USE_EXT_RAM
/*
 * mem_error_screen.inc.c
 *
 * This enhancement should be used for ROM hacks that require the expansion pak.
 *
 */
// Require 8 MB of RAM, even if the pool doesn't go into extended memory.
// Change the '8' to whatever MB limit you want.
// Note: only special emulators allow for RAM sizes above 8 MB.
#define REQUIRED_MIN_MEM_SIZE 0x100000 * 8

u8 gNotEnoughMemory = FALSE;
u8 gDelayForErrorMessage = 0;

u8 does_pool_end_lie_out_of_bounds(void *end) {
    u32 endPhy = ((u32) end) & 0x1FFFFFFF;
    u32 memSize = *((u32 *) 0x80000318); // osMemSize

    if (endPhy > memSize) {
        gNotEnoughMemory = TRUE;
        return TRUE;
    } else {
        if (memSize < REQUIRED_MIN_MEM_SIZE) {
            gNotEnoughMemory = TRUE;
        }
        return FALSE;
    }
}

// If you're using an N64 console, then you will need to buy an\nexpansion pak to play this ROM hack.
u8 text_console_8mb[] = { TEXT_CONSOLE_8MB };

// If you are using PJ64 1.6, go to: Options ► Settings ► Rom Settings Tab ► Memory Size then select 8
// MB from the drop-down box.
u8 text_pj64[] = { TEXT_PJ64 };

// If you are using PJ64 2.X, go to: Options ► Settings ► Config: ► Memory Size, select 8 MB
u8 text_pj64_2[] = { TEXT_PJ64_2 };

Gfx *geo_display_error_message(u32 callContext, UNUSED struct GraphNode *node, UNUSED u32 unused) {
    if (callContext) {
        if (gDelayForErrorMessage > 0) {
            // Draw color text title.
            print_text(10, 210, "ERROR    Need more memory");

            // Init generic text rendering
            create_dl_ortho_matrix();
            gSPDisplayList(gDisplayListHead++,
                           dl_ia_text_begin); // Init rendering stuff for generic text

            // Set text color to white
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

            print_generic_string(8, 170, text_console_8mb);
            print_generic_string(8, 120, text_pj64);
            print_generic_string(8, 54, text_pj64_2);

            // Cleanup
            gSPDisplayList(gDisplayListHead++,
                           dl_ia_text_end); // Reset back to default render settings.
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        } else {
            gDelayForErrorMessage += 1;
        }
    }

    return 0;
}

// Basic main loop for the error screen. Note that controllers are not enabled here.
void thread5_mem_error_message_loop(UNUSED void *arg) {
    struct LevelCommand *addr;

    setup_game_memory();
    set_vblank_handler(2, &gGameVblankHandler, &gGameVblankQueue, (OSMesg) 1);

    addr = segmented_to_virtual(level_script_entry_error_screen);

    render_init();

    while (1) {
        select_gfx_pool();
        addr = level_script_execute(addr);
        display_and_vsync();
    }
}
#endif
