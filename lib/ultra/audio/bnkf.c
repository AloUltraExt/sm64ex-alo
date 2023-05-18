#include "PR/os_internal.h"
#include "PR/libaudio.h"

static void _bnkfPatchBank(ALBank *bank, s32 offset, s32 table);
static void _bnkfPatchInst(ALInstrument *i, s32 offset, s32 table);
static void _bnkfPatchSound(ALSound *s, s32 offset, s32 table);
static void _bnkfPatchWaveTable(ALWaveTable *w, s32 offset, s32 table);

void alSeqFileNew(ALSeqFile *file, u8 *base)
{
    s32 offset = (intptr_t) base;
    s32 i;

    /*
     * patch the file so that offsets are pointers
     */
    for (i = 0; i < file->seqCount; i++) {
        file->seqArray[i].offset = ALBnkfPatch(file->seqArray[i].offset, offset, u8 *);
    }
}

void alBnkfNew(ALBankFile *file, u8 *table)
{
    s32 offset = (intptr_t) file;
    s32 woffset = (intptr_t) table;

    s32 i;

    /*
     * check the file format revision in debug libraries
     */
    ALFailIf(file->revision != AL_BANK_VERSION, ERR_ALBNKFNEW);

    /*
     * patch the file so that offsets are pointers
     */
    for (i = 0; i < file->bankCount; i++) {
        file->bankArray[i] = ALBnkfPatch(file->bankArray[i], offset, ALBank *);
        if(file->bankArray[i])
            _bnkfPatchBank(file->bankArray[i], offset, woffset);
    }
}

void _bnkfPatchBank(ALBank *bank, s32 offset, s32 table)
{
    s32 i;

    if (bank->flags)
        return;

    bank->flags = 1;

    if (bank->percussion) {
        bank->percussion = ALBnkfPatch(bank->percussion, offset, ALInstrument *);
        _bnkfPatchInst(bank->percussion, offset, table);
    }

    for (i = 0; i < bank->instCount; i++) {
        bank->instArray[i] = ALBnkfPatch(bank->instArray[i], offset, ALInstrument *);
        if(bank->instArray[i])
            _bnkfPatchInst(bank->instArray[i], offset, table);
    }
}

void _bnkfPatchInst(ALInstrument *inst, s32 offset, s32 table)
{
    s32 i;

    if (inst->flags)
        return;

    inst->flags = 1;

    for (i = 0; i < inst->soundCount; i++) {
        inst->soundArray[i] = ALBnkfPatch(inst->soundArray[i], offset, ALSound *);
        _bnkfPatchSound(inst->soundArray[i], offset, table);

    }
}

void _bnkfPatchSound(ALSound *s, s32 offset, s32 table)
{
    if (s->flags)
        return;

    s->flags = 1;

    s->envelope  = ALBnkfPatch(s->envelope, offset, ALEnvelope *);
    s->keyMap    = ALBnkfPatch(s->keyMap, offset, ALKeyMap *);

    s->wavetable = ALBnkfPatch(s->wavetable, offset, ALWaveTable *);
    _bnkfPatchWaveTable(s->wavetable, offset, table);
}

void _bnkfPatchWaveTable(ALWaveTable *w, s32 offset, s32 table)
{
    if (w->flags)
        return;

    w->flags = 1;

    w->base += table;

    /* sct 2/14/96 - patch wavetable loop info based on type. */
    if (w->type == AL_ADPCM_WAVE)
    {
	w->waveInfo.adpcmWave.book  = ALBnkfPatch(w->waveInfo.adpcmWave.book, offset, ALADPCMBook *);
	if (w->waveInfo.adpcmWave.loop)
	    w->waveInfo.adpcmWave.loop = ALBnkfPatch(w->waveInfo.adpcmWave.loop, offset, ALADPCMloop *);
    }
    else if (w->type == AL_RAW16_WAVE)
    {
	if (w->waveInfo.rawWave.loop)
	    w->waveInfo.rawWave.loop = ALBnkfPatch(w->waveInfo.rawWave.loop, offset, ALRawLoop *);
    }
}
