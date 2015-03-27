// ------------------------------------------------------------------
// kvr / KUT AVR Library
// USART for XX8 Library / "kvr/usart/XX8.h" / v1.1
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012/04/15 22:52)
//   ����
//
// - v1.1 (2012/05/24 20:19)
//   ��M�@�\��ǉ�
//
// ------------------------------------------------------------------

#ifndef KVR_USART_XX8
#define KVR_USART_XX8

// USART �̌�
#define KVR_USART_LENGTH 1

// ������
static void usart_init_impl(
	volatile const uint8_t num,
	volatile const uint16_t ubrr
	)
{
	// �{�[���[�g�ݒ�
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	// ���M���� & ��M����
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	
	// 8 bit ����
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

// ���M
static void usart_send_impl(
	volatile const uint8_t num,
	volatile const char c
	)
{
	// ���M�\�܂őҋ@
	loop_until_bit_is_set(UCSR0A, UDRE0);
	
	// ���M
	UDR0 = c;
}

// ��M
static uint8_t usart_receive_impl(
	volatile const uint8_t num
	)
{
	// ��M����܂őҋ@
	loop_until_bit_is_set(UCSR0A, RXC0);
	
	// ��M
	return UDR0;
}

// ��M���荞��
static void usart_interrupt_impl(
	volatile const uint8_t num
	)
{
	// ��M���荞�݋���
	UCSR0B |= _BV(RXCIE0);
	
	// ���荞�݋���
	sei();
}

// ���荞�ݏ���
ISR(USART_RX_vect){
	usart_interrupt_callback(0, UDR0);
}

#endif
