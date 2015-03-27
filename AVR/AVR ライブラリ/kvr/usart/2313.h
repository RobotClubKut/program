// ------------------------------------------------------------------
// kvr / KUT AVR Library
// USART for 2313 Library / "kvr/usart/2313.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012/10/07 20:27)
//   ����
//
// ------------------------------------------------------------------

#ifndef __KVR_USART_2313__
#define __KVR_USART_2313__

// USART �̌�
#define KVR_USART_LENGTH 1

// ������
static void usart_init_impl(
	volatile const uint8_t num,
	volatile const uint16_t ubrr
	)
{
	// �{�[���[�g�ݒ�
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;
	
	// ���M���� & ��M����
	UCSRB = _BV(TXEN) | _BV(RXEN);
	
	// 8 bit ����
	UCSRC = _BV(UCSZ1) | _BV(UCSZ0);
}

// ���M
static void usart_send_impl(
	volatile const uint8_t num,
	volatile const char c
	)
{
	// ���M�\�܂őҋ@
	loop_until_bit_is_set(UCSRA, UDRE);
	
	// ���M
	UDR = c;
}

// ��M
static uint8_t usart_receive_impl(
	volatile const uint8_t num
	)
{
	// ��M����܂őҋ@
	loop_until_bit_is_set(UCSRA, RXC);
	
	// ��M
	return UDR;
}

// ��M���荞��
static void usart_interrupt_impl(
	volatile const uint8_t num
	)
{
	// ��M���荞�݋���
	UCSRB |= _BV(RXCIE);
	
	// ���荞�݋���
	sei();
}

// ���荞�ݏ���
ISR(USART_RX_vect){
	usart_interrupt_callback(0, UDR);
}

#endif
