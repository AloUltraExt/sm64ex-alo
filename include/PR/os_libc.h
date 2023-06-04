
/*====================================================================
 * os_libc.h
 *
 * Copyright 1995, Silicon Graphics, Inc.
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

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)
        
        $RCSfile: os_libc.h,v $
        $Revision: 1.3 $
        $Date: 1999/07/13 01:43:47 $
 *---------------------------------------------------------------------*/

#ifndef _OS_LIBC_H_
#define	_OS_LIBC_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Type definitions
 *
 */


#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

/**************************************************************************
 *
 * Global definitions
 *
 */


#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Macro definitions
 *
 */


/**************************************************************************
 *
 * Extern variables
 *
 */


/**************************************************************************
 *
 * Function prototypes
 *
 */

/* byte string operations */

// old bstring functions that aren't present on some platforms

#if defined(__APPLE__) || defined(__ANDROID__) || defined(__HAIKU__)

// macOS libc has them
#include <strings.h>

#elif defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200809L) || defined(NO_BZERO_BCOPY)

// They don't exist so better use memcpy/memset
#include <string.h>
#undef bzero
#undef bcopy
#define bzero(buf, len) memset((buf), 0, (len))
#define bcopy(src, dst, len) memcpy((dst), (src), (len))

#else

// hope for the best
extern void     bcopy(const void *, void *, size_t);
extern void     bzero(void *, size_t);
#endif

/* Printf */

#ifdef TARGET_N64
extern int		sprintf(char *s, const char *fmt, ...);
extern void		osSyncPrintf(const char *fmt, ...);
#endif

#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_LIBC_H_ */
