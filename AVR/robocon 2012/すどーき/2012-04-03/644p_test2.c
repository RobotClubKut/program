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

/* UART�ŕ����񑗐M */
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

void buzzer_on(void){
	PORTD |= _BV(5);
}

void buzzer_off(void){
	PORTD &= ~_BV(5);
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

/*-------���[�^---------*/
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
	OCR2A = s;  
	OCR2B = 0; 
}

int motaj_down(int s){
	OCR2A = 0;  
	OCR2B = s; 
}

int motaj_stop(){
	OCR2A = 255;  
	OCR2B = 255; 
}


/*-----------���C��-------------*/

int main(void){

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
/*---------------�����------------------*/
		
		if(ps_top()){
			motaA_front(255);
		}

		else if(ps_bottom()){
			motaA_back(255);
		}
		
		else {
			motaA_stop();
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
	if(ps_l1){
		if(0 < analog_y < 100){
			motaj_up(150);
		}
		else if(140 < analog_y < 255){
			motaj_down(150);
		}
		else {
			motaj_stop();
		}
	}













	}
//	return 0;
}
