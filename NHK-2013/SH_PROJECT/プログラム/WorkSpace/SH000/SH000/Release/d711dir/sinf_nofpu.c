/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file sinf.c
 *  \brief FFlib sinf関数ファイル
 */

#include "common.h"


/*!
 *  \brief  sinf関数（ライブラリ）
 *  \param  d0  入力値
 * （代入の手間を省くため、float型をunsigned long型として受け取っている）
 *  \return  sinf値
 * （代入の手間を省くため、float型をunsigned long型として返している）
 *
 *<hr>
 *  \par 内部処理：
 */
unsigned long sinf(unsigned long d0)	/* FFLIB B-012 B-016 */
{	
	unsigned long m;			/* 浮動小数点の仮数部(Q32固定小数点数)	*/
	unsigned long fpart;		/* 浮動小数点の小数部					*/
	long e;						/* 浮動小数点の指数部					*/

	/*! 浮動小数点の指数部と仮数部の切り出し				*/
	/*! →指数部の切り出し frexp_e()						*/
	e = frexp_e( d0 );			/* -126～e～129				*/
	/*! →仮数部の切り出し frexp_m()						*/
	m = frexp_m( d0 );			/* MSB = 1のQ32固定小数点数	*/

	/*! 指数部のチェック */
	if( e <= 0 ){
		/* 入力値が0.5以下の場合 */
		if( e < -16 ){
			/*! 指数部が-16未満の場合、入力値をそのまま返す「sin(x)=x x≒0」 */
		}else{
			/*! →指数部が０以下の場合は直接多項式計算をする __poly_sinL()   */
			/* 仮数部のうち小数点以下の数値を求める */
			m >>= 1;					/* 01mmmmmmmmmmmmm								*/
			fpart = m >> (-e);			/* 0.1mmmmmmmmmmmm(e=0) 0.001mmmmmmmmmm(e=-2)	*/
			d0 = __poly_sinL( (long)fpart, (long)m, e, (long)d0 );		/* FFLIB B-011	*/
		}
	}else{
		/*! →指数部が１以上の場合内部関数を呼ぶ __insinL() */
		/*! 　(異常値チェックは内部関数で行なっている)      */

		/* 入力値が正の時 n = 0、負の時 n = 4 */
		unsigned long n = (long)d0 < 0 ? 4 : 0;
		d0 = __insinL( n, m, e, d0);									/* FFLIB B-011	*/
	}
	return (d0);					/* FFLIB B-016 */
}
