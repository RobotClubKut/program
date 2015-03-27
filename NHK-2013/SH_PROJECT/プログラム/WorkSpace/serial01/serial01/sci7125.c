//
// SH2-7125(48MHz) �pSCI���W���[��
//
//
// 2007.02.15 K.Nishimura
//
#include <stdarg.h>
#include "iodefine.h"

void SCI_init(void);
short SCI_write(unsigned char c);
short SCI_read(unsigned char *c);


#define SCI_RX_BUF_SHIFT   3
#define SCI_RX_BUF_SIZE   (1<<SCI_RX_BUF_SHIFT)
#define SCI_RX_BUF_MASK   (SCI_RX_BUF_SIZE-1)

volatile static struct stSCI_RX{
	unsigned short rdptr;                // ���[�h�|�C���^
	unsigned short wrptr;                // ���C�g�|�C���^
	unsigned short dataNum;              // �o�b�t�@���f�[�^��
	unsigned char buf[SCI_RX_BUF_SIZE];  // ��M�o�b�t�@
}SCI_RX;

// --------------------------------------------------------
// SCI ������
// --------------------------------------------------------
void SCI_init(void){

	SCI_RX.rdptr = 0;
	SCI_RX.wrptr = 0;
	SCI_RX.dataNum = 0;

	// �X�^���o�C�@�\�̉���
	STB.CR3.BIT._SCI1 = 0;       // SCI1 start

	// SCI�����~
	SCI1.SCSCR.BIT.TIE = 0;      // ���M������:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.RIE = 0;      // ��M������:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.TE  = 0;      // ���M����:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.RE  = 0;      // ��M����:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.MPIE = 0;     // MP�����݃C�l�[�u��
	SCI1.SCSCR.BIT.TEIE = 0;     // ���M�I��������:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.CKE  = 0;     // �N���b�N�\�[�X�I��

	// SCI�ݒ�
	SCI1.SCSMR.BIT.CA   = 0;      // 0:���������A1:�N���b�N����
	SCI1.SCSMR.BIT.CHR  = 0;      // 0:8�r�b�g�f�[�^�A1:7�r�b�g�f�[�^
	SCI1.SCSMR.BIT._PE  = 0;      // 0:�p���e�B�֎~�A1:�p���e�B����
	SCI1.SCSMR.BIT.OE   = 0;      // 0:�����p���e�B�A1:��p���e�B
	SCI1.SCSMR.BIT.STOP = 0;      // 0:1�X�g�b�v�r�b�g�A1:2�X�g�b�v�r�b�g
	SCI1.SCSMR.BIT.MP   = 0;      // �}���`�v���Z�b�T���[�h 0:�֎~,1:����
	SCI1.SCSMR.BIT.CKS  = 0;      // �N���b�N�Z���N�g 00:1/1 , 01:1/4 , 10:1/16 , 11:1/64

	// �{�[���[�g�ݒ�
	SCI1.SCBRR = 19;             // 38400 bps

	// SSR�����ݒ�
	SCI1.SCSSR.BIT.TDRE = 0;     // TDR�G���v�e�B
	SCI1.SCSSR.BIT.RDRF = 0;     // RDR�t��
	SCI1.SCSSR.BIT.ORER = 0;     // �I�[�o�[�����G���[
	SCI1.SCSSR.BIT.FER  = 0;     // �t���[�~���O�G���[
	SCI1.SCSSR.BIT.PER  = 0;     // �p���e�B�G���[

	// TXD�[�q�ݒ�
	PFC.PACRL2.BIT.PA4MD = 1;    // 000:PA4,001:TXD1,111:IRQ2

	// RXD�[�q�ݒ�
	PFC.PACRL1.BIT.PA3MD = 1;    // 000:PA3,001:RXD1,111:IRQ1

	SCI1.SCSCR.BIT.RIE = 1;      // ��M������:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.TE  = 1;      // ���M����:����(1)/�֎~(0)
	SCI1.SCSCR.BIT.RE  = 1;      // ��M����:����(1)/�֎~(0)

}

// --------------------------------------------------------
// SCI 1�o�C�g���M
//   ����   - unsigned char c : ���M�f�[�^
//   �߂�l - 0:���M���s�A1:���M����
// --------------------------------------------------------
short SCI_write(unsigned char c){
	unsigned long i;
	unsigned short flag;
	
	// ���M�o�b�t�@����������̂��|�[�����O�őҋ@
	// �^�C���A�E�g����
	flag = 0;
	for(i=0;i<0x00200000;i++){
		if(SCI1.SCSSR.BIT.TDRE){
			flag = 1;
			break;
		}
	}
	
	if(flag){
		SCI1.SCTDR = c;  // ���M�o�b�t�@�Ƀf�[�^�Z�b�g
		SCI1.SCSSR.BIT.TDRE = 0;
		return 1;
	}
	return 0;
}

// --------------------------------------------------------
// ��M������
//   �ݒ�
//     intprg.c �̐擪�����Ɉȉ���ǉ�
//       extern void intprg_rxi1(void);
//     intprg.c ����SCI�����ݕ����ȉ��̂悤�ɏC��
//       void INT_SCI1_RXI1(void){intprg_rxi1();}
//   �����ݐݒ�
//	   INTC.IPRL.BIT._SCI1 = 0xF;    // ���荞�݃��x���ݒ�(SCI1)
//	   set_imask(14);                // ���荞�݃}�X�N�N���A
// --------------------------------------------------------
#pragma regsave(intprg_rxi1)
void intprg_rxi1(void){
	unsigned char c;

	SCI1.SCSSR.BIT.ORER = 0;     // �I�[�o�[�����G���[
	SCI1.SCSSR.BIT.FER  = 0;     // �t���[�~���O�G���[
	SCI1.SCSSR.BIT.PER  = 0;     // �p���e�B�G���[

	// ��M�o�b�t�@�Ƀf�[�^�i�[
	if(SCI1.SCSSR.BIT.RDRF){                      // ��M�t���O�`�F�b�N
		SCI1.SCSSR.BIT.RDRF = 0;                  // ��M�t���O�N���A
		c = SCI1.SCRDR;                           // ��M�f�[�^�擾
		if(SCI_RX.dataNum != SCI_RX_BUF_SIZE){    // ��M�o�b�t�@�̋󂫃`�F�b�N
			SCI_RX.buf[SCI_RX.wrptr] = c;         // ��M�o�b�t�@�Ɋi�[
			SCI_RX.wrptr = (SCI_RX.wrptr + 1 ) & SCI_RX_BUF_MASK;  // ���C�g�|�C���^�̍X�V
			SCI_RX.dataNum++;                     // �f�[�^���̃C���N�������g
		}
	}
}

// --------------------------------------------------------
// SCI 1�o�C�g��M
//   ����   - unsigned char *c : ��M�f�[�^(�|�C���^�n��)
//   �߂�l - 0:��M�Ȃ��A1:��M����
// --------------------------------------------------------
short SCI_read(unsigned char *c){
	// ��M�o�b�t�@����f�[�^���o��
	if(SCI_RX.dataNum != 0){                    // �f�[�^���`�F�b�N
		*c = SCI_RX.buf[SCI_RX.rdptr];          // ��M�o�b�t�@����f�[�^�擾
		SCI_RX.rdptr = (SCI_RX.rdptr + 1 ) & SCI_RX_BUF_MASK;  // ���[�h�|�C���^�̍X�V
		SCI_RX.dataNum--;                       // �f�[�^���̃f�N�������g
		return 1;
	}
	
	*c = 0;
	return 0;
}

// --------------------------------------------------------
// 1������M
//   ����   - 
//   �߂�l - 
// --------------------------------------------------------
short s_read(unsigned char *c){
	short ret=0;

	// ��M�o�b�t�@�Ƀf�[�^�i�[
	if(SCI1.SCSSR.BIT.RDRF){             // ��M�t���O�`�F�b�N
		SCI1.SCSSR.BIT.RDRF = 0;         // ��M�t���O�N���A
		*c = SCI1.SCRDR;                 // ��M�f�[�^�擾
		// ���s�R�[�h�̕ϊ�
		if(*c == 0x0D) *c = '\n';
		ret = 1;
	}
	return ret;
}
