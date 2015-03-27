/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = e_calci :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

/*
**  ���ʃT�u���[�`�� _lsft(), _add() �̒��ł� 2�o�C�g�A�N�Z�X���s����ׁA
**  �o�b�t�@�ւ̃|�C���^�� 2�o�C�g��������Ă��Ȃ���΂Ȃ�Ȃ��B
*/

#define ALIGN2_UP(x)     (((x)+1)&~1)  /* 2�o�C�g���E�����؂�グ */
#define ALIGN2_DOWN(x)   ((x)&(~1))    /* 2�o�C�g���E�����؂�̂� */

#define STRBYTE     (31)               /* 31 = ����������10�i�����̏�� */
#define NUMBYTE     ALIGN2_UP(13)      /* 13 = ���l 1*(10**31) �̏��v�o�C�g�� */

extern void *memcpy(void *, const void *, size_t);
extern INT    _lsfts(UCHAR*, INT, SHORT);
extern VOID   _add(UCHAR*, UCHAR*, INT);
extern INT    _lsft(UCHAR*, INT);
extern VOID   _calcint2(UCHAR*, INT, INT);
