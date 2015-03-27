// ------------------------------------------------------------------
// kvr / KUT AVR Library
// I2C Slave Library / "kvr/i2c/slave.h" / v1.0
// Author: KUT RobotClub, MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   ����
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
// �֐�
// ------------------------------------------------------------------

// �X���[�u�̏�����
// �߂�l: ���� = �t�@�C���|�C���^, ���s = NULL
FILE *i2c_slave_init(
	const i2c_addr7_t addr,     // �A�h���X
	const bool        broadcast // ��ČĂяo������
	);

// �X���[�u��M
// �߂�l: ���� = true, ���s = false
bool i2c_slave_receive();
	
bool i2c_slave_receive_ex(
	bool *const broadcast // ��ČĂяo�����ǂ��� (�s�v�ȏꍇ�� NULL)
	);

// I2C �X���[�u���M
// �߂�l: ���� = true, ���s = false
bool i2c_slave_send(void);


// ------------------------------------------------------------------
// �� �����ϐ�
// ------------------------------------------------------------------

// �o�X�G���[
static volatile bool i2c_slave_bus_error;

// �t�@�C���|�C���^
static volatile FILE *i2c_slave_fp;

// ��M�o�b�t�@
static volatile uint8_t i2c_slave_receive_buffer[KVR_I2C_PACKET_SIZE + 1]; // �o�b�t�@ (+1 �̓f�[�^��)
static volatile uint8_t i2c_slave_receive_buffer_position;                 // ���݈ʒu
static volatile uint8_t i2c_slave_receive_buffer_length;                   // �傫��
static volatile bool    i2c_slave_receive_buffer_writable;                 // �������݉�
static volatile bool    i2c_slave_receive_broadcast;                       // ��ČĂяo�����ǂ���

// ���M�o�b�t�@
static volatile uint8_t i2c_slave_send_buffer[KVR_I2C_PACKET_SIZE]; // �o�b�t�@
static volatile uint8_t i2c_slave_send_buffer_position;             // �ʒu
static volatile uint8_t i2c_slave_send_buffer_length;               // �傫��
static volatile bool    i2c_slave_send_buffer_writable;             // �������݉�


// ------------------------------------------------------------------
// �� �����֐�
// ------------------------------------------------------------------

// �o�b�t�@����ꕶ������
// (fdevopen �Ŏg�p���� getc)
static int i2c_slave_getc(FILE *fp){
	char c;
	
	// �o�b�t�@�̖����ɓ��B�������A�k�������ȏꍇ
	if(
		i2c_slave_receive_buffer[i2c_slave_receive_buffer_position] == '\0' ||
		i2c_slave_receive_buffer_position >= i2c_slave_receive_buffer_length
		)
	{
		return _FDEV_EOF;
	}
	
	// �߂�l��ޔ�
	c = i2c_slave_receive_buffer[i2c_slave_receive_buffer_position];
	
	// �o�b�t�@�ʒu��i�߂�
	++i2c_slave_receive_buffer_position;
	
	return c;
}

// �o�b�t�@�ֈꕶ���o��
// (fdevopen �Ŏg�p���� putc)
static int i2c_slave_putc(char c, FILE *fp){
	
	if(i2c_slave_send_buffer_position >= KVR_I2C_PACKET_SIZE){
		return _FDEV_EOF;
	}
	
	// �o�b�t�@�ɕۑ�
	i2c_slave_send_buffer[i2c_slave_send_buffer_position] = c;
	
	// �o�b�t�@�ʒu��i�߂�
	++i2c_slave_send_buffer_position;
	
	// �o�͂�Ԃ�
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

// I2C �X���[�u������
FILE *i2c_slave_init(
	const i2c_addr7_t addr,     // �A�h���X
	const bool        broadcast // ��ČĂяo������
	)
{
	// �ϐ�������
	i2c_slave_receive_buffer_position = 0;     // �o�b�t�@�ʒu
	i2c_slave_receive_buffer_length   = 0;     // �o�b�t�@�̑傫��
	i2c_slave_receive_broadcast       = false; // ��ČĂяo�����ǂ���
	i2c_slave_receive_buffer_writable = true;  // �o�b�t�@�ɏ������߂邩
	
	i2c_slave_send_buffer_position    = 0;
	i2c_slave_send_buffer_length      = 0;
	i2c_slave_send_buffer_writable    = true;
	
	// �X���[�u�A�h���X�ݒ�
	TWAR = addr << 1;
	
	// ��ČĂяo������
	if(broadcast){
		TWAR |= _BV(TWGCE);
	}
	
	// �X���[�u������
	// TWEA = 1, TWSTA = 0, TWSTO = 0, TWEN = 1
	TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
	TWCR |=  _BV(TWINT) |  _BV(TWEA) | _BV(TWEN);
	
	// �t�@�C���|�C���^���쐬
	i2c_slave_fp = fdevopen(i2c_slave_putc, i2c_slave_getc);
	
	// ���荞�݋���
	TWCR |= _BV(TWIE);
	sei();
	
	// �t�@�C���|�C���^��Ԃ�
	return (FILE*)i2c_slave_fp;
}

// I2C �X���[�u��M
// �߂�l: ���� = true, ���s = false
bool i2c_slave_receive(void){
	return i2c_slave_receive_ex(NULL);
}

bool i2c_slave_receive_ex(
	bool *const broadcast // ��ČĂяo�����ǂ���
	)
{
	// �o�b�t�@���������݉�Ԃɂ��� (��M����)
	i2c_slave_receive_buffer_writable = true;
	i2c_slave_receive_buffer_length   = 0;
	i2c_slave_receive_buffer_position = 0;
	
	// �o�X�G���[�����o����ׂɏ�����
	i2c_slave_bus_error = false;
	
	// �o�b�t�@���������ݕs��� (�ǂݍ��݉��) �ɂȂ�܂ő҂�
	while(i2c_slave_receive_buffer_writable){
		if(i2c_slave_bus_error){ // �o�X�G���[
			
			// �o�X�G���[���N���A
			i2c_slave_bus_error = false;
			
			// �o�b�t�@���������ݕs�ɐݒ肷�� (��M���Ȃ�)
			i2c_slave_receive_buffer_writable = false;
			
			return false;
		}
	}
	
	// �o�b�t�@�̑傫����ۑ�
	i2c_slave_receive_buffer_length = i2c_slave_receive_buffer_position;
	
	// �o�b�t�@�ʒu��������
	i2c_slave_receive_buffer_position = 1;
	
	clearerr((FILE*)i2c_slave_fp);
	
	// ��ČĂяo����������
	if(broadcast != NULL){
		*broadcast = i2c_slave_receive_broadcast;
	}
	
	return true; // ����
}

// I2C �X���[�u���M
// �߂�l: ���� = true, ���s = false
bool i2c_slave_send(void){
	// �o�b�t�@���������ݕs��� (���M���) �ɂ���
	i2c_slave_send_buffer_writable = false;
	
	// �o�b�t�@�̑傫����ۑ�
	i2c_slave_send_buffer_length = i2c_slave_send_buffer_position;
	
	// �o�b�t�@�ʒu��������
	i2c_slave_send_buffer_position = 0;
	
	// �o�X�G���[�����o���邽�߂ɏ�����
	i2c_slave_bus_error = false;
	
	// �o�b�t�@���������݉\��ԂɂȂ�܂ő҂� (���M�I����ҋ@)
	while(!i2c_slave_send_buffer_writable){
		if(i2c_slave_bus_error){
			i2c_slave_bus_error = false; // �o�X�G���[���N���A
			return false; // ���s
		}
	}
	
	// �o�b�t�@�̑傫����������
	i2c_slave_send_buffer_length = 0;
	
	// �o�b�t�@�̈ʒu��������
	i2c_slave_send_buffer_position = 0;

	// �G���[���N���A
	clearerror(i2c_slave_fp);
	
	return true; // ����
}

// ------------------------------------------------------------------
// ���荞��
// ------------------------------------------------------------------

ISR(TWI_vect){
//	printf("TW_STATUS = 0x%X\n", TW_STATUS);

	switch(TW_STATUS){

	// ��M�v��
	case TW_SR_SLA_ACK: // 0x60

	// ��ČĂяo�� ��M
	case TW_SR_GCALL_ACK: // 0x70
		// printf("%s\n", TW_STATUS == TW_SR_SLA_ACK ? "TW_SR_SLA_ACK" : "TW_SR_GCALL_ACK");
		
		// ��M�o�b�t�@�ɏ������݉\�ȏꍇ
		if(i2c_slave_receive_buffer_writable){
		
			// ��ČĂяo�����ǂ����ۑ�����
			i2c_slave_receive_broadcast = (TW_STATUS == TW_SR_GCALL_ACK);
			
			// �f�[�^��M ACK ����
			// TWSTO = 0, TWINT = 1, TWEA = 1
			TWCR &= ~_BV(TWSTO);
			TWCR |=  _BV(TWINT) | _BV(TWEA);
		}
		
		// ��M�o�b�t�@�ɏ������ݕs�ȏꍇ
		else {
			// �f�[�^��M NACK ����
			// TWSTO = 0, TWINT = 1, TWEA = 0
			TWCR &= ~_BV(TWSTO) & ~ _BV(TWEA);
			TWCR |=  _BV(TWINT);
		}

		break;

	// �f�[�^��M ACK
	case TW_SR_DATA_ACK: // 0x80

	// ��ČĂяo���̃f�[�^�o�C�h��M ACK ����
	case TW_SR_GCALL_DATA_ACK: // 0x90
	//	printf("%s\n", TW_STATUS == TW_SR_DATA_ACK ? "TW_SR_DATA_ACK" : "TW_SR_GCALL_DATA_ACK");
		
		i2c_slave_receive_buffer[i2c_slave_receive_buffer_position++] = TWDR;
		
		// �f�[�^��M ACK ����
		// TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) | _BV(TWEA);

		break;
	
	// �����f�[�^�o�C�g��M NACK ����
	case TW_SR_DATA_NACK: // 0x88
	
	case TW_SR_GCALL_DATA_NACK: // 0x98
	//	printf("TW_SR_DATA_NACK\n");		
		
		// ���w��X���[�u����ֈڍs�A�����Ή�
		// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);
		
		break;
	
	// ���M�v��
	case TW_ST_SLA_ACK: // 0xA8
//		printf("TW_ST_SLA_ACK\n");
		
		/*
		printf(
			"> writable = %d, length = %d\n",
			i2c_slave_send_buffer_writable,
			i2c_slave_send_buffer_length
		);*/
		
		// ���M����f�[�^�����݂���
		if(
			!i2c_slave_send_buffer_writable  &&
			i2c_slave_send_buffer_length > 0
			)
		{
			// �f�[�^���𑗐M
			TWDR = i2c_slave_send_buffer_length;
			
			// ACK ��M�\��
			// TWSTO = 0, TWINT = 1, TWEA = 1
			TWCR &= ~_BV(TWSTO);
			TWCR |=  _BV(TWINT) | _BV(TWEA);
		}
		
		else {
			// �f�[�^�� = 0
			TWDR = 0;
			
			// NACK ��M�\��
			// TWSTO = 0, TWINT = 1, TWEA = 0
			TWCR &= ~_BV(TWSTO) & ~_BV(TWEA);
			TWCR |=  _BV(TWINT);
		}
		
		break;
	
	// �f�[�^�o�C�g���M NACK ��M
	case TW_ST_DATA_NACK: // 0xC0
//		printf("TW_ST_DATA_NACK\n");

		// ���M����f�[�^�����݂��Ȃ��ׁA�������Ȃ�		
		TWDR = 0x00;

		// NACK ��M�\��
		// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);

		break;
	
	// �f�[�^�o�C�g���M ACK ��M
	case TW_ST_DATA_ACK: // 0xB8
	//	printf("TW_ST_DATA_ACK\n");
		
		/*
		printf(
			"> length = %d, position = %d\n",
			i2c_slave_send_buffer_length,
			i2c_slave_send_buffer_position
			);
		*/
		
		// ���M����f�[�^�����݂���
		if(
			!i2c_slave_send_buffer_writable  &&
			i2c_slave_send_buffer_length > 0 &&
			i2c_slave_send_buffer_position <= i2c_slave_send_buffer_length
			)
		{
			// �f�[�^�𑗐M
			TWDR = i2c_slave_send_buffer[i2c_slave_send_buffer_position];
			
			// �o�b�t�@�ʒu���X�V
			++i2c_slave_send_buffer_position;
			
			// �ŏI�o�C�g�̏���
			if(i2c_slave_send_buffer_position >= i2c_slave_send_buffer_length){
				// NACK ��M�\��
				// TWSTO = 0, TWINT = 1, TWEA = 0
				TWCR &= ~_BV(TWSTO) & ~_BV(TWEA);
				TWCR |=  _BV(TWINT);
			}
			
			else {
				// ACK ��M�\��
				// TWSTO = 0, TWINT = 1, TWEA = 1
				TWCR &= ~_BV(TWSTO);
				TWCR |=  _BV(TWINT) | _BV(TWEA);
			}
		}
		
		// ���M����f�[�^�����݂��Ȃ��ꍇ
		else {
			// �_�~�[�f�[�^���M
			TWDR = 0x00;
			
			// NACK ��M�\��
			// TWSTA = X, TWSTO = 0, TWINT = 1, TWEA = 0
			TWCR &= ~_BV(TWSTO) & ~_BV(TWEA);
			TWCR |=  _BV(TWINT);
		}
		
		break;
	
	// �ŏI�f�[�^�o�C�g���M ACK ��M
	case TW_ST_LAST_DATA: // 0xC8
		// ���w��X���[�u����ֈڍs, �����Ή�
		// TWSTA = 0, TWSTO = 0, TWINT = 1, TWEA = 1
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);
		
		// �f�[�^�𑗐M���Ă���ꍇ
		if(!i2c_slave_send_buffer_writable){
			// �������݉ɐݒ�
			i2c_slave_send_buffer_writable = true;
		}
		
//		printf("TW_ST_LAST_DATA\n");
		
		break;
	
	// �s���ȊJ�n���� / ��~�����ł̃o�X�ُ�
	case TW_BUS_ERROR: // 0x00
		
		// �o�X�ُ킩��񕜂���
		// TWSTA = 0, TWSTO = 1, TWINT = 1
		TWCR &= ~_BV(TWSTA);
		TWCR |=  _BV(TWSTO) | _BV(TWINT);
		
		i2c_slave_bus_error = true;
		
//		printf("TW_BUS_ERROR\n");
		
		break;
	
	// ��~	
	case TW_SR_STOP: // 0xA0
		TWCR &= ~_BV(TWSTA) & ~_BV(TWSTO);
		TWCR |=  _BV(TWINT) |  _BV(TWEA);
		
		// �f�[�^�������Ă��邩
		if(i2c_slave_receive_buffer_writable && i2c_slave_receive_buffer_position > 0){			
			// �������ݕs�ɐݒ�
			i2c_slave_receive_buffer_writable = false;
		}
		
		// �f�[�^�𑗐M���Ă���ꍇ
		if(!i2c_slave_send_buffer_writable && i2c_slave_send_buffer_position > 0){
			// �������݉ɐݒ�
			i2c_slave_send_buffer_writable = true;
		}
		
//		printf("TW_SR_STOP\n");

		break;
	
	// ����`
	default:
//		printf("UNKOWN STATUS: %x\n", TW_STATUS);
//		while(1);
	}
}

#endif
