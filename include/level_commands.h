#ifndef LEVEL_COMMANDS_H
#define LEVEL_COMMANDS_H

#include "command_macros_base.h"

#include "level_table.h"

#define OP_AND   0
#define OP_NAND  1
#define OP_EQ    2
#define OP_NEQ   3
#define OP_LT    4
#define OP_LEQ   5
#define OP_GT    6
#define OP_GEQ   7

#define OP_SET   0
#define OP_GET   1

#define VAR_CURR_SAVE_FILE_NUM  0
#define VAR_CURR_COURSE_NUM     1
#define VAR_CURR_ACT_NUM        2
#define VAR_CURR_LEVEL_NUM      3
#define VAR_CURR_AREA_INDEX     4

#define WARP_CHECKPOINT 0x80
#define WARP_NO_CHECKPOINT 0x00

#define WHIRLPOOL_COND_ALWAYS 0
#define WHIRLPOOL_COND_BOWSER2_BEATEN 2
#define WHIRLPOOL_COND_AT_LEAST_SECOND_STAR 3

// Head defines
#define REGULAR_FACE 0x0002
#define DIZZY_FACE 0x0003

// List of commands as enum for ifdefs
// Vanilla ones are left unnamed, custom ones are named
enum LevelCommandsIDList
{
    LVL_SCRIPT_CMD_00,
    LVL_SCRIPT_CMD_01,
    LVL_SCRIPT_CMD_02,
    LVL_SCRIPT_CMD_03,
    LVL_SCRIPT_CMD_04,
    LVL_SCRIPT_CMD_05,
    LVL_SCRIPT_CMD_06,
    LVL_SCRIPT_CMD_07,
    LVL_SCRIPT_CMD_08,
    LVL_SCRIPT_CMD_09,
    LVL_SCRIPT_CMD_0A,
    LVL_SCRIPT_CMD_0B,
    LVL_SCRIPT_CMD_0C,
    LVL_SCRIPT_CMD_0D,
    LVL_SCRIPT_CMD_0E,
    LVL_SCRIPT_CMD_0F,
    LVL_SCRIPT_CMD_10,
    LVL_SCRIPT_CMD_11,
    LVL_SCRIPT_CMD_12,
    LVL_SCRIPT_CMD_13,
    LVL_SCRIPT_CMD_14,
    LVL_SCRIPT_CMD_15,
    LVL_SCRIPT_CMD_16,
    LVL_SCRIPT_CMD_17,
    LVL_SCRIPT_CMD_18,
    LVL_SCRIPT_CMD_19,
    LVL_SCRIPT_CMD_1A,
    LVL_SCRIPT_CMD_1B,
    LVL_SCRIPT_CMD_1C,
    LVL_SCRIPT_CMD_1D,
    LVL_SCRIPT_CMD_1E,
    LVL_SCRIPT_CMD_1F,
    LVL_SCRIPT_CMD_20,
    LVL_SCRIPT_CMD_21,
    LVL_SCRIPT_CMD_22,
    LVL_SCRIPT_CMD_23,
    LVL_SCRIPT_CMD_24,
    LVL_SCRIPT_CMD_25,
    LVL_SCRIPT_CMD_26,
    LVL_SCRIPT_CMD_27,
    LVL_SCRIPT_CMD_28,
    LVL_SCRIPT_CMD_29,
    LVL_SCRIPT_CMD_2A,
    LVL_SCRIPT_CMD_2B,
    LVL_SCRIPT_CMD_2C,
    LVL_SCRIPT_CMD_2D,
    LVL_SCRIPT_CMD_2E,
    LVL_SCRIPT_CMD_2F,
    LVL_SCRIPT_CMD_30,
    LVL_SCRIPT_CMD_31,
    LVL_SCRIPT_CMD_32,
    LVL_SCRIPT_CMD_33,
    LVL_SCRIPT_CMD_34,
    LVL_SCRIPT_CMD_35,
    LVL_SCRIPT_CMD_36,
    LVL_SCRIPT_CMD_37,
    LVL_SCRIPT_CMD_38,
    LVL_SCRIPT_CMD_39,
    LVL_SCRIPT_CMD_3A,
    LVL_SCRIPT_CMD_3B,
    LVL_SCRIPT_CMD_3C,
#ifdef BETTERCAMERA
    LVL_SCRIPT_CMD_PUPPYVOLUME,
#endif
};

#ifdef NO_SEGMENTED_MEMORY
#define EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(LVL_SCRIPT_CMD_00, 0x10, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL), \
    CMD_PTR(entry)

#define EXIT_AND_EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(LVL_SCRIPT_CMD_01, 0x10, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL), \
    CMD_PTR(entry)
#else
#define EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(LVL_SCRIPT_CMD_00, 0x10, seg), \
    CMD_PTR(script), \
    CMD_PTR(scriptEnd), \
    CMD_PTR(entry)

#define EXIT_AND_EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(LVL_SCRIPT_CMD_01, 0x10, seg), \
    CMD_PTR(script), \
    CMD_PTR(scriptEnd), \
    CMD_PTR(entry)
#endif

#define EXIT() \
    CMD_BBH(LVL_SCRIPT_CMD_02, 0x04, 0x0000)

#define SLEEP(frames) \
    CMD_BBH(LVL_SCRIPT_CMD_03, 0x04, frames)

#define SLEEP_BEFORE_EXIT(frames) \
    CMD_BBH(LVL_SCRIPT_CMD_04, 0x04, frames)

#define JUMP(target) \
    CMD_BBH(LVL_SCRIPT_CMD_05, 0x08, 0x0000), \
    CMD_PTR(target)

#define JUMP_LINK(target) \
    CMD_BBH(LVL_SCRIPT_CMD_06, 0x08, 0x0000), \
    CMD_PTR(target)

#define RETURN() \
    CMD_BBH(LVL_SCRIPT_CMD_07, 0x04, 0x0000)

#define JUMP_LINK_PUSH_ARG(arg) \
    CMD_BBH(LVL_SCRIPT_CMD_08, 0x04, arg)

#define JUMP_N_TIMES() \
    CMD_BBH(LVL_SCRIPT_CMD_09, 0x04, 0x0000)

#define LOOP_BEGIN() \
    CMD_BBH(LVL_SCRIPT_CMD_0A, 0x04, 0x0000)

#define LOOP_UNTIL(op, arg) \
    CMD_BBBB(LVL_SCRIPT_CMD_0B, 0x08, op, 0x00), \
    CMD_W(arg)

#define JUMP_IF(op, arg, target) \
    CMD_BBBB(LVL_SCRIPT_CMD_0C, 0x0C, op, 0x00), \
    CMD_W(arg), \
    CMD_PTR(target)

#define JUMP_LINK_IF(op, arg, target) \
    CMD_BBBB(LVL_SCRIPT_CMD_0D, 0x0C, op, 0x00), \
    CMD_W(arg), \
    CMD_PTR(target)


#define SKIP_IF(op, arg) \
    CMD_BBBB(LVL_SCRIPT_CMD_0E, 0x08, op, 0) \
    CMD_W(arg)

#define SKIP() \
    CMD_BBH(LVL_SCRIPT_CMD_0F, 0x04, 0x0000)

#define SKIP_NOP() \
    CMD_BBH(LVL_SCRIPT_CMD_10, 0x04, 0x0000)

#define CALL(arg, func) \
    CMD_BBH(LVL_SCRIPT_CMD_11, 0x08, arg), \
    CMD_PTR(func)

// Calls func in a loop until it returns nonzero
#define CALL_LOOP(arg, func) \
    CMD_BBH(LVL_SCRIPT_CMD_12, 0x08, arg), \
    CMD_PTR(func)

#define SET_REG(value) \
    CMD_BBH(LVL_SCRIPT_CMD_13, 0x04, value)

#define PUSH_POOL() \
    CMD_BBH(LVL_SCRIPT_CMD_14, 0x04, 0x0000)

#define POP_POOL() \
    CMD_BBH(LVL_SCRIPT_CMD_15, 0x04, 0x0000)

#ifdef NO_SEGMENTED_MEMORY
#define FIXED_LOAD(loadAddr, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_16, 0x10, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)

#define LOAD_RAW(seg, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_17, 0x0C, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)

#define LOAD_MIO0(seg, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_18, 0x0C, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)
#else
#define FIXED_LOAD(loadAddr, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_16, 0x10, 0x0000), \
    CMD_PTR(loadAddr), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)

#define LOAD_RAW(seg, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_17, 0x0C, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)

#define LOAD_MIO0(seg, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_18, 0x0C, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)
#endif

#ifdef GODDARD_MFACE
#define LOAD_MARIO_HEAD(sethead) \
    CMD_BBH(LVL_SCRIPT_CMD_19, 0x04, sethead)
#else
#define LOAD_MARIO_HEAD(sethead) \
    CMD_BBH(LVL_SCRIPT_CMD_19, 0x04, NULL)
#endif

#ifdef NO_SEGMENTED_MEMORY
#define LOAD_MIO0_TEXTURE(seg, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_1A, 0x0C, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)
#else
#define LOAD_MIO0_TEXTURE(seg, romStart, romEnd) \
    CMD_BBH(LVL_SCRIPT_CMD_1A, 0x0C, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)
#endif

#define INIT_LEVEL() \
    CMD_BBH(LVL_SCRIPT_CMD_1B, 0x04, 0x0000)

#define CLEAR_LEVEL() \
    CMD_BBH(LVL_SCRIPT_CMD_1C, 0x04, 0x0000)

#define ALLOC_LEVEL_POOL() \
    CMD_BBH(LVL_SCRIPT_CMD_1D, 0x04, 0x0000)

#define FREE_LEVEL_POOL() \
    CMD_BBH(LVL_SCRIPT_CMD_1E, 0x04, 0x0000)

#define AREA(index, geo) \
    CMD_BBBB(LVL_SCRIPT_CMD_1F, 0x08, index, 0), \
    CMD_PTR(geo)

#define END_AREA() \
    CMD_BBH(LVL_SCRIPT_CMD_20, 0x04, 0x0000)

#define LOAD_MODEL_FROM_DL(model, dl, layer) \
    CMD_BBH(LVL_SCRIPT_CMD_21, 0x08, ((layer << 12) | model)), \
    CMD_PTR(dl)

#define LOAD_MODEL_FROM_GEO(model, geo) \
    CMD_BBH(LVL_SCRIPT_CMD_22, 0x08, model), \
    CMD_PTR(geo)

// unk8 is float, but doesn't really matter since CMD23 is unused
#define CMD23(model, unk4, unk8) \
    CMD_BBH(LVL_SCRIPT_CMD_23, 0x08, model), \
    CMD_PTR(unk4), \
    CMD_W(unk8)

#define OBJECT_WITH_ACTS(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh, acts) \
    CMD_BBBB(LVL_SCRIPT_CMD_24, 0x18, acts, model), \
    CMD_HHHHHH(posX, posY, posZ, angleX, angleY, angleZ), \
    CMD_W(behParam), \
    CMD_PTR(beh)

#define OBJECT(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh) \
    OBJECT_WITH_ACTS(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh, 0x1F)

#define MARIO(unk3, behArg, beh) \
    CMD_BBBB(LVL_SCRIPT_CMD_25, 0x0C, 0x00, unk3), \
    CMD_W(behArg), \
    CMD_PTR(beh)

#define WARP_NODE(id, destLevel, destArea, destNode, flags) \
    CMD_BBBB(LVL_SCRIPT_CMD_26, 0x08, id, destLevel), \
    CMD_BBBB(destArea, destNode, flags, 0x00)

#define PAINTING_WARP_NODE(id, destLevel, destArea, destNode, flags) \
    CMD_BBBB(LVL_SCRIPT_CMD_27, 0x08, id, destLevel), \
    CMD_BBBB(destArea, destNode, flags, 0x00)

#define INSTANT_WARP(index, destArea, displaceX, displaceY, displaceZ) \
    CMD_BBBB(LVL_SCRIPT_CMD_28, 0x0C, index, destArea), \
    CMD_HH(displaceX, displaceY), \
    CMD_HH(displaceZ, 0x0000)

#define LOAD_AREA(area) \
    CMD_BBBB(LVL_SCRIPT_CMD_29, 0x04, area, 0x00)

#define CMD2A(unk2) \
    CMD_BBBB(LVL_SCRIPT_CMD_2A, 0x04, unk2, 0x00)

#define MARIO_POS(area, yaw, posX, posY, posZ) \
    CMD_BBBB(LVL_SCRIPT_CMD_2B, 0x0C, area, 0x00), \
    CMD_HH(yaw, posX), \
    CMD_HH(posY, posZ)

// unused
#define CMD2C() \
    CMD_BBH(LVL_SCRIPT_CMD_2C, 0x04, 0x0000)

// unused
#define CMD2D() \
    CMD_BBH(LVL_SCRIPT_CMD_2D, 0x04, 0x0000)

#define TERRAIN(terrainData) \
    CMD_BBH(LVL_SCRIPT_CMD_2E, 0x08, 0x0000), \
    CMD_PTR(terrainData)

#define ROOMS(surfaceRooms) \
    CMD_BBH(LVL_SCRIPT_CMD_2F, 0x08, 0x0000), \
    CMD_PTR(surfaceRooms)

#define SHOW_DIALOG(index, dialogId) \
    CMD_BBBB(LVL_SCRIPT_CMD_30, 0x04, index, dialogId)

#define TERRAIN_TYPE(terrainType) \
    CMD_BBH(LVL_SCRIPT_CMD_31, 0x04, terrainType)

#define NOP() \
    CMD_BBH(LVL_SCRIPT_CMD_32, 0x04, 0x0000)

#define TRANSITION(transType, time, colorR, colorG, colorB) \
    CMD_BBBB(LVL_SCRIPT_CMD_33, 0x08, transType, time), \
    CMD_BBBB(colorR, colorG, colorB, 0x00)

#define BLACKOUT(active) \
    CMD_BBBB(LVL_SCRIPT_CMD_34, 0x04, active, 0x00)

#define GAMMA(enabled) \
    CMD_BBBB(LVL_SCRIPT_CMD_35, 0x04, enabled, 0x00)

#define SET_BACKGROUND_MUSIC(settingsPreset, seq) \
    CMD_BBH(LVL_SCRIPT_CMD_36, 0x08, settingsPreset), \
    CMD_HH(seq, 0x0000)

#define SET_MENU_MUSIC(seq) \
    CMD_BBH(LVL_SCRIPT_CMD_37, 0x04, seq)

#define STOP_MUSIC(fadeOutTime) \
    CMD_BBH(LVL_SCRIPT_CMD_38, 0x04, fadeOutTime)

#define MACRO_OBJECTS(objList) \
    CMD_BBH(LVL_SCRIPT_CMD_39, 0x08, 0x0000), \
    CMD_PTR(objList)

// unused
#define CMD3A(unk2, unk4, unk6, unk8, unk10) \
    CMD_BBH(LVL_SCRIPT_CMD_3A, 0x0C, unk2), \
    CMD_HH(unk6, unk8), \
    CMD_HH(unk10, 0x0000)

#define WHIRLPOOL(index, condition, posX, posY, posZ, strength) \
    CMD_BBBB(LVL_SCRIPT_CMD_3B, 0x0C, index, condition), \
    CMD_HH(posX, posY), \
    CMD_HH(posZ, strength)

#define GET_OR_SET(op, var) \
    CMD_BBBB(LVL_SCRIPT_CMD_3C, 0x04, op, var)

#endif // LEVEL_COMMANDS_H
