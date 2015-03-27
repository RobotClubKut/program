#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

static int timer0_count = 0;
static int timer2_count = 0;

void servo_init(void)
{
//	servo0x_init();
	servo1x_init();
//	servo2x_init();
}
void servo1x_init(void)
{
	//OCR1A,OCR1B (16bit)の設定
	TCCR1A = 0b10100010;	//高速PWM(TOP値 = ICR1)
							//比較一致でLow、BOTTOM(TCNT = 0)でHigh
	TCCR1B = 0b00011010;	//8分周
	ICR1 = 20000;			//TCNT = 20000でTCNT = 0
}
void servo1b_set(int32_t angle_deg)
{
	OCR1B = 25*angle_deg/3+1000;
}
void servo1a_set(int32_t angle_deg)
{
	OCR1A = 25*angle_deg/3+1000;
}
/*
//タイマ0オーバーフロー割り込み
ISR(TIMER0_OVF_vect)
{
	if(timer0_count < 4)
	{
		TCNT0 = OCR0B-1;
		timer0_count++;
		_delay_us(65);
		TCNT0 = 131;
	}
	else
	{
		timer0_count = 0;
	}
}

//servo0x初期化関数
void servo0x_init(void)
{
	//OCR0A,OCR0B の設定
	TCCR0A = 0b10100011;	//8ビット高速PWM
	TCCR0B = 0b00000100;	//256分周

	TIMSK0 = 0b00000001;	//タイマ0オーバーフロー割り込み許可
	//sei();
}
void servo0b_set(int32_t angle_deg)
{
	OCR0B = 31.25*angle_deg/120+31.25;
}

void servo0a_set(int32_t angle_deg)
{
	OCR0A = 31.25*angle_deg/120+31.25;
}

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
	//sei();
}
void servo2b_set(int32_t angle_deg)
{
	OCR2B = 31.25*angle_deg/120+31.25;
}

void servo2a_set(int32_t angle_deg)
{
	OCR2A = 31.25*angle_deg/120+31.25;
}
*/
