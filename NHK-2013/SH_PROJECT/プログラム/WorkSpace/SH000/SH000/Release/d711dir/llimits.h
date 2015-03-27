/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = limits.h :                                                  */
/*                                                                     */
/*  FUNC = this module do the following functions                      */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#define       CHAR_BIT                8
#define       CHAR_MAX              127
#define       CHAR_MIN           (-128)
#define       SCHAR_MAX             127
#define       SCHAR_MIN          (-128)
#define       UCHAR_MAX             255
#define       SHRT_MAX            32767
#define       SHRT_MIN         (-32768)
#define       USHRT_MAX           65535
#define       INT_MAX        2147483647
#define       INT_MIN    (-2147483647-1)
#define       UINT_MAX      4294967295u
#define       LONG_MAX       2147483647
#define       LONG_MIN   (-2147483647L-1L)
#define       ULONG_MAX     4294967295u
/*#if (defined _SH5M) || (defined _SH5C)              /* A S70004 P */ /* D V80#1.05 */
#define       LLONG_MAX    9223372036854775807LL      /* A S70004 P */
#define       LLONG_MIN  (-9223372036854775807-1LL)   /* A S70004 P */
#define       ULLONG_MAX 18446744073709551615ULL      /* A S70004 P */
/*#endif                                              /* A S70004 P */ /* D V80#1.05 */
