/*  ATmega168P��p�v���O����  */
/*  AVR PlayStationController */
/*  Dualshock2�Ή�            */

/*
   SwitchRecv[]�̃J�b�R�ɂ�0����3�܂œ���B
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
		�A�i���O�X�e�B�b�NL��x��0�`255�i���S127�j

	SwitchRecv[3]
		�A�i���O�X�e�B�b�NL��y��0�`255�i���S127�j
*/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* PS�R���g���[���[�{�^����` */

#define l1         SwitchRecv[1]==0x04
#define r1		   SwitchRecv[1]==0x08
#define l2		   SwitchRecv[1]==0x01
#define r2		   SwitchRecv[1]==0x02
#define l3		   SwitchRecv[0]==0x02		//L3, R3�̓A�i���O�X�e�B�b�N�̉������݃{�^��
#define r3		   SwitchRecv[0]==0x04

#define start	   SwitchRecv[0]==0x08
#define select     SwitchRecv[0]==0x01

#define analog_x   SwitchRecv[2]   // ��0 < ���S127 < �E255 
#define analog_y   SwitchRecv[3]   // ��0 < ���S127 < ��255


volatile uint16_t SwitchRecv[8]; //SwitchRecv[]���O���[�o���ϐ��Ő錾

// ==========================================================================
// PlayStation �R���g���[���[ �֐�
// ==========================================================================

#define PS_UP       4
#define PS_RIGHT    5
#define PS_DOWN     6
#define PS_LEFT     7
#define PS_L2       0
#define PS_R2       1
#define PS_L1       2
#define PS_R1       3
#define PS_TRIANGLE 4
#define PS_CIRCLE   5
#define PS_CROSS    6
#define PS_SQUARE   7


// ��L�[��������Ă��邩�Ԃ�
inline bool ps_top(void){
	return SwitchRecv[0] & _BV(PS_UP);
}

// �E�L�[��������Ă��邩�Ԃ�
inline bool ps_right(void){
	return SwitchRecv[0] & _BV(PS_RIGHT);
}

// ���L�[��������Ă��邩�Ԃ�
inline bool ps_bottom(void){
	return SwitchRecv[0] & _BV(PS_DOWN);
}

// ���L�[��������Ă��邩�Ԃ�
inline bool ps_left(void){
	return SwitchRecv[0] & _BV(PS_LEFT);
}

// L2 �L�[��������Ă��邩�Ԃ�
inline bool ps_l2(void){
	return SwitchRecv[1] & _BV(PS_L2);
}

// R2 �L�[��������Ă��邩�Ԃ�
inline bool ps_r2(void){
	return SwitchRecv[1] & _BV(PS_R2);
}

// L1 �L�[��������Ă��邩�Ԃ�
inline bool ps_l1(void){
	return SwitchRecv[1] & _BV(PS_L1);
}

// R1 �L�[��������Ă��邩�Ԃ�
inline bool ps_r1(void){
	return SwitchRecv[1] & _BV(PS_R1);
}

// ���L�[��������Ă��邩�Ԃ�
inline bool ps_triangle(void){
	return SwitchRecv[1] & _BV(PS_TRIANGLE);
}

// �~�L�[��������Ă��邩�Ԃ�
inline bool ps_cross(void){
	return SwitchRecv[1] & _BV(PS_CROSS);
}

// ���L�[��������Ă��邩�Ԃ�
inline bool ps_circle(void){
	return SwitchRecv[1] & _BV(PS_CIRCLE);
}

// ���L�[��������Ă��邩�Ԃ�
inline bool ps_square(void){
	return SwitchRecv[1] & _BV(PS_SQUARE);
}


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



/*-----------�u�U�[�֘A-----------*/
void buzzer_on(void){
	PORTB |= _BV(0);
}

void buzzer_off(void){
	PORTB &= ~_BV(0);
}

void buzzer_times(int n){
	int i;

	for(i = 0; i < n; ++i){
		buzzer_on();

		_delay_ms(100);

		buzzer_off();

		_delay_ms(80);
	}
}



/*-----------���k��C-----------*/

void token_on(){
	PORTB |= _BV(3);

	_delay_ms(300);

	PORTB &=~_BV(3);
}

void token_off(){
	PORTB |= _BV(4);

	_delay_ms(300);

	PORTB &=~_BV(4);	
}


void basket_on(){
	PORTB |= _BV(5);

	_delay_ms(600);

	PORTB &=~_BV(5);
}

void basket_off(){
	PORTD |= _BV(7);

	_delay_ms(600);

	PORTD &=~_BV(7);
}




/*------------���[�^--------------*/
/*
	motaA:�����[�^�[
	motaB:�E���[�^�[
*/

void motaA_front(){

	OCR0A = 255;  //PB3-AHI
	OCR0B = 0;    //PB4-BHI
}

void motaA_back(){	
	OCR0A = 0;  
	OCR0B = 255; 
}

void motaA_stop(){
	OCR0A = 0xff;  
	OCR0B = 0xff; 

}

void motaB_front(){
	OCR2A = 255;  //PD6-AHI
	OCR2B = 0;    //PD7-BHI
}

void motaB_back(){
	OCR2A = 0;
	OCR2B = 255; 
}

void motaB_stop(){
	OCR2A = 0xff;  
	OCR2B = 0xff; 
}

	//�㉺�@�\���[�^�[
int motaj_up(int s){
	OCR1A = s;  //PD5-
	OCR1B = 0;  //PD4
}

int motaj_down(int s){
	OCR1A = 0;  
	OCR1B = s; 
}

int motaj_stop(){
	OCR1A = 255;  
	OCR1B = 255; 
}

/*-------------�A�i���O���x�ω�------------*/
int analog_up_down(){
	if(IIR_y(analog_y * 2) == 2){

		motaj_up(150);
	}
	else if(IIR_y(analog_y * 2) == 1){
		motaj_up(200);
	}
	else if(IIR_y(analog_y * 2) == 0){
		motaj_up(250);
	}
	else if(IIR_y(analog_y * 2) == 5){
		motaj_down(150);
	}
	else if(IIR_y(analog_y * 2) == 6){
		motaj_down(200);
	}
	else if(IIR_y(analog_y * 2) == 7){
		motaj_down(250);
	}
	else {
		motaj_stop();
	}
}
/*
int analog_lr(){
	if(IIR_x(analog_x * 2) == 2){

		motaA_front(150);
	}
	else if(IIR_x(analog_x * 2) == 1){
		motaA_front(200);
	}
	else if(IIR_x(analog_x * 2) == 0){
		motaA_front(250);
	}
	else if(IIR_x(analog_x * 2) == 5){
		motaA_back(150);
	}
	else if(IIR_x(analog_x * 2) == 6){
		motaA_back(200);
	}
	else if(IIR_x(analog_x * 2) == 7){
		motaA_back(250);
	}
	else {
		motaA_stop();
	}

}
*/

/*------------�A�i���O�t�B���^�[-------------*/

int IIR_y(int n){
	static int z[4]={0};//�����̌�ɑ��������
	//int a0=0x7b; //4.12 fc = fs / 16
	int a0 = 0x24; //fc = fs /32
	int	a1=a0 * 2,a2=a0;
	//int b1=0x174,b2=0x93;//8.8 fc = fs /16
	int b1=0x1b8,b2=0xc1;//fc = fs / 32
	int add[] = {0,0,0};

	a0 = a0 << 12;
	a1 = a1 << 12;
	a2 = a2 << 12;
	
	b1 = b1 << 12;
	b2 = b2 << 12;
	
	n = n << 6;
	
	a2 = (z[1] << 8) * a2;
	a1 = (z[0] << 8) * a1;
	a0 = n << 6 * a0;
	
	b2 = (z[3] << 8) * b2;
	b1 = (z[2] << 8) * b1;
	
	z[1] = z[0];
	z[0] = n >> 2;
	z[3] = z[2];
	z[2] = add[0];
	
	add[0] = add[1] + (a0 >> 4);
	add[0] = add[0] >> 8;
	add[1] = (a1 >> 4) + b1 + add[2];
	add[2] = (a2 >> 4) - b2;
	
	return add[0];
}

int IIR_x(int n){
	static int z[4]={0};//�����̌�ɑ��������
	//int a0=0x7b; //4.12 fc = fs / 16
	int a0 = 0x24; //fc = fs /32
	int	a1=a0 * 2,a2=a0;
	//int b1=0x174,b2=0x93;//8.8 fc = fs /16
	int b1=0x1b8,b2=0xc1;//fc = fs / 32
	int add[] = {0,0,0};

	a0 = a0 << 12;
	a1 = a1 << 12;
	a2 = a2 << 12;
	
	b1 = b1 << 12;
	b2 = b2 << 12;
	
	n = n << 6;
	
	a2 = (z[1] << 8) * a2;
	a1 = (z[0] << 8) * a1;
	a0 = n << 6 * a0;
	
	b2 = (z[3] << 8) * b2;
	b1 = (z[2] << 8) * b1;
	
	z[1] = z[0];
	z[0] = n >> 2;
	z[3] = z[2];
	z[2] = add[0];
	
	add[0] = add[1] + (a0 >> 4);
	add[0] = add[0] >> 8;
	add[1] = (a1 >> 4) + b1 + add[2];
	add[2] = (a2 >> 4) - b2;
	
	return add[0];
}


/*-----------���C��-------------*/

int main(void){

	char buf[6];
	int motaA_front_flag = 0, motaA_back_flag = 0;
	int i, j;

	DDRA = 0b00000000;
	DDRB = 0b11111111;
	DDRC = 0b00000000;
	DDRD = 0b11111111;

	// OCR0A OCR0B �̐ݒ�
	TCCR0A = 0b10100011;  
	TCCR0B = 0b00000001;
	// OCR1A OCR1B �̐ݒ�
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	// OCR2A OCR2B �̐ݒ�
	TCCR2A = 0b10100011;
	TCCR2B = 0b00000001;

	buzzer_on();
	_delay_ms(500);

	usart_init(MYUBRR);   // USART�ݒ�

    sei();    //���荞�݋���(�����Ȃ���PS�R���g���[���[�̐M�����󂯂�Ȃ�)
	
	buzzer_off();

	while(1){
/*---------������~---------*/
		if(ps_r1()){
			while(1){
				buzzer_times(2);
				motaA_stop();
				motaB_stop();
				motaj_stop();
			}
		}


/*---------------�����------------------*/
		if(ps_top()){
			if(motaA_front_flag == 0){
				for(i = 0; i < 50; i++){
					motaA_front(205 + i);
					_delay_ms(10);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));
					usart_sendStr(" \r\n");

					motaA_front_flag = 1;
				}
			}
	
			else {
				motaA_front(255);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));					
					usart_sendStr(" \r\n");
			}
		}

		else if(ps_bottom()){
			if(motaA_back_flag == 0){
				for(i = 0; i < 100; i++){
					motaA_back(155 + i);
					_delay_ms(10);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));
					usart_sendStr(" \r\n");
				}
				motaA_back_flag = 1;
			}
			else {
				motaA_back(255);

				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
			}
		}
		
		else {
			if(motaA_front_flag == 1){
				for(j = 0; j < 100; j++){
					motaA_front(255 - j);
					_delay_ms(10);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));
					usart_sendStr(" \r\n");
				}
				motaA_front_flag = 0;
			}

			else {
				motaA_stop();
				
				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
			}


			if(motaA_back_flag == 1){
				for(j = 0; j < 100; j++){
					motaA_back(255 - j);
					_delay_ms(10);

				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
				}
				motaA_back_flag = 0;
			}
			else {
				motaA_stop();

				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
			}

		}

		if(ps_triangle()){
			motaB_front(255);
		}

		else if(ps_cross()){
			motaB_back(255);
		}

		else {
			motaB_stop();
		}

/*---------------�㉺�@�\----------------*/
		//�㏸
		if(ps_l1()){

			analog_up_down();

			usart_sendStr("OCR1A= ");
			usart_sendStr(intToStr(OCR1A,buf));
			usart_sendStr(" OCR1B= ");
			usart_sendStr(intToStr(OCR1B,buf));
			usart_sendStr(" OCR0A= ");
			usart_sendStr(intToStr(OCR0A,buf));
			usart_sendStr(" OCR0B= ");
			usart_sendStr(intToStr(OCR0B,buf));
			
		}
		else {

			motaj_stop();

		}





		usart_sendStr(" analog_y = ");
		usart_sendStr(intToStr(IIR_y(analog_y * 2),buf));
		usart_sendStr("  ");
		usart_sendStr("analog_x = ");
		usart_sendStr(intToStr(IIR_y(analog_x * 2),buf));
		usart_sendStr("\r\n");
		
	}
//	return 0;
}
