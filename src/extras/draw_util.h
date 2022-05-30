#pragma once

#include <PR/ultratypes.h>
#include "game/ingame_menu.h"

// get_str_x_pos_from_center_custom_hex
enum xPosCenterCustomTypesHex {
    LUT_TYPE_HUD_HEX,
    LUT_TYPE_STR_HEX
};

// get_str_x_pos_from_center_custom_ascii
enum xPosCenterCustomTypesAscii {
    LUT_TYPE_HUD_ASCII,
    LUT_TYPE_STR_ASCII
};

extern Gfx dl_texture_rect_ex_start[];
extern Gfx dl_texture_rect_ex_end[];
extern Gfx dl_tri_quad_ex_start[];
extern Gfx dl_tri_quad_ex_end[];

s16 get_hud_str_width(u8 *str);
s16 get_hud_str_width_ascii(char *str);
s16 get_string_width_ascii(char *str);

s16 get_str_x_pos_from_center_custom_hex(s16 lutType, s16 centerPos, u8 *strHex, u8 useScale, f32 scale);
s16 get_str_x_pos_from_center_custom_ascii(s16 lutType, s16 centerPos, char *strAscii, u8 useScale, f32 scale);

void print_generic_string_ascii(s16 x, s16 y, const char *str);
void print_generic_string_detail(s16 x, s16 y, u8 *text, u8 r, u8 g, u8 b, u8 a, s8 hasShadow, s8 shadowPad);
void print_generic_string_ascii_detail(s16 x, s16 y, const char *str, u8 r, u8 g, u8 b, u8 a, s8 hasShadow, s8 shadowPad);

void print_solid_color_quad(s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b, u8 a);

void print_texture_rectangle(s32 x, s32 y, u32 w, u32 h, u8 *texture, s16 xS, s16 yS);
void print_texture_rectangle_rgba(u8 *texture, u8 siz, s16 x, s16 y, u16 w, u16 h, s16 xS, s16 yS);
void print_texture_rectangle_ia(u8 *texture, u8 siz, s16 x, s16 y, u16 w, u16 h, s16 xS, s16 yS);
void print_texture_rectangle_ci(u8 *palette, u8 fmtPal, u8 *texture, u8 sizTex, s16 x, s16 y, u16 w, u16 h, s16 xS, s16 yS);

void print_texture_tri_quad_rgba(u8 *texture, u8 siz, u16 w, u16 h);
void print_texture_tri_quad_ia(u8 *texture, u8 siz, u16 w, u16 h);
void print_texture_tri_quad_ci(u8 *palette, u8 fmtPal, u8 *texture, u8 sizTex, u16 w, u16 h);
