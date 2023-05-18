/**************************************************************************
 *									  *
 *		 Copyright (C) 1995, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)
        
        $RCSfile: os_internal_vi.h,v $
        $Revision: 1.1 $
        $Date: 1998/10/09 08:01:13 $
 *---------------------------------------------------------------------*/

#ifndef _OS_INTERNAL_VI_H_
#define	_OS_INTERNAL_VI_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/os.h>

/**************************************************************************
 *
 * Global definitions
 *
 */

/*
 * Video Interface (VI) states
 */
#define VI_STATE_MODE_UPDATED 0x01
#define VI_STATE_XSCALE_UPDATED 0x02
#define VI_STATE_YSCALE_UPDATED 0x04
#define VI_STATE_CTRL_UPDATED 0x08   // related to control regs changing
#define VI_STATE_BUFFER_UPDATED 0x10 // swap buffer
#define VI_STATE_BLACK 0x20          // probably related to a black screen
#define VI_STATE_REPEATLINE 0x40     // repeat line?
#define VI_STATE_FADE 0x80           // fade

/*
 * Video Interface (VI) masks
 */
#define VI_SCALE_MASK 0xfff //see rcp scale_x/scale_y
#define VI_2_10_FPART_MASK 0x3ff
#define VI_SUBPIXEL_SH 0x10

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/*
 * Structure for VI context
 */
 
typedef struct {
    /* 0x0 */ f32 factor;
    /* 0x4 */ u16 offset;
    /* 0x8 */ u32 scale;
} __OSViScale;

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void* framep;
    /* 0x08 */ OSViMode *modep;
    /* 0x0c */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg *msg;
    /* 0x18 */ __OSViScale x;
    /* 0x24 */ __OSViScale y;
} __OSViContext;

/* Video interface (Vi) */

extern __OSViContext *__osViGetCurrentContext(void);
extern void __osViSwapContext(void);
extern void __osViInit(void);

extern __OSViContext *__osViNext;
extern __OSViContext *__osViCurr;

extern u32 __additional_scanline;

#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_INTERNAL_VI_H */
