void bhv_sandblock_loop(void) {
	if (o->oAction<2){
		load_object_collision_model();
	}
	//disappearing
	switch(o->oAction){
		case 1:
			if (o->oTimer==300){
				o->oAction=2;
			}
			o->header.gfx.scale[1]=((f32)(300-o->oTimer))/300.0f;
			spawn_object_relative(0,0,0,0,o, 0, bhvDirtParticleSpawner);
			cur_obj_play_sound_1(SOUND_ENV_MOVINGSAND);
			break;
		case 2:
			cur_obj_hide();
			if (o->oTimer==301){
				o->oAction=0;
				o->header.gfx.scale[1]=1.0f;
				cur_obj_unhide();
			}
			break;
	}
	if (cur_obj_is_mario_on_platform() && o->oAction==0){
		o->oAction=1;
	}
}