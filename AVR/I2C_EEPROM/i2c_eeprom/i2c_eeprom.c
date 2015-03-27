#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "kvr/usart.h"

int main(void)
{
	long data=0;
	char test[64]={"abcdefghigklmnopqrstuvwxyz\nyamamoto tatsuya\nsakura\n"};
	char test2[64];
	//ポートの入出力の設定
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	//PWMの設定

	//OCR0A,OCR0B の設定
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000001;

	//OCR1A,OCR1B の設定
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;

	//OCR2A,OCR2B の設定
	TCCR2A = 0b10110011;
	TCCR2B = 0b00000001;

	
	// USART0, 9600 bps
	usart_init(0, 9600);
	// USART0 を標準出力に設定
	usart_stdout(0);
	// TWIの SCL周波数を 200kHzに設定
	twi_init(200000);
	while(1)
	{
		eeprom_i2c_write_page(0xa0,0,test);
		eeprom_i2c_read_sequential(0xa0,0,test2,64);
		printf("%s",test2);
	}
}

/*------------ TWI主装置制御関数 ------------*/

// TWI初期化関数
void twi_init(long f)
{
	//TWI分周(SCL周波数 = CPU周波数/(16+2*(TWBR)×前置分周値)
	TWBR = F_CPU/(2*f)-8;
}
void twi_start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	_delay_us(100);
}
void twi_end()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	_delay_us(100);
}
void twi_write_slave_address(int add)
{
	TWDR = add;
	TWCR = (1<<TWINT)|(1<<TWEN);
	_delay_us(100);
}
void twi_read_slave_address(int add)
{
	TWDR = add+1;
	TWCR = (1<<TWINT)|(1<<TWEN);
	_delay_us(100);
}
void twi_write_data(int data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	_delay_us(100);
}
int twi_read_data_noack()
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	_delay_us(100);
	return TWDR;
}
int twi_read_data_ack()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	_delay_us(100);
	return TWDR;
}

/*------------ EEPROM制御 ------------*/
// sla     : 従装置アドレス(1010xxx0) xxx=A0,A1,A2
// address : EEPROM内メモリアドレス
// data	   : 書き込みデータ

// EEPROM1バイト書き込み
void eeprom_i2c_write_byte(int sla,uint16_t address,int data)
{
	twi_start();
	twi_write_slave_address(sla);
	twi_write_data((address>>8)&0xff);
	twi_write_data(address&0xff);
	twi_write_data(data);
	twi_end();
	_delay_ms(10);
}
// EEPROM１バイト読み出し
int eeprom_i2c_read_byte(int sla,uint16_t address)
{
	int data;
	twi_start();
	twi_write_slave_address(sla);
	twi_write_data((address>>8)&0xff);
	twi_write_data(address&0xff);
	twi_start();
	twi_read_slave_address(sla);
	data = twi_read_data_noack();
	twi_end();
	return data;
}
// EEPROMページ書き込み（６４バイト以下でも以上でも６４バイト書き込み）
void eeprom_i2c_write_page(int sla,uint16_t address,char *data)
{
	int i;
	twi_start();
	twi_write_slave_address(sla);
	twi_write_data((address>>8)&0xff);
	twi_write_data(address&0xff);
	for(i = 0;i < 64;i++)
	{
		twi_write_data(*(data+i));
	}
	twi_end();
	_delay_ms(20);
}
// EEPROMシーケンシャル読み出し（lengthの大きさ読み込む）
void eeprom_i2c_read_sequential(int sla,uint16_t address,char *data,int length)
{
	int i;
	twi_start();
	twi_write_slave_address(sla);
	twi_write_data((address>>8)&0xff);
	twi_write_data(address&0xff);
	twi_start();
	twi_read_slave_address(sla);
	for(i = 0;i < length-1;i++)
	{
		*(data+i) = twi_read_data_ack();
	}
	*(data+i+1) = twi_read_data_noack();
	twi_end();
}

