void bhv_pswitch_swap_coins_and_boxes(void) {
	struct Object *obj;
	struct Object *Cobj;
	//two loops so they don't couple and infinite loop
	while(1) {
		obj = cur_obj_nearest_object_with_behavior(bhvBreakableBox);
		if (obj==NULL) {
			break;
		} else {
			if (obj) {
                obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                spawn_object(obj, 116, bhvOneCoin);
			}
		}
	}
	while(1) {
		Cobj = cur_obj_nearest_object_with_behavior(bhvYellowCoin);
		if (Cobj==NULL) {
			break;
		} else {
			if (Cobj) {
                Cobj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                Cobj->oIntangibleTimer = -1;
                spawn_object(Cobj, 129, bhvBreakableBox);
			}
		}
	}
}
