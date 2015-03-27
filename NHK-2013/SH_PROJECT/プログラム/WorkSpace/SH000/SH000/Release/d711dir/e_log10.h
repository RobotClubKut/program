/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = eh2lfun :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

extern int    _duchek(long double);    /* C S40001SP  C S01001SP */
extern INT    _lsft(UCHAR*, INT);                  /* C S01001SP */
extern int    _log10(long double);     /* C S40001SP  C S01001SP */
#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int _errno;                        /* C S01001SP */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P  */
