/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_calci :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

/*
**  下位サブルーチン _lsft(), _add() の中では 2バイトアクセスが行われる為、
**  バッファへのポインタは 2バイト整合されていなければならない。
*/

#define ALIGN2_UP(x)     (((x)+1)&~1)  /* 2バイト境界整合切り上げ */
#define ALIGN2_DOWN(x)   ((x)&(~1))    /* 2バイト境界整合切り捨て */

#define STRBYTE     (31)               /* 31 = 小数部分の10進桁数の上限 */
#define NUMBYTE     ALIGN2_UP(13)      /* 13 = 数値 1*(10**31) の所要バイト数 */

extern void *memcpy(void *, const void *, size_t);
extern INT    _lsfts(UCHAR*, INT, SHORT);
extern VOID   _add(UCHAR*, UCHAR*, INT);
extern INT    _lsft(UCHAR*, INT);
extern VOID   _calcint2(UCHAR*, INT, INT);
