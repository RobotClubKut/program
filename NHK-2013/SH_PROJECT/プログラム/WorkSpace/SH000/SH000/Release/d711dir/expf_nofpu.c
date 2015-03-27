/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file expf.c
 *  \brief FFlib expf�֐��t�@�C��
 * 
 */

#include "common.h"

/* loge(2)�萔 */
/* ���ۂ�S31�Ȃǂ��|���ČŒ菬���_�����Ă��邽�߁A�g�p���Ă��Ȃ� */
/* #define logE2		(0.6931471805599453094172321214581765680755) */

/* #define logE	1.442695041 */
/*! log2(e)�萔(Q31�Œ菬���_��) */
/* expf.c�Ŏg�p */
#define LOGEL		((unsigned long)0xB8AA3B29) /* S31*logE */

#undef MUL
/*! �������v�Z���̏�Z��` */
#define MUL(x,y) (dmuls_h(x, y)<<1)


/*! expf�p�������W���e�[�u�� */
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
 * �����֐��i�v���g�^�C�v�j
 *--------------------------------------------------*/
/* power2��float�������ߎ��l�����߂� */
static long poly_pow2L(long d1, long e, long sign);


/*!
 *  \brief  expf�֐��i���C�u�����j
 *  \param  d0  ���͒l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��Ď󂯎���Ă���j
 *  \return  expf�l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��ĕԂ��Ă���j
 *  \note ���������_���Œ菬���_�̐������Ə������ɕ�����\n
 *        exp(x) = 2^(x*log2(E))���v�Z����\n
 *        ���͂����ł������ꍇ��\n
 *        2^(-x) = 2^(x+1) * 2^(1-x)\n
 *
 *<hr>
 *  \par ���������F
 */
unsigned long expf(unsigned long d0)	/* FFLIB B-012 B-016 */
{
	unsigned long m;			/* ���������_�̉�����(Q32�Œ菬���_��) */
	unsigned long fpart;		/* ���������_�̏����� */
	long e;						/* ���������_�̎w���� */
	long i;						/* ���������_�̐����� */

	/*! ���������_�̎w�����Ɖ������̐؂�o��				*/
	/*! ���w�����̐؂�o�� frexp_e()						*/
	e = frexp_e( d0 );			/* -126�`e�`129				*/
	/*! ���������̐؂�o�� frexp_m()						*/
	m = frexp_m( d0 );			/* MSB=1��Q32�Œ菬���_��	*/

	/*! �ُ�l�`�F�b�N */
	/*! ���w������7���傫������e^x�́{����Ԃ� */
	/* e^(0.5*2^8) = e^128 = 3.887708405*10^55 ��float�̍ő�l�𒴂��Ă���� */
	if( e > 7 ){
		/*! ���}NAN�̎��́}NAN��Ԃ�(�݊����̂��ߐ�������ʂ���) */
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
		/*! �������͂̎��͂O��Ԃ� e^(-128�`-��) = 0 */
		if( (long)d0 < 0 ){
			d0 = 0;
			return (d0);		/* FFLIB B-016	*/
		}else{
			_errno = ERANGE;	/* FFLIB B-015	*/
			d0 = PLS_INF;
			return (d0);		/* FFLIB B-016	*/
		}
	}

	/*! ���w������-28�����̎���e^x��1.0��Ԃ� */
	if( e < -28){
		return (0x3F800000);	/* FFLIB B-016	*/
	}

	/*! �Œ菬���_���Ǝw�����琮�����Ə��������v�Z */
	/*! �������� i �擾 integer()                  */
	i = integer( m, e );
	/*! �������� fpart �擾 fraction()             */
	fpart = fraction( m, e );

	/*! ���͕ϊ� x*log2(E)
	**  (����x�͐�������i�ŏ�������fpart)
	*/
	/* ���ꂼ��32b�Ȃ̂ŏ����_�ʒu�ɒ��ӂ��ď�Z�Ɖ��Z������ */
	/* �W��log2(E)��LOGEL��Q31�Œ菬���_�� */
	/* LOGEL =     .EEEE(Q31)              */
	/* fpart =     .ffff(Q32)              */
	/* i     = iiii.    (Q0)               */
	/* ��������log2(E)�̏�Z���ʏ��32b���������ɑ�� */
	fpart = dmulu_h( fpart, LOGEL );	/* .ffff * .EEEE = .(ffff)ffff(Q63) = fpart(Q31) */
	/* ��������log2(E)�̏�Z���ʉ���32b����(m)�ɑ�� */
	m = i * LOGEL;						/* iiii. * .EEEE = iiii.(iiii)(Q31) = m(Q31) */
	/* ��������log2(E)�̏�Z���ʏ��32b�𐮐����ɑ�� */
	i = dmulu_h( i, LOGEL );			/* iiii. * .EEEE = (iiii).iiii(Q31) = i(Q-1) */

	/* 32b.+.32b+.32b���� */
#ifdef _SH
	clrt();								/* ��̌v�Z�ׂ̈̂s�r�b�g�N���A */
	/* �������̉��Z */
	fpart = addc( m, fpart);			/* .mmmm + .ffff = .ffff(Q31) = fpart(Q31) */
										/* �s�r�b�g�ɂ��ӂꂽMSB������ */
	/* �L�����[�̉��Z�i�s�r�b�g�j */
	i = addc( 0, i);					/* 0 + iiii. + T = .iiii(Q-1) = i(Q-1) */

	/* 64b��1b�V�t�g���� */
	fpart = rotcl( fpart );				/* Q31�ɂȂ�����������Q32�ɖ߂� */
										/* �s�r�b�g�ɂ��ӂꂽMSB������ */
	i = rotcl( i );						/* LSB�ɂs�r�b�g������ */
										/* Q-1�ɂȂ�����������Q0�ɖ߂� */
#else
#ifdef __H8__
	__addc3( &i, &fpart, m);

	/* 64b��1b�V�t�g���� */
	__shll64(&i, &fpart);
#endif	/* __H8__ */
#endif	/* _SH */
	/* �����͂̎��� */
	if( (long)d0 < 0 ){					/* i+fpart --> (-i-1)+(1-fpart) */
		i = -i - 1;
		fpart = ~fpart;					/* Q32�̃r�b�g���]��1-fpart�Ɠ����Ӗ��ɂȂ� */
	}

	/*! power2��float�������ߎ��l�����߂� poly_pow2L() */
	/* �߂�l�͕��������_���ɂȂ��Ă���i�^��long�j    */
	d0 = poly_pow2L( fpart>>1, (short)i , 0 );
	return (d0);						/* FFLIB B-016	*/
}

/*!
 *  \brief  power2��float�������ߎ��l�����߂�
 *  \param  d1   ���͒l
 *  \param  e    �w���l
 *  \param  sign �����p
 *  \return  power�ߎ��l
 */
static long poly_pow2L(long d1, long e, long sign) /* d3,e: for padding */
{
	unsigned long ans;		/* pow2���������� */
	long *p;				/* �������W���e�[�u���ւ̃|�C���^ */

	p = (const long *)pow2coeff1L;
	ans = *p++;
#ifdef OPT_TYPE_SIZE
	/* ROM�T�C�Y�D��I�v�V������I�������ꍇ�͑������v�Z�����[�v�ɂ��� */
	/* �������R���p�C���̍œK���I�v�V�����Ń��[�v�W�J��I�������ꍇ */
	/* �W�J�����\�������� */
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
