#pragma once

//1サイクルdelay *50ns
#ifndef nop()
#define nop() __asm__ __volatile__ ("nop")
#endif

//Enable Pulse delay *450ns
#define glcd_epd() nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()


//PIN設定

//データピン
#define GLCD_DPORT PORTA
#define GLCD_DDDR DDRA
#define GLCD_DPIN PINA

//レジスタピン
#define GLCD_RPORT PORTC
#define GLCD_RDDR DDRC
#define GLCD_RPIN PINC

//データピン
#define GLCD_DB0 0x01
#define GLCD_DB1 0x02
#define GLCD_DB2 0x04
#define GLCD_DB3 0x08
#define GLCD_DB4 0x10
#define GLCD_DB5 0x20
#define GLCD_DB6 0x40
#define GLCD_DB7 0x80
#define GLCD_ADB 0xff
#define GLCD_TRANS(data) (data)

//レジスタピン
#define GLCD_RS 0x20
#define GLCD_RW 0x40
#define GLCD_E 0x80
#define GLCD_CS1 0x04
#define GLCD_CS2 0x08
#define GLCD_RST 0x10
#define GLCD_ACS 0x0c
#define GLCD_ARB 0xfc



//コマンドマクロ


//ディスプレイON/OFF
#define GLCD_DISPLAY 0x3e
#define glcd_display(cmd) glcd_cmd (GLCD_DISPLAY | (cmd))

#define GDISPLAY_ON 0x01
#define GDISPLAY_OFF 0x00

//アドレスセット
#define GLCD_POSITION 0x40
#define glcd_position(add) glcd_cmd (GLCD_POSITION | (add))

//ページセット
#define GLCD_PAGE 0xb8
#define glcd_page(add) glcd_cmd (GLCD_PAGE | (add))

//Display Data RAM start line set
#define GLCD_RAMSET 0xc0
#define glcd_ramset(add) glcd_cmd (GLCD_RAMSET | (add))




//関数

uint8_t glcd_draw (uint8_t);
void glcd_nbf_draw (uint8_t);
uint8_t glcd_cmd (uint8_t);
void glcd_nbf_cmd (uint8_t);
uint8_t glcd_bf (void);
void glcd_init (void);
void glcd_cs (uint8_t);

void glcd_cs (uint8_t cs)
{
	GLCD_RPORT &= ~GLCD_ACS;
	GLCD_RPORT |= (cs & GLCD_ACS);
	return;
}


uint8_t glcd_draw (uint8_t data)
{
	GLCD_RPORT &= ~GLCD_RW;
	GLCD_RPORT |= GLCD_RS;
	GLCD_DPORT = GLCD_TRANS (data);
	GLCD_RPORT |= GLCD_E;
	glcd_epd ();
	GLCD_RPORT &= ~GLCD_E;
	return glcd_bf ();
}

void glcd_nbf_draw (uint8_t data)
{
	GLCD_RPORT &= ~GLCD_RW;
	GLCD_RPORT |= GLCD_RS;
	GLCD_DPORT = GLCD_TRANS (data);
	GLCD_RPORT |= GLCD_E;
	glcd_epd ();
	GLCD_RPORT &= ~GLCD_E;
	_delay_ms (2);
	return;
}

uint8_t glcd_cmd (uint8_t cmd)
{
	GLCD_RPORT &= ~(GLCD_RS | GLCD_RW);
	GLCD_DPORT = GLCD_TRANS (cmd);
	GLCD_RPORT |= GLCD_E;
	glcd_epd ();
	GLCD_RPORT &= ~GLCD_E;
	return glcd_bf ();
}

void glcd_nbf_cmd (uint8_t cmd)
{
	GLCD_RPORT &= ~(GLCD_RS | GLCD_RW);
	GLCD_DPORT = GLCD_TRANS (cmd);
	GLCD_RPORT |= GLCD_E;
	glcd_epd ();
	GLCD_RPORT &= ~GLCD_E;
	_delay_ms (3);
	return;
}

uint8_t glcd_bf (void)
{
	uint8_t stat;
	GLCD_DPORT &= ~GLCD_ADB;
	GLCD_DDDR &= ~GLCD_ADB;
	GLCD_RPORT &= ~GLCD_RS;
	GLCD_RPORT |= GLCD_RW;
	do
	{
		glcd_epd ();
		GLCD_RPORT |= GLCD_E;
		glcd_epd ();
		stat = GLCD_DPIN;
		GLCD_RPORT &= ~GLCD_E;
	}
	while ((stat & GLCD_DB7) > 0);
	GLCD_DDDR = GLCD_ADB;
	GLCD_RPORT &= ~GLCD_RW;
	glcd_epd ();
	return stat;
}


void glcd_init (void)
{
	GLCD_DDDR |= GLCD_ADB;
	GLCD_RDDR |= GLCD_ARB;
	GLCD_DPORT &= ~GLCD_ADB;
	GLCD_RPORT &= ~GLCD_ARB;
	_delay_ms (50);
	GLCD_RPORT |= GLCD_RST;
	_delay_ms (10);
	glcd_cs (GLCD_CS1);
	glcd_nbf_cmd (GLCD_RAMSET);
	glcd_nbf_cmd (GLCD_DISPLAY | GDISPLAY_ON);
	glcd_cs (GLCD_CS2);
	glcd_nbf_cmd (GLCD_RAMSET);
	glcd_nbf_cmd (GLCD_DISPLAY | GDISPLAY_ON);
	glcd_cs (GLCD_CS1);
	return ;
}
