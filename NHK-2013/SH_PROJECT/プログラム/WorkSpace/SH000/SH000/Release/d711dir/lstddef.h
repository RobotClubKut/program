/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = stddef :                                                    */
/*                                                                     */
/*  FUNC = this module do the following functions                      */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef int ptrdiff_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#ifndef  NULL
#define  NULL           ((void *)0)
#endif

#ifndef  offsetof
#define  offsetof(type,id) ((char *)(&(((type *)NULL)->id))  -    \
                            (char *)((type *)NULL))
#endif

#ifndef  errno
#ifndef _REENTRANT                              /* A S70003P */
#define  errno          _errno
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* A S70001SP */
#define  errno          (*errno_addr())            /* A S70001SP */
#endif                                             /* A S70003P */
#endif
