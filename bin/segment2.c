#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "config.h"
#include "macros.h"
#include "types.h"
#include "game/ingame_menu.h"

#include "make_const_nonconst.h"

// SM64 (US/JP/EU/SH) Segment 02

ALIGNED8 static const Texture texture_hud_char_0[] = {
#include "textures/segment2/segment2.00000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_1[] = {
#include "textures/segment2/segment2.00200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_2[] = {
#include "textures/segment2/segment2.00400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_3[] = {
#include "textures/segment2/segment2.00600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_4[] = {
#include "textures/segment2/segment2.00800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_5[] = {
#include "textures/segment2/segment2.00A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_6[] = {
#include "textures/segment2/segment2.00C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_7[] = {
#include "textures/segment2/segment2.00E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_8[] = {
#include "textures/segment2/segment2.01000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_9[] = {
#include "textures/segment2/segment2.01200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_A[] = {
#include "textures/segment2/segment2.01400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_B[] = {
#include "textures/segment2/segment2.01600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_C[] = {
#include "textures/segment2/segment2.01800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_D[] = {
#include "textures/segment2/segment2.01A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_E[] = {
#include "textures/segment2/segment2.01C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_F[] = {
#include "textures/segment2/segment2.01E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_G[] = {
#include "textures/segment2/segment2.02000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_H[] = {
#include "textures/segment2/segment2.02200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_I[] = {
#include "textures/segment2/segment2.02400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_J[] = {
#include "textures/segment2/predone/segment2.02600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_K[] = {
#include "textures/segment2/segment2.02800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_L[] = {
#include "textures/segment2/segment2.02A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_M[] = {
#include "textures/segment2/segment2.02C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_N[] = {
#include "textures/segment2/segment2.02E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_O[] = {
#include "textures/segment2/segment2.03000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_P[] = {
#include "textures/segment2/segment2.03200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_Q[] = {
#include "textures/segment2/predone/segment2.03400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_R[] = {
#include "textures/segment2/segment2.03600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_S[] = {
#include "textures/segment2/segment2.03800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_T[] = {
#include "textures/segment2/segment2.03A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_U[] = {
#include "textures/segment2/segment2.03C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_V[] = {
#include "textures/segment2/predone/segment2.03E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_W[] = {
#include "textures/segment2/segment2.04000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_X[] = {
#include "textures/segment2/predone/segment2.04200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_Y[] = {
#include "textures/segment2/segment2.04400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_Z[] = {
#include "textures/segment2/predone/segment2.04600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_apostrophe[] = {
#include "textures/segment2/segment2.04800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_double_quote[] = {
#include "textures/segment2/segment2.04A00.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_umlaut[] = {
#include "textures/segment2/predone/segment2.umlaut.rgba16.inc.c"// EU ¨
};

ALIGNED8 static const Texture texture_hud_char_exclamation[] = {
#include "textures/segment2/predone/segment2.04C00.rgba16.inc.c"// JP !
};

ALIGNED8 static const Texture texture_hud_char_double_exclamation[] = {
#include "textures/segment2/predone/segment2.04E00.rgba16.inc.c"// JP !!
};

ALIGNED8 static const Texture texture_hud_char_question[] = {
#include "textures/segment2/segment2.05000.rgba16.inc.c"// JP ?
};

ALIGNED8 static const Texture texture_hud_char_ampersand[] = {
#include "textures/segment2/predone/segment2.05200.rgba16.inc.c"// JP &
};

ALIGNED8 static const Texture texture_hud_char_percent[] = {
#include "textures/segment2/predone/segment2.05400.rgba16.inc.c"// JP %
};

ALIGNED8 static const Texture texture_hud_char_multiply[] = {
#include "textures/segment2/segment2.05600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_coin[] = {
#include "textures/segment2/segment2.05800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_mario_head[] = {
#include "textures/segment2/segment2.05A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_star[] = {
#include "textures/segment2/segment2.05C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_circle_fill[] = {
#include "textures/segment2/predone/segment2.05E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_beta_key[] = {
#include "textures/segment2/predone/segment2.06000.rgba16.inc.c"
};

// Custom fonts

ALIGNED8 static const Texture texture_hud_char_decimal_point[] = {
#include "textures/segment2/custom/tex_decimal_point.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_minus[] = {
#include "textures/segment2/custom/tex_minus.rgba16.inc.c"
};

#ifdef MOUSE_ACTIONS
ALIGNED8 const Texture texture_hud_char_mouse_small[] = {
#include "textures/segment2/custom/tex_mouse_small.rgba16.inc.c"
};
#endif

#if defined(VERSION_CN)
ALIGNED8 static const Texture texture_hud_char_cn_04A00[] = {
#include "textures/segment2/segment2_cn.04A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_04C00[] = {
#include "textures/segment2/segment2_cn.04C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_04E00[] = {
#include "textures/segment2/segment2_cn.04E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05000[] = {
#include "textures/segment2/segment2_cn.05000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05200[] = {
#include "textures/segment2/segment2_cn.05200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05400[] = {
#include "textures/segment2/segment2_cn.05400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05600[] = {
#include "textures/segment2/segment2_cn.05600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05800[] = {
#include "textures/segment2/segment2_cn.05800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05A00[] = {
#include "textures/segment2/segment2_cn.05A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05C00[] = {
#include "textures/segment2/segment2_cn.05C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_05E00[] = {
#include "textures/segment2/segment2_cn.05E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06000[] = {
#include "textures/segment2/segment2_cn.06000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06200[] = {
#include "textures/segment2/segment2_cn.06200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06400[] = {
#include "textures/segment2/segment2_cn.06400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06600[] = {
#include "textures/segment2/segment2_cn.06600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06800[] = {
#include "textures/segment2/segment2_cn.06800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06A00[] = {
#include "textures/segment2/segment2_cn.06A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06C00[] = {
#include "textures/segment2/segment2_cn.06C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_06E00[] = {
#include "textures/segment2/segment2_cn.06E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07000[] = {
#include "textures/segment2/segment2_cn.07000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07200[] = {
#include "textures/segment2/segment2_cn.07200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07400[] = {
#include "textures/segment2/segment2_cn.07400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07600[] = {
#include "textures/segment2/segment2_cn.07600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07800[] = {
#include "textures/segment2/segment2_cn.07800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07A00[] = {
#include "textures/segment2/segment2_cn.07A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07C00[] = {
#include "textures/segment2/segment2_cn.07C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_07E00[] = {
#include "textures/segment2/segment2_cn.07E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08000[] = {
#include "textures/segment2/segment2_cn.08000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08200[] = {
#include "textures/segment2/segment2_cn.08200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08400[] = {
#include "textures/segment2/segment2_cn.08400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08600[] = {
#include "textures/segment2/segment2_cn.08600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08800[] = {
#include "textures/segment2/segment2_cn.08800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08A00[] = {
#include "textures/segment2/segment2_cn.08A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08C00[] = {
#include "textures/segment2/segment2_cn.08C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_08E00[] = {
#include "textures/segment2/segment2_cn.08E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09000[] = {
#include "textures/segment2/segment2_cn.09000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09200[] = {
#include "textures/segment2/segment2_cn.09200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09400[] = {
#include "textures/segment2/segment2_cn.09400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09600[] = {
#include "textures/segment2/segment2_cn.09600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09800[] = {
#include "textures/segment2/segment2_cn.09800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09A00[] = {
#include "textures/segment2/segment2_cn.09A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09C00[] = {
#include "textures/segment2/segment2_cn.09C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_09E00[] = {
#include "textures/segment2/segment2_cn.09E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0A000[] = {
#include "textures/segment2/segment2_cn.0A000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0A200[] = {
#include "textures/segment2/segment2_cn.0A200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0A400[] = {
#include "textures/segment2/segment2_cn.0A400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0A600[] = {
#include "textures/segment2/segment2_cn.0A600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0A800[] = {
#include "textures/segment2/segment2_cn.0A800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0AA00[] = {
#include "textures/segment2/segment2_cn.0AA00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0AC00[] = {
#include "textures/segment2/segment2_cn.0AC00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0AE00[] = {
#include "textures/segment2/segment2_cn.0AE00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0B000[] = {
#include "textures/segment2/segment2_cn.0B000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0B200[] = {
#include "textures/segment2/segment2_cn.0B200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0B400[] = {
#include "textures/segment2/segment2_cn.0B400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0B600[] = {
#include "textures/segment2/segment2_cn.0B600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0B800[] = {
#include "textures/segment2/segment2_cn.0B800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0BA00[] = {
#include "textures/segment2/segment2_cn.0BA00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0BC00[] = {
#include "textures/segment2/segment2_cn.0BC00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0BE00[] = {
#include "textures/segment2/segment2_cn.0BE00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0C000[] = {
#include "textures/segment2/segment2_cn.0C000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0C200[] = {
#include "textures/segment2/segment2_cn.0C200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0C400[] = {
#include "textures/segment2/segment2_cn.0C400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0C600[] = {
#include "textures/segment2/segment2_cn.0C600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0C800[] = {
#include "textures/segment2/segment2_cn.0C800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0CA00[] = {
#include "textures/segment2/segment2_cn.0CA00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0CC00[] = {
#include "textures/segment2/segment2_cn.0CC00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0CE00[] = {
#include "textures/segment2/segment2_cn.0CE00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0D000[] = {
#include "textures/segment2/segment2_cn.0D000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0D200[] = {
#include "textures/segment2/segment2_cn.0D200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0D400[] = {
#include "textures/segment2/segment2_cn.0D400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0D600[] = {
#include "textures/segment2/segment2_cn.0D600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0D800[] = {
#include "textures/segment2/segment2_cn.0D800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0DA00[] = {
#include "textures/segment2/segment2_cn.0DA00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0DC00[] = {
#include "textures/segment2/segment2_cn.0DC00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0DE00[] = {
#include "textures/segment2/segment2_cn.0DE00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0E000[] = {
#include "textures/segment2/segment2_cn.0E000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0E200[] = {
#include "textures/segment2/segment2_cn.0E200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0E400[] = {
#include "textures/segment2/segment2_cn.0E400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0E600[] = {
#include "textures/segment2/segment2_cn.0E600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0E800[] = {
#include "textures/segment2/segment2_cn.0E800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0EA00[] = {
#include "textures/segment2/segment2_cn.0EA00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0EC00[] = {
#include "textures/segment2/segment2_cn.0EC00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0EE00[] = {
#include "textures/segment2/segment2_cn.0EE00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0F000[] = {
#include "textures/segment2/segment2_cn.0F000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0F200[] = {
#include "textures/segment2/segment2_cn.0F200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0F400[] = {
#include "textures/segment2/segment2_cn.0F400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0F600[] = {
#include "textures/segment2/segment2_cn.0F600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0F800[] = {
#include "textures/segment2/segment2_cn.0F800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0FA00[] = {
#include "textures/segment2/segment2_cn.0FA00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0FC00[] = {
#include "textures/segment2/segment2_cn.0FC00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_0FE00[] = {
#include "textures/segment2/segment2_cn.0FE00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10000[] = {
#include "textures/segment2/segment2_cn.10000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10200[] = {
#include "textures/segment2/segment2_cn.10200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10400[] = {
#include "textures/segment2/segment2_cn.10400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10600[] = {
#include "textures/segment2/segment2_cn.10600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10800[] = {
#include "textures/segment2/segment2_cn.10800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10A00[] = {
#include "textures/segment2/segment2_cn.10A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10C00[] = {
#include "textures/segment2/segment2_cn.10C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_10E00[] = {
#include "textures/segment2/segment2_cn.10E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11000[] = {
#include "textures/segment2/segment2_cn.11000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11200[] = {
#include "textures/segment2/segment2_cn.11200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11400[] = {
#include "textures/segment2/segment2_cn.11400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11600[] = {
#include "textures/segment2/segment2_cn.11600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11800[] = {
#include "textures/segment2/segment2_cn.11800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11A00[] = {
#include "textures/segment2/segment2_cn.11A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11C00[] = {
#include "textures/segment2/segment2_cn.11C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_11E00[] = {
#include "textures/segment2/segment2_cn.11E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12000[] = {
#include "textures/segment2/segment2_cn.12000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12200[] = {
#include "textures/segment2/segment2_cn.12200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12400[] = {
#include "textures/segment2/segment2_cn.12400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12600[] = {
#include "textures/segment2/segment2_cn.12600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12800[] = {
#include "textures/segment2/segment2_cn.12800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12A00[] = {
#include "textures/segment2/segment2_cn.12A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12C00[] = {
#include "textures/segment2/segment2_cn.12C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_12E00[] = {
#include "textures/segment2/segment2_cn.12E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13000[] = {
#include "textures/segment2/segment2_cn.13000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13200[] = {
#include "textures/segment2/segment2_cn.13200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13400[] = {
#include "textures/segment2/segment2_cn.13400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13600[] = {
#include "textures/segment2/segment2_cn.13600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13800[] = {
#include "textures/segment2/segment2_cn.13800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13A00[] = {
#include "textures/segment2/segment2_cn.13A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13C00[] = {
#include "textures/segment2/segment2_cn.13C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_13E00[] = {
#include "textures/segment2/segment2_cn.13E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_cn_14000[] = {
#include "textures/segment2/segment2_cn.14000.rgba16.inc.c"
};
#endif // VERSION_CN

#if !CREDITS_TEXT_STRING_FONT
ALIGNED8 static const Texture texture_credits_char_3[] = {
#include "textures/segment2/segment2.06200.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_4[] = {
#include "textures/segment2/segment2.06280.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_6[] = {
#include "textures/segment2/segment2.06300.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_A[] = {
#include "textures/segment2/segment2.06380.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_B[] = {
#include "textures/segment2/segment2.06400.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_C[] = {
#include "textures/segment2/segment2.06480.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_D[] = {
#include "textures/segment2/segment2.06500.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_E[] = {
#include "textures/segment2/segment2.06580.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_F[] = {
#include "textures/segment2/segment2.06600.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_G[] = {
#include "textures/segment2/segment2.06680.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_H[] = {
#include "textures/segment2/segment2.06700.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_I[] = {
#include "textures/segment2/segment2.06780.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_J[] = {
#include "textures/segment2/segment2.06800.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_K[] = {
#include "textures/segment2/segment2.06880.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_L[] = {
#include "textures/segment2/segment2.06900.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_M[] = {
#include "textures/segment2/segment2.06980.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_N[] = {
#include "textures/segment2/segment2.06A00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_O[] = {
#include "textures/segment2/segment2.06A80.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_P[] = {
#include "textures/segment2/segment2.06B00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_Q[] = {
#include "textures/segment2/segment2.06B80.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_R[] = {
#include "textures/segment2/segment2.06C00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_S[] = {
#include "textures/segment2/segment2.06C80.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_T[] = {
#include "textures/segment2/segment2.06D00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_U[] = {
#include "textures/segment2/segment2.06D80.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_V[] = {
#include "textures/segment2/segment2.06E00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_W[] = {
#include "textures/segment2/segment2.06E80.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_X[] = {
#include "textures/segment2/segment2.06F00.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_Y[] = {
#include "textures/segment2/segment2.06F80.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_Z[] = {
#include "textures/segment2/segment2.07000.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_credits_char_period[] = {
#include "textures/segment2/segment2.07080.rgba16.inc.c"
};
#endif

// JP Small Font
#ifdef JAPANESE_CHARACTERS
ALIGNED8 static const Texture texture_font_char_jp_0[] = {
#include "textures/segment2/segment2.07100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_1[] = {
#include "textures/segment2/segment2.07110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_2[] = {
#include "textures/segment2/segment2.07120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_3[] = {
#include "textures/segment2/segment2.07130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_4[] = {
#include "textures/segment2/segment2.07140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_5[] = {
#include "textures/segment2/segment2.07150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_6[] = {
#include "textures/segment2/segment2.07160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_7[] = {
#include "textures/segment2/segment2.07170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_8[] = {
#include "textures/segment2/segment2.07180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_9[] = {
#include "textures/segment2/segment2.07190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_A[] = {
#include "textures/segment2/segment2.071A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_B[] = {
#include "textures/segment2/segment2.071B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_C[] = {
#include "textures/segment2/segment2.071C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_D[] = {
#include "textures/segment2/segment2.071D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_E[] = {
#include "textures/segment2/segment2.071E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_F[] = {
#include "textures/segment2/segment2.071F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_G[] = {
#include "textures/segment2/segment2.07200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_H[] = {
#include "textures/segment2/segment2.07210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_I[] = {
#include "textures/segment2/segment2.07220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_J[] = {
#include "textures/segment2/segment2.07230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_K[] = {
#include "textures/segment2/segment2.07240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_L[] = {
#include "textures/segment2/segment2.07250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_M[] = {
#include "textures/segment2/segment2.07260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_N[] = {
#include "textures/segment2/segment2.07270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_O[] = {
#include "textures/segment2/segment2.07280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_P[] = {
#include "textures/segment2/segment2.07290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_Q[] = {
#include "textures/segment2/segment2.072A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_R[] = {
#include "textures/segment2/segment2.072B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_S[] = {
#include "textures/segment2/segment2.072C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_T[] = {
#include "textures/segment2/segment2.072D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_U[] = {
#include "textures/segment2/segment2.072E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_V[] = {
#include "textures/segment2/segment2.072F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_W[] = {
#include "textures/segment2/segment2.07300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_X[] = {
#include "textures/segment2/segment2.07310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_Y[] = {
#include "textures/segment2/segment2.07320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_Z[] = {
#include "textures/segment2/segment2.07330.ia1.inc.c"
};

#if (defined(VERSION_JP) || defined(VERSION_SH)) && !defined(MULTILANG)
ALIGNED8 static const Texture texture_font_char_jp_a[] = {
#include "textures/segment2/custom/font_graphics_jp.a.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_b[] = {
#include "textures/segment2/custom/font_graphics_jp.b.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_c[] = {
#include "textures/segment2/custom/font_graphics_jp.c.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_d[] = {
#include "textures/segment2/custom/font_graphics_jp.d.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_e[] = {
#include "textures/segment2/custom/font_graphics_jp.e.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_f[] = {
#include "textures/segment2/custom/font_graphics_jp.f.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_g[] = {
#include "textures/segment2/custom/font_graphics_jp.g.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_h[] = {
#include "textures/segment2/custom/font_graphics_jp.h.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_i[] = {
#include "textures/segment2/custom/font_graphics_jp.i.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_j[] = {
#include "textures/segment2/custom/font_graphics_jp.j.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_k[] = {
#include "textures/segment2/custom/font_graphics_jp.k.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_l[] = {
#include "textures/segment2/custom/font_graphics_jp.l.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_m[] = {
#include "textures/segment2/custom/font_graphics_jp.m.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_n[] = {
#include "textures/segment2/custom/font_graphics_jp.n.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_o[] = {
#include "textures/segment2/custom/font_graphics_jp.o.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_p[] = {
#include "textures/segment2/custom/font_graphics_jp.p.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_q[] = {
#include "textures/segment2/custom/font_graphics_jp.q.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_r[] = {
#include "textures/segment2/custom/font_graphics_jp.r.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_s[] = {
#include "textures/segment2/custom/font_graphics_jp.s.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_t[] = {
#include "textures/segment2/custom/font_graphics_jp.t.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_u[] = {
#include "textures/segment2/custom/font_graphics_jp.u.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_v[] = {
#include "textures/segment2/custom/font_graphics_jp.v.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_w[] = {
#include "textures/segment2/custom/font_graphics_jp.w.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_x[] = {
#include "textures/segment2/custom/font_graphics_jp.x.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_y[] = {
#include "textures/segment2/custom/font_graphics_jp.y.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_z[] = {
#include "textures/segment2/custom/font_graphics_jp.z.ia1.inc.c"
};
#endif

ALIGNED8 static const Texture texture_font_char_jp_long_vowel[] = {
#include "textures/segment2/segment2.07340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_exclamation[] = {
#include "textures/segment2/segment2.07350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_dakuten[] = {
#include "textures/segment2/segment2.07360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_period[] = {
#include "textures/segment2/segment2.07370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_percent[] = {
#include "textures/segment2/segment2.07380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_question[] = {
#include "textures/segment2/segment2.07390.ia1.inc.c"
};

//ALIGNED8 static const Texture texture_font_char_jp_left_right_arrow[] = {
//#include "textures/segment2/segment2.073A0.ia1.inc.c"
//};

ALIGNED8 static const Texture texture_font_char_jp_open_parentheses[] = {
#include "textures/segment2/segment2.073B0.ia1.inc.c"
};

//ALIGNED8 static const Texture texture_font_char_jp_close_open_parentheses[] = {
//#include "textures/segment2/segment2.073C0.ia1.inc.c"
//};

ALIGNED8 static const Texture texture_font_char_jp_close_parentheses[] = {
#include "textures/segment2/segment2.073D0.ia1.inc.c"
};

//ALIGNED8 static const Texture texture_font_char_jp_coin[] = {
//#include "textures/segment2/segment2.073E0.ia1.inc.c"
//};

ALIGNED8 static const Texture texture_font_char_jp_multiply[] = {
#include "textures/segment2/segment2.073F0.ia1.inc.c"
};

//ALIGNED8 static const Texture texture_font_char_jp_star_filled[] = {
//#include "textures/segment2/segment2.07400.ia1.inc.c"
//};

//ALIGNED8 static const Texture texture_font_char_jp_star_hollow[] = {
//#include "textures/segment2/segment2.07410.ia1.inc.c"
//};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_a[] = {
#include "textures/segment2/segment2.07420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_i[] = {
#include "textures/segment2/segment2.07430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_u[] = {
#include "textures/segment2/segment2.07440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_e[] = {
#include "textures/segment2/segment2.07450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_o[] = {
#include "textures/segment2/segment2.07460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ka[] = {
#include "textures/segment2/segment2.07470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ki[] = {
#include "textures/segment2/segment2.07480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ku[] = {
#include "textures/segment2/segment2.07490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ke[] = {
#include "textures/segment2/segment2.074A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ko[] = {
#include "textures/segment2/segment2.074B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_sa[] = {
#include "textures/segment2/segment2.074C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_shi[] = {
#include "textures/segment2/segment2.074D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_su[] = {
#include "textures/segment2/segment2.074E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_se[] = {
#include "textures/segment2/segment2.074F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_so[] = {
#include "textures/segment2/segment2.07500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ta[] = {
#include "textures/segment2/segment2.07510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_chi[] = {
#include "textures/segment2/segment2.07520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_tsu[] = {
#include "textures/segment2/segment2.07530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_te[] = {
#include "textures/segment2/segment2.07540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_to[] = {
#include "textures/segment2/segment2.07550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_na[] = {
#include "textures/segment2/segment2.07560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ni[] = {
#include "textures/segment2/segment2.07570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_nu[] = {
#include "textures/segment2/segment2.07580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ne[] = {
#include "textures/segment2/segment2.07590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_no[] = {
#include "textures/segment2/segment2.075A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ha[] = {
#include "textures/segment2/segment2.075B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_hi[] = {
#include "textures/segment2/segment2.075C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_fu[] = {
#include "textures/segment2/segment2.075D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_he[] = {
#include "textures/segment2/segment2.075E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ho[] = {
#include "textures/segment2/segment2.075F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ma[] = {
#include "textures/segment2/segment2.07600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_mi[] = {
#include "textures/segment2/segment2.07610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_mu[] = {
#include "textures/segment2/segment2.07620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_me[] = {
#include "textures/segment2/segment2.07630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_mo[] = {
#include "textures/segment2/segment2.07640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ya[] = {
#include "textures/segment2/segment2.07650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_yu[] = {
#include "textures/segment2/segment2.07660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_yo[] = {
#include "textures/segment2/segment2.07670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ra[] = {
#include "textures/segment2/segment2.07680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ri[] = {
#include "textures/segment2/segment2.07690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ru[] = {
#include "textures/segment2/segment2.076A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_re[] = {
#include "textures/segment2/segment2.076B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_ro[] = {
#include "textures/segment2/segment2.076C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_wa[] = {
#include "textures/segment2/segment2.076D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_wo[] = {
#include "textures/segment2/segment2.076E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_n[] = {
#include "textures/segment2/segment2.076F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_e[] = {
#include "textures/segment2/segment2.07700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_tsu[] = {
#include "textures/segment2/segment2.07710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_ya[] = {
#include "textures/segment2/segment2.07720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_yu[] = {
#include "textures/segment2/segment2.07730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_yo[] = {
#include "textures/segment2/segment2.07740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_a[] = {
#include "textures/segment2/segment2.07750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_i[] = {
#include "textures/segment2/segment2.07760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_o[] = {
#include "textures/segment2/segment2.07770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_hiragana_small_u[] = {
#include "textures/segment2/segment2.07780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_interpunct[] = {
#include "textures/segment2/segment2.07790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_comma[] = {
#include "textures/segment2/segment2.077A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_a[] = {
#include "textures/segment2/segment2.077B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_i[] = {
#include "textures/segment2/segment2.077C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_u[] = {
#include "textures/segment2/segment2.077D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_e[] = {
#include "textures/segment2/segment2.077E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_o[] = {
#include "textures/segment2/segment2.077F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ka[] = {
#include "textures/segment2/segment2.07800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ki[] = {
#include "textures/segment2/segment2.07810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ku[] = {
#include "textures/segment2/segment2.07820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ke[] = {
#include "textures/segment2/segment2.07830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ko[] = {
#include "textures/segment2/segment2.07840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_sa[] = {
#include "textures/segment2/segment2.07850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_shi[] = {
#include "textures/segment2/segment2.07860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_su[] = {
#include "textures/segment2/segment2.07870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_se[] = {
#include "textures/segment2/segment2.07880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_so[] = {
#include "textures/segment2/segment2.07890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ta[] = {
#include "textures/segment2/segment2.078A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_chi[] = {
#include "textures/segment2/segment2.078B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_tsu[] = {
#include "textures/segment2/segment2.078C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_te[] = {
#include "textures/segment2/segment2.078D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_to[] = {
#include "textures/segment2/segment2.078E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_na[] = {
#include "textures/segment2/segment2.078F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ni[] = {
#include "textures/segment2/segment2.07900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_nu[] = {
#include "textures/segment2/segment2.07910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ne[] = {
#include "textures/segment2/segment2.07920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_no[] = {
#include "textures/segment2/segment2.07930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ha[] = {
#include "textures/segment2/segment2.07940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_hi[] = {
#include "textures/segment2/segment2.07950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_fu[] = {
#include "textures/segment2/segment2.07960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_he[] = {
#include "textures/segment2/segment2.07970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ho[] = {
#include "textures/segment2/segment2.07980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ma[] = {
#include "textures/segment2/segment2.07990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_mi[] = {
#include "textures/segment2/segment2.079A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_mu[] = {
#include "textures/segment2/segment2.079B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_me[] = {
#include "textures/segment2/segment2.079C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_mo[] = {
#include "textures/segment2/segment2.079D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ya[] = {
#include "textures/segment2/segment2.079E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_yu[] = {
#include "textures/segment2/segment2.079F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_yo[] = {
#include "textures/segment2/segment2.07A00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ra[] = {
#include "textures/segment2/segment2.07A10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ri[] = {
#include "textures/segment2/segment2.07A20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ru[] = {
#include "textures/segment2/segment2.07A30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_re[] = {
#include "textures/segment2/segment2.07A40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_ro[] = {
#include "textures/segment2/segment2.07A50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_wa[] = {
#include "textures/segment2/segment2.07A60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_n[] = {
#include "textures/segment2/segment2.07A70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_e[] = {
#include "textures/segment2/segment2.07A80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_tsu[] = {
#include "textures/segment2/segment2.07A90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_ya[] = {
#include "textures/segment2/segment2.07AA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_yu[] = {
#include "textures/segment2/segment2.07AB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_yo[] = {
#include "textures/segment2/segment2.07AC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_a[] = {
#include "textures/segment2/segment2.07AD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_i[] = {
#include "textures/segment2/segment2.07AE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_u[] = {
#include "textures/segment2/segment2.07AF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_katakana_small_o[] = {
#include "textures/segment2/segment2.07B00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_double_quotation_open[] = {
#include "textures/segment2/segment2.07B10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_double_quotation_close[] = {
#include "textures/segment2/segment2.07B20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_jp_tilde[] = {
#include "textures/segment2/segment2.07B30.ia1.inc.c"
};

//ALIGNED8 static const Texture texture_font_char_jp_ellipsis[] = {
//#include "textures/segment2/segment2.07B40.ia1.inc.c"
//};
#endif

// EU Small Font
/**
#elif defined(VERSION_EU)

ALIGNED8 static const Texture texture_font_char_eu_0[] = {
#include "textures/segment2/font_graphics.05F00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_1[] = {
#include "textures/segment2/font_graphics.05F10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_2[] = {
#include "textures/segment2/font_graphics.05F20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_3[] = {
#include "textures/segment2/font_graphics.05F30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_4[] = {
#include "textures/segment2/font_graphics.05F40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_5[] = {
#include "textures/segment2/font_graphics.05F50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_6[] = {
#include "textures/segment2/font_graphics.05F60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_7[] = {
#include "textures/segment2/font_graphics.05F70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_8[] = {
#include "textures/segment2/font_graphics.05F80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_9[] = {
#include "textures/segment2/font_graphics.05F90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_A[] = {
#include "textures/segment2/font_graphics.05FA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_B[] = {
#include "textures/segment2/font_graphics.05FB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_C[] = {
#include "textures/segment2/font_graphics.05FC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_D[] = {
#include "textures/segment2/font_graphics.05FD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_E[] = {
#include "textures/segment2/font_graphics.05FE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_F[] = {
#include "textures/segment2/font_graphics.05FF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_G[] = {
#include "textures/segment2/font_graphics.06000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_H[] = {
#include "textures/segment2/font_graphics.06010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_I[] = {
#include "textures/segment2/font_graphics.06020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_J[] = {
#include "textures/segment2/font_graphics.06030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_K[] = {
#include "textures/segment2/font_graphics.06040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_L[] = {
#include "textures/segment2/font_graphics.06050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_M[] = {
#include "textures/segment2/font_graphics.06060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_N[] = {
#include "textures/segment2/font_graphics.06070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_O[] = {
#include "textures/segment2/font_graphics.06080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_P[] = {
#include "textures/segment2/font_graphics.06090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_Q[] = {
#include "textures/segment2/font_graphics.060A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_R[] = {
#include "textures/segment2/font_graphics.060B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_S[] = {
#include "textures/segment2/font_graphics.060C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_T[] = {
#include "textures/segment2/font_graphics.060D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_U[] = {
#include "textures/segment2/font_graphics.060E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_V[] = {
#include "textures/segment2/font_graphics.060F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_W[] = {
#include "textures/segment2/font_graphics.06100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_X[] = {
#include "textures/segment2/font_graphics.06110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_Y[] = {
#include "textures/segment2/font_graphics.06120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_Z[] = {
#include "textures/segment2/font_graphics.06130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_a[] = {
#include "textures/segment2/font_graphics.06140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_b[] = {
#include "textures/segment2/font_graphics.06150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_c[] = {
#include "textures/segment2/font_graphics.06160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_d[] = {
#include "textures/segment2/font_graphics.06170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_e[] = {
#include "textures/segment2/font_graphics.06180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_f[] = {
#include "textures/segment2/font_graphics.06190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_g[] = {
#include "textures/segment2/font_graphics.061A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_h[] = {
#include "textures/segment2/font_graphics.061B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_i[] = {
#include "textures/segment2/font_graphics.061C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_j[] = {
#include "textures/segment2/font_graphics.061D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_k[] = {
#include "textures/segment2/font_graphics.061E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_l[] = {
#include "textures/segment2/font_graphics.061F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_m[] = {
#include "textures/segment2/font_graphics.06200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_n[] = {
#include "textures/segment2/font_graphics.06210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_o[] = {
#include "textures/segment2/font_graphics.06220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_p[] = {
#include "textures/segment2/font_graphics.06230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_q[] = {
#include "textures/segment2/font_graphics.06240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_r[] = {
#include "textures/segment2/font_graphics.06250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_s[] = {
#include "textures/segment2/font_graphics.06260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_t[] = {
#include "textures/segment2/font_graphics.06270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_u[] = {
#include "textures/segment2/font_graphics.06280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_v[] = {
#include "textures/segment2/font_graphics.06290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_w[] = {
#include "textures/segment2/font_graphics.062A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_x[] = {
#include "textures/segment2/font_graphics.062B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_y[] = {
#include "textures/segment2/font_graphics.062C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_z[] = {
#include "textures/segment2/font_graphics.062D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_left_right_arrow[] = {
#include "textures/segment2/font_graphics.062E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_ampersand[] = {
#include "textures/segment2/font_graphics.062F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_exclamation[] = {
#include "textures/segment2/font_graphics.06300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_coin[] = {
#include "textures/segment2/font_graphics.06310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_multiply[] = {
#include "textures/segment2/font_graphics.06320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_open_parentheses[] = {
#include "textures/segment2/font_graphics.06330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_close_open_parentheses[] = {
#include "textures/segment2/font_graphics.06340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_close_parentheses[] = {
#include "textures/segment2/font_graphics.06350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_tilde[] = {
#include "textures/segment2/font_graphics.06360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_period[] = {
#include "textures/segment2/font_graphics.06370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_percent[] = {
#include "textures/segment2/font_graphics.06380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_interpunct[] = {
#include "textures/segment2/font_graphics.06390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_comma[] = {
#include "textures/segment2/font_graphics.063A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_apostrophe[] = {
#include "textures/segment2/font_graphics.063B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_question[] = {
#include "textures/segment2/font_graphics.063C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_star_filled[] = {
#include "textures/segment2/font_graphics.063D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_star_hollow[] = {
#include "textures/segment2/font_graphics.063E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_double_quote_open[] = {
#include "textures/segment2/font_graphics.063F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_double_quote_close[] = {
#include "textures/segment2/font_graphics.06400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_colon[] = {
#include "textures/segment2/font_graphics.06410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_EU_slash[] = {
#include "textures/segment2/font_graphics.06420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_A[] = {
#include "textures/segment2/font_graphics.06430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_B[] = {
#include "textures/segment2/font_graphics.06440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_C[] = {
#include "textures/segment2/font_graphics.06450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_Z[] = {
#include "textures/segment2/font_graphics.06460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_R[] = {
#include "textures/segment2/font_graphics.06470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_C_up[] = {
#include "textures/segment2/font_graphics.06480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_C_down[] = {
#include "textures/segment2/font_graphics.06490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_C_left[] = {
#include "textures/segment2/font_graphics.064A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_button_C_right[] = {
#include "textures/segment2/font_graphics.064B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_umlaut[] = {
#include "textures/segment2/font_graphics.064C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_circumflex[] = {
#include "textures/segment2/font_graphics.064D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_grave[] = {
#include "textures/segment2/font_graphics.064E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_acute[] = {
#include "textures/segment2/font_graphics.064F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_cedilla[] = {
#include "textures/segment2/font_graphics.06500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_unknown[] = {
#include "textures/segment2/font_graphics.06510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_Cedilla[] = {
#include "textures/segment2/font_graphics.06520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eu_eszeet[] = {
#include "textures/segment2/font_graphics.06530.ia1.inc.c"
};
 */
// US Small Font
//#else
ALIGNED8 static const Texture texture_font_char_us_0[] = {
#include "textures/segment2/font_graphics.05900.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_1[] = {
#include "textures/segment2/font_graphics.05940.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_2[] = {
#include "textures/segment2/font_graphics.05980.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_3[] = {
#include "textures/segment2/font_graphics.059C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_4[] = {
#include "textures/segment2/font_graphics.05A00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_5[] = {
#include "textures/segment2/font_graphics.05A40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_6[] = {
#include "textures/segment2/font_graphics.05A80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_7[] = {
#include "textures/segment2/font_graphics.05AC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_8[] = {
#include "textures/segment2/font_graphics.05B00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_9[] = {
#include "textures/segment2/font_graphics.05B40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_A[] = {
#include "textures/segment2/font_graphics.05B80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_B[] = {
#include "textures/segment2/font_graphics.05BC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_C[] = {
#include "textures/segment2/font_graphics.05C00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_D[] = {
#include "textures/segment2/font_graphics.05C40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_E[] = {
#include "textures/segment2/font_graphics.05C80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_F[] = {
#include "textures/segment2/font_graphics.05CC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_G[] = {
#include "textures/segment2/font_graphics.05D00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_H[] = {
#include "textures/segment2/font_graphics.05D40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_I[] = {
#include "textures/segment2/font_graphics.05D80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_J[] = {
#include "textures/segment2/font_graphics.05DC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_K[] = {
#include "textures/segment2/font_graphics.05E00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_L[] = {
#include "textures/segment2/font_graphics.05E40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_M[] = {
#include "textures/segment2/font_graphics.05E80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_N[] = {
#include "textures/segment2/font_graphics.05EC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_O[] = {
#include "textures/segment2/font_graphics.05F00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_P[] = {
#include "textures/segment2/font_graphics.05F40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_Q[] = {
#include "textures/segment2/font_graphics.05F80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_R[] = {
#include "textures/segment2/font_graphics.05FC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_S[] = {
#include "textures/segment2/font_graphics.06000.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_T[] = {
#include "textures/segment2/font_graphics.06040.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_U[] = {
#include "textures/segment2/font_graphics.06080.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_V[] = {
#include "textures/segment2/font_graphics.060C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_W[] = {
#include "textures/segment2/font_graphics.06100.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_X[] = {
#include "textures/segment2/font_graphics.06140.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_Y[] = {
#include "textures/segment2/font_graphics.06180.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_Z[] = {
#include "textures/segment2/font_graphics.061C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_a[] = {
#include "textures/segment2/font_graphics.06200.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_b[] = {
#include "textures/segment2/font_graphics.06240.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_c[] = {
#include "textures/segment2/font_graphics.06280.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_d[] = {
#include "textures/segment2/font_graphics.062C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_e[] = {
#include "textures/segment2/font_graphics.06300.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_f[] = {
#include "textures/segment2/font_graphics.06340.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_g[] = {
#include "textures/segment2/font_graphics.06380.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_h[] = {
#include "textures/segment2/font_graphics.063C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_i[] = {
#include "textures/segment2/font_graphics.06400.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_j[] = {
#include "textures/segment2/font_graphics.06440.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_k[] = {
#include "textures/segment2/font_graphics.06480.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_l[] = {
#include "textures/segment2/font_graphics.064C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_m[] = {
#include "textures/segment2/font_graphics.06500.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_n[] = {
#include "textures/segment2/font_graphics.06540.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_o[] = {
#include "textures/segment2/font_graphics.06580.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_p[] = {
#include "textures/segment2/font_graphics.065C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_q[] = {
#include "textures/segment2/font_graphics.06600.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_r[] = {
#include "textures/segment2/font_graphics.06640.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_s[] = {
#include "textures/segment2/font_graphics.06680.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_t[] = {
#include "textures/segment2/font_graphics.066C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_u[] = {
#include "textures/segment2/font_graphics.06700.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_v[] = {
#include "textures/segment2/font_graphics.06740.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_w[] = {
#include "textures/segment2/font_graphics.06780.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_x[] = {
#include "textures/segment2/font_graphics.067C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_y[] = {
#include "textures/segment2/font_graphics.06800.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_z[] = {
#include "textures/segment2/font_graphics.06840.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_left_right_arrow[] = {
#include "textures/segment2/font_graphics.06880.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_exclamation[] = {
#include "textures/segment2/font_graphics.068C0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_coin[] = {
#include "textures/segment2/font_graphics.06900.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_multiply[] = {
#include "textures/segment2/font_graphics.06940.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_open_parentheses[] = {
#include "textures/segment2/font_graphics.06980.ia4.inc.c"
};

//ALIGNED8 static const Texture texture_font_char_us_close_open_parentheses[] = {
//#include "textures/segment2/font_graphics.069C0.ia4.inc.c"
//};

ALIGNED8 static const Texture texture_font_char_us_close_parentheses[] = {
#include "textures/segment2/font_graphics.06A00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_tilde[] = {
#include "textures/segment2/font_graphics.06A40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_period[] = {
#include "textures/segment2/font_graphics.06A80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_percent[] = {
#include "textures/segment2/font_graphics.06AC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_interpunct[] = {
#include "textures/segment2/font_graphics.06B00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_comma[] = {
#include "textures/segment2/font_graphics.06B40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_apostrophe[] = {
#include "textures/segment2/font_graphics.06B80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_question[] = {
#include "textures/segment2/font_graphics.06BC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_star_filled[] = {
#include "textures/segment2/font_graphics.06C00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_star_hollow[] = {
#include "textures/segment2/font_graphics.06C40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_double_quote_open[] = {
#include "textures/segment2/font_graphics.06C80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_double_quote_close[] = {
#include "textures/segment2/font_graphics.06CC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_colon[] = {
#include "textures/segment2/font_graphics.06D00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_hyphen[] = {
#include "textures/segment2/font_graphics.06D40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_ampersand[] = {
#include "textures/segment2/font_graphics.06D80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_A[] = {
#include "textures/segment2/font_graphics.06DC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_B[] = {
#include "textures/segment2/font_graphics.06E00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_C[] = {
#include "textures/segment2/font_graphics.06E40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_Z[] = {
#include "textures/segment2/font_graphics.06E80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_R[] = {
#include "textures/segment2/font_graphics.06EC0.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_C_up[] = {
#include "textures/segment2/font_graphics.06F00.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_C_down[] = {
#include "textures/segment2/font_graphics.06F40.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_C_left[] = {
#include "textures/segment2/font_graphics.06F80.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_button_C_right[] = {
#include "textures/segment2/font_graphics.06FC0.ia4.inc.c"
};
//#endif

// Custom Font
ALIGNED8 static const Texture texture_font_char_plus[] = {
#include "textures/segment2/custom/font_graphics.plus.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_slash[] = {
#include "textures/segment2/custom/font_graphics.slash.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_backslash[] = {
#include "textures/segment2/custom/font_graphics.backslash.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_inverted_exclamation_mark[] = {
#include "textures/segment2/custom/font_graphics.inverted_exclamation_mark.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_inverted_question_mark[] = {
#include "textures/segment2/custom/font_graphics.inverted_question_mark.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_double_low_quote[] = {
#include "textures/segment2/custom/font_graphics.double_low_quote.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_eszett[] = {
#include "textures/segment2/custom/font_graphics.eszett.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_diacritic_grave[] = {
#include "textures/segment2/custom/font_graphics.grave.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_diacritic_acute[] = {
#include "textures/segment2/custom/font_graphics.acute.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_diacritic_circumflex[] = {
#include "textures/segment2/custom/font_graphics.circumflex.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_diacritic_tilde[] = {
#include "textures/segment2/custom/font_graphics.tilde_diacritic.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_diacritic_umlaut[] = {
#include "textures/segment2/custom/font_graphics.umlaut.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_diacritic_cedilla[] = {
#include "textures/segment2/custom/font_graphics.cedilla.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_us_i_no_dot[] = {
#include "textures/segment2/custom/font_graphics.i_no_dot.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_missing_character[] = {
#include "textures/segment2/custom/font_graphics.missing_character.ia4.inc.c"
};

#if defined(VERSION_CN)
ALIGNED8 static const Texture texture_font_char_cn_16800[] = {
#include "textures/segment2/segment2_cn.16800.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16840[] = {
#include "textures/segment2/segment2_cn.16840.ia4.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16880[] = {
#include "textures/segment2/segment2_cn.16880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16890[] = {
#include "textures/segment2/segment2_cn.16890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_168A0[] = {
#include "textures/segment2/segment2_cn.168A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_168B0[] = {
#include "textures/segment2/segment2_cn.168B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_168C0[] = {
#include "textures/segment2/segment2_cn.168C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_168D0[] = {
#include "textures/segment2/segment2_cn.168D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_168E0[] = {
#include "textures/segment2/segment2_cn.168E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_168F0[] = {
#include "textures/segment2/segment2_cn.168F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16900[] = {
#include "textures/segment2/segment2_cn.16900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16910[] = {
#include "textures/segment2/segment2_cn.16910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16920[] = {
#include "textures/segment2/segment2_cn.16920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16930[] = {
#include "textures/segment2/segment2_cn.16930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16940[] = {
#include "textures/segment2/segment2_cn.16940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16950[] = {
#include "textures/segment2/segment2_cn.16950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16960[] = {
#include "textures/segment2/segment2_cn.16960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16970[] = {
#include "textures/segment2/segment2_cn.16970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16980[] = {
#include "textures/segment2/segment2_cn.16980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16990[] = {
#include "textures/segment2/segment2_cn.16990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_169A0[] = {
#include "textures/segment2/segment2_cn.169A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_169B0[] = {
#include "textures/segment2/segment2_cn.169B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_169C0[] = {
#include "textures/segment2/segment2_cn.169C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_169D0[] = {
#include "textures/segment2/segment2_cn.169D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_169E0[] = {
#include "textures/segment2/segment2_cn.169E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_169F0[] = {
#include "textures/segment2/segment2_cn.169F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A00[] = {
#include "textures/segment2/segment2_cn.16A00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A10[] = {
#include "textures/segment2/segment2_cn.16A10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A20[] = {
#include "textures/segment2/segment2_cn.16A20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A30[] = {
#include "textures/segment2/segment2_cn.16A30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A40[] = {
#include "textures/segment2/segment2_cn.16A40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A50[] = {
#include "textures/segment2/segment2_cn.16A50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A60[] = {
#include "textures/segment2/segment2_cn.16A60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A70[] = {
#include "textures/segment2/segment2_cn.16A70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A80[] = {
#include "textures/segment2/segment2_cn.16A80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16A90[] = {
#include "textures/segment2/segment2_cn.16A90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16AA0[] = {
#include "textures/segment2/segment2_cn.16AA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16AB0[] = {
#include "textures/segment2/segment2_cn.16AB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16AC0[] = {
#include "textures/segment2/segment2_cn.16AC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16AD0[] = {
#include "textures/segment2/segment2_cn.16AD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16AE0[] = {
#include "textures/segment2/segment2_cn.16AE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16AF0[] = {
#include "textures/segment2/segment2_cn.16AF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B00[] = {
#include "textures/segment2/segment2_cn.16B00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B10[] = {
#include "textures/segment2/segment2_cn.16B10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B20[] = {
#include "textures/segment2/segment2_cn.16B20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B30[] = {
#include "textures/segment2/segment2_cn.16B30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B40[] = {
#include "textures/segment2/segment2_cn.16B40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B50[] = {
#include "textures/segment2/segment2_cn.16B50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B60[] = {
#include "textures/segment2/segment2_cn.16B60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B70[] = {
#include "textures/segment2/segment2_cn.16B70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B80[] = {
#include "textures/segment2/segment2_cn.16B80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16B90[] = {
#include "textures/segment2/segment2_cn.16B90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16BA0[] = {
#include "textures/segment2/segment2_cn.16BA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16BB0[] = {
#include "textures/segment2/segment2_cn.16BB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16BC0[] = {
#include "textures/segment2/segment2_cn.16BC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16BD0[] = {
#include "textures/segment2/segment2_cn.16BD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16BE0[] = {
#include "textures/segment2/segment2_cn.16BE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16BF0[] = {
#include "textures/segment2/segment2_cn.16BF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C00[] = {
#include "textures/segment2/segment2_cn.16C00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C10[] = {
#include "textures/segment2/segment2_cn.16C10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C20[] = {
#include "textures/segment2/segment2_cn.16C20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C30[] = {
#include "textures/segment2/segment2_cn.16C30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C40[] = {
#include "textures/segment2/segment2_cn.16C40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C50[] = {
#include "textures/segment2/segment2_cn.16C50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C60[] = {
#include "textures/segment2/segment2_cn.16C60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C70[] = {
#include "textures/segment2/segment2_cn.16C70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C80[] = {
#include "textures/segment2/segment2_cn.16C80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16C90[] = {
#include "textures/segment2/segment2_cn.16C90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16CA0[] = {
#include "textures/segment2/segment2_cn.16CA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16CB0[] = {
#include "textures/segment2/segment2_cn.16CB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16CC0[] = {
#include "textures/segment2/segment2_cn.16CC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16CD0[] = {
#include "textures/segment2/segment2_cn.16CD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16CE0[] = {
#include "textures/segment2/segment2_cn.16CE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16CF0[] = {
#include "textures/segment2/segment2_cn.16CF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D00[] = {
#include "textures/segment2/segment2_cn.16D00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D10[] = {
#include "textures/segment2/segment2_cn.16D10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D20[] = {
#include "textures/segment2/segment2_cn.16D20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D30[] = {
#include "textures/segment2/segment2_cn.16D30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D40[] = {
#include "textures/segment2/segment2_cn.16D40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D50[] = {
#include "textures/segment2/segment2_cn.16D50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D60[] = {
#include "textures/segment2/segment2_cn.16D60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D70[] = {
#include "textures/segment2/segment2_cn.16D70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D80[] = {
#include "textures/segment2/segment2_cn.16D80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16D90[] = {
#include "textures/segment2/segment2_cn.16D90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16DA0[] = {
#include "textures/segment2/segment2_cn.16DA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16DB0[] = {
#include "textures/segment2/segment2_cn.16DB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16DC0[] = {
#include "textures/segment2/segment2_cn.16DC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16DD0[] = {
#include "textures/segment2/segment2_cn.16DD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16DE0[] = {
#include "textures/segment2/segment2_cn.16DE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16DF0[] = {
#include "textures/segment2/segment2_cn.16DF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E00[] = {
#include "textures/segment2/segment2_cn.16E00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E10[] = {
#include "textures/segment2/segment2_cn.16E10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E20[] = {
#include "textures/segment2/segment2_cn.16E20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E30[] = {
#include "textures/segment2/segment2_cn.16E30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E40[] = {
#include "textures/segment2/segment2_cn.16E40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E50[] = {
#include "textures/segment2/segment2_cn.16E50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E60[] = {
#include "textures/segment2/segment2_cn.16E60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E70[] = {
#include "textures/segment2/segment2_cn.16E70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E80[] = {
#include "textures/segment2/segment2_cn.16E80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16E90[] = {
#include "textures/segment2/segment2_cn.16E90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16EA0[] = {
#include "textures/segment2/segment2_cn.16EA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16EB0[] = {
#include "textures/segment2/segment2_cn.16EB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16EC0[] = {
#include "textures/segment2/segment2_cn.16EC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16ED0[] = {
#include "textures/segment2/segment2_cn.16ED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16EE0[] = {
#include "textures/segment2/segment2_cn.16EE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16EF0[] = {
#include "textures/segment2/segment2_cn.16EF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F00[] = {
#include "textures/segment2/segment2_cn.16F00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F10[] = {
#include "textures/segment2/segment2_cn.16F10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F20[] = {
#include "textures/segment2/segment2_cn.16F20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F30[] = {
#include "textures/segment2/segment2_cn.16F30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F40[] = {
#include "textures/segment2/segment2_cn.16F40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F50[] = {
#include "textures/segment2/segment2_cn.16F50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F60[] = {
#include "textures/segment2/segment2_cn.16F60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F70[] = {
#include "textures/segment2/segment2_cn.16F70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F80[] = {
#include "textures/segment2/segment2_cn.16F80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16F90[] = {
#include "textures/segment2/segment2_cn.16F90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16FA0[] = {
#include "textures/segment2/segment2_cn.16FA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16FB0[] = {
#include "textures/segment2/segment2_cn.16FB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16FC0[] = {
#include "textures/segment2/segment2_cn.16FC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16FD0[] = {
#include "textures/segment2/segment2_cn.16FD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16FE0[] = {
#include "textures/segment2/segment2_cn.16FE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_16FF0[] = {
#include "textures/segment2/segment2_cn.16FF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17000[] = {
#include "textures/segment2/segment2_cn.17000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17010[] = {
#include "textures/segment2/segment2_cn.17010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17020[] = {
#include "textures/segment2/segment2_cn.17020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17030[] = {
#include "textures/segment2/segment2_cn.17030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17040[] = {
#include "textures/segment2/segment2_cn.17040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17050[] = {
#include "textures/segment2/segment2_cn.17050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17060[] = {
#include "textures/segment2/segment2_cn.17060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17070[] = {
#include "textures/segment2/segment2_cn.17070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17080[] = {
#include "textures/segment2/segment2_cn.17080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17090[] = {
#include "textures/segment2/segment2_cn.17090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_170A0[] = {
#include "textures/segment2/segment2_cn.170A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_170B0[] = {
#include "textures/segment2/segment2_cn.170B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_170C0[] = {
#include "textures/segment2/segment2_cn.170C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_170D0[] = {
#include "textures/segment2/segment2_cn.170D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_170E0[] = {
#include "textures/segment2/segment2_cn.170E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_170F0[] = {
#include "textures/segment2/segment2_cn.170F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17100[] = {
#include "textures/segment2/segment2_cn.17100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17110[] = {
#include "textures/segment2/segment2_cn.17110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17120[] = {
#include "textures/segment2/segment2_cn.17120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17130[] = {
#include "textures/segment2/segment2_cn.17130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17140[] = {
#include "textures/segment2/segment2_cn.17140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17150[] = {
#include "textures/segment2/segment2_cn.17150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17160[] = {
#include "textures/segment2/segment2_cn.17160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17170[] = {
#include "textures/segment2/segment2_cn.17170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17180[] = {
#include "textures/segment2/segment2_cn.17180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17190[] = {
#include "textures/segment2/segment2_cn.17190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_171A0[] = {
#include "textures/segment2/segment2_cn.171A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_171B0[] = {
#include "textures/segment2/segment2_cn.171B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_171C0[] = {
#include "textures/segment2/segment2_cn.171C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_171D0[] = {
#include "textures/segment2/segment2_cn.171D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_171E0[] = {
#include "textures/segment2/segment2_cn.171E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_171F0[] = {
#include "textures/segment2/segment2_cn.171F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17200[] = {
#include "textures/segment2/segment2_cn.17200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17210[] = {
#include "textures/segment2/segment2_cn.17210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17220[] = {
#include "textures/segment2/segment2_cn.17220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17230[] = {
#include "textures/segment2/segment2_cn.17230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17240[] = {
#include "textures/segment2/segment2_cn.17240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17250[] = {
#include "textures/segment2/segment2_cn.17250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17260[] = {
#include "textures/segment2/segment2_cn.17260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17270[] = {
#include "textures/segment2/segment2_cn.17270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17280[] = {
#include "textures/segment2/segment2_cn.17280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17290[] = {
#include "textures/segment2/segment2_cn.17290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_172A0[] = {
#include "textures/segment2/segment2_cn.172A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_172B0[] = {
#include "textures/segment2/segment2_cn.172B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_172C0[] = {
#include "textures/segment2/segment2_cn.172C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_172D0[] = {
#include "textures/segment2/segment2_cn.172D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_172E0[] = {
#include "textures/segment2/segment2_cn.172E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_172F0[] = {
#include "textures/segment2/segment2_cn.172F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17300[] = {
#include "textures/segment2/segment2_cn.17300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17310[] = {
#include "textures/segment2/segment2_cn.17310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17320[] = {
#include "textures/segment2/segment2_cn.17320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17330[] = {
#include "textures/segment2/segment2_cn.17330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17340[] = {
#include "textures/segment2/segment2_cn.17340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17350[] = {
#include "textures/segment2/segment2_cn.17350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17360[] = {
#include "textures/segment2/segment2_cn.17360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17370[] = {
#include "textures/segment2/segment2_cn.17370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17380[] = {
#include "textures/segment2/segment2_cn.17380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17390[] = {
#include "textures/segment2/segment2_cn.17390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_173A0[] = {
#include "textures/segment2/segment2_cn.173A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_173B0[] = {
#include "textures/segment2/segment2_cn.173B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_173C0[] = {
#include "textures/segment2/segment2_cn.173C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_173D0[] = {
#include "textures/segment2/segment2_cn.173D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_173E0[] = {
#include "textures/segment2/segment2_cn.173E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_173F0[] = {
#include "textures/segment2/segment2_cn.173F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17400[] = {
#include "textures/segment2/segment2_cn.17400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17410[] = {
#include "textures/segment2/segment2_cn.17410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17420[] = {
#include "textures/segment2/segment2_cn.17420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17430[] = {
#include "textures/segment2/segment2_cn.17430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17440[] = {
#include "textures/segment2/segment2_cn.17440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17450[] = {
#include "textures/segment2/segment2_cn.17450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17460[] = {
#include "textures/segment2/segment2_cn.17460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17470[] = {
#include "textures/segment2/segment2_cn.17470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17480[] = {
#include "textures/segment2/segment2_cn.17480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17490[] = {
#include "textures/segment2/segment2_cn.17490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_174A0[] = {
#include "textures/segment2/segment2_cn.174A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_174B0[] = {
#include "textures/segment2/segment2_cn.174B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_174C0[] = {
#include "textures/segment2/segment2_cn.174C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_174D0[] = {
#include "textures/segment2/segment2_cn.174D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_174E0[] = {
#include "textures/segment2/segment2_cn.174E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_174F0[] = {
#include "textures/segment2/segment2_cn.174F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17500[] = {
#include "textures/segment2/segment2_cn.17500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17510[] = {
#include "textures/segment2/segment2_cn.17510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17520[] = {
#include "textures/segment2/segment2_cn.17520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17530[] = {
#include "textures/segment2/segment2_cn.17530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17540[] = {
#include "textures/segment2/segment2_cn.17540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17550[] = {
#include "textures/segment2/segment2_cn.17550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17560[] = {
#include "textures/segment2/segment2_cn.17560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17570[] = {
#include "textures/segment2/segment2_cn.17570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17580[] = {
#include "textures/segment2/segment2_cn.17580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17590[] = {
#include "textures/segment2/segment2_cn.17590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_175A0[] = {
#include "textures/segment2/segment2_cn.175A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_175B0[] = {
#include "textures/segment2/segment2_cn.175B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_175C0[] = {
#include "textures/segment2/segment2_cn.175C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_175D0[] = {
#include "textures/segment2/segment2_cn.175D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_175E0[] = {
#include "textures/segment2/segment2_cn.175E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_175F0[] = {
#include "textures/segment2/segment2_cn.175F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17600[] = {
#include "textures/segment2/segment2_cn.17600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17610[] = {
#include "textures/segment2/segment2_cn.17610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17620[] = {
#include "textures/segment2/segment2_cn.17620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17630[] = {
#include "textures/segment2/segment2_cn.17630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17640[] = {
#include "textures/segment2/segment2_cn.17640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17650[] = {
#include "textures/segment2/segment2_cn.17650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17660[] = {
#include "textures/segment2/segment2_cn.17660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17670[] = {
#include "textures/segment2/segment2_cn.17670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17680[] = {
#include "textures/segment2/segment2_cn.17680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17690[] = {
#include "textures/segment2/segment2_cn.17690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_176A0[] = {
#include "textures/segment2/segment2_cn.176A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_176B0[] = {
#include "textures/segment2/segment2_cn.176B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_176C0[] = {
#include "textures/segment2/segment2_cn.176C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_176D0[] = {
#include "textures/segment2/segment2_cn.176D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_176E0[] = {
#include "textures/segment2/segment2_cn.176E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_176F0[] = {
#include "textures/segment2/segment2_cn.176F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17700[] = {
#include "textures/segment2/segment2_cn.17700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17710[] = {
#include "textures/segment2/segment2_cn.17710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17720[] = {
#include "textures/segment2/segment2_cn.17720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17730[] = {
#include "textures/segment2/segment2_cn.17730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17740[] = {
#include "textures/segment2/segment2_cn.17740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17750[] = {
#include "textures/segment2/segment2_cn.17750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17760[] = {
#include "textures/segment2/segment2_cn.17760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17770[] = {
#include "textures/segment2/segment2_cn.17770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17780[] = {
#include "textures/segment2/segment2_cn.17780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17790[] = {
#include "textures/segment2/segment2_cn.17790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_177A0[] = {
#include "textures/segment2/segment2_cn.177A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_177B0[] = {
#include "textures/segment2/segment2_cn.177B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_177C0[] = {
#include "textures/segment2/segment2_cn.177C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_177D0[] = {
#include "textures/segment2/segment2_cn.177D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_177E0[] = {
#include "textures/segment2/segment2_cn.177E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_177F0[] = {
#include "textures/segment2/segment2_cn.177F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17800[] = {
#include "textures/segment2/segment2_cn.17800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17810[] = {
#include "textures/segment2/segment2_cn.17810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17820[] = {
#include "textures/segment2/segment2_cn.17820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17830[] = {
#include "textures/segment2/segment2_cn.17830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17840[] = {
#include "textures/segment2/segment2_cn.17840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17850[] = {
#include "textures/segment2/segment2_cn.17850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17860[] = {
#include "textures/segment2/segment2_cn.17860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17870[] = {
#include "textures/segment2/segment2_cn.17870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17880[] = {
#include "textures/segment2/segment2_cn.17880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17890[] = {
#include "textures/segment2/segment2_cn.17890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_178A0[] = {
#include "textures/segment2/segment2_cn.178A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_178B0[] = {
#include "textures/segment2/segment2_cn.178B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_178C0[] = {
#include "textures/segment2/segment2_cn.178C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_178D0[] = {
#include "textures/segment2/segment2_cn.178D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_178E0[] = {
#include "textures/segment2/segment2_cn.178E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_178F0[] = {
#include "textures/segment2/segment2_cn.178F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17900[] = {
#include "textures/segment2/segment2_cn.17900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17910[] = {
#include "textures/segment2/segment2_cn.17910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17920[] = {
#include "textures/segment2/segment2_cn.17920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17930[] = {
#include "textures/segment2/segment2_cn.17930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17940[] = {
#include "textures/segment2/segment2_cn.17940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17950[] = {
#include "textures/segment2/segment2_cn.17950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17960[] = {
#include "textures/segment2/segment2_cn.17960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17970[] = {
#include "textures/segment2/segment2_cn.17970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17980[] = {
#include "textures/segment2/segment2_cn.17980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17990[] = {
#include "textures/segment2/segment2_cn.17990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_179A0[] = {
#include "textures/segment2/segment2_cn.179A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_179B0[] = {
#include "textures/segment2/segment2_cn.179B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_179C0[] = {
#include "textures/segment2/segment2_cn.179C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_179D0[] = {
#include "textures/segment2/segment2_cn.179D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_179E0[] = {
#include "textures/segment2/segment2_cn.179E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_179F0[] = {
#include "textures/segment2/segment2_cn.179F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A00[] = {
#include "textures/segment2/segment2_cn.17A00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A10[] = {
#include "textures/segment2/segment2_cn.17A10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A20[] = {
#include "textures/segment2/segment2_cn.17A20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A30[] = {
#include "textures/segment2/segment2_cn.17A30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A40[] = {
#include "textures/segment2/segment2_cn.17A40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A50[] = {
#include "textures/segment2/segment2_cn.17A50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A60[] = {
#include "textures/segment2/segment2_cn.17A60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A70[] = {
#include "textures/segment2/segment2_cn.17A70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A80[] = {
#include "textures/segment2/segment2_cn.17A80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17A90[] = {
#include "textures/segment2/segment2_cn.17A90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17AA0[] = {
#include "textures/segment2/segment2_cn.17AA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17AB0[] = {
#include "textures/segment2/segment2_cn.17AB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17AC0[] = {
#include "textures/segment2/segment2_cn.17AC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17AD0[] = {
#include "textures/segment2/segment2_cn.17AD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17AE0[] = {
#include "textures/segment2/segment2_cn.17AE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17AF0[] = {
#include "textures/segment2/segment2_cn.17AF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B00[] = {
#include "textures/segment2/segment2_cn.17B00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B10[] = {
#include "textures/segment2/segment2_cn.17B10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B20[] = {
#include "textures/segment2/segment2_cn.17B20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B30[] = {
#include "textures/segment2/segment2_cn.17B30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B40[] = {
#include "textures/segment2/segment2_cn.17B40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B50[] = {
#include "textures/segment2/segment2_cn.17B50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B60[] = {
#include "textures/segment2/segment2_cn.17B60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B70[] = {
#include "textures/segment2/segment2_cn.17B70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B80[] = {
#include "textures/segment2/segment2_cn.17B80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17B90[] = {
#include "textures/segment2/segment2_cn.17B90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17BA0[] = {
#include "textures/segment2/segment2_cn.17BA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17BB0[] = {
#include "textures/segment2/segment2_cn.17BB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17BC0[] = {
#include "textures/segment2/segment2_cn.17BC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17BD0[] = {
#include "textures/segment2/segment2_cn.17BD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17BE0[] = {
#include "textures/segment2/segment2_cn.17BE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17BF0[] = {
#include "textures/segment2/segment2_cn.17BF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C00[] = {
#include "textures/segment2/segment2_cn.17C00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C10[] = {
#include "textures/segment2/segment2_cn.17C10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C20[] = {
#include "textures/segment2/segment2_cn.17C20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C30[] = {
#include "textures/segment2/segment2_cn.17C30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C40[] = {
#include "textures/segment2/segment2_cn.17C40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C50[] = {
#include "textures/segment2/segment2_cn.17C50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C60[] = {
#include "textures/segment2/segment2_cn.17C60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C70[] = {
#include "textures/segment2/segment2_cn.17C70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C80[] = {
#include "textures/segment2/segment2_cn.17C80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17C90[] = {
#include "textures/segment2/segment2_cn.17C90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17CA0[] = {
#include "textures/segment2/segment2_cn.17CA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17CB0[] = {
#include "textures/segment2/segment2_cn.17CB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17CC0[] = {
#include "textures/segment2/segment2_cn.17CC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17CD0[] = {
#include "textures/segment2/segment2_cn.17CD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17CE0[] = {
#include "textures/segment2/segment2_cn.17CE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17CF0[] = {
#include "textures/segment2/segment2_cn.17CF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D00[] = {
#include "textures/segment2/segment2_cn.17D00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D10[] = {
#include "textures/segment2/segment2_cn.17D10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D20[] = {
#include "textures/segment2/segment2_cn.17D20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D30[] = {
#include "textures/segment2/segment2_cn.17D30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D40[] = {
#include "textures/segment2/segment2_cn.17D40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D50[] = {
#include "textures/segment2/segment2_cn.17D50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D60[] = {
#include "textures/segment2/segment2_cn.17D60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D70[] = {
#include "textures/segment2/segment2_cn.17D70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D80[] = {
#include "textures/segment2/segment2_cn.17D80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17D90[] = {
#include "textures/segment2/segment2_cn.17D90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17DA0[] = {
#include "textures/segment2/segment2_cn.17DA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17DB0[] = {
#include "textures/segment2/segment2_cn.17DB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17DC0[] = {
#include "textures/segment2/segment2_cn.17DC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17DD0[] = {
#include "textures/segment2/segment2_cn.17DD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17DE0[] = {
#include "textures/segment2/segment2_cn.17DE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17DF0[] = {
#include "textures/segment2/segment2_cn.17DF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E00[] = {
#include "textures/segment2/segment2_cn.17E00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E10[] = {
#include "textures/segment2/segment2_cn.17E10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E20[] = {
#include "textures/segment2/segment2_cn.17E20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E30[] = {
#include "textures/segment2/segment2_cn.17E30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E40[] = {
#include "textures/segment2/segment2_cn.17E40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E50[] = {
#include "textures/segment2/segment2_cn.17E50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E60[] = {
#include "textures/segment2/segment2_cn.17E60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E70[] = {
#include "textures/segment2/segment2_cn.17E70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E80[] = {
#include "textures/segment2/segment2_cn.17E80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17E90[] = {
#include "textures/segment2/segment2_cn.17E90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17EA0[] = {
#include "textures/segment2/segment2_cn.17EA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17EB0[] = {
#include "textures/segment2/segment2_cn.17EB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17EC0[] = {
#include "textures/segment2/segment2_cn.17EC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17ED0[] = {
#include "textures/segment2/segment2_cn.17ED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17EE0[] = {
#include "textures/segment2/segment2_cn.17EE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17EF0[] = {
#include "textures/segment2/segment2_cn.17EF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F00[] = {
#include "textures/segment2/segment2_cn.17F00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F10[] = {
#include "textures/segment2/segment2_cn.17F10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F20[] = {
#include "textures/segment2/segment2_cn.17F20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F30[] = {
#include "textures/segment2/segment2_cn.17F30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F40[] = {
#include "textures/segment2/segment2_cn.17F40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F50[] = {
#include "textures/segment2/segment2_cn.17F50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F60[] = {
#include "textures/segment2/segment2_cn.17F60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F70[] = {
#include "textures/segment2/segment2_cn.17F70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F80[] = {
#include "textures/segment2/segment2_cn.17F80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17F90[] = {
#include "textures/segment2/segment2_cn.17F90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17FA0[] = {
#include "textures/segment2/segment2_cn.17FA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17FB0[] = {
#include "textures/segment2/segment2_cn.17FB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17FC0[] = {
#include "textures/segment2/segment2_cn.17FC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17FD0[] = {
#include "textures/segment2/segment2_cn.17FD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17FE0[] = {
#include "textures/segment2/segment2_cn.17FE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_17FF0[] = {
#include "textures/segment2/segment2_cn.17FF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18000[] = {
#include "textures/segment2/segment2_cn.18000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18010[] = {
#include "textures/segment2/segment2_cn.18010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18020[] = {
#include "textures/segment2/segment2_cn.18020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18030[] = {
#include "textures/segment2/segment2_cn.18030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18040[] = {
#include "textures/segment2/segment2_cn.18040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18050[] = {
#include "textures/segment2/segment2_cn.18050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18060[] = {
#include "textures/segment2/segment2_cn.18060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18070[] = {
#include "textures/segment2/segment2_cn.18070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18080[] = {
#include "textures/segment2/segment2_cn.18080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18090[] = {
#include "textures/segment2/segment2_cn.18090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_180A0[] = {
#include "textures/segment2/segment2_cn.180A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_180B0[] = {
#include "textures/segment2/segment2_cn.180B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_180C0[] = {
#include "textures/segment2/segment2_cn.180C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_180D0[] = {
#include "textures/segment2/segment2_cn.180D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_180E0[] = {
#include "textures/segment2/segment2_cn.180E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_180F0[] = {
#include "textures/segment2/segment2_cn.180F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18100[] = {
#include "textures/segment2/segment2_cn.18100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18110[] = {
#include "textures/segment2/segment2_cn.18110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18120[] = {
#include "textures/segment2/segment2_cn.18120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18130[] = {
#include "textures/segment2/segment2_cn.18130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18140[] = {
#include "textures/segment2/segment2_cn.18140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18150[] = {
#include "textures/segment2/segment2_cn.18150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18160[] = {
#include "textures/segment2/segment2_cn.18160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18170[] = {
#include "textures/segment2/segment2_cn.18170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18180[] = {
#include "textures/segment2/segment2_cn.18180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18190[] = {
#include "textures/segment2/segment2_cn.18190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_181A0[] = {
#include "textures/segment2/segment2_cn.181A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_181B0[] = {
#include "textures/segment2/segment2_cn.181B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_181C0[] = {
#include "textures/segment2/segment2_cn.181C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_181D0[] = {
#include "textures/segment2/segment2_cn.181D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_181E0[] = {
#include "textures/segment2/segment2_cn.181E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_181F0[] = {
#include "textures/segment2/segment2_cn.181F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18200[] = {
#include "textures/segment2/segment2_cn.18200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18210[] = {
#include "textures/segment2/segment2_cn.18210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18220[] = {
#include "textures/segment2/segment2_cn.18220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18230[] = {
#include "textures/segment2/segment2_cn.18230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18240[] = {
#include "textures/segment2/segment2_cn.18240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18250[] = {
#include "textures/segment2/segment2_cn.18250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18260[] = {
#include "textures/segment2/segment2_cn.18260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18270[] = {
#include "textures/segment2/segment2_cn.18270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18280[] = {
#include "textures/segment2/segment2_cn.18280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18290[] = {
#include "textures/segment2/segment2_cn.18290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_182A0[] = {
#include "textures/segment2/segment2_cn.182A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_182B0[] = {
#include "textures/segment2/segment2_cn.182B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_182C0[] = {
#include "textures/segment2/segment2_cn.182C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_182D0[] = {
#include "textures/segment2/segment2_cn.182D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_182E0[] = {
#include "textures/segment2/segment2_cn.182E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_182F0[] = {
#include "textures/segment2/segment2_cn.182F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18300[] = {
#include "textures/segment2/segment2_cn.18300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18310[] = {
#include "textures/segment2/segment2_cn.18310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18320[] = {
#include "textures/segment2/segment2_cn.18320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18330[] = {
#include "textures/segment2/segment2_cn.18330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18340[] = {
#include "textures/segment2/segment2_cn.18340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18350[] = {
#include "textures/segment2/segment2_cn.18350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18360[] = {
#include "textures/segment2/segment2_cn.18360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18370[] = {
#include "textures/segment2/segment2_cn.18370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18380[] = {
#include "textures/segment2/segment2_cn.18380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18390[] = {
#include "textures/segment2/segment2_cn.18390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_183A0[] = {
#include "textures/segment2/segment2_cn.183A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_183B0[] = {
#include "textures/segment2/segment2_cn.183B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_183C0[] = {
#include "textures/segment2/segment2_cn.183C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_183D0[] = {
#include "textures/segment2/segment2_cn.183D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_183E0[] = {
#include "textures/segment2/segment2_cn.183E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_183F0[] = {
#include "textures/segment2/segment2_cn.183F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18400[] = {
#include "textures/segment2/segment2_cn.18400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18410[] = {
#include "textures/segment2/segment2_cn.18410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18420[] = {
#include "textures/segment2/segment2_cn.18420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18430[] = {
#include "textures/segment2/segment2_cn.18430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18440[] = {
#include "textures/segment2/segment2_cn.18440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18450[] = {
#include "textures/segment2/segment2_cn.18450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18460[] = {
#include "textures/segment2/segment2_cn.18460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18470[] = {
#include "textures/segment2/segment2_cn.18470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18480[] = {
#include "textures/segment2/segment2_cn.18480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18490[] = {
#include "textures/segment2/segment2_cn.18490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_184A0[] = {
#include "textures/segment2/segment2_cn.184A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_184B0[] = {
#include "textures/segment2/segment2_cn.184B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_184C0[] = {
#include "textures/segment2/segment2_cn.184C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_184D0[] = {
#include "textures/segment2/segment2_cn.184D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_184E0[] = {
#include "textures/segment2/segment2_cn.184E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_184F0[] = {
#include "textures/segment2/segment2_cn.184F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18500[] = {
#include "textures/segment2/segment2_cn.18500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18510[] = {
#include "textures/segment2/segment2_cn.18510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18520[] = {
#include "textures/segment2/segment2_cn.18520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18530[] = {
#include "textures/segment2/segment2_cn.18530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18540[] = {
#include "textures/segment2/segment2_cn.18540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18550[] = {
#include "textures/segment2/segment2_cn.18550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18560[] = {
#include "textures/segment2/segment2_cn.18560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18570[] = {
#include "textures/segment2/segment2_cn.18570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18580[] = {
#include "textures/segment2/segment2_cn.18580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18590[] = {
#include "textures/segment2/segment2_cn.18590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_185A0[] = {
#include "textures/segment2/segment2_cn.185A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_185B0[] = {
#include "textures/segment2/segment2_cn.185B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_185C0[] = {
#include "textures/segment2/segment2_cn.185C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_185D0[] = {
#include "textures/segment2/segment2_cn.185D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_185E0[] = {
#include "textures/segment2/segment2_cn.185E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_185F0[] = {
#include "textures/segment2/segment2_cn.185F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18600[] = {
#include "textures/segment2/segment2_cn.18600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18610[] = {
#include "textures/segment2/segment2_cn.18610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18620[] = {
#include "textures/segment2/segment2_cn.18620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18630[] = {
#include "textures/segment2/segment2_cn.18630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18640[] = {
#include "textures/segment2/segment2_cn.18640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18650[] = {
#include "textures/segment2/segment2_cn.18650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18660[] = {
#include "textures/segment2/segment2_cn.18660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18670[] = {
#include "textures/segment2/segment2_cn.18670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18680[] = {
#include "textures/segment2/segment2_cn.18680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18690[] = {
#include "textures/segment2/segment2_cn.18690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_186A0[] = {
#include "textures/segment2/segment2_cn.186A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_186B0[] = {
#include "textures/segment2/segment2_cn.186B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_186C0[] = {
#include "textures/segment2/segment2_cn.186C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_186D0[] = {
#include "textures/segment2/segment2_cn.186D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_186E0[] = {
#include "textures/segment2/segment2_cn.186E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_186F0[] = {
#include "textures/segment2/segment2_cn.186F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18700[] = {
#include "textures/segment2/segment2_cn.18700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18710[] = {
#include "textures/segment2/segment2_cn.18710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18720[] = {
#include "textures/segment2/segment2_cn.18720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18730[] = {
#include "textures/segment2/segment2_cn.18730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18740[] = {
#include "textures/segment2/segment2_cn.18740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18750[] = {
#include "textures/segment2/segment2_cn.18750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18760[] = {
#include "textures/segment2/segment2_cn.18760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18770[] = {
#include "textures/segment2/segment2_cn.18770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18780[] = {
#include "textures/segment2/segment2_cn.18780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18790[] = {
#include "textures/segment2/segment2_cn.18790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_187A0[] = {
#include "textures/segment2/segment2_cn.187A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_187B0[] = {
#include "textures/segment2/segment2_cn.187B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_187C0[] = {
#include "textures/segment2/segment2_cn.187C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_187D0[] = {
#include "textures/segment2/segment2_cn.187D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_187E0[] = {
#include "textures/segment2/segment2_cn.187E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_187F0[] = {
#include "textures/segment2/segment2_cn.187F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18800[] = {
#include "textures/segment2/segment2_cn.18800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18810[] = {
#include "textures/segment2/segment2_cn.18810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18820[] = {
#include "textures/segment2/segment2_cn.18820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18830[] = {
#include "textures/segment2/segment2_cn.18830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18840[] = {
#include "textures/segment2/segment2_cn.18840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18850[] = {
#include "textures/segment2/segment2_cn.18850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18860[] = {
#include "textures/segment2/segment2_cn.18860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18870[] = {
#include "textures/segment2/segment2_cn.18870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18880[] = {
#include "textures/segment2/segment2_cn.18880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18890[] = {
#include "textures/segment2/segment2_cn.18890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_188A0[] = {
#include "textures/segment2/segment2_cn.188A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_188B0[] = {
#include "textures/segment2/segment2_cn.188B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_188C0[] = {
#include "textures/segment2/segment2_cn.188C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_188D0[] = {
#include "textures/segment2/segment2_cn.188D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_188E0[] = {
#include "textures/segment2/segment2_cn.188E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_188F0[] = {
#include "textures/segment2/segment2_cn.188F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18900[] = {
#include "textures/segment2/segment2_cn.18900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18910[] = {
#include "textures/segment2/segment2_cn.18910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18920[] = {
#include "textures/segment2/segment2_cn.18920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18930[] = {
#include "textures/segment2/segment2_cn.18930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18940[] = {
#include "textures/segment2/segment2_cn.18940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18950[] = {
#include "textures/segment2/segment2_cn.18950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18960[] = {
#include "textures/segment2/segment2_cn.18960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18970[] = {
#include "textures/segment2/segment2_cn.18970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18980[] = {
#include "textures/segment2/segment2_cn.18980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18990[] = {
#include "textures/segment2/segment2_cn.18990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_189A0[] = {
#include "textures/segment2/segment2_cn.189A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_189B0[] = {
#include "textures/segment2/segment2_cn.189B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_189C0[] = {
#include "textures/segment2/segment2_cn.189C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_189D0[] = {
#include "textures/segment2/segment2_cn.189D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_189E0[] = {
#include "textures/segment2/segment2_cn.189E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_189F0[] = {
#include "textures/segment2/segment2_cn.189F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A00[] = {
#include "textures/segment2/segment2_cn.18A00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A10[] = {
#include "textures/segment2/segment2_cn.18A10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A20[] = {
#include "textures/segment2/segment2_cn.18A20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A30[] = {
#include "textures/segment2/segment2_cn.18A30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A40[] = {
#include "textures/segment2/segment2_cn.18A40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A50[] = {
#include "textures/segment2/segment2_cn.18A50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A60[] = {
#include "textures/segment2/segment2_cn.18A60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A70[] = {
#include "textures/segment2/segment2_cn.18A70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A80[] = {
#include "textures/segment2/segment2_cn.18A80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18A90[] = {
#include "textures/segment2/segment2_cn.18A90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18AA0[] = {
#include "textures/segment2/segment2_cn.18AA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18AB0[] = {
#include "textures/segment2/segment2_cn.18AB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18AC0[] = {
#include "textures/segment2/segment2_cn.18AC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18AD0[] = {
#include "textures/segment2/segment2_cn.18AD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18AE0[] = {
#include "textures/segment2/segment2_cn.18AE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18AF0[] = {
#include "textures/segment2/segment2_cn.18AF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B00[] = {
#include "textures/segment2/segment2_cn.18B00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B10[] = {
#include "textures/segment2/segment2_cn.18B10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B20[] = {
#include "textures/segment2/segment2_cn.18B20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B30[] = {
#include "textures/segment2/segment2_cn.18B30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B40[] = {
#include "textures/segment2/segment2_cn.18B40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B50[] = {
#include "textures/segment2/segment2_cn.18B50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B60[] = {
#include "textures/segment2/segment2_cn.18B60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B70[] = {
#include "textures/segment2/segment2_cn.18B70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B80[] = {
#include "textures/segment2/segment2_cn.18B80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18B90[] = {
#include "textures/segment2/segment2_cn.18B90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18BA0[] = {
#include "textures/segment2/segment2_cn.18BA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18BB0[] = {
#include "textures/segment2/segment2_cn.18BB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18BC0[] = {
#include "textures/segment2/segment2_cn.18BC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18BD0[] = {
#include "textures/segment2/segment2_cn.18BD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18BE0[] = {
#include "textures/segment2/segment2_cn.18BE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18BF0[] = {
#include "textures/segment2/segment2_cn.18BF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C00[] = {
#include "textures/segment2/segment2_cn.18C00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C10[] = {
#include "textures/segment2/segment2_cn.18C10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C20[] = {
#include "textures/segment2/segment2_cn.18C20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C30[] = {
#include "textures/segment2/segment2_cn.18C30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C40[] = {
#include "textures/segment2/segment2_cn.18C40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C50[] = {
#include "textures/segment2/segment2_cn.18C50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C60[] = {
#include "textures/segment2/segment2_cn.18C60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C70[] = {
#include "textures/segment2/segment2_cn.18C70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C80[] = {
#include "textures/segment2/segment2_cn.18C80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18C90[] = {
#include "textures/segment2/segment2_cn.18C90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18CA0[] = {
#include "textures/segment2/segment2_cn.18CA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18CB0[] = {
#include "textures/segment2/segment2_cn.18CB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18CC0[] = {
#include "textures/segment2/segment2_cn.18CC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18CD0[] = {
#include "textures/segment2/segment2_cn.18CD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18CE0[] = {
#include "textures/segment2/segment2_cn.18CE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18CF0[] = {
#include "textures/segment2/segment2_cn.18CF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D00[] = {
#include "textures/segment2/segment2_cn.18D00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D10[] = {
#include "textures/segment2/segment2_cn.18D10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D20[] = {
#include "textures/segment2/segment2_cn.18D20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D30[] = {
#include "textures/segment2/segment2_cn.18D30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D40[] = {
#include "textures/segment2/segment2_cn.18D40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D50[] = {
#include "textures/segment2/segment2_cn.18D50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D60[] = {
#include "textures/segment2/segment2_cn.18D60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D70[] = {
#include "textures/segment2/segment2_cn.18D70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D80[] = {
#include "textures/segment2/segment2_cn.18D80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18D90[] = {
#include "textures/segment2/segment2_cn.18D90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18DA0[] = {
#include "textures/segment2/segment2_cn.18DA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18DB0[] = {
#include "textures/segment2/segment2_cn.18DB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18DC0[] = {
#include "textures/segment2/segment2_cn.18DC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18DD0[] = {
#include "textures/segment2/segment2_cn.18DD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18DE0[] = {
#include "textures/segment2/segment2_cn.18DE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18DF0[] = {
#include "textures/segment2/segment2_cn.18DF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E00[] = {
#include "textures/segment2/segment2_cn.18E00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E10[] = {
#include "textures/segment2/segment2_cn.18E10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E20[] = {
#include "textures/segment2/segment2_cn.18E20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E30[] = {
#include "textures/segment2/segment2_cn.18E30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E40[] = {
#include "textures/segment2/segment2_cn.18E40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E50[] = {
#include "textures/segment2/segment2_cn.18E50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E60[] = {
#include "textures/segment2/segment2_cn.18E60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E70[] = {
#include "textures/segment2/segment2_cn.18E70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E80[] = {
#include "textures/segment2/segment2_cn.18E80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18E90[] = {
#include "textures/segment2/segment2_cn.18E90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18EA0[] = {
#include "textures/segment2/segment2_cn.18EA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18EB0[] = {
#include "textures/segment2/segment2_cn.18EB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18EC0[] = {
#include "textures/segment2/segment2_cn.18EC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18ED0[] = {
#include "textures/segment2/segment2_cn.18ED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18EE0[] = {
#include "textures/segment2/segment2_cn.18EE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18EF0[] = {
#include "textures/segment2/segment2_cn.18EF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F00[] = {
#include "textures/segment2/segment2_cn.18F00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F10[] = {
#include "textures/segment2/segment2_cn.18F10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F20[] = {
#include "textures/segment2/segment2_cn.18F20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F30[] = {
#include "textures/segment2/segment2_cn.18F30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F40[] = {
#include "textures/segment2/segment2_cn.18F40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F50[] = {
#include "textures/segment2/segment2_cn.18F50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F60[] = {
#include "textures/segment2/segment2_cn.18F60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F70[] = {
#include "textures/segment2/segment2_cn.18F70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F80[] = {
#include "textures/segment2/segment2_cn.18F80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18F90[] = {
#include "textures/segment2/segment2_cn.18F90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18FA0[] = {
#include "textures/segment2/segment2_cn.18FA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18FB0[] = {
#include "textures/segment2/segment2_cn.18FB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18FC0[] = {
#include "textures/segment2/segment2_cn.18FC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18FD0[] = {
#include "textures/segment2/segment2_cn.18FD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18FE0[] = {
#include "textures/segment2/segment2_cn.18FE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_18FF0[] = {
#include "textures/segment2/segment2_cn.18FF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19000[] = {
#include "textures/segment2/segment2_cn.19000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19010[] = {
#include "textures/segment2/segment2_cn.19010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19020[] = {
#include "textures/segment2/segment2_cn.19020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19030[] = {
#include "textures/segment2/segment2_cn.19030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19040[] = {
#include "textures/segment2/segment2_cn.19040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19050[] = {
#include "textures/segment2/segment2_cn.19050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19060[] = {
#include "textures/segment2/segment2_cn.19060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19070[] = {
#include "textures/segment2/segment2_cn.19070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19080[] = {
#include "textures/segment2/segment2_cn.19080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19090[] = {
#include "textures/segment2/segment2_cn.19090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_190A0[] = {
#include "textures/segment2/segment2_cn.190A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_190B0[] = {
#include "textures/segment2/segment2_cn.190B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_190C0[] = {
#include "textures/segment2/segment2_cn.190C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_190D0[] = {
#include "textures/segment2/segment2_cn.190D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_190E0[] = {
#include "textures/segment2/segment2_cn.190E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_190F0[] = {
#include "textures/segment2/segment2_cn.190F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19100[] = {
#include "textures/segment2/segment2_cn.19100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19110[] = {
#include "textures/segment2/segment2_cn.19110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19120[] = {
#include "textures/segment2/segment2_cn.19120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19130[] = {
#include "textures/segment2/segment2_cn.19130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19140[] = {
#include "textures/segment2/segment2_cn.19140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19150[] = {
#include "textures/segment2/segment2_cn.19150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19160[] = {
#include "textures/segment2/segment2_cn.19160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19170[] = {
#include "textures/segment2/segment2_cn.19170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19180[] = {
#include "textures/segment2/segment2_cn.19180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19190[] = {
#include "textures/segment2/segment2_cn.19190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_191A0[] = {
#include "textures/segment2/segment2_cn.191A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_191B0[] = {
#include "textures/segment2/segment2_cn.191B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_191C0[] = {
#include "textures/segment2/segment2_cn.191C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_191D0[] = {
#include "textures/segment2/segment2_cn.191D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_191E0[] = {
#include "textures/segment2/segment2_cn.191E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_191F0[] = {
#include "textures/segment2/segment2_cn.191F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19200[] = {
#include "textures/segment2/segment2_cn.19200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19210[] = {
#include "textures/segment2/segment2_cn.19210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19220[] = {
#include "textures/segment2/segment2_cn.19220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19230[] = {
#include "textures/segment2/segment2_cn.19230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19240[] = {
#include "textures/segment2/segment2_cn.19240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19250[] = {
#include "textures/segment2/segment2_cn.19250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19260[] = {
#include "textures/segment2/segment2_cn.19260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19270[] = {
#include "textures/segment2/segment2_cn.19270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19280[] = {
#include "textures/segment2/segment2_cn.19280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19290[] = {
#include "textures/segment2/segment2_cn.19290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_192A0[] = {
#include "textures/segment2/segment2_cn.192A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_192B0[] = {
#include "textures/segment2/segment2_cn.192B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_192C0[] = {
#include "textures/segment2/segment2_cn.192C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_192D0[] = {
#include "textures/segment2/segment2_cn.192D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_192E0[] = {
#include "textures/segment2/segment2_cn.192E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_192F0[] = {
#include "textures/segment2/segment2_cn.192F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19300[] = {
#include "textures/segment2/segment2_cn.19300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19310[] = {
#include "textures/segment2/segment2_cn.19310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19320[] = {
#include "textures/segment2/segment2_cn.19320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19330[] = {
#include "textures/segment2/segment2_cn.19330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19340[] = {
#include "textures/segment2/segment2_cn.19340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19350[] = {
#include "textures/segment2/segment2_cn.19350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19360[] = {
#include "textures/segment2/segment2_cn.19360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19370[] = {
#include "textures/segment2/segment2_cn.19370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19380[] = {
#include "textures/segment2/segment2_cn.19380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19390[] = {
#include "textures/segment2/segment2_cn.19390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_193A0[] = {
#include "textures/segment2/segment2_cn.193A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_193B0[] = {
#include "textures/segment2/segment2_cn.193B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_193C0[] = {
#include "textures/segment2/segment2_cn.193C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_193D0[] = {
#include "textures/segment2/segment2_cn.193D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_193E0[] = {
#include "textures/segment2/segment2_cn.193E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_193F0[] = {
#include "textures/segment2/segment2_cn.193F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19400[] = {
#include "textures/segment2/segment2_cn.19400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19410[] = {
#include "textures/segment2/segment2_cn.19410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19420[] = {
#include "textures/segment2/segment2_cn.19420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19430[] = {
#include "textures/segment2/segment2_cn.19430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19440[] = {
#include "textures/segment2/segment2_cn.19440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19450[] = {
#include "textures/segment2/segment2_cn.19450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19460[] = {
#include "textures/segment2/segment2_cn.19460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19470[] = {
#include "textures/segment2/segment2_cn.19470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19480[] = {
#include "textures/segment2/segment2_cn.19480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19490[] = {
#include "textures/segment2/segment2_cn.19490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_194A0[] = {
#include "textures/segment2/segment2_cn.194A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_194B0[] = {
#include "textures/segment2/segment2_cn.194B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_194C0[] = {
#include "textures/segment2/segment2_cn.194C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_194D0[] = {
#include "textures/segment2/segment2_cn.194D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_194E0[] = {
#include "textures/segment2/segment2_cn.194E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_194F0[] = {
#include "textures/segment2/segment2_cn.194F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19500[] = {
#include "textures/segment2/segment2_cn.19500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19510[] = {
#include "textures/segment2/segment2_cn.19510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19520[] = {
#include "textures/segment2/segment2_cn.19520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19530[] = {
#include "textures/segment2/segment2_cn.19530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19540[] = {
#include "textures/segment2/segment2_cn.19540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19550[] = {
#include "textures/segment2/segment2_cn.19550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19560[] = {
#include "textures/segment2/segment2_cn.19560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19570[] = {
#include "textures/segment2/segment2_cn.19570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19580[] = {
#include "textures/segment2/segment2_cn.19580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19590[] = {
#include "textures/segment2/segment2_cn.19590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_195A0[] = {
#include "textures/segment2/segment2_cn.195A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_195B0[] = {
#include "textures/segment2/segment2_cn.195B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_195C0[] = {
#include "textures/segment2/segment2_cn.195C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_195D0[] = {
#include "textures/segment2/segment2_cn.195D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_195E0[] = {
#include "textures/segment2/segment2_cn.195E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_195F0[] = {
#include "textures/segment2/segment2_cn.195F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19600[] = {
#include "textures/segment2/segment2_cn.19600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19610[] = {
#include "textures/segment2/segment2_cn.19610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19620[] = {
#include "textures/segment2/segment2_cn.19620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19630[] = {
#include "textures/segment2/segment2_cn.19630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19640[] = {
#include "textures/segment2/segment2_cn.19640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19650[] = {
#include "textures/segment2/segment2_cn.19650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19660[] = {
#include "textures/segment2/segment2_cn.19660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19670[] = {
#include "textures/segment2/segment2_cn.19670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19680[] = {
#include "textures/segment2/segment2_cn.19680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19690[] = {
#include "textures/segment2/segment2_cn.19690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_196A0[] = {
#include "textures/segment2/segment2_cn.196A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_196B0[] = {
#include "textures/segment2/segment2_cn.196B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_196C0[] = {
#include "textures/segment2/segment2_cn.196C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_196D0[] = {
#include "textures/segment2/segment2_cn.196D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_196E0[] = {
#include "textures/segment2/segment2_cn.196E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_196F0[] = {
#include "textures/segment2/segment2_cn.196F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19700[] = {
#include "textures/segment2/segment2_cn.19700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19710[] = {
#include "textures/segment2/segment2_cn.19710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19720[] = {
#include "textures/segment2/segment2_cn.19720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19730[] = {
#include "textures/segment2/segment2_cn.19730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19740[] = {
#include "textures/segment2/segment2_cn.19740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19750[] = {
#include "textures/segment2/segment2_cn.19750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19760[] = {
#include "textures/segment2/segment2_cn.19760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19770[] = {
#include "textures/segment2/segment2_cn.19770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19780[] = {
#include "textures/segment2/segment2_cn.19780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19790[] = {
#include "textures/segment2/segment2_cn.19790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_197A0[] = {
#include "textures/segment2/segment2_cn.197A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_197B0[] = {
#include "textures/segment2/segment2_cn.197B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_197C0[] = {
#include "textures/segment2/segment2_cn.197C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_197D0[] = {
#include "textures/segment2/segment2_cn.197D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_197E0[] = {
#include "textures/segment2/segment2_cn.197E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_197F0[] = {
#include "textures/segment2/segment2_cn.197F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19800[] = {
#include "textures/segment2/segment2_cn.19800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19810[] = {
#include "textures/segment2/segment2_cn.19810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19820[] = {
#include "textures/segment2/segment2_cn.19820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19830[] = {
#include "textures/segment2/segment2_cn.19830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19840[] = {
#include "textures/segment2/segment2_cn.19840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19850[] = {
#include "textures/segment2/segment2_cn.19850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19860[] = {
#include "textures/segment2/segment2_cn.19860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19870[] = {
#include "textures/segment2/segment2_cn.19870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19880[] = {
#include "textures/segment2/segment2_cn.19880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19890[] = {
#include "textures/segment2/segment2_cn.19890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_198A0[] = {
#include "textures/segment2/segment2_cn.198A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_198B0[] = {
#include "textures/segment2/segment2_cn.198B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_198C0[] = {
#include "textures/segment2/segment2_cn.198C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_198D0[] = {
#include "textures/segment2/segment2_cn.198D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_198E0[] = {
#include "textures/segment2/segment2_cn.198E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_198F0[] = {
#include "textures/segment2/segment2_cn.198F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19900[] = {
#include "textures/segment2/segment2_cn.19900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19910[] = {
#include "textures/segment2/segment2_cn.19910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19920[] = {
#include "textures/segment2/segment2_cn.19920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19930[] = {
#include "textures/segment2/segment2_cn.19930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19940[] = {
#include "textures/segment2/segment2_cn.19940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19950[] = {
#include "textures/segment2/segment2_cn.19950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19960[] = {
#include "textures/segment2/segment2_cn.19960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19970[] = {
#include "textures/segment2/segment2_cn.19970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19980[] = {
#include "textures/segment2/segment2_cn.19980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19990[] = {
#include "textures/segment2/segment2_cn.19990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_199A0[] = {
#include "textures/segment2/segment2_cn.199A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_199B0[] = {
#include "textures/segment2/segment2_cn.199B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_199C0[] = {
#include "textures/segment2/segment2_cn.199C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_199D0[] = {
#include "textures/segment2/segment2_cn.199D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_199E0[] = {
#include "textures/segment2/segment2_cn.199E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_199F0[] = {
#include "textures/segment2/segment2_cn.199F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A00[] = {
#include "textures/segment2/segment2_cn.19A00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A10[] = {
#include "textures/segment2/segment2_cn.19A10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A20[] = {
#include "textures/segment2/segment2_cn.19A20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A30[] = {
#include "textures/segment2/segment2_cn.19A30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A40[] = {
#include "textures/segment2/segment2_cn.19A40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A50[] = {
#include "textures/segment2/segment2_cn.19A50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A60[] = {
#include "textures/segment2/segment2_cn.19A60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A70[] = {
#include "textures/segment2/segment2_cn.19A70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A80[] = {
#include "textures/segment2/segment2_cn.19A80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19A90[] = {
#include "textures/segment2/segment2_cn.19A90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19AA0[] = {
#include "textures/segment2/segment2_cn.19AA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19AB0[] = {
#include "textures/segment2/segment2_cn.19AB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19AC0[] = {
#include "textures/segment2/segment2_cn.19AC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19AD0[] = {
#include "textures/segment2/segment2_cn.19AD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19AE0[] = {
#include "textures/segment2/segment2_cn.19AE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19AF0[] = {
#include "textures/segment2/segment2_cn.19AF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B00[] = {
#include "textures/segment2/segment2_cn.19B00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B10[] = {
#include "textures/segment2/segment2_cn.19B10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B20[] = {
#include "textures/segment2/segment2_cn.19B20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B30[] = {
#include "textures/segment2/segment2_cn.19B30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B40[] = {
#include "textures/segment2/segment2_cn.19B40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B50[] = {
#include "textures/segment2/segment2_cn.19B50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B60[] = {
#include "textures/segment2/segment2_cn.19B60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B70[] = {
#include "textures/segment2/segment2_cn.19B70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B80[] = {
#include "textures/segment2/segment2_cn.19B80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19B90[] = {
#include "textures/segment2/segment2_cn.19B90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19BA0[] = {
#include "textures/segment2/segment2_cn.19BA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19BB0[] = {
#include "textures/segment2/segment2_cn.19BB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19BC0[] = {
#include "textures/segment2/segment2_cn.19BC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19BD0[] = {
#include "textures/segment2/segment2_cn.19BD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19BE0[] = {
#include "textures/segment2/segment2_cn.19BE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19BF0[] = {
#include "textures/segment2/segment2_cn.19BF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C00[] = {
#include "textures/segment2/segment2_cn.19C00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C10[] = {
#include "textures/segment2/segment2_cn.19C10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C20[] = {
#include "textures/segment2/segment2_cn.19C20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C30[] = {
#include "textures/segment2/segment2_cn.19C30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C40[] = {
#include "textures/segment2/segment2_cn.19C40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C50[] = {
#include "textures/segment2/segment2_cn.19C50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C60[] = {
#include "textures/segment2/segment2_cn.19C60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C70[] = {
#include "textures/segment2/segment2_cn.19C70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C80[] = {
#include "textures/segment2/segment2_cn.19C80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19C90[] = {
#include "textures/segment2/segment2_cn.19C90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19CA0[] = {
#include "textures/segment2/segment2_cn.19CA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19CB0[] = {
#include "textures/segment2/segment2_cn.19CB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19CC0[] = {
#include "textures/segment2/segment2_cn.19CC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19CD0[] = {
#include "textures/segment2/segment2_cn.19CD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19CE0[] = {
#include "textures/segment2/segment2_cn.19CE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19CF0[] = {
#include "textures/segment2/segment2_cn.19CF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D00[] = {
#include "textures/segment2/segment2_cn.19D00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D10[] = {
#include "textures/segment2/segment2_cn.19D10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D20[] = {
#include "textures/segment2/segment2_cn.19D20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D30[] = {
#include "textures/segment2/segment2_cn.19D30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D40[] = {
#include "textures/segment2/segment2_cn.19D40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D50[] = {
#include "textures/segment2/segment2_cn.19D50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D60[] = {
#include "textures/segment2/segment2_cn.19D60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D70[] = {
#include "textures/segment2/segment2_cn.19D70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D80[] = {
#include "textures/segment2/segment2_cn.19D80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19D90[] = {
#include "textures/segment2/segment2_cn.19D90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19DA0[] = {
#include "textures/segment2/segment2_cn.19DA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19DB0[] = {
#include "textures/segment2/segment2_cn.19DB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19DC0[] = {
#include "textures/segment2/segment2_cn.19DC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19DD0[] = {
#include "textures/segment2/segment2_cn.19DD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19DE0[] = {
#include "textures/segment2/segment2_cn.19DE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19DF0[] = {
#include "textures/segment2/segment2_cn.19DF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E00[] = {
#include "textures/segment2/segment2_cn.19E00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E10[] = {
#include "textures/segment2/segment2_cn.19E10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E20[] = {
#include "textures/segment2/segment2_cn.19E20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E30[] = {
#include "textures/segment2/segment2_cn.19E30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E40[] = {
#include "textures/segment2/segment2_cn.19E40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E50[] = {
#include "textures/segment2/segment2_cn.19E50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E60[] = {
#include "textures/segment2/segment2_cn.19E60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E70[] = {
#include "textures/segment2/segment2_cn.19E70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E80[] = {
#include "textures/segment2/segment2_cn.19E80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19E90[] = {
#include "textures/segment2/segment2_cn.19E90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19EA0[] = {
#include "textures/segment2/segment2_cn.19EA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19EB0[] = {
#include "textures/segment2/segment2_cn.19EB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19EC0[] = {
#include "textures/segment2/segment2_cn.19EC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19ED0[] = {
#include "textures/segment2/segment2_cn.19ED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19EE0[] = {
#include "textures/segment2/segment2_cn.19EE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19EF0[] = {
#include "textures/segment2/segment2_cn.19EF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F00[] = {
#include "textures/segment2/segment2_cn.19F00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F10[] = {
#include "textures/segment2/segment2_cn.19F10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F20[] = {
#include "textures/segment2/segment2_cn.19F20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F30[] = {
#include "textures/segment2/segment2_cn.19F30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F40[] = {
#include "textures/segment2/segment2_cn.19F40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F50[] = {
#include "textures/segment2/segment2_cn.19F50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F60[] = {
#include "textures/segment2/segment2_cn.19F60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F70[] = {
#include "textures/segment2/segment2_cn.19F70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F80[] = {
#include "textures/segment2/segment2_cn.19F80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19F90[] = {
#include "textures/segment2/segment2_cn.19F90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19FA0[] = {
#include "textures/segment2/segment2_cn.19FA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19FB0[] = {
#include "textures/segment2/segment2_cn.19FB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19FC0[] = {
#include "textures/segment2/segment2_cn.19FC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19FD0[] = {
#include "textures/segment2/segment2_cn.19FD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19FE0[] = {
#include "textures/segment2/segment2_cn.19FE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_19FF0[] = {
#include "textures/segment2/segment2_cn.19FF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A000[] = {
#include "textures/segment2/segment2_cn.1A000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A010[] = {
#include "textures/segment2/segment2_cn.1A010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A020[] = {
#include "textures/segment2/segment2_cn.1A020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A030[] = {
#include "textures/segment2/segment2_cn.1A030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A040[] = {
#include "textures/segment2/segment2_cn.1A040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A050[] = {
#include "textures/segment2/segment2_cn.1A050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A060[] = {
#include "textures/segment2/segment2_cn.1A060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A070[] = {
#include "textures/segment2/segment2_cn.1A070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A080[] = {
#include "textures/segment2/segment2_cn.1A080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A090[] = {
#include "textures/segment2/segment2_cn.1A090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A0A0[] = {
#include "textures/segment2/segment2_cn.1A0A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A0B0[] = {
#include "textures/segment2/segment2_cn.1A0B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A0C0[] = {
#include "textures/segment2/segment2_cn.1A0C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A0D0[] = {
#include "textures/segment2/segment2_cn.1A0D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A0E0[] = {
#include "textures/segment2/segment2_cn.1A0E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A0F0[] = {
#include "textures/segment2/segment2_cn.1A0F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A100[] = {
#include "textures/segment2/segment2_cn.1A100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A110[] = {
#include "textures/segment2/segment2_cn.1A110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A120[] = {
#include "textures/segment2/segment2_cn.1A120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A130[] = {
#include "textures/segment2/segment2_cn.1A130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A140[] = {
#include "textures/segment2/segment2_cn.1A140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A150[] = {
#include "textures/segment2/segment2_cn.1A150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A160[] = {
#include "textures/segment2/segment2_cn.1A160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A170[] = {
#include "textures/segment2/segment2_cn.1A170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A180[] = {
#include "textures/segment2/segment2_cn.1A180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A190[] = {
#include "textures/segment2/segment2_cn.1A190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A1A0[] = {
#include "textures/segment2/segment2_cn.1A1A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A1B0[] = {
#include "textures/segment2/segment2_cn.1A1B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A1C0[] = {
#include "textures/segment2/segment2_cn.1A1C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A1D0[] = {
#include "textures/segment2/segment2_cn.1A1D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A1E0[] = {
#include "textures/segment2/segment2_cn.1A1E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A1F0[] = {
#include "textures/segment2/segment2_cn.1A1F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A200[] = {
#include "textures/segment2/segment2_cn.1A200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A210[] = {
#include "textures/segment2/segment2_cn.1A210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A220[] = {
#include "textures/segment2/segment2_cn.1A220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A230[] = {
#include "textures/segment2/segment2_cn.1A230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A240[] = {
#include "textures/segment2/segment2_cn.1A240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A250[] = {
#include "textures/segment2/segment2_cn.1A250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A260[] = {
#include "textures/segment2/segment2_cn.1A260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A270[] = {
#include "textures/segment2/segment2_cn.1A270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A280[] = {
#include "textures/segment2/segment2_cn.1A280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A290[] = {
#include "textures/segment2/segment2_cn.1A290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A2A0[] = {
#include "textures/segment2/segment2_cn.1A2A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A2B0[] = {
#include "textures/segment2/segment2_cn.1A2B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A2C0[] = {
#include "textures/segment2/segment2_cn.1A2C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A2D0[] = {
#include "textures/segment2/segment2_cn.1A2D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A2E0[] = {
#include "textures/segment2/segment2_cn.1A2E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A2F0[] = {
#include "textures/segment2/segment2_cn.1A2F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A300[] = {
#include "textures/segment2/segment2_cn.1A300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A310[] = {
#include "textures/segment2/segment2_cn.1A310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A320[] = {
#include "textures/segment2/segment2_cn.1A320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A330[] = {
#include "textures/segment2/segment2_cn.1A330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A340[] = {
#include "textures/segment2/segment2_cn.1A340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A350[] = {
#include "textures/segment2/segment2_cn.1A350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A360[] = {
#include "textures/segment2/segment2_cn.1A360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A370[] = {
#include "textures/segment2/segment2_cn.1A370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A380[] = {
#include "textures/segment2/segment2_cn.1A380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A390[] = {
#include "textures/segment2/segment2_cn.1A390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A3A0[] = {
#include "textures/segment2/segment2_cn.1A3A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A3B0[] = {
#include "textures/segment2/segment2_cn.1A3B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A3C0[] = {
#include "textures/segment2/segment2_cn.1A3C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A3D0[] = {
#include "textures/segment2/segment2_cn.1A3D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A3E0[] = {
#include "textures/segment2/segment2_cn.1A3E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A3F0[] = {
#include "textures/segment2/segment2_cn.1A3F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A400[] = {
#include "textures/segment2/segment2_cn.1A400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A410[] = {
#include "textures/segment2/segment2_cn.1A410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A420[] = {
#include "textures/segment2/segment2_cn.1A420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A430[] = {
#include "textures/segment2/segment2_cn.1A430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A440[] = {
#include "textures/segment2/segment2_cn.1A440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A450[] = {
#include "textures/segment2/segment2_cn.1A450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A460[] = {
#include "textures/segment2/segment2_cn.1A460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A470[] = {
#include "textures/segment2/segment2_cn.1A470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A480[] = {
#include "textures/segment2/segment2_cn.1A480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A490[] = {
#include "textures/segment2/segment2_cn.1A490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A4A0[] = {
#include "textures/segment2/segment2_cn.1A4A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A4B0[] = {
#include "textures/segment2/segment2_cn.1A4B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A4C0[] = {
#include "textures/segment2/segment2_cn.1A4C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A4D0[] = {
#include "textures/segment2/segment2_cn.1A4D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A4E0[] = {
#include "textures/segment2/segment2_cn.1A4E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A4F0[] = {
#include "textures/segment2/segment2_cn.1A4F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A500[] = {
#include "textures/segment2/segment2_cn.1A500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A510[] = {
#include "textures/segment2/segment2_cn.1A510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A520[] = {
#include "textures/segment2/segment2_cn.1A520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A530[] = {
#include "textures/segment2/segment2_cn.1A530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A540[] = {
#include "textures/segment2/segment2_cn.1A540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A550[] = {
#include "textures/segment2/segment2_cn.1A550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A560[] = {
#include "textures/segment2/segment2_cn.1A560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A570[] = {
#include "textures/segment2/segment2_cn.1A570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A580[] = {
#include "textures/segment2/segment2_cn.1A580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A590[] = {
#include "textures/segment2/segment2_cn.1A590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A5A0[] = {
#include "textures/segment2/segment2_cn.1A5A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A5B0[] = {
#include "textures/segment2/segment2_cn.1A5B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A5C0[] = {
#include "textures/segment2/segment2_cn.1A5C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A5D0[] = {
#include "textures/segment2/segment2_cn.1A5D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A5E0[] = {
#include "textures/segment2/segment2_cn.1A5E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A5F0[] = {
#include "textures/segment2/segment2_cn.1A5F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A600[] = {
#include "textures/segment2/segment2_cn.1A600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A610[] = {
#include "textures/segment2/segment2_cn.1A610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A620[] = {
#include "textures/segment2/segment2_cn.1A620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A630[] = {
#include "textures/segment2/segment2_cn.1A630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A640[] = {
#include "textures/segment2/segment2_cn.1A640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A650[] = {
#include "textures/segment2/segment2_cn.1A650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A660[] = {
#include "textures/segment2/segment2_cn.1A660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A670[] = {
#include "textures/segment2/segment2_cn.1A670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A680[] = {
#include "textures/segment2/segment2_cn.1A680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A690[] = {
#include "textures/segment2/segment2_cn.1A690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A6A0[] = {
#include "textures/segment2/segment2_cn.1A6A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A6B0[] = {
#include "textures/segment2/segment2_cn.1A6B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A6C0[] = {
#include "textures/segment2/segment2_cn.1A6C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A6D0[] = {
#include "textures/segment2/segment2_cn.1A6D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A6E0[] = {
#include "textures/segment2/segment2_cn.1A6E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A6F0[] = {
#include "textures/segment2/segment2_cn.1A6F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A700[] = {
#include "textures/segment2/segment2_cn.1A700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A710[] = {
#include "textures/segment2/segment2_cn.1A710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A720[] = {
#include "textures/segment2/segment2_cn.1A720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A730[] = {
#include "textures/segment2/segment2_cn.1A730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A740[] = {
#include "textures/segment2/segment2_cn.1A740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A750[] = {
#include "textures/segment2/segment2_cn.1A750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A760[] = {
#include "textures/segment2/segment2_cn.1A760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A770[] = {
#include "textures/segment2/segment2_cn.1A770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A780[] = {
#include "textures/segment2/segment2_cn.1A780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A790[] = {
#include "textures/segment2/segment2_cn.1A790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A7A0[] = {
#include "textures/segment2/segment2_cn.1A7A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A7B0[] = {
#include "textures/segment2/segment2_cn.1A7B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A7C0[] = {
#include "textures/segment2/segment2_cn.1A7C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A7D0[] = {
#include "textures/segment2/segment2_cn.1A7D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A7E0[] = {
#include "textures/segment2/segment2_cn.1A7E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A7F0[] = {
#include "textures/segment2/segment2_cn.1A7F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A800[] = {
#include "textures/segment2/segment2_cn.1A800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A810[] = {
#include "textures/segment2/segment2_cn.1A810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A820[] = {
#include "textures/segment2/segment2_cn.1A820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A830[] = {
#include "textures/segment2/segment2_cn.1A830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A840[] = {
#include "textures/segment2/segment2_cn.1A840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A850[] = {
#include "textures/segment2/segment2_cn.1A850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A860[] = {
#include "textures/segment2/segment2_cn.1A860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A870[] = {
#include "textures/segment2/segment2_cn.1A870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A880[] = {
#include "textures/segment2/segment2_cn.1A880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A890[] = {
#include "textures/segment2/segment2_cn.1A890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A8A0[] = {
#include "textures/segment2/segment2_cn.1A8A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A8B0[] = {
#include "textures/segment2/segment2_cn.1A8B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A8C0[] = {
#include "textures/segment2/segment2_cn.1A8C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A8D0[] = {
#include "textures/segment2/segment2_cn.1A8D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A8E0[] = {
#include "textures/segment2/segment2_cn.1A8E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A8F0[] = {
#include "textures/segment2/segment2_cn.1A8F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A900[] = {
#include "textures/segment2/segment2_cn.1A900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A910[] = {
#include "textures/segment2/segment2_cn.1A910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A920[] = {
#include "textures/segment2/segment2_cn.1A920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A930[] = {
#include "textures/segment2/segment2_cn.1A930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A940[] = {
#include "textures/segment2/segment2_cn.1A940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A950[] = {
#include "textures/segment2/segment2_cn.1A950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A960[] = {
#include "textures/segment2/segment2_cn.1A960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A970[] = {
#include "textures/segment2/segment2_cn.1A970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A980[] = {
#include "textures/segment2/segment2_cn.1A980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A990[] = {
#include "textures/segment2/segment2_cn.1A990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A9A0[] = {
#include "textures/segment2/segment2_cn.1A9A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A9B0[] = {
#include "textures/segment2/segment2_cn.1A9B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A9C0[] = {
#include "textures/segment2/segment2_cn.1A9C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A9D0[] = {
#include "textures/segment2/segment2_cn.1A9D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A9E0[] = {
#include "textures/segment2/segment2_cn.1A9E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1A9F0[] = {
#include "textures/segment2/segment2_cn.1A9F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA00[] = {
#include "textures/segment2/segment2_cn.1AA00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA10[] = {
#include "textures/segment2/segment2_cn.1AA10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA20[] = {
#include "textures/segment2/segment2_cn.1AA20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA30[] = {
#include "textures/segment2/segment2_cn.1AA30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA40[] = {
#include "textures/segment2/segment2_cn.1AA40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA50[] = {
#include "textures/segment2/segment2_cn.1AA50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA60[] = {
#include "textures/segment2/segment2_cn.1AA60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA70[] = {
#include "textures/segment2/segment2_cn.1AA70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA80[] = {
#include "textures/segment2/segment2_cn.1AA80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AA90[] = {
#include "textures/segment2/segment2_cn.1AA90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AAA0[] = {
#include "textures/segment2/segment2_cn.1AAA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AAB0[] = {
#include "textures/segment2/segment2_cn.1AAB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AAC0[] = {
#include "textures/segment2/segment2_cn.1AAC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AAD0[] = {
#include "textures/segment2/segment2_cn.1AAD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AAE0[] = {
#include "textures/segment2/segment2_cn.1AAE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AAF0[] = {
#include "textures/segment2/segment2_cn.1AAF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB00[] = {
#include "textures/segment2/segment2_cn.1AB00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB10[] = {
#include "textures/segment2/segment2_cn.1AB10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB20[] = {
#include "textures/segment2/segment2_cn.1AB20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB30[] = {
#include "textures/segment2/segment2_cn.1AB30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB40[] = {
#include "textures/segment2/segment2_cn.1AB40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB50[] = {
#include "textures/segment2/segment2_cn.1AB50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB60[] = {
#include "textures/segment2/segment2_cn.1AB60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB70[] = {
#include "textures/segment2/segment2_cn.1AB70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB80[] = {
#include "textures/segment2/segment2_cn.1AB80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AB90[] = {
#include "textures/segment2/segment2_cn.1AB90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ABA0[] = {
#include "textures/segment2/segment2_cn.1ABA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ABB0[] = {
#include "textures/segment2/segment2_cn.1ABB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ABC0[] = {
#include "textures/segment2/segment2_cn.1ABC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ABD0[] = {
#include "textures/segment2/segment2_cn.1ABD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ABE0[] = {
#include "textures/segment2/segment2_cn.1ABE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ABF0[] = {
#include "textures/segment2/segment2_cn.1ABF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC00[] = {
#include "textures/segment2/segment2_cn.1AC00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC10[] = {
#include "textures/segment2/segment2_cn.1AC10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC20[] = {
#include "textures/segment2/segment2_cn.1AC20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC30[] = {
#include "textures/segment2/segment2_cn.1AC30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC40[] = {
#include "textures/segment2/segment2_cn.1AC40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC50[] = {
#include "textures/segment2/segment2_cn.1AC50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC60[] = {
#include "textures/segment2/segment2_cn.1AC60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC70[] = {
#include "textures/segment2/segment2_cn.1AC70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC80[] = {
#include "textures/segment2/segment2_cn.1AC80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AC90[] = {
#include "textures/segment2/segment2_cn.1AC90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ACA0[] = {
#include "textures/segment2/segment2_cn.1ACA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ACB0[] = {
#include "textures/segment2/segment2_cn.1ACB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ACC0[] = {
#include "textures/segment2/segment2_cn.1ACC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ACD0[] = {
#include "textures/segment2/segment2_cn.1ACD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ACE0[] = {
#include "textures/segment2/segment2_cn.1ACE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ACF0[] = {
#include "textures/segment2/segment2_cn.1ACF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD00[] = {
#include "textures/segment2/segment2_cn.1AD00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD10[] = {
#include "textures/segment2/segment2_cn.1AD10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD20[] = {
#include "textures/segment2/segment2_cn.1AD20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD30[] = {
#include "textures/segment2/segment2_cn.1AD30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD40[] = {
#include "textures/segment2/segment2_cn.1AD40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD50[] = {
#include "textures/segment2/segment2_cn.1AD50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD60[] = {
#include "textures/segment2/segment2_cn.1AD60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD70[] = {
#include "textures/segment2/segment2_cn.1AD70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD80[] = {
#include "textures/segment2/segment2_cn.1AD80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AD90[] = {
#include "textures/segment2/segment2_cn.1AD90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ADA0[] = {
#include "textures/segment2/segment2_cn.1ADA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ADB0[] = {
#include "textures/segment2/segment2_cn.1ADB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ADC0[] = {
#include "textures/segment2/segment2_cn.1ADC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ADD0[] = {
#include "textures/segment2/segment2_cn.1ADD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ADE0[] = {
#include "textures/segment2/segment2_cn.1ADE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ADF0[] = {
#include "textures/segment2/segment2_cn.1ADF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE00[] = {
#include "textures/segment2/segment2_cn.1AE00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE10[] = {
#include "textures/segment2/segment2_cn.1AE10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE20[] = {
#include "textures/segment2/segment2_cn.1AE20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE30[] = {
#include "textures/segment2/segment2_cn.1AE30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE40[] = {
#include "textures/segment2/segment2_cn.1AE40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE50[] = {
#include "textures/segment2/segment2_cn.1AE50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE60[] = {
#include "textures/segment2/segment2_cn.1AE60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE70[] = {
#include "textures/segment2/segment2_cn.1AE70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE80[] = {
#include "textures/segment2/segment2_cn.1AE80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AE90[] = {
#include "textures/segment2/segment2_cn.1AE90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AEA0[] = {
#include "textures/segment2/segment2_cn.1AEA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AEB0[] = {
#include "textures/segment2/segment2_cn.1AEB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AEC0[] = {
#include "textures/segment2/segment2_cn.1AEC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AED0[] = {
#include "textures/segment2/segment2_cn.1AED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AEE0[] = {
#include "textures/segment2/segment2_cn.1AEE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AEF0[] = {
#include "textures/segment2/segment2_cn.1AEF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF00[] = {
#include "textures/segment2/segment2_cn.1AF00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF10[] = {
#include "textures/segment2/segment2_cn.1AF10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF20[] = {
#include "textures/segment2/segment2_cn.1AF20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF30[] = {
#include "textures/segment2/segment2_cn.1AF30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF40[] = {
#include "textures/segment2/segment2_cn.1AF40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF50[] = {
#include "textures/segment2/segment2_cn.1AF50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF60[] = {
#include "textures/segment2/segment2_cn.1AF60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF70[] = {
#include "textures/segment2/segment2_cn.1AF70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF80[] = {
#include "textures/segment2/segment2_cn.1AF80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AF90[] = {
#include "textures/segment2/segment2_cn.1AF90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AFA0[] = {
#include "textures/segment2/segment2_cn.1AFA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AFB0[] = {
#include "textures/segment2/segment2_cn.1AFB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AFC0[] = {
#include "textures/segment2/segment2_cn.1AFC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AFD0[] = {
#include "textures/segment2/segment2_cn.1AFD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AFE0[] = {
#include "textures/segment2/segment2_cn.1AFE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1AFF0[] = {
#include "textures/segment2/segment2_cn.1AFF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B000[] = {
#include "textures/segment2/segment2_cn.1B000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B010[] = {
#include "textures/segment2/segment2_cn.1B010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B020[] = {
#include "textures/segment2/segment2_cn.1B020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B030[] = {
#include "textures/segment2/segment2_cn.1B030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B040[] = {
#include "textures/segment2/segment2_cn.1B040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B050[] = {
#include "textures/segment2/segment2_cn.1B050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B060[] = {
#include "textures/segment2/segment2_cn.1B060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B070[] = {
#include "textures/segment2/segment2_cn.1B070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B080[] = {
#include "textures/segment2/segment2_cn.1B080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B090[] = {
#include "textures/segment2/segment2_cn.1B090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B0A0[] = {
#include "textures/segment2/segment2_cn.1B0A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B0B0[] = {
#include "textures/segment2/segment2_cn.1B0B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B0C0[] = {
#include "textures/segment2/segment2_cn.1B0C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B0D0[] = {
#include "textures/segment2/segment2_cn.1B0D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B0E0[] = {
#include "textures/segment2/segment2_cn.1B0E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B0F0[] = {
#include "textures/segment2/segment2_cn.1B0F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B100[] = {
#include "textures/segment2/segment2_cn.1B100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B110[] = {
#include "textures/segment2/segment2_cn.1B110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B120[] = {
#include "textures/segment2/segment2_cn.1B120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B130[] = {
#include "textures/segment2/segment2_cn.1B130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B140[] = {
#include "textures/segment2/segment2_cn.1B140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B150[] = {
#include "textures/segment2/segment2_cn.1B150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B160[] = {
#include "textures/segment2/segment2_cn.1B160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B170[] = {
#include "textures/segment2/segment2_cn.1B170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B180[] = {
#include "textures/segment2/segment2_cn.1B180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B190[] = {
#include "textures/segment2/segment2_cn.1B190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B1A0[] = {
#include "textures/segment2/segment2_cn.1B1A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B1B0[] = {
#include "textures/segment2/segment2_cn.1B1B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B1C0[] = {
#include "textures/segment2/segment2_cn.1B1C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B1D0[] = {
#include "textures/segment2/segment2_cn.1B1D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B1E0[] = {
#include "textures/segment2/segment2_cn.1B1E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B1F0[] = {
#include "textures/segment2/segment2_cn.1B1F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B200[] = {
#include "textures/segment2/segment2_cn.1B200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B210[] = {
#include "textures/segment2/segment2_cn.1B210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B220[] = {
#include "textures/segment2/segment2_cn.1B220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B230[] = {
#include "textures/segment2/segment2_cn.1B230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B240[] = {
#include "textures/segment2/segment2_cn.1B240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B250[] = {
#include "textures/segment2/segment2_cn.1B250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B260[] = {
#include "textures/segment2/segment2_cn.1B260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B270[] = {
#include "textures/segment2/segment2_cn.1B270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B280[] = {
#include "textures/segment2/segment2_cn.1B280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B290[] = {
#include "textures/segment2/segment2_cn.1B290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B2A0[] = {
#include "textures/segment2/segment2_cn.1B2A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B2B0[] = {
#include "textures/segment2/segment2_cn.1B2B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B2C0[] = {
#include "textures/segment2/segment2_cn.1B2C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B2D0[] = {
#include "textures/segment2/segment2_cn.1B2D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B2E0[] = {
#include "textures/segment2/segment2_cn.1B2E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B2F0[] = {
#include "textures/segment2/segment2_cn.1B2F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B300[] = {
#include "textures/segment2/segment2_cn.1B300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B310[] = {
#include "textures/segment2/segment2_cn.1B310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B320[] = {
#include "textures/segment2/segment2_cn.1B320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B330[] = {
#include "textures/segment2/segment2_cn.1B330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B340[] = {
#include "textures/segment2/segment2_cn.1B340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B350[] = {
#include "textures/segment2/segment2_cn.1B350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B360[] = {
#include "textures/segment2/segment2_cn.1B360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B370[] = {
#include "textures/segment2/segment2_cn.1B370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B380[] = {
#include "textures/segment2/segment2_cn.1B380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B390[] = {
#include "textures/segment2/segment2_cn.1B390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B3A0[] = {
#include "textures/segment2/segment2_cn.1B3A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B3B0[] = {
#include "textures/segment2/segment2_cn.1B3B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B3C0[] = {
#include "textures/segment2/segment2_cn.1B3C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B3D0[] = {
#include "textures/segment2/segment2_cn.1B3D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B3E0[] = {
#include "textures/segment2/segment2_cn.1B3E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B3F0[] = {
#include "textures/segment2/segment2_cn.1B3F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B400[] = {
#include "textures/segment2/segment2_cn.1B400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B410[] = {
#include "textures/segment2/segment2_cn.1B410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B420[] = {
#include "textures/segment2/segment2_cn.1B420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B430[] = {
#include "textures/segment2/segment2_cn.1B430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B440[] = {
#include "textures/segment2/segment2_cn.1B440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B450[] = {
#include "textures/segment2/segment2_cn.1B450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B460[] = {
#include "textures/segment2/segment2_cn.1B460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B470[] = {
#include "textures/segment2/segment2_cn.1B470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B480[] = {
#include "textures/segment2/segment2_cn.1B480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B490[] = {
#include "textures/segment2/segment2_cn.1B490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B4A0[] = {
#include "textures/segment2/segment2_cn.1B4A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B4B0[] = {
#include "textures/segment2/segment2_cn.1B4B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B4C0[] = {
#include "textures/segment2/segment2_cn.1B4C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B4D0[] = {
#include "textures/segment2/segment2_cn.1B4D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B4E0[] = {
#include "textures/segment2/segment2_cn.1B4E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B4F0[] = {
#include "textures/segment2/segment2_cn.1B4F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B500[] = {
#include "textures/segment2/segment2_cn.1B500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B510[] = {
#include "textures/segment2/segment2_cn.1B510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B520[] = {
#include "textures/segment2/segment2_cn.1B520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B530[] = {
#include "textures/segment2/segment2_cn.1B530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B540[] = {
#include "textures/segment2/segment2_cn.1B540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B550[] = {
#include "textures/segment2/segment2_cn.1B550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B560[] = {
#include "textures/segment2/segment2_cn.1B560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B570[] = {
#include "textures/segment2/segment2_cn.1B570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B580[] = {
#include "textures/segment2/segment2_cn.1B580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B590[] = {
#include "textures/segment2/segment2_cn.1B590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B5A0[] = {
#include "textures/segment2/segment2_cn.1B5A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B5B0[] = {
#include "textures/segment2/segment2_cn.1B5B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B5C0[] = {
#include "textures/segment2/segment2_cn.1B5C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B5D0[] = {
#include "textures/segment2/segment2_cn.1B5D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B5E0[] = {
#include "textures/segment2/segment2_cn.1B5E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B5F0[] = {
#include "textures/segment2/segment2_cn.1B5F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B600[] = {
#include "textures/segment2/segment2_cn.1B600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B610[] = {
#include "textures/segment2/segment2_cn.1B610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B620[] = {
#include "textures/segment2/segment2_cn.1B620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B630[] = {
#include "textures/segment2/segment2_cn.1B630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B640[] = {
#include "textures/segment2/segment2_cn.1B640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B650[] = {
#include "textures/segment2/segment2_cn.1B650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B660[] = {
#include "textures/segment2/segment2_cn.1B660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B670[] = {
#include "textures/segment2/segment2_cn.1B670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B680[] = {
#include "textures/segment2/segment2_cn.1B680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B690[] = {
#include "textures/segment2/segment2_cn.1B690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B6A0[] = {
#include "textures/segment2/segment2_cn.1B6A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B6B0[] = {
#include "textures/segment2/segment2_cn.1B6B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B6C0[] = {
#include "textures/segment2/segment2_cn.1B6C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B6D0[] = {
#include "textures/segment2/segment2_cn.1B6D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B6E0[] = {
#include "textures/segment2/segment2_cn.1B6E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B6F0[] = {
#include "textures/segment2/segment2_cn.1B6F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B700[] = {
#include "textures/segment2/segment2_cn.1B700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B710[] = {
#include "textures/segment2/segment2_cn.1B710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B720[] = {
#include "textures/segment2/segment2_cn.1B720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B730[] = {
#include "textures/segment2/segment2_cn.1B730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B740[] = {
#include "textures/segment2/segment2_cn.1B740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B750[] = {
#include "textures/segment2/segment2_cn.1B750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B760[] = {
#include "textures/segment2/segment2_cn.1B760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B770[] = {
#include "textures/segment2/segment2_cn.1B770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B780[] = {
#include "textures/segment2/segment2_cn.1B780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B790[] = {
#include "textures/segment2/segment2_cn.1B790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B7A0[] = {
#include "textures/segment2/segment2_cn.1B7A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B7B0[] = {
#include "textures/segment2/segment2_cn.1B7B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B7C0[] = {
#include "textures/segment2/segment2_cn.1B7C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B7D0[] = {
#include "textures/segment2/segment2_cn.1B7D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B7E0[] = {
#include "textures/segment2/segment2_cn.1B7E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B7F0[] = {
#include "textures/segment2/segment2_cn.1B7F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B800[] = {
#include "textures/segment2/segment2_cn.1B800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B810[] = {
#include "textures/segment2/segment2_cn.1B810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B820[] = {
#include "textures/segment2/segment2_cn.1B820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B830[] = {
#include "textures/segment2/segment2_cn.1B830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B840[] = {
#include "textures/segment2/segment2_cn.1B840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B850[] = {
#include "textures/segment2/segment2_cn.1B850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B860[] = {
#include "textures/segment2/segment2_cn.1B860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B870[] = {
#include "textures/segment2/segment2_cn.1B870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B880[] = {
#include "textures/segment2/segment2_cn.1B880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B890[] = {
#include "textures/segment2/segment2_cn.1B890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B8A0[] = {
#include "textures/segment2/segment2_cn.1B8A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B8B0[] = {
#include "textures/segment2/segment2_cn.1B8B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B8C0[] = {
#include "textures/segment2/segment2_cn.1B8C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B8D0[] = {
#include "textures/segment2/segment2_cn.1B8D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B8E0[] = {
#include "textures/segment2/segment2_cn.1B8E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B8F0[] = {
#include "textures/segment2/segment2_cn.1B8F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B900[] = {
#include "textures/segment2/segment2_cn.1B900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B910[] = {
#include "textures/segment2/segment2_cn.1B910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B920[] = {
#include "textures/segment2/segment2_cn.1B920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B930[] = {
#include "textures/segment2/segment2_cn.1B930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B940[] = {
#include "textures/segment2/segment2_cn.1B940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B950[] = {
#include "textures/segment2/segment2_cn.1B950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B960[] = {
#include "textures/segment2/segment2_cn.1B960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B970[] = {
#include "textures/segment2/segment2_cn.1B970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B980[] = {
#include "textures/segment2/segment2_cn.1B980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B990[] = {
#include "textures/segment2/segment2_cn.1B990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B9A0[] = {
#include "textures/segment2/segment2_cn.1B9A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B9B0[] = {
#include "textures/segment2/segment2_cn.1B9B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B9C0[] = {
#include "textures/segment2/segment2_cn.1B9C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B9D0[] = {
#include "textures/segment2/segment2_cn.1B9D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B9E0[] = {
#include "textures/segment2/segment2_cn.1B9E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1B9F0[] = {
#include "textures/segment2/segment2_cn.1B9F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA00[] = {
#include "textures/segment2/segment2_cn.1BA00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA10[] = {
#include "textures/segment2/segment2_cn.1BA10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA20[] = {
#include "textures/segment2/segment2_cn.1BA20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA30[] = {
#include "textures/segment2/segment2_cn.1BA30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA40[] = {
#include "textures/segment2/segment2_cn.1BA40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA50[] = {
#include "textures/segment2/segment2_cn.1BA50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA60[] = {
#include "textures/segment2/segment2_cn.1BA60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA70[] = {
#include "textures/segment2/segment2_cn.1BA70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA80[] = {
#include "textures/segment2/segment2_cn.1BA80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BA90[] = {
#include "textures/segment2/segment2_cn.1BA90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BAA0[] = {
#include "textures/segment2/segment2_cn.1BAA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BAB0[] = {
#include "textures/segment2/segment2_cn.1BAB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BAC0[] = {
#include "textures/segment2/segment2_cn.1BAC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BAD0[] = {
#include "textures/segment2/segment2_cn.1BAD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BAE0[] = {
#include "textures/segment2/segment2_cn.1BAE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BAF0[] = {
#include "textures/segment2/segment2_cn.1BAF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB00[] = {
#include "textures/segment2/segment2_cn.1BB00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB10[] = {
#include "textures/segment2/segment2_cn.1BB10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB20[] = {
#include "textures/segment2/segment2_cn.1BB20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB30[] = {
#include "textures/segment2/segment2_cn.1BB30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB40[] = {
#include "textures/segment2/segment2_cn.1BB40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB50[] = {
#include "textures/segment2/segment2_cn.1BB50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB60[] = {
#include "textures/segment2/segment2_cn.1BB60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB70[] = {
#include "textures/segment2/segment2_cn.1BB70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB80[] = {
#include "textures/segment2/segment2_cn.1BB80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BB90[] = {
#include "textures/segment2/segment2_cn.1BB90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BBA0[] = {
#include "textures/segment2/segment2_cn.1BBA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BBB0[] = {
#include "textures/segment2/segment2_cn.1BBB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BBC0[] = {
#include "textures/segment2/segment2_cn.1BBC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BBD0[] = {
#include "textures/segment2/segment2_cn.1BBD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BBE0[] = {
#include "textures/segment2/segment2_cn.1BBE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BBF0[] = {
#include "textures/segment2/segment2_cn.1BBF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC00[] = {
#include "textures/segment2/segment2_cn.1BC00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC10[] = {
#include "textures/segment2/segment2_cn.1BC10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC20[] = {
#include "textures/segment2/segment2_cn.1BC20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC30[] = {
#include "textures/segment2/segment2_cn.1BC30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC40[] = {
#include "textures/segment2/segment2_cn.1BC40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC50[] = {
#include "textures/segment2/segment2_cn.1BC50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC60[] = {
#include "textures/segment2/segment2_cn.1BC60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC70[] = {
#include "textures/segment2/segment2_cn.1BC70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC80[] = {
#include "textures/segment2/segment2_cn.1BC80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BC90[] = {
#include "textures/segment2/segment2_cn.1BC90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BCA0[] = {
#include "textures/segment2/segment2_cn.1BCA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BCB0[] = {
#include "textures/segment2/segment2_cn.1BCB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BCC0[] = {
#include "textures/segment2/segment2_cn.1BCC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BCD0[] = {
#include "textures/segment2/segment2_cn.1BCD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BCE0[] = {
#include "textures/segment2/segment2_cn.1BCE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BCF0[] = {
#include "textures/segment2/segment2_cn.1BCF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD00[] = {
#include "textures/segment2/segment2_cn.1BD00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD10[] = {
#include "textures/segment2/segment2_cn.1BD10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD20[] = {
#include "textures/segment2/segment2_cn.1BD20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD30[] = {
#include "textures/segment2/segment2_cn.1BD30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD40[] = {
#include "textures/segment2/segment2_cn.1BD40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD50[] = {
#include "textures/segment2/segment2_cn.1BD50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD60[] = {
#include "textures/segment2/segment2_cn.1BD60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD70[] = {
#include "textures/segment2/segment2_cn.1BD70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD80[] = {
#include "textures/segment2/segment2_cn.1BD80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BD90[] = {
#include "textures/segment2/segment2_cn.1BD90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BDA0[] = {
#include "textures/segment2/segment2_cn.1BDA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BDB0[] = {
#include "textures/segment2/segment2_cn.1BDB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BDC0[] = {
#include "textures/segment2/segment2_cn.1BDC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BDD0[] = {
#include "textures/segment2/segment2_cn.1BDD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BDE0[] = {
#include "textures/segment2/segment2_cn.1BDE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BDF0[] = {
#include "textures/segment2/segment2_cn.1BDF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE00[] = {
#include "textures/segment2/segment2_cn.1BE00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE10[] = {
#include "textures/segment2/segment2_cn.1BE10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE20[] = {
#include "textures/segment2/segment2_cn.1BE20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE30[] = {
#include "textures/segment2/segment2_cn.1BE30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE40[] = {
#include "textures/segment2/segment2_cn.1BE40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE50[] = {
#include "textures/segment2/segment2_cn.1BE50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE60[] = {
#include "textures/segment2/segment2_cn.1BE60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE70[] = {
#include "textures/segment2/segment2_cn.1BE70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE80[] = {
#include "textures/segment2/segment2_cn.1BE80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BE90[] = {
#include "textures/segment2/segment2_cn.1BE90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BEA0[] = {
#include "textures/segment2/segment2_cn.1BEA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BEB0[] = {
#include "textures/segment2/segment2_cn.1BEB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BEC0[] = {
#include "textures/segment2/segment2_cn.1BEC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BED0[] = {
#include "textures/segment2/segment2_cn.1BED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BEE0[] = {
#include "textures/segment2/segment2_cn.1BEE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BEF0[] = {
#include "textures/segment2/segment2_cn.1BEF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF00[] = {
#include "textures/segment2/segment2_cn.1BF00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF10[] = {
#include "textures/segment2/segment2_cn.1BF10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF20[] = {
#include "textures/segment2/segment2_cn.1BF20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF30[] = {
#include "textures/segment2/segment2_cn.1BF30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF40[] = {
#include "textures/segment2/segment2_cn.1BF40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF50[] = {
#include "textures/segment2/segment2_cn.1BF50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF60[] = {
#include "textures/segment2/segment2_cn.1BF60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF70[] = {
#include "textures/segment2/segment2_cn.1BF70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF80[] = {
#include "textures/segment2/segment2_cn.1BF80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BF90[] = {
#include "textures/segment2/segment2_cn.1BF90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BFA0[] = {
#include "textures/segment2/segment2_cn.1BFA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BFB0[] = {
#include "textures/segment2/segment2_cn.1BFB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BFC0[] = {
#include "textures/segment2/segment2_cn.1BFC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BFD0[] = {
#include "textures/segment2/segment2_cn.1BFD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BFE0[] = {
#include "textures/segment2/segment2_cn.1BFE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1BFF0[] = {
#include "textures/segment2/segment2_cn.1BFF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C000[] = {
#include "textures/segment2/segment2_cn.1C000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C010[] = {
#include "textures/segment2/segment2_cn.1C010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C020[] = {
#include "textures/segment2/segment2_cn.1C020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C030[] = {
#include "textures/segment2/segment2_cn.1C030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C040[] = {
#include "textures/segment2/segment2_cn.1C040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C050[] = {
#include "textures/segment2/segment2_cn.1C050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C060[] = {
#include "textures/segment2/segment2_cn.1C060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C070[] = {
#include "textures/segment2/segment2_cn.1C070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C080[] = {
#include "textures/segment2/segment2_cn.1C080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C090[] = {
#include "textures/segment2/segment2_cn.1C090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C0A0[] = {
#include "textures/segment2/segment2_cn.1C0A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C0B0[] = {
#include "textures/segment2/segment2_cn.1C0B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C0C0[] = {
#include "textures/segment2/segment2_cn.1C0C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C0D0[] = {
#include "textures/segment2/segment2_cn.1C0D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C0E0[] = {
#include "textures/segment2/segment2_cn.1C0E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C0F0[] = {
#include "textures/segment2/segment2_cn.1C0F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C100[] = {
#include "textures/segment2/segment2_cn.1C100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C110[] = {
#include "textures/segment2/segment2_cn.1C110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C120[] = {
#include "textures/segment2/segment2_cn.1C120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C130[] = {
#include "textures/segment2/segment2_cn.1C130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C140[] = {
#include "textures/segment2/segment2_cn.1C140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C150[] = {
#include "textures/segment2/segment2_cn.1C150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C160[] = {
#include "textures/segment2/segment2_cn.1C160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C170[] = {
#include "textures/segment2/segment2_cn.1C170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C180[] = {
#include "textures/segment2/segment2_cn.1C180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C190[] = {
#include "textures/segment2/segment2_cn.1C190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C1A0[] = {
#include "textures/segment2/segment2_cn.1C1A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C1B0[] = {
#include "textures/segment2/segment2_cn.1C1B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C1C0[] = {
#include "textures/segment2/segment2_cn.1C1C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C1D0[] = {
#include "textures/segment2/segment2_cn.1C1D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C1E0[] = {
#include "textures/segment2/segment2_cn.1C1E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C1F0[] = {
#include "textures/segment2/segment2_cn.1C1F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C200[] = {
#include "textures/segment2/segment2_cn.1C200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C210[] = {
#include "textures/segment2/segment2_cn.1C210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C220[] = {
#include "textures/segment2/segment2_cn.1C220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C230[] = {
#include "textures/segment2/segment2_cn.1C230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C240[] = {
#include "textures/segment2/segment2_cn.1C240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C250[] = {
#include "textures/segment2/segment2_cn.1C250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C260[] = {
#include "textures/segment2/segment2_cn.1C260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C270[] = {
#include "textures/segment2/segment2_cn.1C270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C280[] = {
#include "textures/segment2/segment2_cn.1C280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C290[] = {
#include "textures/segment2/segment2_cn.1C290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C2A0[] = {
#include "textures/segment2/segment2_cn.1C2A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C2B0[] = {
#include "textures/segment2/segment2_cn.1C2B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C2C0[] = {
#include "textures/segment2/segment2_cn.1C2C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C2D0[] = {
#include "textures/segment2/segment2_cn.1C2D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C2E0[] = {
#include "textures/segment2/segment2_cn.1C2E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C2F0[] = {
#include "textures/segment2/segment2_cn.1C2F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C300[] = {
#include "textures/segment2/segment2_cn.1C300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C310[] = {
#include "textures/segment2/segment2_cn.1C310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C320[] = {
#include "textures/segment2/segment2_cn.1C320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C330[] = {
#include "textures/segment2/segment2_cn.1C330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C340[] = {
#include "textures/segment2/segment2_cn.1C340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C350[] = {
#include "textures/segment2/segment2_cn.1C350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C360[] = {
#include "textures/segment2/segment2_cn.1C360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C370[] = {
#include "textures/segment2/segment2_cn.1C370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C380[] = {
#include "textures/segment2/segment2_cn.1C380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C390[] = {
#include "textures/segment2/segment2_cn.1C390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C3A0[] = {
#include "textures/segment2/segment2_cn.1C3A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C3B0[] = {
#include "textures/segment2/segment2_cn.1C3B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C3C0[] = {
#include "textures/segment2/segment2_cn.1C3C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C3D0[] = {
#include "textures/segment2/segment2_cn.1C3D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C3E0[] = {
#include "textures/segment2/segment2_cn.1C3E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C3F0[] = {
#include "textures/segment2/segment2_cn.1C3F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C400[] = {
#include "textures/segment2/segment2_cn.1C400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C410[] = {
#include "textures/segment2/segment2_cn.1C410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C420[] = {
#include "textures/segment2/segment2_cn.1C420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C430[] = {
#include "textures/segment2/segment2_cn.1C430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C440[] = {
#include "textures/segment2/segment2_cn.1C440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C450[] = {
#include "textures/segment2/segment2_cn.1C450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C460[] = {
#include "textures/segment2/segment2_cn.1C460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C470[] = {
#include "textures/segment2/segment2_cn.1C470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C480[] = {
#include "textures/segment2/segment2_cn.1C480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C490[] = {
#include "textures/segment2/segment2_cn.1C490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C4A0[] = {
#include "textures/segment2/segment2_cn.1C4A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C4B0[] = {
#include "textures/segment2/segment2_cn.1C4B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C4C0[] = {
#include "textures/segment2/segment2_cn.1C4C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C4D0[] = {
#include "textures/segment2/segment2_cn.1C4D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C4E0[] = {
#include "textures/segment2/segment2_cn.1C4E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C4F0[] = {
#include "textures/segment2/segment2_cn.1C4F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C500[] = {
#include "textures/segment2/segment2_cn.1C500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C510[] = {
#include "textures/segment2/segment2_cn.1C510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C520[] = {
#include "textures/segment2/segment2_cn.1C520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C530[] = {
#include "textures/segment2/segment2_cn.1C530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C540[] = {
#include "textures/segment2/segment2_cn.1C540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C550[] = {
#include "textures/segment2/segment2_cn.1C550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C560[] = {
#include "textures/segment2/segment2_cn.1C560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C570[] = {
#include "textures/segment2/segment2_cn.1C570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C580[] = {
#include "textures/segment2/segment2_cn.1C580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C590[] = {
#include "textures/segment2/segment2_cn.1C590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C5A0[] = {
#include "textures/segment2/segment2_cn.1C5A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C5B0[] = {
#include "textures/segment2/segment2_cn.1C5B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C5C0[] = {
#include "textures/segment2/segment2_cn.1C5C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C5D0[] = {
#include "textures/segment2/segment2_cn.1C5D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C5E0[] = {
#include "textures/segment2/segment2_cn.1C5E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C5F0[] = {
#include "textures/segment2/segment2_cn.1C5F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C600[] = {
#include "textures/segment2/segment2_cn.1C600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C610[] = {
#include "textures/segment2/segment2_cn.1C610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C620[] = {
#include "textures/segment2/segment2_cn.1C620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C630[] = {
#include "textures/segment2/segment2_cn.1C630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C640[] = {
#include "textures/segment2/segment2_cn.1C640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C650[] = {
#include "textures/segment2/segment2_cn.1C650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C660[] = {
#include "textures/segment2/segment2_cn.1C660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C670[] = {
#include "textures/segment2/segment2_cn.1C670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C680[] = {
#include "textures/segment2/segment2_cn.1C680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C690[] = {
#include "textures/segment2/segment2_cn.1C690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C6A0[] = {
#include "textures/segment2/segment2_cn.1C6A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C6B0[] = {
#include "textures/segment2/segment2_cn.1C6B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C6C0[] = {
#include "textures/segment2/segment2_cn.1C6C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C6D0[] = {
#include "textures/segment2/segment2_cn.1C6D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C6E0[] = {
#include "textures/segment2/segment2_cn.1C6E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C6F0[] = {
#include "textures/segment2/segment2_cn.1C6F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C700[] = {
#include "textures/segment2/segment2_cn.1C700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C710[] = {
#include "textures/segment2/segment2_cn.1C710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C720[] = {
#include "textures/segment2/segment2_cn.1C720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C730[] = {
#include "textures/segment2/segment2_cn.1C730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C740[] = {
#include "textures/segment2/segment2_cn.1C740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C750[] = {
#include "textures/segment2/segment2_cn.1C750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C760[] = {
#include "textures/segment2/segment2_cn.1C760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C770[] = {
#include "textures/segment2/segment2_cn.1C770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C780[] = {
#include "textures/segment2/segment2_cn.1C780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C790[] = {
#include "textures/segment2/segment2_cn.1C790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C7A0[] = {
#include "textures/segment2/segment2_cn.1C7A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C7B0[] = {
#include "textures/segment2/segment2_cn.1C7B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C7C0[] = {
#include "textures/segment2/segment2_cn.1C7C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C7D0[] = {
#include "textures/segment2/segment2_cn.1C7D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C7E0[] = {
#include "textures/segment2/segment2_cn.1C7E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C7F0[] = {
#include "textures/segment2/segment2_cn.1C7F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C800[] = {
#include "textures/segment2/segment2_cn.1C800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C810[] = {
#include "textures/segment2/segment2_cn.1C810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C820[] = {
#include "textures/segment2/segment2_cn.1C820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C830[] = {
#include "textures/segment2/segment2_cn.1C830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C840[] = {
#include "textures/segment2/segment2_cn.1C840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C850[] = {
#include "textures/segment2/segment2_cn.1C850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C860[] = {
#include "textures/segment2/segment2_cn.1C860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C870[] = {
#include "textures/segment2/segment2_cn.1C870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C880[] = {
#include "textures/segment2/segment2_cn.1C880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C890[] = {
#include "textures/segment2/segment2_cn.1C890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C8A0[] = {
#include "textures/segment2/segment2_cn.1C8A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C8B0[] = {
#include "textures/segment2/segment2_cn.1C8B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C8C0[] = {
#include "textures/segment2/segment2_cn.1C8C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C8D0[] = {
#include "textures/segment2/segment2_cn.1C8D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C8E0[] = {
#include "textures/segment2/segment2_cn.1C8E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C8F0[] = {
#include "textures/segment2/segment2_cn.1C8F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C900[] = {
#include "textures/segment2/segment2_cn.1C900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C910[] = {
#include "textures/segment2/segment2_cn.1C910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C920[] = {
#include "textures/segment2/segment2_cn.1C920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C930[] = {
#include "textures/segment2/segment2_cn.1C930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C940[] = {
#include "textures/segment2/segment2_cn.1C940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C950[] = {
#include "textures/segment2/segment2_cn.1C950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C960[] = {
#include "textures/segment2/segment2_cn.1C960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C970[] = {
#include "textures/segment2/segment2_cn.1C970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C980[] = {
#include "textures/segment2/segment2_cn.1C980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C990[] = {
#include "textures/segment2/segment2_cn.1C990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C9A0[] = {
#include "textures/segment2/segment2_cn.1C9A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C9B0[] = {
#include "textures/segment2/segment2_cn.1C9B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C9C0[] = {
#include "textures/segment2/segment2_cn.1C9C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C9D0[] = {
#include "textures/segment2/segment2_cn.1C9D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C9E0[] = {
#include "textures/segment2/segment2_cn.1C9E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1C9F0[] = {
#include "textures/segment2/segment2_cn.1C9F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA00[] = {
#include "textures/segment2/segment2_cn.1CA00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA10[] = {
#include "textures/segment2/segment2_cn.1CA10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA20[] = {
#include "textures/segment2/segment2_cn.1CA20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA30[] = {
#include "textures/segment2/segment2_cn.1CA30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA40[] = {
#include "textures/segment2/segment2_cn.1CA40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA50[] = {
#include "textures/segment2/segment2_cn.1CA50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA60[] = {
#include "textures/segment2/segment2_cn.1CA60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA70[] = {
#include "textures/segment2/segment2_cn.1CA70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA80[] = {
#include "textures/segment2/segment2_cn.1CA80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CA90[] = {
#include "textures/segment2/segment2_cn.1CA90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CAA0[] = {
#include "textures/segment2/segment2_cn.1CAA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CAB0[] = {
#include "textures/segment2/segment2_cn.1CAB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CAC0[] = {
#include "textures/segment2/segment2_cn.1CAC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CAD0[] = {
#include "textures/segment2/segment2_cn.1CAD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CAE0[] = {
#include "textures/segment2/segment2_cn.1CAE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CAF0[] = {
#include "textures/segment2/segment2_cn.1CAF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB00[] = {
#include "textures/segment2/segment2_cn.1CB00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB10[] = {
#include "textures/segment2/segment2_cn.1CB10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB20[] = {
#include "textures/segment2/segment2_cn.1CB20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB30[] = {
#include "textures/segment2/segment2_cn.1CB30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB40[] = {
#include "textures/segment2/segment2_cn.1CB40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB50[] = {
#include "textures/segment2/segment2_cn.1CB50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB60[] = {
#include "textures/segment2/segment2_cn.1CB60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB70[] = {
#include "textures/segment2/segment2_cn.1CB70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB80[] = {
#include "textures/segment2/segment2_cn.1CB80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CB90[] = {
#include "textures/segment2/segment2_cn.1CB90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CBA0[] = {
#include "textures/segment2/segment2_cn.1CBA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CBB0[] = {
#include "textures/segment2/segment2_cn.1CBB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CBC0[] = {
#include "textures/segment2/segment2_cn.1CBC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CBD0[] = {
#include "textures/segment2/segment2_cn.1CBD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CBE0[] = {
#include "textures/segment2/segment2_cn.1CBE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CBF0[] = {
#include "textures/segment2/segment2_cn.1CBF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC00[] = {
#include "textures/segment2/segment2_cn.1CC00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC10[] = {
#include "textures/segment2/segment2_cn.1CC10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC20[] = {
#include "textures/segment2/segment2_cn.1CC20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC30[] = {
#include "textures/segment2/segment2_cn.1CC30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC40[] = {
#include "textures/segment2/segment2_cn.1CC40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC50[] = {
#include "textures/segment2/segment2_cn.1CC50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC60[] = {
#include "textures/segment2/segment2_cn.1CC60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC70[] = {
#include "textures/segment2/segment2_cn.1CC70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC80[] = {
#include "textures/segment2/segment2_cn.1CC80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CC90[] = {
#include "textures/segment2/segment2_cn.1CC90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CCA0[] = {
#include "textures/segment2/segment2_cn.1CCA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CCB0[] = {
#include "textures/segment2/segment2_cn.1CCB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CCC0[] = {
#include "textures/segment2/segment2_cn.1CCC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CCD0[] = {
#include "textures/segment2/segment2_cn.1CCD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CCE0[] = {
#include "textures/segment2/segment2_cn.1CCE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CCF0[] = {
#include "textures/segment2/segment2_cn.1CCF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD00[] = {
#include "textures/segment2/segment2_cn.1CD00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD10[] = {
#include "textures/segment2/segment2_cn.1CD10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD20[] = {
#include "textures/segment2/segment2_cn.1CD20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD30[] = {
#include "textures/segment2/segment2_cn.1CD30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD40[] = {
#include "textures/segment2/segment2_cn.1CD40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD50[] = {
#include "textures/segment2/segment2_cn.1CD50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD60[] = {
#include "textures/segment2/segment2_cn.1CD60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD70[] = {
#include "textures/segment2/segment2_cn.1CD70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD80[] = {
#include "textures/segment2/segment2_cn.1CD80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CD90[] = {
#include "textures/segment2/segment2_cn.1CD90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CDA0[] = {
#include "textures/segment2/segment2_cn.1CDA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CDB0[] = {
#include "textures/segment2/segment2_cn.1CDB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CDC0[] = {
#include "textures/segment2/segment2_cn.1CDC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CDD0[] = {
#include "textures/segment2/segment2_cn.1CDD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CDE0[] = {
#include "textures/segment2/segment2_cn.1CDE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CDF0[] = {
#include "textures/segment2/segment2_cn.1CDF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE00[] = {
#include "textures/segment2/segment2_cn.1CE00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE10[] = {
#include "textures/segment2/segment2_cn.1CE10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE20[] = {
#include "textures/segment2/segment2_cn.1CE20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE30[] = {
#include "textures/segment2/segment2_cn.1CE30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE40[] = {
#include "textures/segment2/segment2_cn.1CE40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE50[] = {
#include "textures/segment2/segment2_cn.1CE50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE60[] = {
#include "textures/segment2/segment2_cn.1CE60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE70[] = {
#include "textures/segment2/segment2_cn.1CE70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE80[] = {
#include "textures/segment2/segment2_cn.1CE80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CE90[] = {
#include "textures/segment2/segment2_cn.1CE90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CEA0[] = {
#include "textures/segment2/segment2_cn.1CEA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CEB0[] = {
#include "textures/segment2/segment2_cn.1CEB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CEC0[] = {
#include "textures/segment2/segment2_cn.1CEC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CED0[] = {
#include "textures/segment2/segment2_cn.1CED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CEE0[] = {
#include "textures/segment2/segment2_cn.1CEE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CEF0[] = {
#include "textures/segment2/segment2_cn.1CEF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF00[] = {
#include "textures/segment2/segment2_cn.1CF00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF10[] = {
#include "textures/segment2/segment2_cn.1CF10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF20[] = {
#include "textures/segment2/segment2_cn.1CF20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF30[] = {
#include "textures/segment2/segment2_cn.1CF30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF40[] = {
#include "textures/segment2/segment2_cn.1CF40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF50[] = {
#include "textures/segment2/segment2_cn.1CF50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF60[] = {
#include "textures/segment2/segment2_cn.1CF60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF70[] = {
#include "textures/segment2/segment2_cn.1CF70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF80[] = {
#include "textures/segment2/segment2_cn.1CF80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CF90[] = {
#include "textures/segment2/segment2_cn.1CF90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CFA0[] = {
#include "textures/segment2/segment2_cn.1CFA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CFB0[] = {
#include "textures/segment2/segment2_cn.1CFB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CFC0[] = {
#include "textures/segment2/segment2_cn.1CFC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CFD0[] = {
#include "textures/segment2/segment2_cn.1CFD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CFE0[] = {
#include "textures/segment2/segment2_cn.1CFE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1CFF0[] = {
#include "textures/segment2/segment2_cn.1CFF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D000[] = {
#include "textures/segment2/segment2_cn.1D000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D010[] = {
#include "textures/segment2/segment2_cn.1D010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D020[] = {
#include "textures/segment2/segment2_cn.1D020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D030[] = {
#include "textures/segment2/segment2_cn.1D030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D040[] = {
#include "textures/segment2/segment2_cn.1D040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D050[] = {
#include "textures/segment2/segment2_cn.1D050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D060[] = {
#include "textures/segment2/segment2_cn.1D060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D070[] = {
#include "textures/segment2/segment2_cn.1D070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D080[] = {
#include "textures/segment2/segment2_cn.1D080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D090[] = {
#include "textures/segment2/segment2_cn.1D090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D0A0[] = {
#include "textures/segment2/segment2_cn.1D0A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D0B0[] = {
#include "textures/segment2/segment2_cn.1D0B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D0C0[] = {
#include "textures/segment2/segment2_cn.1D0C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D0D0[] = {
#include "textures/segment2/segment2_cn.1D0D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D0E0[] = {
#include "textures/segment2/segment2_cn.1D0E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D0F0[] = {
#include "textures/segment2/segment2_cn.1D0F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D100[] = {
#include "textures/segment2/segment2_cn.1D100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D110[] = {
#include "textures/segment2/segment2_cn.1D110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D120[] = {
#include "textures/segment2/segment2_cn.1D120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D130[] = {
#include "textures/segment2/segment2_cn.1D130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D140[] = {
#include "textures/segment2/segment2_cn.1D140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D150[] = {
#include "textures/segment2/segment2_cn.1D150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D160[] = {
#include "textures/segment2/segment2_cn.1D160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D170[] = {
#include "textures/segment2/segment2_cn.1D170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D180[] = {
#include "textures/segment2/segment2_cn.1D180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D190[] = {
#include "textures/segment2/segment2_cn.1D190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D1A0[] = {
#include "textures/segment2/segment2_cn.1D1A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D1B0[] = {
#include "textures/segment2/segment2_cn.1D1B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D1C0[] = {
#include "textures/segment2/segment2_cn.1D1C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D1D0[] = {
#include "textures/segment2/segment2_cn.1D1D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D1E0[] = {
#include "textures/segment2/segment2_cn.1D1E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D1F0[] = {
#include "textures/segment2/segment2_cn.1D1F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D200[] = {
#include "textures/segment2/segment2_cn.1D200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D210[] = {
#include "textures/segment2/segment2_cn.1D210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D220[] = {
#include "textures/segment2/segment2_cn.1D220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D230[] = {
#include "textures/segment2/segment2_cn.1D230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D240[] = {
#include "textures/segment2/segment2_cn.1D240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D250[] = {
#include "textures/segment2/segment2_cn.1D250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D260[] = {
#include "textures/segment2/segment2_cn.1D260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D270[] = {
#include "textures/segment2/segment2_cn.1D270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D280[] = {
#include "textures/segment2/segment2_cn.1D280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D290[] = {
#include "textures/segment2/segment2_cn.1D290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D2A0[] = {
#include "textures/segment2/segment2_cn.1D2A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D2B0[] = {
#include "textures/segment2/segment2_cn.1D2B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D2C0[] = {
#include "textures/segment2/segment2_cn.1D2C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D2D0[] = {
#include "textures/segment2/segment2_cn.1D2D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D2E0[] = {
#include "textures/segment2/segment2_cn.1D2E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D2F0[] = {
#include "textures/segment2/segment2_cn.1D2F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D300[] = {
#include "textures/segment2/segment2_cn.1D300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D310[] = {
#include "textures/segment2/segment2_cn.1D310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D320[] = {
#include "textures/segment2/segment2_cn.1D320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D330[] = {
#include "textures/segment2/segment2_cn.1D330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D340[] = {
#include "textures/segment2/segment2_cn.1D340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D350[] = {
#include "textures/segment2/segment2_cn.1D350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D360[] = {
#include "textures/segment2/segment2_cn.1D360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D370[] = {
#include "textures/segment2/segment2_cn.1D370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D380[] = {
#include "textures/segment2/segment2_cn.1D380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D390[] = {
#include "textures/segment2/segment2_cn.1D390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D3A0[] = {
#include "textures/segment2/segment2_cn.1D3A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D3B0[] = {
#include "textures/segment2/segment2_cn.1D3B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D3C0[] = {
#include "textures/segment2/segment2_cn.1D3C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D3D0[] = {
#include "textures/segment2/segment2_cn.1D3D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D3E0[] = {
#include "textures/segment2/segment2_cn.1D3E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D3F0[] = {
#include "textures/segment2/segment2_cn.1D3F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D400[] = {
#include "textures/segment2/segment2_cn.1D400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D410[] = {
#include "textures/segment2/segment2_cn.1D410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D420[] = {
#include "textures/segment2/segment2_cn.1D420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D430[] = {
#include "textures/segment2/segment2_cn.1D430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D440[] = {
#include "textures/segment2/segment2_cn.1D440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D450[] = {
#include "textures/segment2/segment2_cn.1D450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D460[] = {
#include "textures/segment2/segment2_cn.1D460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D470[] = {
#include "textures/segment2/segment2_cn.1D470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D480[] = {
#include "textures/segment2/segment2_cn.1D480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D490[] = {
#include "textures/segment2/segment2_cn.1D490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D4A0[] = {
#include "textures/segment2/segment2_cn.1D4A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D4B0[] = {
#include "textures/segment2/segment2_cn.1D4B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D4C0[] = {
#include "textures/segment2/segment2_cn.1D4C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D4D0[] = {
#include "textures/segment2/segment2_cn.1D4D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D4E0[] = {
#include "textures/segment2/segment2_cn.1D4E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D4F0[] = {
#include "textures/segment2/segment2_cn.1D4F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D500[] = {
#include "textures/segment2/segment2_cn.1D500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D510[] = {
#include "textures/segment2/segment2_cn.1D510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D520[] = {
#include "textures/segment2/segment2_cn.1D520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D530[] = {
#include "textures/segment2/segment2_cn.1D530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D540[] = {
#include "textures/segment2/segment2_cn.1D540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D550[] = {
#include "textures/segment2/segment2_cn.1D550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D560[] = {
#include "textures/segment2/segment2_cn.1D560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D570[] = {
#include "textures/segment2/segment2_cn.1D570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D580[] = {
#include "textures/segment2/segment2_cn.1D580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D590[] = {
#include "textures/segment2/segment2_cn.1D590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D5A0[] = {
#include "textures/segment2/segment2_cn.1D5A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D5B0[] = {
#include "textures/segment2/segment2_cn.1D5B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D5C0[] = {
#include "textures/segment2/segment2_cn.1D5C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D5D0[] = {
#include "textures/segment2/segment2_cn.1D5D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D5E0[] = {
#include "textures/segment2/segment2_cn.1D5E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D5F0[] = {
#include "textures/segment2/segment2_cn.1D5F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D600[] = {
#include "textures/segment2/segment2_cn.1D600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D610[] = {
#include "textures/segment2/segment2_cn.1D610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D620[] = {
#include "textures/segment2/segment2_cn.1D620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D630[] = {
#include "textures/segment2/segment2_cn.1D630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D640[] = {
#include "textures/segment2/segment2_cn.1D640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D650[] = {
#include "textures/segment2/segment2_cn.1D650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D660[] = {
#include "textures/segment2/segment2_cn.1D660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D670[] = {
#include "textures/segment2/segment2_cn.1D670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D680[] = {
#include "textures/segment2/segment2_cn.1D680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D690[] = {
#include "textures/segment2/segment2_cn.1D690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D6A0[] = {
#include "textures/segment2/segment2_cn.1D6A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D6B0[] = {
#include "textures/segment2/segment2_cn.1D6B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D6C0[] = {
#include "textures/segment2/segment2_cn.1D6C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D6D0[] = {
#include "textures/segment2/segment2_cn.1D6D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D6E0[] = {
#include "textures/segment2/segment2_cn.1D6E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D6F0[] = {
#include "textures/segment2/segment2_cn.1D6F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D700[] = {
#include "textures/segment2/segment2_cn.1D700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D710[] = {
#include "textures/segment2/segment2_cn.1D710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D720[] = {
#include "textures/segment2/segment2_cn.1D720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D730[] = {
#include "textures/segment2/segment2_cn.1D730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D740[] = {
#include "textures/segment2/segment2_cn.1D740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D750[] = {
#include "textures/segment2/segment2_cn.1D750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D760[] = {
#include "textures/segment2/segment2_cn.1D760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D770[] = {
#include "textures/segment2/segment2_cn.1D770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D780[] = {
#include "textures/segment2/segment2_cn.1D780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D790[] = {
#include "textures/segment2/segment2_cn.1D790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D7A0[] = {
#include "textures/segment2/segment2_cn.1D7A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D7B0[] = {
#include "textures/segment2/segment2_cn.1D7B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D7C0[] = {
#include "textures/segment2/segment2_cn.1D7C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D7D0[] = {
#include "textures/segment2/segment2_cn.1D7D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D7E0[] = {
#include "textures/segment2/segment2_cn.1D7E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D7F0[] = {
#include "textures/segment2/segment2_cn.1D7F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D800[] = {
#include "textures/segment2/segment2_cn.1D800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D810[] = {
#include "textures/segment2/segment2_cn.1D810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D820[] = {
#include "textures/segment2/segment2_cn.1D820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D830[] = {
#include "textures/segment2/segment2_cn.1D830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D840[] = {
#include "textures/segment2/segment2_cn.1D840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D850[] = {
#include "textures/segment2/segment2_cn.1D850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D860[] = {
#include "textures/segment2/segment2_cn.1D860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D870[] = {
#include "textures/segment2/segment2_cn.1D870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D880[] = {
#include "textures/segment2/segment2_cn.1D880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D890[] = {
#include "textures/segment2/segment2_cn.1D890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D8A0[] = {
#include "textures/segment2/segment2_cn.1D8A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D8B0[] = {
#include "textures/segment2/segment2_cn.1D8B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D8C0[] = {
#include "textures/segment2/segment2_cn.1D8C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D8D0[] = {
#include "textures/segment2/segment2_cn.1D8D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D8E0[] = {
#include "textures/segment2/segment2_cn.1D8E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D8F0[] = {
#include "textures/segment2/segment2_cn.1D8F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D900[] = {
#include "textures/segment2/segment2_cn.1D900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D910[] = {
#include "textures/segment2/segment2_cn.1D910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D920[] = {
#include "textures/segment2/segment2_cn.1D920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D930[] = {
#include "textures/segment2/segment2_cn.1D930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D940[] = {
#include "textures/segment2/segment2_cn.1D940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D950[] = {
#include "textures/segment2/segment2_cn.1D950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D960[] = {
#include "textures/segment2/segment2_cn.1D960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D970[] = {
#include "textures/segment2/segment2_cn.1D970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D980[] = {
#include "textures/segment2/segment2_cn.1D980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D990[] = {
#include "textures/segment2/segment2_cn.1D990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D9A0[] = {
#include "textures/segment2/segment2_cn.1D9A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D9B0[] = {
#include "textures/segment2/segment2_cn.1D9B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D9C0[] = {
#include "textures/segment2/segment2_cn.1D9C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D9D0[] = {
#include "textures/segment2/segment2_cn.1D9D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D9E0[] = {
#include "textures/segment2/segment2_cn.1D9E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1D9F0[] = {
#include "textures/segment2/segment2_cn.1D9F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA00[] = {
#include "textures/segment2/segment2_cn.1DA00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA10[] = {
#include "textures/segment2/segment2_cn.1DA10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA20[] = {
#include "textures/segment2/segment2_cn.1DA20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA30[] = {
#include "textures/segment2/segment2_cn.1DA30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA40[] = {
#include "textures/segment2/segment2_cn.1DA40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA50[] = {
#include "textures/segment2/segment2_cn.1DA50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA60[] = {
#include "textures/segment2/segment2_cn.1DA60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA70[] = {
#include "textures/segment2/segment2_cn.1DA70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA80[] = {
#include "textures/segment2/segment2_cn.1DA80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DA90[] = {
#include "textures/segment2/segment2_cn.1DA90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DAA0[] = {
#include "textures/segment2/segment2_cn.1DAA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DAB0[] = {
#include "textures/segment2/segment2_cn.1DAB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DAC0[] = {
#include "textures/segment2/segment2_cn.1DAC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DAD0[] = {
#include "textures/segment2/segment2_cn.1DAD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DAE0[] = {
#include "textures/segment2/segment2_cn.1DAE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DAF0[] = {
#include "textures/segment2/segment2_cn.1DAF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB00[] = {
#include "textures/segment2/segment2_cn.1DB00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB10[] = {
#include "textures/segment2/segment2_cn.1DB10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB20[] = {
#include "textures/segment2/segment2_cn.1DB20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB30[] = {
#include "textures/segment2/segment2_cn.1DB30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB40[] = {
#include "textures/segment2/segment2_cn.1DB40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB50[] = {
#include "textures/segment2/segment2_cn.1DB50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB60[] = {
#include "textures/segment2/segment2_cn.1DB60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB70[] = {
#include "textures/segment2/segment2_cn.1DB70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB80[] = {
#include "textures/segment2/segment2_cn.1DB80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DB90[] = {
#include "textures/segment2/segment2_cn.1DB90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DBA0[] = {
#include "textures/segment2/segment2_cn.1DBA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DBB0[] = {
#include "textures/segment2/segment2_cn.1DBB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DBC0[] = {
#include "textures/segment2/segment2_cn.1DBC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DBD0[] = {
#include "textures/segment2/segment2_cn.1DBD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DBE0[] = {
#include "textures/segment2/segment2_cn.1DBE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DBF0[] = {
#include "textures/segment2/segment2_cn.1DBF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC00[] = {
#include "textures/segment2/segment2_cn.1DC00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC10[] = {
#include "textures/segment2/segment2_cn.1DC10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC20[] = {
#include "textures/segment2/segment2_cn.1DC20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC30[] = {
#include "textures/segment2/segment2_cn.1DC30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC40[] = {
#include "textures/segment2/segment2_cn.1DC40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC50[] = {
#include "textures/segment2/segment2_cn.1DC50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC60[] = {
#include "textures/segment2/segment2_cn.1DC60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC70[] = {
#include "textures/segment2/segment2_cn.1DC70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC80[] = {
#include "textures/segment2/segment2_cn.1DC80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DC90[] = {
#include "textures/segment2/segment2_cn.1DC90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DCA0[] = {
#include "textures/segment2/segment2_cn.1DCA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DCB0[] = {
#include "textures/segment2/segment2_cn.1DCB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DCC0[] = {
#include "textures/segment2/segment2_cn.1DCC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DCD0[] = {
#include "textures/segment2/segment2_cn.1DCD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DCE0[] = {
#include "textures/segment2/segment2_cn.1DCE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DCF0[] = {
#include "textures/segment2/segment2_cn.1DCF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD00[] = {
#include "textures/segment2/segment2_cn.1DD00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD10[] = {
#include "textures/segment2/segment2_cn.1DD10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD20[] = {
#include "textures/segment2/segment2_cn.1DD20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD30[] = {
#include "textures/segment2/segment2_cn.1DD30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD40[] = {
#include "textures/segment2/segment2_cn.1DD40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD50[] = {
#include "textures/segment2/segment2_cn.1DD50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD60[] = {
#include "textures/segment2/segment2_cn.1DD60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD70[] = {
#include "textures/segment2/segment2_cn.1DD70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD80[] = {
#include "textures/segment2/segment2_cn.1DD80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DD90[] = {
#include "textures/segment2/segment2_cn.1DD90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DDA0[] = {
#include "textures/segment2/segment2_cn.1DDA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DDB0[] = {
#include "textures/segment2/segment2_cn.1DDB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DDC0[] = {
#include "textures/segment2/segment2_cn.1DDC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DDD0[] = {
#include "textures/segment2/segment2_cn.1DDD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DDE0[] = {
#include "textures/segment2/segment2_cn.1DDE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DDF0[] = {
#include "textures/segment2/segment2_cn.1DDF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE00[] = {
#include "textures/segment2/segment2_cn.1DE00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE10[] = {
#include "textures/segment2/segment2_cn.1DE10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE20[] = {
#include "textures/segment2/segment2_cn.1DE20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE30[] = {
#include "textures/segment2/segment2_cn.1DE30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE40[] = {
#include "textures/segment2/segment2_cn.1DE40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE50[] = {
#include "textures/segment2/segment2_cn.1DE50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE60[] = {
#include "textures/segment2/segment2_cn.1DE60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE70[] = {
#include "textures/segment2/segment2_cn.1DE70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE80[] = {
#include "textures/segment2/segment2_cn.1DE80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DE90[] = {
#include "textures/segment2/segment2_cn.1DE90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DEA0[] = {
#include "textures/segment2/segment2_cn.1DEA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DEB0[] = {
#include "textures/segment2/segment2_cn.1DEB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DEC0[] = {
#include "textures/segment2/segment2_cn.1DEC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DED0[] = {
#include "textures/segment2/segment2_cn.1DED0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DEE0[] = {
#include "textures/segment2/segment2_cn.1DEE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DEF0[] = {
#include "textures/segment2/segment2_cn.1DEF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF00[] = {
#include "textures/segment2/segment2_cn.1DF00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF10[] = {
#include "textures/segment2/segment2_cn.1DF10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF20[] = {
#include "textures/segment2/segment2_cn.1DF20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF30[] = {
#include "textures/segment2/segment2_cn.1DF30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF40[] = {
#include "textures/segment2/segment2_cn.1DF40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF50[] = {
#include "textures/segment2/segment2_cn.1DF50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF60[] = {
#include "textures/segment2/segment2_cn.1DF60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF70[] = {
#include "textures/segment2/segment2_cn.1DF70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF80[] = {
#include "textures/segment2/segment2_cn.1DF80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DF90[] = {
#include "textures/segment2/segment2_cn.1DF90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DFA0[] = {
#include "textures/segment2/segment2_cn.1DFA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DFB0[] = {
#include "textures/segment2/segment2_cn.1DFB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DFC0[] = {
#include "textures/segment2/segment2_cn.1DFC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DFD0[] = {
#include "textures/segment2/segment2_cn.1DFD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DFE0[] = {
#include "textures/segment2/segment2_cn.1DFE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1DFF0[] = {
#include "textures/segment2/segment2_cn.1DFF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E000[] = {
#include "textures/segment2/segment2_cn.1E000.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E010[] = {
#include "textures/segment2/segment2_cn.1E010.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E020[] = {
#include "textures/segment2/segment2_cn.1E020.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E030[] = {
#include "textures/segment2/segment2_cn.1E030.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E040[] = {
#include "textures/segment2/segment2_cn.1E040.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E050[] = {
#include "textures/segment2/segment2_cn.1E050.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E060[] = {
#include "textures/segment2/segment2_cn.1E060.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E070[] = {
#include "textures/segment2/segment2_cn.1E070.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E080[] = {
#include "textures/segment2/segment2_cn.1E080.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E090[] = {
#include "textures/segment2/segment2_cn.1E090.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E0A0[] = {
#include "textures/segment2/segment2_cn.1E0A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E0B0[] = {
#include "textures/segment2/segment2_cn.1E0B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E0C0[] = {
#include "textures/segment2/segment2_cn.1E0C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E0D0[] = {
#include "textures/segment2/segment2_cn.1E0D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E0E0[] = {
#include "textures/segment2/segment2_cn.1E0E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E0F0[] = {
#include "textures/segment2/segment2_cn.1E0F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E100[] = {
#include "textures/segment2/segment2_cn.1E100.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E110[] = {
#include "textures/segment2/segment2_cn.1E110.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E120[] = {
#include "textures/segment2/segment2_cn.1E120.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E130[] = {
#include "textures/segment2/segment2_cn.1E130.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E140[] = {
#include "textures/segment2/segment2_cn.1E140.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E150[] = {
#include "textures/segment2/segment2_cn.1E150.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E160[] = {
#include "textures/segment2/segment2_cn.1E160.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E170[] = {
#include "textures/segment2/segment2_cn.1E170.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E180[] = {
#include "textures/segment2/segment2_cn.1E180.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E190[] = {
#include "textures/segment2/segment2_cn.1E190.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E1A0[] = {
#include "textures/segment2/segment2_cn.1E1A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E1B0[] = {
#include "textures/segment2/segment2_cn.1E1B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E1C0[] = {
#include "textures/segment2/segment2_cn.1E1C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E1D0[] = {
#include "textures/segment2/segment2_cn.1E1D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E1E0[] = {
#include "textures/segment2/segment2_cn.1E1E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E1F0[] = {
#include "textures/segment2/segment2_cn.1E1F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E200[] = {
#include "textures/segment2/segment2_cn.1E200.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E210[] = {
#include "textures/segment2/segment2_cn.1E210.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E220[] = {
#include "textures/segment2/segment2_cn.1E220.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E230[] = {
#include "textures/segment2/segment2_cn.1E230.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E240[] = {
#include "textures/segment2/segment2_cn.1E240.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E250[] = {
#include "textures/segment2/segment2_cn.1E250.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E260[] = {
#include "textures/segment2/segment2_cn.1E260.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E270[] = {
#include "textures/segment2/segment2_cn.1E270.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E280[] = {
#include "textures/segment2/segment2_cn.1E280.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E290[] = {
#include "textures/segment2/segment2_cn.1E290.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E2A0[] = {
#include "textures/segment2/segment2_cn.1E2A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E2B0[] = {
#include "textures/segment2/segment2_cn.1E2B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E2C0[] = {
#include "textures/segment2/segment2_cn.1E2C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E2D0[] = {
#include "textures/segment2/segment2_cn.1E2D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E2E0[] = {
#include "textures/segment2/segment2_cn.1E2E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E2F0[] = {
#include "textures/segment2/segment2_cn.1E2F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E300[] = {
#include "textures/segment2/segment2_cn.1E300.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E310[] = {
#include "textures/segment2/segment2_cn.1E310.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E320[] = {
#include "textures/segment2/segment2_cn.1E320.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E330[] = {
#include "textures/segment2/segment2_cn.1E330.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E340[] = {
#include "textures/segment2/segment2_cn.1E340.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E350[] = {
#include "textures/segment2/segment2_cn.1E350.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E360[] = {
#include "textures/segment2/segment2_cn.1E360.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E370[] = {
#include "textures/segment2/segment2_cn.1E370.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E380[] = {
#include "textures/segment2/segment2_cn.1E380.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E390[] = {
#include "textures/segment2/segment2_cn.1E390.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E3A0[] = {
#include "textures/segment2/segment2_cn.1E3A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E3B0[] = {
#include "textures/segment2/segment2_cn.1E3B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E3C0[] = {
#include "textures/segment2/segment2_cn.1E3C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E3D0[] = {
#include "textures/segment2/segment2_cn.1E3D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E3E0[] = {
#include "textures/segment2/segment2_cn.1E3E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E3F0[] = {
#include "textures/segment2/segment2_cn.1E3F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E400[] = {
#include "textures/segment2/segment2_cn.1E400.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E410[] = {
#include "textures/segment2/segment2_cn.1E410.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E420[] = {
#include "textures/segment2/segment2_cn.1E420.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E430[] = {
#include "textures/segment2/segment2_cn.1E430.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E440[] = {
#include "textures/segment2/segment2_cn.1E440.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E450[] = {
#include "textures/segment2/segment2_cn.1E450.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E460[] = {
#include "textures/segment2/segment2_cn.1E460.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E470[] = {
#include "textures/segment2/segment2_cn.1E470.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E480[] = {
#include "textures/segment2/segment2_cn.1E480.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E490[] = {
#include "textures/segment2/segment2_cn.1E490.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E4A0[] = {
#include "textures/segment2/segment2_cn.1E4A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E4B0[] = {
#include "textures/segment2/segment2_cn.1E4B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E4C0[] = {
#include "textures/segment2/segment2_cn.1E4C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E4D0[] = {
#include "textures/segment2/segment2_cn.1E4D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E4E0[] = {
#include "textures/segment2/segment2_cn.1E4E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E4F0[] = {
#include "textures/segment2/segment2_cn.1E4F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E500[] = {
#include "textures/segment2/segment2_cn.1E500.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E510[] = {
#include "textures/segment2/segment2_cn.1E510.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E520[] = {
#include "textures/segment2/segment2_cn.1E520.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E530[] = {
#include "textures/segment2/segment2_cn.1E530.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E540[] = {
#include "textures/segment2/segment2_cn.1E540.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E550[] = {
#include "textures/segment2/segment2_cn.1E550.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E560[] = {
#include "textures/segment2/segment2_cn.1E560.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E570[] = {
#include "textures/segment2/segment2_cn.1E570.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E580[] = {
#include "textures/segment2/segment2_cn.1E580.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E590[] = {
#include "textures/segment2/segment2_cn.1E590.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E5A0[] = {
#include "textures/segment2/segment2_cn.1E5A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E5B0[] = {
#include "textures/segment2/segment2_cn.1E5B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E5C0[] = {
#include "textures/segment2/segment2_cn.1E5C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E5D0[] = {
#include "textures/segment2/segment2_cn.1E5D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E5E0[] = {
#include "textures/segment2/segment2_cn.1E5E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E5F0[] = {
#include "textures/segment2/segment2_cn.1E5F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E600[] = {
#include "textures/segment2/segment2_cn.1E600.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E610[] = {
#include "textures/segment2/segment2_cn.1E610.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E620[] = {
#include "textures/segment2/segment2_cn.1E620.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E630[] = {
#include "textures/segment2/segment2_cn.1E630.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E640[] = {
#include "textures/segment2/segment2_cn.1E640.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E650[] = {
#include "textures/segment2/segment2_cn.1E650.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E660[] = {
#include "textures/segment2/segment2_cn.1E660.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E670[] = {
#include "textures/segment2/segment2_cn.1E670.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E680[] = {
#include "textures/segment2/segment2_cn.1E680.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E690[] = {
#include "textures/segment2/segment2_cn.1E690.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E6A0[] = {
#include "textures/segment2/segment2_cn.1E6A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E6B0[] = {
#include "textures/segment2/segment2_cn.1E6B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E6C0[] = {
#include "textures/segment2/segment2_cn.1E6C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E6D0[] = {
#include "textures/segment2/segment2_cn.1E6D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E6E0[] = {
#include "textures/segment2/segment2_cn.1E6E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E6F0[] = {
#include "textures/segment2/segment2_cn.1E6F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E700[] = {
#include "textures/segment2/segment2_cn.1E700.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E710[] = {
#include "textures/segment2/segment2_cn.1E710.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E720[] = {
#include "textures/segment2/segment2_cn.1E720.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E730[] = {
#include "textures/segment2/segment2_cn.1E730.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E740[] = {
#include "textures/segment2/segment2_cn.1E740.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E750[] = {
#include "textures/segment2/segment2_cn.1E750.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E760[] = {
#include "textures/segment2/segment2_cn.1E760.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E770[] = {
#include "textures/segment2/segment2_cn.1E770.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E780[] = {
#include "textures/segment2/segment2_cn.1E780.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E790[] = {
#include "textures/segment2/segment2_cn.1E790.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E7A0[] = {
#include "textures/segment2/segment2_cn.1E7A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E7B0[] = {
#include "textures/segment2/segment2_cn.1E7B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E7C0[] = {
#include "textures/segment2/segment2_cn.1E7C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E7D0[] = {
#include "textures/segment2/segment2_cn.1E7D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E7E0[] = {
#include "textures/segment2/segment2_cn.1E7E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E7F0[] = {
#include "textures/segment2/segment2_cn.1E7F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E800[] = {
#include "textures/segment2/segment2_cn.1E800.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E810[] = {
#include "textures/segment2/segment2_cn.1E810.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E820[] = {
#include "textures/segment2/segment2_cn.1E820.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E830[] = {
#include "textures/segment2/segment2_cn.1E830.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E840[] = {
#include "textures/segment2/segment2_cn.1E840.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E850[] = {
#include "textures/segment2/segment2_cn.1E850.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E860[] = {
#include "textures/segment2/segment2_cn.1E860.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E870[] = {
#include "textures/segment2/segment2_cn.1E870.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E880[] = {
#include "textures/segment2/segment2_cn.1E880.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E890[] = {
#include "textures/segment2/segment2_cn.1E890.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E8A0[] = {
#include "textures/segment2/segment2_cn.1E8A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E8B0[] = {
#include "textures/segment2/segment2_cn.1E8B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E8C0[] = {
#include "textures/segment2/segment2_cn.1E8C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E8D0[] = {
#include "textures/segment2/segment2_cn.1E8D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E8E0[] = {
#include "textures/segment2/segment2_cn.1E8E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E8F0[] = {
#include "textures/segment2/segment2_cn.1E8F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E900[] = {
#include "textures/segment2/segment2_cn.1E900.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E910[] = {
#include "textures/segment2/segment2_cn.1E910.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E920[] = {
#include "textures/segment2/segment2_cn.1E920.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E930[] = {
#include "textures/segment2/segment2_cn.1E930.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E940[] = {
#include "textures/segment2/segment2_cn.1E940.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E950[] = {
#include "textures/segment2/segment2_cn.1E950.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E960[] = {
#include "textures/segment2/segment2_cn.1E960.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E970[] = {
#include "textures/segment2/segment2_cn.1E970.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E980[] = {
#include "textures/segment2/segment2_cn.1E980.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E990[] = {
#include "textures/segment2/segment2_cn.1E990.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E9A0[] = {
#include "textures/segment2/segment2_cn.1E9A0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E9B0[] = {
#include "textures/segment2/segment2_cn.1E9B0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E9C0[] = {
#include "textures/segment2/segment2_cn.1E9C0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E9D0[] = {
#include "textures/segment2/segment2_cn.1E9D0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E9E0[] = {
#include "textures/segment2/segment2_cn.1E9E0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1E9F0[] = {
#include "textures/segment2/segment2_cn.1E9F0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA00[] = {
#include "textures/segment2/segment2_cn.1EA00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA10[] = {
#include "textures/segment2/segment2_cn.1EA10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA20[] = {
#include "textures/segment2/segment2_cn.1EA20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA30[] = {
#include "textures/segment2/segment2_cn.1EA30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA40[] = {
#include "textures/segment2/segment2_cn.1EA40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA50[] = {
#include "textures/segment2/segment2_cn.1EA50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA60[] = {
#include "textures/segment2/segment2_cn.1EA60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA70[] = {
#include "textures/segment2/segment2_cn.1EA70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA80[] = {
#include "textures/segment2/segment2_cn.1EA80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EA90[] = {
#include "textures/segment2/segment2_cn.1EA90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EAA0[] = {
#include "textures/segment2/segment2_cn.1EAA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EAB0[] = {
#include "textures/segment2/segment2_cn.1EAB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EAC0[] = {
#include "textures/segment2/segment2_cn.1EAC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EAD0[] = {
#include "textures/segment2/segment2_cn.1EAD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EAE0[] = {
#include "textures/segment2/segment2_cn.1EAE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EAF0[] = {
#include "textures/segment2/segment2_cn.1EAF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB00[] = {
#include "textures/segment2/segment2_cn.1EB00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB10[] = {
#include "textures/segment2/segment2_cn.1EB10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB20[] = {
#include "textures/segment2/segment2_cn.1EB20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB30[] = {
#include "textures/segment2/segment2_cn.1EB30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB40[] = {
#include "textures/segment2/segment2_cn.1EB40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB50[] = {
#include "textures/segment2/segment2_cn.1EB50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB60[] = {
#include "textures/segment2/segment2_cn.1EB60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB70[] = {
#include "textures/segment2/segment2_cn.1EB70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB80[] = {
#include "textures/segment2/segment2_cn.1EB80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EB90[] = {
#include "textures/segment2/segment2_cn.1EB90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EBA0[] = {
#include "textures/segment2/segment2_cn.1EBA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EBB0[] = {
#include "textures/segment2/segment2_cn.1EBB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EBC0[] = {
#include "textures/segment2/segment2_cn.1EBC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EBD0[] = {
#include "textures/segment2/segment2_cn.1EBD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EBE0[] = {
#include "textures/segment2/segment2_cn.1EBE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EBF0[] = {
#include "textures/segment2/segment2_cn.1EBF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC00[] = {
#include "textures/segment2/segment2_cn.1EC00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC10[] = {
#include "textures/segment2/segment2_cn.1EC10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC20[] = {
#include "textures/segment2/segment2_cn.1EC20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC30[] = {
#include "textures/segment2/segment2_cn.1EC30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC40[] = {
#include "textures/segment2/segment2_cn.1EC40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC50[] = {
#include "textures/segment2/segment2_cn.1EC50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC60[] = {
#include "textures/segment2/segment2_cn.1EC60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC70[] = {
#include "textures/segment2/segment2_cn.1EC70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC80[] = {
#include "textures/segment2/segment2_cn.1EC80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EC90[] = {
#include "textures/segment2/segment2_cn.1EC90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ECA0[] = {
#include "textures/segment2/segment2_cn.1ECA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ECB0[] = {
#include "textures/segment2/segment2_cn.1ECB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ECC0[] = {
#include "textures/segment2/segment2_cn.1ECC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ECD0[] = {
#include "textures/segment2/segment2_cn.1ECD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ECE0[] = {
#include "textures/segment2/segment2_cn.1ECE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ECF0[] = {
#include "textures/segment2/segment2_cn.1ECF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED00[] = {
#include "textures/segment2/segment2_cn.1ED00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED10[] = {
#include "textures/segment2/segment2_cn.1ED10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED20[] = {
#include "textures/segment2/segment2_cn.1ED20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED30[] = {
#include "textures/segment2/segment2_cn.1ED30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED40[] = {
#include "textures/segment2/segment2_cn.1ED40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED50[] = {
#include "textures/segment2/segment2_cn.1ED50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED60[] = {
#include "textures/segment2/segment2_cn.1ED60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED70[] = {
#include "textures/segment2/segment2_cn.1ED70.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED80[] = {
#include "textures/segment2/segment2_cn.1ED80.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1ED90[] = {
#include "textures/segment2/segment2_cn.1ED90.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EDA0[] = {
#include "textures/segment2/segment2_cn.1EDA0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EDB0[] = {
#include "textures/segment2/segment2_cn.1EDB0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EDC0[] = {
#include "textures/segment2/segment2_cn.1EDC0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EDD0[] = {
#include "textures/segment2/segment2_cn.1EDD0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EDE0[] = {
#include "textures/segment2/segment2_cn.1EDE0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EDF0[] = {
#include "textures/segment2/segment2_cn.1EDF0.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE00[] = {
#include "textures/segment2/segment2_cn.1EE00.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE10[] = {
#include "textures/segment2/segment2_cn.1EE10.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE20[] = {
#include "textures/segment2/segment2_cn.1EE20.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE30[] = {
#include "textures/segment2/segment2_cn.1EE30.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE40[] = {
#include "textures/segment2/segment2_cn.1EE40.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE50[] = {
#include "textures/segment2/segment2_cn.1EE50.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE60[] = {
#include "textures/segment2/segment2_cn.1EE60.ia1.inc.c"
};

ALIGNED8 static const Texture texture_font_char_cn_1EE70[] = {
#include "textures/segment2/segment2_cn.1EE70.ia1.inc.c"
};
#endif // VERSION_CN

ALIGNED8 static const Texture texture_hud_char_camera[] = {
#include "textures/segment2/segment2.07B50.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_lakitu[] = {
#include "textures/segment2/segment2.07D50.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_no_camera[] = {
#include "textures/segment2/segment2.07F50.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_arrow_up[] = {
#include "textures/segment2/segment2.08150.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_arrow_down[] = {
#include "textures/segment2/segment2.081D0.rgba16.inc.c"
};

#ifdef BETTERCAMERA
ALIGNED8 const Texture texture_hud_char_puppycam[] = {
#include "textures/segment2/custom/tex_puppycam_icon.rgba16.inc.c"
};
#endif

// Moved from menu segment 7 to segment 2 to be unified with rest of HUD font
#ifdef JAPANESE_CHARACTERS
ALIGNED8 static const Texture texture_hud_char_katakana_fu[] = {
#include "levels/menu/main_menu_seg7.073D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_small_a[] = {
#include "levels/menu/main_menu_seg7.075D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_i[] = {
#include "levels/menu/main_menu_seg7.077D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_ru[] = {
#include "levels/menu/main_menu_seg7.079D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_se[] = {
#include "levels/menu/main_menu_seg7.07BD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_re[] = {
#include "levels/menu/main_menu_seg7.07DD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_ku[] = {
#include "levels/menu/main_menu_seg7.07FD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_to[] = {
#include "levels/menu/main_menu_seg7.081D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hiragana_wo[] = {
#include "levels/menu/main_menu_seg7.083D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_ko[] = {
#include "levels/menu/main_menu_seg7.085D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_kana_handakuten_pi[] = {
#include "levels/menu/main_menu_seg7.087D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_long_vowel[] = {
#include "levels/menu/main_menu_seg7.089D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hiragana_su[] = {
#include "levels/menu/main_menu_seg7.08BD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hiragana_ru[] = {
#include "levels/menu/main_menu_seg7.08DD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hiragana_ke[] = {
#include "levels/menu/main_menu_seg7.08FD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_ma[] = {
#include "levels/menu/main_menu_seg7.091D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_ri[] = {
#include "levels/menu/main_menu_seg7.093D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_o[] = {
#include "levels/menu/main_menu_seg7.095D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_su[] = {
#include "levels/menu/main_menu_seg7.097D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_a[] = {
#include "levels/menu/main_menu_seg7.099D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hiragana_mi[] = {
#include "levels/menu/main_menu_seg7.09BD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hira_dakuten_do[] = {
#include "levels/menu/main_menu_seg7.09DD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_hiragana_no[] = {
#include "levels/menu/main_menu_seg7.09FD0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_sa[] = {
#include "levels/menu/main_menu_seg7.0A3D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_u[] = {
#include "levels/menu/main_menu_seg7.0A5D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_n[] = {
#include "levels/menu/main_menu_seg7.0A7D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_kana_dakuten_do[] = {
#include "levels/menu/main_menu_seg7.0A9D0.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_katakana_ra[] = {
#include "levels/menu/custom/main_menu_seg7.katakana_ra.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_kana_dakuten_ge[] = {
#include "levels/menu/custom/main_menu_seg7.kana_dakuten_ge.rgba16.inc.c"
};

ALIGNED8 static const Texture texture_hud_char_kana_dakuten_ji[] = {
#include "levels/menu/custom/main_menu_seg7.kana_dakuten_ji.rgba16.inc.c"
};
#endif

// ASCII lookup table for the colorful HUD font
const struct AsciiCharLUTEntry main_hud_lut[] = {
    {NULL, 8}, // 32 " "
    {texture_hud_char_exclamation, 12}, // 33 "!"
    {texture_hud_char_double_quote, 10}, // 34 "\""
    {NULL, 0}, // 35 "#" (Unimplemented)
    {NULL, 0}, // 36 "$" (Unimplemented)
    {texture_hud_char_percent, 12}, // 37 "%"
    {texture_hud_char_ampersand, 12}, // 38 "&"
    {texture_hud_char_apostrophe, 8}, // 39 "'"
    {NULL, 0}, // 40 "(" (Unimplemented)
    {NULL, 0}, // 41 ")" (Unimplemented)
    {NULL, 0}, // 42 "*" (Unimplemented)
    {NULL, 0}, // 43 "+" (Unimplemented)
    {texture_hud_char_apostrophe, 8}, // 44 ","
    {texture_hud_char_minus, 16}, // 45 "-"
    {texture_hud_char_decimal_point, 8}, // 46 "."
    {NULL, 0}, // 47 "/" (Unimplemented)
    {texture_hud_char_0, 12}, // 48 "0"
    {texture_hud_char_1, 12}, // 49 "1"
    {texture_hud_char_2, 12}, // 50 "2"
    {texture_hud_char_3, 12}, // 51 "3"
    {texture_hud_char_4, 12}, // 52 "4"
    {texture_hud_char_5, 12}, // 53 "5"
    {texture_hud_char_6, 12}, // 54 "6"
    {texture_hud_char_7, 12}, // 55 "7"
    {texture_hud_char_8, 12}, // 56 "8"
    {texture_hud_char_9, 12}, // 57 "9"
    {NULL, 0}, // 58 ":" (Unimplemented)
    {NULL, 0}, // 59 ";" (Unimplemented)
    {NULL, 0}, // 60 "<" (Unimplemented)
    {NULL, 0}, // 61 "=" (Unimplemented)
    {NULL, 0}, // 62 ">" (Unimplemented)
    {texture_hud_char_question, 12}, // 63 "?"
    {NULL, 0}, // 64 "@" (Unimplemented)
    {texture_hud_char_A, 12}, // 65 "A"
    {texture_hud_char_B, 12}, // 66 "B"
    {texture_hud_char_C, 12}, // 67 "C"
    {texture_hud_char_D, 12}, // 68 "D"
    {texture_hud_char_E, 12}, // 69 "E"
    {texture_hud_char_F, 12}, // 70 "F"
    {texture_hud_char_G, 12}, // 71 "G"
    {texture_hud_char_H, 12}, // 72 "H"
    {texture_hud_char_I, 12}, // 73 "I"
    {texture_hud_char_J, 12}, // 74 "J"
    {texture_hud_char_K, 12}, // 75 "K"
    {texture_hud_char_L, 12}, // 76 "L"
    {texture_hud_char_M, 12}, // 77 "M"
    {texture_hud_char_N, 12}, // 78 "N"
    {texture_hud_char_O, 12}, // 79 "O"
    {texture_hud_char_P, 12}, // 80 "P"
    {texture_hud_char_Q, 12}, // 81 "Q"
    {texture_hud_char_R, 12}, // 82 "R"
    {texture_hud_char_S, 12}, // 83 "S"
    {texture_hud_char_T, 12}, // 84 "T"
    {texture_hud_char_U, 12}, // 85 "U"
    {texture_hud_char_V, 12}, // 86 "V"
    {texture_hud_char_W, 12}, // 87 "W"
    {texture_hud_char_X, 12}, // 88 "X"
    {texture_hud_char_Y, 12}, // 89 "Y"
    {texture_hud_char_Z, 12}, // 90 "Z"
    {NULL, 0}, // 91 "[" (Unimplemented)
    {NULL, 0}, // 92 "\\" (Unimplemented)
    {NULL, 0}, // 93 "]" (Unimplemented)
    {NULL, 0}, // 94 "^" (Unimplemented)
    {NULL, 0}, // 95 "_" (Unimplemented)
    {NULL, 0}, // 96 "`" (Unimplemented)
    {texture_hud_char_A, 12}, // 97 "a"
    {texture_hud_char_B, 12}, // 98 "b"
    {texture_hud_char_C, 12}, // 99 "c"
    {texture_hud_char_D, 12}, // 100 "d"
    {texture_hud_char_E, 12}, // 101 "e"
    {texture_hud_char_F, 12}, // 102 "f"
    {texture_hud_char_G, 12}, // 103 "g"
    {texture_hud_char_H, 12}, // 104 "h"
    {texture_hud_char_I, 12}, // 105 "i"
    {texture_hud_char_J, 12}, // 106 "j"
    {texture_hud_char_K, 12}, // 107 "k"
    {texture_hud_char_L, 12}, // 108 "l"
    {texture_hud_char_M, 12}, // 109 "m"
    {texture_hud_char_N, 12}, // 110 "n"
    {texture_hud_char_O, 12}, // 111 "o"
    {texture_hud_char_P, 12}, // 112 "p"
    {texture_hud_char_Q, 12}, // 113 "q"
    {texture_hud_char_R, 12}, // 114 "r"
    {texture_hud_char_S, 12}, // 115 "s"
    {texture_hud_char_T, 12}, // 116 "t"
    {texture_hud_char_U, 12}, // 117 "u"
    {texture_hud_char_V, 12}, // 118 "v"
    {texture_hud_char_W, 12}, // 119 "w"
    {texture_hud_char_X, 12}, // 120 "x"
    {texture_hud_char_Y, 12}, // 121 "y"
    {texture_hud_char_Z, 12}, // 122 "z"
    {NULL, 0}, // 123 "{" (Unimplemented)
    {NULL, 0}, // 124 "|" (Unimplemented)
    {NULL, 0}, // 125 "}" (Unimplemented)
    {NULL, 0}, // 126 "~" (Unimplemented)
};

// UTF-8 lookup tables for the colorful HUD font
const struct Utf8CharLUTEntry main_hud_utf8_2byte_lut[] = {
    {0x00C4, 12, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_hud_char_A}, // Ä
    {0x00CB, 12, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_hud_char_E}, // Ë
    {0x00CF, 12, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_hud_char_I}, // Ï
    {0x00D6, 12, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_hud_char_O}, // Ö
    {0x00D7, 15, 0, texture_hud_char_multiply}, // ×
    {0x00DC, 12, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_hud_char_U}, // Ü
};

const struct Utf8CharLUTEntry main_hud_utf8_3byte_lut[] = {
    {0x203C, 12, 0, texture_hud_char_double_exclamation}, // ‼
    {0x25CD, 16, 0, texture_hud_char_circle_fill}, // ◍
    {0x2605, 16, 0, texture_hud_char_star}, // ★
    {0x263A, 16, 0, texture_hud_char_mario_head}, // ☺
    {0x26BF, 16, 0, texture_hud_char_beta_key}, // ⚿
    {0x272A, 16, 0, texture_hud_char_coin}, // ✪

#ifdef JAPANESE_CHARACTERS
    {0x3000, 16, 0, NULL}, // "　" (ideographic space)

    {0x3051, 16, 0, texture_hud_char_hiragana_ke}, // け
    {0x3059, 16, 0, texture_hud_char_hiragana_su}, // す
    {0x3069, 16, 0, texture_hud_char_hira_dakuten_do}, // ど
    {0x306E, 16, 0, texture_hud_char_hiragana_no}, // の
    {0x307F, 16, 0, texture_hud_char_hiragana_mi}, // み
    {0x308B, 16, 0, texture_hud_char_hiragana_ru}, // る
    {0x3092, 16, 0, texture_hud_char_hiragana_wo}, // を

    {0x30A1, 16, 0, texture_hud_char_katakana_small_a}, // ァ
    {0x30A2, 16, 0, texture_hud_char_katakana_a}, // ア
    {0x30A4, 16, 0, texture_hud_char_katakana_i}, // イ
    {0x30A6, 16, 0, texture_hud_char_katakana_u}, // ウ
    {0x30AA, 16, 0, texture_hud_char_katakana_o}, // オ
    {0x30AF, 16, 0, texture_hud_char_katakana_ku}, // ク
    {0x30B2, 16, 0, texture_hud_char_kana_dakuten_ge}, // ゲ
    {0x30B3, 16, 0, texture_hud_char_katakana_ko}, // コ
    {0x30B5, 16, 0, texture_hud_char_katakana_sa}, // サ
    {0x30B8, 16, 0, texture_hud_char_kana_dakuten_ji}, // ジ
    {0x30B9, 16, 0, texture_hud_char_katakana_su}, // ス
    {0x30BB, 16, 0, texture_hud_char_katakana_se}, // セ
    {0x30C8, 16, 0, texture_hud_char_katakana_to}, // ト
    {0x30C9, 16, 0, texture_hud_char_kana_dakuten_do}, // ド
    {0x30D4, 16, 0, texture_hud_char_kana_handakuten_pi}, // ピ
    {0x30D5, 16, 0, texture_hud_char_katakana_fu}, // フ
    {0x30DE, 16, 0, texture_hud_char_katakana_ma}, // マ
    {0x30E9, 16, 0, texture_hud_char_katakana_ra}, // ラ
    {0x30EA, 16, 0, texture_hud_char_katakana_ri}, // リ
    {0x30EB, 16, 0, texture_hud_char_katakana_ru}, // ル
    {0x30EC, 16, 0, texture_hud_char_katakana_re}, // レ
    {0x30F3, 16, 0, texture_hud_char_katakana_n}, // ン

    {0x30FC, 16, 0, texture_hud_char_long_vowel}, // ー
    {0xFF1F, 16, 0, texture_hud_char_question}, // ？
#endif
};

const struct Utf8CharLUTEntry main_hud_utf8_4byte_lut[] = {
};

const struct Utf8CharLUTEntry main_hud_utf8_missing_char = {0, 16, 0, texture_hud_char_question};

const struct Utf8LUT main_hud_utf8_lut = {
    main_hud_utf8_2byte_lut,
    main_hud_utf8_3byte_lut,
    main_hud_utf8_4byte_lut,
    ARRAY_COUNT(main_hud_utf8_2byte_lut),
    ARRAY_COUNT(main_hud_utf8_3byte_lut),
    ARRAY_COUNT(main_hud_utf8_4byte_lut),
    &main_hud_utf8_missing_char,
};

// Diacritics for the generic white font
const struct DiacriticLUTEntry main_font_diacritic_lut[] = {
    [TEXT_DIACRITIC_CIRCUMFLEX]           = { 0,  0, "ˆ"},
    [TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE] = { 1,  4, "ˆ"},
    [TEXT_DIACRITIC_ACUTE]                = {-1,  0, "ˊ"},
    [TEXT_DIACRITIC_ACUTE_UPPERCASE]      = { 0,  4, "ˊ"},
    [TEXT_DIACRITIC_GRAVE]                = {-1,  0, "ˋ"},
    [TEXT_DIACRITIC_GRAVE_UPPERCASE]      = { 0,  4, "ˋ"},
    [TEXT_DIACRITIC_TILDE]                = {-1,  0, "˜"},
    [TEXT_DIACRITIC_TILDE_UPPERCASE]      = { 1,  4, "˜"},
    [TEXT_DIACRITIC_UMLAUT]               = { 0,  0, "¨"},
    [TEXT_DIACRITIC_UMLAUT_UPPERCASE]     = { 1,  4, "¨"},
    [TEXT_DIACRITIC_CEDILLA]              = { 0,  0, "¸"},
#if JAPANESE_CHARACTERS
    [TEXT_DIACRITIC_DAKUTEN]              = { 4,  6, "゛"},
    [TEXT_DIACRITIC_HANDAKUTEN]           = { 7,  6, "゜"},
#endif
};

// If you build JP or SH without multilanguage, textures for these versions are used instead
#if !defined(MULTILANG)
#if defined(VERSION_JP) || defined(VERSION_SH)
#define EXCLUSIVE_TEXTURE_FONT 1
#else
#define EXCLUSIVE_TEXTURE_FONT 0
#endif
#endif

#if EXCLUSIVE_TEXTURE_FONT == 1
// ASCII lookup table for the generic white font
const struct AsciiCharLUTEntry main_font_lut[] = {
    {NULL, 5}, // 32 " "
    {texture_font_char_jp_exclamation, 8}, // 33 "!"
    {texture_font_char_us_double_quote_open, 6}, // 34 "\""
    {NULL, 0}, // 35 "#" (Unimplemented)
    {NULL, 0}, // 36 "$" (Unimplemented)
    {texture_font_char_jp_percent, 10}, // 37 "%"
    {texture_font_char_us_ampersand, 8}, // 38 "&"
    {texture_font_char_us_apostrophe, 4}, // 39 "'"
    {texture_font_char_jp_open_parentheses, 10}, // 40 "("
    {texture_font_char_jp_close_parentheses, 10}, // 41 ")"
    {NULL, 0}, // 42 "*" (Unimplemented)
    {texture_font_char_plus, 7}, // 43 "+"
    {texture_font_char_jp_comma, 6}, // 44 ","
    {texture_font_char_jp_long_vowel, 10}, // 45 "-"
    {texture_font_char_jp_period, 7}, // 46 "."
    {texture_font_char_slash, 5}, // 47 "/"
    {texture_font_char_jp_0, 10}, // 48 "0"
    {texture_font_char_jp_1, 10}, // 49 "1"
    {texture_font_char_jp_2, 10}, // 50 "2"
    {texture_font_char_jp_3, 10}, // 51 "3"
    {texture_font_char_jp_4, 10}, // 52 "4"
    {texture_font_char_jp_5, 10}, // 53 "5"
    {texture_font_char_jp_6, 10}, // 54 "6"
    {texture_font_char_jp_7, 10}, // 55 "7"
    {texture_font_char_jp_8, 10}, // 56 "8"
    {texture_font_char_jp_9, 10}, // 57 "9"
    {texture_font_char_us_colon, 4}, // 58 ":"
    {NULL, 0}, // 59 ";" (Unimplemented)
    {NULL, 0}, // 60 "<" (Unimplemented)
    {NULL, 0}, // 61 "=" (Unimplemented)
    {NULL, 0}, // 62 ">" (Unimplemented)
    {texture_font_char_jp_question, 10}, // 63 "?"
    {NULL, 0}, // 64 "@" (Unimplemented, used for color codes by default)
    {texture_font_char_jp_A, 10}, // 65 "A"
    {texture_font_char_jp_B, 10}, // 66 "B"
    {texture_font_char_jp_C, 10}, // 67 "C"
    {texture_font_char_jp_D, 10}, // 68 "D"
    {texture_font_char_jp_E, 10}, // 69 "E"
    {texture_font_char_jp_F, 10}, // 70 "F"
    {texture_font_char_jp_G, 10}, // 71 "G"
    {texture_font_char_jp_H, 10}, // 72 "H"
    {texture_font_char_jp_I, 10}, // 73 "I"
    {texture_font_char_jp_J, 10}, // 74 "J"
    {texture_font_char_jp_K, 10}, // 75 "K"
    {texture_font_char_jp_L, 10}, // 76 "L"
    {texture_font_char_jp_M, 10}, // 77 "M"
    {texture_font_char_jp_N, 10}, // 78 "N"
    {texture_font_char_jp_O, 10}, // 79 "O"
    {texture_font_char_jp_P, 10}, // 80 "P"
    {texture_font_char_jp_Q, 10}, // 81 "Q"
    {texture_font_char_jp_R, 10}, // 82 "R"
    {texture_font_char_jp_S, 10}, // 83 "S"
    {texture_font_char_jp_T, 10}, // 84 "T"
    {texture_font_char_jp_U, 10}, // 85 "U"
    {texture_font_char_jp_V, 10}, // 86 "V"
    {texture_font_char_jp_W, 10}, // 87 "W"
    {texture_font_char_jp_X, 10}, // 88 "X"
    {texture_font_char_jp_Y, 10}, // 89 "Y"
    {texture_font_char_jp_Z, 10}, // 90 "Z"
    {NULL, 0}, // 91 "[" (Unimplemented)
    {texture_font_char_backslash, 6}, // 92 "\\"
    {NULL, 0}, // 93 "]" (Unimplemented)
    {NULL, 0}, // 94 "^" (Unimplemented)
    {NULL, 0}, // 95 "_" (Unimplemented)
    {NULL, 0}, // 96 "`" (Unimplemented)
    {texture_font_char_jp_a, 9}, // 97 "a"
    {texture_font_char_jp_b, 8}, // 98 "b"
    {texture_font_char_jp_c, 8}, // 99 "c"
    {texture_font_char_jp_d, 8}, // 100 "d"
    {texture_font_char_jp_e, 8}, // 101 "e"
    {texture_font_char_jp_f, 8}, // 102 "f"
    {texture_font_char_jp_g, 9}, // 103 "g"
    {texture_font_char_jp_h, 8}, // 104 "h"
    {texture_font_char_jp_i, 6}, // 105 "i"
    {texture_font_char_jp_j, 8}, // 106 "j"
    {texture_font_char_jp_k, 8}, // 107 "k"
    {texture_font_char_jp_l, 4}, // 108 "l"
    {texture_font_char_jp_m, 10}, // 109 "m"
    {texture_font_char_jp_n, 8}, // 110 "n"
    {texture_font_char_jp_o, 8}, // 111 "o"
    {texture_font_char_jp_p, 8}, // 112 "p"
    {texture_font_char_jp_q, 9}, // 113 "q"
    {texture_font_char_jp_r, 8}, // 114 "r"
    {texture_font_char_jp_s, 8}, // 115 "s"
    {texture_font_char_jp_t, 8}, // 116 "t"
    {texture_font_char_jp_u, 8}, // 117 "u"
    {texture_font_char_jp_v, 8}, // 118 "v"
    {texture_font_char_jp_w, 10}, // 119 "w"
    {texture_font_char_jp_x, 9}, // 120 "x"
    {texture_font_char_jp_y, 8}, // 121 "y"
    {texture_font_char_jp_z, 8}, // 122 "z"
    {NULL, 0}, // 123 "{" (Unimplemented)
    {NULL, 0}, // 124 "|" (Unimplemented)
    {NULL, 0}, // 125 "}" (Unimplemented)
    {texture_font_char_jp_tilde, 10}, // 126 "~"
};
#else
const struct AsciiCharLUTEntry main_font_lut[] = {
    {NULL, 5}, // 32 " "
    {texture_font_char_us_exclamation, 5}, // 33 "!"
    {texture_font_char_us_double_quote_open, 6}, // 34 "\""
    {NULL, 0}, // 35 "#" (Unimplemented)
    {NULL, 0}, // 36 "$" (Unimplemented)
    {texture_font_char_us_percent, 7}, // 37 "%"
    {texture_font_char_us_ampersand, 8}, // 38 "&"
    {texture_font_char_us_apostrophe, 4}, // 39 "'"
    {texture_font_char_us_open_parentheses, 5}, // 40 "("
    {texture_font_char_us_close_parentheses, 5}, // 41 ")"
    {NULL, 0}, // 42 "*" (Unimplemented)
    {texture_font_char_plus, 7}, // 43 "+"
    {texture_font_char_us_comma, 4}, // 44 ","
    {texture_font_char_us_hyphen, 6}, // 45 "-"
    {texture_font_char_us_period, 4}, // 46 "."
    {texture_font_char_slash, 5}, // 47 "/"
    {texture_font_char_us_0, 7}, // 48 "0"
    {texture_font_char_us_1, 7}, // 49 "1"
    {texture_font_char_us_2, 7}, // 50 "2"
    {texture_font_char_us_3, 7}, // 51 "3"
    {texture_font_char_us_4, 7}, // 52 "4"
    {texture_font_char_us_5, 7}, // 53 "5"
    {texture_font_char_us_6, 7}, // 54 "6"
    {texture_font_char_us_7, 7}, // 55 "7"
    {texture_font_char_us_8, 7}, // 56 "8"
    {texture_font_char_us_9, 7}, // 57 "9"
    {texture_font_char_us_colon, 4}, // 58 ":"
    {NULL, 0}, // 59 ";" (Unimplemented)
    {NULL, 0}, // 60 "<" (Unimplemented)
    {NULL, 0}, // 61 "=" (Unimplemented)
    {NULL, 0}, // 62 ">" (Unimplemented)
    {texture_font_char_us_question, 7}, // 63 "?"
    {NULL, 0}, // 64 "@" (Unimplemented, used for color codes by default)

    {texture_font_char_us_A, 6}, // 65 "A"
    {texture_font_char_us_B, 6}, // 66 "B"
    {texture_font_char_us_C, 6}, // 67 "C"
    {texture_font_char_us_D, 6}, // 68 "D"
    {texture_font_char_us_E, 6}, // 69 "E"
    {texture_font_char_us_F, 6}, // 70 "F"
    {texture_font_char_us_G, 6}, // 71 "G"
    {texture_font_char_us_H, 6}, // 72 "H"
    {texture_font_char_us_I, 5}, // 73 "I"
    {texture_font_char_us_J, 6}, // 74 "J"
    {texture_font_char_us_K, 6}, // 75 "K"
    {texture_font_char_us_L, 5}, // 76 "L"
    {texture_font_char_us_M, 8}, // 77 "M"
    {texture_font_char_us_N, 8}, // 78 "N"
    {texture_font_char_us_O, 6}, // 79 "O"
    {texture_font_char_us_P, 6}, // 80 "P"
    {texture_font_char_us_Q, 6}, // 81 "Q"
    {texture_font_char_us_R, 6}, // 82 "R"
    {texture_font_char_us_S, 6}, // 83 "S"
    {texture_font_char_us_T, 5}, // 84 "T"
    {texture_font_char_us_U, 6}, // 85 "U"
    {texture_font_char_us_V, 6}, // 86 "V"
    {texture_font_char_us_W, 8}, // 87 "W"
    {texture_font_char_us_X, 7}, // 88 "X"
    {texture_font_char_us_Y, 6}, // 89 "Y"
    {texture_font_char_us_Z, 6}, // 90 "Z"

    {NULL, 0}, // 91 "[" (Unimplemented)
    {texture_font_char_backslash, 6}, // 92 "\\"
    {NULL, 0}, // 93 "]" (Unimplemented)
    {NULL, 0}, // 94 "^" (Unimplemented)
    {NULL, 0}, // 95 "_" (Unimplemented)
    {NULL, 0}, // 96 "`" (Unimplemented)

    {texture_font_char_us_a, 6}, // 97 "a"
    {texture_font_char_us_b, 5}, // 98 "b"
    {texture_font_char_us_c, 5}, // 99 "c"
    {texture_font_char_us_d, 6}, // 100 "d"
    {texture_font_char_us_e, 5}, // 101 "e"
    {texture_font_char_us_f, 5}, // 102 "f"
    {texture_font_char_us_g, 6}, // 103 "g"
    {texture_font_char_us_h, 5}, // 104 "h"
    {texture_font_char_us_i, 4}, // 105 "i"
    {texture_font_char_us_j, 5}, // 106 "j"
    {texture_font_char_us_k, 5}, // 107 "k"
    {texture_font_char_us_l, 3}, // 108 "l"
    {texture_font_char_us_m, 7}, // 109 "m"
    {texture_font_char_us_n, 5}, // 110 "n"
    {texture_font_char_us_o, 5}, // 111 "o"
    {texture_font_char_us_p, 5}, // 112 "p"
    {texture_font_char_us_q, 6}, // 113 "q"
    {texture_font_char_us_r, 5}, // 114 "r"
    {texture_font_char_us_s, 5}, // 115 "s"
    {texture_font_char_us_t, 5}, // 116 "t"
    {texture_font_char_us_u, 5}, // 117 "u"
    {texture_font_char_us_v, 5}, // 118 "v"
    {texture_font_char_us_w, 7}, // 119 "w"
    {texture_font_char_us_x, 7}, // 120 "x"
    {texture_font_char_us_y, 5}, // 121 "y"
    {texture_font_char_us_z, 5}, // 122 "z"

    {NULL, 0}, // 123 "{" (Unimplemented)
    {NULL, 0}, // 124 "|" (Unimplemented)
    {NULL, 0}, // 125 "}" (Unimplemented)
    {texture_font_char_us_tilde, 8}, // 126 "~"
};
#endif

/* 
 * This struct defines the UTF-8 characters supported by the main white font!
 * There are also similar tables for colorful HUD font and the smaller white font.
 * Adding new characters to the font is very easy!
 *
 * Look up the UTF-8 codepoint for your character. If the character is U+0D9E, the codepoint is 0x0D9E.
 * Determine which table the character belongs to, depending on if it takes up 2, 3 or 4 bytes.
 * Between U+0080 and U+07FF: 2 bytes
 * Between U+0800 and U+FFFF: 3 bytes
 * Between U+10000 and U+10FFFF: 4 bytes
 *
 * Add the texture with the other textures above, and add an entry for your new character in the corresponding table.
 * The format of the entry is: {<codepoint>, <character width>, <flags>, <texture name>}.
 * (flags will likely be 0).
 * 
 * MUST NOTE: You must place your entry in EXACTLY the right spot! The table is sorted by codepoint.
 * The tables will not work if they are not sorted properly.
 */

// UTF-8 lookup table for the generic white font
const struct Utf8CharLUTEntry main_font_utf8_2byte_lut[] = {
    {0x00A1, 5, 0, texture_font_char_inverted_exclamation_mark}, // ¡
    {0x00A8, 0, 0, texture_font_char_diacritic_umlaut}, // ¨
    {0x00B7, 4, 0, texture_font_char_us_interpunct}, // ·
    {0x00B8, 0, 0, texture_font_char_diacritic_cedilla}, // ¸
    {0x00BF, 7, 0, texture_font_char_inverted_question_mark}, // ¿

    {0x00C0, 6, TEXT_DIACRITIC_GRAVE_UPPERCASE, texture_font_char_us_A}, // À
    {0x00C1, 6, TEXT_DIACRITIC_ACUTE_UPPERCASE, texture_font_char_us_A}, // Á
    {0x00C2, 6, TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE, texture_font_char_us_A}, // Â
    {0x00C3, 6, TEXT_DIACRITIC_TILDE_UPPERCASE, texture_font_char_us_A}, // Ã
    {0x00C4, 6, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_font_char_us_A}, // Ä

    {0x00C7, 6, TEXT_DIACRITIC_CEDILLA, texture_font_char_us_C}, // Ç
    {0x00C8, 6, TEXT_DIACRITIC_GRAVE_UPPERCASE, texture_font_char_us_E}, // È
    {0x00C9, 6, TEXT_DIACRITIC_ACUTE_UPPERCASE, texture_font_char_us_E}, // É
    {0x00CA, 6, TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE, texture_font_char_us_E}, // Ê
    {0x00CB, 6, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_font_char_us_E}, // Ë

    {0x00CC, 5, TEXT_DIACRITIC_GRAVE_UPPERCASE, texture_font_char_us_I}, // Ì
    {0x00CD, 5, TEXT_DIACRITIC_ACUTE_UPPERCASE, texture_font_char_us_I}, // Í
    {0x00CE, 5, TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE, texture_font_char_us_I}, // Î
    {0x00CF, 5, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_font_char_us_I}, // Ï

    {0x00D1, 6, TEXT_DIACRITIC_TILDE_UPPERCASE, texture_font_char_us_N}, // Ñ
    {0x00D2, 6, TEXT_DIACRITIC_GRAVE_UPPERCASE, texture_font_char_us_O}, // Ò
    {0x00D3, 6, TEXT_DIACRITIC_ACUTE_UPPERCASE, texture_font_char_us_O}, // Ó
    {0x00D4, 6, TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE, texture_font_char_us_O}, // Ô
    {0x00D5, 6, TEXT_DIACRITIC_TILDE_UPPERCASE, texture_font_char_us_O}, // Õ
    {0x00D6, 6, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_font_char_us_O}, // Ö

    {0x00D7, 6, 0, texture_font_char_us_multiply}, // ×

    {0x00D9, 6, TEXT_DIACRITIC_GRAVE_UPPERCASE, texture_font_char_us_U}, // Ù
    {0x00DA, 6, TEXT_DIACRITIC_ACUTE_UPPERCASE, texture_font_char_us_U}, // Ú
    {0x00DB, 6, TEXT_DIACRITIC_CIRCUMFLEX_UPPERCASE, texture_font_char_us_U}, // Û
    {0x00DC, 6, TEXT_DIACRITIC_UMLAUT_UPPERCASE, texture_font_char_us_U}, // Ü

    {0x00DF, 6, 0, texture_font_char_eszett}, // ß

    {0x00E0, 6, TEXT_DIACRITIC_GRAVE, texture_font_char_us_a}, // à
    {0x00E1, 6, TEXT_DIACRITIC_ACUTE, texture_font_char_us_a}, // á
    {0x00E2, 6, TEXT_DIACRITIC_CIRCUMFLEX, texture_font_char_us_a}, // â
    {0x00E3, 6, TEXT_DIACRITIC_TILDE, texture_font_char_us_a}, // ã
    {0x00E4, 6, TEXT_DIACRITIC_UMLAUT, texture_font_char_us_a}, // ä

    {0x00E7, 5, TEXT_DIACRITIC_CEDILLA, texture_font_char_us_c}, // ç
    {0x00E8, 5, TEXT_DIACRITIC_GRAVE, texture_font_char_us_e}, // è
    {0x00E9, 5, TEXT_DIACRITIC_ACUTE, texture_font_char_us_e}, // é
    {0x00EA, 5, TEXT_DIACRITIC_CIRCUMFLEX, texture_font_char_us_e}, // ê
    {0x00EB, 5, TEXT_DIACRITIC_UMLAUT, texture_font_char_us_e}, // ë

    {0x00EC, 4, TEXT_DIACRITIC_GRAVE, texture_font_char_us_i_no_dot}, // ì
    {0x00ED, 4, TEXT_DIACRITIC_ACUTE, texture_font_char_us_i_no_dot}, // í
    {0x00EE, 4, TEXT_DIACRITIC_CIRCUMFLEX, texture_font_char_us_i_no_dot}, // î
    {0x00EF, 4, TEXT_DIACRITIC_UMLAUT, texture_font_char_us_i_no_dot}, // ï

    {0x00F1, 5, TEXT_DIACRITIC_TILDE, texture_font_char_us_n}, // ñ
    {0x00F2, 5, TEXT_DIACRITIC_GRAVE, texture_font_char_us_o}, // ò
    {0x00F3, 5, TEXT_DIACRITIC_ACUTE, texture_font_char_us_o}, // ó
    {0x00F4, 5, TEXT_DIACRITIC_CIRCUMFLEX, texture_font_char_us_o}, // ô
    {0x00F5, 5, TEXT_DIACRITIC_TILDE, texture_font_char_us_o}, // õ
    {0x00F6, 5, TEXT_DIACRITIC_UMLAUT, texture_font_char_us_o}, // ö

    {0x00F9, 5, TEXT_DIACRITIC_GRAVE, texture_font_char_us_u}, // ù
    {0x00FA, 5, TEXT_DIACRITIC_ACUTE, texture_font_char_us_u}, // ú
    {0x00FB, 5, TEXT_DIACRITIC_CIRCUMFLEX, texture_font_char_us_u}, // û
    {0x00FC, 5, TEXT_DIACRITIC_UMLAUT, texture_font_char_us_u}, // ü

    {0x02C6, 0, 0, texture_font_char_diacritic_circumflex}, // ˆ
    {0x02CA, 0, 0, texture_font_char_diacritic_acute}, // ˊ
    {0x02CB, 0, 0, texture_font_char_diacritic_grave}, // ˋ
    {0x02DC, 0, 0, texture_font_char_diacritic_tilde}, // ˜
};

const struct Utf8CharLUTEntry main_font_utf8_3byte_lut[] = {
    {0x201C, 6, 0, texture_font_char_us_double_quote_open}, // “
    {0x201D, 6, 0, texture_font_char_us_double_quote_close}, // ”
    {0x201E, 6, 0, texture_font_char_us_double_low_quote}, // „
    {0x2194, 9, 0, texture_font_char_us_left_right_arrow}, // ↔
    
    {0x24B6, 7, 0, texture_font_char_us_button_A}, // Ⓐ
    {0x24B7, 7, 0, texture_font_char_us_button_B}, // Ⓑ
    {0x24B8, 6, 0, texture_font_char_us_button_C}, // Ⓒ
    {0x24C7, 7, 0, texture_font_char_us_button_R}, // Ⓡ
    {0x24CF, 7, 0, texture_font_char_us_button_Z}, // Ⓩ

    {0x25B2, 8, 0, texture_font_char_us_button_C_up}, // ▲
    {0x25B6, 8, 0, texture_font_char_us_button_C_right}, // ▶
    {0x25BC, 8, 0, texture_font_char_us_button_C_down}, // ▼
    {0x25C0, 8, 0, texture_font_char_us_button_C_left}, // ◀

    {0x2605, 10, 0, texture_font_char_us_star_filled}, // ★
    {0x2606, 10, 0, texture_font_char_us_star_hollow}, // ☆
    {0x272A, 8, 0, texture_font_char_us_coin}, // ✪

#if JAPANESE_CHARACTERS
    {0x3000, 10, 0, NULL}, // "　" (ideographic space)
    {0x3001, 10, TEXT_FLAG_PACKED, texture_font_char_jp_comma}, // 、
    {0x3002, 10, TEXT_FLAG_PACKED, texture_font_char_jp_period}, // 。
    {0x300E, 10, TEXT_FLAG_PACKED, texture_font_char_jp_double_quotation_open}, // 『
    {0x300F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_double_quotation_close}, // 』

    {0x3041, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_a}, // ぁ
    {0x3042, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_a}, // あ
    {0x3043, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_i}, // ぃ
    {0x3044, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_i}, // い
    {0x3045, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_u}, // ぅ
    {0x3046, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_u}, // う
    {0x3047, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_e}, // ぇ
    {0x3048, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_e}, // え
    {0x3049, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_o}, // ぉ
    {0x304A, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_o}, // お
    {0x304B, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ka}, // か
    {0x304C, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ka}, // が
    {0x304D, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ki}, // き
    {0x304E, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ki}, // ぎ
    {0x304F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ku}, // く
    {0x3050, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ku}, // ぐ
    {0x3051, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ke}, // け
    {0x3052, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ke}, // げ
    {0x3053, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ko}, // こ
    {0x3054, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ko}, // ご
    {0x3055, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_sa}, // さ
    {0x3056, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_sa}, // ざ
    {0x3057, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_shi}, // し
    {0x3058, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_shi}, // じ
    {0x3059, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_su}, // す
    {0x305A, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_su}, // ず
    {0x305B, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_se}, // せ
    {0x305C, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_se}, // ぜ
    {0x305D, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_so}, // そ
    {0x305E, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_so}, // ぞ
    {0x305F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ta}, // た
    {0x3060, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ta}, // だ
    {0x3061, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_chi}, // ち
    {0x3062, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_chi}, // ぢ
    {0x3063, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_tsu}, // っ
    {0x3064, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_tsu}, // つ
    {0x3065, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_tsu}, // づ
    {0x3066, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_te}, // て
    {0x3067, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_te}, // で
    {0x3068, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_to}, // と
    {0x3069, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_to}, // ど
    {0x306A, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_na}, // な
    {0x306B, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ni}, // に
    {0x306C, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_nu}, // ぬ
    {0x306D, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ne}, // ね
    {0x306E, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_no}, // の
    {0x306F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ha}, // は
    {0x3070, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ha}, // ば
    {0x3071, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_hiragana_ha}, // ぱ
    {0x3072, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_hi}, // ひ
    {0x3073, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_hi}, // び
    {0x3074, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_hiragana_hi}, // ぴ
    {0x3075, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_fu}, // ふ
    {0x3076, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_fu}, // ぶ
    {0x3077, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_hiragana_fu}, // ぷ
    {0x3078, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_he}, // へ
    {0x3079, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_he}, // べ
    {0x307A, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_hiragana_he}, // ぺ
    {0x307B, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ho}, // ほ
    {0x307C, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_hiragana_ho}, // ぼ
    {0x307D, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_hiragana_ho}, // ぽ
    {0x307E, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ma}, // ま
    {0x307F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_mi}, // み
    {0x3080, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_mu}, // む
    {0x3081, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_me}, // め
    {0x3082, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_mo}, // も
    {0x3083, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_ya}, // ゃ
    {0x3084, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ya}, // や
    {0x3085, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_yu}, // ゅ
    {0x3086, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_yu}, // ゆ
    {0x3087, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_small_yo}, // ょ
    {0x3088, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_yo}, // よ
    {0x3089, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ra}, // ら
    {0x308A, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ri}, // り
    {0x308B, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ru}, // る
    {0x308C, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_re}, // れ
    {0x308D, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_ro}, // ろ
    {0x308F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_wa}, // わ
    {0x3092, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_wo}, // を
    {0x3093, 10, TEXT_FLAG_PACKED, texture_font_char_jp_hiragana_n}, // ん

    {0x309B, 0, TEXT_FLAG_PACKED, texture_font_char_jp_dakuten}, // ゛
    {0x309C, 0, TEXT_FLAG_PACKED, texture_font_char_jp_period}, // ゜

    {0x30A1, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_a}, // ァ
    {0x30A2, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_a}, // ア
    {0x30A3, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_i}, // ィ
    {0x30A4, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_i}, // イ
    {0x30A5, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_u}, // ゥ
    {0x30A6, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_u}, // ウ
    {0x30A7, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_e}, // ェ
    {0x30A8, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_e}, // エ
    {0x30A9, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_o}, // ォ
    {0x30AA, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_o}, // オ
    {0x30AB, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ka}, // カ
    {0x30AC, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ka}, // ガ
    {0x30AD, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ki}, // キ
    {0x30AE, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ki}, // ギ
    {0x30AF, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ku}, // ク
    {0x30B0, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ku}, // グ
    {0x30B1, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ke}, // ケ
    {0x30B2, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ke}, // ゲ
    {0x30B3, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ko}, // コ
    {0x30B4, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ko}, // ゴ
    {0x30B5, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_sa}, // サ
    {0x30B6, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_sa}, // ザ
    {0x30B7, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_shi}, // シ
    {0x30B8, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_shi}, // ジ
    {0x30B9, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_su}, // ス
    {0x30BA, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_su}, // ズ
    {0x30BB, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_se}, // セ
    {0x30BC, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_se}, // ゼ
    {0x30BD, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_so}, // ソ
    {0x30BE, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_so}, // ゾ
    {0x30BF, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ta}, // タ
    {0x30C0, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ta}, // ダ
    {0x30C1, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_chi}, // チ
    {0x30C2, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_chi}, // ヂ
    {0x30C3, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_tsu}, // ッ
    {0x30C4, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_tsu}, // ツ
    {0x30C5, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_tsu}, // ヅ
    {0x30C6, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_te}, // テ
    {0x30C7, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_te}, // デ
    {0x30C8, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_to}, // ト
    {0x30C9, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_to}, // ド
    {0x30CA, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_na}, // ナ
    {0x30CB, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ni}, // ニ
    {0x30CC, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_nu}, // ヌ
    {0x30CD, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ne}, // ネ
    {0x30CE, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_no}, // ノ
    {0x30CF, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ha}, // ハ
    {0x30D0, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ha}, // バ
    {0x30D1, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_katakana_ha}, // パ
    {0x30D2, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_hi}, // ヒ
    {0x30D3, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_hi}, // ビ
    {0x30D4, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_katakana_hi}, // ピ
    {0x30D5, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_fu}, // フ
    {0x30D6, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_fu}, // ブ
    {0x30D7, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_katakana_fu}, // プ
    {0x30D8, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_he}, // ヘ
    {0x30D9, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_he}, // ベ
    {0x30DA, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_katakana_he}, // ペ
    {0x30DB, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ho}, // ホ
    {0x30DC, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_DAKUTEN, texture_font_char_jp_katakana_ho}, // ボ
    {0x30DD, 10, TEXT_FLAG_PACKED | TEXT_DIACRITIC_HANDAKUTEN, texture_font_char_jp_katakana_ho}, // ポ
    {0x30DE, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ma}, // マ
    {0x30DF, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_mi}, // ミ
    {0x30E0, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_mu}, // ム
    {0x30E1, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_me}, // メ
    {0x30E2, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_mo}, // モ
    {0x30E3, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_ya}, // ャ
    {0x30E4, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ya}, // ヤ
    {0x30E5, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_yu}, // ュ
    {0x30E6, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_yu}, // ユ
    {0x30E7, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_small_yo}, // ョ
    {0x30E8, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_yo}, // ヨ
    {0x30E9, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ra}, // ラ
    {0x30EA, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ri}, // リ
    {0x30EB, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ru}, // ル
    {0x30EC, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_re}, // レ
    {0x30ED, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_ro}, // ロ
    {0x30EF, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_wa}, // ワ
    {0x30F3, 10, TEXT_FLAG_PACKED, texture_font_char_jp_katakana_n}, // ン
    {0x30FB, 10, TEXT_FLAG_PACKED, texture_font_char_jp_interpunct}, // ・
    {0x30FC, 10, TEXT_FLAG_PACKED, texture_font_char_jp_long_vowel}, // ー

    {0xFF01, 10, TEXT_FLAG_PACKED, texture_font_char_jp_exclamation}, // ！
    {0xFF05, 10, TEXT_FLAG_PACKED, texture_font_char_jp_percent}, // ％
    {0xFF08, 10, TEXT_FLAG_PACKED, texture_font_char_jp_open_parentheses}, // （
    {0xFF09, 10, TEXT_FLAG_PACKED, texture_font_char_jp_close_parentheses}, // ）
    {0xFF10, 10, TEXT_FLAG_PACKED, texture_font_char_jp_0}, // ０
    {0xFF11, 10, TEXT_FLAG_PACKED, texture_font_char_jp_1}, // １
    {0xFF12, 10, TEXT_FLAG_PACKED, texture_font_char_jp_2}, // ２
    {0xFF13, 10, TEXT_FLAG_PACKED, texture_font_char_jp_3}, // ３
    {0xFF14, 10, TEXT_FLAG_PACKED, texture_font_char_jp_4}, // ４
    {0xFF15, 10, TEXT_FLAG_PACKED, texture_font_char_jp_5}, // ５
    {0xFF16, 10, TEXT_FLAG_PACKED, texture_font_char_jp_6}, // ６
    {0xFF17, 10, TEXT_FLAG_PACKED, texture_font_char_jp_7}, // ７
    {0xFF18, 10, TEXT_FLAG_PACKED, texture_font_char_jp_8}, // ８
    {0xFF19, 10, TEXT_FLAG_PACKED, texture_font_char_jp_9}, // ９
    {0xFF1F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_question}, // ？
    {0xFF21, 10, TEXT_FLAG_PACKED, texture_font_char_jp_A}, // Ａ
    {0xFF22, 10, TEXT_FLAG_PACKED, texture_font_char_jp_B}, // Ｂ
    {0xFF23, 10, TEXT_FLAG_PACKED, texture_font_char_jp_C}, // Ｃ
    {0xFF24, 10, TEXT_FLAG_PACKED, texture_font_char_jp_D}, // Ｄ
    {0xFF25, 10, TEXT_FLAG_PACKED, texture_font_char_jp_E}, // Ｅ
    {0xFF26, 10, TEXT_FLAG_PACKED, texture_font_char_jp_F}, // Ｆ
    {0xFF27, 10, TEXT_FLAG_PACKED, texture_font_char_jp_G}, // Ｇ
    {0xFF28, 10, TEXT_FLAG_PACKED, texture_font_char_jp_H}, // Ｈ
    {0xFF29, 10, TEXT_FLAG_PACKED, texture_font_char_jp_I}, // Ｉ
    {0xFF2A, 10, TEXT_FLAG_PACKED, texture_font_char_jp_J}, // Ｊ
    {0xFF2B, 10, TEXT_FLAG_PACKED, texture_font_char_jp_K}, // Ｋ
    {0xFF2C, 10, TEXT_FLAG_PACKED, texture_font_char_jp_L}, // Ｌ
    {0xFF2D, 10, TEXT_FLAG_PACKED, texture_font_char_jp_M}, // Ｍ
    {0xFF2E, 10, TEXT_FLAG_PACKED, texture_font_char_jp_N}, // Ｎ
    {0xFF2F, 10, TEXT_FLAG_PACKED, texture_font_char_jp_O}, // Ｏ
    {0xFF30, 10, TEXT_FLAG_PACKED, texture_font_char_jp_P}, // Ｐ
    {0xFF31, 10, TEXT_FLAG_PACKED, texture_font_char_jp_Q}, // Ｑ
    {0xFF32, 10, TEXT_FLAG_PACKED, texture_font_char_jp_R}, // Ｒ
    {0xFF33, 10, TEXT_FLAG_PACKED, texture_font_char_jp_S}, // Ｓ
    {0xFF34, 10, TEXT_FLAG_PACKED, texture_font_char_jp_T}, // Ｔ
    {0xFF35, 10, TEXT_FLAG_PACKED, texture_font_char_jp_U}, // Ｕ
    {0xFF36, 10, TEXT_FLAG_PACKED, texture_font_char_jp_V}, // Ｖ
    {0xFF37, 10, TEXT_FLAG_PACKED, texture_font_char_jp_W}, // Ｗ
    {0xFF38, 10, TEXT_FLAG_PACKED, texture_font_char_jp_X}, // Ｘ
    {0xFF39, 10, TEXT_FLAG_PACKED, texture_font_char_jp_Y}, // Ｙ
    {0xFF3A, 10, TEXT_FLAG_PACKED, texture_font_char_jp_Z}, // Ｚ

    {0xFF58, 10, TEXT_FLAG_PACKED, texture_font_char_jp_multiply}, // ｘ
    {0xFF5E, 10, TEXT_FLAG_PACKED, texture_font_char_jp_tilde}, // ～
#endif
};

const struct Utf8CharLUTEntry main_font_utf8_4byte_lut[] = {

};

const struct Utf8CharLUTEntry main_font_utf8_missing_char = {0, 9, 0, texture_font_missing_character};

const struct Utf8LUT main_font_utf8_lut = {
    main_font_utf8_2byte_lut,
    main_font_utf8_3byte_lut,
    main_font_utf8_4byte_lut,
    ARRAY_COUNT(main_font_utf8_2byte_lut),
    ARRAY_COUNT(main_font_utf8_3byte_lut),
    ARRAY_COUNT(main_font_utf8_4byte_lut),
    &main_font_utf8_missing_char,
};

#if !CREDITS_TEXT_STRING_FONT
// ASCII lookup table for the green credits font
const struct AsciiCharLUTEntry main_credits_font_lut[] = {
    {NULL, 4}, // 32 " "
    {NULL, 0}, // 33 "!" (Unimplemented)
    {NULL, 0}, // 34 "\"" (Unimplemented)
    {NULL, 0}, // 35 "#" (Unimplemented)
    {NULL, 0}, // 36 "$" (Unimplemented)
    {NULL, 0}, // 37 "%" (Unimplemented)
    {NULL, 0}, // 38 "&" (Unimplemented)
    {NULL, 0}, // 39 "'" (Unimplemented)
    {NULL, 0}, // 40 "(" (Unimplemented)
    {NULL, 0}, // 41 ")" (Unimplemented)
    {NULL, 0}, // 42 "*" (Unimplemented)
    {NULL, 0}, // 43 "+" (Unimplemented)
    {NULL, 0}, // 44 "," (Unimplemented)
    {NULL, 0}, // 45 "-" (Unimplemented)
    {texture_credits_char_period, 7}, // 46 "."
    {NULL, 0}, // 47 "/" (Unimplemented)
    {NULL, 0}, // 48 "0" (Unimplemented)
    {NULL, 0}, // 49 "1" (Unimplemented)
    {NULL, 0}, // 50 "2" (Unimplemented)
    {texture_credits_char_3, 7}, // 51 "3"
    {texture_credits_char_4, 7}, // 52 "4"
    {NULL, 0}, // 53 "5" (Unimplemented)
    {texture_credits_char_6, 7}, // 54 "6"
    {NULL, 0}, // 55 "7" (Unimplemented)
    {NULL, 0}, // 56 "8" (Unimplemented)
    {NULL, 0}, // 57 "9" (Unimplemented)
    {NULL, 0}, // 58 ":" (Unimplemented)
    {NULL, 0}, // 59 ";" (Unimplemented)
    {NULL, 0}, // 60 "<" (Unimplemented)
    {NULL, 0}, // 61 "=" (Unimplemented)
    {NULL, 0}, // 62 ">" (Unimplemented)
    {NULL, 0}, // 63 "?" (Unimplemented)
    {NULL, 0}, // 64 "@" (Unimplemented)
    {texture_credits_char_A, 7}, // 65 "A"
    {texture_credits_char_B, 7}, // 66 "B"
    {texture_credits_char_C, 7}, // 67 "C"
    {texture_credits_char_D, 7}, // 68 "D"
    {texture_credits_char_E, 7}, // 69 "E"
    {texture_credits_char_F, 7}, // 70 "F"
    {texture_credits_char_G, 7}, // 71 "G"
    {texture_credits_char_H, 7}, // 72 "H"
    {texture_credits_char_I, 7}, // 73 "I"
    {texture_credits_char_J, 7}, // 74 "J"
    {texture_credits_char_K, 7}, // 75 "K"
    {texture_credits_char_L, 7}, // 76 "L"
    {texture_credits_char_M, 7}, // 77 "M"
    {texture_credits_char_N, 7}, // 78 "N"
    {texture_credits_char_O, 7}, // 79 "O"
    {texture_credits_char_P, 7}, // 80 "P"
    {texture_credits_char_Q, 7}, // 81 "Q"
    {texture_credits_char_R, 7}, // 82 "R"
    {texture_credits_char_S, 7}, // 83 "S"
    {texture_credits_char_T, 7}, // 84 "T"
    {texture_credits_char_U, 7}, // 85 "U"
    {texture_credits_char_V, 7}, // 86 "V"
    {texture_credits_char_W, 7}, // 87 "W"
    {texture_credits_char_X, 7}, // 88 "X"
    {texture_credits_char_Y, 7}, // 89 "Y"
    {texture_credits_char_Z, 7}, // 90 "Z"
    {NULL, 0}, // 91 "[" (Unimplemented)
    {NULL, 0}, // 92 "\" (Unimplemented)
    {NULL, 0}, // 93 "]" (Unimplemented)
    {NULL, 0}, // 94 "^" (Unimplemented)
    {NULL, 0}, // 95 "_" (Unimplemented)
    {NULL, 0}, // 96 "`" (Unimplemented)
    {texture_credits_char_A, 7}, // 97 "a"
    {texture_credits_char_B, 7}, // 98 "b"
    {texture_credits_char_C, 7}, // 99 "c"
    {texture_credits_char_D, 7}, // 100 "d"
    {texture_credits_char_E, 7}, // 101 "e"
    {texture_credits_char_F, 7}, // 102 "f"
    {texture_credits_char_G, 7}, // 103 "g"
    {texture_credits_char_H, 7}, // 104 "h"
    {texture_credits_char_I, 7}, // 105 "i"
    {texture_credits_char_J, 7}, // 106 "j"
    {texture_credits_char_K, 7}, // 107 "k"
    {texture_credits_char_L, 7}, // 108 "l"
    {texture_credits_char_M, 7}, // 109 "m"
    {texture_credits_char_N, 7}, // 110 "n"
    {texture_credits_char_O, 7}, // 111 "o"
    {texture_credits_char_P, 7}, // 112 "p"
    {texture_credits_char_Q, 7}, // 113 "q"
    {texture_credits_char_R, 7}, // 114 "r"
    {texture_credits_char_S, 7}, // 115 "s"
    {texture_credits_char_T, 7}, // 116 "t"
    {texture_credits_char_U, 7}, // 117 "u"
    {texture_credits_char_V, 7}, // 118 "v"
    {texture_credits_char_W, 7}, // 119 "w"
    {texture_credits_char_X, 7}, // 120 "x"
    {texture_credits_char_Y, 7}, // 121 "y"
    {texture_credits_char_Z, 7}, // 122 "z"
    {NULL, 0}, // 123 "{" (Unimplemented)
    {NULL, 0}, // 124 "|" (Unimplemented)
    {NULL, 0}, // 125 "}" (Unimplemented)
    {NULL, 0}, // 126 "~" (Unimplemented)
};
#endif

// HUD camera table 0x020087CC-0x020087E3
const Texture *const main_hud_camera_lut[] = {
    texture_hud_char_camera, texture_hud_char_mario_head, texture_hud_char_lakitu, texture_hud_char_no_camera,
    texture_hud_char_arrow_up, texture_hud_char_arrow_down,
};

// If not using multilang, include the text data here in segment 0x02.
// Otherwise, it will be placed into segment 0x19.
#ifndef MULTILANG
#include "sounds.h"
#include "seq_ids.h"

#define COURSE_NAME_TABLE seg2_course_name_table
#define ACT_NAME_TABLE seg2_act_name_table
#define DIALOG_TABLE seg2_dialog_table

#if defined(VERSION_JP) || defined(VERSION_SH)
#define DIALOG_FILE "jp/dialogs.h"
#define COURSE_FILE "jp/courses.h"
#else
#define DIALOG_FILE "us/dialogs.h"
#define COURSE_FILE "us/courses.h"
#endif
#include "text/define_text.inc.c"
#undef DIALOG_FILE
#undef COURSE_FILE
#endif

// 0x0200EC60 - 0x0200EC98
const Gfx dl_hud_img_begin[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(255, 255, 255, 255),
    // ex-alo change
    // Forces HUD Filter
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

// 0x0200EC98 - 0x0200ECC8
const Gfx dl_hud_img_load_tex_block[] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0200ECC8 - 0x0200ED00
const Gfx dl_hud_img_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    // ex-alo change
    // Forces HUD Filter
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

// 0x0200ED00 - 0x0200ED38
const Gfx dl_rgba16_text_begin[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

// 0x0200ED38 - 0x0200ED68
const Gfx dl_rgba16_load_tex_block[] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0200ED68 - 0x0200EDA8
const Gfx dl_rgba16_text_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

const Gfx dl_shade_screen_begin[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 127),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

const Gfx dl_shade_screen_end[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0200EDA8 - 0x0200EDE8
static const Vtx vertex_text_bg_box[] = {
    {{{     0,    -80,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   130,    -80,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   130,      0,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0200EDE8 - 0x0200EE28
const Gfx dl_draw_text_bg_box[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPVertex(vertex_text_bg_box, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

const Gfx dl_ia_text_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x0200EE28 - 0x0200EE68
static const Vtx vertex_ia8_char[] = {
#if defined(VERSION_JP) || defined(VERSION_SH)
    {{{     0,      0,      0}, 0, {     0,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,      0,      0}, 0, {   512,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,     16,      0}, 0, {   512,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     16,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
#else
    // ex-alo change
    // Corrects IA font UV (iQue has this change by default as well)
    {{{     0,      0,      0}, 0, {     0,    256}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,      0,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,     16,      0}, 0, {   512,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     16,      0}, 0, {   512,    256}, {0xff, 0xff, 0xff, 0xff}}},
#endif
};

// 0x020073E8 - 0x02007418
const Gfx dl_ia_text_tex_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_MIRROR), 3, G_TX_NOLOD, (G_TX_WRAP | G_TX_MIRROR), 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((((16 * 8) + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1), CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_MIRROR), 3, G_TX_NOLOD, (G_TX_WRAP | G_TX_MIRROR), 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((16 - 1) << G_TEXTURE_IMAGE_FRAC), ((8 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPVertex(vertex_ia8_char, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0200EE28 - 0x0200EE68
static const Vtx vertex_ia8_char_packed[] = {
    {{{     0,      0,      0}, 0, {     0,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,      0,      0}, 0, {   512,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,     16,      0}, 0, {   512,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     16,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0200EEA8 - 0x0200EEF0
const Gfx dl_ia_text_tex_settings_packed[] = {
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON), // gross
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((8 * 16) - 1), CALC_DXT(8, G_IM_SIZ_8b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((8 - 1) << G_TEXTURE_IMAGE_FRAC), ((16 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPVertex(vertex_ia8_char_packed, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON), // gross
    gsSPEndDisplayList(),
};

// 0x0200EEF0 - 0x0200EF30
const Gfx dl_ia_text_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};


// 0x0200EF30 - 0x0200EF60
static const Vtx vertex_triangle[] = {
    {{{     0,      0,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,      8,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     16,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0200EF60 - 0x0200EFB0
const Gfx dl_draw_triangle[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPVertex(vertex_triangle, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0200EFB0 - 0x0200EFF0
static const Vtx vertex_billboard_num[] = {
    {{{   -32,    -32,      0}, 0, {     0,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    32,    -32,      0}, 0, {  1024,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    32,     32,      0}, 0, {  1024,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -32,     32,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0200EFF0 - 0x0200F038
const Gfx dl_billboard_num_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0200F038 - 0x0200F078
const Gfx dl_billboard_num_end[] = {
    gsSPVertex(vertex_billboard_num, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0200F078 - 0x0200F0A8
const Gfx dl_billboard_num_0[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F0A8 - 0x0200F0D8
const Gfx dl_billboard_num_1[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F0D8 - 0x0200F108
const Gfx dl_billboard_num_2[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F108 - 0x0200F138
const Gfx dl_billboard_num_3[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_3),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F138 - 0x0200F168
const Gfx dl_billboard_num_4[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_4),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F168 - 0x0200F198
const Gfx dl_billboard_num_5[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_5),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F198 - 0x0200F1C8
const Gfx dl_billboard_num_6[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_6),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F1C8 - 0x0200F1F8
const Gfx dl_billboard_num_7[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_7),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F1F8 - 0x0200F228
const Gfx dl_billboard_num_8[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F228 - 0x0200F258
const Gfx dl_billboard_num_9[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_9),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

ALIGNED8 static const Texture texture_shadow_quarter_circle[] = {
#include "textures/segment2/shadow_quarter_circle.ia8.inc.c"
};

ALIGNED8 static const Texture texture_shadow_quarter_square[] = {
#include "textures/segment2/shadow_quarter_square.ia8.inc.c"
};

#if PROPER_TREE_SHADOWS
ALIGNED8 static const Texture texture_shadow_spike[] = {
#include "textures/segment2/custom/shadow_spike_custom.ia8.inc.c"
};
#endif

const Texture texture_transition_star_half[] = {
#include "textures/segment2/segment2.0F458.ia8.inc.c"
};

const Texture texture_transition_circle_half[] = {
#include "textures/segment2/segment2.0FC58.ia8.inc.c"
};

const Texture texture_transition_mario[] = {
#include "textures/segment2/segment2.10458.ia8.inc.c"
};

const Texture texture_transition_bowser_half[] = {
#include "textures/segment2/segment2.11458.ia8.inc.c"
};

const Texture texture_waterbox_water[] = {
#include "textures/segment2/segment2.11C58.rgba16.inc.c"
};

const Texture texture_waterbox_jrb_water[] = {
#include "textures/segment2/segment2.12458.rgba16.inc.c"
};

const Texture texture_waterbox_unknown_water[] = {
#include "textures/segment2/segment2.12C58.rgba16.inc.c"
};

const Texture texture_waterbox_mist[] = {
#include "textures/segment2/segment2.13458.ia16.inc.c"
};

const Texture texture_waterbox_lava[] = {
#include "textures/segment2/segment2.13C58.rgba16.inc.c"
};

// Unreferenced light group
UNUSED static const Lights1 segment2_lights_unused = gdSPDefLights1(
    0x40, 0x40, 0x40,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x02014470 - 0x020144B0
static const Mtx matrix_identity = {
#ifndef GBI_FLOATS
    {{0x00010000, 0x00000000,
      0x00000001, 0x00000000},
     {0x00000000, 0x00010000,
      0x00000000, 0x00000001},
     {0x00000000, 0x00000000,
      0x00000000, 0x00000000},
     {0x00000000, 0x00000000,
      0x00000000, 0x00000000}}
#else
    {{1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}}
#endif
};


// 0x020144B0 - 0x020144F0
static const Mtx matrix_fullscreen = {
#ifndef GBI_FLOATS
    {{0x00000000, 0x00000000,
      0x00000000, 0x00000000},
     {0x00000000, 0xffff0000,
      0xffffffff, 0xffff0001},
     {((65536 * 2 / SCREEN_WIDTH) << 16) | 0, 0x00000000,
      (0 << 16) | (65536 * 2 / SCREEN_HEIGHT), 0x00000000},
     {0x00000000, 0x00000000,
      0x00000000, 0x00000000}}
#else
    {{2.0f / SCREEN_WIDTH, 0.0f, 0.0f, 0.0f},
    {0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, 0.0f},
    {0.0f, 0.0f, -1.0f, 0.0f},
    {-1.0f, -1.0f, -1.0f, 1.0f}}
#endif
};


// 0x020144F0 - 0x02014508
const Gfx dl_draw_quad_verts_0123[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014508 - 0x02014520
const Gfx dl_draw_quad_verts_4567[] = {
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

#if OPTIMIZED_SHADOWS
const Gfx dl_shadow_begin_decal[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIFADEA, G_CC_MODULATEIFADEA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

const Gfx dl_shadow_begin_non_decal[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_MODULATEIFADEA, G_CC_MODULATEIFADEA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};
#else
const Gfx dl_shadow_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};
#endif

const Gfx dl_shadow_circle[] = {
#if !OPTIMIZED_SHADOWS
    gsSPDisplayList(dl_shadow_begin),
#endif
    gsDPLoadTextureBlock(texture_shadow_quarter_circle, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

const Gfx dl_shadow_square[] = {
#if !OPTIMIZED_SHADOWS
    gsSPDisplayList(dl_shadow_begin),
#endif
    gsDPLoadTextureBlock(texture_shadow_quarter_square, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

#if PROPER_TREE_SHADOWS
const Gfx dl_shadow_spike[] = {
#if !OPTIMIZED_SHADOWS
    gsSPDisplayList(dl_shadow_begin),
#endif
    gsDPLoadTextureBlock(texture_shadow_spike, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};
#endif

#if OPTIMIZED_SHADOWS
static const Vtx vertex_shadow[] = {
    {{{    -1,      0,     -1}, 0, {  -528,   -528}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     1,      0,     -1}, 0, {   496,   -528}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    -1,      0,      1}, 0, {  -528,    496}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     1,      0,      1}, 0, {   496,    496}, {0xff, 0xff, 0xff, 0xff}}},
};

const Gfx dl_shadow_end[] = {
    gsSPVertex(vertex_shadow, 4, 0),
    gsSP2Triangles( 0,  2,  1, 0x0,  1,  2,  3, 0x0),
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
#else
// 0x020145D8 - 0x02014620
const Gfx dl_shadow_9_verts[] = {
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014620 - 0x02014638
const Gfx dl_shadow_4_verts[] = {
    gsSP2Triangles( 0,  2,  1, 0x0,  1,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014638 - 0x02014660
const Gfx dl_shadow_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
#endif

// 0x02014660 - 0x02014698
const Gfx dl_proj_mtx_fullscreen[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPMatrix(&matrix_fullscreen, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH),
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPPerspNormalize(0xFFFF),
    gsSPEndDisplayList(),
};

// 0x02014698 - 0x020146C0
const Gfx dl_screen_transition_end[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPEndDisplayList(),
};

// 0x020146C0 - 0x02014708
const Gfx dl_transition_draw_filled_region[] = {
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  3,  7,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014708 - 0x02014738
const Gfx dl_skybox_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPPerspNormalize(0xFFFF),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPEndDisplayList(),
};

// 0x02014738 - 0x02014768
const Gfx dl_skybox_tile_tex_settings[] = {
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x02014768 - 0x02014790
const Gfx dl_skybox_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014790 - 0x020147D0
const Gfx dl_waterbox_rgba16_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x020147D0 - 0x02014810
const Gfx dl_waterbox_ia16_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x02014810 - 0x02014838
const Gfx dl_waterbox_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014838 - 0x02014878
ALIGNED8 static const Texture texture_ia8_up_arrow[] = {
#include "textures/segment2/segment2.14838.ia8.inc.c"
};

// 0x02014878 - 0x020148B0
const Gfx dl_ia8_up_arrow_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_NOOP2),
    gsSPPerspNormalize(0xFFFF),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPEndDisplayList(),
};

// 0x020148B0 - 0x020148E0
// Unused, seems to be an early DL for the power meter, seeing that is loading a 64x32 texture
const Gfx dl_rgba16_unused[] = {
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x020148E0 - 0x02014938
const Gfx dl_ia8_up_arrow_load_texture_block[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 1, texture_ia8_up_arrow),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_8b_BYTES)),
    gsSPEndDisplayList(),
};

// 0x02014938 - 0x02014958
const Gfx dl_ia8_up_arrow_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014958 - 0x02014960
static const Lights1 seg2_lights_02014958 = gdSPDefLights1(
    0x50, 0x50, 0x50,
    0xff, 0xff, 0xff, 0x32, 0x32, 0x32
);

// 0x02014970 - 0x020149A8
const Gfx dl_paintings_rippling_begin[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPLight(&seg2_lights_02014958.l, 1),
    gsSPLight(&seg2_lights_02014958.a, 2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x020149A8 - 0x020149C8
const Gfx dl_paintings_rippling_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x020149C8 - 0x02014A00
const Gfx dl_paintings_env_mapped_begin[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPLight(&seg2_lights_02014958.l, 1),
    gsSPLight(&seg2_lights_02014958.a, 2),
    gsSPTexture(0x4000, 0x4000, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x02014A00 - 0x02014A30
const Gfx dl_paintings_env_mapped_end[] = {
    gsSPTexture(0x4000, 0x4000, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPGeometryModeSetFirst(G_TEXTURE_GEN, G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014A30 - 0x02014A60
const Gfx dl_paintings_draw_ripples[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 14A60: triangle mesh
// 0x02014A60
const s16 seg2_painting_triangle_mesh[] = {
    157, // numVtx
    // format:
    // 2D point (x, y), ripple (0 or 1)
    614, 583,   0, // 0
    614, 614,   0, // 1
    562, 614,   0, // 2
    562, 553,   1, // 3
    614, 522,   0, // 4
    511, 583,   1, // 5
    511, 614,   0, // 6
    307, 614,   0, // 7
    307, 583,   1, // 8
    358, 614,   0, // 9
    256, 614,   0, // 10
    256, 553,   1, // 11
    307, 522,   1, // 12
    358, 553,   1, // 13
    409, 583,   1, // 14
    460, 614,   0, // 15
    511, 522,   1, // 16
    460, 553,   1, // 17
    409, 522,   1, // 18
    562, 307,   1, // 19
    614, 338,   0, // 20
    562, 430,   1, // 21
    614, 399,   0, // 22
    562, 368,   1, // 23
    511, 338,   1, // 24
    460, 307,   1, // 25
    460, 430,   1, // 26
    511, 399,   1, // 27
    511, 460,   1, // 28
    409, 338,   1, // 29
    460, 368,   1, // 30
    358, 307,   1, // 31
    409, 460,   1, // 32
    358, 430,   1, // 33
    409, 399,   1, // 34
    358, 368,   1, // 35
    307, 338,   1, // 36
    256, 307,   1, // 37
    307, 399,   1, // 38
    256, 430,   1, // 39
    307, 460,   1, // 40
    614, 460,   0, // 41
    562, 491,   1, // 42
    460, 491,   1, // 43
    358, 491,   1, // 44
    256, 491,   1, // 45
    409, 276,   1, // 46
    511, 276,   1, // 47
    307, 276,   1, // 48
    614,  31,   0, // 49
    614,   0,   0, // 50
    562,   0,   0, // 51
    562, 123,   1, // 52
    614,  92,   0, // 53
    511,  31,   1, // 54
    562,  61,   1, // 55
    460,   0,   0, // 56
    511,   0,   0, // 57
    460, 123,   1, // 58
    511,  92,   1, // 59
    511, 153,   1, // 60
    409,  31,   1, // 61
    460,  61,   1, // 62
    358,   0,   0, // 63
    409,   0,   0, // 64
    409,  92,   1, // 65
    358, 123,   1, // 66
    409, 153,   1, // 67
    307,  31,   1, // 68
    358,  61,   1, // 69
    256,   0,   0, // 70
    307,   0,   0, // 71
    256, 123,   1, // 72
    307,  92,   1, // 73
    307, 153,   1, // 74
    614, 153,   0, // 75
    562, 246,   1, // 76
    614, 215,   0, // 77
    562, 184,   1, // 78
    460, 246,   1, // 79
    511, 215,   1, // 80
    460, 184,   1, // 81
    358, 246,   1, // 82
    409, 215,   1, // 83
    358, 184,   1, // 84
    256, 246,   1, // 85
    307, 215,   1, // 86
    205, 583,   1, // 87
      0, 614,   0, // 88
      0, 583,   0, // 89
     51, 614,   0, // 90
     51, 553,   1, // 91
    102, 583,   1, // 92
    205, 522,   1, // 93
    153, 553,   1, // 94
    153, 614,   0, // 95
    102, 522,   1, // 96
    256, 368,   1, // 97
    205, 338,   1, // 98
    153, 307,   1, // 99
    153, 430,   1, // 100
    205, 399,   1, // 101
    205, 460,   1, // 102
    153, 368,   1, // 103
    102, 338,   1, // 104
     51, 307,   1, // 105
     51, 430,   1, // 106
    102, 399,   1, // 107
    102, 460,   1, // 108
     51, 368,   1, // 109
      0, 338,   0, // 110
      0, 460,   0, // 111
    153, 491,   1, // 112
     51, 491,   1, // 113
    153, 246,   1, // 114
    102, 276,   1, // 115
    205, 276,   1, // 116
      0, 276,   0, // 117
     51, 246,   1, // 118
    205,  31,   1, // 119
    256,  61,   1, // 120
    205,   0,   0, // 121
    153,   0,   0, // 122
    205, 153,   1, // 123
    205,  92,   1, // 124
    153, 123,   1, // 125
    102,  31,   1, // 126
    153,  61,   1, // 127
    102,   0,   0, // 128
     51,   0,   0, // 129
     51, 123,   1, // 130
    102,  92,   1, // 131
    102, 153,   1, // 132
      0,  31,   0, // 133
     51,  61,   1, // 134
      0, 153,   0, // 135
    256, 184,   1, // 136
    205, 215,   1, // 137
    153, 184,   1, // 138
    102, 215,   1, // 139
     51, 184,   1, // 140
    409, 614,   0, // 141
    614, 307,   0, // 142
    614, 276,   0, // 143
    511, 307,   1, // 144
    409, 307,   1, // 145
    307, 307,   1, // 146
    205, 614,   0, // 147
      0, 522,   0, // 148
    102, 614,   0, // 149
    205, 307,   1, // 150
    102, 307,   1, // 151
      0, 399,   0, // 152
      0, 307,   0, // 153
      0, 215,   0, // 154
      0,  92,   0, // 155
      0,   0,   0, // 156
    // triangles
    264,
      8,  12,  13, // 0
      0,   1,   2, // 1
      3,   0,   2, // 2
      4,   0,   3, // 3
      5,   2,   6, // 4
      2,   5,   3, // 5
      7,   8,   9, // 6
      8,   7,  10, // 7
     11,   8,  10, // 8
     12,   8,  11, // 9
      9,   8,  13, // 10
     13,  14,   9, // 11
     14, 141,   9, // 12
      5,   6,  15, // 13
      5,  16,   3, // 14
     16,   5,  17, // 15
     17,   5,  15, // 16
     14,  15, 141, // 17
     15,  14,  17, // 18
     18,  14,  13, // 19
     14,  18,  17, // 20
     19, 142,  20, // 21
     19,  20,  23, // 22
     28,  27,  21, // 23
     21,  23,  22, // 24
     22,  41,  21, // 25
     20,  22,  23, // 26
     23,  24,  19, // 27
     21,  27,  23, // 28
     24,  23,  27, // 29
     25, 144,  24, // 30
     19,  24, 144, // 31
     24,  27,  30, // 32
     25,  24,  30, // 33
     26,  30,  27, // 34
     27,  28,  26, // 35
     36,  38,  97, // 36
     26,  34,  30, // 37
     29,  30,  34, // 38
     30,  29,  25, // 39
     25,  29, 145, // 40
     31, 145,  29, // 41
     31,  29,  35, // 42
     29,  34,  35, // 43
     32,  34,  26, // 44
     33,  35,  34, // 45
     34,  32,  33, // 46
     33,  38,  35, // 47
     35,  36,  31, // 48
     36,  35,  38, // 49
     37,  36,  97, // 50
     37, 146,  36, // 51
     31,  36, 146, // 52
     28,  16,  43, // 53
     38,  40,  39, // 54
     39,  97,  38, // 55
     40,  38,  33, // 56
     21,  41,  42, // 57
     41,   4,  42, // 58
      3,  42,   4, // 59
     42,  28,  21, // 60
     28,  42,  16, // 61
      3,  16,  42, // 62
     26,  28,  43, // 63
     17,  43,  16, // 64
     43,  32,  26, // 65
     32,  43,  18, // 66
     17,  18,  43, // 67
     33,  32,  44, // 68
     32,  18,  44, // 69
     13,  44,  18, // 70
     44,  40,  33, // 71
     13,  12,  44, // 72
     40,  44,  12, // 73
     39,  40,  45, // 74
     40,  12,  45, // 75
     48,  31, 146, // 76
     11,  45,  12, // 77
     25,  47, 144, // 78
     46,  25, 145, // 79
     47,  19, 144, // 80
     19, 143, 142, // 81
     31,  46, 145, // 82
     60,  59,  52, // 83
     49,  53,  55, // 84
     50,  49,  51, // 85
     51,  49,  55, // 86
     52,  55,  53, // 87
     53,  75,  52, // 88
     54,  55,  59, // 89
     52,  59,  55, // 90
     55,  54,  51, // 91
     54,  59,  62, // 92
     56,  54,  62, // 93
     57,  54,  56, // 94
     54,  57,  51, // 95
     58,  62,  59, // 96
     59,  60,  58, // 97
     68,  71,  63, // 98
     61,  62,  65, // 99
     58,  65,  62, // 100
     62,  61,  56, // 101
     61,  65,  69, // 102
     63,  61,  69, // 103
     64,  61,  63, // 104
     61,  64,  56, // 105
     65,  67,  66, // 106
     66,  69,  65, // 107
     67,  65,  58, // 108
     68,  69,  73, // 109
     69,  68,  63, // 110
     66,  73,  69, // 111
     68,  73, 120, // 112
     70,  68, 120, // 113
     71,  68,  70, // 114
     72, 120,  73, // 115
     73,  74,  72, // 116
     74,  73,  66, // 117
     75,  77,  78, // 118
     52,  75,  78, // 119
     76,  78,  77, // 120
     77, 143,  76, // 121
     76,  80,  78, // 122
     60,  78,  80, // 123
     78,  60,  52, // 124
     46,  83,  79, // 125
     58,  60,  81, // 126
     60,  80,  81, // 127
     79,  81,  80, // 128
     80,  47,  79, // 129
     47,  80,  76, // 130
     81,  67,  58, // 131
     67,  81,  83, // 132
     79,  83,  81, // 133
     66,  67,  84, // 134
     67,  83,  84, // 135
     82,  84,  83, // 136
     83,  46,  82, // 137
     84,  74,  66, // 138
     82,  86,  84, // 139
     74,  84,  86, // 140
     74,  86, 136, // 141
     72,  74, 136, // 142
     85, 136,  86, // 143
     86,  48,  85, // 144
     48,  86,  82, // 145
     25,  46,  79, // 146
     79,  47,  25, // 147
     82,  46,  31, // 148
     19,  47,  76, // 149
     76, 143,  19, // 150
     31,  48,  82, // 151
     37,  48, 146, // 152
     85,  48,  37, // 153
     10,  87,  11, // 154
     87,  10, 147, // 155
     92,  95, 149, // 156
     88,  89,  90, // 157
     89, 148,  91, // 158
     90,  89,  91, // 159
     91,  92,  90, // 160
     92, 149,  90, // 161
     93,  87,  94, // 162
     87,  93,  11, // 163
     94,  87,  95, // 164
     87, 147,  95, // 165
     95,  92,  94, // 166
     96,  92,  91, // 167
     92,  96,  94, // 168
     39, 101,  97, // 169
     97,  98,  37, // 170
     98,  97, 101, // 171
     99,  98, 103, // 172
     99, 150,  98, // 173
     37,  98, 150, // 174
     98, 101, 103, // 175
    100, 103, 101, // 176
    101, 102, 100, // 177
    102, 101,  39, // 178
    100, 107, 103, // 179
    103, 104,  99, // 180
    104, 103, 107, // 181
    105, 104, 109, // 182
    105, 151, 104, // 183
     99, 104, 151, // 184
    104, 107, 109, // 185
    106, 109, 107, // 186
    107, 108, 106, // 187
    108, 107, 100, // 188
    109, 110, 105, // 189
    106, 152, 109, // 190
    110, 109, 152, // 191
    105, 110, 153, // 192
    111, 152, 106, // 193
     11,  93,  45, // 194
    102,  45,  93, // 195
     45, 102,  39, // 196
    102,  93, 112, // 197
    100, 102, 112, // 198
     94, 112,  93, // 199
    112, 108, 100, // 200
    108, 112,  96, // 201
     94,  96, 112, // 202
    106, 108, 113, // 203
    108,  96, 113, // 204
     91, 113,  96, // 205
     91, 148, 113, // 206
    113, 111, 106, // 207
    111, 113, 148, // 208
    114, 116,  99, // 209
     99, 115, 114, // 210
    115,  99, 151, // 211
     99, 116, 150, // 212
     72, 124, 120, // 213
    116,  37, 150, // 214
     37, 116,  85, // 215
    117, 105, 153, // 216
    105, 115, 151, // 217
    105, 117, 118, // 218
    118, 115, 105, // 219
    119, 120, 124, // 220
    120, 119,  70, // 221
    119, 124, 127, // 222
    119, 121,  70, // 223
    121, 119, 122, // 224
    122, 119, 127, // 225
    123, 124,  72, // 226
    124, 123, 125, // 227
    125, 127, 124, // 228
    126, 127, 131, // 229
    127, 126, 122, // 230
    125, 131, 127, // 231
    126, 131, 134, // 232
    128, 126, 129, // 233
    129, 126, 134, // 234
    126, 128, 122, // 235
    136, 123,  72, // 236
    130, 134, 131, // 237
    131, 132, 130, // 238
    132, 131, 125, // 239
    133, 134, 155, // 240
    134, 133, 129, // 241
    130, 155, 134, // 242
    133, 156, 129, // 243
    135, 155, 130, // 244
    123, 136, 137, // 245
     85, 137, 136, // 246
    139, 115, 118, // 247
    123, 137, 138, // 248
    125, 123, 138, // 249
    114, 138, 137, // 250
    137, 116, 114, // 251
    116, 137,  85, // 252
    114, 139, 138, // 253
    132, 138, 139, // 254
    138, 132, 125, // 255
    132, 139, 140, // 256
    130, 132, 140, // 257
    115, 139, 114, // 258
    118, 140, 139, // 259
    135, 140, 154, // 260
    118, 154, 140, // 261
    140, 135, 130, // 262
    117, 154, 118, // 263
};

/* 0x02015444: seg2_painting_mesh_neighbor_tris
 * Lists the neighboring triangles for each vertex in the mesh.
 * Used when applying gouraud shading to the generated ripple mesh
 *
 * Format:
 *      num neighbors, neighbor0, neighbor1, ...
 * The nth entry corresponds to the nth vertex in seg2_painting_triangle_mesh
 */
const s16 seg2_painting_mesh_neighbor_tris[] = {
      3,   1,   2,   3,
      1,   1,
      4,   1,   2,   4,   5,
      6,   2,   3,   5,  14,  59,  62,
      3,   3,  58,  59,
      6,   4,   5,  13,  14,  15,  16,
      2,   4,  13,
      2,   6,   7,
      6,   0,   6,   7,   8,   9,  10,
      4,   6,  10,  11,  12,
      4,   7,   8, 154, 155,
      6,   8,   9,  77, 154, 163, 194,
      6,   0,   9,  72,  73,  75,  77,
      6,   0,  10,  11,  19,  70,  72,
      6,  11,  12,  17,  18,  19,  20,
      4,  13,  16,  17,  18,
      6,  14,  15,  53,  61,  62,  64,
      6,  15,  16,  18,  20,  64,  67,
      6,  19,  20,  66,  67,  69,  70,
      8,  21,  22,  27,  31,  80,  81, 149, 150,
      3,  21,  22,  26,
      6,  23,  24,  25,  28,  57,  60,
      3,  24,  25,  26,
      6,  22,  24,  26,  27,  28,  29,
      6,  27,  29,  30,  31,  32,  33,
      8,  30,  33,  39,  40,  78,  79, 146, 147,
      6,  34,  35,  37,  44,  63,  65,
      6,  23,  28,  29,  32,  34,  35,
      6,  23,  35,  53,  60,  61,  63,
      6,  38,  39,  40,  41,  42,  43,
      6,  32,  33,  34,  37,  38,  39,
      8,  41,  42,  48,  52,  76,  82, 148, 151,
      6,  44,  46,  65,  66,  68,  69,
      6,  45,  46,  47,  56,  68,  71,
      6,  37,  38,  43,  44,  45,  46,
      6,  42,  43,  45,  47,  48,  49,
      6,  36,  48,  49,  50,  51,  52,
      8,  50,  51, 152, 153, 170, 174, 214, 215,
      6,  36,  47,  49,  54,  55,  56,
      6,  54,  55,  74, 169, 178, 196,
      6,  54,  56,  71,  73,  74,  75,
      3,  25,  57,  58,
      6,  57,  58,  59,  60,  61,  62,
      6,  53,  63,  64,  65,  66,  67,
      6,  68,  69,  70,  71,  72,  73,
      6,  74,  75,  77, 194, 195, 196,
      6,  79,  82, 125, 137, 146, 148,
      6,  78,  80, 129, 130, 147, 149,
      6,  76, 144, 145, 151, 152, 153,
      3,  84,  85,  86,
      1,  85,
      4,  85,  86,  91,  95,
      6,  83,  87,  88,  90, 119, 124,
      3,  84,  87,  88,
      6,  89,  91,  92,  93,  94,  95,
      6,  84,  86,  87,  89,  90,  91,
      4,  93,  94, 101, 105,
      2,  94,  95,
      6,  96,  97, 100, 108, 126, 131,
      6,  83,  89,  90,  92,  96,  97,
      6,  83,  97, 123, 124, 126, 127,
      6,  99, 101, 102, 103, 104, 105,
      6,  92,  93,  96,  99, 100, 101,
      4,  98, 103, 104, 110,
      2, 104, 105,
      6,  99, 100, 102, 106, 107, 108,
      6, 106, 107, 111, 117, 134, 138,
      6, 106, 108, 131, 132, 134, 135,
      6,  98, 109, 110, 112, 113, 114,
      6, 102, 103, 107, 109, 110, 111,
      4, 113, 114, 221, 223,
      2,  98, 114,
      6, 115, 116, 142, 213, 226, 236,
      6, 109, 111, 112, 115, 116, 117,
      6, 116, 117, 138, 140, 141, 142,
      3,  88, 118, 119,
      6, 120, 121, 122, 130, 149, 150,
      3, 118, 120, 121,
      6, 118, 119, 120, 122, 123, 124,
      6, 125, 128, 129, 133, 146, 147,
      6, 122, 123, 127, 128, 129, 130,
      6, 126, 127, 128, 131, 132, 133,
      6, 136, 137, 139, 145, 148, 151,
      6, 125, 132, 133, 135, 136, 137,
      6, 134, 135, 136, 138, 139, 140,
      6, 143, 144, 153, 215, 246, 252,
      6, 139, 140, 141, 143, 144, 145,
      6, 154, 155, 162, 163, 164, 165,
      1, 157,
      3, 157, 158, 159,
      4, 157, 159, 160, 161,
      6, 158, 159, 160, 167, 205, 206,
      6, 156, 160, 161, 166, 167, 168,
      6, 162, 163, 194, 195, 197, 199,
      6, 162, 164, 166, 168, 199, 202,
      4, 156, 164, 165, 166,
      6, 167, 168, 201, 202, 204, 205,
      6,  36,  50,  55, 169, 170, 171,
      6, 170, 171, 172, 173, 174, 175,
      8, 172, 173, 180, 184, 209, 210, 211, 212,
      6, 176, 177, 179, 188, 198, 200,
      6, 169, 171, 175, 176, 177, 178,
      6, 177, 178, 195, 196, 197, 198,
      6, 172, 175, 176, 179, 180, 181,
      6, 180, 181, 182, 183, 184, 185,
      8, 182, 183, 189, 192, 216, 217, 218, 219,
      6, 186, 187, 190, 193, 203, 207,
      6, 179, 181, 185, 186, 187, 188,
      6, 187, 188, 200, 201, 203, 204,
      6, 182, 185, 186, 189, 190, 191,
      3, 189, 191, 192,
      3, 193, 207, 208,
      6, 197, 198, 199, 200, 201, 202,
      6, 203, 204, 205, 206, 207, 208,
      6, 209, 210, 250, 251, 253, 258,
      6, 210, 211, 217, 219, 247, 258,
      6, 209, 212, 214, 215, 251, 252,
      3, 216, 218, 263,
      6, 218, 219, 247, 259, 261, 263,
      6, 220, 221, 222, 223, 224, 225,
      6, 112, 113, 115, 213, 220, 221,
      2, 223, 224,
      4, 224, 225, 230, 235,
      6, 226, 227, 236, 245, 248, 249,
      6, 213, 220, 222, 226, 227, 228,
      6, 227, 228, 231, 239, 249, 255,
      6, 229, 230, 232, 233, 234, 235,
      6, 222, 225, 228, 229, 230, 231,
      2, 233, 235,
      4, 233, 234, 241, 243,
      6, 237, 238, 242, 244, 257, 262,
      6, 229, 231, 232, 237, 238, 239,
      6, 238, 239, 254, 255, 256, 257,
      3, 240, 241, 243,
      6, 232, 234, 237, 240, 241, 242,
      3, 244, 260, 262,
      6, 141, 142, 143, 236, 245, 246,
      6, 245, 246, 248, 250, 251, 252,
      6, 248, 249, 250, 253, 254, 255,
      6, 247, 253, 254, 256, 258, 259,
      6, 256, 257, 259, 260, 261, 262,
      2,  12,  17,
      2,  21,  81,
      3,  81, 121, 150,
      4,  30,  31,  78,  80,
      4,  40,  41,  79,  82,
      4,  51,  52,  76, 152,
      2, 155, 165,
      3, 158, 206, 208,
      2, 156, 161,
      4, 173, 174, 212, 214,
      4, 183, 184, 211, 217,
      3, 190, 191, 193,
      2, 192, 216,
      3, 260, 261, 263,
      3, 240, 242, 244,
      1, 243,
};
