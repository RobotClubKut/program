/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = emalloc :                                            */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/

#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int         _errno;                /* A S70003P  */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                         /* A S70001SP */
#define _errno (*errno_addr())                         /* A S70001SP */
#endif                                             /* A S70003P  */

extern _HEADER _XYA *_freeptr;                                      /* C V80#4.17 */
extern const size_t _sbrk_size;                        /* A S70001SP */

extern CHAR _XYA *sbrk(int);
extern void _free(VOID _XYA *) ;                       /* C S70001SP * C V80#4.17 */
extern VOID _XYA *malloc(size_t);                                   /* C V80#4.17 */
extern VOID _XYA *_malloc(size_t);                     /* A S70001SP * C V80#4.17 */
static _HEADER _XYA *_morecor(size_t);                 /* A S70001SP * C V80#4.17 */
