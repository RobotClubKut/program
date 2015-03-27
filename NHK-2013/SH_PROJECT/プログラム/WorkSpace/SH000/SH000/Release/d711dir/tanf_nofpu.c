/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file tanf.c
 *  \brief FFlib tanf関数ファイル
 */

#include "common.h"
#ifdef _DEBUG
#include <stdio.h>
#endif
/*! 4/PAI定数(Q32固定小数点数) */
//#define RPI4		((unsigned long)((1.273239545f-1.0f)*S32))
#define RPI4        (0x45F306DD)				/* FFLIB B-001		*/
/*! PAI/4定数(Q32固定小数点数)上位ワード */
#define P4L			(0xC90FDAA2)
/*! PAI/4定数(Q32固定小数点数)下位ワード */
#define P4LLOW		(0x2168C235)

/*! 多項式計算時の乗算定義 */
#define MUL(x,y)	(dmuls_h(x,y)<<1)

/*! tanf多項式係数 */
static const long coeff_tanf[] = {
	0x00966DD2,			/* S31*4.590728487528E-03, */
	0xFFF4BEDA,			/* S31*-3.434600730543E-04, */
	0x016E36D7,			/* S31*1.117597134726E-02, */
	0x02B51707,			/* S31*2.115142712501E-02, */
	0x06EC4381,			/* S31*5.408519573393E-02, */
	0x1110C617,			/* S31*1.333243955637E-01, */
	0x2AAAAC99			/* S31*3.333335636132E-01, */
};

#ifndef UNSUPPORT_SINCOS_BIGINPUT
/*! 2/PAI定数(Q32固定小数点数)224ビット */		/* FFLIB B-003		*/
static const unsigned long P2af[] = {			/* FFLIB B-003		*/
	0,											/* FFLIB B-003		*/
	0xA2F9836E,									/* FFLIB B-003		*/
	0x4E441529,									/* FFLIB B-003		*/
	0xFC2757D1,									/* FFLIB B-003		*/
	0xF534DDC0,									/* FFLIB B-003		*/
	0xDB629599,									/* FFLIB B-003		*/
	0x3C439041,									/* FFLIB B-003		*/
	0xFE5163AB									/* FFLIB B-003		*/
};												/* FFLIB B-003		*/
#endif /* UNSUPPORT_SINCOS_BIGINPUT */

/*--------------------------------------------------
 * 内部関数（プロトタイプ）
 *--------------------------------------------------*/
#ifndef UNSUPPORT_SINCOS_BIGINPUT
static long big_inputL(unsigned long m, long e, char sign);									/* FFLIB B-003		*/
#endif /* UNSUPPORT_SINCOS_BIGINPUT */
static long intanF(unsigned long m, long e, char sign);
static long poly_oddf(unsigned long d1, unsigned long d2, long e, char sign);				/* FFLIB B-005		*/
INLINE long myfmod(unsigned long i, unsigned long f, unsigned long n, unsigned long *p);	/* FFLIB B-005		*/

/*!
 *  \brief  還元(3)(4) d0+= -pi4r*nのd0を計算する
 *  \param  i  固定小数点の整数部
 *  \param  f  固定小数点の小数部
 *  \param  n  還元(1)の整数部
 *  \param  *p 下位32bit返却用
 *  \return 結果 d0
 *
 *<hr>
 *  \par 内部処理：
 */
INLINE long myfmod(unsigned long i, unsigned long f, unsigned long n, unsigned long *p)		/* FFLIB B-005		*/
{
								/* PI/4(64b) * n(32b)の結果96bitを格納する */
	unsigned long x0;			/* 最上位ワード格納 */
	unsigned long x1;			/* 中位ワード格納(n*P4Lowの上位ワード) */
	unsigned long y1;			/* 中位ワード格納(n*P4Lの下位ワード) */
	unsigned long y2;			/* 最下位ワード格納 */
	/* i:d0整数部 */
	/* f:d0小数部 */

	/*! 還元(3) d0+= -pi4k*n;     pi4k=(float)(int)(3.141592*1024)/1024.0)/4 */
	/*! 還元(4) d0+= -pi4r*n;     pi4r=(float)(PI/4-pi4r) */
#ifdef _DEBUG
    printf("##### myfmod IN(i = %08lx, f = %08lx, n = %08lx)\n", i, f, n);
#endif

	/* PI/4 * nの96bit計算 */
	y2 = n * P4LLOW;			/* y2 = 0000000000000000XXXXXXXX */
	y1 = dmulu_n( n, P4LLOW );	/* y1 = 00000000XXXXXXXX00000000 */	/* FFLIB B-009		*/
	x1 = n * P4L;				/* x1 = 00000000XXXXXXXX00000000 */
	x0 = dmulu_n( n, P4L );		/* x0 = XXXXXXXX0000000000000000 */	/* FFLIB B-009		*/

	/* 32b.+.32b+.32b処理 */
#ifdef _SH
	clrt();						/*Ｔビットクリア(SH) */
	x1 = addc( y1, x1 );		/* x1 = y1 + x1 オーバーフローしたらＴフラグが１に */
	x0 = addc( x0, 0 );			/* x0 = x0 + 0 + Ｔ オーバーフロー時の加算 */
#else
#ifdef __H8__
	__addc3((long *)&x0, &x1, y1);
#endif
#endif

	/* d0 += -X -> d0 -= Xの計算 */
	/* d0 = iiii.ffff0000 */
	/*  X = x0x0.x1x1y2y2 */
	/*  -                 */
	/*--------------------*/
	/* output iiii.ffff*p*p */
	/* 64b-96b処理 */
#ifdef _SH
	y2 = negc( y2 );			/* y2 = 0 - y2 （Ｔビット=1） */
	f = subc( f, x1 );			/* f = f - x1 - T */				/* FFLIB B-005		*/
	i = subc( i, x0 );			/* i = i - x0 - T */				/* FFLIB B-005		*/
	f = rotcr( f );				/* MSB = T 符号ビット付加 */		/* FFLIB B-005		*/
	*p = rotcr( y2 );			/* 下位32ビット */					/* FFLIB B-005		*/
#else
#ifdef __H8__
	*p = __sub96( &i, &f, x0, x1, y2);
#endif
#endif

#ifdef _DEBUG
    printf("##### myfmod OUT(f = %08lx, p = %08lx)\n", f, *p);
#endif
	return (f);					/* 中位32ビット */					/* FFLIB B-005		*/
}

/*!
 *  \brief  tanf関数（ライブラリ）
 *  \param  d0  入力値
 * （代入の手間を省くため、float型をunsigned long型として受け取っている）
 *  \return  tanf値
 * （代入の手間を省くため、float型をunsigned long型として返している）
 *
 *<hr>
 *  \par 内部処理：
 */
unsigned long tanf( unsigned long d0 )		/* FFLIB B-012 B-016 */
{
	unsigned long m;			/* 浮動小数点の仮数部(Q32固定小数点数) */
	unsigned long fpart;		/* 浮動小数点の小数部 */
	long e;						/* 浮動小数点の指数部 */
	char sign;					/* 符号用             */

	/*! 浮動小数点の指数部と仮数部の切り出し				*/
	/*! →指数部の切り出し frexp_e()						*/
	e = frexp_e( d0 );				/* -126～e～129 */
	/*! →仮数部の切り出し frexp_m()						*/
	m = frexp_m( d0 );				/* MSB = 1のQ32固定小数点数 */

	sign = 0;
	if( (d0 & 0x80000000) != 0 ){
		sign = ~sign;				/* sign = -1 */
	}

	if( (d0 & 0x7FFFFFFF) < 0x3F490FDB ){
		/*! 入力の絶対値がPI/4未満の時は、直接多項式計算を呼ぶ poly_oddf() */
		if( e < -16 ){
			/*! 指数部が-16未満の場合、入力値をそのまま返す「tanf(x)=x x≒0」 */
#ifdef SUPPORT_DENORMALIZE
			/* denormal数をサポートするならtanf(x) = x */
			/* 入力値をそのまま返す「tanf(x)=x x≒0」 */
			return (d0);			/* FFLIB B-016	*/
#else
			/* denormal数をサポートしないなら */
			if ( (d0 & 0x7F800000) == 0 ) {
				/* denormal数の時はtanf(x) = 0.0 */
				d0 = 0;
				if( sign != 0 ){
					d0 |= 0x80000000;
				}
				return (d0);	/* FFLIB B-016	*/
			} else {
				return (d0);	/* FFLIB B-016	*/
			}
#endif
		}else{
			/* 仮数部のうち小数点以下の数値を求める */
			m >>= 1;					/* 01mmmmmmmmmmmmm */
			fpart = fraction( m, e );	/* 0.1mmmmmmmmmmmm(e=0) 0.001mmmmmmmmmm(e=-2) */
			d0 = poly_oddf(fpart, m, e, sign);			/* FFLIB B-005		*/
		}
	}else{
		/*! その他は内部関数を呼ぶ intanF() */
		d0 = intanF(m, e, sign);
	}
	return (d0);				/* FFLIB B-016	*/
}

/*!
 *  \brief  内部tanf関数
 *  \param  m    Q32固定小数点
 *  \param  sign 符号
 *  \param  e    指数
 *  \return  tanf値（long型）
 */
static long intanF(unsigned long m, long e, char sign)
{
	unsigned long d1;			/* d0 - n*(PI/4) tan値を求める元の値（Q32固定小数点）*/
	float d2;
	unsigned long d3;			/* FFLIB B-005		*/
	unsigned long n;			/* n = (long)((float)(4/PI)*d0) */
	unsigned long i;			/* 固定小数点の整数部 */
	unsigned long fpart;		/* 固定小数点の小数部 */
	unsigned long fpart2;		/* 固定小数点の小数部 */
	unsigned long low_half;		/* d1と同じ意味でd1の下位ワード（Q64固定小数点）*/
	char poly_sign;

	/* 巨大入力判別 */
	/*! 指数が32以上の場合巨大値として扱う						*/
	if( e >= 32 ){
#ifdef UNSUPPORT_SINCOS_BIGINPUT
	/*! →サイズ最適化オプションで巨大値入力非対応が定義された場合
	**  big_inputL()は使わないでNANを返す
	*/
		_errno = EDOM;			/* FFLIB B-015	*/
		return (TANF_NAN);		/* return nan if(nan or inf)	*/
#else
	/*! →巨大値計算関数を呼ぶ big_inputL()	*/
		return (big_inputL( m, e, sign ));	/* FFLIB B-003		*/
#endif /* UNSUPPORT_SINCOS_BIGINPUT */
	}

	/*! 固定小数点数と指数から整数部と小数部を計算 */
	/*! →整数部 i 取得 integer()                  */
	i = integer( m, e );
	/*! →小数部 fpart 取得 fraction()             */
	fpart = fraction( m, e );

	/*! 還元 */
	/* n = (long)((float)(4/PI)*d0)  (1) */
	/*! →還元(1)(2) n*(π/4)のnを求める */
	/* 整数部分を計算する（>> (31 - e)） */
	n = dmulu_n( i, RPI4 ) + i;				/* FFLIB B-009		*/
	d1 = i * RPI4;
	fpart2 = dmulu_h( fpart, RPI4 );
#ifdef _DEBUG
	printf("n = %08lx, RPI4 = %08lx\n", n, RPI4);
	printf("fpart = %08lx, fpart2 = %08lx, d1 = %08lx\n", fpart, fpart2, d1);
#endif
	if( d1 + fpart2 < d1 ){
		n++;
	}
	d1 += fpart2;
	if( d1 + fpart < d1 ){
		n++;
	}
	/*! →還元(3)(4) d0 = d1 + n*(PI/4)のd1を求める myfmod() */
	d1 = myfmod( i, fpart, n, &low_half );	/* d0 = d1 + n*(PI/4), -PI/4 <= d1 <= PI/4 */	/* FFLIB B-005		*/
	if ( (n & 1) != 0 ){																	/* FFLIB B-005		*/
		d1 = (P4L >> 1) - d1;																/* FFLIB B-005		*/
		if ( low_half > ((P4LLOW >> 1) | (P4L << 31)) ){									/* FFLIB B-005		*/
			d1--;																			/* FFLIB B-005		*/
		}																					/* FFLIB B-005		*/
		low_half = ((P4LLOW >> 1) | (P4L << 31)) - low_half;								/* FFLIB B-005		*/
	}																						/* FFLIB B-005		*/
	if ( (long)d1 < 0 ){																	/* FFLIB B-005		*/
		low_half = -low_half;																/* FFLIB B-005		*/
		d1 = -d1;																			/* FFLIB B-005		*/
		sign = ~sign;																		/* FFLIB B-006		*/
		if ( low_half != 0 ){																/* FFLIB B-005		*/
			d1--;																			/* FFLIB B-005		*/
		}																					/* FFLIB B-005		*/
	}																						/* FFLIB B-005		*/
	e = 0;																					/* FFLIB B-005		*/
	d3 = d1;																				/* FFLIB B-005		*/
	while ((long)d3 > 0){																	/* FFLIB B-005		*/
		e--;																				/* FFLIB B-005		*/
		d3 = (d3 << 1) | (low_half >> 31);													/* FFLIB B-005		*/
		low_half <<= 1;																		/* FFLIB B-005		*/
	}																						/* FFLIB B-005		*/
	poly_sign = 0;
	if ( (n & 2) != 0 ){
		poly_sign = ~poly_sign;
	}
	e++;																					/* FFLIB B-005		*/
	d3 >>= 1;																				/* FFLIB B-005		*/
	/*! tanf多項式計算を呼ぶ poly_oddf() */
	d1=poly_oddf(d1, d3, e, poly_sign);														/* FFLIB B-005		*/
	if( sign != 0 ){
		d1 ^= 0x80000000;
	}
	if( ((n&3) == 1) || ((n&3) == 2) ){
		d2 = *(float *)&d1;
		*(float *)&d1 = (1.0f / d2);
	}
	return d1;
}

/*!
 *  \brief  tanf多項式計算
 *  \param  d0  unsigned long d1^2
 *  \param  d1  unsigned long（0～4/PI:Q32）
 *  \param  sign 符号
 *  \param  e   指数
 *  \return  tanf値（long型）
 */
static long poly_oddf(unsigned long d0, unsigned long d1, long e, char sign)				/* FFLIB B-005		*/
{
	unsigned long d2;																		/* FFLIB B-005		*/
	long fr5, fr6, fr7, fr8, d4;
	const long *p;

#ifdef _DEBUG
    printf("$$$$$ poly_oddf IN(d0 = %08lx, d1 = %08lx, e = %04x, s = %01x)\n", d0, d1, e, sign);
#endif
	d2 =dmulu_h(d0, d0) << 1;																/* FFLIB B-005		*/
	d4 = MUL(d2, d2);
	p = coeff_tanf;

	/*fr5 = *p++;*/			/*fr7 = *p++;*/
	/*fr6 = *p++;*/			fr8 = *p++;				/* c9,c7							*/
	/*fr6 += d4 * fr5;*/	/*fr8 += d4 * fr7;*/	/* c8+d4*c10, c7+d4*c9, 			*/
	fr5 = *p++;				fr7 = *p++;				/* c6,c5							*/
	/*fr5 += d4 * fr6;*/	fr7 += MUL(d4, fr8);	/* c6+d4*(c8+..), c5+d4*(c7+..)		*/
	fr6 = *p++;				fr8 = *p++;				/* c4,c3							*/
	fr6 += MUL(d4, fr5);	fr8 += MUL(d4, fr7);	/* c4+d4*(c6+..), c3+d4*(c5+..)		*/
	fr5 = *p++;				fr7 = *p++;				/* c2,c1							*/
	fr5 += MUL(d4, fr6);	fr7 += MUL(d4, fr8);	/* c2+d4*(c4+..), c1+d4*(c3+..)		*/
	fr5  = MUL(fr5, d4);							/* d4*(c2*d4*(c4+..))				*/
	fr5 += MUL(d2, fr7);							/* d2*c1+d4*c2+c6*c3+d8*c4+..		*/
#ifdef _DEBUG
	printf("&&&&& d1+=MUL(d1 = %08lx, fr5 = %08lx)\n", d1, fr5); 
#endif
	d1 += MUL(d1, fr5);								/* d1+d3*c1+d5*c2+c7*c3+d9*c4+..	*/
#ifdef _DEBUG
	printf("&&&&& d1 = %08lx\n", d1);
#endif

#ifdef _DEBUG
    printf("----- fixed_normalize IN(d1 = %08lx, e = %04x)\n", d1, e);
#endif
	/* 固定小数点正規化 */
	while( (long)d1 > 0 ){		/* MSB = 0なら繰り返す		*/
		e--;					/* 指数は-1する				*/
		d1 = d1 << 1;			/* 固定小数点数を左シフト	*/
	}
#ifdef _DEBUG
    printf("----- fixed_normalize OUT(d1 = %08lx, e = %04x)\n", d1, e);
#endif
	e += 127;

#ifndef _DEBUG
	return (__myround(d1, e, sign));				/* FFLIB B-011	*/
#else
	printf("!!!!! __myround IN(d1 = %08lx, e = %04x, s = %01x)\n", d1, e, sign);
	d1 = __myround(d1, e, sign);					/* FFLIB B-011	*/
	printf("!!!!! __myround OUT(d1 = %08lx)\n", d1);
    printf("$$$$$ poly_oddf OUT(d1 = %08lx)\n", d1);
    return (d1);
#endif
}

#ifndef UNSUPPORT_SINCOS_BIGINPUT					/* FFLIB B-003	*/
/*!
 *  \brief  巨大値入力時の計算
 *  \param  m     Q32固定小数点(0.1mmmmmmmmmmm...)
 *  \param  e     指数
 *  \param  sign  符号
 *  \return 
 *
 *<hr>
 *  \par 内部処理：
 */
static long big_inputL(unsigned long m, long e, char sign)
{
	unsigned long x1, x2, x3;
	unsigned long *p;			/* 2/PI = P2af = 0.ppppppppp...		*/
#ifdef _DEBUG
	printf("----- big_inputL IN(m = %08lX, e = %d, sign = %08lX)\n", m, e, sign);
#endif
	
	e -= 2;						/* 小数点位置の調整 */
	/* INF/NANチェック */
	if( e >= 127 ){
		/*! INF/NANの場合NANを返す */
		_errno = EDOM;			/* FFLIB B-015	*/
		return (TANF_NAN);		/* return nan if(nan or inf) */
	}
	p = (unsigned long *)P2af;
	while( e >= 32 ){			/* 32bit小数点位置調整 */
		p++;
		e -= 32;
	}
	x1 = *p++;					/* 2/PIの整数部 */
	x2 = *p++;					/* 2/PIの小数部上位32bit */
	x3 = *p++;					/* 2/PIの小数部下位32bit */
	if( e != 0 ){				/* 32bit未満の小数点位置調整 */
		x1 = (x1 << (e)) | (x2 >> (32 - e));
		x2 = (x2 << (e)) | (x3 >> (32 - e));
	}
	/* x1*mの小数部（乗算結果の下位32bit）とx2*mの小数部（乗算結果の上位32bit）を加算する。 */
	x1 = x1 * m + dmulu_h( x2, m );		/* 0.0<=x1<1.0 */
	/*! d0*2/PIの小数部（余り）を求める */
	/* d0 = PI/4 * 余り */
	m = dmulu_h( x1, P4L );				/* 0.0<=d2<2PI */
	/*! 本処理を呼ぶ intanF() */
	return (intanF(m, 3, sign));
}
#endif /* UNSUPPORT_SINCOS_BIGINPUT */				/* FFLIB B-003	*/
