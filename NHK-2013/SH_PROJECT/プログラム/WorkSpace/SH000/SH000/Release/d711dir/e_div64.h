/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_div64 :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*   NOTE = New (V.1.1)                                          */
/*   END ;                                                       */
/*****************************************************************/


extern INT    _lsft(UCHAR*, INT);
extern INT    _rsft(UCHAR*, INT);
extern VOID   _setsbit(UCHAR*, INT, INT);
extern void *memset(void *, int, size_t);
extern void *memcpy(void *, const void *, size_t);
extern VOID   _add(UCHAR*, UCHAR*, INT);
extern INT    _sub(INT, UCHAR*, UCHAR*, INT);
extern VOID   _div64(SHORT *, UCHAR *, SHORT, UCHAR *);
