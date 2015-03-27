/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = erealo :                                             */
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

extern _HEADER _XYA *_freeptr;                                          /* C V80#4.17 */

extern VOID _XYA *_malloc(size_t);                         /* C S70001SP * C V80#4.17 */
extern void _free(VOID _XYA *) ;                           /* C S70001SP * C V80#4.17 */
extern VOID _XYA *memset(VOID _XYA *, int, size_t);                     /* C V80#4.17 */
extern VOID _XYA *memcpy(VOID _XYA *, const VOID _XYA *, size_t);       /* C V80#4.17 */
extern VOID _XYA *realloc(VOID _XYA *, size_t) ;                        /* C V80#4.17 */
extern VOID _XYA *_realloc(VOID _XYA *, size_t) ;          /* A S70001SP * C V80#4.17 */
