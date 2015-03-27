/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*  NAME = e_strlar :                                            */
/*  FUNC = this header file do the following functions;          */
/*  (1) symbol define;                                           */
/*                                                               */
/*  CLAS = UNIT;                                                 */
/* END ;                                                         */
/*****************************************************************/

extern unsigned char _ctype[];
#ifndef _REENTRANT
extern volatile int _errno;
#else
extern  int *errno_addr(void);
#define _errno (*errno_addr())
#endif

#ifdef _DSPC
extern INT  _strchek(const CHAR*, const CHAR*);             /* A V80#4.17 */
extern VOID _stlar(INT, CHAR*, CHAR*, CHAR, CHAR, VOID*);   /* A V80#4.17 */
extern VOID _strtolar(const CHAR*, CHAR**, CHAR, VOID*);    /* A V80#4.17 */
#endif /* _DSPC */
