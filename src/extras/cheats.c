#ifdef CHEATS_ACTIONS

#include <PR/ultratypes.h>

#include "sm64.h"
#include "behavior_data.h"
#include "level_table.h"
#include "model_ids.h"
#include "object_fields.h"
#include "seq_ids.h"

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

#include "cheats.h"

struct CheatList Cheats;

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

void cheats_responsible_controls(struct MarioState *m) {
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

#endif // CHEATS_ACTIONS
