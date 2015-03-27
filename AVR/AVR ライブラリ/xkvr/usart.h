// ======================================================================
// xkvr (XMEGA KUT AVR Library) / usart.h / v1.0
// USART ライブラリ
// ======================================================================
//
// * USART の初期化
//
//     usart_init(USART のポート, ボーレート);
//
// * printf 関数互換
//
//     usart_printf(USART のポート, フォーマット文字列, 可変長引数 ...);
//
// * vprintf 関数互換
//
//     usart_vprintf(USART のポート, フォーマット文字列, 可変長引数リスト);
//
// * puts 関数互換
//
//     usart_puts(USART のポート, 文字列);
//
// * putchar 関数互換
//
//     usart_putchar(USART のポート, 文字);
//
// ======================================================================
//
// * v1.0
//   初版
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


// USART のポートの設定
void usart_port_init(USART_t * const usart);


// USART の設定
void usart_init(USART_t * const usart, const uint32_t boud){
	const uint16_t ubrr = F_CPU / 16 / boud - 1;
	
	// ポートの設定
	usart_port_init(usart);
	
	// ボーレート設定
	usart->BAUDCTRLA = (uint8_t)ubrr;
	usart->BAUDCTRLB = (uint8_t)(ubrr >> 8);
	
	// 送信有効 & 受信有効
	usart->CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	// 非同期 & 8 ビット & パリティ無効 & ストップビット 1
	usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc;
}

// 1 バイト送信
void usart_send(USART_t * const usart, char c){
	
	// 送信可能まで待機
	loop_until_bit_is_set(usart->STATUS, USART_DREIF_bp);
	
	// 送信
	usart->DATA = c;
}

// 1 文字送信 (改行コードの自動変換を含む)
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

// 1 行送信
// puts 互換
int usart_puts(USART_t * const usart, const char *s){
	int i;
	
	for(i = 0; s[i] != '\0'; ++i){
		usart_putchar(usart, s[i]);
	}
	
	usart_putchar(usart, '\n');
	
	return 0;
}

// vprintf 互換
int usart_vprintf(USART_t * const usart, const char *format, va_list arg){
	int result, i;
	char buff[XKVR_USART_BUFFER]; // バッファ
	
	result = vsprintf(buff, format, arg);
	
	// 送信
	for(i = 0; buff[i] != '\0'; ++i){
		usart_putchar(usart, buff[i]);
	}
	
	return result;
}

// printf 互換
int usart_printf(USART_t * const usart, const char *format, ...){
	va_list arg;
	int result;
	
	va_start(arg, format);
	
	result = usart_vprintf(usart, format, arg);
	
	va_end(arg);
	
	return result;
}

// USART のポートの設定
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
