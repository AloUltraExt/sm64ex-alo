#include "sm64.h"
#include "gfx_dimensions.h"

#include "game/ingame_menu.h"
#include "game/geo_misc.h"
#include "game/game_init.h"
#include "game/segment2.h"

#if defined(VERSION_US) || defined(VERSION_EU)
extern u8 gDialogCharWidths[];
#endif

const Gfx dl_ex_texrect_block_start[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

const Gfx dl_ex_texrect_block_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

static u8 ascii_to_font_char(u8 c) {
    if (c >= '0' && c <= '9')
        return (c - '0' + 0x00);

    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 0x0A);

    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 0x24);

    if (c == '\'') return 0x3E;
    if (c == '.')  return 0x3F;
    if (c == ',')  return 0x6F;
    if (c == ' ')  return 0x9E;
    if (c == '-')  return 0x9F;
    if (c == '(')  return 0xE1;
    if (c == ')')  return 0xE3;
    if (c == '+')  return 0xE4;
    if (c == '&')  return 0xE5;
    if (c == ':')  return 0xE6;
    if (c == '!')  return 0xF2;
    if (c == '%')  return 0xF3;
    if (c == '?')  return 0xF4;
    if (c == '~')  return 0xF7;
    if (c == '$')  return 0xF9;
    if (c == '*')  return 0xFA;
    if (c == '#')  return 0xFD;
    if (c == '\n') return 0xFE;

    return 0x9E;
}

void print_generic_str_ascii(s16 x, s16 y, const char *str) {
    s16 i;
    u8  buf[50];
    for (i = 0; str[i] != 0; i++)
        buf[i] = ascii_to_font_char(str[i]);
    buf[i] = DIALOG_CHAR_TERMINATOR;

    print_generic_string(x, y, buf);
}

s16 get_string_width_ascii(char *str) {
    s16 i;
    u8  buf[50];
    s16 bufPos = 0;
    s16 width = 0;

    for (i = 0; str[i] != 0; i++)
        buf[i] = ascii_to_font_char(str[i]);
    buf[i] = DIALOG_CHAR_TERMINATOR;

    while (buf[bufPos] != DIALOG_CHAR_TERMINATOR) {
        #if defined(VERSION_US) || defined(VERSION_EU)
        width += gDialogCharWidths[buf[bufPos]];
        #else
        width += JP_DIALOG_CHAR_STRING;
        #endif
        bufPos++;
    }

    return width;
}

static s8 ext_f3d_res_to_mask(s16 res) {
    if(res >= 2)    return 1;
    if(res >= 4)    return 2;
    if(res >= 8)    return 3;
    if(res >= 16)   return 4;
    if(res >= 32)   return 5;
    if(res >= 64)   return 6;
    if(res >= 128)  return 7;
    if(res >= 256)  return 8;
    if(res >= 512)  return 9;
    if(res >= 1024) return 10;
    
    return 0;
}

void ext_print_generic_string_ascii_adv(s16 x, s16 y, char *text, u8 r, u8 g, u8 b, u8 a, s8 dropShadow) {
    create_dl_ortho_matrix();

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    if (dropShadow) {
        gDPSetEnvColor(gDisplayListHead++, 10, 10, 10, 255);
        print_generic_str_ascii(x, SCREEN_HEIGHT - y - 1, text);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    }
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
    print_generic_str_ascii(x, SCREEN_HEIGHT - y, text);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
}

#define BLANK 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT

void ext_print_quad_rect(s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b, u8 a) {
    gDPSetCombineMode(gDisplayListHead++, BLANK, BLANK);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    if (a != 255) {
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    } else {
        gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF);
    }
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
    gDPFillRectangle(gDisplayListHead++, x1, y1, x2, y2);
    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPDisplayList(gDisplayListHead++,dl_hud_img_end);
}

#undef BLANK

void ext_draw_texture_rect(s16 x, s16 y, u32 w, u32 h, u8 *texture, s16 scale) {
    gSPDisplayList(gDisplayListHead++, dl_ex_texrect_block_start);
    gDPLoadTextureBlock(gDisplayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 
            (ext_f3d_res_to_mask(w)), (ext_f3d_res_to_mask(h)), G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w * scale) << 2, (y + h * scale) << 2, G_TX_RENDERTILE, 0, 0, (1 << 10) / scale, (1 << 10) / scale);
    gSPDisplayList(gDisplayListHead++, dl_ex_texrect_block_end);
}

