#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/area.h"
#include "game/level_update.h"
#include "menu/title_screen.h"

#include "levels/scripts.h"
#include "levels/menu/header.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/intro/header.h"

#if defined(TARGET_N64) && defined(N64_USE_EXTENDED_RAM)
const LevelScript level_intro_entry_error_screen[] = {
    INIT_LEVEL(),
#ifdef GODDARD_MFACE
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
#endif
    LOAD_MIO0(/*seg*/ 0x07, _intro_segment_7SegmentRomStart, _intro_segment_7SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_error_screen),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SLEEP(/*frames*/ 32767),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_error_screen),
};
#endif

const LevelScript level_intro_splash_screen[] = {
    INIT_LEVEL(),
#ifdef GODDARD_MFACE
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
#endif
    LOAD_RAW (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0(/*seg*/ 0x07, _intro_segment_7SegmentRomStart, _intro_segment_7SegmentRomEnd),
    // Load "Super Mario 64" logo
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_0002D0),
    END_AREA(),

    FREE_LEVEL_POOL(),
    // Start animation
    LOAD_AREA(/*area*/ 1),

    GET_OR_SET(/*op*/ OP_GET, /*var*/ VAR_CURR_GAME_SKIPS),
    JUMP_IF(/*op*/ OP_AND, /*arg*/ GAME_SKIP_TITLE_SCREEN, level_intro_mario_head_regular),

    SET_MENU_MUSIC(/*seq*/ SEQ_SOUND_PLAYER),
    CALL(/*arg*/ LVL_INTRO_PLAY_ITS_A_ME_MARIO, /*func*/ lvl_intro_update),
    SLEEP(/*frames*/ 75),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),
    CMD2A(/*unk2*/ 1),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_mario_head_regular),
};

const LevelScript level_intro_mario_head_regular[] = {
#ifndef GODDARD_MFACE
    JUMP(level_intro_mario_head_regular_skip),
#else
    INIT_LEVEL(),
    BLACKOUT(/*active*/ TRUE),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MARIO_HEAD(/*loadHeadID*/ REGULAR_FACE),
    LOAD_RAW         (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),

    ALLOC_LEVEL_POOL(),
    AREA(/*index*/ 1, intro_geo_mario_head_regular),
    END_AREA(),
    FREE_LEVEL_POOL(),

    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    LOAD_AREA(/*area*/ 1),

    GET_OR_SET(/*op*/ OP_GET, /*var*/ VAR_CURR_GAME_SKIPS),
    JUMP_IF(/*op*/ OP_AND, /*arg*/ GAME_SKIP_GODDARD, level_intro_mario_head_regular_skip),

    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_TITLE_SCREEN),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_STAR, /*time*/ 20, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 20),
    CALL_LOOP(/*arg*/ LVL_INTRO_REGULAR, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    JUMP(script_intro_L4),
#endif
};

const LevelScript level_intro_mario_head_dizzy[] = {
#ifndef GODDARD_MFACE
    JUMP(level_intro_mario_head_dizzy_skip),
#else
    INIT_LEVEL(),
    BLACKOUT(/*active*/ TRUE),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MARIO_HEAD(/*loadHeadID*/ DIZZY_FACE),
    LOAD_RAW         (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_mario_head_dizzy),
    END_AREA(),

    FREE_LEVEL_POOL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_GAME_OVER),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_STAR, /*time*/ 20, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 20),
    CALL_LOOP(/*arg*/ LVL_INTRO_GAME_OVER, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    JUMP(script_intro_L4),
#endif
};

const LevelScript level_intro_mario_head_regular_skip[] = {
    INIT_LEVEL(),
    PUSH_POOL(),
    CALL_LOOP(/*arg*/ LVL_INTRO_REGULAR, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _menuSegmentRomStart, _menuSegmentRomEnd, level_main_menu_entry_1),
};

const LevelScript level_intro_mario_head_dizzy_skip[] = {
    INIT_LEVEL(),
    PUSH_POOL(),
    CALL_LOOP(/*arg*/ LVL_INTRO_GAME_OVER, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_splash_screen),
};

const LevelScript level_intro_entry_4[] = {
    INIT_LEVEL(),
    LOAD_RAW         (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x07, _debug_level_select_mio0SegmentRomStart, _debug_level_select_mio0SegmentRomEnd),
#ifdef GODDARD_MFACE
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
#endif
#if ZELDA_STYLE_LEVEL_SELECT
    CALL(/*arg*/ 0, /*func*/ lvl_init_intro_level_select),
#endif
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_000414),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_TITLE_SCREEN),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CALL_LOOP(/*arg*/ LVL_INTRO_LEVEL_SELECT, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ -1, script_intro_L5),
    JUMP(script_intro_L3),
};

// These should be static, but C doesn't allow non-sized forward declarations of static arrays

const LevelScript script_intro_L1[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    SET_REG(/*value*/ 16),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _menuSegmentRomStart, _menuSegmentRomEnd, level_main_menu_entry_1),
};

const LevelScript script_intro_L2[] = {
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_4),
};

const LevelScript script_intro_L3[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x15, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript script_intro_L4[] = {
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x15, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript script_intro_L5[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_splash_screen),
};
