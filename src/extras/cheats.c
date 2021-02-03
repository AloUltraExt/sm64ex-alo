#ifdef CHEATS_ACTIONS

#include <PR/ultratypes.h>

#include "sm64.h"
#include "behavior_data.h"
#include "level_table.h"
#include "model_ids.h"
#include "object_fields.h"
#include "seq_ids.h"
#include "text_strings.h"

#include "actors/common0.h"

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

#include "pc/configfile.h"

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
    DEF_OPT_TOGGLE( optsCheatsStr[4], &Cheats.SuperSpeed ),
    DEF_OPT_TOGGLE( optsCheatsStr[5], &Cheats.Responsive ),
    DEF_OPT_TOGGLE( optsCheatsStr[6], &Cheats.ExitAnywhere ),
    DEF_OPT_CHOICE( optsCheatsStr[7], &Cheats.MarioSize, cheatChoicesMarioSize ),
    DEF_OPT_SUBMENU( optsCheatsStr[8], &menuCheatWalkOn ),
};

struct SubMenu menuCheats = DEF_SUBMENU( optCheatMenuStr[0], optsCheats );

void cheats_moon_jump(struct MarioState *m) {
    if (Cheats.MoonJump) {        
        if (m->controller->buttonPressed & L_TRIG) {
            set_mario_action(m, ACT_JUMP, 0);
        }

        if (m->controller->buttonDown & L_TRIG) {
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

void cheats_mario_action(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        cheats_infinite_health(m);
        
        cheats_infinite_lives(m);

        cheats_super_speed(m);
    }
}

void cheats_responsive_controls(struct MarioState *m) {
    if (Cheats.Responsive && Cheats.EnableCheats) {
        m->faceAngle[1] = m->intendedYaw;
    } else {
        m->faceAngle[1] = m->intendedYaw - approach_s32((s16)(m->intendedYaw - m->faceAngle[1]), 0, 0x800, 0x800);
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

    if (Cheats.EnableCheats) {
        if (Cheats.WalkOn.Water && height < waterLevel && gCurrentObject == gMarioObject) {
            newHeight = waterLevel;
        } else if (Cheats.WalkOn.Gas && height < gasLevel && gCurrentObject == gMarioObject) {
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
