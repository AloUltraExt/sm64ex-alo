#ifndef INTRO_HEADER_H
#define INTRO_HEADER_H

#include "types.h"

#ifdef TARGET_N64
#include "boot/ext_mem_screen.h"
#endif

// geo
extern const GeoLayout intro_geo_0002D0[];
extern const GeoLayout intro_geo_mario_head_regular[];
extern const GeoLayout intro_geo_mario_head_dizzy[];
extern const GeoLayout intro_geo_000414[];

// leveldata
extern const Gfx intro_seg7_dl_logo[];
extern const Gfx intro_seg7_dl_copyright[];
extern const f32 intro_seg7_table_0700C790[];
extern const f32 intro_seg7_table_0700C880[];

// script
extern const LevelScript level_intro_splash_screen[];
extern const LevelScript level_intro_mario_head_regular[];
extern const LevelScript level_intro_mario_head_dizzy[];
extern const LevelScript level_intro_mario_head_regular_skip[];
extern const LevelScript level_intro_mario_head_dizzy_skip[];
extern const LevelScript level_intro_entry_4[];
extern const LevelScript script_intro_L1[];
extern const LevelScript script_intro_L2[];
extern const LevelScript script_intro_L3[];
extern const LevelScript script_intro_L4[];
extern const LevelScript script_intro_L5[];

#ifdef TARGET_N64
extern const GeoLayout intro_geo_error_screen[];
extern const LevelScript level_intro_entry_error_screen[];
#endif

#endif
