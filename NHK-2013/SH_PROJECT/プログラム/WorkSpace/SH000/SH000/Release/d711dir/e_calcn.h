/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_calcn :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

extern VOID   _power(INT, SHORT*, UCHAR*);
extern VOID   _mult64(SHORT*, UCHAR*, SHORT, UCHAR*);
extern VOID   _div64(SHORT*, UCHAR*, SHORT, UCHAR*); /*  V.1.1  A  T11001V */
extern VOID   _setsbit(UCHAR*, INT, INT);
extern INT    _rsfts(UCHAR*, INT, SHORT);
extern int    _rnd(UCHAR*, INT);
extern void *memcpy(void *, const void *, size_t);
extern VOID   _calcnpw(SHORT, UCHAR*, INT, UCHAR*);
