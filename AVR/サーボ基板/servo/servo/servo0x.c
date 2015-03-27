#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "servo.h"

static int timer0_count = 0;

//�^�C�}0�I�[�o�[�t���[���荞��
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

//servo0x�������֐�
void servo0x_init(void)
{
	//OCR0A,OCR0B �̐ݒ�
	TCCR0A = 0b10100011;	//8�r�b�g����PWM
	TCCR0B = 0b00000100;	//256����

	TIMSK0 = 0b00000001;	//�^�C�}0�I�[�o�[�t���[���荞�݋���
	sei();
}
void servo0b_set(int32_t angle_deg)
{
	OCR0B = 31.25*angle_deg/120+31.25;
}

void servo0a_set(int32_t angle_deg)
{
	OCR0A = 31.25*angle_deg/120+31.25;
}
