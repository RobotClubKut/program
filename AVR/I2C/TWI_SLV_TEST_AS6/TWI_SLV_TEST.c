#define F_CPU 20000000UL // 20 MHz

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>

#include "kvr/usart.h"
#include "../i2c/slave.h"

int main(void){
//	char a, b;
	uint8_t i;

	// USART0, 38400 bps
	usart_init(0, 38400);
	// USART0 を標準出力に設定
	usart_stdout(0);
	
	_delay_ms(100);
	printf("\nusart start\n");

	// I2C 開始
	i2c_slave_init(1, true);
	
	printf("i2c start\n");
	
	while(1){
		bool broadcast;

		if(i2c_slave_receive_ex(&broadcast)){
			printf(
				"S: M->S: broadcast = %d, length = %d, raw data (hex) = ",
				broadcast,
				i2c_slave_receive_buffer_length
				);

			for(i = 0; i < i2c_slave_receive_buffer_length; ++i){
				printf("%02X ", i2c_slave_receive_buffer[i]);
				
				// send (初期バイトはデータ長)
				if(i > 0){
					i2c_slave_write_uint8(i2c_slave_receive_buffer[i]);
				}
			}

			putchar('\n');

			if(i2c_slave_send()){
				printf("S: S->M\n");
			}
		}
	/*
		if(i2c_slave_receive()){
			data = i2c_slave_read_int();
		
			printf("M->S: %d\n", data);

			i2c_slave_write_int(data + 1);
			
			if(i2c_slave_send()){
				printf("S->M: %d\n", data + 1);
			}
		}
		*/
	}
	
	return 0;
}
