// ------------------------------------------------------------------
// kvr / KUT AVR Library
// USART Library / "kvr/usart.h" / v1.2
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   ����
//
// - v1.1
//   ���͏�����ǉ�
//
// - v1.2 (2012/10/07)
//   ATtiny2313 �ɑΉ� (�ꕔ�֐��͖��Ή�)�B
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
//   - 20 PIN
//     ATtiny2313/2313A
//     
//     * �ȉ��̊֐��� 20 PIN �}�C�R���ł͖��Ή��ł��B
//
//       - usart_stdin
//       - usart_stdout
//       - usart_stdio
//       - usart_printf
//       - usart_vprintf
//
// ------------------------------------------------------------------

#ifndef __KVR_USART__
#define __KVR_USART__

#define KVR_USART_VERSION 10200UL // version 1.02.00

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

static uint8_t usart_receive_impl(
	volatile const uint8_t num
	);

static void usart_interrupt_impl(
	volatile const uint8_t num
	);

static void usart_interrupt_callback(
	volatile const uint8_t num,
	volatile const uint8_t c
	);

#if   defined(KVR_BASE_XX4)
#include "usart/XX4.h"
#elif defined(KVR_BASE_XX8)
#include "usart/XX8.h"
#elif defined(KVR_BASE_2313)
#include "usart/2313.h"
#else
#error "This microprocessor is not supported."
#endif

// ------------------------------------------------------------------

#ifndef KVR_BASE_2313

// �t�@�C���|�C���^
static FILE* usart_fp[KVR_USART_LENGTH];

#endif

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

#ifndef KVR_BASE_2313

// fdevopen �p�֐�
int usart_putc(char c, FILE* stream);
int usart_getc(FILE* stream);

#endif

// ------------------------------------------------------------------

// ������
FILE *usart_init(
	volatile uint8_t num,
	volatile uint32_t boud
	)
{
	// �����Ăяo��
	usart_init_impl(num, usart_get_ubrr(boud));
	
#if defined(KVR_BASE_2313)
	return NULL;
#else
	// �t�@�C���|�C���^���擾
	usart_fp[num] = fdevopen(usart_putc, usart_getc);
	
	return usart_fp[num];
#endif

}

// ���M
void usart_send(
	volatile uint8_t num,
	volatile char c
	)
{
	usart_send_impl(num, c);
}

// ��M
uint8_t usart_receive(
	volatile const uint8_t num
	)
{
	return usart_receive_impl(num);
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

#ifndef KVR_BASE_2313

// �W���o�͂ɐݒ�
void usart_stdout(
	volatile const uint8_t num
	)
{
	stdout = usart_fp[num];
}

// �W�����͂ɐݒ�
void usart_stdin(
	volatile const uint8_t num
	)
{
	stdin = usart_fp[num];
}

// �W�����o��
void usart_stdio(
	volatile const uint8_t num
	)
{
	usart_stdout(num);
	usart_stdin(num);
}

int usart_putc(char c, FILE *stream){
	
#if KVR_USART_LENGTH == 1
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

int usart_getc(FILE *stream){
	
#if KVR_USART_LENGTH == 1
	return usart_receive(0);
#else
	register uint8_t i;
	
	for(i = 0; i < KVR_USART_LENGTH; ++i){
		if(usart_fp[i] == stream){
			return usart_receive(i);
		}
	}
#endif
	
	return EOF;
}

#endif

void usart_putchar(
	volatile const uint8_t num,
	volatile const int c
	)
{
	usart_send(num, c);
}

void usart_print(
	volatile const uint8_t num,
	const char *s
	)
{
	while(*s != '\0'){
		usart_send(num, *s++);
	}
}

void usart_puts(
	volatile const uint8_t num,
	const char *s
	)
{
	usart_print(num, s);
	usart_send(num, '\n');
}

void usart_putint(
	volatile const uint8_t  num,
	volatile       uint32_t n
	)
{
	uint8_t  i = 0;
	uint32_t t = 1;
	char buff[11] = { '0' };
	
	// �������v�Z
	while(t <= n){
		++i;
		t *= 10;
	}
	
	// 10 �i��������ɕϊ�
	for(--i ; n > 0; --i){
		buff[i]  = n % 10 + '0';
		n       /= 10;
	}

	usart_print(num, buff);
}

uint8_t usart_getchar(
	volatile const uint8_t num
	)
{
	return usart_receive(num);
}

#ifndef KVR_BASE_2313

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

#endif

#endif
