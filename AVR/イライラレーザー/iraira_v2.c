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

/**********���[�^�[�֐�**********/
void top(int s){
	OCR0A = s;
	OCR0B = 0x00;
}

void down(int s){
	OCR0A = 0x00;
	OCR0B = s;
}

void right(int s){
	OCR2A = s;
	OCR2B = 0x00;
}

void left(int s){
	OCR2A = 0x00;
	OCR2B = s;
}

void stop_up(){
	OCR0A = 0xff;
	OCR0B = 0xff;
}

void stop_side(){
	OCR2A = 0xff;
	OCR2B = 0xff;
}

/**********�����ʒu��**********/
int var1, var2;

void wwww(int s){

	var1 = 0;
	var2 = 0;

	while(1){
		if(!var1 && right_touch()){
			var1 = 1;
			stop_side();
		}
		else{
			if(var1 == 1){
				stop_side();
			}
			else {
				left(s);
				var1 = 0;
			}
		}

		if(!var2 && down_touch()){
			var2 = 1;
			stop_up();
		}
		else{
			if(var2 == 1){
				stop_up();
			}
			else {
				down(s);
				var2 = 0;
			}
		}

		if(var1 == 1 && var2 == 1){
			break;
		}
	}
}

/**********PORT�z�u**********/
// 644P�̂Ƃ�

// PB0: �^�b�`�Z���T�[(��)
// PB1: �^�b�`�Z���T�[(��)
// PB2: �^�b�`�Z���T�[(�E)
// PB3: ���[�^�[(��)
// PB4: ���[�^�[(��)
// PB5: �^�b�`�Z���T�[(��)

// PC1: 
// PC2: 
// PC3:
// PC4:
// PC5:

// PD2: �u�U�[
// PD3: ���[�^�[(��)
// PD4: �p�g�����v
// PD5: ���[�U�[
// PD6: ���[�^�[(��)
// PD7: ���[�^�[(�E)



/**********���C���֐�**********/
int main(){

	DDRA = 0b00000000;
	DDRB = 0b00011000;
	DDRD = 0b11111111;
	DDRC = 0b00000000;

    usart_init(MYUBRR);   // USART�ݒ�
   	//adc_init();           // ADConverter�ݒ�

	//int ad,ad2,ad3;
//    char buf[6];
	
	int s = 255;// ���[�^�[���l
	int sig_up = 0, sig_side = 0; 
	int center_r_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_r_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_l_x = 118;   //127 //125 //118 //131 //184    //�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int center_l_y = 132;   //127 //127 //122 //132 //138�@�@//�R���g���[���[�ɂ���č����ł�̂Ŕ������K�v
	int analog_l_up, analog_l_down, analog_l_right, analog_l_left;
	int analog_r_up, analog_r_down, analog_r_right, analog_r_left;

	TCCR0A = 0b10100011;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0b00000001;
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


	while(1){

/*----�����ʒu��----*/
		if(select){
			wwww(s);
		}

/*----���[�U�[----*/
		if(ps_circle() && sig_up == 0 && sig_side == 0){
			PORTD |= _BV(5);


	/*----�����蔻��----*/
			if(PINC &_BV(1)){

				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);

			}
			else if(PINC &_BV(2)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);


			}
			else if(PINC &_BV(3)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);


			}
			else if(PINC &_BV(4)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);


			}
			else if(PINC &_BV(5)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);

			}
			else if(!(PINC & 0xd3)){

				_delay_ms(500);

			}
		}
		else {
			PORTD &= ~_BV(5);
			_delay_ms(50);			
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
*/
		// ������艺���v���X�e�R���g���[���[���䖽��
		if(analog_l_y <= center_l_y - 60)//center_y����80�����Ă���̂ͱ�۸޽è�����45�����ŕ����邽��
		{
			sig_up  = 1;

			analog_l_up = 0xff - (analog_l_y * 2);

			top(analog_l_up);
			usart_sendStr("UP ");
		}
		else if(analog_l_y >= center_l_y + 60)
		{
			sig_up = 1;

			analog_l_down = (analog_l_y * 2) - 0xff;

			down(analog_l_down);
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

			analog_l_left = 0xff - (analog_l_x * 2);

			left(analog_l_left);

			usart_sendStr("UP ");
		}
		else if(analog_l_x >= center_l_x + 60)
		{
			sig_side = 1;

			analog_l_right = (analog_l_x * 2) - 0xff;

			right(analog_l_right);

			usart_sendStr("DOWN ");
		}
		else
		{
			sig_side = 0;

			stop_side();
			usart_sendStr("STOP ");
		}





/*		if(ps_top()){
			top(s);
		}
		else if(ps_bottom()){
			down(s);
		}
		else {
			stop_up();
		}

		if(ps_right()){
			right(s);
		} 
		else if(ps_left()){
			left(s);
		}
		else {
			stop_side();
		}
*/

/*----�^�b�`�Z���T�[�łƂ܂�----*/
		if(up_touch()){
			stop_up();
			_delay_ms(200);
			down(s);
			while(up_touch());
			_delay_ms(100);
		}

		if(down_touch()){
			stop_up();
			_delay_ms(200);
			top(200);
			while(down_touch());
			_delay_ms(100);
		}

		if(left_touch()){
			stop_side();
			_delay_ms(200);
			left(s);
			while(left_touch());
			_delay_ms(100);
		}

		if(right_touch()){
			stop_side();
			_delay_ms(200);
			right(s);
			while(right_touch());
			_delay_ms(100);
		}



	}
}
