/*
 * oled_test1.c
 *
 * Created: 2013/01/06 (日) AM 4:14:07
 *  Author: hikari
 */ 


//ボーレートの設定とかは"stdafx.h"にあるよ
#include "stdafx.h"


int main (void)
{
	uint8_t i = 0, c = 0;
	char buff, str[2][17] = {"\0", "\0"};
	oled_init (MODE_8BIT | USE_2LINE | DOT_5X8, CDISPLAY_ON | CURSOR_ON | BLINK_OFF, AC_INC | CS_OFF);
	oled_position (LINE1 | 0);
	oled_str ("OLED init OK");
	usart_init(BOUD);
	oled_position (LINE2 | 0);
	oled_str ("usart ready");
	
	while (1)
	{
		c = 0;
		for (i = 0; i < 16; i++)
		{
			if ((buff = usart_receive()) == '\n')
			{
				oled_position (LINE2 | i);
				while ((str[0][i] != 0) && (str[0][i] != ' '))
				{
					oled_ch (str[0][i++] = ' ');
					c = 1;
				}
				while (str[0][i] == ' ')
				{
					str[0][i++] = 0;
					c = 1;
				}
				break;
			}
			if (buff == str[0][i])
				continue;
			oled_position (LINE2 | i);
			oled_ch (str[0][i] = buff);
			c = 1;
		}
		if (c)
		{
			oled_home ();
			oled_str (str[1]);
			for (i = 0; i < 16; i++)
			{
				str[1][i] = str[0][i];
			}
			
		}
	}
	
	/*
	while (1)
	{
		oled_position (LINE2);
		for (i = 0; i < 16; i++)
		{
			if ((buff = usart_receive ()) == '\n')
			{
				while (str[i] != 0)
					str[i++] = 0;
				break;
			}
			oled_ch (str[i] = buff);
		}
		oled_clear ();
		_delay_us(100);
		oled_home ();
		oled_str (str);			
	}
	*/
	/*
	while(1)
	{
		oled_position (LINE1 | 0);
		buff = usart_receive ();
		oled_clear ();
		if (buff == '\n')
		{
			while (str[i] != 0)
			str[i++] = 0;
			continue;
		}
		oled_str (str);
		oled_position (LINE2 | 0);
		oled_ch (str[0] = buff);
		for (i = 1; i < 16; i++)
		{
			buff = usart_receive ();
			if (buff == '\n')
			{
				while (str[i] != 0)
					str[i++] = 0;
				break;
			}
			oled_ch (str[i] = buff);
		}
	}*/
	
	return 0;
}
