// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Base Library / "kvr/usart.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   ����
//
// ------------------------------------------------------------------
// * �Ή��}�C�R��
//
//   - 28 PIN
//     ATmega48/48A/48P/88/88A/88P/88PA/168/168A/168P/328/328P
//
//   - 40 PIN
//     ATmega164P/164A/324P/324A/324PA/644/644P/644A/644PA/1284P
//
// ------------------------------------------------------------------

#ifndef __KVR_USART__
#define __KVR_USART__

#include <stdio.h>
#include <stdint.h>

#include <avr/interrupt.h>

#include "base.h"

// ------------------------------------------------------------------
// * �}�C�R���ʎ���
// ------------------------------------------------------------------

static void usart_init_impl(
	volatile const uint8_t num,
	volatile const uint16_t ubrr
	);

static void usart_send_impl(
	volatile const uint8_t num,
	volatile const char c
	);

static void usart_interrupt_impl(
	volatile const uint8_t num
	);

static void usart_interrupt_callback(
	volatile const uint8_t num,
	volatile const uint8_t c
	);

#if defined(KVR_BASE_XX4)
#include "usart/XX4.h"
#elif defined(KVR_BASE_XX8)
#include "usart/XX8.h"
#else
#error "This microprocessor is not supported."
#endif

// ------------------------------------------------------------------

// �t�@�C���|�C���^
static FILE* usart_fp[KVR_USART_LENGTH];

// �֐��|�C���^
static void (* volatile usart_callback[KVR_USART_LENGTH])(volatile const uint8_t);

// ------------------------------------------------------------------

// �{�[���[�g�v�Z��
static inline uint16_t usart_get_ubrr(volatile uint32_t boud){
	return F_CPU / 16 / boud - 1;
}

// ���荞�݃R�[���o�b�N�֐�
static void usart_interrupt_callback(
	volatile const uint8_t num,
	volatile const uint8_t c
	)
{
	usart_callback[num](c);
}

// ------------------------------------------------------------------

// fdevopen �p�֐�
int usart_putc(char c, FILE* stream);

// ------------------------------------------------------------------

// ������
void usart_init(
	volatile uint8_t num,
	volatile uint32_t boud
	)
{
	// �����Ăяo��
	usart_init_impl(num, usart_get_ubrr(boud));
	
	// �t�@�C���|�C���^���擾
	usart_fp[num] = fdevopen(usart_putc, NULL);
}

// ���M
void usart_send(
	volatile uint8_t num,
	volatile char c
	)
{
	usart_send_impl(num, c);
}

// ��M���荞��
void usart_interrupt(
	volatile const uint8_t num,
	void (* volatile callback)(char)
	)
{
	usart_interrupt_impl(num);
	usart_callback[num] = (void (* volatile)(volatile const uint8_t))callback;
}

// �W���o�͂ɐݒ�
void usart_stdout(
	volatile const uint8_t num
	)
{
	stdout = usart_fp[num];
}

int usart_putc(char c, FILE *stream){
	
#if KVR_USART_LENGTH == 0
	usart_send(0, c);
#else
	register uint8_t i;
	
	for(i = 0; i < KVR_USART_LENGTH; ++i){
		if(usart_fp[i] == stream){
			usart_send(i, c);
			break;
		}
	}
#endif
	
	return 0;
}

void usart_putchar(
	volatile const uint8_t num,
	volatile const int c
	)
{
	(void)fputc(c, usart_fp[num]);
}

void usart_vprintf(
	volatile uint8_t num,
	const char* format,
	va_list arg
	)
{
	(void)vfprintf(usart_fp[num], format, arg);
}

void usart_printf(
	volatile const uint8_t num,
	const char *format, ...
	)
{
	va_list arg;
	
	va_start(arg, format);
	
	(void)vfprintf(usart_fp[num], format, arg);
	
	va_end(arg);
}

void usart_puts(
	volatile const uint8_t num,
	const char *s
	)
{
	(void)fputs(s, usart_fp[num]);
}

#endif
