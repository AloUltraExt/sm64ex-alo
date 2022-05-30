#include "sm64.h"
#include "gfx_dimensions.h"

#include "game/geo_misc.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/print.h"
#include "game/segment2.h"

#include "draw_util.h"

#if defined(VERSION_US) || defined(VERSION_EU)
extern u8 gDialogCharWidths[];
#endif

/**
 * @file draw_util.c
 * An extension of ingame_menu.c and print.c more or less.
 */

/*****************
 * DISPLAY LISTS *
 *****************/

// Start DL of a texture rectangle block
Gfx dl_texture_rect_ex_start[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

// End DL of a texture rectangle block
Gfx dl_texture_rect_ex_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

// Start DL of a triangle quad block
Gfx dl_tri_quad_ex_start[] = {
    gsDPPipeSync(),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// End DL of a triangle quad block
Gfx dl_tri_quad_ex_end[] = {
    gsDPPipeSync(),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

/*****************
 * MISCELLANEOUS *
 *****************/

/**
 * Converts ASCII to hex values (Vanilla) used in generic strings and dialogs.
 * Note, if you edited charmap.txt you may need to edit this function as well.
 */
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

s16 get_hud_str_width(u8 *str) {
    u32 c;
    s16 length = 0;

    while ((c = *str++) != GLOBAL_CHAR_TERMINATOR) {
        length += (c == GLOBAL_CHAR_SPACE ? (HUD_LUT_STRIDE_GLOBAL / 2) : HUD_LUT_STRIDE_GLOBAL);
    }

    return length;
}

s16 get_hud_str_width_ascii(char *str) {
    u32 c;
    s16 length = 0;

    while ((c = *str++) != GLOBAL_CHAR_TERMINATOR) {
        length += (c == ' ' ? (HUD_LUT_STRIDE_GLOBAL / 2) : HUD_LUT_STRIDE_GLOBAL);
    }

    return length;
}

s16 get_string_width_ascii(char *str) {
    s16 i;
    u8  buf[100];
    s16 bufPos = 0;
    s16 width = 0;

    for (i = 0; str[i] != 0; i++)
        buf[i] = ascii_to_font_char(str[i]);
    buf[i] = DIALOG_CHAR_TERMINATOR;

    while (buf[bufPos] != DIALOG_CHAR_TERMINATOR) {
        #if defined(VERSION_US) || defined(VERSION_EU)
        width += gDialogCharWidths[buf[bufPos]];
        #else
        width += JP_DIALOG_CHAR_WIDTH;
        #endif
        bufPos++;
    }

    return width;
}

s16 get_str_x_pos_from_center_custom_hex(s16 lutType, s16 centerPos, u8 *strHex, u8 useScale, f32 scale) {
    s16 spacesWidth = 0;

    switch (lutType) {
        case LUT_TYPE_HUD_HEX:
            spacesWidth = get_hud_str_width(strHex);
            break;
         case LUT_TYPE_STR_HEX:
            spacesWidth = get_string_width(strHex);
            break;
        default:
            break;
    }

    if (useScale) {
        return (f32) centerPos - ((scale / 2.0) * (spacesWidth / 2.0));
    }

    // return the x position of where the string starts as half the string's
    // length from the position of the provided center.
    return (centerPos - (spacesWidth / 2.0));
}

s16 get_str_x_pos_from_center_custom_ascii(s16 lutType, s16 centerPos, char *strAscii, u8 useScale, f32 scale) {
    s16 spacesWidth = 0;

    switch (lutType) {
        case LUT_TYPE_HUD_ASCII:
            spacesWidth = get_hud_str_width_ascii(strAscii);
            break;
         case LUT_TYPE_STR_ASCII:
            spacesWidth = get_string_width_ascii(strAscii);
            break;
        default:
            break;
    }

    if (useScale) {
        return (f32) centerPos - ((scale / 2.0) * (spacesWidth / 2.0));
    }

    // return the x position of where the string starts as half the string's
    // length from the position of the provided center.
    return (centerPos - (spacesWidth / 2.0));
}

/**
 * Convert texture resolution to mask.
 */
static u8 f3d_res_to_mask(u16 res) {
    s32 mask = 1;
    s32 num = 2;
    // Find the resolution mask
    while (TRUE) {
        if (num == res) {
            return mask;
        }
        num *= 2;
        mask++;
        if (mask == 9) {
            print_text(32, 32, "MASK FAILURE");
            break;
        }
    }

    return 0;
}

/**
 * Creates a texture block command to correctly generate it.
 */
void create_f3d_dl_texture_block_format(u8 *texture, u8 fmt, u8 siz, u16 w, u16 h) {
    u8 wM = f3d_res_to_mask(w);
    u8 hM = f3d_res_to_mask(h);

    switch (siz) {
        case G_IM_SIZ_32b:
            gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_32b, w, h, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, wM, hM, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case G_IM_SIZ_16b:
            gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, w, h, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, wM, hM, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case G_IM_SIZ_8b:
            gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, w, h, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, wM, hM, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case G_IM_SIZ_4b:
            gDPLoadTextureBlock_4b(gDisplayListHead++, texture, fmt, w, h, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, wM, hM, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
}

/**
 * Allocates quadrilateral vertices with UVs set by texture height and width.
 */
static void allocate_quad_vertices(Gfx *dlHead, u16 w, u16 h) {
    s16 wV = ((w - 1) << 5);
    s16 hV = ((h - 1) << 5);
    Vtx *verts = (Vtx *) alloc_display_list(4 * sizeof(Vtx));

    if (verts == NULL) {
        return;
    }

    verts[0].v.ob[0] = 0,  verts[0].v.ob[1] = 0,  verts[0].v.ob[2] = 0;
    verts[0].v.tc[0] = 0,  verts[0].v.tc[1] = hV;

    verts[1].v.ob[0] = w,  verts[1].v.ob[1] = 0,  verts[1].v.ob[2] = 0;
    verts[1].v.tc[0] = wV, verts[1].v.tc[1] = hV;

    verts[2].v.ob[0] = w,  verts[2].v.ob[1] = h,  verts[2].v.ob[2] = 0;
    verts[2].v.tc[0] = wV, verts[2].v.tc[1] = 0;

    verts[3].v.ob[0] = 0,  verts[3].v.ob[1] = h,  verts[3].v.ob[2] = 0;
    verts[3].v.tc[0] = 0,  verts[3].v.tc[1] = 0;

    gSPVertex(dlHead, VIRTUAL_TO_PHYSICAL(verts), 4, 0);
}

/******************
 * MISC RENDERING *
 ******************/
 
/**
 * Like print_generic_string but uses ASCII, then it transform it to hex.
 */
void print_generic_string_ascii(s16 x, s16 y, const char *str) {
    s16 i;
    u8  buf[100];
    for (i = 0; str[i] != 0; i++)
        buf[i] = ascii_to_font_char(str[i]);
    buf[i] = DIALOG_CHAR_TERMINATOR;

    print_generic_string(x, y, buf);
}

/**
 * An detailed version of print_generic_strig_ascii that let's you
 * color the font and add shadow to it.
 */
void print_generic_string_detail(s16 x, s16 y, u8 *str, u8 r, u8 g, u8 b, u8 a, s8 hasShadow, s8 shadowPad) {
    if (hasShadow) {
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
        print_generic_string(x + shadowPad, y - shadowPad, str);
    }

    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
    print_generic_string(x, y, str);
}

/**
 * An detailed version of print_generic_strig that let's you
 * color the font and add shadow to it.
 */
void print_generic_string_ascii_detail(s16 x, s16 y, const char *str, u8 r, u8 g, u8 b, u8 a, s8 hasShadow, s8 shadowPad) {
    if (hasShadow) {
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
        print_generic_string_ascii(x + shadowPad, y - shadowPad, str);
    }

    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
    print_generic_string_ascii(x, y, str);
}

/**
 * Prints a quadrilateral solid color.
 */
void print_solid_color_quad(s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b, u8 a) {
    gDPSetCombineMode(gDisplayListHead++, G_CC_ENVIRONMENT, G_CC_ENVIRONMENT);
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
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/********************
 * TEXTURE RENDERING *
 ********************/

/**
 * General print texture params:
 * @param texture - Sets the texture directly.
 * @param siz (sizTex in CI) - Sets the size of a texture type if valid (G_IM_SIZ_#b, # can be 4, 8, 16, 32).
 * @param w, h - Sets the width and height of the texture.
 *
 * Print texture params (CI only):
 * @param palette - Sets the palette to work with the texture.
 * @param fmtPal - Sets the palette type (Can only be RGBA16 or IA16).
 */

/**
 * Coloring a texture:
 * These command(s) need to be called before the print texture functions.
 * On a texture rectangle, use this command:
   gDPSetEnvColor(gDisplayListHead++, r, g, b, a),

 * On a texture quadrangle, use this command:
   gsDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a),
 */

/**
 * How to render a texture rectangle:
 * First call this display list:
   gSPDisplayList(gDisplayListHead++, dl_texture_rect_ex_start);
 * 
 * Then call any print texture rectangle function depending of the texture type.
 *
 * After the texrect is render, call this display list to end if desired:
   gSPDisplayList(gDisplayListHead++, dl_texture_rect_ex_end);
 */

/**
 * Print texture rectangle params
 * @param x, y - Sets the texrect position.
 * @param xS, yS - Sets the texrect scale (Set these to 1).
 */

/**
 * Prints a texture rectangle (for RGBA16 and RGBA32) textures.
 */
void print_texture_rectangle_rgba(u8 *texture, u8 siz, s16 x, s16 y, u16 w, u16 h, s16 xS, s16 yS) {
    create_f3d_dl_texture_block_format(texture, G_IM_FMT_RGBA, siz, w, h);

    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w * xS) << 2, (y + h * yS) << 2, G_TX_RENDERTILE, 0, 0, (1 << 10) / xS, (1 << 10) / yS);
}

/**
 * Prints a texture rectangle (for IA4, IA8 and IA16) textures.
 */
void print_texture_rectangle_ia(u8 *texture, u8 siz, s16 x, s16 y, u16 w, u16 h, s16 xS, s16 yS) {
    create_f3d_dl_texture_block_format(texture, G_IM_FMT_IA, siz, w, h);

    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w * xS) << 2, (y + h * yS) << 2, G_TX_RENDERTILE, 0, 0, (1 << 10) / xS, (1 << 10) / yS);
}

/**
 * Prints a texture rectangle (for CI4 and CI8) textures
 * with selectable palette type (RGBA16 or IA16).
 */
void print_texture_rectangle_ci(u8 *palette, u8 fmtPal, u8 *texture, u8 sizTex, s16 x, s16 y, u16 w, u16 h, s16 xS, s16 yS) {
    switch (fmtPal) {
        case G_IM_FMT_RGBA:
            gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
            break;
        case G_IM_FMT_IA:
            gDPSetTextureLUT(gDisplayListHead++, G_TT_IA16);
            break;
    }

    switch (sizTex) {
        case G_IM_SIZ_4b:
            gDPLoadTLUT_pal16(gDisplayListHead++, 0, palette);
            break;
        case G_IM_SIZ_8b:
            gDPLoadTLUT_pal256(gDisplayListHead++, palette);
            break;
    }

    create_f3d_dl_texture_block_format(texture, G_IM_FMT_CI, sizTex, w, h);

    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w * xS) << 2, (y + h * yS) << 2, G_TX_RENDERTILE, 0, 0, (1 << 10) / xS, (1 << 10) / yS);
    gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
}

/**
 * How to render a texture quadrangle:
 * First call this display list:
   gSPDisplayList(gDisplayListHead++, dl_tri_quad_ex_start);

 * Then you set its position using create_dl_translation_matrix, like this:
   create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0.0f);
 * The x and y values can be used for positioning.
 
 * Optionally you can set its rotation and scale values as well:
 * For rotation:
   create_dl_rotation_matrix(MENU_MTX_NOPUSH, r, 0, 0, 1.0f);
 * Here you only need to change the r value due to this being a 2D plane.
 
 * For scale:
   create_dl_scale_matrix(MENU_MTX_NOPUSH, x, y, 1.0f);
 * The x and y values can be used for scaling.

 * Then call any print texture quadrangle function depending of the texture type.
 *
 * After the texrect is render, call this display list to end if desired:
   gSPDisplayList(gDisplayListHead++, dl_tri_quad_ex_end);
   
 * And finally to render it to the screen, call this:
   gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
 */
 
/**
 * Prints a texture quadrangle (for RGBA16 and RGBA32) textures.
 */
void print_texture_tri_quad_rgba(u8 *texture, u8 siz, u16 w, u16 h) {
    create_f3d_dl_texture_block_format(texture, G_IM_FMT_RGBA, siz, w, h);

    allocate_quad_vertices(gDisplayListHead++, w, h);
    gSPDisplayList(gDisplayListHead++, dl_draw_quad_verts_0123);
}

/**
 * Prints a texture quadrangle (for IA4, IA8 and IA16) textures.
 */
void print_texture_tri_quad_ia(u8 *texture, u8 siz, u16 w, u16 h) {
    create_f3d_dl_texture_block_format(texture, G_IM_FMT_IA, siz, w, h);

    allocate_quad_vertices(gDisplayListHead++, w, h);
    gSPDisplayList(gDisplayListHead++, dl_draw_quad_verts_0123);
}

/**
 * Prints a texture quadrangle (for CI4 and CI8) textures
 * with selectable palette type (RGBA16 or IA16).
 */
void print_texture_tri_quad_ci(u8 *palette, u8 fmtPal, u8 *texture, u8 sizTex, u16 w, u16 h) {
    switch (fmtPal) {
        case G_IM_FMT_RGBA:
            gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
            break;
        case G_IM_FMT_IA:
            gDPSetTextureLUT(gDisplayListHead++, G_TT_IA16);
            break;
    }

    switch (sizTex) {
        case G_IM_SIZ_4b:
            gDPLoadTLUT_pal16(gDisplayListHead++, 0, palette);
            break;
        case G_IM_SIZ_8b:
            gDPLoadTLUT_pal256(gDisplayListHead++, palette);
            break;
    }

    create_f3d_dl_texture_block_format(texture, G_IM_FMT_CI, sizTex, w, h);

    allocate_quad_vertices(gDisplayListHead++, w, h);
    gSPDisplayList(gDisplayListHead++, dl_draw_quad_verts_0123);
    gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
}
