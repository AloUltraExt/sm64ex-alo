// TODO: WIP, doesn't work
void bhv_jukebox_loop(void) {
    u8 minMusic = (u8) o->oBehParams >> 24;
    u8 maxMusic = (u8) o->oBehParams >> 16;
    
    u8 playMusic;

    if (o->oDistanceToMario < 300.0f) {
        if (minMusic <= playMusic && playMusic >= maxMusic) {
            playMusic = minMusic;
            
            if (gPlayer1Controller->buttonPressed & L_JPAD) {
                playMusic++;
            }
            
            if (gPlayer1Controller->buttonPressed & R_JPAD) {
                playMusic--;
            }
            
            stop_background_music(SEQUENCE_ARGS(4, playMusic));
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, playMusic), 0);
        }
	}
}
