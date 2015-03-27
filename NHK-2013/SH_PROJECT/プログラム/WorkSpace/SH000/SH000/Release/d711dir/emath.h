/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = emath :                                               */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/

#ifndef _REENTRANT                              /* A S70003P */
extern volatile int _errno;                        /* C S01002SP */
#else                                              /* A S70003P */
#define _errno (*errno_addr())                         /* A S70001SP */
int  *errno_addr(void);                                /* C S70001SP */
#endif                                             /* A S70003P */

extern const double _HUGE_VAL;                     /* C S01006SP */

extern double frexp(double, int *);
extern double ldexp(double, int );
extern double modf(double, double *);
extern double ceil(double);
extern double fabs(double);
extern double floor(double);
extern double fmod(double, double);
