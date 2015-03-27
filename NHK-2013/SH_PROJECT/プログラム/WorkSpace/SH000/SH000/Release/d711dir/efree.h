/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = efree :                                              */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

#ifndef _REENTRANT                                 /* A S70003P  */
extern volatile int         _errno;                /* A S70003P  */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                         /* A S70001SP */
#define _errno (*errno_addr())                         /* A S70001SP */
#endif                                             /* A S70003P  */

extern _HEADER _XYA *_freeptr;                                      /* C V80#4.17 */

extern void free(VOID _XYA *) ;                                     /* C V80#4.17 */
extern void _free(VOID _XYA *) ;                       /* A S70001SP * C V80#4.17 */

