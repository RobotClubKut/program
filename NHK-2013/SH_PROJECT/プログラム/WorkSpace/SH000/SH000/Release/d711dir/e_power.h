/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_power :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

extern void *memcpy(void *, const void *, size_t);
extern VOID   _pow10(INT, SHORT*, UCHAR*);
extern VOID   _mult64(SHORT*, UCHAR*, SHORT, UCHAR*);
extern int    _rnd(UCHAR*, INT);
extern VOID   _power(INT, SHORT*, UCHAR*);
