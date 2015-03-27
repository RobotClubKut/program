// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Base Library / "kvr/usart/XX8.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012/04/15 22:52)
//   初版
//
// ------------------------------------------------------------------

#ifndef KVR_USART_XX8
#define KVR_USART_XX8

// USART の個数
#define KVR_USART_LENGTH 1

// 初期化
static void usart_init_impl(
	volatile const uint8_t num,
	volatile const uint16_t ubrr
	)
{
	// ボーレート設定
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	// 送信許可
	UCSR0B = _BV(TXEN0);
	
	// 8 bit 動作
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

// 送信
static void usart_send_impl(
	volatile const uint8_t num,
	volatile const char c
	)
{
	// 送信可能まで待機
	loop_until_bit_is_set(UCSR0A, UDRE0);
	
	// 送信
	UDR0 = c;
}

// 受信割り込み
static void usart_interrupt_impl(
	volatile const uint8_t num
	)
{
	// 受信許可 & 受信割り込み許可
	UCSR0B |= _BV(RXEN0) | _BV(RXCIE0);
	
	// 割り込み許可
	sei();
}

// 割り込み処理
ISR(USART_RX_vect){
	usart_interrupt_callback(0, UDR0);
}

#endif