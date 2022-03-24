// lll_rotating_hex_flame.inc.c

void bhv_lll_rotating_hex_flame_loop(void) {
    f32 sp24 = o->oLLLRotatingHexFlameUnkF4;
    f32 sp20 = o->oLLLRotatingHexFlameUnkF8;
    f32 sp1C = o->oLLLRotatingHexFlameUnkFC;

    cur_obj_set_pos_relative(o->parentObj, sp24, sp20, sp1C);
    o->oPosY = o->parentObj->oPosY + 100.0f;

    if (o->parentObj->oAction == 3) {
        obj_mark_for_deletion(o);
    }
}

void fire_bar_spawn_flames(s16 a0) {
    struct Object *sp2C;
    UNUSED u8 filler[4];
    s32 i;
    s32 sp20;
    f32 sp1C = sins(a0) * 200.0f;
    f32 sp18 = coss(a0) * 200.0f;

    sp20 = o->oBhvParams2ndByte == 0 ? 4 : 3;

    for (i = 0; i < sp20; i++) {
        sp2C = spawn_object(o, MODEL_RED_FLAME, bhvLLLRotatingHexFlame);
        sp2C->oLLLRotatingHexFlameUnkF4 += sp1C;
        sp2C->oLLLRotatingHexFlameUnkF8 = o->oPosY - 200.0f;
        sp2C->oLLLRotatingHexFlameUnkFC += sp18;
        obj_scale_xyz(sp2C, 6.0f, 6.0f, 6.0f);
        sp1C += sins(a0) * 150.0f;
        sp18 += coss(a0) * 150.0f;
    }
}

void fire_bar_act_0(void) {
#ifndef NODRAWINGDISTANCE
    if (o->oDistanceToMario < 3000.0f) {
#endif
        o->oAction = 1;
#ifndef NODRAWINGDISTANCE
    }
#endif
}

void fire_bar_act_1(void) {
    fire_bar_spawn_flames(0);
    fire_bar_spawn_flames(-0x8000);
    o->oAngleVelYaw = 0;
    o->oMoveAngleYaw = 0;
    o->oAction = 2;
}

void fire_bar_act_2(void) {
    o->oAngleVelYaw = -0x100;
    o->oMoveAngleYaw += o->oAngleVelYaw;
#ifndef NODRAWINGDISTANCE
    if (o->oDistanceToMario > 3200.0f)
        o->oAction = 3;
#endif
}

void fire_bar_act_3(void) {
    o->oAction = 0;
}

void (*sRotatingCwFireBarsActions[])(void) = {
    fire_bar_act_0,
    fire_bar_act_1,
    fire_bar_act_2,
    fire_bar_act_3,
};

void bhv_lll_rotating_block_fire_bars_loop(void) {
    cur_obj_call_action_function(sRotatingCwFireBarsActions);
    if (o->oBhvParams2ndByte == 0) {
        load_object_collision_model();
    }
}
