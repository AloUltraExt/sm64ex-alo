#pragma once

#include "PR/gbi.h"

// CUSTOM OTR COMMANDS
// ALONOTE: Not used standalone
#define G_SETTIMG_OTR 0x20
#define G_DL_OTR 0x31
#define G_VTX_OTR 0x32
#define G_MARKER 0x33
#define G_BRANCH_Z_OTR 0x35
#define G_MTX_OTR 0x36

#define G_SETFB 0x21
#define G_RESETFB 0x22
#define G_SETTIMG_FB 0x23
#define G_INVALTEXCACHE 0x34
//#define G_TEXRECT_WIDE 0x37
//#define G_FILLWIDERECT 0x38

#define G_TEXRECT_WIDE G_TEXRECT
#define G_FILLWIDERECT G_FILLRECT

/* GFX Effects */

// RDP Cmd
#define G_SETGRAYSCALE 0x39
#define G_SETINTENSITY 0x40

/* Private macro to wrap other macros in do {...} while (0) */
#define _DW(macro) do {macro} while (0)

#define gSPGrayscale(pkt, state)                       \
    {                                                  \
        Gfx* _g = (Gfx*)(pkt);                         \
                                                       \
        _g->words.w0 = _SHIFTL(G_SETGRAYSCALE, 24, 8); \
        _g->words.w1 = state;                          \
    }

#define gsSPGrayscale(state) \
    { (_SHIFTL(G_SETGRAYSCALE, 24, 8)), (state) }

#define gDPSetGrayscaleColor(pkt, r, g, b, lerp) DPRGBColor(pkt, G_SETINTENSITY, r, g, b, lerp)
#define gsDPSetGrayscaleColor(r, g, b, a) sDPRGBColor(G_SETINTENSITY, r, g, b, a)
