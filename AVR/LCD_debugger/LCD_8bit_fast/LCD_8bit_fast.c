//cpuクロック 20MHz
#define F_CPU 20000000

//usart ボーレート
#define BOUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


//プロトタイプ宣言
char usart_receive (void);
void usart_init (uint16_t);

//エントリーポイント
int main (void)
{
	uint8_t i;
	char buff = 0, str[17] = "     ready";

	//LCD 8bit 初期化 ※ 8bitモード, 2行, 5×8ドット, 表示on, カーソルoff, カーソル点滅off, ACデクリメント, カーソルオートシフトoff
	lcd_init (MODE_8BIT | USE_2LINE | DOT_5X8, DISPLAY_ON | CURSOR_OFF | BLINK_OFF, AC_DEC | COS_OFF);

	//usart 初期化
	usart_init (BOUD);

	//usart準備完了
	lcd_position (0 | LINE1);
	lcd_str ("usart receive");
	lcd_position (0 | LINE2);
	lcd_str (str);

	//∞ループ
	while(1)
	{
		//カーソルを2行目に設定
		lcd_position (0 | LINE2);

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
			lcd_ch (str[i] = buff);
		}

		//ディスプレイクリア
		lcd_clear ();

		//バッファの書き込み
		lcd_str (str);
	}
	return 0;
}


//usart受信
char usart_receive (void)
{
	// 受信するまで待機
	loop_until_bit_is_set (UCSRA, RXC);
	
	// 受信
	return UDR;
}

//usart 初期化
void usart_init (uint16_t boud)
{
	boud = (((F_CPU >> 4) / boud) - 1);
	UBRRH = (uint8_t)(boud >> 8);
	UBRRL = (uint8_t)boud;
	UCSRB = _BV (TXEN) | _BV (RXEN);
	UCSRC = _BV (UCSZ1) | _BV (UCSZ0);
	return;
}
