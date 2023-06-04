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

#include "guint.h"

void guRotateF(float mf[4][4], float a, float x, float y, float z)
{
	static float	dtor = GU_PI / 180.0;
	float	sine;
	float	cosine;
	float	ab, bc, ca, t;
#if LIBULTRA_VERSION >= OS_VER_I
    float xxsine, yxsine, zxsine;
/* 2.0I onwards replaced these to t to reduce variables */
#define xx t
#define yy t
#define zz t
#else
    f32 xx, yy, zz;
#endif

	guNormalize(&x, &y, &z);
	a *= dtor;
	sine = sinf(a);
	cosine = cosf(a);
	t = (1-cosine);
	ab = x*y*t;
	bc = y*z*t;
	ca = z*x*t;

	guMtxIdentF(mf);

/* Slight optimization */
#if LIBULTRA_VERSION >= OS_VER_K
#define MULT(s, p, t) s = p*sine; t = p*p;
#define MTX_ADD(c, p, s) c+s;
#define MTX_SUB(c, p, s) c-s;
#else
#define MULT(s, p, t) t = p*p;
#define MTX_ADD(c, p, s) c+(p*sine);
#define MTX_SUB(c, p, s) c-(p*sine);
#endif

    MULT(xxsine, x, xx);
    mf[0][0] = xx+cosine*(1-xx);
    mf[2][1] = MTX_SUB(bc, x, xxsine);
    mf[1][2] = MTX_ADD(bc, x, xxsine);

    MULT(yxsine, y, yy);
    mf[1][1] = yy+cosine*(1-yy);
    mf[2][0] = MTX_ADD(ca, y, yxsine);
    mf[0][2] = MTX_SUB(ca, y, yxsine);

    MULT(zxsine, z, zz);
    mf[2][2] = zz+cosine*(1-zz);
    mf[1][0] = MTX_SUB(ab, z, zxsine);
    mf[0][1] = MTX_ADD(ab, z, zxsine);
}

void guRotate(Mtx *m, float a, float x, float y, float z)
{
	Matrix	mf;

	guRotateF(mf, a, x, y, z);

	guMtxF2L(mf, m);
}
