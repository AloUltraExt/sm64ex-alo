// Timed Star Spawn

void bhv_timed_star_spawn_loop(void) {
    switch (o->oAction) {
        case 0:
            o->oFaceAngleYaw += 0x800;
            if (o->oTimer > 20) {
                o->oAction = 1.0f;
            }
            break;

        case 1:
            obj_move_xyz_using_fvel_and_yaw(o);
            o->oFaceAngleYaw += 0x800;
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            cur_obj_play_sound_1(SOUND_ENV_STAR);
            if (o->oTimer == 30) {
                o->oAction = 2;
                o->oForwardVel = 0;
                play_power_star_jingle(TRUE);
            }
            break;

        case 2:
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            obj_move_xyz_using_fvel_and_yaw(o);
            o->oFaceAngleYaw += 0x800;
            cur_obj_play_sound_1(SOUND_ENV_STAR);
            cur_obj_play_sound_2(SOUND_GENERAL_STAR_APPEARS);
            cur_obj_become_tangible();
            o->oPosY = o->oHomeY;
            o->oAction = 3;
            break;

        case 3:
            o->oFaceAngleYaw += 0x800;
            if (o->oTimer == 20) {
                gObjCutsceneDone = TRUE;
                clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            }

            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                obj_mark_for_deletion(o);
                o->oInteractStatus = 0;
            }
            break;
    }
}