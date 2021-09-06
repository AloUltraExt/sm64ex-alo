#include <stdlib.h>
#include <stdio.h>

#ifdef TARGET_WEB
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include "sm64.h"

#include "game/memory.h"
#include "game/sound_init.h"
#include "audio/external.h"

#include "gfx/gfx_pc.h"

#include "gfx/gfx_opengl.h"
#include "gfx/gfx_direct3d11.h"
#include "gfx/gfx_direct3d12.h"
#include "gfx/gfx_dxgi.h"
#include "gfx/gfx_sdl.h"
#include "gfx/gfx_whb.h"
#include "gfx/gfx_3ds.h"
#include "gfx/gfx_citro3d.h"
#include "gfx/gfx_dummy.h"

#include "audio/audio_api.h"
#include "audio/audio_sdl.h"
#include "audio/audio_null.h"
#include "audio/audio_3ds.h"
#include "audio/audio_3ds_threading.h"

#include "pc_main.h"

#ifdef COMMAND_LINE_OPTIONS
#include "cliopts.h"
#endif

#include "configfile.h"
#include "controller/controller_api.h"
#include "controller/controller_keyboard.h"
#include "controller/controller_touchscreen.h"

#ifdef TARGET_SWITCH
#include "controller/controller_switch.h"
#include "nx_main.h"
#endif

#include "fs/fs.h"

#include "game/game_init.h"
#include "game/main.h"
#include "game/rumble_init.h"

#ifdef DISCORDRPC
#include "pc/discord/discordrpc.h"
#endif

OSMesg gMainReceivedMesg;
OSMesgQueue gSIEventMesgQueue;

s8 gResetTimer;
s8 gNmiResetBarsTimer;
s8 gDebugLevelSelect;
s8 gShowProfiler;
s8 gShowDebugText;

static struct AudioAPI *audio_api;
static struct GfxWindowManagerAPI *wm_api;
static struct GfxRenderingAPI *rendering_api;

extern void gfx_run(Gfx *commands);
extern void thread5_game_loop(void *arg);
extern void create_next_audio_buffer(s16 *samples, u32 num_samples);
void game_loop_one_iteration(void);

void dispatch_audio_sptask(UNUSED struct SPTask *spTask) {
}

void set_vblank_handler(UNUSED s32 index, UNUSED struct VblankHandler *handler, UNUSED OSMesgQueue *queue, UNUSED OSMesg *msg) {
}

static bool inited = false;

#include "game/game_init.h" // for gGlobalTimer
void exec_display_list(struct SPTask *spTask) {
    if (!inited) return;
    gfx_run((Gfx *)spTask->task.t.data_ptr);
}

#ifdef HIGH_FPS_PC
static inline void patch_interpolations(void) {
    extern void mtx_patch_interpolated(void);
    extern void patch_screen_transition_interpolated(void);
    extern void patch_title_screen_scales(void);
    extern void patch_interpolated_dialog(void);
    extern void patch_interpolated_hud(void);
    extern void patch_interpolated_paintings(void);
    extern void patch_interpolated_bubble_particles(void);
    extern void patch_interpolated_snow_particles(void);
    mtx_patch_interpolated();
    patch_screen_transition_interpolated();
    patch_title_screen_scales();
    patch_interpolated_dialog();
    patch_interpolated_hud();
    patch_interpolated_paintings();
    patch_interpolated_bubble_particles();
    patch_interpolated_snow_particles();
}
#endif

#ifdef VERSION_EU
#define SAMPLES_HIGH 656
#define SAMPLES_LOW 640
#else
#define SAMPLES_HIGH 544
#define SAMPLES_LOW 528
#endif

#ifndef TARGET_N3DS
static inline void audio_frame(void) {
    u32 num_audio_samples = audio_api->buffered() < audio_api->get_desired_buffered() ? SAMPLES_HIGH : SAMPLES_LOW;
    static s16 audio_buffer[SAMPLES_HIGH * 2 * 2];
    for (int i = 0; i < 2; i++) {
        create_next_audio_buffer(audio_buffer + i * (num_audio_samples * 2), num_audio_samples);
    }

    audio_api->play((u8 *)audio_buffer, 2 * num_audio_samples * 4);
}
#endif

void produce_one_frame(void) {
    gfx_start_frame();

    change_audio_volumes();

    game_loop_one_iteration();
#ifdef RUMBLE_FEEDBACK
    thread6_rumble_loop(NULL);
#endif
#ifndef TARGET_N3DS
    audio_frame();
#endif
    gfx_end_frame();

#ifdef HIGH_FPS_PC
    gfx_start_frame();
    patch_interpolations();
    exec_display_list(gGfxSPTask);
    gfx_end_frame();
#endif

#if defined(TARGET_N3DS) && !defined(DISABLE_N3DS_AUDIO)
    LightEvent_Wait(&s_event_main);
#endif
}

void audio_shutdown(void) {
    if (audio_api) {
        if (audio_api->shutdown) audio_api->shutdown();
        audio_api = NULL;
    }
}

void game_deinit(void) {
#ifdef DISCORDRPC
    discord_shutdown();
#endif
    configfile_save(configfile_name());
#if defined(TARGET_SWITCH) || !defined(TARGET_PORT_CONSOLE)
    controller_shutdown();
    audio_shutdown();
    gfx_shutdown();
#endif
    inited = false;
}

void game_exit(void) {
#if defined(TARGET_SWITCH) || !defined(TARGET_PORT_CONSOLE)
    game_deinit();
#ifndef TARGET_WEB
    exit(0);
#endif
#endif
}

#ifdef TARGET_WEB
static void em_main_loop(void) {
}

static void request_anim_frame(void (*func)(double time)) {
    EM_ASM(requestAnimationFrame(function(time) {
        dynCall("vd", $0, [time]);
    }), func);
}

static void on_anim_frame(double time) {
    static double target_time;

    time *= 0.03; // milliseconds to frame count (33.333 ms -> 1)

    if (time >= target_time + 10.0) {
        // We are lagging 10 frames behind, probably due to coming back after inactivity,
        // so reset, with a small margin to avoid potential jitter later.
        target_time = time - 0.010;
    }

    for (int i = 0; i < 2; i++) {
        // If refresh rate is 15 Hz or something we might need to generate two frames
        if (time >= target_time) {
            produce_one_frame();
            target_time = target_time + 1.0;
        }
    }

    if (inited) // only continue if the init flag is still set
        request_anim_frame(on_anim_frame);
}
#endif

#ifdef __ANDROID__
#include "platform.h"
extern const char* SDL_AndroidGetInternalStoragePath();
extern const char* SDL_AndroidGetExternalStoragePath();

void move_to_new_dir(char* file) {
    const char *basedir = SDL_AndroidGetExternalStoragePath();
    char original_loc[SYS_MAX_PATH];
    char new_loc[SYS_MAX_PATH];
    snprintf(original_loc, sizeof(original_loc), "%s/%s", basedir, file);
    #ifdef COMMAND_LINE_OPTIONS
    snprintf(new_loc, sizeof(new_loc), "%s/%s/%s", basedir, gCLIOpts.GameDir[0] ? gCLIOpts.GameDir : FS_BASEDIR, file);
    #else
    snprintf(new_loc, sizeof(new_loc), "%s/%s/%s", basedir, FS_BASEDIR, file);
    #endif
    rename(original_loc, new_loc);
}

void move_to_new_dir_user(char* file) {
    const char *olddir = SDL_AndroidGetInternalStoragePath();
    const char *basedir = SDL_AndroidGetExternalStoragePath();
    char original_loc[SYS_MAX_PATH];
    char new_loc[SYS_MAX_PATH];
    snprintf(original_loc, sizeof(original_loc), "%s/%s", basedir, file);
    #ifdef COMMAND_LINE_OPTIONS
    snprintf(new_loc, sizeof(new_loc), "%s/%s/%s", basedir, gCLIOpts.GameDir[0] ? gCLIOpts.GameDir : FS_BASEDIR, file);
    #else
    snprintf(new_loc, sizeof(new_loc), "%s/%s/%s", basedir, FS_BASEDIR, file);
    #endif
    rename(original_loc, new_loc);
}
#endif

void main_func(void) {
#ifdef __ANDROID__
    //Move old stuff to new path
    const char *basedir = SDL_AndroidGetExternalStoragePath();
    char gamedir[SYS_MAX_PATH];
    #ifdef COMMAND_LINE_OPTIONS
    snprintf(gamedir, sizeof(gamedir), "%s/%s", basedir, gCLIOpts.GameDir[0] ? gCLIOpts.GameDir : FS_BASEDIR);
    #else
    snprintf(gamedir, sizeof(gamedir), "%s/%s", basedir, FS_BASEDIR);
    #endif
    if (stat(gamedir, NULL) == -1) {
        mkdir(gamedir, 0770);
    }
    move_to_new_dir("sound");
    move_to_new_dir("gfx");
    move_to_new_dir("base.zip");
#else
    #ifdef COMMAND_LINE_OPTIONS
    const char *gamedir = gCLIOpts.GameDir[0] ? gCLIOpts.GameDir : FS_BASEDIR;
    #else
    const char *gamedir = FS_BASEDIR;
    #endif
#endif

#ifdef COMMAND_LINE_OPTIONS
    const char *userpath = gCLIOpts.SavePath[0] ? gCLIOpts.SavePath : sys_user_path();
#else
    const char *userpath = sys_user_path();
#endif

    fs_init(sys_ropaths, gamedir, userpath);

    #ifndef TARGET_N3DS
    configfile_load(configfile_name());
    #endif

    #ifdef TARGET_WII_U
    configfile_save(configfile_name()); // Mount SD write now
    #endif
    
    #ifdef COMMAND_LINE_OPTIONS
    if (gCLIOpts.FullScreen == 1)
        configWindow.fullscreen = true;
    else if (gCLIOpts.FullScreen == 2)
        configWindow.fullscreen = false;
    #endif

#ifdef USE_SYSTEM_MALLOC
    main_pool_init();
    gGfxAllocOnlyPool = alloc_only_pool_init();
#else

    #ifdef COMMAND_LINE_OPTIONS
    const size_t poolsize = gCLIOpts.PoolSize ? gCLIOpts.PoolSize : DEFAULT_POOL_SIZE;
    #else
    const size_t poolsize = DEFAULT_POOL_SIZE;
    #endif

    u64 *pool = malloc(poolsize);
    if (!pool) sys_fatal("Could not alloc %u bytes for main pool.\n", poolsize);
    main_pool_init(pool, pool + poolsize / sizeof(pool[0]));
#endif

    gEffectsMemoryPool = mem_pool_init(0x4000, MEMORY_POOL_LEFT);

    #if defined(WAPI_SDL1) || defined(WAPI_SDL2)
    wm_api = &gfx_sdl;
    #elif defined(WAPI_DXGI)
    wm_api = &gfx_dxgi;
    #elif defined(WAPI_WHB)
    wm_api = &gfx_whb_window;
    #elif defined(WAPI_3DS)
    wm_api = &gfx_3ds;
    #elif defined(WAPI_DUMMY)
    wm_api = &gfx_dummy_wm_api;
    #else
    #error No window API!
    #endif

    #if defined(RAPI_D3D11)
    rendering_api = &gfx_direct3d11_api;
    # define RAPI_NAME "DirectX 11"
    #elif defined(RAPI_D3D12)
    rendering_api = &gfx_direct3d12_api;
    # define RAPI_NAME "DirectX 12"
    #elif defined(RAPI_GL) || defined(RAPI_GL_LEGACY)
    rendering_api = &gfx_opengl_api;
    # ifdef USE_GLES
    #  define RAPI_NAME "OpenGL ES"
    # else
    #  define RAPI_NAME "OpenGL"
    # endif
    #elif defined(RAPI_WHB)
    rendering_api = &gfx_whb_api;
    # define RAPI_NAME "WHB - GX2"
    #elif defined(RAPI_C3D)
    rendering_api = &gfx_citro3d_api;
    # define RAPI_NAME "3DS - C3D"
    #elif defined(RAPI_DUMMY)
    rendering_api = &gfx_dummy_renderer_api;
    # define RAPI_NAME "DUMMY"
    #else
    #error No rendering API!
    #endif

    char window_title[96] =
    "Super Mario 64 EX (" RAPI_NAME ")"
    ;

    gfx_init(wm_api, rendering_api, window_title);
    #ifndef TARGET_PORT_CONSOLE
    wm_api->set_keyboard_callbacks(keyboard_on_key_down, keyboard_on_key_up, keyboard_on_all_keys_up);
    #endif
    #ifdef TOUCH_CONTROLS
    wm_api->set_touchscreen_callbacks((void *)touch_down, (void *)touch_motion, (void *)touch_up);
    #endif
    
    // TESTING!!!!!!!!!!
    #if defined(AAPI_SDL1) || defined(AAPI_SDL2)
    if (audio_api == NULL && audio_sdl.init()) 
        audio_api = &audio_sdl;
    #endif

    #if defined(AAPI_3DS) && !defined(DISABLE_N3DS_AUDIO)
    if (audio_api == NULL && audio_3ds.init()) {
        audio_api = &audio_3ds;
    }
    #endif

    if (audio_api == NULL) {
        audio_api = &audio_null;
    }

    audio_init();
    sound_init();

    thread5_game_loop(NULL);

    inited = true;

#ifdef EXTERNAL_DATA
    // precache data if needed
    if (configPrecacheRes) {
        fprintf(stdout, "precaching data\n");
        fflush(stdout);
        gfx_precache_textures();
    }
#endif

#ifdef DISCORDRPC
    discord_init();
#endif

#if defined(TARGET_WEB)
    emscripten_set_main_loop(em_main_loop, 0, 0);
    request_anim_frame(on_anim_frame);
#elif defined(TARGET_N3DS)
    wm_api->main_loop(produce_one_frame);
    audio_api->shutdown();
#else

    #if defined(TARGET_WII_U)
    while (whb_window_is_running()) {
    #elif defined(TARGET_SWITCH)
    disableBoostMode();
    while (appletMainLoop()) {
    #else
    while (true) {
    #endif
        wm_api->main_loop(produce_one_frame);
#ifdef DISCORDRPC
        discord_update_rich_presence();
#endif
    }
#endif
}

#ifdef TARGET_PORT_CONSOLE
int main(UNUSED int argc, UNUSED char *argv[]) {
#ifdef TARGET_SWITCH
    enableBoostMode();
    initNX();
#endif
    main_func();
#ifdef TARGET_SWITCH
    exitNX();
#endif
    return 0;
}
#else
int main(int argc, char *argv[]) {
#ifdef COMMAND_LINE_OPTIONS
    parse_cli_opts(argc, argv);
    set_cli_opts();
#endif
    main_func();
    return 0;
}
#endif
