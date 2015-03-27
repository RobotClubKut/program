/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_std :                                              */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/


#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int _errno;                        /* C S01002SP */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P  */

extern void *memset(void *, int, size_t);
extern VOID   _calcint(UCHAR*, INT, INT);
extern double _calcpow(UCHAR*, INT);
extern float  _calcfpow(UCHAR*, INT, CHAR);       /* C S40008SP */
extern LDBL   _calcxpow(UCHAR*, INT, CHAR);       /* C S40008SP */
extern float  _stf(INT, CHAR*, INT, CHAR);        /* C S40008SP  C S40013SP */
                                                  /* C S01001SP */
extern double *_std(INT, CHAR*, INT);
