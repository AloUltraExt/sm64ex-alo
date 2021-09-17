s32 flip_block_sqrtf_diff(struct Object *obj) {
    f32 dx;
    f32 dy;
    f32 dz;

    dx = gMarioObject->oPosX - obj->oPosX;
    dz = obj->oPosZ - gMarioObject->oPosZ;
    dy = obj->oPosY - gMarioObject->oPosY;

    if ((sqrtf(dx * dx) < 104.0f) && (sqrtf(dz * dz) < 104.0f) && (sqrtf(dy * dy) < 304.0f)) {
        return TRUE;
    }
    return FALSE;
}

void bhv_flip_block_loop(void) {
    if (o->oAction == 0) {
        load_object_collision_model();
        if (cur_obj_was_attacked_or_ground_pounded()){
            o->oAction = 1;
        }

        if (flip_block_sqrtf_diff(o) && !(o->oPosY < gMarioObject->oPosY) && !(gMarioState[0].vel[1] < 15.0f)) {
            gMarioState[0].vel[1] = 0.0f;
            o->oAction = 1;
        }
    } else {
        if (o->oTimer == 0) {
            o->oAngleVelPitch = 0x1680;
            o->header.gfx.scale[2] = 0.1f;
            cur_obj_play_sound_1(SOUND_GENERAL_SWISH_WATER);
        }

        o->oFaceAnglePitch += o->oAngleVelPitch;
        o->oAngleVelPitch -= 0x20;

        if (o->oAngleVelPitch == 0) {
            o->header.gfx.scale[2] = 1.0f;
            o->oAction = 0;
            o->oFaceAnglePitch = 0;
        }

        if (o->oFaceAnglePitch & 0x4000) {
            cur_obj_play_sound_1(SOUND_GENERAL_SWISH_WATER);
        }
    }
}
