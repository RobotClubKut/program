/*
 * lcd_test1.c
 *
 * Created: 2012/12/24 (月) AM 12:40:43
 *  Author: hikari
 */


//ボーレートの設定とかは"stdafx.h"にあるよ
#include "stdafx.h"


int main (void)
{
	uint8_t i = 0;
	char buff, str[17] = {0};
	_delay_ms(500);
	clcd_init (MODE_8BIT | USE_2LINE | DOT_5X8, CDISPLAY_ON | CURSOR_ON | BLINK_ON, AC_INC | CS_OFF);
	clcd_position (LINE1 | 0);
	clcd_str ("LCD init OK");
	
	usart_init(BOUD);
	clcd_position (LINE2 | 0);
	clcd_str ("usart ready");
	
	while(1)
	{
		//カーソルを2行目に設定
		clcd_position (LINE2);

		//16文字分回す
		for (i = 0; i < 16; i++)
		{
			//改行のとき
			if ('\n' == (buff = usart_receive ()))
			{
				//バッファクリア
				while (str[i] != '\0')
					str[i++] = '\0';
				break;
			}

			//文字表示
			clcd_ch (str[i] = buff);
		}

		//ディスプレイクリア
		clcd_clear ();

		//バッファの書き込み
		clcd_str (str);
	}

	/*
    while(1)
	{
		clcd_position (LINE1 | 0);
		buff = usart_receive ();
		clcd_clear ();
		if (buff == '\n')
		{
			while (str[i] != 0)
			str[i++] = 0;
			continue;
		}
		clcd_str (str);
		clcd_position (LINE2 | 0);
		clcd_ch (str[0] = buff);
		for (i = 1; i < 16; i++)
		{
			buff = usart_receive ();
			if (buff == '\n')
			{
				while (str[i] != 0)
					str[i++] = 0;
				break;
			}				
			clcd_ch (str[i] = buff);
		}			 
	}*/

	return 0;
}
