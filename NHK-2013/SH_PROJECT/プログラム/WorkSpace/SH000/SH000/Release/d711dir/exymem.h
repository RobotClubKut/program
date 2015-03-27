/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*  NAME = exymem : X/Y memory                                   */
/*  FUNC = this header file do the following functions;          */
/*  (1) macro define;                                            */
/*                                                               */
/*  CLAS = UNIT;                                                 */
/* END ;                                                         */
/*****************************************************************/

#ifndef EXYMEM_H
#define EXYMEM_H

#ifndef _XYA
#define _XYA
#endif

#ifndef _XYB
#define _XYB
#endif

#define NULL_XYA    ((void _XYA *)0)
#define NULL_XYB    ((void _XYB *)0)

/*  concat symbol name */
#define IT(a)               a
#define MAKE_NAME1(name)    IT(name)IT(_XYA)
#define MAKE_NAME2(name)    IT(name)IT(_XYA)IT(_XYB)

/* malloc, realloc, free, calloc, ... */
#define _HEADER             MAKE_NAME1(_HEADER)
#define _header             MAKE_NAME1(_header)
#define malloc              MAKE_NAME1(malloc)
#define _malloc             MAKE_NAME1(_malloc)
#define realloc             MAKE_NAME1(realloc)
#define _realloc            MAKE_NAME1(_realloc)
#define free                MAKE_NAME1(free)
#define _free               MAKE_NAME1(_free)
#define calloc              MAKE_NAME1(calloc)
#define _morecor            MAKE_NAME1(_morecor)
#define _freeptr            MAKE_NAME1(_freeptr)
#define _sbrk_size          MAKE_NAME1(_sbrk_size)
#define sbrk                MAKE_NAME1(sbrk)
#define memset              MAKE_NAME1(memset)

/* memcpy, memmove, ... */
#define memcpy              MAKE_NAME2(memcpy)
#define memcpy1             MAKE_NAME2(memcpy1)
#define memmove             MAKE_NAME2(memmove)
#define memmove_old         MAKE_NAME2(memmove_old)
#define memMOVE1            MAKE_NAME2(memMOVE1)
#define moveLong            MAKE_NAME2(moveLong)
#define moveLong1           MAKE_NAME2(moveLong1)
#define moveChar1           MAKE_NAME2(moveChar1)
#define moveLongReverse     MAKE_NAME2(moveLongReverse)
#define moveLong1Reverse    MAKE_NAME2(moveLong1Reverse)
#define moveChar1Reverse    MAKE_NAME2(moveChar1Reverse)
/*---------------------------------------------------------------*/

#endif  /* EXYMEM_H */

