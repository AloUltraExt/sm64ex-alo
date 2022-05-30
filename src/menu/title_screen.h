#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "config.h"

extern char gLevelSelectStageNames[][16];

enum LevelScriptIntroArgs {
    LVL_INTRO_PLAY_ITS_A_ME_MARIO,
    LVL_INTRO_REGULAR,
    LVL_INTRO_GAME_OVER,
    LVL_INTRO_LEVEL_SELECT
};

#if ZELDA_STYLE_LEVEL_SELECT
#include "extras/redone/title_screen.inc.h"
#endif

s32 lvl_intro_update(s16 arg, UNUSED s32 unusedArg);

#endif // TITLE_SCREEN_H
