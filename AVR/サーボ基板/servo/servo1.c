#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "servo/servo.h"
//ラジコンサーボの角度
//左　15
//中央60
//右  85
int main(void)
{
	int i = 0;	 
	int f = 0;
	int f1 = 0;
	int f2 = 0;
	int j = 1;
	long t = 0;
	int d = 0;
	long deg = 0;

	//ポートの入出力の設定
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	//servo初期化
	//OCR1A,OCR1B (16bit)の設定
	TCCR1A = 0b10100010;	//高速PWM(TOP値 = ICR1)
							//比較一致でLow、BOTTOM(TCNT = 0)でHigh
	TCCR1B = 0b00011010;	//8分周
	ICR1 = 20000;			//TCNT = 20000でTCNT = 0
	
	_delay_ms(500);
	while(1)
	{
		servo1b_set(-25);
		_delay_ms(1000);
		
		servo1b_set(135);
		_delay_ms(1000);
	}
	return 0;
}
