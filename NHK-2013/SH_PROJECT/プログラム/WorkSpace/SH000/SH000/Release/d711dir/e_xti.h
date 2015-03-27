/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_xti :                                              */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/


extern int    _allzero(UCHAR*, INT);
extern VOID   _unpack(long double, CHAR*, SHORT*, UCHAR*);
extern int    _log10(long double);
extern VOID   _pow5(INT, CHAR*);
extern INT    _lsfts(UCHAR*, INT, SHORT);
extern VOID   _calcnpw(SHORT, UCHAR*, INT, UCHAR*);
extern void *memcpy(void *, const void *, size_t);
extern int  memcmp(const void *, const void *,size_t);
extern int    _xti(long double, INT, CHAR*, INT*, CHAR*);
