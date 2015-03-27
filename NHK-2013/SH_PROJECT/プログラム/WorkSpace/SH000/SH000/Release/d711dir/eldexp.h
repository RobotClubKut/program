/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = eldexp :                                             */
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
extern  int *errno_addr(void);                     /* C S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P */

extern double ldexp(double, int );
