// --------------------------------------------------------
// �T�[�{��p�v���O���� v1.0 (2012/03/09 1:08)
// --------------------------------------------------------
// ATmega168p (1 MHz) �p�v���O����
// CKDIV8 ��ݒ肵�� 8 �������A1 MHz �œ��삳���邱�ƁB
// --------------------------------------------------------

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

// GW�T�[�{ (Servo S03T 2BBMG)
int servo(int i){
	
	// �f�t�H���g�ł�9����8�̂ق������肷��炵��
	return (i / 7) + 8;
}

// �����ݒ�
void init(void){
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	// PWM �̐ݒ�
	// 8 bit ���� PWM (64 ����)
	
	// OCR0A, OCR0B
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000011;
	
	// OCR1A, OCR1B
	TCCR1A = 0b10100001;
	TCCR1B = 0b00001011;
	
	// OCR2A, OCR2B
	TCCR2A = 0b10100011;
	TCCR2B = 0b00000100;
}

int main(void){
	
	init();
	
	while(1){
		// 0 �x
		OCR0A = servo(0);
		_delay_ms(1000);
		
		// 180 �x
		OCR0A = servo(180);
		_delay_ms(1000);
	}
	
	return 0;
}
