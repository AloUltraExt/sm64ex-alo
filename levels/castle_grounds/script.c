#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/castle_grounds/header.h"

static const LevelScript script_func_local_1[] = {
    WARP_NODE(/*id*/ WARP_NODE_00, /*destLevel*/ LEVEL_CASTLE,         /*destArea*/ 1, /*destNode*/ WARP_NODE_00, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ WARP_NODE_01, /*destLevel*/ LEVEL_CASTLE,         /*destArea*/ 1, /*destNode*/ WARP_NODE_01, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ WARP_NODE_02, /*destLevel*/ LEVEL_CASTLE,         /*destArea*/ 3, /*destNode*/ WARP_NODE_02, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/     0,   900, -1710, /*angle*/ 0, 180, 0, /*bhvParam*/ BPARAM2(WARP_NODE_03), /*bhv*/ bhvDeathWarp),
    WARP_NODE(/*id*/ WARP_NODE_03, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_03, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1328,   260,  4664, /*angle*/ 0, 180, 0, /*bhvParam*/ BPARAM2(WARP_NODE_04), /*bhv*/ bhvSpinAirborneCircleWarp),
    WARP_NODE(/*id*/ WARP_NODE_04, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_04, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3379,  -815, -2025, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM1(60) | BPARAM2(WARP_NODE_05), /*bhv*/ bhvWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3379,  -500, -2025, /*angle*/ 0, 180, 0, /*bhvParam*/ BPARAM2(WARP_NODE_06), /*bhv*/ bhvLaunchDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3799, -1199, -5816, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(WARP_NODE_07), /*bhv*/ bhvSwimmingWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3379,  -500, -2025, /*angle*/ 0, 180, 0, /*bhvParam*/ BPARAM2(WARP_NODE_08), /*bhv*/ bhvLaunchStarCollectWarp),
    WARP_NODE(/*id*/ WARP_NODE_05, /*destLevel*/ LEVEL_VCUTM,          /*destArea*/ 1, /*destNode*/ WARP_NODE_0A, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ WARP_NODE_06, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_06, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ WARP_NODE_07, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_07, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ WARP_NODE_08, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_08, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  5408,  4500,  3637, /*angle*/ 0, 225, 0, /*bhvParam*/ BPARAM2(WARP_NODE_0A), /*bhv*/ bhvAirborneWarp),
    WARP_NODE(/*id*/ WARP_NODE_0A, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -6901,  2376, -6509, /*angle*/ 0, 230, 0, /*bhvParam*/ BPARAM2(WARP_NODE_14), /*bhv*/ bhvAirborneWarp),
    WARP_NODE(/*id*/ WARP_NODE_14, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_14, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  4997, -1250,  2258, /*angle*/ 0, 210, 0, /*bhvParam*/ BPARAM2(WARP_NODE_1E), /*bhv*/ bhvSwimmingWarp),
    WARP_NODE(/*id*/ WARP_NODE_1E, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_1E, /*flags*/ WARP_NO_CHECKPOINT),
    RETURN(),
};

static const LevelScript script_func_local_2[] = {
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/ -5812,  100, -5937, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvWaterfallSoundLoop),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/ -7430, 1500,   873, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x00), /*bhv*/ bhvBirdsSoundLoop),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/   -80, 1500,  5004, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvBirdsSoundLoop),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/  7131, 1500, -2989, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x02), /*bhv*/ bhvBirdsSoundLoop),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/ -7430, 1500, -5937, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvAmbientSounds),
    OBJECT(/*model*/ MODEL_CASTLE_GROUNDS_VCUTM_GRILL,  /*pos*/     0,    0,     0, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvMoatGrills),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/     0,    0,     0, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvInvisibleObjectsUnderBridge),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -4878, -787, -5690, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -4996, -787, -5548, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5114, -787, -5406, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x02), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5212, -787, -5219, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x03), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5311, -787, -5033, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x04), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5419, -787, -4895, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x05), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5527, -787, -4757, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x06), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5686, -787, -4733, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x07), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_MIST,                        /*pos*/ -5845, -787, -4710, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x08), /*bhv*/ bhvWaterMist2),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/  5223, -975,  1667, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvManyBlueFishSpawner),
    OBJECT(/*model*/ MODEL_BIRDS,                       /*pos*/ -5069,  850,  3221, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(BIRD_BP_SPAWNER), /*bhv*/ bhvBird),
    OBJECT(/*model*/ MODEL_BIRDS,                       /*pos*/ -4711,  742,   433, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(BIRD_BP_SPAWNER), /*bhv*/ bhvBird),
    OBJECT(/*model*/ MODEL_BIRDS,                       /*pos*/  5774,  913, -1114, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(BIRD_BP_SPAWNER), /*bhv*/ bhvBird),
    OBJECT(/*model*/ MODEL_NONE,                        /*pos*/ -1328,  260,  4664, /*angle*/ 0, 180, 0, /*bhvParam*/ BPARAM2(0x28), /*bhv*/ bhvIntroScene),
    OBJECT(/*model*/ MODEL_CASTLE_GROUNDS_CANNON_GRILL, /*pos*/     0,    0,     0, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvHiddenAt120Stars),
    OBJECT(/*model*/ MODEL_LAKITU,                      /*pos*/    11,  803, -3015, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(CAMERA_LAKITU_BP_INTRO), /*bhv*/ bhvCameraLakitu),
    RETURN(),
};

static const LevelScript script_func_local_3[] = {
    OBJECT(/*model*/ MODEL_CASTLE_GROUNDS_FLAG, /*pos*/ -3213, 3348, -3011, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvCastleFlagWaving),
    OBJECT(/*model*/ MODEL_CASTLE_GROUNDS_FLAG, /*pos*/  3213, 3348, -3011, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvCastleFlagWaving),
    OBJECT(/*model*/ MODEL_CASTLE_GROUNDS_FLAG, /*pos*/ -3835, 3348, -6647, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvCastleFlagWaving),
    OBJECT(/*model*/ MODEL_CASTLE_GROUNDS_FLAG, /*pos*/  3835, 3348, -6647, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvCastleFlagWaving),
    RETURN(),
};

static const LevelScript script_func_local_4[] = {
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -4508,  406,  4400, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -4408,  406,  4500, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -4708,  406,  4100, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -6003,  473, -2621, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -6003,  473, -2321, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/  6543,  461,  -617, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/  6143,  461,  -617, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/  5773,  775, -5722, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/  5873,  775, -5622, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/  5473,  775, -5322, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -1504,  326,  3196, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_BUTTERFLY, /*pos*/ -1204,  326,  3296, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT(/*model*/ MODEL_YOSHI,     /*pos*/     0, 3174, -5625, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvYoshi),
    RETURN(),
};

#ifdef PORT_MOP_OBJS
static const LevelScript script_func_local_mop[] = {
    // MOP 1 Objects
    OBJECT(/*model*/ MODEL_MOP_SHELL_GREEN,     /*pos*/ -1025,  260,  5102, /*angle*/  0, 180, 0, /*bhvParam*/ 0, /*bhv*/ bhvBreakableBoxSmall),
    OBJECT(/*model*/ MODEL_MOP_SHELL_RED,       /*pos*/ -1630,  260,  5116, /*angle*/  0, 180, 0, /*bhvParam*/ 0, /*bhv*/ bhvBreakableBoxSmall),
    OBJECT(/*model*/ MODEL_MOP_NOTEBLOCK,       /*pos*/ -4070,  485,  4614, /*angle*/  0, 0, 0, /*bhvParam*/ BPARAM2(0x30), /*bhv*/ bhvNoteblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SANDBLOCK,       /*pos*/ -4822,  890,  4614, /*angle*/  0, 0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvSandblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SPRING,          /*pos*/ -1835,  534,  3527, /*angle*/ 20, 180, 0, /*bhvParam*/ BPARAM1(0xC0) | BPARAM2(0xC0), /*bhv*/ bhvSpring_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/  -671,  934, -1361, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/  -921,  934, -1361, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1171,  934, -1361, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1471,  934, -1361, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1671,  934, -1361, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1921,  934, -1361, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1921,  934, -1661, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1921,  994, -1851, /*angle*/ 30, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1921, 1114, -2061, /*angle*/ 30, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_MOP_SHRINKPLAT,      /*pos*/ -1921, 1174, -2291, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvShrink_Platform_MOP),
    OBJECT(/*model*/ MODEL_RED_FLAME,           /*pos*/ -1427,  458,  4393, /*angle*/  0, 0, 0, /*bhvParam*/ BPARAM2(0x02), /*bhv*/ bhvFlameBouncing),
    OBJECT(/*model*/ MODEL_BREAKABLE_BOX_SMALL, /*pos*/ -1223,  260,  4110, /*angle*/  0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvBreakableBoxSmall),
    // MOP 2 Objects
    OBJECT(/*model*/ MODEL_NONE,                    /*pos*/  3634,  545, -5986, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x8F) | BPARAM2(0x00), /*bhv*/ bhvEmitter_MOP),
    OBJECT(/*model*/ MODEL_NONE,                    /*pos*/  3934,  545, -5986, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x80) | BPARAM2(0xF0), /*bhv*/ bhvEmitter_MOP),
    OBJECT(/*model*/ MODEL_NONE,                    /*pos*/  3634,  545, -5686, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x80) | BPARAM2(0x0F), /*bhv*/ bhvEmitter_MOP),
    OBJECT(/*model*/ MODEL_NONE,                    /*pos*/  3934,  545, -5686, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x8F) | BPARAM2(0xF0), /*bhv*/ bhvEmitter_MOP),
    OBJECT(/*model*/ MODEL_NONE,                    /*pos*/  3850,  545, -5850, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x05) | BPARAM2(0x09), /*bhv*/ bhvJukebox_MOP),
    OBJECT(/*model*/ MODEL_MOP_FLIPBLOCK,           /*pos*/   363, 1279,   -18, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvFlipBlock_MOP),
    OBJECT(/*model*/ MODEL_YELLOW_COIN,             /*pos*/  -979, 1250,  -517, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvYellowCoin),
    OBJECT(/*model*/ MODEL_YELLOW_COIN,             /*pos*/ -1810,  803,   441, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvYellowCoin),
    OBJECT(/*model*/ MODEL_YELLOW_COIN,             /*pos*/ -2474,  400,  -505, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvYellowCoin),
    OBJECT(/*model*/ MODEL_BREAKABLE_BOX,           /*pos*/ -3503,  430,   578, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvBreakableBox),
    OBJECT(/*model*/ MODEL_BREAKABLE_BOX,           /*pos*/ -3874,  430,   551, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvBreakableBox),
    OBJECT(/*model*/ MODEL_BREAKABLE_BOX,           /*pos*/ -3628,  413,   450, /*angle*/ 0, 180, 0, /*bhvParam*/ 0, /*bhv*/ bhvBreakableBox),
    OBJECT(/*model*/ MODEL_PURPLE_SWITCH,           /*pos*/  -278,  804,   967, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(0x04), /*bhv*/ bhvPSwitch_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK,         /*pos*/ -4917,  846,   525, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x02) | BPARAM2(0x02), /*bhv*/ bhvSwitchblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK,         /*pos*/ -6002,  846,   -15, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x02) | BPARAM2(0x02), /*bhv*/ bhvSwitchblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK,         /*pos*/ -5733,  846,  1178, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x02) | BPARAM2(0x02), /*bhv*/ bhvSwitchblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK,         /*pos*/ -3452,  776,  1578, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x02) | BPARAM2(0x00), /*bhv*/ bhvSwitchblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK,         /*pos*/ -4273,  803,  1346, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x02) | BPARAM2(0x02), /*bhv*/ bhvSwitchblock_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK_SWITCH,  /*pos*/ -5565,  291,  2329, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvSwitchblock_Switch_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK_SWITCH,  /*pos*/ -3640,  299,  2084, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvSwitchblock_Switch_MOP),
    OBJECT(/*model*/ MODEL_MOP_SWITCHBLOCK_SWITCH,  /*pos*/ -4817,  280,  1969, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(0x00), /*bhv*/ bhvSwitchblock_Switch_MOP),
    // MOP 3 Objects
    OBJECT(/*model*/ MODEL_MOP_SWITCHBOARD,       /*pos*/  -351,  984,  2435, /*angle*/ 0, 93, 0, /*bhvParam*/ BPARAM1(0xFF), /*bhv*/ bhvGreen_Switchboard_MOP),
    OBJECT(/*model*/ MODEL_MOP_ROTATING_BLOCK,    /*pos*/ -2900,  906, -1473, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x01) | BPARAM2(0x01), /*bhv*/ bhvMoving_Rotating_Block_MOP),
    OBJECT(/*model*/ MODEL_MOP_ROTATING_BLOCK,    /*pos*/ -2142, 1009,  2422, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x01) | BPARAM2(0x00), /*bhv*/ bhvMoving_Rotating_Block_MOP),
    OBJECT(/*model*/ MODEL_MOP_ROTATING_BLOCK,    /*pos*/  2048,  906, -1273, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x00) | BPARAM2(0x02), /*bhv*/ bhvMoving_Rotating_Block_MOP),
    OBJECT(/*model*/ MODEL_MOP_FLIPSWITCH_PANEL,  /*pos*/  1517,  694,   768, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvFlipswitch_Panel_MOP),
    OBJECT(/*model*/ MODEL_MOP_FLIPSWITCH_PANEL,  /*pos*/    20,  856, -2217, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvFlipswitch_Panel_MOP),
    OBJECT(/*model*/ MODEL_MOP_FLIPSWITCH_PANEL,  /*pos*/   180, 1093,  1120, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvFlipswitch_Panel_MOP),
    OBJECT(/*model*/ MODEL_MOP_FLIPSWITCH_PANEL,  /*pos*/   543, 1093,   927, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvFlipswitch_Panel_MOP),
    OBJECT(/*model*/ MODEL_NONE,                  /*pos*/   368, 1069, -1836, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_3), /*bhv*/ bhvFlipswitch_Panel_StarSpawn_MOP),
    OBJECT(/*model*/ MODEL_MOP_CHECKPOINT_FLAG,   /*pos*/    13,  808, -2757, /*angle*/ 0, 180, 0, /*bhvParam*/ BPARAM2(0x01), /*bhv*/ bhvCheckpoint_Flag_MOP),
    OBJECT(/*model*/ MODEL_MOP_FLIPSWAP_PLATFORM, /*pos*/  -506,  502,  4011, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(0x02) | BPARAM2(0x02), /*bhv*/ bhvFlipswap_Platform_MOP),
    RETURN(),
};
#endif

const LevelScript level_castle_grounds_entry[] = {
    INIT_LEVEL(),
    LOAD_MIO0        (/*seg*/ 0x07, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x0A, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _outside_mio0SegmentRomStart, _outside_mio0SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x05, _group10_mio0SegmentRomStart, _group10_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0C, _group10_geoSegmentRomStart,  _group10_geoSegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x06, _group15_mio0SegmentRomStart, _group15_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0D, _group15_geoSegmentRomStart,  _group15_geoSegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0F, _common0_geoSegmentRomStart,  _common0_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*bhvParam*/ BPARAM4(0x01), /*bhv*/ bhvMario),
    JUMP_LINK(script_func_global_1),
    JUMP_LINK(script_func_global_11),
    JUMP_LINK(script_func_global_16),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,           castle_grounds_geo_0006F4),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_BUBBLY_TREE,  bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_WARP_PIPE,    warp_pipe_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CASTLE_DOOR,  castle_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_METAL_DOOR,   metal_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_VCUTM_GRILL,  castle_grounds_geo_00070C),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_FLAG,         castle_grounds_geo_000660),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CANNON_GRILL, castle_grounds_geo_000724),

    AREA(/*index*/ 1, castle_grounds_geo_00073C),
        WARP_NODE(/*id*/ WARP_NODE_DEATH, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_03, /*flags*/ WARP_NO_CHECKPOINT),
        JUMP_LINK(script_func_local_1),
        JUMP_LINK(script_func_local_2),
        JUMP_LINK(script_func_local_3),
        JUMP_LINK(script_func_local_4),
#ifdef PORT_MOP_OBJS
        JUMP_LINK(script_func_local_mop),
#endif
        TERRAIN(/*terrainData*/ castle_grounds_seg7_collision_level),
        MACRO_OBJECTS(/*objList*/ castle_grounds_seg7_macro_objs),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0000, /*seq*/ SEQ_SOUND_PLAYER),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_GRASS),
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 180, /*pos*/ -1328, 260, 4664),
    CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
