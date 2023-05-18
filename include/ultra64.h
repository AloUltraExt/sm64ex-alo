#ifndef _ULTRA64_H_
#define _ULTRA64_H_

/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/**************************************************************************
 *
 *  $Revision: 1.10 $
 *  $Date: 1997/02/11 08:37:33 $
 *  $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/ultra64.h,v $
 *
 **************************************************************************/

#ifndef TARGET_N64
#include <math.h>
#endif

#include <PR/ultratypes.h>
#include <PR/rcp.h>
#include <PR/os.h>
#include <PR/sptask.h>
#include <PR/mbi.h>
#include <PR/libaudio.h>
#include <PR/gu.h>
#include <PR/ucode.h>

#if defined(__MINGW32__)
#include <_mingw.h>
#if !defined(__MINGW64_VERSION_MAJOR)
#include <string.h>
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))
#endif
#endif

#endif
