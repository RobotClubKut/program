/*
 * lcd_usart.c
 *
 * Created: 2012/12/24 (月) AM 5:15:56
 *  Author: hikari
 */ 


#include "stdafx.h"

/*-
//バッファ
uint8_t ubuff[BUFFSIZE];
uint8_t wc, rc;
*/


//usart初期化
void usart_init (uint16_t boud)
{
	boud = (uint16_t)(((F_CPU >> 4) / boud) - 1);
	UBRRH = (uint8_t)(boud >> 8);
	UBRRL = (uint8_t)boud;
	UCSRB = _BV (TXEN) | _BV (RXEN);
	UCSRC = _BV (UCSZ1) | _BV (UCSZ0);

	// 受信割り込み許可
/*	UCSRB |= _BV(RXCIE);
	
	// 割り込み許可
	sei();*/

	return;
}

//usart受信
uint8_t usart_receive (void)
{
	// 受信するまで待機
	loop_until_bit_is_set (UCSRA, RXC);
	
	// 受信
	return UDR;
}

/*

//バッファから1文字取得
uint8_t getubuff (void)
{
	uint8_t buff;
	while (wc == rc);
	buff = ubuff[rc++];
	rc &= ~BUFFSIZE;
	return buff;
}

// 割り込み処理
ISR (USART_RX_vect)
{
	ubuff[wc++] = UDR;
	wc &= ~BUFFSIZE;
	if (wc == rc)
	{
		rc++;
		rc &= ~BUFFSIZE;
	}
	return;
}

*/
