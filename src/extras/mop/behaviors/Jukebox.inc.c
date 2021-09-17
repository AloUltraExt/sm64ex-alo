void set_background_music(u16 a, u16 seqArgs, s16 fadeTimer);

void bhv_jukebox_loop(void) {
    u8 currMusic;

    o->oMopJukeboxChangeMusic = FALSE;

    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        if (o->oAction == 0) {
            currMusic = ((o->oBehParams >> 24) & 0xFF); // bp1
            o->oAction = (s32) currMusic;
            set_background_music(0, currMusic, 0);
        }

        o->oMopJukeboxIndexMusic = o->oAction;

        if (gPlayer1Controller->buttonPressed & R_JPAD) {
            o->oMopJukeboxIndexMusic++;
            o->oMopJukeboxChangeMusic = TRUE;
        }

        if (gPlayer1Controller->buttonPressed & L_JPAD) {
            o->oMopJukeboxIndexMusic--;
            o->oMopJukeboxChangeMusic = TRUE;
        }

        if (o->oMopJukeboxIndexMusic > o->oBehParams2ndByte) {
            o->oMopJukeboxIndexMusic = o->oBehParams2ndByte;
            o->oMopJukeboxChangeMusic = FALSE;
        }

        if (o->oMopJukeboxIndexMusic < ((o->oBehParams >> 24) & 0xFF)) { // bp1
            o->oMopJukeboxIndexMusic = ((o->oBehParams >> 24) & 0xFF);
            o->oMopJukeboxChangeMusic = FALSE;
        }

        if (o->oMopJukeboxChangeMusic) {
            o->oAction = o->oMopJukeboxIndexMusic;
            set_background_music(0, o->oAction, 0);
            o->oMopJukeboxChangeMusic = FALSE;
        }
    }
}
