/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file  fflb_sh.h
 *  \brief FFlb SH用ヘッダファイル
 *  \note  組み込み関数や、SH用の定数を定義する
 */
#ifndef CMN_SH
#define CMN_SH


/* 組み込み関数ヘッダファイルインクルード */
#include <machine.h>	/* for dmulu_h(), dmuls_h(), div1(), etc..(SH instruction) */

/*
**------------------------
** FFlibオプションマクロ
**------------------------
*/
/* ターゲット */
#define TARGET_SH

/* denormalizeサポート用スイッチ */
#define SUPPORT_DENORMALIZE


/*
**------------------------
** 定数・マクロ定義
**------------------------
*/
/* 浮動小数点特殊値定義 */
#define PLS_NAN		0x7F800001
#define MNS_NAN		0xFF800001
#define PLS_INF		0x7F800000
#define MNS_INF		0xFF800000
#define MNS_ZERO	0x80000000

/* 関数用特殊値定義 */
#define SINF_NAN	PLS_NAN
#define LOGF_NAN	PLS_NAN
#define SQRTF_NAN	PLS_NAN
#define TANF_NAN	PLS_NAN

/* denormalize数をサポートしない場合のsqrtf戻り値定義*/
#define SQRTF_RTN_DENORM	(0)		/* FFLIB B-016 */

/*
**------------------------
** errno用の定義
**------------------------
*/
#define ERANGE 1100					/* FFLIB B-015		 */
#define EDOM   1101					/* FFLIB B-015		 */

#ifndef _REENTRANT					/* FFLIB B-015		 */
extern volatile int _errno;			/* FFLIB B-015		 */
#else								/* FFLIB B-015		 */
extern int *errno_addr(void);		/* FFLIB B-015		 */
#define _errno (*errno_addr())		/* FFLIB B-015		 */
#endif								/* FFLIB B-015		 */

#ifdef _SH1
/* SH-1にはdmulx_h()組み込み関数が無い */
/* 独自実装をする */

/* 32b * 32b = H32b */
#undef dmuls_h
long dmuls_h(long c, long i);

/* u32b * u32b = uH32b */
#undef dmulu_h
unsigned long dmulu_h(unsigned long c, unsigned long i);

/* 32b * 32b = H32b(full) */
long dmuls_n(long c, long i);								/* FFLIB B-010		*/

/* u32b * u32b = uH32b(full) */
unsigned long dmulu_n(unsigned long c, unsigned long i);	/* FFLIB B-009		*/

#else														/* FFLIB B-009		*/
/* SH-1以外の場合は、dmulx_nをdmulx_hに置き換える */
#define dmuls_n dmuls_h										/* FFLIB B-010		*/
#define dmulu_n dmulu_h										/* FFLIB B-009		*/
#endif /* _SH1 */



#endif /* CMN_SH */
