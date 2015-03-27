/********************************************/
/*				SCI1�֐�					*/
/*					for SH7125 @ HEW		*/
/*					Wrote by conpe_			*/
/*							2010/12/17		*/
/********************************************/

//SCI1�p�̑���M�֐��ł��B

// �o�b�t�@���g���ď������荞�݂ɂ�著�M
// �o�b�t�@�̃T�C�Y��.h�̕��Ŏw��
// intprg.c��INT_SCI1_TXI1����intSCI1_tx_buff()���Ăяo���ĂˁB
// resetprg.c��#define SR_Init��0x00000000�ɂ���

// �o�b�t�@�����ӂꂻ���ɂȂ�����A���M���ǂ����܂ő҂̂Œ��ӁB

#include <stdarg.h>
#include "iodefine.h"
#include "lib_SCI_buff_101217.h"


char sci1_tx_buffer[SCI1_TxBuffSize];	//�o�b�t�@
unsigned short sci1_tx_writep;			//�������݃|�C���^
unsigned short sci1_tx_readp;			//�ǂݍ��݃|�C���^


/*********************
SCI1������
�����F�{�[���[�g 4800�`115200
**********************/
void SCI1_setup(int br){
	int i;
	
	STB.CR3.BIT._SCI1=0;		// SCI1 ����J�n
	SCI1.SCSCR.BYTE = 0x00;
	SCI1.SCSCR.BIT.CKE = 0x00;	// �N���b�N�\�[�X
	SCI1.SCSMR.BYTE = 0x00;		// ����������, 8bit, �p���e�B����, �X�g�b�v�r�b�g1, �}���`�v���Z�b�T����
	SCI1.SCSMR.BIT.CKS = 0;		// �N���b�N
	SCI1.SCSDCR.BIT.DIR = 0x00;	// LSB���瑗��M
	
	SCI1.SCBRR = Pphi*2*1000000/64/br-(115200>br);	//�{�[���[�g�̐ݒ�
	
	for(i=0;i<65000;i++);		// 1byte���ԑ҂�
	PFC.PACRL1.BIT.PA3MD = 1;	// PA3 �[�q�@�\�ݒ� RXD1����
	PFC.PACRL2.BIT.PA4MD = 1;	// PA4 �[�q�@�\�ݒ� TXD1�o��
	
	SCI1.SCSCR.BYTE = 0x30;		// ����M����
	
	//���荞�݋���
	//SCI1.SCSCR.BIT.RIE = 1;
	INTC.IPRL.BIT._SCI1 = 0x01;	// ���荞�݃��x��
	
}



/*********************
SCI1 �������M
�����F�Ȃ�
�Ԓl�F�Ȃ�
TDRE�̊��荞�݂ɂ���ē���
**********************/
void intSCI1_tx_buff(void){
	char data;
	
	SCI1.SCSSR.BIT.TDRE = 0;
	data = SCI1_read_buff();
	if(data==0x15){	//�Ȃ񂩂���������
		data = '-';
	}
	SCI1.SCTDR = data;
	
	if(sci1_tx_writep == sci1_tx_readp){	//�o�b�t�@�ɒǂ�����
			SCI1.SCSCR.BIT.TIE = 0;			//���荞��off
	}
}

/*********************
SCI1 buffer��ǂ�
�����F�Ȃ�
�Ԓl�F���� �o�b�t�@���Ȃ��Ƃ���0x15
**********************/
char SCI1_read_buff(void){
	char data;
	
	if(sci1_tx_writep != sci1_tx_readp){	//�o�b�t�@������
		data = sci1_tx_buffer[sci1_tx_readp];
		sci1_tx_readp = inc_buff_p(sci1_tx_readp);
	}else{	//�����S���ǂݐ؂��Ă��
		SCI1.SCSSR.BIT.TDRE = 0;			//���M�f�[�^�G���v�e�B0
		SCI1.SCSCR.BIT.TIE = 0;				//���荞��off
		return 0x15;	//NAK
	}
	
	return data;
}

/*********************
SCI1 buffer�ɏ���
�����F����
�Ԓl�F0x00(����), 0x15(�o�b�t�@�����ς�)
**********************/
char SCI1_write_buff(char moji){
	char ack;
	
	if(inc_buff_p(sci1_tx_writep) != sci1_tx_readp){
		sci1_tx_buffer[sci1_tx_writep] = moji;
		sci1_tx_writep = inc_buff_p(sci1_tx_writep);
		
		ack = 0;
	}else{		//�o�b�t�@�����ς�����
		ack = 0x15;	//NAK
	}
	
	if(SCI1.SCSCR.BIT.TIE==0){	//���荞�݃I�t������
		SCI1.SCSCR.BIT.TIE = 1;		//�I���ɂ��� �� �Ȃ��������Ȃ芄�荞�ݓ���(����I�ɂ͂��ꂵ�����ǁc)
	}
	
	return ack;
}




/*********************
SCI1 printf��
�����F������, �ϐ�

�Ή��ϊ��F %c,%s,%d,%x,%X
**********************/
void SCI1_printf(char *in_str, ...){
	va_list list;
	char dat_c;
	long dat_num;
	char *dat_s;
	
	va_start(list, in_str);
	
	while( *in_str != '\0' ){
		if( *in_str == '%' ){
			in_str++;
			switch(*in_str){
				case 'c':
					dat_c = (char)va_arg(list, int);
					SCI1_tx_char(dat_c);
					break;
				case 's':
					dat_s = va_arg(list, char*);
					SCI1_tx_str(dat_s);
					break;
				case 'd':
					dat_num = va_arg(list, long);
					SCI1_tx_d(dat_num);
					break;
				case 'x':
					dat_num = va_arg(list, long);
					SCI1_tx_x(dat_num);
					break;
				case 'X':
					dat_num = va_arg(list, long);
					SCI1_tx_X(dat_num);
					break;
				default:	// %�͕\�����Ȃ�
					SCI1_tx_char(*in_str);
			}
		}else{
			SCI1_tx_char(*in_str);
		}
		
		in_str++;
	}
	
	va_end(list);
}


/*********************
SCI1 1�������M
�����F����
�Ԓl�F�o�b�t�@�������ς���������0x15
**********************/
char SCI1_tx_char(char moji){
	char ack=1;
	
	while(ack!=0){	//�o�b�t�@���󂭂܂ŌJ��Ԃ�
		ack = SCI1_write_buff(moji);	
	}
	return ack; 
}


/*********************
SCI1 �����񑗐M
�����F������
**********************/
void SCI1_tx_str(char *in_str){
	
	while(*in_str != '\0'){			//\0�ɂ������Ǒ��v�H�܂���0
		SCI1_tx_char(*in_str);
    	in_str++;
	}
}


/*********************
SCI1 10�i�������M
�����F����,����
�Ԓl�F�Ȃ�
long�܂ł̐�
**********************/
void SCI1_tx_d(long fig){
	unsigned int i;
	char buf[16];
	
	i=0;
	do{		//�Ƃ肠�������̃P�^���疄�߂Ă���
		buf[i]=( (fig%10) | '0');
		i++;
		if(i>15)	fig=0;
		fig = fig/10;	//���̌���1�̈ʂɎ����Ă���
	}while(fig);		//����؂�����I���
	
	while(i>0){			//buf�̒��g����납��o��
		SCI1_tx_char(buf[i-1]);
		i--;
	}
	
}


/*********************
SCI1 16�i�������M(������)
�����F����,����
�Ԓl�F�Ȃ�
long�܂ł̐�
**********************/
void SCI1_tx_x(long fig){
	unsigned int i;
	char buf[16];
	char tmp;
	
	i=0;
	do{		//�Ƃ肠�������̃P�^���疄�߂Ă���
		tmp = (fig & 0xf); 	//���̃P�^�𒊏o
		if(tmp<10){			//0�`9
			buf[i]=( tmp | '0');
		}else{
			buf[i]=( (tmp-10) + 'a');
		}
		i++;
		if(i>15)	fig=0;
		fig = fig>>4;		//���̌���1�̈ʂɎ����Ă���
	}while(fig);			//����؂�����I���
	
	while(i>0){			//buf�̒��g����납��o��
		SCI1_tx_char(buf[i-1]);
		i--;
	}
	
}

/*********************
SCI1 16�i�������M(�啶��)
�����F����,����
�Ԓl�F�Ȃ�
long�܂ł̐�
**********************/
void SCI1_tx_X(long fig){
	unsigned int i;
	char buf[16];
	char tmp;
	
	i=0;
	do{		//�Ƃ肠�������̃P�^���疄�߂Ă���
		tmp = (fig & 0xf); 	//���̃P�^�𒊏o
		if(tmp<10){			//0�`9
			buf[i]=( tmp | '0');
		}else{
			buf[i]=( (tmp-10) + 'A');
		}
		i++;
		if(i>15)	fig = 0;
		fig = fig>>4;		//���̌���1�̈ʂɎ����Ă���
	}while(fig);			//����؂�����I���
	
	while(i>0){			//buf�̒��g����납��o��
		SCI1_tx_char(buf[i-1]);
		i--;
	}
}


/*********************
SCI1 1������M
�����F�Ȃ�
�Ԓl�F����
����܂ő҂̂Œ���
**********************/
char SCI1_rx_char(void){
	char data;
	
	while ((SCI1.SCSSR.BIT.RDRF) == 0);	// ��M�҂�
	SCI1.SCSSR.BIT.RDRF = 0;	// RDRF�N���A
	data = SCI1.SCRDR;
	
	return data;
}


/*********************
SCI1 1������M(�҂��Ȃ�)
�����F�Ȃ�
�Ԓl�F����
�Ăяo�����Ƃŗ��Ă邩�m�F����K�v����
**********************/
char SCI1_rx_char_nowait(void){
	char data;
	
	if(SCI1.SCSSR.BIT.RDRF){
		SCI1.SCSSR.BIT.RDRF = 0;	// RDRF�N���A
		data = SCI1.SCRDR;
	else{
		data = 0x15;
	}
	
	return data;
}


/*********************
SCI1 �����P�^������M
�����F�Ȃ�
�Ԓl�F��
enter�����܂œǂݑ����B
unsigned int�܂ł̐�
**********************/
unsigned int SCI1_rx_d(void){
	char data_tmp;
	unsigned int data_int;
			
	do{
		data_tmp = SCI1_rx_char();	//��M�҂�
		if(data_tmp != 0x0d){	//�G���^�[�L�[����Ȃ���΁A
			if((data_tmp>='0')&&(data_tmp<='9')){	//0�`9�Ȃ�
				data_int *= 10;
				data_int += (data_tmp - '0');
			}
		}
		SCI1_tx_char(data_tmp);		//�G�R�[
	}while(data_tmp != 0x0d);		//�G���^�[����Ȃ����葱����
	SCI1_tx_str("\n\r");
	
	return data_int;
}



/*********************
SCI1 �o�b�t�@�|�C���^�̃C���N�������g
�����F���̃|�C���^
�Ԓl�F���̃|�C���^
**********************/
unsigned short inc_buff_p(unsigned short p){
	if(p < SCI1_TxBuffSize-1){
		p++;
	}else{
		p = 0;
	}
	
	return p;
}