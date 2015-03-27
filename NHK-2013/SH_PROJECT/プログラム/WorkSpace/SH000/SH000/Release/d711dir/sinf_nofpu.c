/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file sinf.c
 *  \brief FFlib sinf�֐��t�@�C��
 */

#include "common.h"


/*!
 *  \brief  sinf�֐��i���C�u�����j
 *  \param  d0  ���͒l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��Ď󂯎���Ă���j
 *  \return  sinf�l
 * �i����̎�Ԃ��Ȃ����߁Afloat�^��unsigned long�^�Ƃ��ĕԂ��Ă���j
 *
 *<hr>
 *  \par ���������F
 */
unsigned long sinf(unsigned long d0)	/* FFLIB B-012 B-016 */
{	
	unsigned long m;			/* ���������_�̉�����(Q32�Œ菬���_��)	*/
	unsigned long fpart;		/* ���������_�̏�����					*/
	long e;						/* ���������_�̎w����					*/

	/*! ���������_�̎w�����Ɖ������̐؂�o��				*/
	/*! ���w�����̐؂�o�� frexp_e()						*/
	e = frexp_e( d0 );			/* -126�`e�`129				*/
	/*! ���������̐؂�o�� frexp_m()						*/
	m = frexp_m( d0 );			/* MSB = 1��Q32�Œ菬���_��	*/

	/*! �w�����̃`�F�b�N */
	if( e <= 0 ){
		/* ���͒l��0.5�ȉ��̏ꍇ */
		if( e < -16 ){
			/*! �w������-16�����̏ꍇ�A���͒l�����̂܂ܕԂ��usin(x)=x x��0�v */
		}else{
			/*! ���w�������O�ȉ��̏ꍇ�͒��ڑ������v�Z������ __poly_sinL()   */
			/* �������̂��������_�ȉ��̐��l�����߂� */
			m >>= 1;					/* 01mmmmmmmmmmmmm								*/
			fpart = m >> (-e);			/* 0.1mmmmmmmmmmmm(e=0) 0.001mmmmmmmmmm(e=-2)	*/
			d0 = __poly_sinL( (long)fpart, (long)m, e, (long)d0 );		/* FFLIB B-011	*/
		}
	}else{
		/*! ���w�������P�ȏ�̏ꍇ�����֐����Ă� __insinL() */
		/*! �@(�ُ�l�`�F�b�N�͓����֐��ōs�Ȃ��Ă���)      */

		/* ���͒l�����̎� n = 0�A���̎� n = 4 */
		unsigned long n = (long)d0 < 0 ? 4 : 0;
		d0 = __insinL( n, m, e, d0);									/* FFLIB B-011	*/
	}
	return (d0);					/* FFLIB B-016 */
}
