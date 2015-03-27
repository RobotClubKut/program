#define F_CPU 20000000

#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	uint16_t i,j;

	DDRA = 0xff;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;

	while (1)
	{
		j = 0x80;
		for (i = 1; i <= 0x80; i = i << 1)
		{
			PORTA = j;
			PORTB = i;
			PORTC = i;
			PORTD = i;
			j = j >> 1;
			_delay_ms (250);
		}
	}

	return 0;
}
