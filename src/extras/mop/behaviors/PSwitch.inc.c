static void Swap_Coins_Box(void){
	struct Object *obj;
	struct Object *Cobj;
	//two loops so they don't couple and infinite loop
	while(1){
		obj = cur_obj_nearest_object_with_behavior(bhvBreakableBox);
		if (obj==NULL){
			break;
		}else{
			if(obj){
			obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
			spawn_object(obj,116,bhvOneCoin);
			}
		}
	}
	while(1){
		Cobj = cur_obj_nearest_object_with_behavior(bhvYellowCoin);
		if (Cobj==NULL){
			break;
		}else{
			if(Cobj){
			Cobj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
			Cobj->oIntangibleTimer = -1;
			spawn_object(Cobj,129,bhvBreakableBox);
			}
		}
	}
}


void bhv_pswitch_loop(void) {
    UNUSED s32 unused;
    switch (o->oAction) {
        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */
        case PURPLE_SWITCH_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.0f);
            if (gMarioObject->platform == o && !(gMarioStates[0].action & MARIO_UNKNOWN_13)) {
                if (lateral_dist_between_objects(o, gMarioObject) < 127.5) {
                    o->oAction = PURPLE_SWITCH_PRESSED;
                }
            }
            break;
        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_PRESSED:
            cur_obj_scale_over_time(2, 3, 1.0f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
				Swap_Coins_Box();
			}
            break;
        /**
         * Play a continuous ticking sound that gets faster when time is almost
         * up. When time is up, move to a waiting-while-pressed state.
         */
        case PURPLE_SWITCH_TICKING:
			if (o->oTimer < 360) {
				play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
			} else {
				play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
			}
			if (o->oTimer > 400) {
				o->oAction = PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF;
				Swap_Coins_Box();
			}
            break;
        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_UNPRESSED:
            cur_obj_scale_over_time(2, 3, 0.2f, 1.0f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_IDLE;
            }
            break;
        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_UNPRESSED;
            }
            break;
    }
}
