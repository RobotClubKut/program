// ------------------------------------------------------------------
// kvr / KUT AVR Library
// IO Abstract Library / "kvr/io/abstract.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   初版。
//
// ------------------------------------------------------------------

#ifndef __KVR_IO_ABSTRACT__
#define __KVR_IO_ABSTRACT__

#define KVR_IO_ABSTRACT_VERSION 10000UL // version 1.00.00

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <avr/io.h>

typedef uint16_t io_abstract_t;

static volatile uint8_t *io_abstract_port[] = {
	
#if defined(PORTA)
	&PORTA,
#else
	NULL,
#endif
	
#if defined(PORTB)
	&PORTB,
#else
	NULL,
#endif
	
#if defined(PORTC)
	&PORTC,
#else
	NULL,
#endif
	
#if defined(PORTD)
	&PORTD
#else
	NULL
#endif
};

static volatile uint8_t *io_abstract_pin[] = {
	
#if defined(PINA)
	&PINA,
#else
	NULL,
#endif
	
#if defined(PINB)
	&PINB,
#else
	NULL,
#endif
	
#if defined(PINC)
	&PINC,
#else
	NULL,
#endif
	
#if defined(PIND)
	&PIND
#else
	NULL
#endif
};

static volatile uint8_t *io_abstract_ddr[] = {
	
#if defined(DDRA)
	&DDRA,
#else
	NULL,
#endif
	
#if defined(DDRB)
	&DDRB,
#else
	NULL,
#endif
	
#if defined(DDRC)
	&DDRC,
#else
	NULL,
#endif
	
#if defined(DDRD)
	&DDRD
#else
	NULL
#endif
};

static void io_abstract_convert(
	const char *port,
	uint8_t    *num,
	uint8_t    *bv
	);

static inline volatile bool io_abstract_is_multi(
	const char *port
	);

static void io_abstract_write_multi(
	const char *port,
	const bool  data
	);

volatile bool io_read(
	const char *port
	)
{
	uint8_t num, bv;
	
	io_abstract_convert(port, &num, &bv);
	
	*io_abstract_ddr [num] &= ~bv;
	*io_abstract_port[num] &= ~bv;
	
	return !!(*io_abstract_pin[num] & bv);
}

volatile bool io_read_pullup(
	const char *port
	)
{
	uint8_t num, bv;
	
	io_abstract_convert(port, &num, &bv);
	
	*io_abstract_ddr [num] &= ~bv;
	*io_abstract_port[num] |=  bv;
	
	return !!(*io_abstract_pin[num] & bv);
}

void io_write(
	const char *port,
	const bool  data
	)
{
	uint8_t num, bv;
	
	if(io_abstract_is_multi(port)){
		io_abstract_write_multi(port, data);
	}
	
	else {
		io_abstract_convert(port, &num, &bv);
		
		*io_abstract_ddr [num] |= bv;
		
		if(data){
			*io_abstract_port[num] |= bv;
		}
		
		else {
			*io_abstract_port[num] &= ~bv;
		}
	}
}

static void io_abstract_convert(
	const char *port,
	uint8_t    *num,
	uint8_t    *bv
	)
{
	*num = port[0] - 'A';
	*bv  = _BV(port[1] - '0');
}

static inline volatile bool io_abstract_is_multi(
	const char *port
	)
{
	return port[2] != '\0';
}

static void io_abstract_write_multi(
	const char *port,
	const bool  data
	)
{
	const char *current = port;
	char       buff[3]  = { 0 };
	char       end;
	
	while(*current != '\0'){
		// XN-M 形式
		if(*(current + 2) == '-'){
			// 開始地点を記憶
			buff[0] = *current++;
			buff[1] = *current++;
			
			++current;
			
			// 終了地点を取得
			end = *current++;
			
			// 終了地点までループ
			for( ; buff[1] <= end; ++buff[1]){
				io_write(buff, data);
			}
		}
		
		// XN 形式
		else {
			buff[0] = *current++;
			buff[1] = *current++;
			
			io_write(buff, data);
		}
		
		if(*current == ','){
			++current;
		}
	}
}

#endif
