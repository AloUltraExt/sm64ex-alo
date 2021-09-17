void bhv_Switchblock_Switch_loop(void){
	u8 BP2 = o->oBehParams2ndByte;
	load_object_collision_model();
	o->oAnimState = BP2;
	if ((cur_obj_is_mario_on_platform())&& (gMOPSwitchBlockState!=BP2)){
        cur_obj_play_sound_1(SOUND_GENERAL_DOOR_TURN_KEY);
		gMOPSwitchBlockState ^=1;
	}
	o->header.gfx.scale[1] = (f32)(gMOPSwitchBlockState!=BP2)*0.9f+0.1f;
}


void bhv_Switchblock_loop(void){
	u8 BP2 = o->oBehParams2ndByte;
	o->oAnimState = BP2+o->oAction;
	if (gMOPSwitchBlockState==(BP2>>1)){
		load_object_collision_model();
		o->oAction=0;
	}else{
		o->oAction=1;
	}
}