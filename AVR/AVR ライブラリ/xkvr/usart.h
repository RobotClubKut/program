// ======================================================================
// xkvr (XMEGA KUT AVR Library) / usart.h / v1.0
// USART ���C�u����
// ======================================================================
//
// * USART �̏�����
//
//     usart_init(USART �̃|�[�g, �{�[���[�g);
//
// * printf �֐��݊�
//
//     usart_printf(USART �̃|�[�g, �t�H�[�}�b�g������, �ϒ����� ...);
//
// * vprintf �֐��݊�
//
//     usart_vprintf(USART �̃|�[�g, �t�H�[�}�b�g������, �ϒ��������X�g);
//
// * puts �֐��݊�
//
//     usart_puts(USART �̃|�[�g, ������);
//
// * putchar �֐��݊�
//
//     usart_putchar(USART �̃|�[�g, ����);
//
// ======================================================================
//
// * v1.0
//   ����
//
// ======================================================================

#ifndef __XKVR_USART__
#define __XKVR_USART__

#define XKVR_USART_VERSION 10100UL

#ifndef XKVR_USART_BUFFER
#define XKVR_USART_BUFFER 256
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>


// USART �̃|�[�g�̐ݒ�
void usart_port_init(USART_t * const usart);


// USART �̐ݒ�
void usart_init(USART_t * const usart, const uint32_t boud){
	const uint16_t ubrr = F_CPU / 16 / boud - 1;
	
	// �|�[�g�̐ݒ�
	usart_port_init(usart);
	
	// �{�[���[�g�ݒ�
	usart->BAUDCTRLA = (uint8_t)ubrr;
	usart->BAUDCTRLB = (uint8_t)(ubrr >> 8);
	
	// ���M�L�� & ��M�L��
	usart->CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	// �񓯊� & 8 �r�b�g & �p���e�B���� & �X�g�b�v�r�b�g 1
	usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc;
}

// 1 �o�C�g���M
void usart_send(USART_t * const usart, char c){
	
	// ���M�\�܂őҋ@
	loop_until_bit_is_set(usart->STATUS, USART_DREIF_bp);
	
	// ���M
	usart->DATA = c;
}

// 1 �������M (���s�R�[�h�̎����ϊ����܂�)
int usart_putchar(USART_t * const usart, int c){
	
	switch(c){
	case '\n':
		usart_send(usart, '\r');
		usart_send(usart, '\n');
		break;
	
	case '\r':
		break;
	
	default:
		usart_send(usart, c);
	}
	
	return c;
}

// 1 �s���M
// puts �݊�
int usart_puts(USART_t * const usart, const char *s){
	int i;
	
	for(i = 0; s[i] != '\0'; ++i){
		usart_putchar(usart, s[i]);
	}
	
	usart_putchar(usart, '\n');
	
	return 0;
}

// vprintf �݊�
int usart_vprintf(USART_t * const usart, const char *format, va_list arg){
	int result, i;
	char buff[XKVR_USART_BUFFER]; // �o�b�t�@
	
	result = vsprintf(buff, format, arg);
	
	// ���M
	for(i = 0; buff[i] != '\0'; ++i){
		usart_putchar(usart, buff[i]);
	}
	
	return result;
}

// printf �݊�
int usart_printf(USART_t * const usart, const char *format, ...){
	va_list arg;
	int result;
	
	va_start(arg, format);
	
	result = usart_vprintf(usart, format, arg);
	
	va_end(arg);
	
	return result;
}

// USART �̃|�[�g�̐ݒ�
void usart_port_init(USART_t * const usart){
	
#if defined(__AVR_ATxmega64D3__)  || \
	defined(__AVR_ATxmega128D3__) || \
	defined(__AVR_ATxmega192D3__) || \
	defined(__AVR_ATxmega256D3__)
	
	if(usart == &USARTC0){
		PORTC.OUT |= _BV(3);
		PORTC.DIR |= _BV(3);
	}
	
	else if(usart == &USARTD0){
		PORTD.OUT |= _BV(3);
		PORTD.DIR |= _BV(3);
	}
	
	else {
		PORTE.OUT |= _BV(3);
		PORTE.DIR |= _BV(3);
	}
	
#endif
	
}

#endif
