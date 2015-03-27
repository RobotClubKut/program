#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "servo.h"

void servo1x_init(void)
{
	//OCR1A,OCR1B (16bit)‚Ìİ’è
	TCCR1A = 0b10100010;	//‚‘¬PWM(TOP’l = ICR1)
							//”äŠrˆê’v‚ÅLowABOTTOM(TCNT = 0)‚ÅHigh
	TCCR1B = 0b00011010;	//8•ªü
	ICR1 = 20000;			//TCNT = 20000‚ÅTCNT = 0
}
void servo1b_set(int32_t angle_deg)
{
	OCR1B = 25*angle_deg/3+1000;
}
void servo1a_set(int32_t angle_deg)
{
	OCR1A = 25*angle_deg/3+1000;
}

