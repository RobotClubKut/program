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
#include <math.h>

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


#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTE�̎w��BIT��1���Z�b�g
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTE�̎w��BIT���N���A

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

/******�O���[�o���ϐ�******/

int A0_number, B0_number;
int A1_number, B1_number;
int A2_number, B2_number;
int A3_number, B3_number;

int token1 = 0, token2 = 0, token3 = 0;

char buf[6], ps;

double angle_one, angle_twe, angle_apex, angle_apex_plan;



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
//			debug_move(); //�����f�o�b�O


//		A0_number = A0_number + 1;
		A2_number = A2_number + 1;


		a++;	

		if(a > 1){
			if(a == 1){
				A0_number = 0;
			}

			A0_number = A0_number + 1;

		}else {
			if(s <= 100){
				A0_number = A0_number + 1;
			}else {
				A0_number = 0;
			}
		}

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

//			debug_move(); //�����f�o�b�O

		if(s == 100){
			A0_number = s - 4;
			B0_number = 0;
			A2_number = s;
			B2_number = 0;
		}else {
			A0_number = s - 13;
			B0_number = 0;
			A2_number = s;
			B2_number = 0;
		}


		OCR0A = s;
		OCR0B = 0;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = s;
		OCR2B = 0;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);


}

void strat_stop(){
	int i;

	A0_number = 255;
	B0_number = 0;
	A2_number = 255;
	B2_number = 0;

	for(i = 0; i < 126; i++){

//			debug_move(); //�����f�o�b�O

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
		_delay_ms(2);

	}
}




void back0(int s, int bt){
	int i, a = 0;

	A0_number = 0;
	B0_number = s;
	A2_number = 0;
	B2_number = s;

	for(i = 0; i < bt; i++){

//		B0_number = B0_number + 1;
		B2_number = B2_number + 1;

		a++;	
/*
		if(a > 10){
			if(a == 10){
				B0_number = 9;
			}

			B0_number = B0_number + 1;

		}else {
			if(s <= 100){
*/				B0_number = B0_number + 1;
//			}else {
//				B0_number = 0;
//			}
//		}


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

//	debug_move(); //�f�o�b�O

	}
}

void back1(int s){

	if(s == 100){
		A0_number = 0;
		B0_number = s - 9;
		A2_number = 0;
		B2_number = s;
	}else {
		A0_number = 0;
		B0_number = s - 3;
		A2_number = 0;
		B2_number = s;
	}



	OCR0A = A0_number;
	OCR0B = B0_number;
	PORTB |=  _BV(1);
	PORTB |=  _BV(2);

	OCR2A = A2_number;
	OCR2B = B2_number - 7;
	PORTD |=  _BV(2);
	PORTD |=  _BV(3);

//		debug_move(); //�f�o�b�O

}

void back_stop(){
	int i;

	A0_number = 0;
	B0_number = 255;
	A2_number = 0;
	B2_number = 255;

	for(i = 0; i < 126; i++){

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
		_delay_ms(2);

//	debug_move(); //�f�o�b�O


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

	for(i = 0; i < 126; i++){

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

	for(i = 0; i < 126; i++){

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
	PORTD &=  ~_BV(2);
	PORTD &=  ~_BV(3);
}






/*--------------�A�[�����[�^�֐�---------------*/

// ���S���[�^�L�т�
void arm_one_strat0(int s, int t){
	int i;

	A1_number = 0;
	B1_number = s;

	for(i = 0; i < t; i++){

		B1_number = B1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC |= _BV(0);
		PORTC |= _BV(1);

		_delay_ms(1);

		if(!ps_triangle()){
			break;
		}
	}
}

void arm_one_strat1(int s){

	A1_number = 0;
	B1_number = s;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC |= _BV(0);
	PORTC |= _BV(1);
}

void arm_one_strat_stop(){
	int i;

	A1_number = 0;
	B1_number = 255;

	for(i = 0; i < 126; i++){

		A1_number = A1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC &=  ~_BV(0);
		PORTC &=  ~_BV(1);

		_delay_ms(1);

	}
}




// ���S���[�^�k��
void arm_one_back0(int s, int t){
	int i;

	A1_number = s;
	B1_number = 0;

	for(i = 0; i < t; i++){

		A1_number = A1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC |= _BV(0);
		PORTC |= _BV(1);

		_delay_ms(1);

		if(!ps_cross()){
			break;
		}
	}
}

void arm_one_back1(int s){

	A1_number = s;
	B1_number = 0;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC |= _BV(0);
	PORTC |= _BV(1);

}

void arm_one_back_stop(){
	int i;

	A1_number = 255;
	B1_number = 0;

	for(i = 0; i < 126; i++){

		B1_number = B1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC &=  ~_BV(0);
		PORTC &=  ~_BV(1);

		_delay_ms(1);

	}
}

void arm_one_stop(){

	A1_number = 255;
	B1_number = 255;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC &=  ~_BV(0);
	PORTC &=  ~_BV(1);

}


// ���C���[���[�^�L�т�
void arm_twe_strat0(int s, int t){
	int i;

	A3_number = 0;
	B3_number = s;

	for(i = 0; i < t; i++){

		B3_number = B3_number + 1;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC |= _BV(2);
		PORTC |= _BV(3);

		_delay_ms(1);

		if(!ps_triangle()){
			break;
		}
	}
}

void arm_twe_strat1(int s){

	A3_number = 0;
	B3_number = s;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC |= _BV(2);
	PORTC |= _BV(3);
}

void arm_twe_strat_stop(){
	int i;

	A3_number = 0;
	B3_number = 255;

	for(i = 0; i < 126; i++){

		A3_number = A3_number + 2;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC &=  ~_BV(2);
		PORTC &=  ~_BV(3);

		_delay_ms(1);

	}
}

// ���C���[���[�^�k��
void arm_twe_back0(int s, int t){
	int i;

	A3_number = s;
	B3_number = 0;

	for(i = 0; i < t; i++){

		A3_number = A3_number + 1;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC |= _BV(2);
		PORTC |= _BV(3);

		_delay_ms(2);

		if(!ps_cross()){
			break;
		}
	}
}

void arm_twe_back1(int s){

	A3_number = s;
	B3_number = 0;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC |= _BV(2);
	PORTC |= _BV(3);

}

void arm_twe_back_stop(){
	int i;

	A3_number = 255;
	B3_number = 0;

	for(i = 0; i < 126; i++){

		B3_number = B3_number + 2;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC &=  ~_BV(2);
		PORTC &=  ~_BV(3);

		_delay_ms(1);

	}
}

void arm_twe_stop(){

	A3_number = 255;
	B3_number = 255;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC &=  ~_BV(2);
	PORTC &=  ~_BV(3);

}


void stop2(){

	A1_number = 255;
	B1_number = 255;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC &=  ~_BV(0);
	PORTC &=  ~_BV(1);


	A3_number = 255;
	B3_number = 255;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC &=  ~_BV(2);
	PORTC &=  ~_BV(3);

}


void strat0_srow(int t){

	int i;
//	A0_number = s;
	B0_number = 0;
//	A2_number = s;
	B2_number = 0;

	for(i = 0; i < t; i++){

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
		_delay_ms(2);

		if(!ps_top()){
			break;
		}
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
		_delay_ms(2);

		if(!ps_bottom()){
			break;
		}
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
		_delay_ms(2);

		if(!ps_left()){
			break;
		}
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
		_delay_ms(2);

		if(!ps_right()){
			break;
		}
	}
}


int flag_stop1 = 0;
int flag_stop2 = 0;

/*---------------------�X���[�����-----------------*/
void slow_move(){
			
	while(ps_l1()){

		leaf();

		if(ps_top()){
			flag_stop1 = 0;
			if(A0_number == 255 && B0_number == 255){
				strat0(50, 50);
			}else if(A0_number >= 100 && B0_number < 3){

				strat0_srow(A0_number - 100);
			}else{

				strat0(A0_number, 100 - A0_number); //(PWM�����l, �J�E���^�[)
			}

			while(1){

				strat1(100); //(PWM)

				if(!ps_top()){
					strat_stop();
					break;
				}

				if(!ps_l1()){
					strat0(100,154);
					break;
				}
			}
		}else if(ps_bottom()){
			flag_stop1 = 0;

			if(A0_number == 255 && B0_number == 255){
				back0(50, 50);
			}else if(A0_number < 3 && B0_number >= 100){
				back0_srow(B0_number - 100);
			}else{
				back0(B0_number, 100 - B0_number); //(PWM�����l, �J�E���^�[)
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
//			stop();
		}



		if(ps_left()){
			flag_stop2 = 0;

			if(A0_number == 255 && B0_number == 255){
				left0(30, 70);
			}else if(A0_number >= 100 && B0_number < 3){
				left0_srow(A0_number - 100);
			}else{
				left0(A0_number, 100 - A0_number); //(PWM�����l, �J�E���^�[)
			}

			while(1){
				left1(100);

				if(!ps_left()){
					left_stop();
					break;
				}

				if(!ps_l1()){
					break;
				}
			}
		}else if(ps_right()){
			flag_stop2 = 0;

			if(A0_number == 255 && B0_number == 255){
				right0(30, 70);
			}else if(A0_number < 3 && B0_number >= 100){
				right0_srow(B0_number - 100);
			}else{
				right0(B0_number, 100 - B0_number); //(PWM�����l, �J�E���^�[)
			}

			while(1){
				right1(100);

				if(!ps_right()){
					right_stop();
					break;
				}

				if(!ps_l1()){
					break;
				}
			}
		}else {
			flag_stop2 = 1;
			stop();
		}
	}
}

/*----------���k��C�֘A----------*/
void leaf_one_on(){
	PORTC |= _BV(7);

	_delay_ms(100);

	PORTC &=~_BV(7);
}

void leaf_one_off(){
	PORTC |= _BV(6);

	_delay_ms(100);

	PORTC &=~_BV(6);
}

void leaf_twe_on(){
	PORTA |= _BV(3);

	_delay_ms(100);

	PORTA &=~_BV(3);
}

void leaf_twe_off(){
	PORTA |= _BV(4);

	_delay_ms(100);

	PORTA &=~_BV(4);
}

void leaf_up(){
	PORTC |= _BV(5);

	_delay_ms(100);

	PORTC &=~_BV(5);
}

void leaf_down(){
	PORTC |= _BV(4);

	_delay_ms(100);

	PORTC &=~_BV(4);
}

void stone_on(){
	PORTA |= _BV(5);

	_delay_ms(100);

	PORTA &=~_BV(5);
}

void stone_off(){
	PORTA |= _BV(6);

	_delay_ms(100);

	PORTA &=~_BV(6);
}

//	bool token1 = false; // �g�[�N��1���Ƃ��Ă��邩
	int stone = 1;
	

void leaf(){

	while(ps_r1() && ps_r2()){

		//���A�[������������
		if(ps_circle()){
			if(token3 == 0){
				leaf_one_on(); //1����
				token3 = 1;
			}else if(token3 == 1){
				leaf_one_off(); //1�J����
				token3 = 0;
			}
			while(ps_circle());
		}
	}
	//�S�A�[���J���ĕ���
	if(r3){ 	
		if(token1 == 1 && token2 == 1 && token3 == 1){
			leaf_one_off(); //1�J����
			leaf_twe_off(); //2�J����

			token1 = 0;
			token2 = 0;
			token3 = 0;
		}else if(token1 == 0 && token2 == 0 && token3 == 0){
			leaf_one_on(); //1����
			leaf_twe_on(); //2����

			token1 = 1;
			token2 = 1;
			token3 = 1;	
		}
		while(r3);
	}

	//���Ί�
	if(l3){
		if(stone == 0){
			stone_off();
			stone = 1;
		}else if(stone ==1){
			stone_on();
			stone = 0;
		}
		while(l3);
	}


//�t���ϗ��Ƃ��Ƃ�
	if(ps_square()){
		//�O�����Ă��鎞
		if(token1 == 1 && token2 == 1 && token3 == 1){
			leaf_one_off(); //1�J����

			token3 = 0;
		}		
		//������Ă��鎞
		else if(token1 == 1 && token2 == 1 && token3 == 0){
			leaf_down();	//������
			_delay_ms(300);
			leaf_twe_off(); //2�J����
			leaf_up();	//�グ��
			_delay_ms(20);
			leaf_twe_on(); //2����

			token2 = 0;

		}
		//������Ă��鎞
		else if(token1 == 1 && token2 == 0 && token3 == 0){
			leaf_down();	//������
			_delay_ms(300);
			leaf_twe_off(); //2�J����
			leaf_up();	//�グ��

			token1 = 0;
		}else {
			token3 = 0; //?
		}

	while(ps_square());

	}




//�t���ςƂ�Ƃ�
	if(ps_circle()){
		//�����Ă��Ȃ��Ƃ�
		if(token1 == 0 && token2 == 0 && token3 == 0){
			leaf_one_off(); //1�J����
			leaf_twe_off(); //2�J����
			leaf_down(); //������
			_delay_ms(400);
			leaf_twe_on(); //2����
			leaf_up(); //�����グ��
			arm_one_back1(100);
			_delay_ms(450);
			arm_one_stop();
			token1 = 1;
		}
		//������Ă��鎞
		else if(token1 == 1 && token2 == 0 && token3 == 0){
			leaf_twe_off(); //2�J����
			leaf_down(); //������
			_delay_ms(400);
			leaf_twe_on(); //2����
			leaf_up(); //�����グ��
			arm_one_back1(100);
			_delay_ms(500);
			token2 = 1;
			arm_one_stop();
		}
		//������Ă��鎞
		else if(token1 == 1 && token2 == 1 && token3 == 0){
			leaf_one_on(); //1����
			token3 = 1;

		}else {
			token3 = 0; //?
		}
		while(ps_circle());
	}
}
/*----------�p�x�v�Z�֐�----------*/
void count_angle(){
//			0�x				90�x
	double one_max = 650, one_min = 287;
	double twe_max = 419, twe_min = 711;
//			90�x			0�x

	angle_one = (one_max - adc_convert(0)) * (90/(one_max - one_min)); //�A�[���@�̏�����̊p�x
	angle_twe = (twe_min - adc_convert(1)) * (90/(twe_min - twe_max)); //�A�[���A�̐�������̊p�x
	angle_apex = 90 - angle_one + angle_twe; //���ݒ��_�p�x
	angle_apex_plan = 180 - angle_one * 1.8; //���z���_�p�x
									//	���̒l��2.0����傫������΃A�[���Ⴍ, ����������΍����Ȃ�
}

void debug_angle(){

	usart_sendStr("1AD= ");
	usart_sendStr(intToStr(adc_convert(0),buf));
	usart_sendStr(", 2AD= ");
	usart_sendStr(intToStr(adc_convert(1),buf));
	usart_sendStr(", angle_one= ");
	usart_sendStr(intToStr(angle_one,buf));
	usart_sendStr(", angle_twe= ");
	usart_sendStr(intToStr(angle_twe,buf));

	usart_sendStr(", angle_apex= ");
	usart_sendStr(intToStr(angle_apex,buf));

	usart_sendStr(", kakudo= ");
	usart_sendStr(intToStr(angle_apex_plan,buf));
/*
	usart_sendStr(", seki= ");
	usart_sendStr(intToStr(adc_convert(2),buf));

	usart_sendStr(", IIR= ");
	usart_sendStr(intToStr(IIR_y(adc_convert(2)),buf));
*/	usart_sendStr("\r\n"); // ���s

}

void debug_move(){
	usart_sendStr("  ");
	usart_sendStr("0A:"); 
 	usart_sendStr(intToStr(OCR0A,buf)); 
	usart_sendStr("  ");
	usart_sendStr("0B:"); 
 	usart_sendStr(intToStr(OCR0B,buf));
	usart_sendStr("  ");
	usart_sendStr("2A:");
  	usart_sendStr(intToStr(OCR2A,buf));
	usart_sendStr("  "); 
	usart_sendStr("2B:"); 
	usart_sendStr(intToStr(OCR2B,buf));; 

	usart_sendStr("\r\n"); // ���s
}

void debug_pwm_angle(){
	usart_sendStr("  ");
	usart_sendStr("1A:"); 
 	usart_sendStr(intToStr(OCR1A,buf)); 
	usart_sendStr("  ");
	usart_sendStr("1B:"); 
 	usart_sendStr(intToStr(OCR1B,buf));
	usart_sendStr("  ");
	usart_sendStr("3A:");
  	usart_sendStr(intToStr(OCR3A,buf));
	usart_sendStr("  "); 
	usart_sendStr("3B:"); 
	usart_sendStr(intToStr(OCR3B,buf));; 

	usart_sendStr("\r\n"); // ���s
}


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



void arm_strat(){
					count_angle(); //�p�x�v�Z

					arm_one_strat1(255); //(PWM)
/*
					if(!ps_triangle()){ //�����ꂽ���~�߂�
						arm_one_strat_stop();
						arm_twe_stop();
						break;
					}
*/
					if(angle_one < 4){ //�A�[��1���L�т����Ă���̂ł��̊p�x�ŃX�g�b�v
						arm_one_stop();
						if(angle_twe < 75){ //�A�[��2���L�т����Ă��Ȃ��̂ł��̊p�x�܂ŐL�΂�
							arm_twe_strat0(70,70);

						}else if(angle_twe > 85){
							arm_twe_back0(70,70);
						}else {
							arm_twe_stop();
//							break;
						}
					}else {
						//�ŏ�����������Ȃ��悤�ɃA�[��2�������L�΂�
						if(angle_one > 70){
							if(angle_apex < 25){
								arm_one_stop();
								arm_twe_strat1(200);
								while(angle_apex < 25){
									count_angle(); //�p�x�v�Z
								}
								arm_twe_strat_stop();
							}
						}


						if(angle_apex_plan - angle_apex > 15){ //�A�[��2�̊p�x���ƂĂ��󂢎�
							if(angle_twe > 65){ //���̊p�x�ȏ�̎��̓A�[��2�X�g�b�v
								arm_twe_stop();

							}else {

								arm_twe_strat1(200);
								arm_one_strat_stop();
							}
						}else {
							if((angle_apex < angle_apex_plan) && (angle_twe < 85)){
								arm_twe_strat0(100, 150); //�p�x����������L�΂�
						//		arm_twe_strat_stop();
							}
							else if(angle_twe > angle_apex_plan){
								arm_twe_back0(80, 70); //�p�x�傫������k��
						//		arm_twe_back_stop();
							}else {
								arm_twe_stop();
							}
						}
					}
}

void arm_back(){

					count_angle(); //�p�x�v�Z

					arm_one_back1(255); //(PWM)
/*
					if(!ps_cross()){ //�����ꂽ���~�߂�
						arm_one_back_stop();
						arm_twe_stop();
						break;
					}
*/
					if(angle_one > 91){ //�t���ς��^�Ԉʒu�փA�[�����ړ�
						arm_one_stop();
						if(angle_apex < 25){
							arm_twe_strat1(200);

							while(angle_apex < 25){
								count_angle(); //�p�x�v�Z
							}
						}
						arm_twe_stop();
					}else {
						if(angle_apex < 55){ //�t���ς��^�Ԉʒu�փA�[�����ړ�
					//		arm_one_back1(150);
							arm_twe_strat1(200);

						}else {
							if(angle_apex < angle_apex_plan){
								arm_twe_strat0(50, 80); //�p�x����������L�΂�

							}
							else if(angle_apex > angle_apex_plan){
								arm_twe_back0(80, 130); //�p�x�傫������k��

							}else {
								arm_twe_stop();
							}
						}
					}

}

void r1_strat(){
						count_angle(); //�p�x�v�Z

						if(adc_convert(0) <= 580){
							_delay_ms(5);
							if(adc_convert(0) <= 580){
								arm_one_strat1(255); //(PWM)
							}
						}else {
							arm_one_strat_stop();
//							break;
						}


}

void r1_back(){

						count_angle(); //�p�x�v�Z

						if(adc_convert(0) > 192){
//							_delay_ms(5);
//							if(adc_convert(0) > 290){
								arm_one_back1(250);
//							}
						}else {
							arm_one_stop();
//							break;
						}


}

void modoru(){
	if(angle_one < 35){
		arm_one_back1(250);
	}else {
		arm_one_stop();
	}

	if(angle_twe > 30){
		arm_twe_back1(170);
	}else {
		arm_twe_stop();
	}
}


/**********PORT�z�u**********/
// 1284P�̂Ƃ�

// PA0 �A�[��1�̃|�e���V�����[�^
// PA1 �A�[��2�̃|�e���V�����[�^
// PA2 
// PA3 ���k��C(��2)
// PA4 ���k��C(��2)
// PA5 ���k��C(���Ί�)
// PA6 ���k��C(���Ί�)

// PB0: 
// PB1: BHS (�E���[�^�[)
// PB2: AHS (�E���[�^�[)
// PB3: BLS (�E���[�^�[)
// PB4: ALS (�E���[�^�[)
// PB5:
// PB6: ALS (���C���[���[�^�[)
// PB7: BLS (���C���[���[�^�[)

// PC0: AHS (���S���[�^�[)
// PC1: BHS (���S���[�^�[)
// PC2: AHS (���C���[���[�^�[)
// PC3: BHS (���C���[���[�^�[)
// PC4:	���k��C(�㉺)
// PC5:	���k��C(�㉺)
// PC6: ���k��C(��1)
// PC7: ���k��C(��1)

// PD0: �R���g���[���[��M
// PD1:
// PD2: AHS (�����[�^�[)
// PD3: BHS (�����[�^�[)
// PD4: BLS (���S���[�^�[)
// PD5: ALS (���S���[�^�[)
// PD6: ALS (�����[�^�[)
// PD7: BLS (�����[�^�[)


/**********���C���֐�**********/
int main(){

	DDRA = 0b01111000;
	DDRB = 0b11111111;
	DDRD = 0b11111111;
	DDRC = 0b11111111;

    usart_init(MYUBRR);   // USART�ݒ�
   	adc_init();           // ADConverter�ݒ�

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
	TCCR3A = 0b10100001;  // OCR3A OCR3B �̐ݒ�
	TCCR3B = 0b00000011;

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


	int flag_sro = 0, angle_twe_sample = 0;

//	token1 = false; // �g�[�N�����Ƃ��Ă��邩
	leaf_one_off(); //1�J����
	leaf_twe_off(); //2�J����
	stone_off();


	while(1){

		if(start){
			
			leaf_one_off(); //1�J����
			leaf_up();		//�グ��
			leaf_twe_off(); //2�J����

			stone_off();
			stone = 1;

			token1 = 0;
			token2 = 0;
			token3 = 0;

		}
		


		leaf(); //�A�[���J��

		count_angle(); //�p�x�v�Z

		debug_angle(); //�f�o�b�O

/*-------------------�A�[������-------------------*/
/*

		if(ps_triangle()){
			
			arm_one_strat1(255); //(PWM)
			arm_twe_strat1(255); //(PWM)


		}else if(ps_cross()){

			arm_one_back1(255); //(PWM)
			arm_twe_back1(255); //(PWM)

		}else {
			arm_one_stop();
			arm_twe_stop();

		}

*/


	//R1�������Ȃ��灢�w�������ƃA�[��1��������
		if(ps_r1()){
			if(ps_triangle()){

				if(angle_one > 2){ //�A�[��1�L�т�

					arm_one_strat0(0, 255); //(PWM�����l, �J�E���^�[)

					while(1){
						count_angle(); //�p�x�v�Z

						if(angle_one > 3){
							_delay_ms(5);
							if(angle_one > 3){
								arm_one_strat1(255); //(PWM)
							}
						}else {
							arm_one_strat_stop();
							break;
						}

						if(!ps_triangle() || !ps_r1()){ //�����ꂽ���~�߂�
							arm_one_strat_stop();
							arm_twe_stop();
							break;
						}
					}
				}else {
					arm_one_stop();//�A�[��1�~�܂�
					arm_twe_stop();
				}

			}else if(ps_cross()){
				if(angle_one < 90){//�A�[��1�k��

					arm_one_back0(0, 254);

					while(1){
						count_angle(); //�p�x�v�Z

						if(angle_one < 90){
							arm_one_back1(255);
						}else {
							arm_one_stop();
							break;
						}

						if(!ps_cross() || !ps_r1){ //�����ꂽ���~�߂�
							arm_one_back_stop();
							arm_twe_stop();
							break;
						}
					}
				}else {
					arm_one_stop(); //�A�[��1�~�܂�
					arm_twe_stop();
				}
			}else {
				arm_one_stop();
				arm_twe_stop();
			}
		}

	//R2�������Ȃ��灢�w�������ƃA�[��2��������
		else if(ps_r2()){

			if(ps_triangle()){
				if(angle_twe < 90){
					//�A�[��2�L�т�
					arm_twe_strat0(0, 255); //(PWM�����l, �J�E���^�[)

					while(1){
						count_angle(); //�p�x�v�Z

						if(angle_twe < 90){
							arm_twe_strat1(255); //(PWM)
						}else {
							arm_twe_strat_stop();
							break;
						}

						if(!ps_triangle() || !ps_r2()){ //�����ꂽ���~�߂�
							arm_twe_strat_stop();
							break;
						}
					}

				}else {
					arm_one_stop();
					arm_twe_stop();
				}

			}else if(ps_cross()){
				if(angle_twe > 6){
					//�A�[��2�k��
					arm_twe_back0(0, 255);

					while(1){
						count_angle(); //�p�x�v�Z

						if(angle_twe > 7){
							arm_twe_back1(255);
						}else {
							arm_twe_back_stop();
							break;
						}

						if(!ps_cross() || !ps_r2()){ //�����ꂽ���~�߂�
					//		arm_twe_back_stop();
							arm_twe_stop();
							break;
						}
					}

				}else {
					//�A�[��2�~�܂�
					arm_twe_stop();
					arm_one_stop();
				}

			}else {
				arm_twe_stop();
				arm_one_stop();	
			}

	//���w�����������Ɨ����̃A�[���𓯎��ɓ�����
		}else if(!ps_r1() && !ps_r2()){
			if(ps_triangle()){ //�A�[���L�΂�

				if(angle_one > 3){

					arm_one_strat0(0, 200); //(PWM�����l, �J�E���^�[)

					while(ps_triangle()){

						count_angle(); //�p�x�v�Z

						arm_one_strat1(255); //(PWM)

						if(ps_r1()){ //�A�[��1�������������Ƃ�����
//							arm_one_strat_stop();
							arm_twe_stop();
							break;
						}else if(ps_r2()){ //�A�[��2�������������Ƃ�����
							arm_one_strat_stop();
//							arm_twe_stop();
							break;
						}
	
						if(angle_one < 2){ //�A�[��1���L�т����Ă���̂ł��̊p�x�ŃX�g�b�v
							arm_one_stop();
							if(angle_twe < 72){ //�A�[��2���L�т����Ă��Ȃ��̂ł��̊p�x�܂ŏグ��
								arm_twe_strat0(70,100);

							}else if(angle_twe > 75){ //�A�[��2���L�т����Ă���̂ł��̊p�x�܂ŉ�����
								arm_twe_back0(70,100);
							}else {
								arm_twe_stop();
								break;
							}
						}else {
							//�ŏ�����������Ȃ��悤�ɃA�[��2�������L�΂�
							if(angle_one > 80){
								if(angle_apex < 13){
									arm_one_stop();
									arm_twe_strat1(200);
									while(angle_apex < 13){
										count_angle(); //�p�x�v�Z
									}
									arm_twe_strat_stop();
								}
							}



							if(angle_apex_plan - angle_apex > 20){ //�A�[��2�̊p�x���ƂĂ��󂢎�
								if(angle_twe > 80){ //���̊p�x�ȏ�̎��̓A�[��2�X�g�b�v
									arm_twe_stop();

								}else { //�A�[��1�ᑬ�A�A�[��2����
									arm_twe_strat1(200);
									arm_one_strat1(150);
								}
							}else {
								if((angle_apex < angle_apex_plan) && (angle_twe < 85)){
									arm_twe_strat0(70, 140); //�p�x����������L�΂�
							//		arm_twe_strat_stop();
								}
								else if(angle_twe > angle_apex_plan){
									arm_twe_back0(80, 70); //�p�x�傫������k��
							//		arm_twe_back_stop();
								}else {
									arm_twe_stop();
								}
							}
						}
					}
					arm_one_strat_stop();
					arm_twe_stop();

				}else {
					arm_one_stop();
					arm_twe_stop();
			
				}
			}else if(ps_cross()){ //�A�[���k�߂�
				if(angle_one < 85){

					arm_one_back0(0, 200); //(PWM�����l, �J�E���^�[)

					while(1){

						count_angle(); //�p�x�v�Z

						arm_one_back1(255); //(PWM)

						if(ps_r1()){ //�A�[��1�������������Ƃ�����
//							arm_one_strat_stop();
							arm_twe_stop();
							break;
						}else if(ps_r2()){ //�A�[��2�������������Ƃ�����
							arm_one_strat_stop();
//							arm_twe_stop();
							break;
						}


						if(!ps_cross()){ //�����ꂽ���~�߂�
							arm_one_back_stop();
							arm_twe_stop();
							break;
						}

						if(angle_one > 91){ //�t���ς��^�Ԏ��̈ʒu�փA�[�����ړ�
							arm_one_stop();
							if(angle_apex < 25){
								arm_twe_strat1(200);

								while(angle_apex < 25){
									count_angle(); //�p�x�v�Z
								}
							}
							arm_twe_stop();
						}else {
							if(angle_apex < 55){ //�t���ς��^�Ԉʒu�փA�[�����ړ�
						//		arm_one_back1(150);
								arm_twe_strat1(200);

							}else {
								if(angle_apex < angle_apex_plan){
									arm_twe_strat0(50, 80); //�p�x����������L�΂�

								}
								else if(angle_apex > angle_apex_plan){
									arm_twe_back0(60, 150); //�p�x�傫������k��

								}else {
									arm_twe_stop();
								}
							}
						}
					}
				}else {
					arm_one_stop();
					arm_twe_stop();

				}
			}else {
				arm_one_stop();
				arm_twe_stop();
				stop();

			}
		}

		//�L�т���Ԃ���t���ς����ʒu�܂ŃA�[�����k�߂�
		if(ps_l2()){
			modoru();
		}



/*-------------------MAX�����------------------*/
		flag_sro = 0;

		if(ps_l1()){
			flag_sro = 1;

			slow_move();// �X���[
		}

		if(ps_top()){
			flag_stop1 = 0;		

			if(flag_sro == 0){
				strat0(30,225); //(PWM�����l, �J�E���^�[)

			}

			while(1){
				count_angle(); //�p�x�v�Z

				strat1(255); //(PWM���l)

				if(!ps_top()){
					strat_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}
				//�A�[������(�A�[��1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//�A�[������(�O��)
				}else if(ps_l2()){
					modoru();
				}else{
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}
			}

		}else if(ps_bottom()){
			flag_stop1 = 0;

			if(flag_sro == 0){
				back0(30,225); //(PWM�����l, �J�E���^�[)
			}

			while(1){
				count_angle(); //�p�x�v�Z

				back1(255);

				if(!ps_bottom()){
					back_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

				//�A�[������(�A�[��1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//�A�[������(�O��)
				}else if(ps_l2()){
					modoru();
				}else {
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}
			}

		}else {
			flag_stop1 = 1;
		}



		if(ps_left()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				left0(30, 90);
			}
			while(1){
				count_angle(); //�p�x�v�Z

				left1(120);

				if(!ps_left()){
					left_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}


				//�A�[������(�A�[��1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//�A�[������(�O��)
				}else if(ps_l2()){
					modoru();
				}else {
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}


			}

		}else if(ps_right()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				right0(30, 90);
			}
			while(1){
				count_angle(); //�p�x�v�Z

				right1(120);

				if(!ps_right()){
					right_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

				//�A�[������(�A�[��1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//�A�[������(�O��)
				}else if(ps_l2()){
					modoru();
				}else {
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}

			}

		}else {
			flag_stop2 = 1;
			stop();
		}

	}
}


