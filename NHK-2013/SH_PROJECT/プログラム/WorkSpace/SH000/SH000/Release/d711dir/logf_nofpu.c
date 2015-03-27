/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file logf.c
 *  \brief FFlib logf関数ファイル
 */

#include "common.h"


/*! logf用多項式係数テーブル */
static const long coeffLR[] = {	/* coefficients for the rage [0.5,1.0], return negated value */
	0x0046D85D,		/* S31 *  2.1620234356E-03, */ /* inputs is conveted to (m-1.0) */
	0xFE31CA97,		/* S31 * -1.4105488488E-02, */
	0x058321FD,		/* S31 *  4.3064354890E-02, */
	0xF5305B2E,		/* S31 * -8.4461787148E-02, */
	0x101907DF,		/* S31 *  1.2576387820E-01, */
	0xEB48E720,		/* S31 * -1.6183768227E-01, */
	0x197DB9F6,		/* S31 *  1.9914936593E-01, */
	0xE002B398,		/* S31 * -2.4991755600E-01, */
	0x2AAA8F50,		/* S31 *  3.3333007262E-01, */
	0xC0000000,		/* S31 * -0.5, */
	0x7FFFFFFF,		/* 0x7fffffff,	 */ /* neaely equat to S31*1.0, do not overflow */
	0x58B90BFB		/* S31 *  logE2 */
};
/*! logf用多項式係数テーブル */
static const long coeffLL[] = {	/* coefficients for the rage [0.5,1.0], return negated value */
	0xFFDCD5F3,		/* -S30/1024 *  2.1977669774E+00, */ /* inputs is conveted to (m-1.0)*2 */
	0xFF8978B6,		/* -S30/512  *  3.7040148061E+00, */
	0xFF3008F3,		/* -S30/256  *  3.2494540103E+00, */
	0xFF531A88,		/* -S30/128  *  1.3507528622E+00, */
	0xFF6EE95C,		/* -S30/64   *  5.6675172132E-01, */
	0x002EEA11,		/* -S30/32   * -9.1629554867E-02, */
	0xFF2B2109,		/* -S30/16   *  2.0788180312E-01, */
	0x01FF1830,		/* -S30/8    * -2.4955785709E-01, */
	0xFAAAA03D,		/* -S30/4    *  3.3334328173E-01, */
	0x10000000,		/* -S30/2    * -0.5, */
	0xC0000000,		/* 0xc0000000, */
	0x58B90BFB		/* S31 * logE2 */
};

#undef MUL
/*! 多項式計算時の乗算定義 */
#define MUL(x,y) (dmuls_h(x, y)<<1)

/*--------------------------------------------------
 * 内部関数（プロトタイプ）
 *--------------------------------------------------*/
/* Logのfloat多項式近似値を求める */
static long poly_logL(long d1, long *p, long e, long sign);			/* FFLIB B-011	*/


/*!
 *  \brief  logf関数（ライブラリ）
 *  \param  d0  入力値
 * （代入の手間を省くため、float型をunsigned long型として受け取っている）
 *  \return  logf値
 * （代入の手間を省くため、float型をunsigned long型として返している）
 *
 *<hr>
 *  \par 内部処理：
 */
unsigned long logf(unsigned long d0)	/* FFLIB B-012 B-016 */
{
	unsigned long m;			/* 浮動小数点の仮数部(Q32固定小数点数) */
	unsigned long fpart;		/* 浮動小数点の小数部 */
	long e;						/* 浮動小数点の指数部 */
	long i;						/* 浮動小数点の整数部 */

	long sign, *p;

	/*! 浮動小数点の指数部と仮数部の切り出し				*/
	/*! →指数部の切り出し frexp_e()						*/
	e = frexp_e( d0 );		/* -126～e～129	*/
	/*! →仮数部の切り出し frexp_m()						*/
	m = frexp_m( d0 );		/* MSB = 1		*/

	/*! 異常値チェック */
	if( d0 - 0x00800000 >= 0x7F000000 ){
		/* +INF, +NAN, 負の時 */
		/* 極小値(指数部０)または０の時 */
		if ( (d0 << 1) == 0 ) {
			/*! →0.0、-0.0入力の時は－∞を返す */
			_errno = ERANGE;				/* FFLIB B-015	*/
			d0 = MNS_INF;
			return (d0);					/* FFLIB B-016	*/
		} else if ( (long)d0 < 0 ) {
			/*! →負入力の時はNANを返す */
			_errno = EDOM;					/* FFLIB B-015	*/
			d0 = LOGF_NAN;
			return (d0);					/* FFLIB B-016	*/
		} else if ( (d0 >> 23) == 0 ) {
			/* denormal数の時は */
#ifdef SUPPORT_DENORMALIZE
			/*! →denormal数をサポートするなら正規化する */
			if( e <= -126 ){
				m <<= 1;					/* 指数部が０の時は、仮数部MSB = 1を消してから */
											/* 正規化する */
				while( (long)m > 0 ){		/* MSB = 0なら繰り返す		*/
					e--;					/* 指数は-1する				*/
					m <<= 1;				/* 固定小数点数を左シフト	*/
				}
			}
#else
			/*! →denormal数をサポートしないなら0.0の時と同じ－∞を返す */
			_errno = ERANGE;				/* FFLIB B-015	*/
			d0 = MNS_INF;
			return (d0);					/* FFLIB B-016	*/
#endif
		} else if ( (d0 & 0x007FFFFF) == 0 ) {
			/*! →+INFの時はそのまま返す */
			_errno = ERANGE;				/* FFLIB B-015	*/
			return (d0);					/* FFLIB B-016	*/
		} else {
			/*! →+NANの時はNANを返す */
			_errno = EDOM;					/* FFLIB B-015	*/
			d0 = LOGF_NAN;
			return (d0);					/* FFLIB B-016	*/
		}
	}

	if( e < 1 ){
	/* 入力が1.0未満の時 */
		sign = -1;				/* 結果符号は負 */
		e = -e;
								/* m-1.0 */
		p = (long *)coeffLL;
  	}else{ 		
	/* 入力が1.0以上の時 */
		sign = 0;				/* 結果符号は正 */
		e--;
  		m = (m << 1) >> 1;			/* (m*2-1.0)>>1 */
		p = (const long *)coeffLR;
	}

	/*! logのfloat多項式近似値を求める poly_logL()  */
	/* 戻り値は浮動小数点数になっている（型はlong） */
	d0 = poly_logL( m, p, e, sign );
	return (d0);				/* FFLIB B-016	*/
}

/*!
 *  \brief  Logのfloat多項式近似値を求める
 *  \param  d1   入力値
 *  \param  p    多項式係数値へのポインタ
 *  \param  e    指数
 *  \param  sign 符号用
 *  \return  log近似値
 */
static long poly_logL(long d1, long *p, long e, long sign)				/* FFLIB B-011	*/
{
	long n;					/* log(x)値結果の浮動小数点指数部にあたる */
	long ans;				/* log多項式結果上位32b */
	unsigned long wer;		/* log多項式結果下位32b */
	
	/* log(d1)計算 */
	ans = *p++;
#ifdef OPT_TYPE_SIZE
	/* ROMサイズ優先オプションを選択した場合は多項式計算をループにする */
	/* ただしコンパイラの最適化オプションでループ展開を選択した場合 */
	/* 展開される可能性がある */
	{
		unsigned char i;
		for( i = 10; i != 0; +--i ){
			ans = *p++ +MUL(ans, d1);
		}
	}
#else
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
	ans = *p++ +MUL(ans, d1);
#endif
	wer = ans * d1;
	ans = dmuls_n(ans, d1);		/* ans::wer=ans*d1 */					/* FFLIB B-010	*/

	/* 64b左1bシフト処理 */
#ifdef _SH
	wer = rotcl(wer);
	ans = rotcl(ans);			/* ans=(ans::wer<<1(>>32 */
#else
#ifdef __H8__
	__shll64(&ans, &wer);
#endif
#endif
		
	/* Log(y) = log( d1*2^n) = log(d1) + n*log(2) */
	if( e == 0 ){
	/* nが0なら、log(d1)計算だけでいい */
		/* log(d1)も０だったら、０を返す */
		if( ans == 0 ){
			return (0);
		}
		n = 1;
		while( ans > 0 ){
			/* 64b左1bシフト処理 */
#ifdef _SH
			wer = rotcl(wer);
			ans = rotcl(ans);
#else
#ifdef __H8__
			__shll64(&ans, &wer);
#endif
#endif

			n--;
		}
	}else{
	/* nが1以上なら、n*log(2)も計算する */
		/* 係数log(2)は*pで中身はS31*logE2 */
		/* 1 <= e(Q0) <= 129    */
		/* logE2 =   .EEEE(Q31) */
		/* ans */
		n = e * (*p);			/* e. * .logE2 = e.(e) => n */
		e = dmulu_h( (unsigned long)e, (unsigned long)*p );	/* e. * .logE2 = (e.)e => e(MAX 88) */

		/* 32b.+.32b+.32b処理 */
#ifdef _SH
		clrt();
		ans = addc( n, ans );	/* .n + .ans = .ans (over flow > T) */
		e = addc( 0, e);		/* e. + 0 + T = e. */
#else
#ifdef __H8__
		__addc3( &e, (unsigned long *)&ans, n);
#endif
#endif

		n = 1;
		while( e ){				/* loop befor e(eeee).f(ffff) n = 1 */
			/* 64b右1bシフト処理 */
#ifdef _SH
			clrt();				/* loop after e(0000).f(efff) n = 8(MAX) */
			e = rotcr(e);
			ans = rotcr(ans);
#else
#ifdef __H8__
			ans = (e << (31)) | ((unsigned long)ans >> 1);
			e = (unsigned long)e >> 1;
#endif
#endif

			n++;
		}
	}

	return (__normalize( ans, n, sign ));			/* FFLIB B-011	*/
}

