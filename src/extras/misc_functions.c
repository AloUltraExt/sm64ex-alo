#include <ultra64.h>

#include "sm64.h"
#include "gfx_dimensions.h"
#include "engine/math_util.h"
#include "audio/external.h"
#include "game/camera.h"
#include "game/level_update.h"
#include "game/print.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "game/mario_misc.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"

#include "options_menu.h"

#ifndef TARGET_N64
#include "pc/configfile.h"
#endif

#ifdef COMMAND_LINE_OPTIONS
#include "pc/cliopts.h"
#endif

#define SM64_KEY_COMBO (Z_TRIG | START_BUTTON | L_CBUTTONS | R_CBUTTONS)

s16 gSkipIntroKeyCombo = FALSE;

u8 game_key_combo_triggered(void) {   
    if (gPlayer1Controller->buttonDown == SM64_KEY_COMBO) {
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        return TRUE;
    }

    return FALSE;
}

// ifdef hell but it does the job
u8 should_intro_be_skipped(void) {
    return save_file_exists(gCurrSaveFileNum - 1) || gSkipIntroKeyCombo == TRUE
#ifndef TARGET_N64
#ifdef COMMAND_LINE_OPTIONS
    || gCLIOpts.SkipIntro == TRUE
#endif
    || configSkipIntro == TRUE
#endif
    ;
}
