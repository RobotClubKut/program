/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*  NAME = e_stlar :                                             */
/*  FUNC = this header file do the following functions;          */
/*  (1) symbol define;                                           */
/*                                                               */
/*  CLAS = UNIT;                                                 */
/* END ;                                                         */
/*****************************************************************/

#ifndef _REENTRANT
extern volatile int _errno;
#else
extern  int *errno_addr(void);
#define _errno (*errno_addr())
#endif

#ifdef _DSPC
extern int atoi(const char*);                               /* A V80#4.17 */
extern ULONG _fdtob(CHAR*, INT);                            /* A V80#4.17 */
extern VOID _stlar(INT, CHAR*, CHAR*, CHAR, CHAR, VOID*);   /* A V80#4.17 */
#endif /* _DSPC */
