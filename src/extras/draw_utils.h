#ifndef DRAW_ULTILS_EXTRAS_H
#define DRAW_ULTILS_EXTRAS_H

s16 get_string_width_ascii(char *str);

void ext_print_generic_string_ascii_adv(s16 x, s16 y, char *text, u8 r, u8 g, u8 b, u8 a, s8 dropShadow);
void ext_print_quad_rect(s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b, u8 a);
void ext_draw_texture_rect(s32 x, s32 y, u32 w, u32 h, u8 *texture, s16 scale);

#endif // DRAW_ULTILS_EXTRAS_H