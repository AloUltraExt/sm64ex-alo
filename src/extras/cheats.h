#ifndef CHEATS_H
#define CHEATS_H

#include "sm64.h"
#include "gfx_dimensions.h"
#include "engine/math_util.h"
#include "audio/external.h"
#include "game/camera.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"
#include "game/print.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "game/mario_misc.h"

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
    bool    InvinciblePlayer;
    bool    SuperSpeed;
    bool    Responsive;
    bool    ExitAnywhere;
    bool    NoFallDamage;
    u32     MarioSize;
    struct CheatListWalkOn WalkOn;
};

extern struct CheatList Cheats;

extern struct SubMenu menuCheats;

extern void cheats_mario_inputs(struct MarioState *m);
extern void cheats_mario_action(struct MarioState *m);
extern void cheats_mario_size(struct MarioState *m);
extern f32 cheats_walk_on_environment(f32 height, f32 x, f32 z);

#endif // CHEATS_H
