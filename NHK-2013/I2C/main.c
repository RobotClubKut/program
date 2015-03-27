
#include "LPC11xx.h"
#include "i2c.c"
#include "armuart.c"
////////////////////
char I2CTXB[255],I2CRXB[200];
char UARTTXB[255],UARTRXB[200];


void pwm_init(uint32_t f){
	LPC_IOCON->PIO0_8 |= 2;	//16B0_0
	LPC_IOCON->PIO0_9 |= 2;	//16B0_1
	LPC_IOCON->PIO1_9 |= 2;	//16B1_0
	LPC_IOCON->PIO1_10 |= 2;	//16B1_1

	//�s����ݒ�
//    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << ??;				// (1) 32�r�b�g�E�J�E���^/�^�C�}1�ɃN���b�N������(CT32B1='1')
    //�d�͋���
	LPC_TMR16B0->TC &= 0x00;	//�^�C�}�N���A
	LPC_TMR16B1->TC &= 0x00;	//�^�C�}�N���A

	LPC_TMR16B0->PR = (48000000/f/100)-1;//������������
	LPC_TMR16B1->PR = (48000000/f/100)-1;//������������

	LPC_TMR16B0->MCR |= 1<<10;	//�R���y�A�}�b�`3�ŃN���A
	LPC_TMR16B1->MCR |= 1<<10;	//�R���y�A�}�b�`3�ŃN���A

//	LPC_TMR16B0->EMR |=

	LPC_TMR16B0->PWMC |= 3;
	LPC_TMR16B1->PWMC |= 3;

	LPC_TMR16B0->MR0 = 0;	//�}�b�`���W�X�^
	LPC_TMR16B0->MR1 = 0;	//�}�b�`���W�X�^
	LPC_TMR16B0->MR2 = 0;	//�}�b�`���W�X�^
	LPC_TMR16B0->MR3 = 99;	//�}�b�`���W�X�^
	LPC_TMR16B1->MR0 = 0;	//�}�b�`���W�X�^
	LPC_TMR16B1->MR1 = 0;	//�}�b�`���W�X�^
	LPC_TMR16B1->MR2 = 0;	//�}�b�`���W�X�^
	LPC_TMR16B1->MR3 = 99;	//�}�b�`���W�X�^


	LPC_TMR16B0->TCR |= 0x01;	//�N���b�N����
	LPC_TMR16B1->TCR |= 0x01;	//�N���b�N����

}



int main(void) {
	char c;


	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	
	LPC_IOCON->PIO0_1=0xe0;
	LPC_IOCON->PIO0_7=0xd0;

	LPC_GPIO0->DIR|=0xffc;
	LPC_GPIO1->DIR|=0x3bf;
	
//	i2_init(400,I2CTXB,sizeof(I2CTXB),I2CRXB,sizeof(I2CRXB));
	uart_init(19200,I2CTXB,sizeof(UARTTXB),I2CRXB,sizeof(UARTRXB));
	
	uart_puts("I2C\n");
	
	
	LPC_GPIO0->DATA;
	while(1){
		if(uart_rx_buff ()){
			c=uart_getc();
			uart_putc(c);			
//		i2cm_putc(1,c);
		}
		
		if(1&(LPC_GPIO0->MASKED_ACCESS[(1<<1)]>>1)){
			LPC_GPIO0->DATA|=(1<<7);
		}else{
			LPC_GPIO0->DATA&=~(1<<7);
			uart_puts("�{�^����������܂���\n");
			while(!(1&(LPC_GPIO0->MASKED_ACCESS[(1<<1)]>>1)));
		}


	}
	
	
}
