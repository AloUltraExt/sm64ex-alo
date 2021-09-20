#ifdef CHEATS_ACTIONS

#include "sm64.h"
#include "text_strings.h"
#include "gfx_dimensions.h"

#include "audio/external.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game/camera.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/mario_misc.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "game/game_init.h"

#include "options_menu.h"
#include "cheats.h"

struct CheatList Cheats;

const u8 optCheatMenuStr[][32] = {
    { TEXT_OPT_CHEATS },
    { TEXT_OPT_CHEATS_WALKON },
};

static const u8 optsCheatsStr[][64] = {
    { TEXT_OPT_CHEAT0 },
    { TEXT_OPT_CHEAT1 },
    { TEXT_OPT_CHEAT2 },
    { TEXT_OPT_CHEAT3 },
    { TEXT_OPT_CHEAT4 },
    { TEXT_OPT_CHEAT5 },
    { TEXT_OPT_CHEAT6 },
    { TEXT_OPT_CHEAT7 },
    { TEXT_OPT_CHEAT8 },
    { TEXT_OPT_CHEAT9 },
    { TEXT_OPT_CHEAT10 },
};

static const u8 optsMarioSizeCheatStr[][64] = {
    { TEXT_CHEAT_MSIZE0 },
    { TEXT_CHEAT_MSIZE1 },
    { TEXT_CHEAT_MSIZE2 },
};

static const u8 *cheatChoicesMarioSize[] = {
    optsMarioSizeCheatStr[0],
    optsMarioSizeCheatStr[1],
    optsMarioSizeCheatStr[2],
};

static const u8 optsWalkOnCheatStr[][64] = {
    { TEXT_CHEAT_WALKON0 },
    { TEXT_CHEAT_WALKON1 },
    { TEXT_CHEAT_WALKON2 },
    { TEXT_CHEAT_WALKON3 },
    { TEXT_CHEAT_WALKON4 },
    { TEXT_CHEAT_WALKON5 },
};

static struct Option optWalkOnCheats[] = {
    DEF_OPT_TOGGLE( optsWalkOnCheatStr[0], &Cheats.WalkOn.Lava ),
    DEF_OPT_TOGGLE( optsWalkOnCheatStr[1], &Cheats.WalkOn.Quicksand ),
    DEF_OPT_TOGGLE( optsWalkOnCheatStr[2], &Cheats.WalkOn.Water ),
    DEF_OPT_TOGGLE( optsWalkOnCheatStr[3], &Cheats.WalkOn.Gas ),
    DEF_OPT_TOGGLE( optsWalkOnCheatStr[4], &Cheats.WalkOn.Slope ),
    DEF_OPT_TOGGLE( optsWalkOnCheatStr[5], &Cheats.WalkOn.DeathBarrier ),
};

static struct SubMenu menuCheatWalkOn = DEF_SUBMENU( optCheatMenuStr[1], optWalkOnCheats );

struct Option optsCheats[] = {
    DEF_OPT_TOGGLE( optsCheatsStr[0], &Cheats.EnableCheats ),
    DEF_OPT_TOGGLE( optsCheatsStr[1], &Cheats.MoonJump ),
    DEF_OPT_TOGGLE( optsCheatsStr[2], &Cheats.InfiniteHealth ),
    DEF_OPT_TOGGLE( optsCheatsStr[3], &Cheats.InfiniteLives ),
    DEF_OPT_TOGGLE( optsCheatsStr[4], &Cheats.InvinciblePlayer ),
    DEF_OPT_TOGGLE( optsCheatsStr[5], &Cheats.SuperSpeed ),
    DEF_OPT_TOGGLE( optsCheatsStr[6], &Cheats.Responsive ),
    DEF_OPT_TOGGLE( optsCheatsStr[7], &Cheats.ExitAnywhere ),
    DEF_OPT_TOGGLE( optsCheatsStr[8], &Cheats.NoFallDamage ),
    DEF_OPT_CHOICE( optsCheatsStr[9], &Cheats.MarioSize, cheatChoicesMarioSize ),
    DEF_OPT_SUBMENU(optsCheatsStr[10], &menuCheatWalkOn ),
};

struct SubMenu menuCheats = DEF_SUBMENU( optCheatMenuStr[0], optsCheats );

void cheats_moon_jump(struct MarioState *m) {
    if (Cheats.MoonJump) {        
        if (m->controller->buttonDown & L_TRIG) {

            if (m->action != ACT_JUMP && m->heldObj == NULL) {
                set_mario_action(m, ACT_JUMP, 0);
            }

            if (m->action != ACT_HOLD_JUMP && m->heldObj != NULL) {
                set_mario_action(m, ACT_HOLD_JUMP, 0);
            }

            m->vel[1] = 25;
        }
    }
}

void cheats_mario_inputs(struct MarioState *m) {
    m->particleFlags = 0;
    m->collidedObjInteractTypes = m->marioObj->collidedObjInteractTypes;
    m->flags &= 0xFFFFFF;
    
    if (Cheats.EnableCheats) {
        cheats_moon_jump(m);
    }
}

void cheats_infinite_health(struct MarioState *m) {
    if (Cheats.InfiniteHealth)
        m->health = 0x880;
}

void cheats_infinite_lives(struct MarioState *m) {
    if (Cheats.InfiniteLives && m->numLives < 99)
        m->numLives += 1;
}

void cheats_super_speed(struct MarioState *m) {
    if (Cheats.SuperSpeed && m->forwardVel > 0)
        m->forwardVel += 100;
}

void cheats_invincible_player(struct MarioState *m) {
    if (Cheats.InvinciblePlayer)
        m->invincTimer = 1;
}

void cheats_mario_action(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        cheats_infinite_health(m);
        
        cheats_infinite_lives(m);

        cheats_super_speed(m);
        
        cheats_invincible_player(m);
    }
}

void cheats_mario_size(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        switch (Cheats.MarioSize) {
            case 0: // Normal
            default:
                vec3f_set(m->marioObj->header.gfx.scale, 1.0f, 1.0f, 1.0f);
                break;
            case 1: // Tiny
                vec3f_set(m->marioObj->header.gfx.scale, 0.2f, 0.2f, 0.2f);
                break;
            case 2: // Huge   
                vec3f_set(m->marioObj->header.gfx.scale, 2.5f, 2.5f, 2.5f);
                break;
        }
    } else {
        vec3f_set(m->marioObj->header.gfx.scale, 1.0f, 1.0f, 1.0f);
    }
}

f32 cheats_walk_on_environment(f32 height, f32 x, f32 z) {
    f32 newHeight;
    f32 waterLevel = find_water_level(x, z);
    f32 gasLevel = find_poison_gas_level(x, z);

    if (Cheats.EnableCheats && gCurrentObject == gMarioObject) {
        if (Cheats.WalkOn.Water && height < waterLevel) {
            newHeight = waterLevel;
        } else if (Cheats.WalkOn.Gas && height < gasLevel) {
            newHeight = gasLevel;
        } else {
            newHeight = height;
        }
    } else {
        newHeight = height;
    }

    return newHeight;
}

#endif // CHEATS_ACTIONS
