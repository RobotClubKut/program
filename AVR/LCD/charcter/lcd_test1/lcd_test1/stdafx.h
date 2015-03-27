/*
 * stdafx.h
 *
 * Created: 2013/01/01 (火) AM 3:14:24
 *  Author: hikari
 */ 


#ifndef STDAFX_H_
#define STDAFX_H_


//CPUクロック 20MHz
#define F_CPU 20000000

//ボーレート
#define BOUD 9600


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "clcd.h"
#include "lcd_usart.h"


#endif /* STDAFX_H_ */
