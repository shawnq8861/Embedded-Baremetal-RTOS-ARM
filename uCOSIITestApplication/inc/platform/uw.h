/*++
Copyright (c) 2000  University of Washington Extensions

Module Name:

    uw.h

Module Description:

    Master include file used with all projects.

Author:

    Richard Chinn 31-December-2000

Revision History:

--*/

#ifndef __UW_H__
#define __UW_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>


//
// Miscellaneous Helpful Macros
//

#define min(x,y)        (((x) < (y)) ? (x) : (y))
#define max(x,y)        (((x) > (y)) ? (x) : (y))

#define HIBYTE(w)       (((w) >> 8) & 0xFF)
#define LOBYTE(w)       ((w) & 0xFF)

#define HIWORD(l)       (((l) >> 16) & 0xFFFF)
#define LOWORD(l)       ((l) & 0xFFFF)

#define ARRAY_SIZE(a)   (sizeof(a)/sizeof((a)[0]))

//
// Defines for IN and OUT.  These are used to annotate parameter lists.
//

#define IN
#define OUT

//
// Additional typedefs.
//

typedef uint8_t bool, boolean;


/* Function pointer type */
typedef void (*pfunction_t)(void);


#endif /* __UW_H__ */
