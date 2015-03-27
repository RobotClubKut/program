/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file tanf.c
 *  \brief FFlib tanf�֐��t�@�C��
 */

#include "common.h"
#ifdef _DEBUG
#include <stdio.h>
#endif
/*! 4/PAI�萔(Q32�Œ菬���_��) */
//#define RPI4		((unsigned long)((1.273239545f-1.0f)*S32))
#define RPI4        (0x45F306DD)				/* FFLIB B-001		*/
/*! PAI/4�萔(Q32�Œ菬���_��)��ʃ��[�h */
#define P4L			(0xC90FDAA2)
/*! PAI/4�萔(Q32�Œ菬���_��)���ʃ��[�h */
#define P4LLOW		(0x2168C235)

/*! �������v�Z���̏�Z��` */
#define MUL(x,y)	(dmuls_h(x,y)<<1)

/*! tanf�������W�� */
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
/*! 2/PAI�萔(Q32�Œ菬���_��)224�r�b�g */		/* FFLIB B-003		*/
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
 * �����֐��i�v���g�^�C�v�j
 *--------------------------------------------------*/
#ifndef UNSUPPORT_SINCOS_BIGINPUT
static long big_inputL(unsigned long m, long e, char sign);									/* FFLIB B-003		*/
#endif /* UNSUPPORT_SINCOS_BIGINPUT */
static long intanF(unsigned long m, long e, char sign);
static long poly_oddf(unsigned long d1, unsigned long d2, long e, char sign);				/* FFLIB B-005		*/
INLINE long myfmod(unsigned long i, unsigned long f, unsigned long n, unsigned long *p);	/* FFLIB B-005		*/

/*!
 *  \brief  �Ҍ�(3)(4) d0+= -pi4r*n��d0���v�Z����
 *  \param  i  �Œ菬���_�̐�����
 *  \param  f  �Œ菬���_�̏�����
 *  \param  n  �Ҍ�(1)�̐�����
 *  \param  *p ����32bit�ԋp�p
 *  \return ���� d0
 *
 *<hr>
 *  \par ���������F
 */
INLINE long myfmod(unsigned long i, unsigned long f, unsigned long n, unsigned long *p)		/* FFLIB B-005		*/
{
								/* PI/4(64b) * n(32b)�̌���96bit���i�[���� */
	unsigned long x0;			/* �ŏ�ʃ��[�h�i�[ */
	unsigned long x1;			/* ���ʃ��[�h�i�[(n*P4Low�̏�ʃ��[�h) */
	unsigned long y1;			/* ���ʃ��[�h�i�[(n*P4L�̉��ʃ��[�h) */
	unsigned long y2;			/* �ŉ��ʃ��[�h�i�[ */
	/* i:d0������ */
	/* f:d0������ */

	/*! �Ҍ�(3) d0+= -pi4k*n;     pi4k=(float)(int)(3.141592*1024)/1024.0)/4 */
	/*! �Ҍ�(4) d0+= -pi4r*n;     pi4r=(float)(PI/4-pi4r) */
#ifdef _DEBUG
    printf("##### myfmod IN(i = %08lx, f = %08lx, n = %08lx)\n", i, f, n);
#endif

	/* PI/4 * n��96bit�v�Z */
	y2 = n * P4LLOW;			/* y2 = 0000000000000000XXXXXXXX */
	y1 = dmulu_n( n, P4LLOW );	/* y1 = 00000000XXXXXXXX00000000 */	/* FFLIB B-009		*/
	x1 = n * P4L;				/* x1 = 00000000XXXXXXXX00000000 */
	x0 = dmulu_n( n, P4L );		/* x0 = XXXXXXXX0000000000000000 */	/* FFLIB B-009		*/

	/* 32b.+.32b+.32b���� */
#ifdef _SH
	clrt();						/*�s�r�b�g�N���A(SH) */
	x1 = addc( y1, x1 );		/* x1 = y1 + x1 �I�[�o�[�t���[������s�t���O���P�� */
	x0 = addc( x0, 0 );			/* x0 = x0 + 0 + �s �I�[�o�[�t���[���̉��Z */
#else
#ifdef __H8__
	__addc3((long *)&x0, &x1, y1);
#endif
#endif

	/* d0 += -X -> d0 -= X�̌v�Z */
	/* d0 = iiii.ffff0000 */
	/*  X = x0x0.x1x1y2y2 */
	/*  -                 */
	/*--------------------*/
	/* output iiii.ffff*p*p */
	/* 64b-96b���� */
#ifdef _SH
	y2 = negc( y2 );			/* y2 = 0 - y2 �i�s�r�b�g=1�j */
	f = subc( f, x1 );			/* f = f - x1 - T */				/* FFLIB B-005		*/
	i = subc( i, x0 );			/* i = i - x0 - T */				/* FFLIB B-005		*/
	f = rotcr( f );				/* MSB = T �����r�b�g�t�� */		/* FFLIB B-005		*/
	*p = rotcr( y2 );			/* ����32�r�b�g */					/* FFLIB B-005		*/
#else
#ifdef __H8__
	*p = __sub96( &i, &f, x0, x1, y2);
#endif
#endif

#ifdef _DEBUG
    printf("##### myfmod OUT(f = %08lx, p = %08lx)\n", f, *p);
#endif
	return (f);					/* ����32�r�b�g */					/* FFLIB B-005		*/
}

/*!
 *  \brief  tanf�֐��i���C�u�����j
 *  \param  d0  ���͒l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��Ď󂯎���Ă���j
 *  \return  tanf�l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��ĕԂ��Ă���j
 *
 *<hr>
 *  \par ���������F
 */
unsigned long tanf( unsigned long d0 )		/* FFLIB B-012 B-016 */
{
	unsigned long m;			/* ���������_�̉�����(Q32�Œ菬���_��) */
	unsigned long fpart;		/* ���������_�̏����� */
	long e;						/* ���������_�̎w���� */
	char sign;					/* �����p             */

	/*! ���������_�̎w�����Ɖ������̐؂�o��				*/
	/*! ���w�����̐؂�o�� frexp_e()						*/
	e = frexp_e( d0 );				/* -126�`e�`129 */
	/*! ���������̐؂�o�� frexp_m()						*/
	m = frexp_m( d0 );				/* MSB = 1��Q32�Œ菬���_�� */

	sign = 0;
	if( (d0 & 0x80000000) != 0 ){
		sign = ~sign;				/* sign = -1 */
	}

	if( (d0 & 0x7FFFFFFF) < 0x3F490FDB ){
		/*! ���͂̐�Βl��PI/4�����̎��́A���ڑ������v�Z���Ă� poly_oddf() */
		if( e < -16 ){
			/*! �w������-16�����̏ꍇ�A���͒l�����̂܂ܕԂ��utanf(x)=x x��0�v */
#ifdef SUPPORT_DENORMALIZE
			/* denormal�����T�|�[�g����Ȃ�tanf(x) = x */
			/* ���͒l�����̂܂ܕԂ��utanf(x)=x x��0�v */
			return (d0);			/* FFLIB B-016	*/
#else
			/* denormal�����T�|�[�g���Ȃ��Ȃ� */
			if ( (d0 & 0x7F800000) == 0 ) {
				/* denormal���̎���tanf(x) = 0.0 */
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
			/* �������̂��������_�ȉ��̐��l�����߂� */
			m >>= 1;					/* 01mmmmmmmmmmmmm */
			fpart = fraction( m, e );	/* 0.1mmmmmmmmmmmm(e=0) 0.001mmmmmmmmmm(e=-2) */
			d0 = poly_oddf(fpart, m, e, sign);			/* FFLIB B-005		*/
		}
	}else{
		/*! ���̑��͓����֐����Ă� intanF() */
		d0 = intanF(m, e, sign);
	}
	return (d0);				/* FFLIB B-016	*/
}

/*!
 *  \brief  ����tanf�֐�
 *  \param  m    Q32�Œ菬���_
 *  \param  sign ����
 *  \param  e    �w��
 *  \return  tanf�l�ilong�^�j
 */
static long intanF(unsigned long m, long e, char sign)
{
	unsigned long d1;			/* d0 - n*(PI/4) tan�l�����߂錳�̒l�iQ32�Œ菬���_�j*/
	float d2;
	unsigned long d3;			/* FFLIB B-005		*/
	unsigned long n;			/* n = (long)((float)(4/PI)*d0) */
	unsigned long i;			/* �Œ菬���_�̐����� */
	unsigned long fpart;		/* �Œ菬���_�̏����� */
	unsigned long fpart2;		/* �Œ菬���_�̏����� */
	unsigned long low_half;		/* d1�Ɠ����Ӗ���d1�̉��ʃ��[�h�iQ64�Œ菬���_�j*/
	char poly_sign;

	/* ������͔��� */
	/*! �w����32�ȏ�̏ꍇ����l�Ƃ��Ĉ���						*/
	if( e >= 32 ){
#ifdef UNSUPPORT_SINCOS_BIGINPUT
	/*! ���T�C�Y�œK���I�v�V�����ŋ���l���͔�Ή�����`���ꂽ�ꍇ
	**  big_inputL()�͎g��Ȃ���NAN��Ԃ�
	*/
		_errno = EDOM;			/* FFLIB B-015	*/
		return (TANF_NAN);		/* return nan if(nan or inf)	*/
#else
	/*! ������l�v�Z�֐����Ă� big_inputL()	*/
		return (big_inputL( m, e, sign ));	/* FFLIB B-003		*/
#endif /* UNSUPPORT_SINCOS_BIGINPUT */
	}

	/*! �Œ菬���_���Ǝw�����琮�����Ə��������v�Z */
	/*! �������� i �擾 integer()                  */
	i = integer( m, e );
	/*! �������� fpart �擾 fraction()             */
	fpart = fraction( m, e );

	/*! �Ҍ� */
	/* n = (long)((float)(4/PI)*d0)  (1) */
	/*! ���Ҍ�(1)(2) n*(��/4)��n�����߂� */
	/* �����������v�Z����i>> (31 - e)�j */
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
	/*! ���Ҍ�(3)(4) d0 = d1 + n*(PI/4)��d1�����߂� myfmod() */
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
	/*! tanf�������v�Z���Ă� poly_oddf() */
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
 *  \brief  tanf�������v�Z
 *  \param  d0  unsigned long d1^2
 *  \param  d1  unsigned long�i0�`4/PI:Q32�j
 *  \param  sign ����
 *  \param  e   �w��
 *  \return  tanf�l�ilong�^�j
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
	/* �Œ菬���_���K�� */
	while( (long)d1 > 0 ){		/* MSB = 0�Ȃ�J��Ԃ�		*/
		e--;					/* �w����-1����				*/
		d1 = d1 << 1;			/* �Œ菬���_�������V�t�g	*/
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
 *  \brief  ����l���͎��̌v�Z
 *  \param  m     Q32�Œ菬���_(0.1mmmmmmmmmmm...)
 *  \param  e     �w��
 *  \param  sign  ����
 *  \return 
 *
 *<hr>
 *  \par ���������F
 */
static long big_inputL(unsigned long m, long e, char sign)
{
	unsigned long x1, x2, x3;
	unsigned long *p;			/* 2/PI = P2af = 0.ppppppppp...		*/
#ifdef _DEBUG
	printf("----- big_inputL IN(m = %08lX, e = %d, sign = %08lX)\n", m, e, sign);
#endif
	
	e -= 2;						/* �����_�ʒu�̒��� */
	/* INF/NAN�`�F�b�N */
	if( e >= 127 ){
		/*! INF/NAN�̏ꍇNAN��Ԃ� */
		_errno = EDOM;			/* FFLIB B-015	*/
		return (TANF_NAN);		/* return nan if(nan or inf) */
	}
	p = (unsigned long *)P2af;
	while( e >= 32 ){			/* 32bit�����_�ʒu���� */
		p++;
		e -= 32;
	}
	x1 = *p++;					/* 2/PI�̐����� */
	x2 = *p++;					/* 2/PI�̏��������32bit */
	x3 = *p++;					/* 2/PI�̏���������32bit */
	if( e != 0 ){				/* 32bit�����̏����_�ʒu���� */
		x1 = (x1 << (e)) | (x2 >> (32 - e));
		x2 = (x2 << (e)) | (x3 >> (32 - e));
	}
	/* x1*m�̏������i��Z���ʂ̉���32bit�j��x2*m�̏������i��Z���ʂ̏��32bit�j�����Z����B */
	x1 = x1 * m + dmulu_h( x2, m );		/* 0.0<=x1<1.0 */
	/*! d0*2/PI�̏������i�]��j�����߂� */
	/* d0 = PI/4 * �]�� */
	m = dmulu_h( x1, P4L );				/* 0.0<=d2<2PI */
	/*! �{�������Ă� intanF() */
	return (intanF(m, 3, sign));
}
#endif /* UNSUPPORT_SINCOS_BIGINPUT */				/* FFLIB B-003	*/
