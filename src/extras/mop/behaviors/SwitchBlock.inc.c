static u32 SwitchBlockState = 1;

void bhv_Switchblock_Switch_loop(void){
	u8 BP2 = o->oBehParams2ndByte;
	load_object_collision_model();
	o->oAnimState = BP2;
	if ((cur_obj_is_mario_on_platform()==1)&& (SwitchBlockState!=BP2)){
		SwitchBlockState=SwitchBlockState^1;
	}
	o->header.gfx.scale[1] = (f32)(SwitchBlockState!=BP2)*0.9f+0.1f;
}


void bhv_Switchblock_loop(void){
	u8 BP2 = o->oBehParams2ndByte;
	o->oAnimState = BP2+o->oAction;
	if (SwitchBlockState==(BP2>>1)){
		load_object_collision_model();
		o->oAction=0;
	}else{
		o->oAction=1;
	}
}