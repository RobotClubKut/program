/*  ATmega644P��p�v���O����  */
/*  AVR PlayStationController */
/*  Dualshock2�Ή�            */

/*
   SwitchRecv[]�̃J�b�R�ɂ�0����5�܂œ���B
   SwitchRecv[]�ɂ̓v���X�e�̃{�^������������16�i����
   �A���Ă���悤�ɂȂ��Ă���B
   
   �Ⴆ�Ύg�������{�^���������Ƃ���B
   if(SwitchRecv[1] == 0x01);
   �Ƃ��邱�ƂŁ��{�^�����������Ƃ��̖��߂��������Ƃ��\�B

   ���̃{�^���͉��L�̕\���Q��

	SwitchRecv[0] ==
		0x01	SELECT		0x10	�����L�[��
		0x02	L3		0x20	�����L�[��
		0x04	R3		0x40	�����L�[��
		0x08	START		0x80	�����L�[��

	SwitchRecv[1] == 
		0x01	L2		0x10	��
		0x02	R2		0x20	��
		0x04	L1		0x40	�~
		0x08	R1		0x80	��

	SwitchRecv[2]
		�A�i���O�X�e�B�b�NR��x��0�`255�i���S127�j

	SwitchRecv[3]
		�A�i���O�X�e�B�b�NR��y��0�`255�i���S127�j

	SwitchRecv[4]
		�A�i���O�X�e�B�b�NL��x��0�`255�i���S127�j

	SwitchRecv[5]
		�A�i���O�X�e�B�b�NL��y��0�`255�i���S127�j
*/


#define  F_CPU 8000000       //�N���b�N��8MHz�ɐݒ�@�����ݒ肵�ĂȂ���_delay_ms()���g���Ȃ�

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "yama_io.h"

#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTE�̎w��BIT��1���Z�b�g
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTE�̎w��BIT���N���A


/* PS�R���g���[���[�{�^����` */
#define up         SwitchRecv[0]==0x10
#define down       SwitchRecv[0]==0x40
#define right      SwitchRecv[0]==0x20
#define left       SwitchRecv[0]==0x80

#define triangle   SwitchRecv[1]==0x10
#define cross      SwitchRecv[1]==0x40
#define circle     SwitchRecv[1]==0x20
#define square     SwitchRecv[1]==0x80

#define l1         SwitchRecv[1]==0x04
#define r1	   SwitchRecv[1]==0x08
#define l2	   SwitchRecv[1]==0x01
#define r2	   SwitchRecv[1]==0x02
#define l3	   SwitchRecv[0]==0x02	//L3, R3�̓A�i���O�X�e�B�b�N�̉������݃{�^��
#define r3	   SwitchRecv[0]==0x04

#define start	   SwitchRecv[0]==0x08
#define select     SwitchRecv[0]==0x01

#define analog_x   SwitchRecv[2]   // ��0 < ���S127 < �E255 
#define analog_y   SwitchRecv[3]   // ��0 < ���S127 < ��255

#define analog_l_x   SwitchRecv[4]   // ��0 < ���S127 < �E255 
#define analog_l_y   SwitchRecv[5]   // ��0 < ���S127 < ��255


volatile uint16_t SwitchRecv[8]; //SwitchRecv[]���O���[�o���ϐ��Ő錾


/** UART�ݒ� **/	  // �H��o�׎���CKDIV8(1/8MHz)�ƂȂ��Ă���̂�Fuses����CKDIV8���͂���
#define FOSC 8000000  // 8MHz����
#define BAUD 38400    // 38400bps����Ȃ���ATTiny2313����M������M�ł��Ȃ�
#define MYUBRR FOSC/16/BAUD-1 // UART������

/* USART�ݒ� */
void usart_init(unsigned int ubrr){
  UBRR0H = (unsigned char)(ubrr>>8); // �{�[���[�g���8bit
  UBRR0L = (unsigned char)ubrr; // �{�[���[�g����8bit
  UCSR0A = (0<<U2X0); // ����
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); // ����M���A��M�������荞�݋���
  UCSR0C = (0<<UMSEL00)|(3<<UCSZ00)|(1<<USBS0)|(0<<UPM00);
  // �t���[���ݒ� �񓯊��ʐM 8�r�b�g 1�X�g�b�v�r�b�g �p���e�B����
}

/* NoOperation */
void nop(int count){
	int i;
	for(i = 0; i < count; i++){
		_delay_ms(100);
	}
}

/* int�̌�����Ԃ� */
char getDigit(int n){
  char i;
  i = 0;
  while(n>0){
    n /= 10;
    i++;
  }
  return i;
}

/* int->String�ϊ� */
char *intToStr(int n, char *buf){ // �ϊ����鐔�A��Ɨ̈�
  int i, digit;

  if(n == 0){
	buf[0] = '0';
	buf[1] = '\0';

	return buf;
  }

  digit = getDigit(n); // ����
  for(i = digit-1; i >= 0; i--){ // int�͍ő�5��
    buf[i] = n%10+'0';
    n /= 10;
  }
  buf[digit] = '\0'; // �s�����s
  return buf;
}

/* USART�ŕ����񑗐M */
void usart_sendStr(char *str){
  while(*str != '\0'){
    loop_until_bit_is_set(UCSR0A,UDRE0); // ���M�f�[�^���W�X�^�󂫂܂őҋ@
    UDR0 = *str++; // 1�������M�A1�����i��
  }
}

/* AD�R���o�[�^�ݒ� */
void adc_init(void){
  ADMUX = (0<<REFS0); // �O����d��
  ADCSRA =(1<<ADEN)|(1<<ADSC)|(0<<ADPS0);
  // A/D�ϊ����A1��ڕϊ��J�n(����)�A������2
}

/* �s�����w�肵��AD�ϊ� return 0-1023 */
int adc_convert(char pin){
  int ad;
  ADMUX = pin; // AD�ϊ����̓s��
  cbi(ADCSRA,ADIF);
  sbi(ADCSRA,ADSC); // �ϊ��J�n
  loop_until_bit_is_set(ADCSRA,ADIF); // �ϊ������܂ő҂�
  ad = ADCL; // ����8bit�擾
  return ad += (ADCH<<8); // ���2bit�擾
}

/* ATTiny2313����PS�R���g���[���[�̐M������M */
ISR(USART0_RX_vect){
    static uint16_t buff;
    uint16_t data,temp;

    data = UDR0;

    if(!(data & 0x08)){
        buff = data;
        return;
    }
    if((data & 0x07)==(buff & 0x07)){
        temp  = buff & 0xF0;
        temp |= data >> 4;
        SwitchRecv[data & 0x07] = temp;
    }
}

/* ���C���v���O���� */
int main(void){
	DDRA = 0xff;
	DDRB = 0xff;
	DDRD = 0xff;
	DDRC = 0x00;

	int center_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int analog_up, analog_down, analog_right, analog_left;

    	usart_init(MYUBRR);   // USART�ݒ�
   	//adc_init();           // ADConverter�ݒ�

	//int ad,ad2,ad3;
    	char buf[6];

	TCCR0A = 0b10100011;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0b00000001;
	TCCR2A = 0b10100011;  // OCR2A OCR2B �̐ݒ�
	TCCR2B = 0b00000001;

    	sei();    //���荞�݋���(�����Ȃ���PS�R���g���[���[�̐M�����󂯂�Ȃ�)

    	//ANALOG��������ĂȂ��ƃm�C�Y�����̂�ANALOG�������X�^�[�g�������܂ł͑ҋ@
	while(analog_x == 0 || analog_y == 0)usart_sendStr("PUSH ANALOG\r\n");
 	while(start == 0){
		usart_sendStr("PUSH START\r\n");
		//stop();
	}

	//����m�F�̂��߃u�U�[�g������(�E�́E)���!!�H
	PORTA = 0x00;   
	_delay_ms(1000);
	PORTA = 0x00;


    	while(1){
		// SELECT+START���������ŁA�A�i���O�X�e�B�b�N��X, Y�̒��S�ʒu��������
		if(SwitchRecv[0]==0x09){
			usart_sendStr("Initialize center\r\n");
			center_x = 118;
			center_y = 132;
		}
		// �A�i���O�X�e�B�b�N�̒��S�ʒu��ύX
		if(select){
			usart_sendStr("PUSH SELECT");
			center_x = analog_x;
			center_y = analog_y;
		}

		// ������艺���v���X�e�R���g���[���[���䖽��
		if(analog_y <= center_y - 80){    //center_y����80�����Ă���̂ͱ�۸޽è�����45�����ŕ����邽��
			analog_up = 0xff - (analog_y * 2);
//			straight(analog_up);
			usart_sendStr("UP ");
		}
		else if(analog_y >= center_y + 80){
			analog_down = (analog_y * 2) - 0xff;
//			back(analog_down);
			usart_sendStr("DOWN ");
		}

		else if((analog_x <= center_x - 60) && analog_y){
			analog_left = 0xff - (analog_x * 2);
//			roll_left(analog_left);
			usart_sendStr("LEFT ");
		}
		else if((analog_x >= center_x + 60) && analog_y){
			analog_right = (analog_x * 2) - 0xff;
//			roll_right(analog_right);
			usart_sendStr("RIGHT ");
		}

		else{
//			stop();
			usart_sendStr("STOP ");
		}

		
		//�f�o�b�O�p
		//0���A���Ă����ꍇ�X�y�[�X���\�������
		/*
		usart_sendStr(intToStr(analog_x,buf));
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_y,buf));
		usart_sendStr(" "); 
   		usart_sendStr(intToStr(analog_up,buf));     
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_down,buf));  
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_left,buf));
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_right,buf));
		usart_sendStr(" ");   
		usart_sendStr("cx");
		usart_sendStr(intToStr(center_x,buf));
		usart_sendStr(" cy");   
		usart_sendStr(intToStr(center_y,buf)); 
		*/
	
		//�{�^���m�F�@�f�o�b�O�p

		
		usart_sendStr("  ");
		usart_sendStr("L_X:"); 
 		usart_sendStr(intToStr(SwitchRecv[4],buf)); 
		usart_sendStr("  ");
		usart_sendStr("L_Y:"); 
 		usart_sendStr(intToStr(SwitchRecv[5],buf));
		usart_sendStr("  ");
		usart_sendStr("R_X:");
  	    usart_sendStr(intToStr(SwitchRecv[2],buf));
		usart_sendStr("  "); 
		usart_sendStr("R_Y:"); 
	 	usart_sendStr(intToStr(SwitchRecv[3],buf));

		usart_sendStr("  "); 
	 	usart_sendStr(intToStr(SwitchRecv[0],buf));
		usart_sendStr("  ");
 		usart_sendStr(intToStr(SwitchRecv[1],buf)); 

		usart_sendStr("\r\n"); // ���s
		
		
  	}
}

void rail2_up(int n)
{

}

void rail2_down(int n)
{

}

void rail1_front(int n)
{

}

void rail1_back(int n)
{

}
