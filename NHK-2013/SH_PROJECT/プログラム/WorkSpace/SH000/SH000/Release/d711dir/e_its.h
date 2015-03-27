/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_its :                                              */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

extern void *memcpy(void *, const void *, size_t);
extern int  memcmp(const void *, const void *,size_t);
extern int    _sub(INT, UCHAR*, UCHAR*, INT);
extern INT    _rsfts(UCHAR*, INT, SHORT);
extern VOID   _its(CHAR*, CHAR*, INT);
extern int    _umemcmp(const void  *,const void *,int);
