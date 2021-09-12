#ifdef EXT_OPTIONS_MENU

#include "sm64.h"
#include "text_strings.h"
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
#include "draw_utils.h"

#include "pc/configfile.h"

#ifndef TARGET_N64
#include "pc/pc_main.h"
#include "pc/controller/controller_api.h"

#include <stdbool.h>
#include "../../include/libc/stdlib.h"
#endif

#ifdef BETTERCAMERA
#include "bettercamera.h"
#endif

#ifdef CHEATS_ACTIONS
#include "cheats.h"
#endif

#ifdef DEBUG
#include "debug_menu.h"
#endif

u8 optmenu_open = 0;

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
static u8 optmenu_binding = 0;
static u8 optmenu_bind_idx = 0;
#endif

/* Keeps track of how many times the user has pressed L while in the options menu, so cheats can be unlocked */
static s32 l_counter = 0;

// How to add stuff:
// strings: add them to include/text_strings.h.in
//          and to optMainStr[] / opts*Str[]
// options: add them to the relevant options list
// menus:   add a new submenu definition and a new
//          option to the optsMain list

static const u8 toggleStr[][16] = {
    { TEXT_OPT_DISABLED },
    { TEXT_OPT_ENABLED },
};

static const u8 optSmallStr[][32] = {
    { TEXT_OPT_BUTTON1 },
    { TEXT_OPT_BUTTON2 },
    { TEXT_OPT_L_HIGHLIGHT },
    { TEXT_OPT_R_HIGHLIGHT },
};

static const u8 optMainStr[][32] = {
    { TEXT_OPT_OPTIONS },
    { TEXT_OPT_CONTROLS },
    { TEXT_OPT_VIDEO },
    { TEXT_OPT_AUDIO },
    { TEXT_OPT_SETTINGS },
    { TEXT_EXIT_GAME },
};

#ifndef TARGET_N64
static const u8 optsVideoStr[][32] = {
    { TEXT_OPT_FSCREEN },
    { TEXT_OPT_TEXFILTER },
    { TEXT_OPT_NEAREST },
    { TEXT_OPT_LINEAR },
    { TEXT_OPT_RESETWND },
    { TEXT_OPT_VSYNC },
    { TEXT_OPT_AUTO },
    { TEXT_OPT_APPLY },
};
#endif

static const u8 optsAudioStr[][32] = {
    { TEXT_OPT_MVOLUME },
    { TEXT_OPT_MUSVOLUME },
    { TEXT_OPT_SFXVOLUME },
    { TEXT_OPT_ENVVOLUME },
};

static const u8 optsSettingsStr[][32] = {
    { TEXT_OPT_HUD },
    { TEXT_OPT_MOUSE },
};

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
static const u8 optBindStr[][32] = {
    { TEXT_OPT_UNBOUND },
    { TEXT_OPT_PRESSKEY },
    { TEXT_BIND_A },
    { TEXT_BIND_B },
    { TEXT_BIND_START },
    { TEXT_BIND_L },
    { TEXT_BIND_R },
    { TEXT_BIND_Z },
    { TEXT_BIND_C_UP },
    { TEXT_BIND_C_DOWN },
    { TEXT_BIND_C_LEFT },
    { TEXT_BIND_C_RIGHT },
    { TEXT_BIND_D_UP },
    { TEXT_BIND_D_DOWN },
    { TEXT_BIND_D_LEFT },
    { TEXT_BIND_D_RIGHT },
    { TEXT_BIND_UP },
    { TEXT_BIND_DOWN },
    { TEXT_BIND_LEFT },
    { TEXT_BIND_RIGHT },
    { TEXT_OPT_DEADZONE },
    { TEXT_OPT_RUMBLE },
};
#endif

#ifndef TARGET_N64
static const u8 *filterChoices[] = {
    optsVideoStr[2],
    optsVideoStr[3],
};
#endif

/* button action functions */

#ifndef TARGET_N64
static void optmenu_act_exit(UNUSED struct Option *self, s32 arg) {
    if (!arg) game_exit(); // only exit on A press and not directions
}

static void optvideo_reset_window(UNUSED struct Option *self, s32 arg) {
    if (!arg) {
        // Restrict reset to A press and not directions
        configWindow.reset = true;
        configWindow.settings_changed = true;
    }
}

static void optvideo_apply(UNUSED struct Option *self, s32 arg) {
    if (!arg) configWindow.settings_changed = true;
}
#endif

/* submenu option lists */

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
static struct Option optsControls[] = {
    DEF_OPT_BIND( optBindStr[ 2], configKeyA ),
    DEF_OPT_BIND( optBindStr[ 3], configKeyB ),
    DEF_OPT_BIND( optBindStr[ 4], configKeyStart ),
    DEF_OPT_BIND( optBindStr[ 5], configKeyL ),
    DEF_OPT_BIND( optBindStr[ 6], configKeyR ),
    DEF_OPT_BIND( optBindStr[ 7], configKeyZ ),
    DEF_OPT_BIND( optBindStr[ 8], configKeyCUp ),
    DEF_OPT_BIND( optBindStr[ 9], configKeyCDown ),
    DEF_OPT_BIND( optBindStr[10], configKeyCLeft ),
    DEF_OPT_BIND( optBindStr[11], configKeyCRight ),
    DEF_OPT_BIND( optBindStr[12], configKeyDUp ),
    DEF_OPT_BIND( optBindStr[13], configKeyDDown ),
    DEF_OPT_BIND( optBindStr[14], configKeyDLeft ),
    DEF_OPT_BIND( optBindStr[15], configKeyDRight ),
    DEF_OPT_BIND( optBindStr[16], configKeyStickUp ),
    DEF_OPT_BIND( optBindStr[17], configKeyStickDown ),
    DEF_OPT_BIND( optBindStr[18], configKeyStickLeft ),
    DEF_OPT_BIND( optBindStr[19], configKeyStickRight ),
    // max deadzone is 31000; this is less than the max range of ~32768, but this
    // way, the player can't accidentally lock themselves out of using the stick
    DEF_OPT_SCROLL( optBindStr[20], &configStickDeadzone, 0, 100, 1 ),
    DEF_OPT_SCROLL( optBindStr[21], &configRumbleStrength, 0, 100, 1)
};
#endif

#ifndef TARGET_N64
static struct Option optsVideo[] = {
#ifndef TARGET_PORT_CONSOLE
    DEF_OPT_TOGGLE( optsVideoStr[0], &configWindow.fullscreen ),
    #ifndef DISABLE_VSYNC
    DEF_OPT_TOGGLE( optsVideoStr[5], &configWindow.vsync ),
    #endif
#endif
    DEF_OPT_CHOICE( optsVideoStr[1], &configFiltering, filterChoices ),
#if !defined(TARGET_PORT_CONSOLE) && !defined(TARGET_ANDROID)
    DEF_OPT_BUTTON( optsVideoStr[4], optvideo_reset_window ),
#endif
    DEF_OPT_BUTTON( optsVideoStr[6], optvideo_apply ),
};
#endif

static struct Option optsAudio[] = {
    DEF_OPT_SCROLL( optsAudioStr[0], &configMasterVolume, 0, MAX_VOLUME, 1 ),
    DEF_OPT_SCROLL( optsAudioStr[1], &configMusicVolume, 0, MAX_VOLUME, 1),
    DEF_OPT_SCROLL( optsAudioStr[2], &configSfxVolume, 0, MAX_VOLUME, 1),
    DEF_OPT_SCROLL( optsAudioStr[3], &configEnvVolume, 0, MAX_VOLUME, 1),
};

static struct Option optsSettings[] = {
    DEF_OPT_TOGGLE( optsSettingsStr[0], &configHUD ),
#if !defined(TARGET_N64) && defined(MOUSE_ACTIONS)
    DEF_OPT_TOGGLE( optsSettingsStr[1], &configMouse ),
#endif
};

/* submenu definitions */

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
static struct SubMenu menuControls = DEF_SUBMENU( optMainStr[1], optsControls );
#endif

#ifndef TARGET_N64
static struct SubMenu menuVideo    = DEF_SUBMENU( optMainStr[2], optsVideo );
#endif

static struct SubMenu menuAudio    = DEF_SUBMENU( optMainStr[3], optsAudio );
static struct SubMenu menuSettings = DEF_SUBMENU( optMainStr[4], optsSettings );

/* main options menu definition */

static struct Option optsMain[] = {
#ifdef BETTERCAMERA
    DEF_OPT_SUBMENU( optsCameraStr[0], &menuCamera ),
#endif

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
    DEF_OPT_SUBMENU( optMainStr[1], &menuControls ),
#endif

#ifndef TARGET_N64
    DEF_OPT_SUBMENU( optMainStr[2], &menuVideo ),
#endif

    DEF_OPT_SUBMENU( optMainStr[3], &menuAudio ),
    DEF_OPT_SUBMENU( optMainStr[4], &menuSettings ),

#ifdef DEBUG
    // NOTE: always keep cheats the last option here because of the half-assed way I toggle them
    DEF_OPT_SUBMENU( optDebugMenuStr[0], &menuDebug ),
#endif

#if !defined(TARGET_N64) && (defined(TARGET_SWITCH) || !defined(TARGET_PORT_CONSOLE))
    DEF_OPT_BUTTON ( optMainStr[5], optmenu_act_exit ),
#endif

#ifdef CHEATS_ACTIONS
    // NOTE: always keep cheats the last option here because of the half-assed way I toggle them
    DEF_OPT_SUBMENU( optCheatMenuStr[0], &menuCheats ),
#endif
};

static struct SubMenu menuMain = DEF_SUBMENU( optMainStr[0], optsMain );

/* implementation */

static s32 optmenu_option_timer = 0;
static u8 optmenu_hold_count = 0;

static struct SubMenu *currentMenu = &menuMain;

static inline s32 wrap_add(s32 a, const s32 b, const s32 min, const s32 max) {
    a += b;
    if (a < min) a = max - (min - a) + 1;
    else if (a > max) a = min + (a - max) - 1;
    return a;
}

static void uint_to_hex(u32 num, u8 *dst) {
    u8 places = 4;
    while (places--) {
        const u32 digit = num & 0xF;
        dst[places] = digit;
        num >>= 4;
    }
    dst[4] = DIALOG_CHAR_TERMINATOR;
}

static void optmenu_draw_text(s16 x, s16 y, const u8 str[], u8 col) {
    u8 textX = get_str_x_pos_from_center(x, (u8 *) str, 10.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string(textX+1, y-1, str);
    if (col == 0) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 255, 32, 32, 255);
    }
    print_generic_string(textX, y, str);
}

// TODO: Fix the hardcoded values
static void optmenu_draw_opt_scroll(const struct Option *opt, s16 i) {
    s16 maxvar, minvar;
    maxvar = opt->scrMax - opt->scrMin;
    minvar = *opt->uval - opt->scrMin;

    // Grey bar
    ext_print_quad_rect(96,111+(32*i)-(currentMenu->scroll*32),224,117+(32*i)-(currentMenu->scroll*32),0x80,0x80,0x80, 0xFF);
    // White bar
    ext_print_quad_rect(96,111+(32*i)-(currentMenu->scroll*32),96+(((f32)minvar/maxvar)*128),117+(32*i)-(currentMenu->scroll*32),0xFF,0xFF,0xFF, 0xFF);
    // Red middle bar
    ext_print_quad_rect(94+(((f32)minvar/maxvar)*128),109+(32*i)-(currentMenu->scroll*32),98+(((f32)minvar/maxvar)*128),119+(32*i)-(currentMenu->scroll*32),0xFF,0x0,0x0, 0xFF);
    // To fix strings
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
}

static void optmenu_draw_opt(const struct Option *opt, s16 x, s16 y, u8 sel, s16 iScrl) {

    u8 buf[32] = { 0 };

    if (opt->type == OPT_SUBMENU || opt->type == OPT_BUTTON)
        y -= 6;

    optmenu_draw_text(x, y, opt->label, sel);

    switch (opt->type) {
        case OPT_TOGGLE:
            optmenu_draw_text(x, y-13, toggleStr[(int)*opt->bval], sel);
            break;

        case OPT_CHOICE:
            optmenu_draw_text(x, y-13, opt->choices[*opt->uval], sel);
            break;

        case OPT_SCROLL:
            int_to_str(*opt->uval, buf);
            optmenu_draw_text(x, y-13, buf, sel);
            optmenu_draw_opt_scroll(opt, iScrl);
            break;

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
        case OPT_BIND:
            x = 112;
            for (u8 i = 0; i < MAX_BINDS; ++i, x += 48) {
                const u8 white = (sel && (optmenu_bind_idx == i));
                // TODO: button names
                if (opt->uval[i] == VK_INVALID) {
                    if (optmenu_binding && white)
                        optmenu_draw_text(x, y-13, optBindStr[1], 1);
                    else
                        optmenu_draw_text(x, y-13, optBindStr[0], white);
                } else {
                    uint_to_hex(opt->uval[i], buf);
                    optmenu_draw_text(x, y-13, buf, white);
                }
            }
            break;
#endif

        default: break;
    };
}

static void optmenu_opt_change(struct Option *opt, s32 val) {
    switch (opt->type) {
        case OPT_TOGGLE:
            *opt->bval = !*opt->bval;
            break;

        case OPT_CHOICE:
            *opt->uval = wrap_add(*opt->uval, val, 0, opt->numChoices - 1);
            break;

        case OPT_SCROLL:
            *opt->uval = wrap_add(*opt->uval, opt->scrStep * val, opt->scrMin, opt->scrMax);
            break;

        case OPT_SUBMENU:
            opt->nextMenu->prev = currentMenu;
            currentMenu = opt->nextMenu;
            break;

        case OPT_BUTTON:
            if (opt->actionFn)
                opt->actionFn(opt, val);
            break;

#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
        case OPT_BIND:
            if (val == 0xFF) {
                // clear the bind
                opt->uval[optmenu_bind_idx] = VK_INVALID;
            } else if (val == 0) {
                opt->uval[optmenu_bind_idx] = VK_INVALID;
                optmenu_binding = 1;
                controller_get_raw_key(); // clear the last key, which is probably A
            } else {
                optmenu_bind_idx = wrap_add(optmenu_bind_idx, val, 0, MAX_BINDS - 1);
            }
            break;
#endif

        default: break;
    }
}

static inline s16 get_hudstr_centered_x(const s16 sx, const u8 *str) {
    const u8 *chr = str;
    s16 len = 0;
    while (*chr != GLOBAR_CHAR_TERMINATOR) ++chr, ++len;
    return sx - len * 6; // stride is 12
}

//Options menu
void optmenu_draw(void) {
    u8 i;
    s16 scroll;
    s16 scrollpos;
    f32 sinpos;

    ext_print_quad_rect(47, 83, 281, 84, 0x0, 0x0, 0x0, 0xFF);
    ext_print_quad_rect(47, 218, 281, 219, 0x0, 0x0, 0x0, 0xFF);
    ext_print_quad_rect(47, 83, 48, 219, 0x0, 0x0, 0x0, 0xFF);
    ext_print_quad_rect(280, 83, 281, 219, 0x0, 0x0, 0x0, 0xFF);
    ext_print_quad_rect(271, 83, 272, 219, 0x0, 0x0, 0x0, 0xFF);

    ext_print_quad_rect(48, 84, 272, 218, 0x0, 0x0, 0x0, 0x50);

    const s16 labelX = get_hudstr_centered_x(160, currentMenu->label);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_hud_lut_string(HUD_LUT_GLOBAL, labelX, 40, currentMenu->label);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);

    if (currentMenu->numOpts > 4)
    {
        ext_print_quad_rect(272, 84, 280, 218, 0x80, 0x80, 0x80, 0xFF);
        scrollpos = (62)*((f32)currentMenu->scroll/(currentMenu->numOpts-4));
        ext_print_quad_rect(272, 84 + scrollpos,280,156+scrollpos,0xFF,0xFF,0xFF, 0xFF);
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 80, SCREEN_WIDTH, SCREEN_HEIGHT);
    for (i = 0; i < currentMenu->numOpts; i++) {
        scroll = 140-(32*i)+(currentMenu->scroll*32);
        // FIXME: just start from the first visible option bruh
        if (scroll <= 140 && scroll > 32)
            optmenu_draw_opt(&currentMenu->opts[i], 160, scroll, (currentMenu->select == i), i);
    }

    sinpos = sins(gGlobalTimer*5000)*4;
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_generic_string(80 - sinpos, 132 - (32 * (currentMenu->select - currentMenu->scroll)), optSmallStr[2]);
    print_generic_string(232 + sinpos, 132 - (32 * (currentMenu->select - currentMenu->scroll)), optSmallStr[3]);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

//This has been separated for interesting reasons. Don't question it.
void optmenu_draw_prompt(void) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    optmenu_draw_text(264, 212, optSmallStr[optmenu_open], 0);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void optmenu_toggle(void) {
    if (optmenu_open == 0) {
        #ifndef nosound
        play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
        #endif

#ifdef CHEATS_ACTIONS
        // HACK: hide the last option in main if cheats are disabled
        menuMain.numOpts = sizeof(optsMain) / sizeof(optsMain[0]);
        if (!Cheats.EnableCheats) {
            menuMain.numOpts--;
            if (menuMain.select >= menuMain.numOpts) {
                menuMain.select = 0; // don't bother
                menuMain.scroll = 0;
            }
        }
#endif

        currentMenu = &menuMain;
        optmenu_open = 1;
        /* Resets l_counter to 0 every time the options menu is open */
        l_counter = 0;
    } else {
        #ifndef nosound
        play_sound(SOUND_MENU_MARIO_CASTLE_WARP2, gGlobalSoundSource);
        #endif
        optmenu_open = 0;
#ifndef TARGET_N64
        controller_reconfigure(); // rebind using new config values
        configfile_save(configfile_name());
#endif
    }
}

void optmenu_check_buttons(void) {
#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
    if (optmenu_binding) {
        u32 key = controller_get_raw_key();
        if (key != VK_INVALID) {
            #ifndef nosound
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            #endif
            currentMenu->opts[currentMenu->select].uval[optmenu_bind_idx] = key;
            optmenu_binding = 0;
            optmenu_option_timer = 12;
        }
        return;
    }
#endif

    if (gPlayer1Controller->buttonPressed & R_TRIG) {
        optmenu_toggle();
    }

    /* Enables cheats if the user press the L trigger 3 times while in the options menu. Also plays a sound. */
#ifdef CHEATS_ACTIONS
    if ((gPlayer1Controller->buttonPressed & L_TRIG) && !Cheats.EnableCheats) {
        if (l_counter == 2) {
                Cheats.EnableCheats = true;
                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                l_counter = 0;
        } else {
            l_counter++;
        }
    }
#endif

    if (!optmenu_open) return;

    u8 allowInput = 0;

    optmenu_option_timer--;
    if (optmenu_option_timer <= 0) {
        if (optmenu_hold_count == 0) {
            optmenu_hold_count++;
            optmenu_option_timer = 10;
        } else {
            optmenu_option_timer = 3;
        }
        allowInput = 1;
    }

    if (ABS(gPlayer1Controller->rawStickY) > 60 || gPlayer1Controller->buttonDown & U_JPAD || gPlayer1Controller->buttonDown & D_JPAD) {
        if (allowInput) {
            #ifndef nosound
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            #endif

            if (gPlayer1Controller->rawStickY >= 60 || gPlayer1Controller->buttonDown & U_JPAD) {
                currentMenu->select--;
                if (currentMenu->select < 0)
                    currentMenu->select = currentMenu->numOpts-1;
            } else if (gPlayer1Controller->rawStickY <= -60 || gPlayer1Controller->buttonDown & D_JPAD) {
                currentMenu->select++;
                if (currentMenu->select >= currentMenu->numOpts)
                    currentMenu->select = 0;
            }

            if (currentMenu->select < currentMenu->scroll)
                currentMenu->scroll = currentMenu->select;
            else if (currentMenu->select > currentMenu->scroll + 3)
                currentMenu->scroll = currentMenu->select - 3;
        }
    } else if (ABS(gPlayer1Controller->rawStickX) > 60 || gPlayer1Controller->buttonDown & L_JPAD || gPlayer1Controller->buttonDown & R_JPAD) {
        if (allowInput) {
            #ifndef nosound
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            #endif
            if (gPlayer1Controller->rawStickX >= 60 || gPlayer1Controller->buttonDown & R_JPAD) {
                optmenu_opt_change(&currentMenu->opts[currentMenu->select], 1);
            } else if (gPlayer1Controller->rawStickX <= -60 || gPlayer1Controller->buttonDown & L_JPAD) {
                optmenu_opt_change(&currentMenu->opts[currentMenu->select], -1);
            }
        }
    } else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        if (allowInput) {
            #ifndef nosound
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            #endif
            optmenu_opt_change(&currentMenu->opts[currentMenu->select], 0);
        }
    } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        if (allowInput) {
            if (currentMenu->prev) {
                #ifndef nosound
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
                #endif
                currentMenu = currentMenu->prev;
            } else {
                // can't go back, exit the menu altogether
                optmenu_toggle();
            }
        }
#if !defined(TARGET_N64) && !defined(TARGET_PORT_CONSOLE)
    } else if (gPlayer1Controller->buttonPressed & Z_TRIG) {
        // HACK: clear binds with Z
        if (allowInput && currentMenu->opts[currentMenu->select].type == OPT_BIND)
            optmenu_opt_change(&currentMenu->opts[currentMenu->select], 0xFF);
#endif
    } else if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        if (allowInput) optmenu_toggle();
    } else {
        optmenu_hold_count = 0;
        optmenu_option_timer = 0;
    }
}

#endif // EXT_OPTIONS_MENU
