// ------------------------------------------------------------------
// kvr / KUT AVR Library
// USART for 2313 Library / "kvr/usart/2313.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012/10/07 20:27)
//   初版
//
// ------------------------------------------------------------------

#ifndef __KVR_USART_2313__
#define __KVR_USART_2313__

// USART の個数
#define KVR_USART_LENGTH 1

// 初期化
static void usart_init_impl(
	volatile const uint8_t num,
	volatile const uint16_t ubrr
	)
{
	// ボーレート設定
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;
	
	// 送信許可 & 受信許可
	UCSRB = _BV(TXEN) | _BV(RXEN);
	
	// 8 bit 動作
	UCSRC = _BV(UCSZ1) | _BV(UCSZ0);
}

// 送信
static void usart_send_impl(
	volatile const uint8_t num,
	volatile const char c
	)
{
	// 送信可能まで待機
	loop_until_bit_is_set(UCSRA, UDRE);
	
	// 送信
	UDR = c;
}

// 受信
static uint8_t usart_receive_impl(
	volatile const uint8_t num
	)
{
	// 受信するまで待機
	loop_until_bit_is_set(UCSRA, RXC);
	
	// 受信
	return UDR;
}

// 受信割り込み
static void usart_interrupt_impl(
	volatile const uint8_t num
	)
{
	// 受信割り込み許可
	UCSRB |= _BV(RXCIE);
	
	// 割り込み許可
	sei();
}

// 割り込み処理
ISR(USART_RX_vect){
	usart_interrupt_callback(0, UDR);
}

#endif
