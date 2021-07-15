// struct WarpCheckpoint {
    // /*0x00*/ u8 actNum;
    // /*0x01*/ u8 courseNum;
    // /*0x02*/ u8 levelID;
    // /*0x03*/ u8 areaNum;
    // /*0x04*/ u8 warpNode;
// };
extern struct WarpCheckpoint gWarpCheckpoint;

void bhv_checkpoint_flag_init(void){
	if(gWarpCheckpoint.actNum==64 && o->oBehParams==0){
		gMarioStates[0].pos[0]=o->oPosX;
		gMarioStates[0].pos[1]=o->oPosY;
		gMarioStates[0].pos[2]=o->oPosZ;
	}
}
//0 reg, 1 reset
void bhv_checkpoint_flag_loop(void){
	if (o->oBehParams>0){
		if (o->oDistanceToMario<150.0f){
			gWarpCheckpoint.actNum=0;
			gWarpCheckpoint.courseNum=COURSE_NONE;
		}
	}else{
		o->oIntangibleTimer=0;
		if (o->oDistanceToMario<150.0f | gMarioStates[0].interactObj == o){
			//don't set a real checkpoint because we don't have a real
			//warp node to set it to. Instead abuse the fact that
			//in game checkopints only set the course num
			if (o->oAction==0){
				gWarpCheckpoint.actNum=64;
				gWarpCheckpoint.courseNum=COURSE_NONE;
				o->oAction=1;
				cur_obj_play_sound_1(SOUND_GENERAL_OPEN_CHEST);
			}
		}else{
			o->oAction=0;
		}
	}
}