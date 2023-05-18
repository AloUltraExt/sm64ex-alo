#ifndef _GU_H_
#define _GU_H_

/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/**************************************************************************
 *
 *  $Revision: 1.48 $
 *  $Date: 1999/07/13 08:00:20 $
 *  $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/gu.h,v $
 *
 **************************************************************************/

#include <PR/mbi.h>
#include <PR/ultratypes.h>
#include <PR/sptask.h>

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#define M_PI		3.14159265358979323846

#define GU_PI       3.1415926

#define	FTOFIX32(x)	(long)((x) * (float)0x00010000)
#ifdef AVOID_UB
#define	FIX32TOF(x)	((float)(x) * (1.0f / (float)0x00010000))
#else
#define	FIX32TOF(x)	(x / (float)0x00010000)
#endif
#define	FTOFRAC8(x)	((int) MIN(((x) * (128.0f)), 127.0f) & 0xff)

#define  FILTER_WRAP 0
#define  FILTER_CLAMP 1

/* 
 * matrix operations:
 *
 * The 'F' version is floating point, in case the application wants
 * to do matrix manipulations and convert to fixed-point at the last
 * minute.
 */
extern void guMtxIdent(Mtx *m);
extern void guMtxIdentF(float mf[4][4]);
extern void guOrtho(Mtx *m, float l, float r, float b, float t, 
		    float n, float f, float scale);
extern void guOrthoF(float mf[4][4], float l, float r, float b, float t, 
		     float n, float f, float scale);
extern void guPerspective(Mtx *m, u16 *perspNorm, float fovy, 
			  float aspect, float near, float far, float scale);
extern void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, 
			   float aspect, float near, float far, float scale);
extern void guRotate(Mtx *m, float a, float x, float y, float z);
extern void guRotateF(float mf[4][4], float a, float x, float y, float z);
extern void guScale(Mtx *m, float x, float y, float z);
extern void guScaleF(float mf[4][4], float x, float y, float z);
extern void guTranslate(Mtx *m, float x, float y, float z);
extern void guTranslateF(float mf[4][4], float x, float y, float z);
extern void guMtxF2L(float mf[4][4], Mtx *m);
extern void guMtxL2F(float mf[4][4], Mtx *m);

/* vector utility: */
extern void guNormalize(float *x, float *y, float *z);

/* Used only in Fast3DEX2 */
extern void guLookAtReflect(Mtx *m, LookAt *l,
			float xEye, float yEye, float zEye,
			float xAt,  float yAt,  float zAt,
			float xUp,  float yUp,  float zUp);
extern void guLookAtReflectF(float mf[4][4], LookAt *l, 
		      float xEye, float yEye, float zEye,
		      float xAt,  float yAt,  float zAt,
		      float xUp,  float yUp,  float zUp);

/*
 *  Math functions
 */
extern float sinf(float);
extern double sin(double);
extern float cosf(float);
extern double cos(double);

extern float sqrtf(float);

#endif /* !_GU_H_ */
