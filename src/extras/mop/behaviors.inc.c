//bhvUnused05A8 is basically a stub.
//SPAWN_CHILD(ID,bhvUnused05A8) to spawn model parts

const BehaviorScript bhvFlipBlock_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_FLOAT(oDrawingDistance, 7167),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    LOAD_COLLISION_DATA(col_FlipBlock_MOP_0x7d1a98),
    SET_HITBOX(512,512),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flip_block_loop),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};


const BehaviorScript bhvNoteblock_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    LOAD_COLLISION_DATA(col_Noteblock_MOP_0xaa6444),
    SCALE(0,64),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_noteblock_loop),
    CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSandblock_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE ),
    LOAD_COLLISION_DATA(col_Sandblock_MOP_0xaa6444),
        BEGIN_LOOP(),
        CALL_NATIVE(bhv_sandblock_loop),
    END_LOOP(),
};

const BehaviorScript bhvSpring_MOP[] = {
    BEGIN(OBJ_LIST_LEVEL),
    SET_HITBOX(160,160),
    SET_INTERACT_TYPE(INTERACT_COIN),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_Spring_loop),
    END_LOOP(),
};

const BehaviorScript bhvJukebox_MOP[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HITBOX(256,256),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
        CALL_NATIVE(bhv_jukebox_loop),
    END_LOOP(),
};

const BehaviorScript bhvShrink_Platform_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE ),
    LOAD_COLLISION_DATA(col_Shrink_Platform_MOP_0xad3720),
    SPAWN_CHILD(MODEL_MOP_SHRINKPLAT_BORDER, bhvUnused05A8),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_shrinkplatform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSwitchblock_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE ),
    LOAD_COLLISION_DATA(col_Switchblock_MOP_0x7d3058),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_Switchblock_loop),
    END_LOOP(),
};

const BehaviorScript bhvSwitchblock_Switch_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(col_Switchblock_Switch_MOP_0x7d7348),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_Switchblock_Switch_loop),
    END_LOOP(),
};

const BehaviorScript bhvEmitter_MOP[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags,OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    SET_FLOAT(oDrawingDistance,5120),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_emitter_loop),
    END_LOOP(),
};

const BehaviorScript bhvFlipswitch_Panel_StarSpawn_MOP[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    CALL_NATIVE(bhv_flipswitch_panel_starspawn_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flipswitch_panel_starspawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvFlipswitch_Panel_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE ),
    LOAD_COLLISION_DATA(col_Flipswitch_Panel_MOP_0x7daf78),
    SET_FLOAT(oCollisionDistance,1024),
    CALL_NATIVE(bhv_flipswitch_panel_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flipswitch_panel_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvCheckpoint_Flag_MOP[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags,OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    SET_INT(oInteractType,INTERACT_POLE),
    SET_HITBOX(64,650),
    CALL_NATIVE(bhv_checkpoint_flag_init),
    SET_INT(oIntangibleTimer, -1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_checkpoint_flag_loop),
    END_LOOP(),
};

const BehaviorScript bhvFlipswap_Platform_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE ),
    SET_INT(oFaceAngleRoll,0),
    LOAD_COLLISION_DATA(col_Flipswap_Platform_MOP_0x7d9d88),
    SPAWN_CHILD(MODEL_MOP_FLIPSWAP_PLATFORM_BORDER, bhvUnused05A8),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flipswap_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

//bhvYellowCoin gets converted
const BehaviorScript bhvPSwitch_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oBehParams2ndByte, 3),
    GOTO(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvBlargg[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 100, /*Gravity*/ 0, /*Bounciness*/ -10, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 240, /*Height*/ 250),
    SET_HOME(),
    LOAD_ANIMATIONS(oAnimations, blargg_seg5_anims_0500616C),
    ANIMATE(0),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        SET_INT(oInteractStatus, 0),
        CALL_NATIVE(bhv_blargg_mop),
    END_LOOP(),
}; 

const BehaviorScript bhvMoving_Rotating_Block_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(col_Moving_Rotating_Block_MOP_0x7e3ea0),
    SET_FLOAT(oDrawingDistance,19455),
    CALL_NATIVE(bhv_move_rotate_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_move_rotate_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGreen_Switchboard_MOP[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL),
    LOAD_COLLISION_DATA(col_Green_Switchboard_MOP_0x7ddc38),
    CALL_NATIVE(bhv_green_switchboard_init),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_green_switchboard_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

