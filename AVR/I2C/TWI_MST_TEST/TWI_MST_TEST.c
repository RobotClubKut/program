#define F_CPU 20000000UL // 20 MHz

#include <avr/io.h>
#include <util/delay.h>

#include "kvr/usart.h"
#include "../i2c/master.h"



int main(void)
{
	int data = 0;

	// USART0, 38400 bps
	usart_init(0, 38400);
	// USART0 を標準出力に設定
	usart_stdout(0);

	//マイコン安定化させるため待機
	_delay_ms(100);

	// TWIの SCL周波数を 400kHzに設定
	i2c_master_init(400000);
	
	//マイコン安定化させるため待機
	_delay_ms(100);

	usart_printf(0, "\nprogram start\n");
	usart_printf(0, "TWBR = %d\n", (int)TWBR);
	usart_printf(0, "TWSR = %d\n", (int)(TWSR & 0b11));
	
	while(1){
		i2c_master_write_int(data);
		usart_printf(0, "M: M->S: %d\n", data);
		
		while(!i2c_master_send(1));

		_delay_ms(1);

		if(i2c_master_receive(1)){
			data = i2c_master_read_int();

			printf(
				"M: S->M: %d\n",
				data
				);
		}

		++data;
	}
}


