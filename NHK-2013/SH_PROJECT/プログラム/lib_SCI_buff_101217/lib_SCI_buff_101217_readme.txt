SCI�֐�
lib_SCI_buff_101217.c
lib_SCI_buff_101217.h
	for SH7125 @ HEW
	Wrote by conpe_


SH7125��SCI1�p�̑���M�֐��ł��B



�y�g�����z

���߂�
void SCI1_setup(int br);
���Ăяo����SCI��������������܂��B�����̓{�[���[�g�B4800�`115200bps�܂ōs������ۂ��ł��B


[���M]

�o�b�t�@���g���ď������荞�݂ɂ�著�M���܂��B
�Ȃ̂ő��M�҂����ɗ͂��܂���B

intprg.c��INT_SCI1_TXI1����intSCI1_tx_buff()���Ăяo���悤�ɂ��Ă��������B
resetprg.c��#define SR_Init��0x00000000�ɂ���B

�o�b�t�@�T�C�Y��lib_SCI_buff_101217.h�̕��Ŏw��B


��{�I�ɂ́A
 void SCI1_printf(char *, ...);
�ő��M���Ă����΂������[�ł��B���ʂ�printf�Ɠ����g�����B
�ϊ��d�l��%d,%x,%X,%c,%s�̂ݑΉ����Ă��܂��B�����Ή��߂�ǂ��B

����,����(��)�����o�͂���΂����񂾂��ǂ��ĂƂ��́A
 char SCI1_tx_char(char);
 void SCI1_tx_str(char *);
 void SCI1_tx_d(long);
 void SCI1_tx_x(long);
 void SCI1_tx_X(long);
������ւ�g���Ă݂Ă��������BSCI1_printf�g������������҂葬���͂��ł��B



[��M]
1������M����܂ő҂Ƃ��͂���
 unsigned char SCI1_rx_char(void);

�҂��Ȃ��Ƃ��͂���
 unsigned char SCI1_rx_char_nowait(void);

��������M�������Ƃ��͂���
 unsigned int SCI1_rx_d(void);
�����P�^�Ή��B
�G���^�[������܂Ŏ�M�𑱂��܂��B
�����ȊO�������Ƃ��͓ǂݔ�΂��܂��B




�ŏI�X�V
2010/12/17
