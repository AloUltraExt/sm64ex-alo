#ifdef EXT_DEBUG_MENU

#include <stdio.h>

#include "sm64.h"
#include "text_strings.h"
#include "gfx_dimensions.h"
#include "seq_ids.h"

#include "audio/external.h"
#include "engine/math_util.h"
#include "game/camera.h"
#include "game/debug.h"
#include "game/game_init.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/mario_misc.h"
#include "game/moving_texture.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/print.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "game/sound_init.h"
#include "game/ingame_menu.h"

#include "options_menu.h"
#include "debug_menu.h"

extern s8 gShowDebugText;
extern s8 gDebugLevelSelect;
extern s8 gShowProfiler;
extern s16 gMenuMode;
extern s8 gMenuState;
extern struct CreditsEntry sCreditsSequence[];
extern void try_modify_debug_controls(void);
extern void try_change_debug_page(void);
extern void debug_update_mario_cap(u16 button, s32 flags, u16 capTimer, u16 capMusic);
extern void set_play_mode(s16 playMode);

struct DebugOptList DebugOpt;

const u8 optDebugMenuStr[][32] = {
    { TEXT_OPT_DEBUG },
    { TEXT_OPT_DEBUG_WARP },
};

static const u8 optsDebugStr[][64] = {
    { TEXT_OPT_DEBUG0 },
    { TEXT_OPT_DEBUG1 },
    { TEXT_OPT_DEBUG2 },
    { TEXT_OPT_DEBUG3 },
    { TEXT_OPT_DEBUG4 },
    { TEXT_OPT_DEBUG5 },
    { TEXT_OPT_DEBUG6 },
    { TEXT_OPT_DEBUG7 },
};

static const u8 optsDebugWarpDestStr[][64] = {
    { TEXT_DEBUG_WARP0 },
    { TEXT_DEBUG_WARP1 },
    { TEXT_DEBUG_WARP2 },
    { TEXT_DEBUG_WARP3 },
};

static void force_quit_pause_debug(void) {
    level_set_transition(0, NULL);
    optmenu_open = 0;
    gMenuMode = -1;
    gMenuState = 0;
    raise_background_noise(1);
    gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
    set_play_mode(0);
}

static void opt_debug_warp_0(UNUSED struct Option *self, s32 arg) {
    if (!arg) {
        force_quit_pause_debug();
        level_trigger_warp(gMarioState, WARP_OP_CREDITS_START);
    }
}

static void opt_debug_warp_1(UNUSED struct Option *self, s32 arg) {
    if (!arg) {
        force_quit_pause_debug();
        // ensure medium water level in WDW credits cutscene
        gPaintingMarioYEntry = 1500.0f;
        // Define credits sequence (if not then crashes)
        if (gCurrCreditsEntry == NULL) {
            gCurrCreditsEntry = &sCreditsSequence[0];
        }
        // Play music (sounds off but it's better than no music)
        seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
        play_cutscene_music(SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_CREDITS));

        level_trigger_warp(gMarioState, WARP_OP_CREDITS_NEXT);
    }
}

static void opt_debug_warp_2(UNUSED struct Option *self, s32 arg) {
    if (!arg) {
        force_quit_pause_debug();
        // Set Course and Act Num to avoid string crashes
        gLastCompletedCourseNum = gCurrCourseNum;
        gLastCompletedStarNum = gCurrActNum;

        level_trigger_warp(gMarioState, WARP_OP_STAR_EXIT);
    }
}

static void opt_debug_warp_3(UNUSED struct Option *self, s32 arg) {
    if (!arg) {
        force_quit_pause_debug();
        level_trigger_warp(gMarioState, WARP_OP_DEATH);
    }
}

static struct Option optDebugWarpDest[] = {
    DEF_OPT_BUTTON( optsDebugWarpDestStr[0], opt_debug_warp_0 ),
    DEF_OPT_BUTTON( optsDebugWarpDestStr[1], opt_debug_warp_1 ),
    DEF_OPT_BUTTON( optsDebugWarpDestStr[2], opt_debug_warp_2 ),
    DEF_OPT_BUTTON( optsDebugWarpDestStr[3], opt_debug_warp_3 ),
};

static struct SubMenu menuDebugWarpDest = DEF_SUBMENU( optDebugMenuStr[1], optDebugWarpDest );

struct Option optsDebug[] = {
    DEF_OPT_TOGGLE( optsDebugStr[0], &DebugOpt.SimpleDbgTxt ),
    DEF_OPT_TOGGLE( optsDebugStr[1], &DebugOpt.ComplexDbgTxt ),
    DEF_OPT_TOGGLE( optsDebugStr[2], &DebugOpt.LevelSelect ),
    DEF_OPT_TOGGLE( optsDebugStr[3], &DebugOpt.FreeMoveAct ),
    DEF_OPT_TOGGLE( optsDebugStr[4], &DebugOpt.CapChanger ),
    DEF_OPT_TOGGLE( optsDebugStr[5], &DebugOpt.ShowProfiler ),
    DEF_OPT_TOGGLE( optsDebugStr[6], &DebugOpt.ShowFps ),
    DEF_OPT_SUBMENU( optsDebugStr[7], &menuDebugWarpDest ),
};

struct SubMenu menuDebug = DEF_SUBMENU( optDebugMenuStr[0], optsDebug );

void activate_complex_debug_display(void) {
    if (DebugOpt.ComplexDbgTxt) {
        gDebugInfoFlags |= 0xFF; // DEBUG_INFO_FLAG_ALL
        try_modify_debug_controls();
        try_change_debug_page();
    } else {
        gDebugInfoFlags = ~0xFF;
    }
}

void set_debug_free_move_action(struct MarioState *m) {
    if (m->controller->buttonPressed & L_TRIG) {
        set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
    }
}

void set_debug_cap_changer(void) {
    debug_update_mario_cap(CONT_LEFT, MARIO_WING_CAP, 1800, SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
    debug_update_mario_cap(CONT_UP, MARIO_METAL_CAP, 600, SEQUENCE_ARGS(4, SEQ_EVENT_METAL_CAP));
    debug_update_mario_cap(CONT_RIGHT, MARIO_VANISH_CAP, 600, SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
}

#ifdef TARGET_N64
#include "include/PR/os.h"

#define FRAMETIME_COUNT 30

OSTime frameTimes[FRAMETIME_COUNT];
u8 curFrameTimeIndex = 0;

void debug_calculate_and_print_fps(void) {
    f32 fps;
    OSTime newTime = osGetTime();
    OSTime oldTime = frameTimes[curFrameTimeIndex];
    frameTimes[curFrameTimeIndex] = newTime;

    curFrameTimeIndex++;
    if (curFrameTimeIndex >= FRAMETIME_COUNT)
        curFrameTimeIndex = 0;

    fps = ((f32)FRAMETIME_COUNT * 1000000.0f) / (s32)OS_CYCLES_TO_USEC(newTime - oldTime);

    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), 184, "FPS %d", (s16) fps);
}
#else
static OSTime gLastOSTime = 0;

void debug_calculate_and_print_fps(void) {
    f32 fps;
#ifdef HIGH_FPS_PC
    f32 multiplier = 2.0f;
#else
    f32 multiplier = 1.0f;
#endif

    OSTime newTime = osGetTime();
    fps = multiplier * 1000000.0f / (newTime - gLastOSTime);

    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), 184, "FPS %d", (s16) fps);
    gLastOSTime = newTime;
}
#endif

void set_debug_mario_action(struct MarioState *m) {
    if (DebugOpt.FreeMoveAct) {
        set_debug_free_move_action(m);
    }

    if (DebugOpt.CapChanger) {
        set_debug_cap_changer();
    }
}

void set_debug_main_action(void) {
    if (DebugOpt.ShowFps) {
        debug_calculate_and_print_fps();
    }

    gShowDebugText = DebugOpt.SimpleDbgTxt;
    gDebugLevelSelect = DebugOpt.LevelSelect;
    gShowProfiler = DebugOpt.ShowProfiler;
}

#endif
