// ------------------------------------------------------------------
// kvr / KUT AVR Library
// USART for XX8 Library / "kvr/usart/XX8.h" / v1.1
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012/04/15 22:52)
//   初版
//
// - v1.1 (2012/05/24 20:19)
//   受信機能を追加
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
	
	// 送信許可 & 受信許可
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	
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

// 受信
static uint8_t usart_receive_impl(
	volatile const uint8_t num
	)
{
	// 受信するまで待機
	loop_until_bit_is_set(UCSR0A, RXC0);
	
	// 受信
	return UDR0;
}

// 受信割り込み
static void usart_interrupt_impl(
	volatile const uint8_t num
	)
{
	// 受信割り込み許可
	UCSR0B |= _BV(RXCIE0);
	
	// 割り込み許可
	sei();
}

// 割り込み処理
ISR(USART_RX_vect){
	usart_interrupt_callback(0, UDR0);
}

#endif
