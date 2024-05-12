#include "PR/os_internal.h"
#include "PR/libaudio.h"

static void _bnkfPatchBank(ALBank *bank, ALBankFile *file, s32 table);
static void _bnkfPatchInst(ALInstrument *inst, ALBankFile *file, s32 table);
static void _bnkfPatchSound(ALSound *sound, ALBankFile *file, s32 table);
static void _bnkfPatchWaveTable(ALWaveTable *wvtbl, ALBankFile *file, s32 table);

void alSeqFileNew(ALSeqFile *file, u8 *base)
{
    uintptr_t b = (uintptr_t) base;
    int i;

    /*
     * patch the file so that offsets are pointers
     */
    for (i = 0; i < file->seqCount; i++) {
        file->seqArray[i].offset = ALBnkfPatch(file->seqArray[i].offset, b, u8 *);
    }
}

void alBnkfNew(ALBankFile *file, u8 *table)
{
    uintptr_t t = (uintptr_t) table;
    int i;

    /*
     * check the file format revision in debug libraries
     */
    ALFailIf(file->revision != AL_BANK_VERSION, ERR_ALBNKFNEW);

    /*
     * patch the file so that offsets are pointers
     */
    for (i = 0; i < file->bankCount; i++) {
        file->bankArray[i] = ALBnkfPatch(file->bankArray[i], file, ALBank *);
        if(file->bankArray[i])
            _bnkfPatchBank(file->bankArray[i], file, t);
    }
}

void _bnkfPatchBank(ALBank *bank, ALBankFile *file, s32 table)
{
    int i;

    if (bank->flags)
        return;

    bank->flags = 1;

    if (bank->percussion) {
        bank->percussion = ALBnkfPatch(bank->percussion, file, ALInstrument *);
        _bnkfPatchInst(bank->percussion, file, table);
    }

    for (i = 0; i < bank->instCount; i++) {
        bank->instArray[i] = ALBnkfPatch(bank->instArray[i], file, ALInstrument *);
        if(bank->instArray[i])
            _bnkfPatchInst(bank->instArray[i], file, table);
    }
}

void _bnkfPatchInst(ALInstrument *inst, ALBankFile *file, s32 table)
{
    int i;

    if (inst->flags)
        return;

    inst->flags = 1;

    for (i = 0; i < inst->soundCount; i++) {
        inst->soundArray[i] = ALBnkfPatch(inst->soundArray[i], file, ALSound *);
        _bnkfPatchSound(inst->soundArray[i], file, table);

    }
}

void _bnkfPatchSound(ALSound *sound, ALBankFile *file, s32 table)
{
    if (sound->flags)
        return;

    sound->flags = 1;

    sound->envelope  = ALBnkfPatch(sound->envelope, file, ALEnvelope *);
    sound->keyMap    = ALBnkfPatch(sound->keyMap, file, ALKeyMap *);

    sound->wavetable = ALBnkfPatch(sound->wavetable, file, ALWaveTable *);
    _bnkfPatchWaveTable(sound->wavetable, file, table);
}

void _bnkfPatchWaveTable(ALWaveTable *wvtbl, ALBankFile *file, s32 table)
{
    if (wvtbl->flags)
        return;

    wvtbl->flags = 1;

    wvtbl->base += table;

    /* sct 2/14/96 - patch wavetable loop info based on type. */
    if (wvtbl->type == AL_ADPCM_WAVE)
    {
    wvtbl->waveInfo.adpcmWave.book  = ALBnkfPatch(wvtbl->waveInfo.adpcmWave.book, file, ALADPCMBook *);
    if (wvtbl->waveInfo.adpcmWave.loop)
        wvtbl->waveInfo.adpcmWave.loop = ALBnkfPatch(wvtbl->waveInfo.adpcmWave.loop, file, ALADPCMloop *);
    }
    else if (wvtbl->type == AL_RAW16_WAVE)
    {
    if (wvtbl->waveInfo.rawWave.loop)
        wvtbl->waveInfo.rawWave.loop = ALBnkfPatch(wvtbl->waveInfo.rawWave.loop, file, ALRawLoop *);
    }
}
