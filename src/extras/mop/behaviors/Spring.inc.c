void bounce_off_object(struct MarioState *m, struct Object *o, f32 velY);

void bhv_Spring_loop(void) {
	f32 Yspd=56.0f;
	u32 CarmackMeme;
	u32 Tmp;
	if (o->oAction==0){
		if (obj_check_if_collided_with_object(o,gMarioObject)){
			set_mario_action(gMarioState,ACT_DOUBLE_JUMP,0);
			gMarioStates[0].faceAngle[1]=o->oFaceAngleYaw;
			CarmackMeme = * (u32 *) &Yspd;
			Tmp=CarmackMeme+(o->oBehParams2ndByte<<16);
			gMarioStates[0].forwardVel=*(f32 *) &Tmp;
			CarmackMeme+=(((o->oBehParams>>24)&0xFF)<<16);
			bounce_off_object(gMarioState,o,*(f32 *) &CarmackMeme);
			gMarioStates[0].vel[1]=*(f32 *) &CarmackMeme; //?? Redundant but somehow necessary??
			o->oAction=1;
			gMarioStates[0].SelFallDmg=1;
		}
	}else{
		if (o->oTimer==15){
			o->oAction=0;
		}
	}
}
