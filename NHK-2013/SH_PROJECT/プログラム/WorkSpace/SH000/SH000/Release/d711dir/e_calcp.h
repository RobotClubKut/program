/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_calcp :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

#ifndef _REENTRANT                              /* A S70003P */
extern volatile int  _errno;                       /* A S40008SP */
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P */

extern void *memset(void *, int, size_t);
extern INT    _lsfts(UCHAR*, INT, SHORT);
extern void *memcpy(void *, const void *, size_t);
extern VOID   _power(INT, SHORT*, UCHAR*);
extern VOID   _mult64(SHORT*, UCHAR*, SHORT, UCHAR*);
extern VOID   _div64(SHORT*, UCHAR*, SHORT, UCHAR*); /*  V.1.1  A  T11001V */
extern VOID   _setsbit(UCHAR*, INT, INT);
/* extern double _pack(SHORT, UCHAR*);                  D S40001SP */
extern long double  _packx(SHORT, UCHAR*);           /* C S40001SP */
extern float  _packf(SHORT, UCHAR*);
extern long double  _calcxpow(UCHAR*, INT, CHAR);  /* C S40001SP  C S40008SP */
extern float  _calcfpow(UCHAR*, INT, CHAR);                    /* C S40008SP */
                                                     /* D S01001SP */
extern INT    _lsft(UCHAR*, INT);                    /* A S40008SP */
extern int    _rsft(UCHAR*, INT);                    /* A S40008SP */
extern int    _rnd(UCHAR*, INT);                     /* A S40008SP */
