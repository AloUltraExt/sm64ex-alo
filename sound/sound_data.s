#include "macros.inc"

.section .data

#ifdef EXTERNAL_DATA
#define SOUND_FILE(file) .ascii file
#define SKIP(num)   .skip num
#else
#define SOUND_FILE(file) .incbin file
#define SKIP(num)
#endif

glabel gSoundDataADSR
SOUND_FILE("sound/sound_data.ctl")
SKIP(4)
.balign 16

glabel gSoundDataRaw
SOUND_FILE("sound/sound_data.tbl")
SKIP(4)
.balign 16

glabel gMusicData
SOUND_FILE("sound/sequences.bin")
SKIP(4)
.balign 16

#ifndef VERSION_SH
glabel gBankSetsData
SOUND_FILE("sound/bank_sets")
SKIP(4)
.balign 16
#endif

#if defined(EXTERNAL_DATA) && defined(VERSION_SH)
glabel gBankSetsData
SOUND_FILE("sound/bank_sets")
SKIP(4)
.balign 16

glabel gShindouSequencesHeader
SOUND_FILE("sound/sequences_header")
SKIP(4)
.balign 16

glabel gShindouSoundBanksHeader
SOUND_FILE("sound/ctl_header")
SKIP(4)
.balign 16

glabel gShindouSampleBanksHeader
SOUND_FILE("sound/tbl_header")
SKIP(4)
.balign 16

#endif
