#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "servo.h"

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

