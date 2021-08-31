// breakable_wall.inc.c

void bhv_wf_breakable_wall_loop(void) {
    if (gMarioStates[0].action == ACT_SHOT_FROM_CANNON) {
        cur_obj_become_tangible();
        if (obj_check_if_collided_with_object(o, gMarioObject)) {
            if (cur_obj_has_behavior(bhvWfBreakableWallRight)) {
                play_puzzle_jingle();
#if QOL_FEATURE_BETTER_WF_BREAKEABLE_WALL
                set_mario_action(gMarioState, ACT_SPAWN_SPIN_AIRBORNE, 0);
#endif
            }

            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
            o->oInteractType = INTERACT_DAMAGE;
#if !QOL_FEATURE_BETTER_WF_BREAKEABLE_WALL
            o->oDamageOrCoinValue = 1;
#endif
            obj_explode_and_spawn_coins(80.0f, 0);
        }
    } else {
        cur_obj_become_intangible();
    }
}
