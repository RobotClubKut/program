/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = estrtod :                                            */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/


extern unsigned char _ctype[];
#ifndef _REENTRANT                              /* A S70003P */
extern volatile int	_errno;                    /* C S01002SP */
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P */

extern INT    _strchek(CHAR*, CHAR*);
extern long double  _stx(INT, CHAR*, INT, CHAR);
                                      /* C S40001SP  C S40008SP  C S40013SP */
extern float  _stf(INT, CHAR*, INT, CHAR);
                                      /* C S40001SP  C S40008SP  C S40013SP */
extern int    _sub(INT, UCHAR*, UCHAR*, INT);
extern double strtod(const char *, char **) ;
