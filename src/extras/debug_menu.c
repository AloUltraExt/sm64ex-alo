#ifdef DEBUG

#include "sm64.h"
#include "text_strings.h"
#include "gfx_dimensions.h"
#include "seq_ids.h"

#include "audio/external.h"
#include "engine/math_util.h"
#include "game/camera.h"
#include "game/debug.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/mario_misc.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "game/mario_misc.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"

#include "options_menu.h"

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
#endif

extern s8 gShowDebugText;
extern s8 gDebugLevelSelect;
extern s8 gShowProfiler;
extern void try_modify_debug_controls(void);
extern void try_change_debug_page(void);
extern void debug_update_mario_cap(u16 button, s32 flags, u16 capTimer, u16 capMusic);

bool gShowComplexDebugText;
bool gDebugFreeMoveAct;
bool gDebugCapChanger;

const u8 optDebugMenuStr[][32] = {
    { TEXT_OPT_DEBUG },
};

static const u8 optsDebugStr[][64] = {
    { TEXT_OPT_DEBUG0 },
    { TEXT_OPT_DEBUG1 },
    { TEXT_OPT_DEBUG2 },
    { TEXT_OPT_DEBUG3 },
    { TEXT_OPT_DEBUG4 },
    { TEXT_OPT_DEBUG5 },
};

struct Option optsDebug[] = {
    DEF_OPT_TOGGLE( optsDebugStr[0], (bool *) &gShowDebugText ),
    DEF_OPT_TOGGLE( optsDebugStr[1], &gShowComplexDebugText ),
    DEF_OPT_TOGGLE( optsDebugStr[2], (bool *) &gDebugLevelSelect ),
    DEF_OPT_TOGGLE( optsDebugStr[3], &gDebugFreeMoveAct ),
    DEF_OPT_TOGGLE( optsDebugStr[4], &gDebugCapChanger ),
    DEF_OPT_TOGGLE( optsDebugStr[5], (bool *) &gShowProfiler ),
};

struct SubMenu menuDebug = DEF_SUBMENU( optDebugMenuStr[0], optsDebug );

void activate_complex_debug_display(void) {
    if (gShowComplexDebugText) {
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

void set_debug_mario_action(struct MarioState *m) {
    if (gDebugFreeMoveAct) {
        set_debug_free_move_action(m);
    }
    
    if (gDebugCapChanger) {
        set_debug_cap_changer();
    }
}

#endif
