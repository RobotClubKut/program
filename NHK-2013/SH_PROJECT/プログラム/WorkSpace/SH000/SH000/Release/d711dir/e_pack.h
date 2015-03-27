/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_pack :                                             */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int  _errno;                       /* C S01002SP */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P  */

extern INT    _lsft(UCHAR*, INT);
extern void *memset(void *, int, size_t);
extern int    _rsft(UCHAR*, INT);
extern int    _rnd(UCHAR*, INT);
extern INT    _rsfts(UCHAR*, INT, SHORT);
extern void *memcpy(void *, const void *, size_t);
                                                   /* D S01001SP */
extern long double _packx(SHORT, UCHAR*);          /* C S40001SP */
extern float  _packf(SHORT, UCHAR*);
