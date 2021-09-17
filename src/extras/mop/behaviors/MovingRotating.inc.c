#define ZPLUS 0
#define ZMINUS 1
#define XPLUS 2
#define XMINUS 3
#define LOOP 4

static u8 MoveRotatePath1[] = {
    ZPLUS,
    XPLUS,
    ZMINUS,
    XMINUS,
    LOOP
};

static u8 MoveRotatePath2[] = {
    ZPLUS,
    ZPLUS,
    ZPLUS,
    ZMINUS,
    ZMINUS,
    ZMINUS,
    LOOP
};

static u8 MoveRotatePath3[] = {
    XPLUS,
    XPLUS,
    XPLUS,
    XMINUS,
    XMINUS,
    XMINUS,
    LOOP
};

static u8 *Paths[] = {
	MoveRotatePath1,
	MoveRotatePath2,
	MoveRotatePath3
};

//speeds are 8 in each dir
//red is bparam1 =1, offset timer by 0x80 on frame 1
//rotates every 0x110 frames aka ~9s or 272 frames
//rotate for pitch vel of 0x0400 for 0x20 frames
//advanced forward a direction every 0x3C frames

void bhv_move_rotate_init(void) {
	o->oTimer+=0x80*(o->oBehParams>>24);
	o->oAnimState=(o->oBehParams>>24);
}

#define PLAT_SPEED 8

void bhv_move_rotate_loop(void) {
	u8 Direction;
	if (o->oTimer==0x110){
		o->oAngleVelPitch+=0x400;
	}else if (o->oTimer==0x130){
		o->oAngleVelPitch=0;
		o->oTimer=0;
	}
	Direction = Paths[o->oBehParams2ndByte][o->oMopMovingRotatingPath];
	switch(Direction){
		case ZPLUS:
			o->oMopMovingRotatingTimer++;
			o->oVelZ = PLAT_SPEED;
			o->oVelX = 0;
			break;
		
		case ZMINUS:
			o->oMopMovingRotatingTimer++;
			o->oVelZ = -PLAT_SPEED;
			o->oVelX = 0;
			break;
		
		case XPLUS:
			o->oMopMovingRotatingTimer++;
			o->oVelX = PLAT_SPEED;
			o->oVelZ = 0;
			break;

		case XMINUS:
			o->oMopMovingRotatingTimer++;
			o->oVelX = -PLAT_SPEED;
			o->oVelZ = 0;
			break;
		
		default:
			o->oMopMovingRotatingPath=0;
			break;
	}
	if (o->oMopMovingRotatingTimer == 60){
		o->oMopMovingRotatingPath++;
		o->oMopMovingRotatingTimer=0;
	}
	cur_obj_rotate_face_angle_using_vel();
	cur_obj_move_using_vel();
}
