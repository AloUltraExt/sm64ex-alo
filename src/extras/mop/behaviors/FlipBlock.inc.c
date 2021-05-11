
static struct ObjectHitbox sFlipBlockHitbox = {
    /* interactType: */ INTERACT_BREAKABLE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 0,
    /* health: */ 0,
    /* numLootCoins: */ 0,
    /* radius: */ 64,
    /* height: */ 64,
    /* hurtboxRadius: */ 0,
    /* hurtboxHeight: */ 0,
};

#define FLIP_TIMER 210

void bhv_flip_block_loop(void) {
    if (o->oTimer == 0 && o->oAction==0){
        obj_set_hitbox(o, &sBreakableBoxHitbox);
		o->oAction=1;
	}
	//flipping
	if (o->oAction==2){
		//a guess
		if (o->oTimer==FLIP_TIMER){
			o->oAction=1;
			o->oSubAction=0;
		}
		o->oFaceAnglePitch+=(FLIP_TIMER-o->oTimer)*16;
		if (((o->oFaceAnglePitch/0x8000) - o->oSubAction)>0){
			cur_obj_play_sound_1(SOUND_GENERAL_SWISH_WATER);
			o->oSubAction+=1;
		}
	}else{
		if (cur_obj_was_attacked_or_ground_pounded() != 0) {
			o->oAction=2;
			o->oIntangibleTimer=FLIP_TIMER;
			o->header.gfx.scale[2]=0.1f;
			cur_obj_play_sound_1(SOUND_GENERAL_SWISH_WATER);
		}else{
			o->oFaceAnglePitch=0;
			o->header.gfx.scale[2]=1.0f;
			load_object_collision_model();
		}
	}
}
