#ifndef DEBUG_MENU_OPT_H
#define DEBUG_MENU_OPT_H

#include "sm64.h"
#include "gfx_dimensions.h"
#include "engine/math_util.h"
#include "audio/external.h"
#include "game/camera.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/mario_misc.h"
#include "game/print.h"
#include "game/segment2.h"
#include "game/save_file.h"

#include "options_menu.h"

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
#endif

extern const u8 optDebugMenuStr[][32];

struct DebugOptList {
    bool    SimpleDbgTxt;
    bool    ComplexDbgTxt;
    bool    LevelSelect;
    bool    FreeMoveAct;
    bool    CapChanger;
    bool    ShowProfiler;
    bool    ShowFps;
};

extern struct DebugOptList DebugOpt;

extern struct SubMenu menuDebug;

void activate_complex_debug_display(void);
void set_debug_main_action(void);
void set_debug_mario_action(struct MarioState *m);

#endif // DEBUG_MENU_OPT_H
