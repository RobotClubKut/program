/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = setjmp.h :                                ;                 */
/*                                                                     */
/*  FUNC = this module do the following functions    ;                 */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
                                                         /* D S01006SP */
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
typedef int jmp_buf[38];                                 /* C S40010SP */
#else
typedef int jmp_buf[20];                                 /* C S40010SP */
#endif
#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
typedef int jmp_buf_a[54];
#endif


#define SEQERR     1108
