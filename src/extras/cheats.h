#ifndef CHEATS_H
#define CHEATS_H

#include <PR/ultratypes.h>

#include "sm64.h"

#include "audio/data.h"
#include "audio/external.h"

#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/level_script.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"

#include "game/area.h"
#include "game/behavior_actions.h"
#include "game/camera.h"
#include "game/debug.h"
#include "game/game_init.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/main.h"
#include "game/mario.h"
#include "game/mario_actions_airborne.h"
#include "game/mario_actions_automatic.h"
#include "game/mario_actions_cutscene.h"
#include "game/mario_actions_moving.h"
#include "game/mario_actions_object.h"
#include "game/mario_actions_stationary.h"
#include "game/mario_actions_submerged.h"
#include "game/mario_misc.h"
#include "game/mario_step.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "game/rendering_graph_node.h"
#include "game/rumble_init.h"
#include "game/save_file.h"
#include "game/sound_init.h"

#include "options_menu.h"

#ifndef TARGET_N64
#include <stdbool.h>
#else
#define bool int
#endif

extern const u8 optCheatMenuStr[][32];

struct CheatListWalkOn {
    bool    Lava;
    bool    Quicksand;
    bool    Water;
    bool    Gas;
    bool    Slope;
    bool    DeathBarrier;
};

struct CheatList {
    bool    EnableCheats;
    bool    MoonJump;
    bool    InfiniteHealth;
    bool    InfiniteLives;
    bool    SuperSpeed;
    bool    Responsive;
    bool    ExitAnywhere;
    u32     MarioSize;
    struct CheatListWalkOn WalkOn;
};

extern struct CheatList Cheats;

extern struct SubMenu menuCheats;

extern void cheats_mario_inputs(struct MarioState *m);
extern void cheats_mario_action(struct MarioState *m);
extern void cheats_responsive_controls(struct MarioState *m);
extern void cheats_mario_size(struct MarioState *m);
extern f32 cheats_walk_on_environment(f32 height, f32 x, f32 z);

#endif // CHEATS_H
