// --------------------------------------------------------
// サーボ基板用プログラム v1.0 (2012/03/09 1:08)
// --------------------------------------------------------
// ATmega168p (1 MHz) 用プログラム
// CKDIV8 を設定して 8 分周し、1 MHz で動作させること。
// --------------------------------------------------------

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

// GWサーボ (Servo S03T 2BBMG)
int servo(int i){
	
	// デフォルトでは9だが8のほうが安定するらしい
	return (i / 7) + 8;
}

// 初期設定
void init(void){
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	// PWM の設定
	// 8 bit 高速 PWM (64 分周)
	
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
		// 0 度
		OCR0A = servo(0);
		_delay_ms(1000);
		
		// 180 度
		OCR0A = servo(180);
		_delay_ms(1000);
	}
	
	return 0;
}
