#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "servo/servo.h"
//���W�R���T�[�{�̊p�x
//���@15
//����60
//�E  85
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

	//�|�[�g�̓��o�͂̐ݒ�
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	//servo������
	//OCR1A,OCR1B (16bit)�̐ݒ�
	TCCR1A = 0b10100010;	//����PWM(TOP�l = ICR1)
							//��r��v��Low�ABOTTOM(TCNT = 0)��High
	TCCR1B = 0b00011010;	//8����
	ICR1 = 20000;			//TCNT = 20000��TCNT = 0
	
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
