


void bhv_flipswap_loop(void){
	switch(o->oAction){
		//still
		case 0:
			if (((gMarioState->prevAction&ACT_GROUP_MASK)!=ACT_GROUP_AIRBORNE) && ((gMarioState->action& ACT_GROUP_MASK)==ACT_GROUP_AIRBORNE)){
				//sloth brain it
				if (o->oFaceAngleRoll==0){
					o->oMoveAngleRoll=-2048;
				}else{
					o->oMoveAngleRoll=2048;
				}
				o->oAction=1;
			}
			break;
		//flipping
		case 1:
			if (o->oTimer<16){
				o->oFaceAngleRoll+=o->oMoveAngleRoll;
			}else 
			if (((gMarioState->action& ACT_GROUP_MASK)!=ACT_GROUP_AIRBORNE)){
				o->oAction=0;
			}
			break;
	}
};