/**************************************************
	�����V���A���ŉ������邽�߂̃T���v���v���O�����B
							The coll of a distant star. for me?
																			by����
**************************************************/

/****************************************
	�C���N���[�h�t�@�C��
****************************************/
#include <7125.h>

/****************************************
	�}�N���ݒ�
****************************************/
#define whit while(Wheit_i)Wheit_i-=1
#define LED00 PE.DRL.BIT.B0
#define LED01 PE.DRL.BIT.B1
/****************************************
	�O���[�o���ϐ�
****************************************/
char TXD1[30],RXD1[10];

/****************************************
		SH_INIT SH������
****************************************/
void SH_INIT(unsigned int Wheit_i){
	whit;		//�����N���҂�
	//	���荞�ݕs����
	SetSRReg(0xf);
	
	// IO
	PFC.PECRL1.BIT.PE0MD=1;		//IO�|�[�g�ɐݒ�
	PFC.PECRL1.BIT.PE1MD=1;		//IO�|�[�g�ɐݒ�
	PFC.PEIORL.BIT.B0=1;			//�o�̓|�[�g�ɐݒ�
	PFC.PEIORL.BIT.B1=1;			//�o�̓|�[�g�ɐݒ�


	//	SCI1
	SCI1_INIT(br115200,0xa,TXD1,sizeof(TXD1),RXD1,sizeof(RXD1));
	PFC.PACRL1.BIT.PA3MD = 1;//PA3:001-RXD1����
	PFC.PACRL2.BIT.PA4MD = 1;//PA4:001-TXD1�o��

	//	MTU2
	STB.CR4.BIT._MTU2=0;		//�X�^���o�C���A
	MTU2.TSTR.BIT.CST0=MTU2.TSTR.BIT.CST1=0;		//�J�E���g��~
	
	
	//	MTU2 0��1
	
	MTU2.TSTR.BIT.CST1 = MTU2.TSTR.BIT.CST0 = 0;     //MTU21,20�J�E���g��~
	MTU21.TCR.BIT.TPSC = 0;     //�N���b�N���g����/4
	MTU20.TCR.BIT.TPSC = 0;     //�N���b�N���g����/4
	MTU21.TCR.BIT.CCLR = 1;     //TGRA�R���y�A�}�b�`��TCNT�N���A
	MTU20.TCR.BIT.CCLR = 7;     //�����N���A
	MTU2.TSYR.BYTE = 3;         //�`���l��0�C1��������
	MTU20.TIOR.BIT.IOA = 5;     //������Ԃ�1�o�� �R���y�A�}�b�`������0�o��
	MTU20.TIOR.BIT.IOB = 5;     //������Ԃ�1�o�� �R���y�A�}�b�`������0�o��
	MTU20.TIOR.BIT.IOC = 5;     //������Ԃ�1�o�� �R���y�A�}�b�`������0�o��
	MTU20.TIOR.BIT.IOD = 5;     //������Ԃ�1�o�� �R���y�A�}�b�`������0�o��

	MTU21.TGRA = 5000;
	MTU20.TGRA = 100;
	MTU20.TGRB = 5000;
	MTU20.TGRC = 100;
	MTU20.TGRD = 100;
	
	MTU20.TMDR.BIT.MD = 3;      //PWM���[�h2
	MTU21.TMDR.BIT.MD = 3;      //PWM���[�h2

}

/****************************************
		���C��
****************************************/
void main(){

	SH_INIT(1<<21);
	SetSRReg(0x0);
	MTU2.TSTR.BIT.CST0=MTU2.TSTR.BIT.CST1=1;		//�J�E���g�J�n


	SCI1_PRINTF("���b�c�S�[\n");
	int i=5000;
	LED01=1;
	while(1){
		while(i--);
		i=500;
		MTU20.TGRA=(MTU20.TGRA==5000?0:MTU20.TGRA+1);
			
//		LED01=~LED01;
	
	}


}

