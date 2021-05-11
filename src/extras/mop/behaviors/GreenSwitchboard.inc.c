#define MAX_SPEED 20.0f
#define SPEED_INC 2.0f
// static char buf[12];

void bhv_green_switchboard_loop(void) {
	struct Object *child = o->oIntroLakituCloud;
	f32 dot;
	f32 dotH;
	if (cur_obj_is_mario_on_platform()==1){
		f32 dx = gMarioState->pos[0] - o->oPosX;
		f32 dz = gMarioState->pos[2] - o->oPosZ;
		f32 dHx = o->oPosX - o->oHomeX;
		f32 dHz = o->oPosZ - o->oHomeZ;
		f32 facingZ = coss(o->oFaceAngleYaw);
		f32 facingX = sins(o->oFaceAngleYaw);
		//if dot is positive, mario is on front arrow
		dot = facingZ*dz+facingX*dx;
		dotH = facingZ*dHz+facingX*dHx;
		//debug
		// sprintf(buf,"dotH %f",dotH);
		// print_text(32,32,buf);
		// sprintf(buf,"dot %f",dot);
		// print_text(32,64,buf);
		// sprintf(buf,"bp1 %d",(((o->oBehParams>>24)&0xFF)*16));
		// print_text(32,96,buf);
		if((dot)>0){
			if(dotH<(((o->oBehParams>>24)&0xFF)*16)){
				o->oForwardVel = approach_by_increment(MAX_SPEED, o->oForwardVel, SPEED_INC);
			}else{
				o->oForwardVel=0;
			}
			o->oFaceAnglePitch = (u32)approach_by_increment(2048.0f, o->oFaceAnglePitch, 128.0f);
		}else{
			if (dotH>(o->oBehParams2ndByte*-16)){
				o->oForwardVel = approach_by_increment(-MAX_SPEED, o->oForwardVel, SPEED_INC);
			}else{
				o->oForwardVel=0;
			}
			//this function doesn't work well with negatives thanks nintendo
			if (o->oFaceAnglePitch>-2048){
				o->oFaceAnglePitch = (u32)approach_by_increment(-2048.0f, o->oFaceAnglePitch, 128.0f);
			}
			
		}
	}else{
		o->oForwardVel = approach_by_increment(0.0f, o->oForwardVel, SPEED_INC);
		o->oFaceAnglePitch = (u32)approach_by_increment(0.0f, o->oFaceAnglePitch, 128.0f);
	}
	child->oFaceAnglePitch+=(s32)(o->oForwardVel*200);
	obj_copy_pos(child,o);
}


void bhv_green_switchboard_init(void) {
	o->oIntroLakituCloud = spawn_object(o,0x2C,bhvUnused05A8);
}


