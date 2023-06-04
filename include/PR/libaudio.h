/*====================================================================
 * libaudio.h
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

/**************************************************************************
 *
 *  $Revision: 1.173 $
 *  $Date: 1997/12/01 12:42:21 $
 *  $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/libaudio.h,v $
 *
 **************************************************************************/

#ifndef __LIB_AUDIO__
#define __LIB_AUDIO__

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>
#include <PR/mbi.h>

/***********************************************************************
 * misc defines
 ***********************************************************************/

typedef s32     ALMicroTime;
typedef u8      ALPan;

/***********************************************************************
 * Error handling
 ***********************************************************************/

#ifdef _DEBUG
#define ALFailIf(condition, error)	\
            if (condition) {		\
                __osError(error, 0);	\
                return; }

#else
#define ALFailIf(condition, error)	\
            if (condition) {		\
                return; }
#endif

#ifdef _DEBUG
#define ALFlagFailIf(condition, flag, error)	\
            if (condition) {		\
                if(flag) __osError(error, 0);	\
                return; }

#else
#define ALFlagFailIf(condition, flag, error)	\
            if (condition) {		\
                return; }
#endif

/***********************************************************************
 * Macros
 ***********************************************************************/

#define ALBnkfPatch(src, base, type) (type)((uintptr_t) src + (uintptr_t) base)

/***********************************************************************
 * data structures for sound banks
 ***********************************************************************/

#define AL_BANK_VERSION 0x4231 /* 'B1' */

/* Possible wavetable types */
enum    {AL_ADPCM_WAVE = 0,
         AL_RAW16_WAVE};

typedef struct {
    s32 order;
    s32 npredictors;
    s16 book[1];        /* Actually variable size. Must be 8-byte aligned */
} ALADPCMBook;

typedef struct {
    u32         start;
    u32         end;
    u32         count;
    ADPCM_STATE state;
} ALADPCMloop;

typedef struct {
    u32         start;
    u32         end;
    u32         count;
} ALRawLoop;

typedef struct {
    ALMicroTime attackTime;
    ALMicroTime decayTime;
    ALMicroTime releaseTime;
    u8          attackVolume;
    u8          decayVolume;
} ALEnvelope;

typedef struct {
    u8          velocityMin;
    u8          velocityMax;
    u8          keyMin;
    u8          keyMax;
    u8          keyBase;
    s8          detune;
} ALKeyMap;

typedef struct {
    ALADPCMloop *loop;
    ALADPCMBook *book;
} ALADPCMWaveInfo;

typedef struct {
    ALRawLoop *loop;
} ALRAWWaveInfo;

typedef struct ALWaveTable_s {
    u8          *base;          /* ptr to start of wave data    */
    s32         len;            /* length of data in bytes      */
    u8          type;           /* compression type             */
    u8          flags;          /* offset/address flags         */
    union {
        ALADPCMWaveInfo adpcmWave;
        ALRAWWaveInfo   rawWave;
    } waveInfo;
} ALWaveTable;

typedef struct ALSound_s {
    ALEnvelope  *envelope;
    ALKeyMap    *keyMap;
    ALWaveTable *wavetable;     /* offset to wavetable struct           */
    ALPan       samplePan;
    u8          sampleVolume;
    u8          flags;
} ALSound;

typedef struct {
    u8          volume;         /* overall volume for this instrument   */
    ALPan       pan;            /* 0 = hard left, 127 = hard right      */
    u8          priority;       /* voice priority for this instrument   */
    u8          flags;
    u8          tremType;       /* the type of tremelo osc. to use      */
    u8          tremRate;       /* the rate of the tremelo osc.         */
    u8          tremDepth;      /* the depth of the tremelo osc         */
    u8          tremDelay;      /* the delay for the tremelo osc        */
    u8          vibType;        /* the type of tremelo osc. to use      */
    u8          vibRate;        /* the rate of the tremelo osc.         */
    u8          vibDepth;       /* the depth of the tremelo osc         */
    u8          vibDelay;       /* the delay for the tremelo osc        */
    s16         bendRange;      /* pitch bend range in cents            */
    s16         soundCount;     /* number of sounds in this array       */
    ALSound     *soundArray[1];
} ALInstrument;

typedef struct ALBank_s {
    s16                 instCount;      /* number of programs in this bank */
    u8                  flags;
    u8                  pad;
    s32                 sampleRate;     /* e.g. 44100, 22050, etc...       */
    ALInstrument        *percussion;    /* default percussion for GM       */
    ALInstrument        *instArray[1];  /* ARRAY of instruments            */
} ALBank;

typedef struct {                /* Note: sizeof won't be correct        */
    s16         revision;       /* format revision of this file         */
    s16         bankCount;      /* number of banks                      */
    ALBank      *bankArray[1];  /* ARRAY of bank offsets                */
} ALBankFile;

void alBnkfNew(ALBankFile *f, u8 *table);

/***********************************************************************
 * Sequence Files
 ***********************************************************************/

typedef struct
{
    u8 *offset;
    s32 len;
#if defined(VERSION_SH) || defined(VERSION_CN)
    s8 medium;
    s8 magic; // tbl: 0x04, otherwise: 0x03

    // for ctl (else zeros):
    union {
        // unused, just for clarification (big endian)
        struct {
            u8 bank;
            u8 ff;
            u8 numInstruments;
            u8 numDrums;
        } as_u8;

        // used
        struct {
            s16 bankAndFf;
            s16 numInstrumentsAndDrums;
        } as_s16;
    } ctl;
#endif
} ALSeqData;

typedef struct
{
#if !defined(VERSION_SH) && !defined(VERSION_CN)
    s16 revision;
#endif
    s16 seqCount;
#if defined(VERSION_SH) || defined(VERSION_CN)
    s16 unk2;
    u8 *data;
#if !IS_64_BIT
    s32 pad[2];
#endif
#endif
    ALSeqData seqArray[1];
} ALSeqFile;

void alSeqFileNew(ALSeqFile *f, u8 *base);

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif
