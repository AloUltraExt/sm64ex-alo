// door.inc.c

struct DoorAction {
    u32 flag;
    s32 action;
};

static struct DoorAction sDoorActions[] = { { 0x40000, 3 }, { 0x80000, 4 }, { 0x10000, 1 }, { 0x20000, 2 }, { 0xFFFFFFFF, 0 }, };

static s32 sDoorOpenSounds[] = { SOUND_GENERAL_OPEN_WOOD_DOOR, SOUND_GENERAL_OPEN_IRON_DOOR };

static s32 sDoorCloseSounds[] = { SOUND_GENERAL_CLOSE_WOOD_DOOR, SOUND_GENERAL_CLOSE_IRON_DOOR };

void door_animation_and_reset(s32 sp18) {
    cur_obj_init_animation_with_sound(sp18);
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = 0;
    }
}

void set_door_camera_event(void) {
    if (segmented_to_virtual(bhvDoor) == o->behavior) {
        gPlayerCameraState->cameraEvent = CAM_EVENT_DOOR;
    } else {
        gPlayerCameraState->cameraEvent = CAM_EVENT_DOOR_WARP;
    }
    gPlayerCameraState->usedObj = o;
}

#if FIX_METAL_DOOR_CASTLE_SOUND
#define METAL_DOOR_CHECK(x, y) cur_obj_has_model(x) || cur_obj_has_model(y)
#else
#define METAL_DOOR_CHECK(x, y) cur_obj_has_model(x)
#endif

void play_door_open_noise(void) {
    s32 isMetalDoor = METAL_DOOR_CHECK(MODEL_HMC_METAL_DOOR, MODEL_CASTLE_METAL_DOOR);
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(sDoorOpenSounds[isMetalDoor]);
        gTimeStopState |= TIME_STOP_MARIO_OPENED_DOOR;
    }
    if (o->oTimer == 70) {
        cur_obj_play_sound_2(sDoorCloseSounds[isMetalDoor]);
    }
}

void play_warp_door_open_noise(void) {
    s32 isMetalDoor = METAL_DOOR_CHECK(MODEL_HMC_METAL_DOOR, MODEL_CASTLE_METAL_DOOR);
    if (o->oTimer == 30) {
        cur_obj_play_sound_2(sDoorCloseSounds[isMetalDoor]);
    }
}

#undef METAL_DOOR_CHECK

void bhv_door_loop(void) {
    s32 sp1C = 0;

    while (sDoorActions[sp1C].flag != 0xFFFFFFFF) {
        if (cur_obj_clear_interact_status_flag(sDoorActions[sp1C].flag)) {
            set_door_camera_event();
            cur_obj_change_action(sDoorActions[sp1C].action);
        }
        sp1C++;
    }

    switch (o->oAction) {
        case 0:
            cur_obj_init_animation_with_sound(0);
#if FIX_STAR_DOOR_ROOM_RENDER
            load_object_collision_model();
#endif
            break;
        case 1:
            door_animation_and_reset(1);
            play_door_open_noise();
            break;
        case 2:
            door_animation_and_reset(2);
            play_door_open_noise();
            break;
        case 3:
            door_animation_and_reset(3);
            play_warp_door_open_noise();
            break;
        case 4:
            door_animation_and_reset(4);
            play_warp_door_open_noise();
            break;
    }

#if !FIX_STAR_DOOR_ROOM_RENDER
    if (o->oAction == 0) {
        load_object_collision_model();
    }
#endif

    bhv_star_door_loop_2();
}

#if BETTER_ROOM_CHECKS
#define FIND_FLOOR_DOOR find_room_floor
#else
#define FIND_FLOOR_DOOR find_floor
#endif

void bhv_door_init(void) {
    struct Surface *floor;
    f32 x = o->oPosX;
    f32 y = o->oPosY;
    f32 z = o->oPosZ;

    FIND_FLOOR_DOOR(x, y, z, &floor);
    if (floor != NULL) {
        o->oDoorUnkF8 = floor->room;
    }

    x = o->oPosX + sins(o->oMoveAngleYaw) * 200.0f;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * 200.0f;
    FIND_FLOOR_DOOR(x, y, z, &floor);
    if (floor != NULL) {
        o->oDoorUnkFC = floor->room;
    }

    x = o->oPosX + sins(o->oMoveAngleYaw) * -200.0f;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * -200.0f;
    FIND_FLOOR_DOOR(x, y, z, &floor);
    if (floor != NULL) {
        o->oDoorUnk100 = floor->room;
    }

    if (o->oDoorUnkF8 > 0 && o->oDoorUnkF8 < 60) {
        gDoorAdjacentRooms[o->oDoorUnkF8][0] = o->oDoorUnkFC;
        gDoorAdjacentRooms[o->oDoorUnkF8][1] = o->oDoorUnk100;
    }
}

#undef FIND_FLOOR_DOOR

void bhv_star_door_loop_2(void) {
    s32 sp4 = FALSE;

    if (gMarioCurrentRoom != 0) {
        if (o->oDoorUnkF8 == gMarioCurrentRoom) {
            sp4 = TRUE;
        } else if (gMarioCurrentRoom == o->oDoorUnkFC) {
            sp4 = TRUE;
        } else if (gMarioCurrentRoom == o->oDoorUnk100) {
            sp4 = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][0] == o->oDoorUnkFC) {
            sp4 = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][0] == o->oDoorUnk100) {
            sp4 = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][1] == o->oDoorUnkFC) {
            sp4 = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][1] == o->oDoorUnk100) {
            sp4 = TRUE;
        }
    } else {
        sp4 = TRUE;
    }

    if (sp4 == TRUE) {
        o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
        D_8035FEE4++;
    }

    if (!sp4) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    }

    o->oDoorUnk88 = sp4;
}
