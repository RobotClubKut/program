/*  ATmega644P��p�v���O����  */
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdlib.h>
#include <stdbool.h>


/* PS�R���g���[���[�{�^����` */

#define l1         SwitchRecv[1]==0x04
#define r1		   SwitchRecv[1]==0x08
#define l2		   SwitchRecv[1]==0x01
#define r2		   SwitchRecv[1]==0x02
#define l3		   SwitchRecv[0]==0x02		//L3, R3�̓A�i���O�X�e�B�b�N�̉������݃{�^��
#define r3		   SwitchRecv[0]==0x04

#define start	   SwitchRecv[0]==0x08
#define select     SwitchRecv[0]==0x01

#define analog_r_x   SwitchRecv[2]   // ��0 < ���S127 < �E255 
#define analog_r_y   SwitchRecv[3]   // ��0 < ���S127 < ��255
#define analog_l_x   SwitchRecv[4]   // ��0 < ���S127 < �E255 
#define analog_l_y   SwitchRecv[5]   // ��0 < ���S127 < ��255


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


/**********�^�b�`�Z���T�[�֘A**********/
bool up_touch(void){
	return PINB & _BV(0);
}

bool down_touch(void){
	return PINB & _BV(1);
}

bool right_touch(void){
	return PINB & _BV(2);
}

bool left_touch(void){
	return PINB & _BV(5);
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

int A0_number;

int A0_number, B0_number;
int A1_number, B1_number;
int A2_number, B2_number;
   	char buf[6];

















/*----------------------����胂�[�^�[�֐�---------------------------*/
//0A,0B: �E���[�^�[
//2A,2B: �����[�^�[

void strat0(int s, int st){
	int i, a = 0;
	A0_number = s;
	B0_number = 0;
	A2_number = s;
	B2_number = 0;

	for(i = 0; i < st; i++){
/*
		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // ���s




*/

		A0_number = A0_number + 1;
		A2_number = A2_number + 1;
//		a = a + 1;		
/*
		if(a > 10){

			A2_number = A2_number + 1;

		}
*/
		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_top()){
			break;
		}
	}
}

void strat1(int s){

/*

		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // ���s
*/
		A0_number = s - 5;
		B0_number = 0;
		A2_number = s;
		B2_number = 0;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);


}

void strat_stop(){
	int i;

	A0_number = 255;
	B0_number = 0;
	A2_number = 255;
	B2_number = 0;

	for(i = 0; i < 128; i++){


/*

		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // ���s





*/





		B0_number = B0_number + 2;
		B2_number = B2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}




void back0(int s, int bt){
	int i, a = 0;

	A0_number = 0;
	B0_number = s;
	A2_number = 0;
	B2_number = s;

	for(i = 0; i < bt; i++){

		B0_number = B0_number + 1;
		B2_number = B2_number + 1;

//		a = a + 1;		
/*
		if(a > 10){

		B2_number = B2_number + 1;


		}
*/

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_bottom()){
			break;
		}
	}
}

void back1(int s){

		A0_number = 0;
		B0_number = s;
		A2_number = 0;
		B2_number = s - 5;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);

}

void back_stop(){
	int i;

	A0_number = 0;
	B0_number = 255;
	A2_number = 0;
	B2_number = 255;

	for(i = 0; i < 128; i++){

		A0_number = A0_number + 2;
		A2_number = A2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}








void left0(int s, int t){
	int i;

	A0_number = s;
	B0_number = 0;
	A2_number = 0;
	B2_number = s;

	for(i = 0; i < t; i++){

		A0_number = A0_number + 1;
		B2_number = B2_number + 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_left()){
			break;
		}
	}
}

void left1(int s){

		A0_number = s;
		B0_number = 0;
		A2_number = 0;
		B2_number = s;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);

}

void left_stop(){
	int i;

	A0_number = 255;
	B0_number = 0;
	A2_number = 0;
	B2_number = 255;

	for(i = 0; i < 128; i++){

		B0_number = B0_number + 2;
		A2_number = A2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}











void right0(int s, int t){
	int i;

	A0_number = 0;
	B0_number = s;
	A2_number = s;
	B2_number = 0;

	for(i = 0; i < t; i++){

		B0_number = B0_number + 1;
		A2_number = A2_number + 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_right()){
			break;
		}
	}
}

void right1(int s){

		A0_number = 0;
		B0_number = s;
		A2_number = s;
		B2_number = 0;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);

}

void right_stop(){
	int i;

	A0_number = 0;
	B0_number = 255;
	A2_number = 255;
	B2_number = 0;

	for(i = 0; i < 128; i++){

		A0_number = A0_number + 2;
		B2_number = B2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}





void stop(){

	A0_number = 255;
	B0_number = 255;
	A2_number = 255;
	B2_number = 255;

	OCR0A = A0_number;
	OCR0B = B0_number;
	PORTB &=  ~_BV(1);
	PORTB &=  ~_BV(2);


	OCR2A = A2_number;
	OCR2B = B2_number;
	PORTD &=  ~_BV(1);
	PORTD &=  ~_BV(2);
}






/*--------------�A�[�����[�^�֐�---------------*/


void arm_one_strat0(int s, int t){
	int i;

	A1_number = 0;
	B1_number = s;

	for(i = 0; i < t; i++){

		B1_number = B1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB |= _BV(6);
		PORTB |= _BV(7);

		_delay_ms(2);
	}
}

void arm_one_strat1(int s){

	A1_number = 0;
	B1_number = s;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTB |= _BV(6);
	PORTB |= _BV(7);
}

void arm_one_strat_stop(){
	int i;

	A1_number = 0;
	B1_number = 255;

	for(i = 0; i < 128; i++){

		A1_number = A1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB &=  ~_BV(6);
		PORTB &=  ~_BV(7);

		_delay_ms(1);

	}
}





void arm_one_back0(int s, int t){
	int i;

	A1_number = s;
	B1_number = 0;

	for(i = 0; i < t; i++){

		A1_number = A1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB |= _BV(6);
		PORTB |= _BV(7);

		_delay_ms(2);
	}
}

void arm_one_back1(int s){

	A1_number = s;
	B1_number = 0;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTB |= _BV(6);
	PORTB |= _BV(7);

}

void arm_one_back_stop(){
	int i;

	A1_number = 255;
	B1_number = 0;

	for(i = 0; i < 128; i++){

		B1_number = B1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB &=  ~_BV(6);
		PORTB &=  ~_BV(7);

		_delay_ms(1);

	}
}









void arm_twe_strat1(){

		PORTC &=  ~_BV(0);
		PORTC |=  _BV(1);

		PORTC |=  _BV(2);
		PORTC &= ~_BV(3);

}



void arm_twe_back1(){

		PORTC |=  _BV(0);
		PORTC &=  ~_BV(1);

		PORTC &= ~_BV(2);
		PORTC |=  _BV(3);


}



void stop2(){

	A1_number = 255;
	B1_number = 255;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTB &=  ~_BV(6);
	PORTB &=  ~_BV(7);


	PORTC |=  _BV(0);
	PORTC |=  _BV(1);
	PORTC &=  ~_BV(2);
	PORTC &=  ~_BV(3);

}


/*
void strat0_srow2(int t){

	int i;

	A0_number = 100;
	B0_number = 100;
	A2_number = 100;
	B2_number = 100;

	for(i = 0; i < t; i++){


			usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 


		B0_number = B0_number - 1;
		B2_number = B2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);

	}
}
*/



void strat0_srow(int t){

	int i;

//	A0_number = s;
	B0_number = 0;
//	A2_number = s;
	B2_number = 0;

	for(i = 0; i < t; i++){
/*
		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // ���s


*/





		A0_number = A0_number - 1;
		A2_number = A2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);

	}
}

void back0_srow(int t){

	int i;

	A0_number = 0;
//	B0_number = 0;
	A2_number = 0;
//	B2_number = 0;

	for(i = 0; i < t; i++){

		B0_number = B0_number - 1;
		B2_number = B2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);
	}
}

void left0_srow(int t){

	int i;

//	A0_number = 0;
	B0_number = 0;
	A2_number = 0;
//	B2_number = 0;

	for(i = 0; i < t; i++){

		A0_number = A0_number - 1;
		B2_number = B2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);
	}
}

void right0_srow(int t){

	int i;

	A0_number = 0;
//	B0_number = 0;
//	A2_number = 0;
	B2_number = 0;

	for(i = 0; i < t; i++){

		B0_number = B0_number - 1;
		A2_number = A2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);
	}
}

int flag_stop1 = 0;
int flag_stop2 = 0;

/*---------------------�X���[�����-----------------*/
void slow_move(){
			
		while(ps_l1()){

			leaf();

			if(ps_top()){
/*
					usart_sendStr("  ");
					usart_sendStr("��L�["); 
					usart_sendStr("\r\n"); // ���s
*/
				if(flag_stop1 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}
					flag_stop1 = 0;
				if(A0_number > 110){

					strat0_srow(A0_number - 100);
				}else{
					strat0(0, 100); //(PWM�����l, �J�E���^�[)
				}

				while(1){
					strat1(100); //(PWM)

					if(!ps_top()){
						strat_stop();
						break;
					}

					if(!ps_l1()){
						strat0(100,155);
						break;
					}
				}
			}else if(ps_bottom()){
				if(flag_stop1 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}
				
				flag_stop1 = 0;

				if(B0_number > 110){
					back0_srow(B0_number - 100);
				}else{
					back0(0, 100); //(PWM�����l, �J�E���^�[)
				}

				while(1){
					back1(100); //(PWM)

					if(!ps_bottom()){
						back_stop();
						break;
					}

					if(!ps_l1()){
						back0(100,155);
						break;
					}
				}

			}else {
				flag_stop1 = 1;
				stop();
			}



			if(ps_left()){

				if(flag_stop2 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}

				flag_stop2 = 0;

				if(A0_number > 110){
					left0_srow(A0_number - 100);
				}else{
					left0(0, 100); //(PWM�����l, �J�E���^�[)
				}

				while(1){
					left1(100);

					if(!ps_left()){
						left_stop();
						break;
					}

					if(!ps_l1()){
						left0(100,155);
						break;
					}
				}
			}else if(ps_right()){

				if(flag_stop2 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}

				flag_stop2 = 0;

				if(B0_number > 110){
					right0_srow(B0_number - 100);
				}else{
					right0(0, 100); //(PWM�����l, �J�E���^�[)
				}

				while(1){
					right1(100);

					if(!ps_right()){
						right_stop();
						break;
					}

					if(!ps_l1()){
						right0(100,155);
						break;
					}
				}

			}else {
				flag_stop2 = 1;
				stop();

			}









			if(ps_triangle()){
//				arm_twe_strat1();
				arm_one_strat0(0, 255); //(PWM�����l, �J�E���^�[)


				while(1){
					arm_one_strat1(255); //(PWM)
//					arm_twe_strat1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();
					}

					if(!ps_triangle()){
						arm_one_strat_stop();
						break;
					}
				}
			}else if(ps_cross()){
				arm_one_back0(0, 255);
//				arm_twe_back1();	
				while(1){
					arm_one_back1(255);
//					arm_twe_back1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();


					}



					if(!ps_cross()){
						arm_one_back_stop();
						break;
					}
				}

			}else {
//				stop2();

			}


			if(ps_triangle()){
					arm_one_strat1(255); //(PWM)


			}else if(ps_cross()){
					arm_one_back1(255);



			}

			
			if(ps_r2()){

				arm_twe_back1();
			}else if(ps_r1()){

				arm_twe_strat1();


			}else {
				stop2();
			}



		}
}

void leaf_on(){
	PORTC |= _BV(7);

	_delay_ms(600);

	PORTC &=~_BV(7);
}

void leaf_off(){
	PORTC |= _BV(6);

	_delay_ms(600);

	PORTC &=~_BV(6);
}

	bool token = false; // �g�[�N�����Ƃ��Ă��邩
//	bool basket = false; // �Ă��Ƃ��Ă��邩

void leaf(){
		if(ps_circle()){
			
			// �g�[�N����͂�ł���ꍇ
			if(token){
				leaf_off();
				token = false;
			}
			
			// �g�[�N����͂�ł��Ȃ��ꍇ
			else {
				leaf_on();
				token = true;
			}

			while(ps_circle());
		}

}

/**********PORT�z�u**********/
// 644P�̂Ƃ�

// PA0 
// PA1 
// PA2 
// PA3 
// PA4 

// PB0: 
// PB1: BHS (�E���[�^�[)
// PB2: AHS (�E���[�^�[)
// PB3: ALS (�E���[�^�[)
// PB4: BLS (�E���[�^�[)
// PB5:
// PB6: AHS (���S���[�^�[)
// PB7: BHS (���S���[�^�[)

// PC0: ALS (���C���[���[�^�[)
// PC1: BLS (���C���[���[�^�[)
// PC2: AHS (���C���[���[�^�[)
// PC3: BHS (���C���[���[�^�[)
// PC4:
// PC5:
// PC6:
// PC7:

// PD0: �R���g���[���[��M
// PD1:
// PD2: AHS (�����[�^�[)
// PD3: BHS (�����[�^�[)
// PD4: BLS (���S���[�^�[)
// PD5: ALS (���S���[�^�[)
// PD6: BLS (�����[�^�[)
// PD7: ALS (�����[�^�[)


/**********���C���֐�**********/
int main(){

	token = false; // �g�[�N�����Ƃ��Ă��邩


	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRD = 0b11111111;
	DDRC = 0b11111111;

    usart_init(MYUBRR);   // USART�ݒ�
   	//adc_init();           // ADConverter�ݒ�

	//int ad,ad2,ad3;
//    char buf[6];
/*	
	int s = 255;// ���[�^�[���l
	int sig_up = 0, sig_side = 0; 
	int center_r_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_r_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_l_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_l_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int analog_l_up, analog_l_down, analog_l_right, analog_l_left;
	int analog_r_up, analog_r_down, analog_r_right, analog_r_left;
*/
	TCCR0A = 0b10100011;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0b00000001;	
	TCCR1A = 0b10100001;  // OCR1A OCR1B �̐ݒ�
	TCCR1B = 0b00000011;
	TCCR2A = 0b10100011;  // OCR2A OCR2B �̐ݒ�
	TCCR2B = 0b00000001;

   	sei();    //���荞�݋���(�����Ȃ���PS�R���g���[���[�̐M�����󂯂�Ȃ�)

    //ANALOG��������ĂȂ��ƃm�C�Y�����̂�ANALOG�������X�^�[�g�������܂ł͑ҋ@.
	while(analog_r_x == 0 || analog_r_y == 0)usart_sendStr("PUSH ANALOG\r\n");
 	while(start == 0){
		usart_sendStr("PUSH START\r\n");

	}
/*
	//����m�F�̂��߃u�U�[�g������(�E�́E)���!!�H
	PORTB = _BV(0);   
	_delay_ms(1000);
	PORTB ^= _BV(0);
*/
//		wwww(s);

	int sum;
	int flag_sro = 0;

	while(1){

		leaf(); //�A�[���J��


/*-------------------�A�[������-------------------*/

			if(ps_cross()){
//				arm_twe_strat1();
				arm_one_strat0(0, 255); //(PWM�����l, �J�E���^�[)


				while(1){
					arm_one_strat1(255); //(PWM)
//					arm_twe_strat1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();
					}

					if(!ps_cross()){
						arm_one_strat_stop();
						break;
					}
				}
			}else if(ps_triangle()){
				arm_one_back0(0, 255);
//				arm_twe_back1();	
				while(1){
					arm_one_back1(255);
//					arm_twe_back1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();


					}



					if(!ps_triangle()){
						arm_one_back_stop();
						break;
					}
				}

			}else {
//				stop2();

			}

/*
			if(ps_triangle()){
					arm_one_strat1(255); //(PWM)


			}else if(ps_cross()){
					arm_one_back1(255);



			}
*/
			
			if(ps_r2()){

				arm_twe_back1();
			}else if(ps_r1()){

				arm_twe_strat1();


			}else {
				stop2();
			}
			
			
			
			


		if(!(SwitchRecv[0] == 0xff)){
			flag_stop1 = 1;
			flag_stop2 = 1;
			stop();
		}



		flag_sro = 0;

		if(ps_l1()){

			slow_move();// �X���[

			flag_sro = 1;
		}

/*-------------------MAX�����------------------*/

		if(ps_top()){
/*			usart_sendStr("  ");
			usart_sendStr("��L�["); 
			usart_sendStr("\r\n"); // ���s
*/
			flag_stop1 = 0;		

			if(flag_sro == 0){
				strat0(0,255); //(PWM�����l, �J�E���^�[)
			}

			while(1){
				strat1(255); //(PWM���l)

				if(!ps_top()){
					strat_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}
			
			}
			
		}else if(ps_bottom()){	
			flag_stop1 = 0;	
					
			if(flag_sro == 0){
				back0(0,255); //(PWM�����l, �J�E���^�[)
			}

			while(1){
				back1(255);

				if(!ps_bottom()){
					back_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

			}
		
		}else {
			flag_stop1 = 1;
			stop();
		}



		if(ps_left()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				left0(0, 255);
			}
			while(1){
				left1(255);

				if(!ps_left()){
					left_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}
			}

		}else if(ps_right()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				right0(0, 255);
			}
			while(1){
				right1(255);

				if(!ps_right()){
					right_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

			}

		}else {
			flag_stop2 = 1;
			stop();
		}



/*----�ړ�----*/


		// SELECT+START���������ŁA�A�i���O�X�e�B�b�N��X, Y�̒��S�ʒu��������
/*		if(SwitchRecv[0]==0x09){
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
			sig_up  = 1;

//			analog_l_up = 0xff - (analog_l_y * 2);

			top(s);
			usart_sendStr("UP ");
		}
		else if(analog_l_y >= center_l_y + 60)
		{
			sig_up = 1;

//			analog_l_down = (analog_l_y * 2) - 0xff;

			down(s);
			usart_sendStr("DOWN ");
		}
		else
		{
			sig_up = 0;

			stop_up();
			usart_sendStr("STOP ");
		}
		
		if(analog_l_x <= center_l_x - 60)//center_y����80�����Ă���̂ͱ�۸޽è�����45�����ŕ����邽��
		{
			sig_side = 1;

//			analog_l_left = 0xff - (analog_l_x * 2);

			left(s);

			usart_sendStr("UP ");
		}
		else if(analog_l_x >= center_l_x + 60)
		{
			sig_side = 1;

//			analog_l_right = (analog_l_x * 2) - 0xff;

			right(s);

			usart_sendStr("DOWN ");
		}
		else
		{
			sig_side = 0;

			stop_side();
			usart_sendStr("STOP ");
		}


*/






	}
}


