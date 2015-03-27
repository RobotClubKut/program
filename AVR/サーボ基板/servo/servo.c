#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "servo/servo.h"

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
	servo_init();
	
	//PINX ���̓��W�X�^
	while(1)
	{
		if(f == 0)
		{
			deg=0;
			f=1;
		}
		else
		{
			deg=100;
			f=0;
		}
		servo1b_set(deg);
		servo1b_set(deg);
		_delay_ms(1000);
	}
	return 0;
}
