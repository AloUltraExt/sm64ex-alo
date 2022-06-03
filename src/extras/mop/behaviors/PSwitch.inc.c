void bhv_pswitch_swap_coins_and_boxes(void) {
	// Two loops so they don't couple and infinite loop
	while (1) {
        struct Object *boxObj  = cur_obj_nearest_object_with_behavior(bhvBreakableBox);
        if (!boxObj) {
            break;
        } else {
            boxObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            spawn_object(boxObj, MODEL_YELLOW_COIN, bhvOneCoin);
        }
	}

	while (1) {
        struct Object *coinObj = cur_obj_nearest_object_with_behavior(bhvYellowCoin);
        if (!coinObj) {
            break;
        } else {
            coinObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            coinObj->oIntangibleTimer = -1;
            spawn_object(coinObj, MODEL_BREAKABLE_BOX, bhvBreakableBox);
        }
	}
}
