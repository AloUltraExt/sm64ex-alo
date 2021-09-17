void bhv_flipswap_loop(void){
	switch(o->oAction){
		//still
		case 0:
			if (((gMarioState->prevAction&ACT_GROUP_MASK)!=ACT_GROUP_AIRBORNE) && ((gMarioState->action& ACT_GROUP_MASK)==ACT_GROUP_AIRBORNE)){
				//sloth brain it
				if (o->oFaceAngleRoll==0){
					o->oMoveAngleRoll=-0x800; // originally 0x400
				}else{
					o->oMoveAngleRoll=0x800; // originally 0x400
				}
				o->oAction=1;
			}
			break;
		//flipping
		case 1:
			if (o->oTimer<0x10){ // originally 0x20
				o->oFaceAngleRoll+=o->oMoveAngleRoll;
			}else 
			if (((gMarioState->action& ACT_GROUP_MASK)!=ACT_GROUP_AIRBORNE)){
				o->oAction=0;
			}
			break;
	}
};