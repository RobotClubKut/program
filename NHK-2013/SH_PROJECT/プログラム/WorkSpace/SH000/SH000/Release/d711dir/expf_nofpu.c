/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file expf.c
 *  \brief FFlib expf関数ファイル
 * 
 */

#include "common.h"

/* loge(2)定数 */
/* 実際はS31などを掛けて固定小数点化しているため、使用していない */
/* #define logE2		(0.6931471805599453094172321214581765680755) */

/* #define logE	1.442695041 */
/*! log2(e)定数(Q31固定小数点数) */
/* expf.cで使用 */
#define LOGEL		((unsigned long)0xB8AA3B29) /* S31*logE */

#undef MUL
/*! 多項式計算時の乗算定義 */
#define MUL(x,y) (dmuls_h(x, y)<<1)


/*! expf用多項式係数テーブル */
static const long pow2coeff1L[] = {					/* FFLIB B-011	*/
/* 4.0928471983E-11	max. relative err. */
	0x000059F9,		/* S30 * 2.1451470097E-05, */
	0x00025ABA,		/* S30 * 1.4370184309E-04, */
	0x0015FCBA,		/* S30 * 1.3419938473E-03, */
	0x009D84F9,		/* S30 * 9.6142235925E-03, */
	0x038D6505,		/* S30 * 5.5505042518E-02, */
	0x0F5FDE8F,		/* S30 * 2.4022640215E-01, */
	0x2C5C8602,		/* S30 * 6.9314718450E-01, */
	0x40000000 		/* S30 * 1.0 */
};


/*--------------------------------------------------
 * 内部関数（プロトタイプ）
 *--------------------------------------------------*/
/* power2のfloat多項式近似値を求める */
static long poly_pow2L(long d1, long e, long sign);


/*!
 *  \brief  expf関数（ライブラリ）
 *  \param  d0  入力値
 * （代入の手間を省くため、float型をunsigned long型として受け取っている）
 *  \return  expf値
 * （代入の手間を省くため、float型をunsigned long型として返している）
 *  \note 浮動小数点を固定小数点の整数部と小数部に分けて\n
 *        exp(x) = 2^(x*log2(E))を計算する\n
 *        入力が負であった場合は\n
 *        2^(-x) = 2^(x+1) * 2^(1-x)\n
 *
 *<hr>
 *  \par 内部処理：
 */
unsigned long expf(unsigned long d0)	/* FFLIB B-012 B-016 */
{
	unsigned long m;			/* 浮動小数点の仮数部(Q32固定小数点数) */
	unsigned long fpart;		/* 浮動小数点の小数部 */
	long e;						/* 浮動小数点の指数部 */
	long i;						/* 浮動小数点の整数部 */

	/*! 浮動小数点の指数部と仮数部の切り出し				*/
	/*! →指数部の切り出し frexp_e()						*/
	e = frexp_e( d0 );			/* -126～e～129				*/
	/*! →仮数部の切り出し frexp_m()						*/
	m = frexp_m( d0 );			/* MSB=1のQ32固定小数点数	*/

	/*! 異常値チェック */
	/*! →指数部が7より大きい時のe^xは＋∞を返す */
	/* e^(0.5*2^8) = e^128 = 3.887708405*10^55 ←floatの最大値を超えている為 */
	if( e > 7 ){
		/*! →±NANの時は±NANを返す(互換性のため正負を区別する) */
		if( (e > 128) && ((m & 0x7FFFFFFF) != 0) ){
			/* NAN */
			_errno = EDOM;		/* FFLIB B-015	*/
			if( (long)d0 < 0 ){
				/* -NAN */
				d0 = MNS_NAN;
			}else{
				/* +NAN */
				d0 = PLS_NAN;
			}
			return (d0);		/* FFLIB B-016	*/
		}
		/*! →負入力の時は０を返す e^(-128～-∞) = 0 */
		if( (long)d0 < 0 ){
			d0 = 0;
			return (d0);		/* FFLIB B-016	*/
		}else{
			_errno = ERANGE;	/* FFLIB B-015	*/
			d0 = PLS_INF;
			return (d0);		/* FFLIB B-016	*/
		}
	}

	/*! →指数部が-28未満の時のe^xは1.0を返す */
	if( e < -28){
		return (0x3F800000);	/* FFLIB B-016	*/
	}

	/*! 固定小数点数と指数から整数部と小数部を計算 */
	/*! →整数部 i 取得 integer()                  */
	i = integer( m, e );
	/*! →小数部 fpart 取得 fraction()             */
	fpart = fraction( m, e );

	/*! 入力変換 x*log2(E)
	**  (入力xは整数部がiで小数部がfpart)
	*/
	/* それぞれ32bなので小数点位置に注意して乗算と加算をする */
	/* 係数log2(E)はLOGELでQ31固定小数点数 */
	/* LOGEL =     .EEEE(Q31)              */
	/* fpart =     .ffff(Q32)              */
	/* i     = iiii.    (Q0)               */
	/* 小数部とlog2(E)の乗算結果上位32bを小数部に代入 */
	fpart = dmulu_h( fpart, LOGEL );	/* .ffff * .EEEE = .(ffff)ffff(Q63) = fpart(Q31) */
	/* 整数部とlog2(E)の乗算結果下位32bを仮(m)に代入 */
	m = i * LOGEL;						/* iiii. * .EEEE = iiii.(iiii)(Q31) = m(Q31) */
	/* 整数部とlog2(E)の乗算結果上位32bを整数部に代入 */
	i = dmulu_h( i, LOGEL );			/* iiii. * .EEEE = (iiii).iiii(Q31) = i(Q-1) */

	/* 32b.+.32b+.32b処理 */
#ifdef _SH
	clrt();								/* 後の計算の為のＴビットクリア */
	/* 小数部の加算 */
	fpart = addc( m, fpart);			/* .mmmm + .ffff = .ffff(Q31) = fpart(Q31) */
										/* ＴビットにあふれたMSBが入る */
	/* キャリーの加算（Ｔビット） */
	i = addc( 0, i);					/* 0 + iiii. + T = .iiii(Q-1) = i(Q-1) */

	/* 64b左1bシフト処理 */
	fpart = rotcl( fpart );				/* Q31になった小数部をQ32に戻す */
										/* ＴビットにあふれたMSBが入る */
	i = rotcl( i );						/* LSBにＴビットを入れる */
										/* Q-1になった整数部をQ0に戻す */
#else
#ifdef __H8__
	__addc3( &i, &fpart, m);

	/* 64b左1bシフト処理 */
	__shll64(&i, &fpart);
#endif	/* __H8__ */
#endif	/* _SH */
	/* 負入力の時は */
	if( (long)d0 < 0 ){					/* i+fpart --> (-i-1)+(1-fpart) */
		i = -i - 1;
		fpart = ~fpart;					/* Q32のビット反転は1-fpartと同じ意味になる */
	}

	/*! power2のfloat多項式近似値を求める poly_pow2L() */
	/* 戻り値は浮動小数点数になっている（型はlong）    */
	d0 = poly_pow2L( fpart>>1, (short)i , 0 );
	return (d0);						/* FFLIB B-016	*/
}

/*!
 *  \brief  power2のfloat多項式近似値を求める
 *  \param  d1   入力値
 *  \param  e    指数値
 *  \param  sign 符号用
 *  \return  power近似値
 */
static long poly_pow2L(long d1, long e, long sign) /* d3,e: for padding */
{
	unsigned long ans;		/* pow2多項式結果 */
	long *p;				/* 多項式係数テーブルへのポインタ */

	p = (const long *)pow2coeff1L;
	ans = *p++;
#ifdef OPT_TYPE_SIZE
	/* ROMサイズ優先オプションを選択した場合は多項式計算をループにする */
	/* ただしコンパイラの最適化オプションでループ展開を選択した場合 */
	/* 展開される可能性がある */
	{
		unsigned char i;
		for( i = 0; i < 7; ++i ){
			ans = *p++ +MUL(ans, d1);
		}
	}
#else
	ans = *p++ + MUL(ans, d1);
	ans = *p++ + MUL(ans, d1);
	ans = *p++ + MUL(ans, d1);
	ans = *p++ + MUL(ans, d1);
	ans = *p++ + MUL(ans, d1);
	ans = *p++ + MUL(ans, d1);
	ans = *p++ + MUL(ans, d1);
#endif

	return (__normalize(ans, e+2, sign));			/* FFLIB B-011	*/
}
