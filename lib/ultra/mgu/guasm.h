/************************************************************************
 Copyright (C) 1998,1999 NINTENDO CO,Ltd,
 Copyright (C) 1998,1999 MONEGI CORPORATION,
    All Rights Reserved
This program is a trade secret of NINTENDO CO,Ltd and MONEGI Corp.
and it is not to be reproduced, published, disclosed to others, copied,
adapted, distributed, or displayed without the prior authorization of
NINTENDO CO,Ltd. and MONEGI Corp. Licensee agrees to attach or embed
this Notice on all copies of the program, including partial copies or
modified versions thereof.
*************************************************************************/
/************************************************************************
 $Date: 1999/06/16 09:15:38 $
 $Revision: 1.1 $
 $Author: doseki $
************************************************************************/

#include "PR/os_version.h"
#include "sys/asm.h"
#include "sys/regdef.h"

#define    HALF_SIZE_MTX    32
#define    SIZE_OF_MTX        64    /* sizeof( Mtx ) */
#define FLOAT_0x10000    6.5536e+04    /* (float)0x00010000) */

/*
 * FTOFIX32 (float to fix32)
 * a:    input
 * t:    output
 * ft0 : (float)0x00010000
 * ft1, ft2, ft3, t0 :    work reg
 */
#define FTOFIX32(a, t)    \
    mtc1        a, ft1        ;    \
    mul.s        ft2, ft1, ft0    ;    \
    trunc.w.s    ft3, ft2, t0    ;    \
    mfc1        t, ft3        ;
