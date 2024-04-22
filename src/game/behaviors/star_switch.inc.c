// Star Switch Function (Most code borrowed from Red Switch, credits to peachypeach)

void bhv_star_switch_loop(void) {
    switch (o->oAction) {
        case SWITCH_ACT_IDLE: {
            cur_obj_scale(1.5f);
            if (gMarioObject->platform == o && !(gMarioStates->action & MARIO_UNKNOWN_13)) {
                if (lateral_dist_between_objects(o, gMarioObject) < 80.f) {
                    o->oAction = SWITCH_ACT_PRESSED;
                }
            }
        } break;

        case SWITCH_ACT_PRESSED: {
            cur_obj_scale_over_time(2, 3, 1.5f, 0.2f);
            if (o->oTimer >= 3) {
                f32 dist;
                struct Object *star = cur_obj_find_nearest_object_with_behavior(bhvStarSwitchSpawnCondition, &dist);
                if (star) {
                    star->oAction = 1;
                }
                cur_obj_play_sound_2(SOUND_GENERAL2_SWITCH);
                o->oAction = SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
#ifdef RUMBLE_FEEDBACK
                queue_rumble_data(5, 80);
#endif
                o->oTimer = 0;
            }
        } break;

        case SWITCH_ACT_TICKING: {
            s32 maxDuration = (o->oBhvParams2ndByte * 30);
            if (o->oTimer >= maxDuration) {
                f32 dist;
                struct Object *star = cur_obj_find_nearest_object_with_behavior(bhvStarSwitchSpawnCondition, &dist);
                if (star) {
                    star->oAction = 3;
                }
                cur_obj_play_sound_2(SOUND_GENERAL2_SWITCH);
                o->oAction = SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
            } else if (o->oTimer >= maxDuration - 60) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            } else if (o->oTimer > 10) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
            }
        } break;

        case SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF: {
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = SWITCH_ACT_UNPRESSED;
            }
        } break;

        case SWITCH_ACT_UNPRESSED: {
            cur_obj_scale_over_time(2, 3, 0.2f, 1.f);
            if (o->oTimer >= 3) {
                o->oAction = SWITCH_ACT_IDLE;
            }
        } break;
    }
}