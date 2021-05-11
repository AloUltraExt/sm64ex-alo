void bhv_blargg_mop(void) {
    f32 speed = 10.f;
    cur_obj_scale(2.0f);
    switch (o->oAction) {
        case 0:
            // swim after Mario
            cur_obj_init_animation(0);
            if (cur_obj_lateral_dist_from_mario_to_home() < 1400.f) {
                o->oPosY = approach_f32(o->oPosY, o->oHomeY - 140.f, 5.0f, 5.0f);
            } else {
                o->oPosY = approach_f32(o->oPosY, o->oHomeY - 220.f, 5.0f, 5.0f);
                o->oAngleToMario = cur_obj_angle_to_home();
                if (cur_obj_lateral_dist_to_home() < 200.f) {
                    speed = 0.f;
                }
            }
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x0140);
            if (coss(o->oMoveAngleYaw - o->oAngleToMario) > 0.f) {
                o->oForwardVel = approach_f32(
                    o->oForwardVel, (coss(o->oMoveAngleYaw - o->oAngleToMario) + 1.0f) * speed, 1.0f, 1.0f);
            }
            if (o->oDistanceToMario < 600.f){
                if (abs_angle_diff(obj_angle_to_object(o, gMarioObject), o->oMoveAngleYaw) < 0x2000){
                o->oAction = 1;
                }
            }
            break;
        case 1:
            // attack
            o->oPosY = approach_f32(o->oPosY, o->oHomeY, 5.0f, 5.0f);
            o->oForwardVel = approach_f32(o->oForwardVel, 24.f, 1.0f, 1.0f);
            cur_obj_init_animation(1);
            if (o->oTimer == 0x2D) {
                o->oAction = 0;
            }
            break;
    }
    cur_obj_move_xz_using_fvel_and_yaw();
    resolve_and_return_wall_collisions(&o->oPosX, 10.0f, 150.0f);
}

/*
        case 0:
            cur_obj_init_animation(0);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
            if (o->oDistanceToMario < 220.f) {
                o->oAction = 1;
                gMarioState->action = ACT_BACKWARD_AIR_KB;
                cur_obj_play_sound_2(SOUND_OBJ_HEAVEHO_TOSSED);
                cur_obj_play_sound_2(SOUND_MARIO_WAAAOOOW);
                gMarioObject->oInteractStatus |= INT_STATUS_MARIO_UNK2;
                gMarioState->forwardVel = -55.0f;
                gMarioState->vel[1] = 95.0f;
                gMarioState->faceAngle[1] = o->oMoveAngleYaw - 0x8000;
                cur_obj_init_animation(1);
                o->header.gfx.animInfo.animFrame = 2;
            }
            break;
        case 1:
            if (o->oTimer == 0x2D) {
                o->oAction = 0;
            }
            break;*/ 
