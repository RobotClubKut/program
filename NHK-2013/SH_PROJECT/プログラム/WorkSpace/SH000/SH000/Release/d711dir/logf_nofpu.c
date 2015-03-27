/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file logf.c
 *  \brief FFlib logf�֐��t�@�C��
 */

#include "common.h"


/*! logf�p�������W���e�[�u�� */
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
/*! logf�p�������W���e�[�u�� */
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
/*! �������v�Z���̏�Z��` */
#define MUL(x,y) (dmuls_h(x, y)<<1)

/*--------------------------------------------------
 * �����֐��i�v���g�^�C�v�j
 *--------------------------------------------------*/
/* Log��float�������ߎ��l�����߂� */
static long poly_logL(long d1, long *p, long e, long sign);			/* FFLIB B-011	*/


/*!
 *  \brief  logf�֐��i���C�u�����j
 *  \param  d0  ���͒l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��Ď󂯎���Ă���j
 *  \return  logf�l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��ĕԂ��Ă���j
 *
 *<hr>
 *  \par ���������F
 */
unsigned long logf(unsigned long d0)	/* FFLIB B-012 B-016 */
{
	unsigned long m;			/* ���������_�̉�����(Q32�Œ菬���_��) */
	unsigned long fpart;		/* ���������_�̏����� */
	long e;						/* ���������_�̎w���� */
	long i;						/* ���������_�̐����� */

	long sign, *p;

	/*! ���������_�̎w�����Ɖ������̐؂�o��				*/
	/*! ���w�����̐؂�o�� frexp_e()						*/
	e = frexp_e( d0 );		/* -126�`e�`129	*/
	/*! ���������̐؂�o�� frexp_m()						*/
	m = frexp_m( d0 );		/* MSB = 1		*/

	/*! �ُ�l�`�F�b�N */
	if( d0 - 0x00800000 >= 0x7F000000 ){
		/* +INF, +NAN, ���̎� */
		/* �ɏ��l(�w�����O)�܂��͂O�̎� */
		if ( (d0 << 1) == 0 ) {
			/*! ��0.0�A-0.0���͂̎��́|����Ԃ� */
			_errno = ERANGE;				/* FFLIB B-015	*/
			d0 = MNS_INF;
			return (d0);					/* FFLIB B-016	*/
		} else if ( (long)d0 < 0 ) {
			/*! �������͂̎���NAN��Ԃ� */
			_errno = EDOM;					/* FFLIB B-015	*/
			d0 = LOGF_NAN;
			return (d0);					/* FFLIB B-016	*/
		} else if ( (d0 >> 23) == 0 ) {
			/* denormal���̎��� */
#ifdef SUPPORT_DENORMALIZE
			/*! ��denormal�����T�|�[�g����Ȃ琳�K������ */
			if( e <= -126 ){
				m <<= 1;					/* �w�������O�̎��́A������MSB = 1�������Ă��� */
											/* ���K������ */
				while( (long)m > 0 ){		/* MSB = 0�Ȃ�J��Ԃ�		*/
					e--;					/* �w����-1����				*/
					m <<= 1;				/* �Œ菬���_�������V�t�g	*/
				}
			}
#else
			/*! ��denormal�����T�|�[�g���Ȃ��Ȃ�0.0�̎��Ɠ����|����Ԃ� */
			_errno = ERANGE;				/* FFLIB B-015	*/
			d0 = MNS_INF;
			return (d0);					/* FFLIB B-016	*/
#endif
		} else if ( (d0 & 0x007FFFFF) == 0 ) {
			/*! ��+INF�̎��͂��̂܂ܕԂ� */
			_errno = ERANGE;				/* FFLIB B-015	*/
			return (d0);					/* FFLIB B-016	*/
		} else {
			/*! ��+NAN�̎���NAN��Ԃ� */
			_errno = EDOM;					/* FFLIB B-015	*/
			d0 = LOGF_NAN;
			return (d0);					/* FFLIB B-016	*/
		}
	}

	if( e < 1 ){
	/* ���͂�1.0�����̎� */
		sign = -1;				/* ���ʕ����͕� */
		e = -e;
								/* m-1.0 */
		p = (long *)coeffLL;
  	}else{ 		
	/* ���͂�1.0�ȏ�̎� */
		sign = 0;				/* ���ʕ����͐� */
		e--;
  		m = (m << 1) >> 1;			/* (m*2-1.0)>>1 */
		p = (const long *)coeffLR;
	}

	/*! log��float�������ߎ��l�����߂� poly_logL()  */
	/* �߂�l�͕��������_���ɂȂ��Ă���i�^��long�j */
	d0 = poly_logL( m, p, e, sign );
	return (d0);				/* FFLIB B-016	*/
}

/*!
 *  \brief  Log��float�������ߎ��l�����߂�
 *  \param  d1   ���͒l
 *  \param  p    �������W���l�ւ̃|�C���^
 *  \param  e    �w��
 *  \param  sign �����p
 *  \return  log�ߎ��l
 */
static long poly_logL(long d1, long *p, long e, long sign)				/* FFLIB B-011	*/
{
	long n;					/* log(x)�l���ʂ̕��������_�w�����ɂ����� */
	long ans;				/* log���������ʏ��32b */
	unsigned long wer;		/* log���������ʉ���32b */
	
	/* log(d1)�v�Z */
	ans = *p++;
#ifdef OPT_TYPE_SIZE
	/* ROM�T�C�Y�D��I�v�V������I�������ꍇ�͑������v�Z�����[�v�ɂ��� */
	/* �������R���p�C���̍œK���I�v�V�����Ń��[�v�W�J��I�������ꍇ */
	/* �W�J�����\�������� */
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

	/* 64b��1b�V�t�g���� */
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
	/* n��0�Ȃ�Alog(d1)�v�Z�����ł��� */
		/* log(d1)���O��������A�O��Ԃ� */
		if( ans == 0 ){
			return (0);
		}
		n = 1;
		while( ans > 0 ){
			/* 64b��1b�V�t�g���� */
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
	/* n��1�ȏ�Ȃ�An*log(2)���v�Z���� */
		/* �W��log(2)��*p�Œ��g��S31*logE2 */
		/* 1 <= e(Q0) <= 129    */
		/* logE2 =   .EEEE(Q31) */
		/* ans */
		n = e * (*p);			/* e. * .logE2 = e.(e) => n */
		e = dmulu_h( (unsigned long)e, (unsigned long)*p );	/* e. * .logE2 = (e.)e => e(MAX 88) */

		/* 32b.+.32b+.32b���� */
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
			/* 64b�E1b�V�t�g���� */
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

