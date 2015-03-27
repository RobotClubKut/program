/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_unpac :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

extern void *memcpy(void *, const void *, size_t);
extern INT    _lsfts(UCHAR*, INT, SHORT);
extern VOID   _unpack(long double, CHAR*, SHORT*, UCHAR*);
                                   /* ^^^ C S01001SP  C S40001SP */
