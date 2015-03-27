// ------------------------------------------------------------------
// kvr / KUT AVR Library
// I2C Master Library / "kvr/i2c/master.h" / v1.0
// Author: KUT RobotClub, MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   ����
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
// �� �֐�
// ------------------------------------------------------------------

// I2C �}�X�^�[ ������
// �߂�l: ���� = �t�@�C���|�C���^, ���s = NULL
FILE *i2c_master_init(
	const uint32_t f // ���g��
	);

// I2C �}�X�^�[ ���M
// �߂�l: ���� = true, ���s = false
bool i2c_master_send(
	const i2c_addr7_t addr // �A�h���X
	);

// I2C �}�X�^�[ ��M
// �߂�l: ���� = true, ���s = false
bool i2c_master_receive(
	const i2c_addr7_t addr // �A�h���X
	);

// I2C �}�X�^�[ �W�����o�͊֐�
int i2c_master_printf(const char *format, ...);
int i2c_master_scanf(const char *format, ...);


// ------------------------------------------------------------------
// �� �����ϐ�
// ------------------------------------------------------------------

// �t�@�C���|�C���^
static FILE *i2c_master_fp;

// ���M�o�b�t�@
static volatile uint8_t i2c_master_send_buffer[KVR_I2C_PACKET_SIZE];
static volatile uint8_t i2c_master_send_buffer_position;

// ��M�o�b�t�@
static volatile uint8_t i2c_master_receive_buffer[KVR_I2C_PACKET_SIZE];
static volatile uint8_t i2c_master_receive_buffer_length;
static volatile uint8_t i2c_master_receive_buffer_position;


// ------------------------------------------------------------------
// �� �����֐�
// ------------------------------------------------------------------

// I2C �}�X�^�[ �J�n�������o
static bool i2c_master_start(void);

// I2C �}�X�^�[ ��~�������o
static void i2c_master_stop(void);

// I2C �}�X�^�[ �����o�C�g���M
static bool i2c_master_send_bytes(
	const i2c_addr7_t        addr, // �A�h���X
	const uint8_t            size, // �f�[�^�T�C�Y
	const void        *const buff  // ���M�f�[�^
	);

// I2C �}�X�^�[ �����o�C�g��M
static bool i2c_master_receive_bytes(
	const    i2c_addr7_t addr,        // �A�h���X
	const    uint8_t     buff_size,   // �o�b�t�@�T�C�Y
	void    *const       buff,        // ��M�f�[�^
	uint8_t *const       receive_size // ��M�f�[�^�T�C�Y
	);

// I2C �}�X�^�[ �X���[�u�A�h���X�w��
static bool i2c_master_set_slave_address(
	const i2c_addr7_t addr, // �A�h���X
	const char        dir   // ���M = W, ��M = R
	);

// I2C �}�X�^�[ 1�o�C�g���M
static bool i2c_master_send_data(
	const uint8_t data // �f�[�^
	);

// I2C �}�X�^�[ �����o�C�g��M
static bool i2c_master_receive_first_data(
	uint8_t * const data
	);

// I2C �}�X�^�[ 1�o�C�g��M
static bool i2c_master_receive_data(
	uint8_t * const data
	);

// I2C ���荞�ݑ҂��֐� (TWINT = 0 �̊ԃ��[�v)
static bool i2c_twint_wait(void){
	TWCR |= _BV(TWINT);
	
	while(!(TWCR & _BV(TWINT))){
	//	printf("TW_STATUS = 0x%X\n", TW_STATUS);
		
		if(TW_STATUS == TW_BUS_ERROR){
			
			// ��~�����𑗏o�����o�X���J��
			// TWSTA = 0, TWSTO = 1, TWINT = 1, TWEA = X
			TWCR &= ~_BV(TWSTA);
			TWCR |=  _BV(TWINT) | _BV(TWSTO);
			
			return false; // ���s
		}
	}
	
	return true; // ����
}


// fdevopen �֐��p putc, getc �֐�
static int i2c_master_putc(char c, FILE *fp);
static int i2c_master_getc(FILE *fp);

static int i2c_master_putc(char c, FILE *fp){
	
	// ���M�o�b�t�@�ȏ�̃f�[�^�̑��M
	if(i2c_master_send_buffer_position >= KVR_I2C_PACKET_SIZE){
		return _FDEV_ERR; // �G���[
	}
	
	return i2c_master_send_buffer[i2c_master_send_buffer_position++] = c;
}

static int i2c_master_getc(FILE *fp){
	uint8_t data;
	
	// ��M�o�b�t�@�ȏ�̃f�[�^�擾
	if(i2c_master_receive_buffer_position >= i2c_master_receive_buffer_length){
		return _FDEV_ERR; // �G���[
	}
	
	// �f�[�^���擾
	data = i2c_master_receive_buffer[i2c_master_receive_buffer_position];
	
	// �o�b�t�@�ʒu���ړ�
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

// I2C �}�X�^�[ ������
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
	
	// �O�u�����l����s�\.
	if(prescaler > 0b11){
		return NULL; // ���s
	}
	
	// �O�u�����l = 1
	TWSR = (TWSR & 0b11111100) | prescaler;
	
	// TWI ����
	// SCL ���g�� = CPU ���g�� / (16 + 2 * TWBR * �O�u�����l)
	// TWBR       = CPU ���g�� / (2 * SCL ���g��) - 8
	TWBR = bitrate;
	
	// TWI ����
	TWCR |= _BV(TWEN);
	
	// �t�@�C���|�C���^���擾
	i2c_master_fp = fdevopen(i2c_master_putc, i2c_master_getc);
	
	// �o�b�t�@�ʒu��������
	i2c_master_send_buffer_position    = 0;
	i2c_master_receive_buffer_length   = 0;
	i2c_master_receive_buffer_position = 0;
	
	return i2c_master_fp; // ����
}

// I2C �}�X�^�[ ���M
bool i2c_master_send(
	const i2c_addr7_t addr
	)
{
//	printf("position = %d\n", i2c_master_send_buffer_position);
	
	// ���M����f�[�^�����݂���ꍇ
	if(i2c_master_send_buffer_position > 0){
		bool ret;
		
		ret = i2c_master_send_bytes(addr, i2c_master_send_buffer_position, (void*)i2c_master_send_buffer);
		
		// �o�b�t�@�T�C�Y���N���A
		i2c_master_send_buffer_position = 0;
		
		return ret;
	}
	
	return false; // ���s
}

// I2C �}�X�^�[ ��M
bool i2c_master_receive(
	const i2c_addr7_t addr
	)
{
	bool ret;
	
	// �f�[�^��M�����݂�
	ret = i2c_master_receive_bytes(
		addr,
		KVR_I2C_PACKET_SIZE,
		(uint8_t*)i2c_master_receive_buffer,
		(uint8_t*)(&i2c_master_receive_buffer_length)
		);
	
	// �ʐM���s or �f�[�^�� = 0
	if(!ret || i2c_master_receive_buffer_length == 0){
		return false; // ���s
	}
	
	// �o�b�t�@�ʒu��������
	i2c_master_receive_buffer_position = 0;
	
	return true; // ����
}

// I2C �}�X�^�[ �����o�C�g���M
bool i2c_master_send_bytes(
	const i2c_addr7_t        addr, // �A�h���X
	const uint8_t            size, // �f�[�^�T�C�Y
	const void        *const buff  // �f�[�^
	)
{
	uint8_t i;
	
	// I2C �}�X�^�[ �J�n
	if(!i2c_master_start()){
		return false;
	}
	
	// I2C �}�X�^�[ ���M�A�h���X�w��
	if(i2c_master_set_slave_address(addr, 'W')){
		i2c_master_send_data(size);
		
		for(i = 0; i < size; ++i){
			i2c_master_send_data(((const char*)buff)[i]);
		}
		
		i2c_master_stop();
		
		return true; // ����
	}
	
	else {
		i2c_master_stop();
		return false;
	}
}

// I2C �}�X�^�[ �����o�C�g��M
bool i2c_master_receive_bytes(
	const    i2c_addr7_t addr,        // �A�h���X
	const    uint8_t     buff_size,   // �o�b�t�@�T�C�Y
	void    *const       buff,        // ��M�f�[�^
	uint8_t *const       receive_size // ��M�f�[�^�T�C�Y
	)
{
	uint8_t i;
	uint8_t len;
	
	// I2C �}�X�^�[ �J�n����
	if(!i2c_master_start()){
		return false; // ���s
	}
	
	// I2C �}�X�^�[ �X���[�u�A�h���X�w��
	if(!i2c_master_set_slave_address(addr, 'R')){
		return false; // ���s
	}
	
	// �����o�C�g�ǂݍ���
	if(!i2c_master_receive_first_data(receive_size)){
		i2c_master_stop();
		return false; // ���s
	}
	
//	usart_printf(0, "TW_STATUS = 0x%02X\n", TW_STATUS);
//	usart_printf(0, "TWDR = %d (first byte)\n", *receive_size);
	
	// �X���[�u���M�̃f�[�^����
	if(*receive_size == 0){
		i2c_master_stop();
		return false;
	}
	
	// �ǂݍ��ރo�C�g�� = min(receive_size, buff_size)
	len = *receive_size < buff_size ? *receive_size : buff_size;
	
	// �o�C�g�����ǂݍ���
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


//I2C �}�X�^�[ �J�n
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

// I2C �}�X�^�[ �I��
void i2c_master_stop(void){
	TWCR |= _BV(TWINT) | _BV(TWSTO); // �I��
	
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
	
	_delay_us(10);					// I2C�I���������M�҂����� 
}

// I2C �}�X�^�[ �A�h���X�w��
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
	
	if(dir == 'W'){ // �}�X�^�[ �� �X���[�u
		TWDR = addr <<1;
	}
	
	else if(dir == 'R'){ // �X���[�u �� �}�X�^�[
		TWDR = (addr << 1) | 0x01;
	}
	
	else {
		return false; // ���s
	}
	
	// �f�[�^���M/��M ACK/NACK ����
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
	
	// NACK ����, ���̑�
	return false;
}


bool i2c_master_send_data(
	const uint8_t data
	)
{
	// ���M
	TWDR = data;
	
	// I2C �}�X�^�[ ���荞�ݑ҂�
	if(!i2c_twint_wait()){
		return false;
	}
	
	// ���M����
	if(TW_STATUS == TW_MT_DATA_ACK){
		return true; // ����
	}
	
	return false; // ���s
}

bool i2c_master_receive_first_data(
	uint8_t * const data
	)
{
//	printf("TW_STATUS = 0x%X\n", TW_STATUS);
	
	// SLA+R ���M ACK ��M (0x40)
	if(TW_STATUS != TW_MR_SLA_ACK){
		return false;
	}
	
	// �f�[�^��M ACK ����
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWEA);
	
	// �����҂�
	if(!i2c_twint_wait()){
		return false;
	}
	
//	printf("TW_STATUS = 0x%2X\n", TW_STATUS);
	
	// �f�[�^�o�C�g��M ACK ����
	if(TW_STATUS != TW_MR_DATA_ACK){
		return false;
	}
	
	// �f�[�^����M
	*data = TWDR;
	
//	printf("TW_STATUS = 0x%2X\n", TW_STATUS);
//	printf("TWDR = 0x%2X\n", (int)(*data));
	
	// �f�[�^��M ACK ����
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWEA);
	
	// ���荞�ݑ҂�
	if(!i2c_twint_wait()){
		return false;
	}
	
	// �f�[�^�o�C�g��M ACK ����
	if(TW_STATUS != TW_MR_DATA_ACK){ // 0x50
		return false;
	}
	
	return true;
}


bool i2c_master_receive_data(
	uint8_t * const data
	)
{
	// �f�[�^�o�C�g��M ACK ����
	if(TW_STATUS != TW_MR_DATA_ACK){ // 0x50
		return false;
	}
	
	// �f�[�^����M
	*data = TWDR;
	
//	printf("TW_STATUS = 0x%02X\n", TW_STATUS);
//	printf("TWDR = 0x%02X\n", (int)(*data));
	
	// �f�[�^��M ACK ����
	// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWEA);
	
	return i2c_twint_wait();
}

#endif
