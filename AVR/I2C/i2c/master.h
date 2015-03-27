// ------------------------------------------------------------------
// kvr / KUT AVR Library
// I2C Master Library / "kvr/i2c/master.h" / v1.0
// Author: KUT RobotClub, MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   初版
//
// ------------------------------------------------------------------

#ifndef __KVR_I2C_MASTER__
#define __KVR_I2C_MASTER__

#define KVR_I2C_VERSION 10000UL // version 1.00.00

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

#include "def.h"
#include "common.h"


// ------------------------------------------------------------------
// ■ 関数
// ------------------------------------------------------------------

// I2C マスター 初期化
// 戻り値: 成功 = ファイルポインタ, 失敗 = NULL
FILE *i2c_master_init(
	const uint32_t f // 周波数
	);

// I2C マスター 送信
// 戻り値: 成功 = true, 失敗 = false
bool i2c_master_send(
	const i2c_addr7_t addr // アドレス
	);

// I2C マスター 受信
// 戻り値: 成功 = true, 失敗 = false
bool i2c_master_receive(
	const i2c_addr7_t addr // アドレス
	);

// I2C マスター 標準入出力関数
int i2c_master_printf(const char *format, ...);
int i2c_master_scanf(const char *format, ...);


// ------------------------------------------------------------------
// ■ 内部変数
// ------------------------------------------------------------------

// ファイルポインタ
static FILE *i2c_master_fp;

// 送信バッファ
static volatile uint8_t i2c_master_send_buffer[KVR_I2C_PACKET_SIZE];
static volatile uint8_t i2c_master_send_buffer_position;

// 受信バッファ
static volatile uint8_t i2c_master_receive_buffer[KVR_I2C_PACKET_SIZE];
static volatile uint8_t i2c_master_receive_buffer_length;
static volatile uint8_t i2c_master_receive_buffer_position;


// ------------------------------------------------------------------
// ■ 内部関数
// ------------------------------------------------------------------

// I2C マスター 開始条件送出
static bool i2c_master_start(void);

// I2C マスター 停止条件送出
static void i2c_master_stop(void);

// I2C マスター 複数バイト送信
static bool i2c_master_send_bytes(
	const i2c_addr7_t        addr, // アドレス
	const uint8_t            size, // データサイズ
	const void        *const buff  // 送信データ
	);

// I2C マスター 複数バイト受信
static bool i2c_master_receive_bytes(
	const    i2c_addr7_t addr,        // アドレス
	const    uint8_t     buff_size,   // バッファサイズ
	void    *const       buff,        // 受信データ
	uint8_t *const       receive_size // 受信データサイズ
	);

// I2C マスター スレーブアドレス指定
static bool i2c_master_set_slave_address(
	const i2c_addr7_t addr, // アドレス
	const char        dir   // 送信 = W, 受信 = R
	);

// I2C マスター 1バイト送信
static bool i2c_master_send_data(
	const uint8_t data // データ
	);

// I2C マスター 初期バイト受信
static bool i2c_master_receive_first_data(
	uint8_t * const data
	);

// I2C マスター 1バイト受信
static bool i2c_master_receive_data(
	uint8_t * const data
	);

// I2C 割り込み待ち関数 (TWINT = 0 の間ループ)
static bool i2c_twint_wait(void){
	TWCR |= _BV(TWINT);
	
	while(!(TWCR & _BV(TWINT))){
	//	printf("TW_STATUS = 0x%X\n", TW_STATUS);
		
		if(TW_STATUS == TW_BUS_ERROR){
			
			// 停止条件を送出せずバスを開放
			// TWSTA = 0, TWSTO = 1, TWINT = 1, TWEA = X
			TWCR &= ~_BV(TWSTA);
			TWCR |=  _BV(TWINT) | _BV(TWSTO);
			
			return false; // 失敗
		}
	}
	
	return true; // 成功
}


// fdevopen 関数用 putc, getc 関数
static int i2c_master_putc(char c, FILE *fp);
static int i2c_master_getc(FILE *fp);

static int i2c_master_putc(char c, FILE *fp){
	
	// 送信バッファ以上のデータの送信
	if(i2c_master_send_buffer_position >= KVR_I2C_PACKET_SIZE){
		return _FDEV_ERR; // エラー
	}
	
	return i2c_master_send_buffer[i2c_master_send_buffer_position++] = c;
}

static int i2c_master_getc(FILE *fp){
	uint8_t data;
	
	// 受信バッファ以上のデータ取得
	if(i2c_master_receive_buffer_position >= i2c_master_receive_buffer_length){
		return _FDEV_ERR; // エラー
	}
	
	// データを取得
	data = i2c_master_receive_buffer[i2c_master_receive_buffer_position];
	
	// バッファ位置を移動
	++i2c_master_receive_buffer_position;
	
	return data;
}

// ------------------------------------------------------------------

int i2c_master_printf(const char *format, ...){
	va_list arg;
	int ret;
	
	va_start(arg, format);
	
	ret = vfprintf(i2c_master_fp, format, arg);
	
	va_end(arg);
	
	return ret;
}


int i2c_master_scanf(const char * format, ...){
	va_list arg;
	int ret;
	
	va_start(arg, format);
	
	ret = vfscanf(i2c_master_fp, format, arg);
	
	va_end(arg);
	
	return ret;
}

void i2c_master_write_uint8(const uint8_t data){
	i2c_master_send_buffer[i2c_master_send_buffer_position++] = data;
}

void i2c_master_write_int8(const int8_t data){
	i2c_master_write_uint8(data);
}

void i2c_master_write_uint16(const uint16_t data){
	i2c_common_write_uint16(i2c_master_write_uint8, data);
}

void i2c_master_write_int16(const int16_t data){
	i2c_common_write_int16(i2c_master_write_uint8, data);
}

void i2c_master_write_uint32(const uint32_t data){
	i2c_common_write_uint32(i2c_master_write_uint8, data);
}

void i2c_master_write_int32(const int32_t data){
	i2c_common_write_int32(i2c_master_write_uint8, data);
}

void i2c_master_write_uint64(const uint64_t data){
	i2c_common_write_uint64(i2c_master_write_uint8, data);
}

void i2c_master_write_int64(const int64_t data){
	i2c_common_write_int64(i2c_master_write_uint8, data);
}

void i2c_master_write_int(const int data){
	i2c_common_write_int(i2c_master_write_uint8, data);
}

void i2c_master_write_long(const long data){
	i2c_common_write_long(i2c_master_write_uint8, data);
}

void i2c_master_write_longlong(const long long data){
	i2c_common_write_longlong(i2c_master_write_uint8, data);
}

uint8_t i2c_master_read_uint8(void){
	return i2c_master_receive_buffer[i2c_master_receive_buffer_position++];
}

int8_t i2c_master_read_int8(void){
	return i2c_master_read_uint8();
}

uint16_t i2c_master_read_uint16(void){
	return i2c_common_read_uint16(i2c_master_read_uint8);
}

int16_t i2c_master_read_int16(void){
	return i2c_common_read_int16(i2c_master_read_uint8);
}

uint32_t i2c_master_read_uint32(void){
	return i2c_common_read_uint32(i2c_master_read_uint8);
}

int32_t i2c_master_read_int32(void){
	return i2c_common_read_int32(i2c_master_read_uint8);
}

uint64_t i2c_master_read_uint64(void){
	return i2c_common_read_uint64(i2c_master_read_uint8);
}

int64_t i2c_master_read_int64(void){
	return i2c_common_read_int64(i2c_master_read_uint8);
}

// int = 16 bit, Big Endian
int i2c_master_read_int(void){
	return i2c_common_read_int(i2c_master_read_uint8);
}

// long = 32 bit, Big Endian
long i2c_master_read_long(void){
	return i2c_common_read_long(i2c_master_read_uint8);
}

// long long = 32 bit, Big Endian
long long i2c_master_read_longlong(void){
return i2c_common_read_longlong(i2c_master_read_uint8);
}

// ------------------------------------------------------------------

// I2C マスター 初期化
FILE *i2c_master_init(const uint32_t f){
	volatile const int PRESCALER[] = { 1, 4, 16, 64 };
	uint8_t  prescaler;
	uint32_t bitrate;
	
	for(prescaler = 0; prescaler <= 0b11; ++prescaler){
		bitrate = (F_CPU - 16 * f) / (2 * f * PRESCALER[prescaler]);
		
		if(bitrate <= 0xff){
			break;
		}
	}
	
	// 前置分周値決定不能.
	if(prescaler > 0b11){
		return NULL; // 失敗
	}
	
	// 前置分周値 = 1
	TWSR = (TWSR & 0b11111100) | prescaler;
	
	// TWI 分周
	// SCL 周波数 = CPU 周波数 / (16 + 2 * TWBR * 前置分周値)
	// TWBR       = CPU 周波数 / (2 * SCL 周波数) - 8
	TWBR = bitrate;
	
	// TWI 許可
	TWCR |= _BV(TWEN);
	
	// ファイルポインタを取得
	i2c_master_fp = fdevopen(i2c_master_putc, i2c_master_getc);
	
	// バッファ位置を初期化
	i2c_master_send_buffer_position    = 0;
	i2c_master_receive_buffer_length   = 0;
	i2c_master_receive_buffer_position = 0;
	
	return i2c_master_fp; // 成功
}

// I2C マスター 送信
bool i2c_master_send(
	const i2c_addr7_t addr
	)
{
//	printf("position = %d\n", i2c_master_send_buffer_position);
	
	// 送信するデータが存在する場合
	if(i2c_master_send_buffer_position > 0){
		bool ret;
		
		ret = i2c_master_send_bytes(addr, i2c_master_send_buffer_position, (void*)i2c_master_send_buffer);
		
		// バッファサイズをクリア
		i2c_master_send_buffer_position = 0;
		
		return ret;
	}
	
	return false; // 失敗
}

// I2C マスター 受信
bool i2c_master_receive(
	const i2c_addr7_t addr
	)
{
	bool ret;
	
	// データ受信を試みる
	ret = i2c_master_receive_bytes(
		addr,
		KVR_I2C_PACKET_SIZE,
		(uint8_t*)i2c_master_receive_buffer,
		(uint8_t*)(&i2c_master_receive_buffer_length)
		);
	
	// 通信失敗 or データ長 = 0
	if(!ret || i2c_master_receive_buffer_length == 0){
		return false; // 失敗
	}
	
	// バッファ位置を初期化
	i2c_master_receive_buffer_position = 0;
	
	return true; // 成功
}

// I2C マスター 複数バイト送信
bool i2c_master_send_bytes(
	const i2c_addr7_t        addr, // アドレス
	const uint8_t            size, // データサイズ
	const void        *const buff  // データ
	)
{
	uint8_t i;
	
	// I2C マスター 開始
	if(!i2c_master_start()){
		return false;
	}
	
	// I2C マスター 送信アドレス指定
	if(i2c_master_set_slave_address(addr, 'W')){
		i2c_master_send_data(size);
		
		for(i = 0; i < size; ++i){
			i2c_master_send_data(((const char*)buff)[i]);
		}
		
		i2c_master_stop();
		
		return true; // 成功
	}
	
	else {
		i2c_master_stop();
		return false;
	}
}

// I2C マスター 複数バイト受信
bool i2c_master_receive_bytes(
	const    i2c_addr7_t addr,        // アドレス
	const    uint8_t     buff_size,   // バッファサイズ
	void    *const       buff,        // 受信データ
	uint8_t *const       receive_size // 受信データサイズ
	)
{
	uint8_t i;
	uint8_t len;
	
	// I2C マスター 開始条件
	if(!i2c_master_start()){
		return false; // 失敗
	}
	
	// I2C マスター スレーブアドレス指定
	if(!i2c_master_set_slave_address(addr, 'R')){
		return false; // 失敗
	}
	
	// 初期バイト読み込み
	if(!i2c_master_receive_first_data(receive_size)){
		i2c_master_stop();
		return false; // 失敗
	}
	
//	usart_printf(0, "TW_STATUS = 0x%02X\n", TW_STATUS);
//	usart_printf(0, "TWDR = %d (first byte)\n", *receive_size);
	
	// スレーブ送信のデータ無し
	if(*receive_size == 0){
		i2c_master_stop();
		return false;
	}
	
	// 読み込むバイト数 = min(receive_size, buff_size)
	len = *receive_size < buff_size ? *receive_size : buff_size;
	
	// バイト数分読み込む
	for(i = 0; i < len; ++i){
		if(!i2c_master_receive_data((uint8_t *const)buff + i)){
			i2c_master_stop();
			return false;
		}
		
//		usart_printf(0, "> buff[%d] = %d\n", i, *((char*)buff + i));
	}
	
	i2c_master_stop();
	
	return true;
}


//I2C マスター 開始
bool i2c_master_start(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!( TWCR & (1<<TWINT)))
	{
		if(TW_STATUS == 0x00)
		{
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
			return false;
		}
	}
	
	return true;
}

// I2C マスター 終了
void i2c_master_stop(void){
	TWCR |= _BV(TWINT) | _BV(TWSTO); // 終了
	
	while(TWCR & _BV(TWSTO)){
		if(TW_STATUS == TW_BUS_ERROR){
			_delay_us(10);
			return;
		}
	}
	
	while(TW_STATUS != 0xF8){
		if(TW_STATUS == TW_BUS_ERROR){
			_delay_us(10);
			return;
		}
	}
	
//	printf("TW_STATUS = 0x%02X\n", TW_STATUS);
	
	_delay_us(10);					// I2C終了条件送信待ち時間 
}

// I2C マスター アドレス指定
bool i2c_master_set_slave_address(
	const i2c_addr7_t addr,
	const char        dir
	)
{
	
	while(TW_STATUS != TW_START){
		if(TW_STATUS == 0x00)
		{
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
			return false;
		}
	}
	
	if(dir == 'W'){ // マスター → スレーブ
		TWDR = addr <<1;
	}
	
	else if(dir == 'R'){ // スレーブ → マスター
		TWDR = (addr << 1) | 0x01;
	}
	
	else {
		return false; // 失敗
	}
	
	// データ送信/受信 ACK/NACK 応答
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = X
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	
	if(!i2c_twint_wait()){
		return false;
	}
	
//	printf("SLA+%c: 0x%X\n", dir, TW_STATUS);
	
	if(dir == 'W' && TW_STATUS == TW_MT_SLA_ACK){
		return true;
	}
	
	if(dir == 'R' && TW_STATUS == TW_MR_SLA_ACK){
		return true;
	}
	
	// NACK 応答, その他
	return false;
}


bool i2c_master_send_data(
	const uint8_t data
	)
{
	// 送信
	TWDR = data;
	
	// I2C マスター 割り込み待ち
	if(!i2c_twint_wait()){
		return false;
	}
	
	// 送信結果
	if(TW_STATUS == TW_MT_DATA_ACK){
		return true; // 成功
	}
	
	return false; // 失敗
}

bool i2c_master_receive_first_data(
	uint8_t * const data
	)
{
//	printf("TW_STATUS = 0x%X\n", TW_STATUS);
	
	// SLA+R 送信 ACK 受信 (0x40)
	if(TW_STATUS != TW_MR_SLA_ACK){
		return false;
	}
	
	// データ受信 ACK 応答
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWEA);
	
	// 処理待ち
	if(!i2c_twint_wait()){
		return false;
	}
	
//	printf("TW_STATUS = 0x%2X\n", TW_STATUS);
	
	// データバイト受信 ACK 応答
	if(TW_STATUS != TW_MR_DATA_ACK){
		return false;
	}
	
	// データを受信
	*data = TWDR;
	
//	printf("TW_STATUS = 0x%2X\n", TW_STATUS);
//	printf("TWDR = 0x%2X\n", (int)(*data));
	
	// データ受信 ACK 応答
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWEA);
	
	// 割り込み待ち
	if(!i2c_twint_wait()){
		return false;
	}
	
	// データバイト受信 ACK 応答
	if(TW_STATUS != TW_MR_DATA_ACK){ // 0x50
		return false;
	}
	
	return true;
}


bool i2c_master_receive_data(
	uint8_t * const data
	)
{
	// データバイト受信 ACK 応答
	if(TW_STATUS != TW_MR_DATA_ACK){ // 0x50
		return false;
	}
	
	// データを受信
	*data = TWDR;
	
//	printf("TW_STATUS = 0x%02X\n", TW_STATUS);
//	printf("TWDR = 0x%02X\n", (int)(*data));
	
	// データ受信 ACK 応答
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWEA);
	
	return i2c_twint_wait();
}

#endif
