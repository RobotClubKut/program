/***********************************************************************/
/*  HEW����͂��߂܂��Ă�낵���ł��B�B  	                           */
/***********************************************************************/

#include "iodefine.h"
#include "lib_SCI_buff_101217.c"
/****************************************
	�}�N���ݒ�
****************************************/
#define whit while(Wheit_i)Wheit_i-=1
#define LED00 PE.DRL.BIT.B0
#define LED01 PE.DRL.BIT.B1

/****************************************
		SH_INIT SH������
****************************************/
void SH_INIT(unsigned int Wheit_i){
	whit;		//�����N���҂�
	//	���荞�ݕs����
//	SetSRReg(0xf);
	
	// IO
	PFC.PECRL1.BIT.PE0MD=0;		//IO�|�[�g�ɐݒ�
	PFC.PECRL1.BIT.PE1MD=0;		//IO�|�[�g�ɐݒ�
	PFC.PEIORL.BIT.B0=1;			//�o�̓|�[�g�ɐݒ�
	PFC.PEIORL.BIT.B1=1;			//�o�̓|�[�g�ɐݒ�


	//	SCI1
//	SCI1_INIT(br115200,0xa,TXD1,sizeof(TXD1),RXD1,sizeof(RXD1));
//	PFC.PACRL1.BIT.PA3MD = 1;//PA3:001-RXD1����
//	PFC.PACRL2.BIT.PA4MD = 1;//PA4:001-TXD1�o��


}



void main(void){

	void intSCI1_tx_buff(void);
	void SCI1_setup(19200);

SCI1_setup(19200);

	SH_INIT(1<<22);
//	SetSRReg(0x0);


//	SCI1_PRINTF("���b�c�S�[\n");
	
	LED00=1;
	while(1){
		LED01=~LED01;
	
	}

}
