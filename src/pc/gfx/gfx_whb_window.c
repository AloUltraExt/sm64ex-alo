#ifdef WAPI_WHB

#include <macros.h>

#include <coreinit/foreground.h>
#include <gx2/display.h>
#include <gx2/event.h>
#include <gx2/swap.h>
#include <proc_ui/procui.h>
#include <sndcore2/core.h>

#include <whb/crash.h>
#include <whb/gfx.h>
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>

#include "gfx_window_manager_api.h"
#include "gfx_whb.h"
#include "../pc_main.h"

static bool is_running;
uint32_t window_height = 0;

void gfx_whb_window_proc_ui_save_callback(void) {
    OSSavesDone_ReadyToRelease();
}

uint32_t gfx_whb_window_proc_ui_exit_callback(UNUSED void* data) {
    WHBLogPrint("Exit callback");
    is_running = false;

    game_deinit();

    whb_free_vbo();
    whb_free();

    controller_shutdown();
    AXQuit();
    gfx_shutdown();

    WHBLogCafeDeinit();
    WHBLogUdpDeinit();

    return 0;
}

static void gfx_whb_window_init(UNUSED const char *game_name) {
    ProcUIInit(&gfx_whb_window_proc_ui_save_callback);
    ProcUIRegisterCallback(PROCUI_CALLBACK_EXIT, &gfx_whb_window_proc_ui_exit_callback, NULL, 0);

    is_running = true;

    WHBLogCafeInit();
    WHBLogUdpInit();
    WHBInitCrashHandler();

    WHBGfxInit();

#ifdef HIGH_FPS_PC
    GX2SetSwapInterval(1);
#else
    GX2SetSwapInterval(2);
#endif
}

static void gfx_whb_window_main_loop(void (*run_one_game_iter)(void)) {
    run_one_game_iter();
}

static void gfx_whb_window_get_dimensions(uint32_t *width, uint32_t *height) {
    switch (GX2GetSystemTVScanMode()) {
        case GX2_TV_SCAN_MODE_480I:
        case GX2_TV_SCAN_MODE_480P:
            *width = 854;
            *height = 480; window_height = 480;
            break;
        case GX2_TV_SCAN_MODE_1080I:
        case GX2_TV_SCAN_MODE_1080P:
            *width = 1920;
            *height = 1080; window_height = 1080;
            break;
        case GX2_TV_SCAN_MODE_720P:
        default:
            *width = 1280;
            *height = 720; window_height = 720;
            break;
    }
}

static void gfx_whb_window_handle_events(void) {
}

static bool gfx_whb_window_start_frame(void) {
    if (!is_running) {
        return false;
    } else {
        GX2WaitForFlip();
        return true;
    }
}

static void gfx_whb_window_swap_buffers_begin(void) {
    WHBGfxFinishRender();
    whb_free_vbo();
}

static void gfx_whb_window_swap_buffers_end(void) {
}

static double gfx_whb_window_get_time(void) {
    return 0.0;
}

static void gfx_whb_window_shutdown(void) {
}

bool whb_window_is_running(void) {
    if (!is_running) {
        return false;
    }

    ProcUIStatus status = ProcUIProcessMessages(true);

    switch (status) {
        case PROCUI_STATUS_EXITING:
            ProcUIShutdown();
            is_running = false;
            return false;
        case PROCUI_STATUS_RELEASE_FOREGROUND:
            ProcUIDrawDoneRelease();
            break;
        case PROCUI_STATUS_IN_BACKGROUND:
        case PROCUI_STATUS_IN_FOREGROUND:
            break;
    }
    return true;
}

struct GfxWindowManagerAPI gfx_whb_window = {
    gfx_whb_window_init,
    gfx_whb_window_main_loop,
    gfx_whb_window_get_dimensions,
    gfx_whb_window_handle_events,
    gfx_whb_window_start_frame,
    gfx_whb_window_swap_buffers_begin,
    gfx_whb_window_swap_buffers_end,
    gfx_whb_window_get_time,
    gfx_whb_window_shutdown
};

#endif
