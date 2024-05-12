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
            load_object_collision_model();
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

    bhv_door_rendering_loop();
}

#if BETTER_ROOM_CHECKS
#define GET_ROOM_DOOR(x, y, z, r) r = get_room_at_pos(x, y, z);
#else
#define GET_ROOM_DOOR(x, y, z, r)      \
    find_room_floor(x, y, z, &floor);  \
    if (floor != NULL) r = floor->room;
#endif

void bhv_door_init(void) {
    const f32 checkDist = 200.0f;

#if !BETTER_ROOM_CHECKS
    struct Surface *floor;
#endif

    f32 x = o->oPosX;
    f32 y = o->oPosY;
    f32 z = o->oPosZ;

    GET_ROOM_DOOR(x, y, z, o->oDoorSelfRoom);

    x = o->oPosX + sins(o->oMoveAngleYaw) * checkDist;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * checkDist;

    GET_ROOM_DOOR(x, y, z, o->oDoorForwardRoom);

    x = o->oPosX + sins(o->oMoveAngleYaw) * -checkDist;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * -checkDist;

    GET_ROOM_DOOR(x, y, z, o->oDoorBackwardRoom);

    if (
        // Ensure the room number is in bounds.
        o->oDoorSelfRoom > 0 && o->oDoorSelfRoom < ARRAY_COUNT(gDoorAdjacentRooms)
#if !FIX_DOOR_NO_ROOM_VISIBLE
        // Only set gDoorAdjacentRooms for transition rooms.
        && o->oDoorSelfRoom    != o->oDoorForwardRoom
        && o->oDoorSelfRoom    != o->oDoorBackwardRoom
        && o->oDoorForwardRoom != o->oDoorBackwardRoom
#endif
    ) {
        gDoorAdjacentRooms[o->oDoorSelfRoom].forwardRoom  = o->oDoorForwardRoom;
        gDoorAdjacentRooms[o->oDoorSelfRoom].backwardRoom = o->oDoorBackwardRoom;
    }
}

#undef GET_ROOM_DOOR

void bhv_door_rendering_loop(void) {
    struct TransitionRoomData* transitionRoom = &gDoorAdjacentRooms[gMarioCurrentRoom];

    o->oDoorIsRendering = (
        gMarioCurrentRoom            == 0                    || // Mario is in the "global" room.
        gMarioCurrentRoom            == o->oDoorSelfRoom     || // Mario is in the same room as the door.
        gMarioCurrentRoom            == o->oDoorForwardRoom  || // Mario is in the door's  forward room.
        gMarioCurrentRoom            == o->oDoorBackwardRoom || // Mario is in the door's backward room.
        transitionRoom->forwardRoom  == o->oDoorForwardRoom  || // The transition room's  forward room is in the same room as this door's  forward room.
        transitionRoom->forwardRoom  == o->oDoorBackwardRoom || // The transition room's  forward room is in the same room as this door's backward room.
        transitionRoom->backwardRoom == o->oDoorForwardRoom  || // The transition room's backward room is in the same room as this door's  forward room.
        transitionRoom->backwardRoom == o->oDoorBackwardRoom    // The transition room's backward room is in the same room as this door's backward room.
    );

    if (o->oDoorIsRendering) {
        o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
        gNumDoorRenderCount++;
    } else {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    }
}
