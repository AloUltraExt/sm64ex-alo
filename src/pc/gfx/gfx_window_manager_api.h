#ifndef GFX_WINDOW_MANAGER_API_H
#define GFX_WINDOW_MANAGER_API_H

#include <stdint.h>
#include <stdbool.h>

#include "gfx_defines.h"

// special value for window position that signifies centered position
#define WAPI_WIN_CENTERPOS 0xFFFFFFFF

typedef bool (*kb_callback_t)(int code); // scancode

struct GfxWindowManagerAPI {
#ifdef LEGACY_GFX_WIDOW_API
    void (*init)(const char *window_title);
#else
    void (*init)(const char* game_name, bool start_in_fullscreen, uint32_t width, uint32_t height);
#endif
#ifdef LEGACY_GFX_WIDOW_API // pretty sure these are the same
#ifndef TARGET_PORT_CONSOLE
    void (*set_keyboard_callbacks)(kb_callback_t on_key_down, kb_callback_t on_key_up, void (*on_all_keys_up)(void));
#endif
#else
    void (*set_keyboard_callbacks)(bool (*on_key_down)(int scancode), bool (*on_key_up)(int scancode),
                                   void (*on_all_keys_up)(void));
#endif
    //void (*set_fullscreen_changed_callback)(void (*on_fullscreen_changed)(bool is_now_fullscreen)); // config fullscreen replaces it
    //void (*set_fullscreen)(bool enable); // config fullscreen replaces it
    //void (*set_cursor_visibility)(bool visible); // controller_mouse.c takes care of it
    void (*main_loop)(void (*run_one_game_iter)(void));
    void (*get_dimensions)(uint32_t* width, uint32_t* height);
    void (*handle_events)(void);
    bool (*start_frame)(void);
    void (*swap_buffers_begin)(void);
    void (*swap_buffers_end)(void);
    double (*get_time)(void); // For debug
#ifndef LEGACY_GFX_WIDOW_API // TODO: Maybe limit this to non TARGET_PORT_CONSOLE?
    void (*set_target_fps)(int fps);
    void (*set_maximum_frame_latency)(int latency);
    float (*get_detected_hz)(void);
    const char* (*get_key_name)(int scancode);
#else
    void (*shutdown)(void); // modern render doesn't have this, closes window but game still runs
#endif
};

#endif
