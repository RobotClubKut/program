/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = estrtoull :                                           */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/

extern unsigned char _ctype[];
#ifndef _REENTRANT                                 /* A V8.0 LI-070 */
extern volatile int _errno;                        /* C S01002SP */
#else                                              /* A V8.0 LI-070 */
extern  int *errno_addr(void);                     /* A V8.0 LI-070 */
#define _errno (*errno_addr())                     /* A V8.0 LI-070 */
#endif                                             /* A V8.0 LI-070 */

extern INT    _strchek(CHAR*, CHAR*);
extern unsigned long long int strtoull(const char *, char **, int); /* A S70004 P  */
