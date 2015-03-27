/********************************************************************************/
/* Copyright (C) 1992,2007 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*! \file  fflb_sh.h
 *  \brief FFlb SH�p�w�b�_�t�@�C��
 *  \note  �g�ݍ��݊֐���ASH�p�̒萔���`����
 */
#ifndef CMN_SH
#define CMN_SH


/* �g�ݍ��݊֐��w�b�_�t�@�C���C���N���[�h */
#include <machine.h>	/* for dmulu_h(), dmuls_h(), div1(), etc..(SH instruction) */

/*
**------------------------
** FFlib�I�v�V�����}�N��
**------------------------
*/
/* �^�[�Q�b�g */
#define TARGET_SH

/* denormalize�T�|�[�g�p�X�C�b�` */
#define SUPPORT_DENORMALIZE


/*
**------------------------
** �萔�E�}�N����`
**------------------------
*/
/* ���������_����l��` */
#define PLS_NAN		0x7F800001
#define MNS_NAN		0xFF800001
#define PLS_INF		0x7F800000
#define MNS_INF		0xFF800000
#define MNS_ZERO	0x80000000

/* �֐��p����l��` */
#define SINF_NAN	PLS_NAN
#define LOGF_NAN	PLS_NAN
#define SQRTF_NAN	PLS_NAN
#define TANF_NAN	PLS_NAN

/* denormalize�����T�|�[�g���Ȃ��ꍇ��sqrtf�߂�l��`*/
#define SQRTF_RTN_DENORM	(0)		/* FFLIB B-016 */

/*
**------------------------
** errno�p�̒�`
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
/* SH-1�ɂ�dmulx_h()�g�ݍ��݊֐������� */
/* �Ǝ����������� */

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
/* SH-1�ȊO�̏ꍇ�́Admulx_n��dmulx_h�ɒu�������� */
#define dmuls_n dmuls_h										/* FFLIB B-010		*/
#define dmulu_n dmulu_h										/* FFLIB B-009		*/
#endif /* _SH1 */



#endif /* CMN_SH */
