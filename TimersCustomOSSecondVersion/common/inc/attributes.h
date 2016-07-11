/*++
Copyright (c) 2010  University of Washington

Module Name:

    attributes_gcc.h

Module Description:

    Include file for compiler specific attributes.

Author:


Revision History:

--*/

#ifndef __ATTRIBUTES_GCC_H__
#define __ATTRIBUTES_GCC_H__


/* Attributes for hardware register struct alignment and packing
 * http://gcc.gnu.org/onlinedocs/gcc/Type-Attributes.html*/
#define ATTR_PACKED_ALIGNED4  __attribute__ ((__packed__,__aligned__(4)))
#define ATTR_PACKED           __attribute__ ((__packed__))


#endif /* __ATTRIBUTES_GCC_H__ */
