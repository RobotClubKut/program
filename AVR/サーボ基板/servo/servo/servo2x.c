#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include"servo.h"
static int timer2_count = 0;

//タイマ2オーバーフロー割り込み
ISR(TIMER2_OVF_vect)
{
	if(timer2_count < 4)
	{
		TCNT2 = OCR2B-1;
		timer2_count++;
		_delay_us(65);
		TCNT2 = 131;
	}
	else
	{
		timer2_count = 0;
	}
}

//servo2x初期化関数
void servo2x_init(void)
{
	//OCR2A,OCR2B の設定
	TCCR2A = 0b10100011;	//8ビット高速PWM
	TCCR2B = 0b00000110;	//256分周

	TIMSK2 = 0b00000001;	//タイマ0オーバーフロー割り込み許可
	sei();
}
void servo2b_set(int32_t angle_deg)
{
	OCR2B = 31.25*angle_deg/120+31.25;
}

void servo2a_set(int32_t angle_deg)
{
	OCR2A = 31.25*angle_deg/120+31.25;
}
