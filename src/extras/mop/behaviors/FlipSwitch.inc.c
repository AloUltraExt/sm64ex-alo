void bhv_flipswitch_panel_init(void){
	o->parentObj = cur_obj_nearest_object_with_behavior(bhvFlipswitch_Panel_StarSpawn_MOP);
}

void bhv_flipswitch_panel_loop(void){
	if (gMOPFlipSwitchStarSpawned) {
		o->oAnimState = 2;
	} else {
		switch(o->oAction){
			//mario is not on
			case 0:
				if (cur_obj_is_mario_on_platform()) {
					o->oAction = 1;
					o->parentObj->oHiddenStarTriggerCounter += 1-(2*o->oAnimState);
					o->oAnimState ^= 1;
					cur_obj_play_sound_1(SOUND_GENERAL_BIG_CLOCK);
				}
				break;
			//mario is on
			case 1:
				if(!cur_obj_is_mario_on_platform()) {
					o->oAction=0;
				}
				break;
		}
	}
}

void bhv_flipswitch_panel_starspawn_init(void){
	o->oHealth = count_objects_with_behavior(bhvFlipswitch_Panel_MOP);
}

void bhv_flipswitch_panel_starspawn_loop(void){
	if(o->oHealth==o->oHiddenStarTriggerCounter && !gMOPFlipSwitchStarSpawned){
		spawn_default_star(o->oPosX, o->oPosY, o->oPosZ);
		gMOPFlipSwitchStarSpawned = TRUE;
		o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
	}
}