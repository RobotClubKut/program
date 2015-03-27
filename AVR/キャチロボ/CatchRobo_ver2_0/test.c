/* �L���`���{�p�v���O����
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

/*-------- �|�[�g��` --------*/
/* 
   �㉺���[�^ AHI : OC0B
   �㉺���[�^ BHI : OC0A
   �㉺���[�^ ALI : PORTB1
   �㉺���[�^ BLI : PORTB0

   �O�ヂ�[�^ AHI : OC2B
   �O�ヂ�[�^ BHI : OC2A
   �O�ヂ�[�^ ALI : PORTC1
   �O�ヂ�[�^ BLI : PORTC0

   �T�[�{���[�^ �E : OC1B 
   �T�[�{���[�^ �� : OC1A

   ���~�b�g�X�C�b�`�O�i���E : PORTA5
   ���~�b�g�X�C�b�`��i���E : PORTA6
   ���~�b�g�X�C�b�`�㏸���E : PORTA7
   ���~�b�g�X�C�b�`���~���E : PORTC7

   �d���� : PORTC5    
*/

/*-------- �R���g���[���{�^�����蓖�� --------*/
/*
�� : �T�[�{���[�^��]�i�����Ă���ԃA�[�����X���A�����Ɩ߂�j
�� : �d���فi�����Ă���ԉ����o���A�����Ɩ߂�j

�A�i���O�X�e�B�b�N�E : �㉺���[�^�i�O�ɓ|���Ə㏸�A���ɓ|���Ɖ��~�j
�A�i���O�X�e�B�b�N�� : �O�ヂ�[�^�i�O�ɓ|���ƑO�i�A���ɓ|���ƌ�i�j

R1,R2 : �㉺���[�^���x�ω��i�ǂ��炩�������Ă���Ԓᑬ�A���������ƍ����j
L1,L2 : �O�ヂ�[�^���x�ω��i�ǂ��炩�������Ă���Ԓᑬ�A���������ƍ����j

START : �v���O�����X�^�[�g�{�^��(�A�i���O�{�^����������Ă��Ȃ��Ɣ������Ȃ�)

SELECT : �A�i���O�X�e�B�b�N��ύX�i���̎��̃A�i���O�X�e�B�b�N�̈ʒu����ƂȂ�j

SELECT + START : �A�i���O�X�e�B�b�N��������i�v���O�����K��l����ƂȂ�j

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
#define up         (SwitchRecv[0]&0x10)==0x10
#define down       (SwitchRecv[0]&0x40)==0x40
#define right      (SwitchRecv[0]&0x20)==0x20
#define left       (SwitchRecv[0]&0x80)==0x80

#define triangle   (SwitchRecv[1]&0x10)==0x10
#define cross      (SwitchRecv[1]&0x40)==0x40
#define circle     (SwitchRecv[1]&0x20)==0x20
#define square     (SwitchRecv[1]&0x80)==0x80

#define l1     (SwitchRecv[1]&0x04)==0x04
#define r1	   (SwitchRecv[1]&0x08)==0x08
#define l2	   (SwitchRecv[1]&0x01)==0x01
#define r2	   (SwitchRecv[1]&0x02)==0x02
#define l3	   (SwitchRecv[0]&0x02)==0x02	//L3, R3�̓A�i���O�X�e�B�b�N�̉������݃{�^��
#define r3	   (SwitchRecv[0]&0x04)==0x04

#define start	   (SwitchRecv[0]&0x08)==0x08
#define select     (SwitchRecv[0]&0x01)==0x01

#define analog_r_x   SwitchRecv[2]   // ��0 < ���S127 < �E255 
#define analog_r_y   SwitchRecv[3]   // ��0 < ���S127 < ��255

#define analog_l_x   SwitchRecv[4]   // ��0 < ���S127 < �E255 
#define analog_l_y   SwitchRecv[5]   // ��0 < ���S127 < ��255

//�Z���T�|�[�g��`
#define PR0 !PINA_0		//��ԑO
#define PR1 !PINA_1
#define PR2 !PINA_2
#define PR3 !PINA_3
#define PR4 !PINA_4

//���~�b�g�X�C�b�`��`
#define RS_F PINA_5		//���~�b�g�X�C�b�`�O�i���E
#define RS_B PINA_6		//���~�b�g�X�C�b�`��i���E
#define RS_U PINA_7		//���~�b�g�X�C�b�`�㏸���E
#define RS_D PINC_7 	//���~�b�g�X�C�b�`���~���E

//�X�s�[�h��`
#define LOWSP 100
#define HIGHSP 150

volatile uint16_t SwitchRecv[8]; //SwitchRecv[]���O���[�o���ϐ��Ő錾
volatile int rail0_flag = 0;
volatile int rail1_flag = 0;


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

	void rail0_up(int);
	void rail0_down(int);
	void rail0_stop(void);
	void rail1_front(int);
	void rail1_back(int);
	void rail1_stop(void);
	void servo1a_set(int32_t);	
	void servo1b_set(int32_t);

	DDRA = 0x00;
	DDRB = 0xff;
	DDRD = 0xff;
	DDRC = 0x7f;

	int center_r_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_r_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_l_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_l_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int analog_l_up, analog_l_down, analog_l_right, analog_l_left;
	int analog_r_up, analog_r_down, analog_r_right, analog_r_left;
	int up_f = 0;
	int down_f = 0;

    usart_init(MYUBRR);   // USART�ݒ�
   	//adc_init();           // ADConverter�ݒ�

	//int ad,ad2,ad3;
   	char buf[6];

	TCCR0A = 0b10100011;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0b00000001;
	TCCR2A = 0b10100011;  // OCR2A OCR2B �̐ݒ�
	TCCR2B = 0b00000001;
	TCCR1A = 0b10100010;	//����PWM(TOP�l = ICR1)
							//��r��v��Low�ABOTTOM(TCNT = 0)��High
	TCCR1B = 0b00011010;	//8����
	ICR1 = 20000;			//TCNT = 20000��TCNT = 0
	

    sei();    //���荞�݋���(�����Ȃ���PS�R���g���[���[�̐M�����󂯂�Ȃ�)
	servo1b_set(0);
	servo1a_set(160);
	OCR0A = 0;
	OCR0B = 0;
	PORTB_0 = 0;
	PORTB_1 = 0;
	OCR2A = 0;
	OCR2B = 0;
	PORTC_0 = 0;
	PORTC_1 = 0;
	
    //ANALOG��������ĂȂ��ƃm�C�Y�����̂�ANALOG�������X�^�[�g�������܂ł͑ҋ@
	while(analog_r_x == 0 || analog_r_y == 0)usart_sendStr("PUSH ANALOG\r\n");
 	while(start == 0){
		usart_sendStr("PUSH START\r\n");
		//stop();
	}


    	while(1){
		// SELECT+START���������ŁA�A�i���O�X�e�B�b�N��X, Y�̒��S�ʒu��������
		if(SwitchRecv[0]==0x09){
			usart_sendStr("Initialize center\r\n");
			center_r_x = 118;
			center_r_y = 132;
			center_l_x = 118;
			center_l_y = 132;
		}
		// �A�i���O�X�e�B�b�N�̒��S�ʒu��ύX
		if(select){
			usart_sendStr("PUSH SELECT");
			center_r_x = analog_r_x;
			center_r_y = analog_r_y;
			center_l_x = analog_l_x;
			center_l_y = analog_l_y;
		}

		// ������艺���v���X�e�R���g���[���[���䖽��
		if(analog_l_y <= center_l_y - 60)//center_y����80�����Ă���̂ͱ�۸޽è�����45�����ŕ����邽��
		{
			analog_l_up = 0xff - (analog_l_y * 2);
			if(l1||l2)
			{
				rail1_front(analog_l_up/2);
			}
			else
			{
				rail1_front(analog_l_up);
			}
			usart_sendStr("UP ");
		}
		else if(analog_l_y >= center_l_y + 60)
		{
			analog_l_down = (analog_l_y * 2) - 0xff;
			if(l1||l2)
			{
				rail1_back(analog_l_down/2);
			}
			else
			{
				rail1_back(analog_l_down);
			}
			usart_sendStr("DOWN ");
		}
		else
		{
			rail1_stop();
			usart_sendStr("STOP ");
		}
		
		if(analog_r_y <= center_r_y - 60)//center_y����80�����Ă���̂ͱ�۸޽è�����45�����ŕ����邽��
		{
			analog_r_up = 0xff - (analog_r_y * 2);
			if(r1||r2)
			{
				rail0_up(analog_r_up/3);
			}
			else
			{
				rail0_up(analog_r_up);
			}
			usart_sendStr("UP ");
		}
		else if(analog_r_y >= center_r_y + 60)
		{
			analog_r_down = (analog_r_y * 2) - 0xff;
			if(r1||r2)
			{
				rail0_down(analog_r_down/3);
			}
			else
			{
				rail0_down(analog_r_down);
			}
			usart_sendStr("DOWN ");
		}
		else
		{
			rail0_stop();
			usart_sendStr("STOP ");
		}

		//�T�[�{����
		if((SwitchRecv[1]&0x20)==0x20)
		{
			servo1a_set(0);
			servo1b_set(160);
		}
		else
		{
			servo1a_set(160);
			servo1b_set(0);
		}

		// �d���ِ���
		if(square)
		{
			solenoid_side(1);
		}
		else
		{
			solenoid_side(0);
		}
		

		//��������
		if(up)
		{
			if(up_f == 0)
			{
				up_f = 1;
				moter_front_auto();
			}
		}
		else
		{
			up_f = 0;
		}
		if(down)
		{
			if(down_f == 0)
			{
				down_f = 1;
				moter_back_auto();
			}
		}
		else
		{
			down_f = 0;
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
	 	usart_sendStr(intToStr(analog_r_up,buf));
		usart_sendStr("  ");
 		usart_sendStr(intToStr(SwitchRecv[1],buf)); 

		usart_sendStr("\r\n"); // ���s
		
		
  	}
}



/*-----------------------------�㉺���[������֐�------------------------------*/

//�㉺���[���㏸�p
void rail0_up(int n)
{
	if(RS_U == 1)
	{
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 1;
		PORTB_1 = 1;
		return;
	}
	if(rail0_flag != 1)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR0A = 0;
			OCR0B = n;
			PORTB_0 = 1;
			PORTB_1 = 0;
			_delay_ms(1);
		}
		rail0_flag = 1;
	}
	OCR0A = 0;
	OCR0B = n;
	PORTB_0 = 1;
	PORTB_1 = 0;
}
//�㉺���[�����~�p
void rail0_down(int n)
{	
	if(RS_D == 1)
	{
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 1;
		PORTB_1 = 1;
		return;
	}
	if(rail0_flag != 2)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR0A = n;
			OCR0B = 0;
			PORTB_0 = 0;
			PORTB_1 = 1;
			_delay_ms(1);
		}
		rail0_flag = 2;
	}
	OCR0A = n;
	OCR0B = 0;
	PORTB_0 = 0;
	PORTB_1 = 1;
}
//�㉺���[����~�p
void rail0_stop()
{
	if(rail0_flag != 3)
	{
		_delay_ms(50);
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 0;
		PORTB_1 = 0;
		rail0_flag = 3;
	}
	OCR0A = 0;
	OCR0B = 0;
	PORTB_0 = 1;
	PORTB_1 = 1;
}


/*-----------------------------�O�ヌ�[������֐�------------------------------*/

//�O�ヌ�[���O�i�p
void rail1_front(int n)
{
	if(RS_F == 1)
	{
		OCR2A = 0;
		OCR2B = 0;
		PORTC_0 = 1;
		PORTC_1 = 1;
		return;
	}
/*	if(rail1_flag != 1)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR2A = n;
			OCR2B = 0;
			PORTC_0 = 0;
			PORTC_1 = 1;
			_delay_ms(1);
		}
		rail1_flag = 1;
	}
	*/
	OCR2A = n;
	OCR2B = 0;
	PORTC_0 = 0;
	PORTC_1 = 1;
}
//�O�ヌ�[����i�p
void rail1_back(int n)
{
	if(RS_B == 1)
	{
		OCR2A = 0;
		OCR2B = 0;
		PORTC_0 = 1;
		PORTC_1 = 1;
		return;
	}
	/*
	if(rail1_flag != 2)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR2A = 0;
			OCR2B = n;
			PORTC_0 = 1;
			PORTC_1 = 0;
			_delay_ms(1);
		}
		rail1_flag = 2;
	}
	*/
	OCR2A = 0;
	OCR2B = n;
	PORTC_0 = 1;
	PORTC_1 = 0;
}
//�O�ヌ�[����~�p
void rail1_stop()
{
	/*
	if(rail1_flag != 3)
	{
		_delay_ms(50);
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 0;
		PORTB_1 = 0;
		rail1_flag = 3;
	}
	*/
	OCR2A = 0;
	OCR2B = 0;
	PORTC_0 = 1;
	PORTC_1 = 1;
}


void servo1b_set(int32_t angle_deg)
{
	OCR1B = 25*angle_deg/3+1000;
}
void servo1a_set(int32_t angle_deg)
{
	OCR1A = 25*angle_deg/3+1000;
}



/*-----------------------------�O�ヂ�[�^��������֐�------------------------------*/

//���[�^1�X�e�b�v�O�i
void moter_front_auto()
{
	if(RS_F == 1)							//���[�����L�т����Ă�������s���Ȃ�
		return;
	while((PR4 == 1)&&(RS_F == 0))			//���[�����Z���T�͈͂����ł����̃Z���T�܂ňړ�
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:10000\r\n"); 
	}
	while((PR3 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:01000\r\n"); 
	}
	while((PR2 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:00100\r\n"); 
	}
	while((PR1 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:00010\r\n"); 
	}
	while((PR0 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:00001\r\n"); 
	}

	//�`���^�����O�h�~
	_delay_ms(10);

	// �Z���T���������Ȃ��ꍇ�͍����Ԃ��ړ���������ō����ňړ�
	while((PR0 == 0)&&(PR1 == 0)&&(PR2 == 0)&&(PR3 == 0)&&(PR4 == 0)&&(RS_F == 0))
	{
		rail1_front(HIGHSP);
		usart_sendStr("zensin:00000\r\n"); 
	}
	rail1_stop();
	_delay_ms(10);
	// ���������~���邽�߂ɃX�s�[�h�𗎂Ƃ�
	while((PR4 == 1)&&(PR3 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while((PR4 == 1)&&(PR3 == 1)&&(PR2 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while((PR4 == 1)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while(RS_F == 0)
	{
		rail1_stop();
		_delay_ms(100);
		if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_stop();
			usart_sendStr("zensin:01110\r\n");
			return;
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:10000\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:01100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11000\r\n");
		}

		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00111\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00110\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00001\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00011\r\n");
		}
		else
		{
			rail1_stop();
			usart_sendStr("zensin:else\r\n");
			return;
		}
	}
}
//���[�^1�X�e�b�v��i
void moter_back_auto()
{
	if(RS_B == 1)							//���[�����k�݂����Ă�������s���Ȃ�
		return;
	while((PR0 == 1)&&(RS_B == 0))			//���[�����Z���T�͈͂��O�ł����̃Z���T�܂ňړ�
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:10000\r\n");
	}
	while((PR1 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:01000\r\n");
	}
	while((PR2 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:00100\r\n");
	}
	while((PR3 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:00010\r\n");
	}
	while((PR4 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:00001\r\n");
	}

	//�`���^�����O�h�~
	_delay_ms(10);
	// �Z���T���������Ȃ��ꍇ�͍����Ԃ��ړ���������ō����ňړ�
	while((PR0 == 0)&&(PR1 == 0)&&(PR2 == 0)&&(PR3 == 0)&&(PR4 == 0)&&(RS_B == 0))
	{
		rail1_back(HIGHSP);
		usart_sendStr("kousin:00000\r\n");
	}
	rail1_stop();
	_delay_ms(10);
	// ���������~���邽�߂ɃX�s�[�h�𗎂Ƃ�
	while((PR0 == 1)&&(PR1 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while((PR0 == 1)&&(PR1 == 1)&&(PR2 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while((PR0 == 1)&&(PR1 == 1)&&(PR2 == 1)&&(PR3 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while((PR0 == 0)&&(PR1 == 1)&&(PR2 == 1)&&(PR3 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while(RS_B == 0)
	{
		rail1_stop();
		_delay_ms(100);
		if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_stop();
			usart_sendStr("zensin:01110\r\n");
			return;
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:10000\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:01100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11000\r\n");
		}

		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00111\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00110\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00001\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00011\r\n");
		}
		else
		{
			rail1_stop();
			usart_sendStr("zensin:else\r\n");
			return;
		}
	}
}

/*-----------------------------�d���ِ���------------------------------*/
// �T�C�h2�̓d����
void solenoid_side(int sl)
{
	PORTC_5 = sl;
}

// �o�b�N�̓d����
void solenoid_back()
{

}
