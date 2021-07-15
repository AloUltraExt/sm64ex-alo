// TODO: Implement proper distance and RGB values
void bhv_emitter_loop(void) {
    struct Object *sparkle;
	//if (((f32)((o->oBehParams>>24)&0xFF)>o->oDistanceToMario && (gGlobalTimer % 4 == 0))){
    if (gGlobalTimer % 4 == 0){
		sparkle = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
		sparkle->oPosX += random_float() * 150 - 75;
		sparkle->oPosY += random_float() * 50;
		sparkle->oPosZ += random_float() * 150 - 75;
	}
}
