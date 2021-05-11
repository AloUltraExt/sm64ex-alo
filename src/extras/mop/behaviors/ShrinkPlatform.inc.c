#define SHRINK_TIME 150
#define SHRINK_TIMEF 150.0f

void bhv_shrinkplatform_loop(void) {
	if (o->oAction<2){
		load_object_collision_model();
	}
	//disappearing
	switch(o->oAction){
		case 1:
			if (o->oTimer==SHRINK_TIME){
				o->oAction=2;
			}
			o->header.gfx.scale[0]=((f32)(SHRINK_TIME-o->oTimer))/SHRINK_TIMEF;
			o->header.gfx.scale[2]=((f32)(SHRINK_TIME-o->oTimer))/SHRINK_TIMEF;
			break;
		case 2:
			cur_obj_hide();
			if (o->oTimer==(SHRINK_TIME+1)){
				o->oAction=0;
				o->header.gfx.scale[0]=1.0f;
				o->header.gfx.scale[2]=1.0f;
				cur_obj_unhide();
			}
			break;
	}
	if (cur_obj_is_mario_on_platform() && o->oAction==0){
		o->oAction=1;
		cur_obj_play_sound_1(SOUND_OBJ_UNK23);
	}
}
