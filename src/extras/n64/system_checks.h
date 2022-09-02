#pragma once
#include <ultra64.h>
#include "lib/src/libultra_internal.h"
#include "PR/rcp.h"

extern u8 gIsConsole;
extern u8 gIsWiiVC;
extern u8 gCacheEmulated;
extern u8 gIsHLE;

void check_cache_emulation();

// This function must not be inlined by the compiler
f32 round_double_to_float(f64);

void n64_system_device_checks(void);

/*
 * This check forces RTZ bug on VC (Works only if you inject SM64 wad, not others).
 * If console is N64/adequate Emu round-to-nearest (RTN) rounding mode is used
 * If console is VC round-to-zero (RTZ) mode is used
 *
 * The double value 0.9999999999999999 used is 0x3FEFFFFFFFFFFFFF in binary
 * Exponent=01111111110, Mantissa=14BexZMoP1gqvSbLZSfYigjUvfcXkroScK11111111111111111
 * RTZ will output not 1.0f, RTN will output exactly 1.0f */
#define IS_WII_VC() (1.0f != round_double_to_float(0.9999999999999999))
