/*���C���g���[�X�}�V������v���O����*/
//8MHz

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>


#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTE�̎w��BIT��1���Z�b�g
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTE�̎w��BIT���N���A


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

/* ���C���g���[�X�����錾 */
/* ���C���g���[�X�Z���^�[1���� */
#define f_left3  PINA&_BV(6)
#define f_left2  PINA&_BV(5)                                                                                                                                                                                                           
#define f_left1  PINA&_BV(4)
#define f_center PINA&_BV(3)
#define f_right1 PINA&_BV(2)
#define f_right2 PINA&_BV(1)
#define f_right3 PINA&_BV(0)

#define r_left3  PINC&_BV(0)
#define r_left2  PINC&_BV(1)
#define r_left1  PINC&_BV(2)
#define r_center  PINC&_BV(3)
#define r_right1  PINC&_BV(4)
#define r_right2  PINC&_BV(5)
#define r_right3  PINC&_BV(6)

/* ���C���g���[�X�T�C�h */

/*void lt_straight_Mk2(){
		if(f_center){
			PORTB = 0x00;
			_delay_ms(5);
			if(f_center) straight();
		}


		if(f_right2){
			_delay_ms(3);
			if(f_right2) turn_right(0xff - 30);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left(0xff - 30);
		}
		else if(f_right1){
			_delay_ms(1);
			if(f_right1) turn_right(0xff - 20);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left(0xff - 20);
		}
		else if(f_center){
			PORTB = 0x00;
			_delay_ms(3);
		}
		else{
			//motor_R(0xff,0xff);
			//motor_L(0xff,0xff);
		}
}*/

int img_boad1(){//���z���C���g���[�X���

	if(f_center){
		_delay_us(1000);
		if(f_center) return 0;
	}
	if(f_right2){
		_delay_us(1000);
		if(f_right2) return 2;
	}
	else if(f_left2){
		_delay_us(1000);
		if(f_left2) return -2;
	}
	else if(f_right1){
		_delay_us(1000);
		if(f_right1) return 1;
	}
	else if(f_left1){
		_delay_us(1000);
		if(f_left1) return -1;
	}
	else if(f_center){
		_delay_us(1000);
		if(f_center) return 0;
	}
	else return 0;
}
int img_boad2(){//���z���C���g���[�X���
	if(r_center){
		_delay_us(1000);
		if(r_center) return 0;
	}
	if(r_right2){
		_delay_us(1000);
		if(r_right2) return 2;
	}
	else if(r_left2){
		_delay_us(1000);
		if(r_left2) return -2;
	}
	else if(r_right1){
		_delay_us(1000);
		if(r_right1) return 1;
	}
	else if(r_left1){
		_delay_us(1000);
		if(r_left1) return -1;
	}
	else if(r_center){
		_delay_us(1000);
		if(r_center) return 0;
	}
	else return 0;
}

int place(i,j){
	int p;
	return p = 2*i+j;
}

void lt_straight(){
		if(f_center){
			_delay_ms(5);
			if(f_center) straight(0xff/2);
		}

		if(f_right2){
			_delay_ms(3);
			if(f_right2) turn_right(0xff-20);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left(0xff-20);
		}
		else if(f_right1){
			_delay_ms(1);
			if(f_right1) turn_right(0xef-20);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left(0xef-20);
		}
		else if(f_center){
			_delay_ms(3);
			if(f_center) straight(0xff-20);
		}
		else straight(0xff);
}

void lt_straight2(){
		if(r_center){
			_delay_ms(5);
			if(r_center) straight(0xff/2);
		}

		if(r_right2){
			_delay_ms(3);
			if(r_right2) turn_right(0xff-20);
		}
		else if(r_left2){
			_delay_ms(3);
			if(r_left2) turn_left(0xff-20);
		}
		else if(r_right1){
			_delay_ms(1);
			if(r_right1) turn_right(0xef-20);
		}
		else if(r_left1){
			_delay_ms(1);
			if(r_left1) turn_left(0xef-20);
		}
		else if(r_center){
			_delay_ms(3);
			if(r_center) straight(0xff-20);
		}
		else straight(0xff);
}

void lt_back(int p){
		if(p == 0){
			r_straight(0xff);
		}

		if(p == 2){
			r_turn_right2(0xff-20);
		}
		else if(p == -2){
			r_turn_left2(0xff-20);
		}
		else if(p == 1){
			r_turn_right(0xef-20);
		}
		else if(p == -1){
			r_turn_left(0xef-20);
		}
		else if(p == 0){
			r_straight(0xff-20);
		}
		else r_straight(0xff);
}

/*���[�^�[�h���C�o���䖽��(�W������)*/

//�������C���g���[�X�p
/*�ʏ����*/
void straight(int s){
	motor_R(s,0);
	motor_L(s,0);
}

void back(int s){
	motor_R(0,s);
	motor_L(0,s);
}

void turn_right(int s){
	motor_R(s-50,0);
	motor_L(s,0);
}

void turn_left(int s){
	motor_R(s,0);
	motor_L(s-50,0);
}

void roll_left(int s){
	motor_R(s,0);
	motor_L(0,s);
}

void roll_right(int s){
	motor_R(0,s);
	motor_L(s,0);
}

void stop(){
	motor_R(0,0);
	motor_L(0,0);
}

/*�t����]��*/
void r_straight(int s){
	motor_R(0,s);
	motor_L(0,s);
}

void r_back(int s){
	motor_R(s,0);
	motor_L(s,0);
}

void r_turn_right(int s){
	motor_R(0,s);
	motor_L(0,s-50);
}

void r_turn_right2(int s){
	motor_R(0,s);
	motor_L(0,s-80);
}

void r_turn_right3(int s){
	motor_R(0,s);
	motor_L(0,s-100);
}

void r_turn_left(int s){
	motor_R(0,s-50);
	motor_L(0,s);
}

void r_turn_left2(int s){
	motor_R(0,s-80);
	motor_L(0,s);
}

void r_turn_left3(int s){
	motor_R(0,s-100);
	motor_L(0,s);
}

void r_roll_right(int s){
	motor_R(s,0);
	motor_L(0,s);
}

void r_roll_left(int s){
	motor_R(0,s);
	motor_L(s,0);
}


// �����g�Z���T�[
// 1cm�P�ʂŐ��l���A���Ă���
int sonic_sensor(){
	int cnt = 0;
	int n = 0.0;
	int buf[6];

	DDRA = 0x40;    // PA1���o�̓|�[�g�w��i���̃v���O�����̏ꍇ��PA6,7���o�͎w��j
	sbi(PORTA,PA6); //�����g�Z���T�[�̐ڑ��|�[�g��PA1
	_delay_us(5);
	cbi(PORTA,PA6);
	cnt = 0;

	DDRA = 0x00;	// PA1����̓|�[�g�w��(���̃v���O������PA6,7�͏o�͎w��)
	while(!(PINA & _BV(6))) TCNT1 = 0;
	while(PINA & _BV(6));

	n = TCNT1;
		
	cnt = n / 7.6598;	

	
//	usart_sendStr("TCNT1:"); // AD�l�𕶎���ɂ��đ��M
//  usart_sendStr(intToStr(cnt,buf)); // AD�l�𕶎���ɂ��đ��M
//  usart_sendStr("\r\n"); // ���s
	_delay_ms(10);
	//nop(2);

	return cnt;
}

void motor_R(int f,int b){//f�O b���
	if(f == 0 && b == 0){
		PORTB |= 0x01;
	}
	else{
		PORTB = 0x00;
		OCR0A = f;
		OCR0B = b;
	}
}

void motor_L(int f,int b){//f�O b���
	if(f == 0 && b == 0){
		PORTB |= 0x02;
	}
	else{
		PORTB = 0x00;
		OCR2A = f;
		OCR2B = b;
	}
}

/*90�x��]*/
void rad90_r(){
	roll_right(0xaf);
	if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)
		while(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)_delay_ms(700);
	
	while(1){
		if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
			if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
				motor_R(0xff,0xff);
				motor_L(0xff,0xff);
				_delay_ms(200);
				return;
			}
			else{
				roll_left(0xaf);
				_delay_ms(100);
			}
		}
	}
}

void rad90_l(){
	roll_left(0xaf);
	if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)
		while(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)_delay_ms(700);
	
	while(1){
		if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
			if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
				motor_R(0xff,0xff);
				motor_L(0xff,0xff);
				_delay_ms(200);
				return;
			}
			else{
				roll_left(0xaf);
				_delay_ms(100);
			}
		}
	}
}

int main(){

	DDRA = 0x00;
	DDRC = 0x00;
	DDRB = 0xff;
	DDRD = 0xff;
	//int cnt=0;
	int c = 0;
	//int lf=0,rf=0;
	int s = 0xff;

	TCCR0A = 0b10100011;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0b00000001;
	TCCR1A = 0;  	  // OCR1A OCR1B �̐ݒ�
	TCCR1B = 3;
	TCCR2A = 0b10100011;  // OCR2A OCR2B �̐ݒ�
	TCCR2B = 0b00000001;
	

	PORTB = 0x03;
	_delay_ms(1500);
	PORTB = 0x00;
	
	TCNT1 = 0;
	while(1){
		lt_back(place(img_boad2(),img_boad1()));
	}
	
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
	_delay_ms(5000);

	return 0;
}
