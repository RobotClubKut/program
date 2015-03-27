// ------------------------------------------------------------------
// kvr / KUT AVR Library
// I2C Slave Library / "kvr/i2c/slave.h" / v1.0
// Author: KUT RobotClub, MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   初版
//
// ------------------------------------------------------------------

#ifndef __KVR_I2C_SLAVE__
#define __KVR_I2C_SLAVE__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

#include "def.h"
#include "common.h"


// ------------------------------------------------------------------
// 関数
// ------------------------------------------------------------------

// スレーブの初期化
// 戻り値: 成功 = ファイルポインタ, 失敗 = NULL
FILE *i2c_slave_init(
	const i2c_addr7_t addr,     // アドレス
	const bool        broadcast // 一斉呼び出し許可
	);

// スレーブ受信
// 戻り値: 成功 = true, 失敗 = false
bool i2c_slave_receive();
	
bool i2c_slave_receive_ex(
	bool *const broadcast // 一斉呼び出しかどうか (不要な場合は NULL)
	);

// I2C スレーブ送信
// 戻り値: 成功 = true, 失敗 = false
bool i2c_slave_send(void);


// ------------------------------------------------------------------
// ■ 内部変数
// ------------------------------------------------------------------

// バスエラー
static volatile bool i2c_slave_bus_error;

// ファイルポインタ
static volatile FILE *i2c_slave_fp;

// 受信バッファ
static volatile uint8_t i2c_slave_receive_buffer[KVR_I2C_PACKET_SIZE + 1]; // バッファ (+1 はデータ長)
static volatile uint8_t i2c_slave_receive_buffer_position;                 // 現在位置
static volatile uint8_t i2c_slave_receive_buffer_length;                   // 大きさ
static volatile bool    i2c_slave_receive_buffer_writable;                 // 書き込み可
static volatile bool    i2c_slave_receive_broadcast;                       // 一斉呼び出しかどうか

// 送信バッファ
static volatile uint8_t i2c_slave_send_buffer[KVR_I2C_PACKET_SIZE]; // バッファ
static volatile uint8_t i2c_slave_send_buffer_position;             // 位置
static volatile uint8_t i2c_slave_send_buffer_length;               // 大きさ
static volatile bool    i2c_slave_send_buffer_writable;             // 書き込み可


// ------------------------------------------------------------------
// ■ 内部関数
// ------------------------------------------------------------------

// バッファから一文字入力
// (fdevopen で使用する getc)
static int i2c_slave_getc(FILE *fp){
	char c;
	
	// バッファの末尾に到達したか、ヌル文字な場合
	if(
		i2c_slave_receive_buffer[i2c_slave_receive_buffer_position] == '\0' ||
		i2c_slave_receive_buffer_position >= i2c_slave_receive_buffer_length
		)
	{
		return _FDEV_EOF;
	}
	
	// 戻り値を退避
	c = i2c_slave_receive_buffer[i2c_slave_receive_buffer_position];
	
	// バッファ位置を進める
	++i2c_slave_receive_buffer_position;
	
	return c;
}

// バッファへ一文字出力
// (fdevopen で使用する putc)
static int i2c_slave_putc(char c, FILE *fp){
	
	if(i2c_slave_send_buffer_position >= KVR_I2C_PACKET_SIZE){
		return _FDEV_EOF;
	}
	
	// バッファに保存
	i2c_slave_send_buffer[i2c_slave_send_buffer_position] = c;
	
	// バッファ位置を進める
	++i2c_slave_send_buffer_position;
	
	// 出力を返す
	return c;
}


// ------------------------------------------------------------------

int i2c_slave_getchar(void){
	return i2c_slave_getc(NULL);
}

int i2c_slave_scanf(const char *format, ...){
	va_list arg;
	int ret;

	va_start(arg, format);

	ret = vfscanf((FILE*)i2c_slave_fp, format, arg);

	va_end(arg);

	return ret;
}

char *i2c_slave_gets(char *str, const uint8_t len){
	return fgets(str, len, (FILE*)i2c_slave_fp);
}

size_t i2c_slave_read(void *buf, size_t size, size_t n){
	return fread(buf, size, n, (FILE*)i2c_slave_fp);
}

int i2c_slave_printf(const char *format, ...){
	va_list arg;
	int ret;

	va_start(arg, format);

	ret = vfprintf((FILE*)i2c_slave_fp, format, arg);

	va_end(arg);

	return ret;
}

void i2c_slave_write_uint8(uint8_t data){
	i2c_slave_send_buffer[i2c_slave_send_buffer_position++] = data;
}

void i2c_slave_write_uint16(uint16_t data){
	i2c_common_write_uint16(i2c_slave_write_uint8, data);
}

void i2c_slave_write_uint32(uint32_t data){
	i2c_common_write_uint32(i2c_slave_write_uint8, data);
}

void i2c_slave_write_uint64(uint64_t data){
	i2c_common_write_uint64(i2c_slave_write_uint8, data);
}

void i2c_slave_write_char(char data){
	i2c_slave_write_uint8(data);
}

void i2c_slave_write_short(short data){
	i2c_common_write_short(i2c_slave_write_uint8, data);
}

void i2c_slave_write_int(int data){
	i2c_common_write_int(i2c_slave_write_uint8, data);
}

void i2c_slave_write_long(long data){
	i2c_common_write_long(i2c_slave_write_uint8, data);
}

void i2c_slave_write_longlong(long long data){
	i2c_common_write_longlong(i2c_slave_write_uint8, data);
}

uint8_t i2c_slave_read_uint8(void){
	return i2c_slave_receive_buffer[i2c_slave_receive_buffer_position++];
}

uint16_t i2c_slave_read_uint16(void){
	return i2c_common_read_uint16(i2c_slave_read_uint8);
}

uint32_t i2c_slave_read_uint32(void){
	return i2c_common_read_uint32(i2c_slave_read_uint8);
}

uint64_t i2c_slave_read_uint64(void){
	return i2c_common_read_uint64(i2c_slave_read_uint8);
}

char i2c_slave_read_char(void){
	return i2c_slave_read_uint8();
}

short i2c_slave_read_short(void){
	return i2c_common_read_short(i2c_slave_read_uint8);
}

int i2c_slave_read_int(void){
	return i2c_common_read_int(i2c_slave_read_uint8);
}

long i2c_slave_read_long(void){
	return i2c_common_read_long(i2c_slave_read_uint8);
}

long long i2c_slave_read_longlong(void){
	return i2c_common_read_longlong(i2c_slave_read_uint8);
}

// I2C スレーブ初期化
FILE *i2c_slave_init(
	const i2c_addr7_t addr,     // アドレス
	const bool        broadcast // 一斉呼び出し許可
	)
{
	// 変数初期化
	i2c_slave_receive_buffer_position = 0;     // バッファ位置
	i2c_slave_receive_buffer_length   = 0;     // バッファの大きさ
	i2c_slave_receive_broadcast       = false; // 一斉呼び出しかどうか
	i2c_slave_receive_buffer_writable = true;  // バッファに書き込めるか
	
	i2c_slave_send_buffer_position    = 0;
	i2c_slave_send_buffer_length      = 0;
	i2c_slave_send_buffer_writable    = true;
	
	// スレーブアドレス設定
	TWAR = addr << 1;
	
	// 一斉呼び出し許可
	if(broadcast){
		TWAR |= _BV(TWGCE);
	}
	
	// スレーブ初期化
	// TWEA = 1, TWSTA = 0, TWSTO = 0, TWEN = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWINT) |  _BV(TWEA) | _BV(TWEN);
	
	// ファイルポインタを作成
	i2c_slave_fp = fdevopen(i2c_slave_putc, i2c_slave_getc);
	
	// 割り込み許可
	TWCR |= _BV(TWIE);
	sei();
	
	// ファイルポインタを返す
	return (FILE*)i2c_slave_fp;
}

// I2C スレーブ受信
// 戻り値: 成功 = true, 失敗 = false
bool i2c_slave_receive(void){
	return i2c_slave_receive_ex(NULL);
}

bool i2c_slave_receive_ex(
	bool *const broadcast // 一斉呼び出しかどうか
	)
{
	// バッファを書き込み可状態にする (受信する)
	i2c_slave_receive_buffer_writable = true;
	i2c_slave_receive_buffer_length   = 0;
	i2c_slave_receive_buffer_position = 0;
	
	// バスエラーを検出する為に初期化
	i2c_slave_bus_error = false;
	
	// バッファが書き込み不可状態 (読み込み可状態) になるまで待つ
	while(i2c_slave_receive_buffer_writable){
		if(i2c_slave_bus_error){ // バスエラー
			
			// バスエラーをクリア
			i2c_slave_bus_error = false;
			
			// バッファを書き込み不可に設定する (受信しない)
			i2c_slave_receive_buffer_writable = false;
			
			return false;
		}
	}
	
	// バッファの大きさを保存
	i2c_slave_receive_buffer_length = i2c_slave_receive_buffer_position;
	
	// バッファ位置を初期化
	i2c_slave_receive_buffer_position = 1;
	
	clearerr((FILE*)i2c_slave_fp);
	
	// 一斉呼び出しだったか
	if(broadcast != NULL){
		*broadcast = i2c_slave_receive_broadcast;
	}
	
	return true; // 成功
}

// I2C スレーブ送信
// 戻り値: 成功 = true, 失敗 = false
bool i2c_slave_send(void){
	// バッファを書き込み不可状態 (送信状態) にする
	i2c_slave_send_buffer_writable = false;
	
	// バッファの大きさを保存
	i2c_slave_send_buffer_length = i2c_slave_send_buffer_position;
	
	// バッファ位置を初期化
	i2c_slave_send_buffer_position = 0;
	
	// バスエラーを検出するために初期化
	i2c_slave_bus_error = false;
	
	// バッファが書き込み可能状態になるまで待つ (送信終了を待機)
	while(!i2c_slave_send_buffer_writable){
		if(i2c_slave_bus_error){
			i2c_slave_bus_error = false; // バスエラーをクリア
			return false; // 失敗
		}
	}
	
	// バッファの大きさを初期化
	i2c_slave_send_buffer_length = 0;
	
	// バッファの位置を初期化
	i2c_slave_send_buffer_position = 0;

	// エラーをクリア
	clearerror(i2c_slave_fp);
	
	return true; // 成功
}

// ------------------------------------------------------------------
// 割り込み
// ------------------------------------------------------------------

ISR(TWI_vect){
//	printf("TW_STATUS = 0x%X\n", TW_STATUS);

	switch(TW_STATUS){

	// 受信要求
	case TW_SR_SLA_ACK: // 0x60

	// 一斉呼び出し 受信
	case TW_SR_GCALL_ACK: // 0x70
		// printf("%s\n", TW_STATUS == TW_SR_SLA_ACK ? "TW_SR_SLA_ACK" : "TW_SR_GCALL_ACK");
		
		// 受信バッファに書き込み可能な場合
		if(i2c_slave_receive_buffer_writable){
		
			// 一斉呼び出しかどうか保存する
			i2c_slave_receive_broadcast = (TW_STATUS == TW_SR_GCALL_ACK);
			
			// データ受信 ACK 応答
			// TWSTO = 0, TWINT = 1, TWEA = 1
			TWCR &= ~_BV(TWSTO);
			TWCR |=  _BV(TWINT) | _BV(TWEA);
		}
		
		// 受信バッファに書き込み不可な場合
		else {
			// データ受信 NACK 応答
			// TWSTO = 0, TWINT = 1, TWEA = 0
			TWCR &= ~_BV(TWSTO) & ~ _BV(TWEA);
			TWCR |=  _BV(TWINT);
		}

		break;

	// データ受信 ACK
	case TW_SR_DATA_ACK: // 0x80

	// 一斉呼び出しのデータバイド受信 ACK 応答
	case TW_SR_GCALL_DATA_ACK: // 0x90
	//	printf("%s\n", TW_STATUS == TW_SR_DATA_ACK ? "TW_SR_DATA_ACK" : "TW_SR_GCALL_DATA_ACK");
		
		i2c_slave_receive_buffer[i2c_slave_receive_buffer_position++] = TWDR;
		
		// データ受信 ACK 応答
		// TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) | _BV(TWEA);

		break;
	
	// 自宛データバイト受信 NACK 応答
	case TW_SR_DATA_NACK: // 0x88
	
	case TW_SR_GCALL_DATA_NACK: // 0x98
	//	printf("TW_SR_DATA_NACK\n");		
		
		// 未指定スレーブ動作へ移行、応答対応
		// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);
		
		break;
	
	// 送信要求
	case TW_ST_SLA_ACK: // 0xA8
//		printf("TW_ST_SLA_ACK\n");
		
		/*
		printf(
			"> writable = %d, length = %d\n",
			i2c_slave_send_buffer_writable,
			i2c_slave_send_buffer_length
		);*/
		
		// 送信するデータが存在する
		if(
			!i2c_slave_send_buffer_writable  &&
			i2c_slave_send_buffer_length > 0
			)
		{
			// データ長を送信
			TWDR = i2c_slave_send_buffer_length;
			
			// ACK 受信予定
			// TWSTO = 0, TWINT = 1, TWEA = 1
			TWCR &= ~_BV(TWSTO);
			TWCR |=  _BV(TWINT) | _BV(TWEA);
		}
		
		else {
			// データ長 = 0
			TWDR = 0;
			
			// NACK 受信予定
			// TWSTO = 0, TWINT = 1, TWEA = 0
			TWCR &= ~_BV(TWSTO) & ~_BV(TWEA);
			TWCR |=  _BV(TWINT);
		}
		
		break;
	
	// データバイト送信 NACK 受信
	case TW_ST_DATA_NACK: // 0xC0
//		printf("TW_ST_DATA_NACK\n");

		// 送信するデータが存在しない為、何もしない		
		TWDR = 0x00;

		// NACK 受信予定
		// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);

		break;
	
	// データバイト送信 ACK 受信
	case TW_ST_DATA_ACK: // 0xB8
	//	printf("TW_ST_DATA_ACK\n");
		
		/*
		printf(
			"> length = %d, position = %d\n",
			i2c_slave_send_buffer_length,
			i2c_slave_send_buffer_position
			);
		*/
		
		// 送信するデータが存在する
		if(
			!i2c_slave_send_buffer_writable  &&
			i2c_slave_send_buffer_length > 0 &&
			i2c_slave_send_buffer_position <= i2c_slave_send_buffer_length
			)
		{
			// データを送信
			TWDR = i2c_slave_send_buffer[i2c_slave_send_buffer_position];
			
			// バッファ位置を更新
			++i2c_slave_send_buffer_position;
			
			// 最終バイトの処理
			if(i2c_slave_send_buffer_position >= i2c_slave_send_buffer_length){
				// NACK 受信予定
				// TWSTO = 0, TWINT = 1, TWEA = 0
				TWCR &= ~_BV(TWSTO) & ~_BV(TWEA);
				TWCR |=  _BV(TWINT);
			}
			
			else {
				// ACK 受信予定
				// TWSTO = 0, TWINT = 1, TWEA = 1
				TWCR &= ~_BV(TWSTO);
				TWCR |=  _BV(TWINT) | _BV(TWEA);
			}
		}
		
		// 送信するデータが存在しない場合
		else {
			// ダミーデータ送信
			TWDR = 0x00;
			
			// NACK 受信予定
			// TWSTA = X, TWSTO = 0, TWINT = 1, TWEA = 0
			TWCR &= ~_BV(TWSTO) & ~_BV(TWEA);
			TWCR |=  _BV(TWINT);
		}
		
		break;
	
	// 最終データバイト送信 ACK 受信
	case TW_ST_LAST_DATA: // 0xC8
		// 未指定スレーブ動作へ移行, 応答対応
		// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);
		
		// データを送信している場合
		if(!i2c_slave_send_buffer_writable){
			// 書き込み可に設定
			i2c_slave_send_buffer_writable = true;
		}
		
//		printf("TW_ST_LAST_DATA\n");
		
		break;
	
	// 不正な開始条件 / 停止条件でのバス異常
	case TW_BUS_ERROR: // 0x00
		
		// バス異常から回復する
		// TWSTA = 0, TWSTO = 1, TWINT = 1
		TWCR &= ~_BV(TWSTA);
		TWCR |=  _BV(TWSTO) | _BV(TWINT);
		
		i2c_slave_bus_error = true;
		
//		printf("TW_BUS_ERROR\n");
		
		break;
	
	// 停止	
	case TW_SR_STOP: // 0xA0
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);
		
		// データが送られているか
		if(i2c_slave_receive_buffer_writable && i2c_slave_receive_buffer_position > 0){			
			// 書き込み不可に設定
			i2c_slave_receive_buffer_writable = false;
		}
		
		// データを送信している場合
		if(!i2c_slave_send_buffer_writable && i2c_slave_send_buffer_position > 0){
			// 書き込み可に設定
			i2c_slave_send_buffer_writable = true;
		}
		
//		printf("TW_SR_STOP\n");

		break;
	
	// 未定義
	default:
//		printf("UNKOWN STATUS: %x\n", TW_STATUS);
//		while(1);
	}
}

#endif
