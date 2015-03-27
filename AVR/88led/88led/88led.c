/*
 * _88led.c
 *
 * Created: 2013/02/22 (金) AM 11:02:49
 *  Author: hikari
 */
#define F_CPU 8000000L

//#define USEFONT_NUM
//#define USEFONT_UPALP
//#define USEFONT_LOWALP
#define USEFONT_KANA
#define USEFONT_HIRA
//#define USEFONT_SYM1
//#define USEFONT_SYM2
//#define USEFONT_SYM3
//#define USEFONT_SYM4
//#define USEFONT_SYM5
//#define USEFONT_SYM6
//#define USEFONT_SYM7
//#define USEFONT_SYM8
//#define USEFONT_SYM9
//#define USEFONT_SYM10
//#define USEFONT_SYM11
//#define USEFONT_SYM12
//#define USEFONT_SYM13

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "font.h"

#define TIME 0
#define LED_H PORTB
#define LED_L1 PORTD
#define LED_L2 PORTA

#define dtime 1000

void led_char (uint8_t *, uint8_t);
//void led_str (char *, uint8_t);
void led_sclstr (char *, uint8_t);

const uint8_t LED_LINE1[8] PROGMEM = {0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00};
const uint8_t LED_LINE2[8] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01};

//表示フォントデータ格納
uint8_t font[8] = {0};

ISR (TIMER0_OVF_vect)
{
	static uint8_t i = 0;
//	TCNT0 = TIME;
	
	LED_H = font[i];
	LED_L1 = pgm_read_byte (LED_LINE1 + i);
	LED_L2 = pgm_read_byte (LED_LINE2 + i);
	(i < 7) ? (i++) : (i = 0);
}
	
int main(void)
{
	char *ch[] = {"ようこそロボットクラブへ"};
	
	DDRD = 0x7f;
	DDRB = 0xff;
	DDRA = 0x03;
	
	TCCR0A = 0x00;
	TCCR0B = 0x02;
	TIMSK = 0x02;
	TCNT0 = TIME;
	sei();
	
    while(1)
    {
		led_sclstr (ch[0], 0);
		//s ^= 1;
    }
	
	return 0;
}
/*
void led_str (char *str, uint8_t rev)
{
	uint8_t *pfont;
	
	for (uint8_t *pch = str; *pch != '\0'; pch++)
	{
		if (fchar (pch, &pfont) == 2)
		{
			pch++;
		}			
		led_char (pfont, (rev & 1));
		_delay_ms (750);
	}
	return;
}
*/
//flag : 0x01 リバースフラグ(1:リバース, 0:ノーマル), 0x02 メモリフラグ(1:ram上配列, 0:rom上配列)
void led_char (uint8_t *data, uint8_t flag)
{
	//*
	for (uint8_t i = 0; i < 8; i++)
	{
		font[i] = data[i];
	}//*/
	/*
	if (flag & 2)
	{
		if (flag & 1)
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				font[i] = ~data[i];
			}
		}
		else
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				font[i] = data[i];
			}
		}
	}		
	else
	{
		if (flag & 1)
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				font[i] = ~pgm_read_byte (data + i);
			}
		}
		else
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				font[i] = pgm_read_byte (data + i);
			}
		}
	}
	//*/
	return;
}


void led_sclstr (char *str, uint8_t rev)
{
	uint8_t *pfont;
	uint8_t data[8] = {0};
	
	for (uint8_t *pch = str; ; pch++)
	{
		if (*pch != '\0')
		{
			if (fchar (pch, &pfont) == 2)
			{
				pch++;
			}
		}		
		
		for (uint8_t j = 7; j < 8; j--)
		{
			for (uint8_t k = 0; k < 8; k++)
			{
				data[k] <<= 1;
				if (*pch != '\0')
				{
					data[k] |= ((pgm_read_byte (pfont + k) >> j) & 1);
				}					
			}
			
			led_char (data, (rev | 2));
			
			_delay_ms (100);
		}
		
		if (*pch == '\0')
		{
			break;
		}
	}
	
	return;
}




