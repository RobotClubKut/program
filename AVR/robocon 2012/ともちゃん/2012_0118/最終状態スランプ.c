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

/*�Z���T�[�̒�`*/
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

#define SW1 PINB&_BV(5)
#define TS1 PINA&_BV(7)
#define LS0 PINC&_BV(7)

/* ���C���g���[�X�T�C�h */

int img_boad1(){//���z���C���g���[�X���
	if(f_center){
		if(f_center) return 0;
	}
	/*if(f_right3){
		if(f_right3) return 3;
	}
	else if(f_left3){
		if(f_left3) return -3;
	}
	else */if(f_right2){
		if(f_right2) return 2;
	}
	else if(f_left2){
		if(f_left2) return -2;
	}
	else if(f_right1){
		if(f_right1) return 1;
	}
	else if(f_left1){
		if(f_left1) return -1;
	}
	else if(f_center){
		if(f_center) return 0;
	}
	else return 0;
}
int img_boad2(){//���z���C���g���[�X���
	if(r_center){
		if(r_center) return 0;
	}
	/*if(r_left3){
		if(r_left3) return 3;
	}
	else if(r_right3){
		if(r_right3) return -3;
	}
	elseif(r_left2){
		if(r_left2) return 2;
	}
	else if(r_right2){
		if(r_right2) return -2;
	}
	else */if(r_left1){
		if(r_left1) return 1;
	}
	else if(r_right1){
		if(r_right1) return -1;
	}
	else if(r_center){
		if(r_center) return 0;
	}
	else return 0;
}

int place(i,j){
	int p;
	p = i;
	p += i;
	p += j;
	return p;
}

void lt_straight(){
		if(f_center){
			_delay_ms(5);
			if(f_center) straight(0xff);
		}

		if(f_right2){
			_delay_ms(3);
			if(f_right2) turn_right2(0xff);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left2(0xff);
		}
		else if(f_right1){
			_delay_ms(1);
			if(f_right1) turn_right1(0xff);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left1(0xff);
		}
		else if(f_center){
			_delay_ms(3);
			if(f_center) straight(0xff);
		}
		else straight(0xff);
}

void lt_straight2(){
		if(f_center){
			_delay_ms(5);
			if(f_center) straight(0xff - 50);
		}

		if(f_right2){
			_delay_ms(3);
			if(f_right2) turn_right2(0xff - 50);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left2(0xff - 50);
		}
		else if(f_right1){
			_delay_ms(1);
			if(f_right1) turn_right1(0xff - 50);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left1(0xff - 50);
		}
		else if(f_center){
			_delay_ms(3);
			if(f_center) straight(0xff - 50);
		}
		else straight(0xff - 50);
}

void lt_back(int p){
	switch(p){
	case -9:
		r_turn_left9(0xff);
		break;
	case -8:
		r_turn_left8(0xff);
		break;
	case -7:
		r_turn_left7(0xff);
		break;
	case -6:
		r_turn_left6(0xff);
		break;
	case -5:
		r_turn_left5(0xff);
		break;
	case -4:
		r_turn_left4(0xff);
		break;
	case -3:
		r_turn_left3(0xff);
		break;
	case -2:
		r_turn_left2(0xff);
		break;
	case -1:
		r_turn_left(0xff);
		break;
	case 0:
		r_straight(0xff);
		break;
	case 1:
		r_turn_right(0xff);
		break;
	case 2:
		r_turn_right2(0xff);
		break;
	case 3:
		r_turn_right3(0xff);
		break;
	case 4:
		r_turn_right4(0xff);
		break;
	case 5:
		r_turn_right5(0xff);
		break;
	case 6:
		r_turn_right6(0xff);
		break;
	case 7:
		r_turn_right7(0xff);
		break;
	case 8:
		r_turn_right8(0xff);
		break;
	case 9:
		r_turn_right9(0xff);
		break;
	}
}

void go(int n,int t){	

	int cnt = 0;
	while(cnt < n){
		if(f_right2){
			if(f_left2){
				if(f_right1){
					if(f_left1){
						if(f_center){
							cnt++;					//�t�H�g�g�����W�X�^5������cnt��+1
							straight();
							while((f_center) && (f_right2) && (f_right1) && (f_left2) && (f_left1)){}
							_delay_ms(t);
							while(cnt>=n) break;   //cnt�̐��l��n(���͂����l)
						}           //���傫���Ȃ�����break����
					}
				}
			}	
		}
		lt_straight();
	}
}

void go2(int n,int t){	

	int cnt = 0;
	while(cnt < n){
		if(f_right2){
			if(f_left2){
				if(f_right1){
					if(f_left1){
						if(f_center){
							cnt++;					//�t�H�g�g�����W�X�^5������cnt��+1
							straight();
							while((f_center) && (f_right2) && (f_right1) && (f_left2) && (f_left1)){}
							_delay_ms(t);
							while(cnt>=n) break;   //cnt�̐��l��n(���͂����l)
						}           //���傫���Ȃ�����break����
					}
				}
			}	
		}
		lt_straight2();
	}
}


void fw_go(int n,int t){	

	int cnt = 0;
	while(cnt < n){
		if(r_right2){
			if(r_left2){
				if(r_right1){
					if(r_left1){
						if(r_center){
							cnt++;					//�t�H�g�g�����W�X�^5������cnt��+1
							fw_straight();
							while((r_center) && (r_right3) && (r_right1) && (r_left3) && (r_left1)){}
							for(int i = 0;i < t;i++){
								_delay_ms(1);
							}
							while(cnt>=n) break;   //cnt�̐��l��n(���͂����l)
						}           //���傫���Ȃ�����break����
					}
				}
			}	
		}
		fw_straight();
	}
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
	motor_L(s-5,0);
}

void turn_right1(int s){
	motor_R(s-20,0);
	motor_L(s-5,0);
}
void turn_right2(int s){
	motor_R(s-40,0);
	motor_L(s-5,0);
}

void turn_left(int s){
	motor_R(s,0);
	motor_L(s-50,0);
}

void turn_left1(int s){
	motor_R(s,0);
	motor_L(s-20,0);
}
void turn_left2(int s){
	motor_R(s,0);
	motor_L(s-40,0);
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
	motor_L(0,s-30);
}

void r_turn_right2(int s){
	motor_R(0,s);
	motor_L(0,s-50);
}

void r_turn_right3(int s){
	motor_R(0,s);
	motor_L(0,s-70);
}

void r_turn_right4(int s){
	motor_R(0,s);
	motor_L(0,s-90);
}

void r_turn_right5(int s){
	motor_R(0,s);
	motor_L(0,s-110);
}

void r_turn_right6(int s){
	motor_R(0,s);
	motor_L(0,s-130);
}

void r_turn_right7(int s){
	motor_R(0,s);
	motor_L(0,s-150);
}

void r_turn_right8(int s){
	motor_R(0,s);
	motor_L(0,s-170);
}

void r_turn_right9(int s){
	motor_R(0,s);
	motor_L(0,s-190);
}

void r_turn_left(int s){
	motor_R(0,s-30);
	motor_L(0,s);
}

void r_turn_left2(int s){
	motor_R(0,s-50);
	motor_L(0,s);
}

void r_turn_left3(int s){
	motor_R(0,s-70);
	motor_L(0,s);
}
void r_turn_left4(int s){
	motor_R(0,s-90);
	motor_L(0,s);
}

void r_turn_left5(int s){
	motor_R(0,s-110);
	motor_L(0,s);
}

void r_turn_left6(int s){
	motor_R(0,s-130);
	motor_L(0,s);
}
void r_turn_left7(int s){
	motor_R(0,s-150);
	motor_L(0,s);
}

void r_turn_left8(int s){
	motor_R(0,s-170);
	motor_L(0,s);
}

void r_turn_left9(int s){
	motor_R(0,s-190);
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
	int c = 0;
	TCNT1 = 0;
	while(1){
		roll_left(0xdf);
		if(TCNT1 > 255){
			c++;
			TCNT1 = 0;
		}
		if(c > 435){
			_delay_ms(10);
			break;

		}
	}
}

void rad90_l2(){
	int c = 0;
	TCNT1 = 0;
	while(1){
		roll_left(0xaf);
		if(TCNT1 > 255){
			c++;
			TCNT1 = 0;
		}
		if(c > (370)){
			_delay_ms(7);
			break;

		}
	}
}

/*���t�g�֘A*/
void lift_up(){
	int n;
	while(1){
		PORTD |= 0x04;
		if(LS0){
			_delay_ms(5);
			if(LS0){
				break;
			}
		}
	}
	n ^= 0x40;
	PORTD &= n;
	
	PORTD |= 0x08;
	_delay_ms(50);
	n ^= 0x80;
	PORTD &= n;

}

void lift_down(){
	int n;
	while(1){
		PORTD |= 0x08;
		if(PINA & _BV(7)){
			_delay_ms(5);
			if(TS1){
				break;
			}
		}
	}
	n ^= 0x80;
	PORTD &= n;
	
	PORTD |= 0x04;
	_delay_ms(50);
	n ^= 0x40;
	PORTD &= n;
}

/*���ߑł��p*/
void lift_down2(int t){
	int n;
	
	PORTD |= 0x08;
	_delay_ms(t);
		
	
	n ^= 0x80;
	PORTD &= n;
	
	PORTD |= 0x04;
	_delay_ms(50);
	n ^= 0x40;
	PORTD &= n;
}

void lift_cyl_o(){
	int n;
	PORTD |= 0x02;
	_delay_ms(500);
	n ^= 0x02;
	PORTD &= n;
}

void lift_cyl_c(){
	int n;
	PORTD |= 0x01;
	_delay_ms(500);
	n ^= 0x01;
	PORTD &= n;
}
/*���t�g�I���*/


void fw_straight(){
		int f,b;
		f = img_boad2();
		b = img_boad1();
		lt_back(place(f,b));
}



void brake(){
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	 while(EECR & (1<<EEPE));	 /* �ȑO��EEPROM��۸���ݸފ����܂őҋ@ */
	 EECR = (0<<EEPM1)|(0<<EEPM0);	 /* �Ή���۸���ݸގ�ʐݒ� */
	 EEAR = uiAddress;	 /* EEPROM���ڽ�ݒ� */
	 EEDR = ucData;	 /* EEPROM�������ݒl��ݒ� */
	 EECR |= (1<<EEMPE);	 /* EEPROM����۸��ы��� */
	 EECR |= (1<<EEPE);	 /* EEPROM��۸���ݸފJ�n */
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	 while(EECR & (1<<EEPE));	 /* �ȑO��EEPROM��۸���ݸފ����܂őҋ@ */
	 EEAR = uiAddress;	 /* EEPROM���ڽ�ݒ� */
	 EECR |= (1<<EERE);	 /* EEPROM�ǂݏo���J�n */
	 return EEDR;	 /* EEPROM�ǂݏo���l���擾,���A */
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

	while(1){
		if(SW1){
			if(SW1){
				_delay_ms(20);
				while(SW1);
				break;
			}
		}
	}
	
	lift_up();
	_delay_ms(100);
	lift_down();
	lift_up();
	lift_cyl_c();
	_delay_ms(500);

	while(1){
		if(SW1){
			if(SW1){
				_delay_ms(20);
				while(SW1);
				break;
			}
		}
	}

	go(7,50);
	//go(3,50);
	brake();
	_delay_ms(1000);
	lift_down();
	_delay_ms(500);
	lift_cyl_o();
	_delay_ms(500);
	lift_up();
	_delay_ms(500);

	fw_go(5,55);
	_delay_ms(100);
	brake();
	_delay_ms(1000);
	rad90_l();
	brake();
	_delay_ms(500);
	lt_straight(0xff>>2);
	_delay_ms(300);
	brake();

	lift_down2(300);
	lift_cyl_c();
	_delay_ms(500);
	brake();

	fw_go(1,50);
	_delay_ms(500);
	brake();	
	_delay_ms(500);
	rad90_l2();
	brake();
	_delay_ms(500);

	go2(2,70);
	
	brake();
	_delay_ms(100);

	return 0;
}
