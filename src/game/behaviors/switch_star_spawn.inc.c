// Star Switch Spawn

void bhv_star_switch_spawn_condition_init(void) {
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
    struct Surface *s;
    f32 floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &s);
    if (s) {
        o->oPosY = floorHeight + 30.f;
        o->oFloorHeight = floorHeight;
    }
    obj_scale_xyz(o, 1.5f, 1.5f, 0.75f);
}

void bhv_star_switch_spawn_condition_loop(void) {
    switch (o->oAction) {

        // Star not spawned
        case 0: {
        } break;

        // Spawn star
        case 1: {
            struct Object *star = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvTimedStarSpawnCoordinates, o->oHomeX, o->oHomeY, o->oHomeZ, 0, 0, 0);
            star->oBhvParams = o->oBhvParams;
            star->oHomeX = o->oHomeX;
            star->oHomeY = o->oHomeY;
            star->oHomeZ = o->oHomeZ;
            star->oFaceAnglePitch = 0;
            star->oFaceAngleRoll = 0;
            star->oBhvParams2ndByte = 1;
            o->oAction = 2;
            o->parentObj = star;
        } break;

        // Star spawned
        case 2: {
        } break;

        // Despawn star
        case 3: {
            struct Object *star = o->parentObj;
            if (star && star->activeFlags && star->behavior == bhvTimedStarSpawnCoordinates) {
                gCurrentObject = star;
                spawn_mist_particles();
                gCurrentObject = o;
                obj_mark_for_deletion(star);
            }
            o->oAction = 0;
        } break;
    }
    o->oFaceAngleYaw = 0x100;
}
