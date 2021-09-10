#include "macros.inc"

.section .data

glabel gSoundDataADSR
#ifdef EXTERNAL_DATA
.ascii  "sound/sound_data.ctl"
#else
.incbin "sound/sound_data.ctl"
#endif
.balign 16

glabel gSoundDataRaw
#ifdef EXTERNAL_DATA
.ascii  "sound/sound_data.tbl"
#else
.incbin "sound/sound_data.tbl"
#endif
.balign 16

glabel gMusicData
#ifdef EXTERNAL_DATA
.ascii  "sound/sequences.bin"
#else
.incbin "sound/sequences.bin"
#endif
.balign 16

#ifndef VERSION_SH
glabel gBankSetsData
#ifdef EXTERNAL_DATA
.ascii  "sound/bank_sets"
#else
.incbin "sound/bank_sets"
#endif
.balign 16
#endif 
