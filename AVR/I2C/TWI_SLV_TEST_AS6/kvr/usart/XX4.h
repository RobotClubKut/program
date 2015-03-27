// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Base Library / "kvr/usart/XX4.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012/04/15 22:56)
//   ����
//
// ------------------------------------------------------------------

#ifndef KVR_USART_XX4
#define KVR_USART_XX4

// USART �̌�
#define KVR_USART_LENGTH 2

#define KVR_USART_UDR   0
#define KVR_USART_UCSRA 1
#define KVR_USART_UCSRB 2
#define KVR_USART_UCSRC 3
#define KVR_USART_UBRRH 4
#define KVR_USART_UBRRL 5

static volatile uint8_t* usart_port[][6] = {
	{
		&UDR0,
		&UCSR0A,
		&UCSR0B,
		&UCSR0C,
		&UBRR0H,
		&UBRR0L
	},
	
	{
		&UDR1,
		&UCSR1A,
		&UCSR1B,
		&UCSR1C,
		&UBRR1H,
		&UBRR1L
	}
};

static void usart_init_impl(
	volatile const uint8_t num,
	volatile const uint16_t ubrr
	)
{
	// �{�[���[�g�ݒ�
	*usart_port[num][KVR_USART_UBRRH] = (uint8_t)(ubrr >> 8);
	*usart_port[num][KVR_USART_UBRRL] = (uint8_t)ubrr;
	
	// ���M����
	*usart_port[num][KVR_USART_UCSRB] = _BV(TXEN0);
	
	// 8 bit ����
	*usart_port[num][KVR_USART_UCSRC] = _BV(UCSZ01) | _BV(UCSZ00);
}

// ���M
static void usart_send_impl(
	volatile const uint8_t num,
	volatile const char c
	)
{
	// ���M�\�܂őҋ@
	loop_until_bit_is_set(*usart_port[num][KVR_USART_UCSRA], UDRE0);
	
	// ���M
	*usart_port[num][KVR_USART_UDR] = c;
}

// ��M���荞��
static void usart_interrupt_impl(
	volatile const uint8_t num
	)
{
	// ��M���� & ��M���荞�݋���
	*usart_port[num][KVR_USART_UCSRB] |= _BV(RXEN0) | _BV(RXCIE0);
	
	// ���荞�݋���
	sei();
}

// ���荞�ݏ���
ISR(USART0_RX_vect){
	usart_interrupt_callback(0, UDR0);
}

ISR(USART1_RX_vect){
	usart_interrupt_callback(1, UDR1);
}

#undef KVR_USART_UDR
#undef KVR_USART_UCSRA
#undef KVR_USART_UCSRB
#undef KVR_USART_UCSRC
#undef KVR_USART_UBRRH
#undef KVR_USART_UBRRL

#endif
