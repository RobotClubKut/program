/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*  NAME = estrtola :                                            */
/*  FUNC = this header file do the following functions;          */
/*  (1) symbol define;                                           */
/*                                                               */
/*  CLAS = UNIT;                                                 */
/* END ;                                                         */
/*****************************************************************/

#ifdef _DSPC
extern LACCUM strtolaccum(const char*, char**);             /* A V80#4.17 */
extern VOID _strtolar(const CHAR*, CHAR**, CHAR, VOID*);    /* A V80#4.17 */
#endif /* _DSPC */
