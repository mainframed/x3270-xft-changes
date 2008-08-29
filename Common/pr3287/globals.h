/*              
 * Copyright 2000, 2004, 2007, 2007 by Paul Mattes.
 *  Permission to use, copy, modify, and distribute this software and its
 *  documentation for any purpose and without fee is hereby granted,
 *  provided that the above copyright notice appear in all copies and that
 *  both that copyright notice and this permission notice appear in
 *  supporting documentation.
 *
 * pr3287 is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the file LICENSE for more details.
 */

#include <stdio.h>			/* Unix standard I/O library */
#include <stdlib.h>			/* Other Unix library functions */
#include <unistd.h>			/* Unix system calls */
#include <ctype.h>			/* Character classes */
#include <string.h>			/* String manipulations */
#include <sys/types.h>			/* Basic system data types */
#include <sys/time.h>			/* System time-related data types */
#include <time.h>			/* C library time functions */

#include "localdefs.h"

#if defined(__STDC_ISO_10646__) && !defined(USE_ICONV) /*[*/
#define UNICODE_WCHAR   1
#endif /*]*/
#if !defined(_WIN32) && !defined(UNICODE_WCHAR) /*[*/
#include <iconv.h>
#endif /*]*/

#define CN	(char *)NULL

extern unsigned long cgcsgid;
extern unsigned long cgcsgid_dbcs;
extern int dbcs;

#define Replace(var, value) { Free(var); var = (value); }

#if defined(_WIN32) /*[*/
typedef unsigned int ucs4_t;
typedef unsigned short ebc_t;
#else /*][*/
typedef __uint32_t ucs4_t;
typedef __uint16_t ebc_t;
#endif /*]*/

#define CS_MASK		0x03	/* mask for specific character sets */
#define CS_BASE		0x00	/*  base character set (X'00') */
#define CS_APL		0x01	/*  APL character set (X'01' or GE) */
#define CS_LINEDRAW	0x02	/*  DEC line-drawing character set (ANSI) */
#define CS_DBCS		0x03	/*  DBCS character set (X'F8') */
#define CS_GE		0x04	/* cs flag for Graphic Escape */
