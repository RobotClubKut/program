#pragma once

//1サイクルdelay *50ns
#ifndef nop()
#define nop() __asm__ __volatile__ ("nop")
#endif

//Enable Pulse delay *460ns
#define clcd_epd() nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()


//PIN設定

//データピン
#define CLCD_DPORT PORTB
#define CLCD_DDDR DDRB
#define CLCD_DPIN PINB

//レジスタピン
#define CLCD_RPORT PORTD
#define CLCD_RDDR DDRD
#define CLCD_RPIN PIND

//データピン
#define CLCD_DB0 0x01
#define CLCD_DB1 0x02
#define CLCD_DB2 0x04
#define CLCD_DB3 0x08
#define CLCD_DB4 0x10
#define CLCD_DB5 0x20
#define CLCD_DB6 0x40
#define CLCD_DB7 0x80
#define CLCD_ADB 0xff
#define CLCD_TRANS(data) (data)

//レジスタピン
#define CLCD_RS 0x20
#define CLCD_RW 0x40
#define CLCD_E 0x80
#define CLCD_R 0x60
#define CLCD_ARB 0xe0


//コマンドマクロ


//ディスプレイクリア
#define CLCD_CLEAR 0x01
#define clcd_clear() clcd_cmd(CLCD_CLEAR)


//カーソルホーム
#define CLCD_HOME 0x02
#define clcd_home() clcd_cmd(CLCD_HOME)


//エントリーモードセット
#define CLCD_ENTRY 0x04
#define clcd_entry(cmd) clcd_cmd(CLCD_ENTRY | (cmd))

//アドレスカウンタ インクリメント
#define AC_INC 0x02

//アドレスカウンタ デクリメント
#define AC_DEC 0x00

//カーソルオートシフトon
#define COS_ON 0x01

//カーソルオートシフトoff
#define COS_OFF 0x00


//スクリーン設定
#define CLCD_SCREEN 0x08
#define clcd_screen(cmd) clcd_cmd(CLCD_SCREEN | (cmd))

//表示on
#define CDISPLAY_ON 0x04

//表示off
#define CDISPLAY_OFF 0x00

//カーソルon
#define CURSOR_ON 0x02

//カーソルoff
#define CURSOR_OFF 0x00

//カーソル点滅on
#define BLINK_ON 0x01

//カーソル点滅off
#define BLINK_OFF 0x00


//シフト設定
#define CLCD_SHIFT 0x10
#define clcd_shift(cmd) clcd_cmd(CLCD_SHIFT | (cmd))

//ディスプレイシフト
#define DISPLAY 0x80

//カーソルシフト
#define CURSOR 0x00

//右シフト
#define RIGHT 0x04

//左シフト
#define LEFT 0x00


//ファンクションセット
#define CLCD_FUNCTION 0x20
#define clcd_function(cmd) clcd_cmd(CLCD_FUNCTION | (cmd))

//8bitモード
#define MODE_8BIT 0x10

//4bitモード
#define MODE_4BIT 0x00

//2行
#define USE_2LINE 0x08

//1行
#define USE_1LINE 0x00

//5×11ドット
#define DOT_5X11 0x04

//5×8ドット
#define DOT_5X8 0x00


//文字登録
#define CLCD_MAKE 0x40
#define clcd_make(add) clcd_cmd(CLCD_MAKE | (add))


//カーソル位置設定
#define CLCD_POSITION 0x80
#define clcd_position(xp) clcd_cmd(CLCD_POSITION | ((xp) - 1))

//1行目
#define LINE1 0x00

//2行目
#define LINE2 0x40

//3行目
#define LINE3 0x14

//4行目
#define LINE4 0x54


//関数

uint8_t clcd_ch (char);
void clcd_nbf_ch (char);
void clcd_str (char *);
uint8_t clcd_cmd (uint8_t);
void clcd_nbf_cmd (uint8_t);
void clcd_make_ch (uint8_t, char *);
void clcd_make_8ch (char *);
void clcd_init (uint8_t, uint8_t, uint8_t);
uint8_t clcd_bf (void);

//文字送信 *8bitモード
uint8_t clcd_ch (char ch)
{
	CLCD_RPORT &= ~CLCD_RW;
	CLCD_RPORT |= CLCD_RS;
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (ch);
	CLCD_DPORT = CLCD_TRANS (ch);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	return clcd_bf ();
}

//文字送信 (BFなし) *8bitモード
void clcd_nbf_ch (char ch)
{
	CLCD_RPORT &= ~CLCD_RW;
	CLCD_RPORT |= CLCD_RS;
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (ch);
	CLCD_DPORT = CLCD_TRANS (ch);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	_delay_ms (1);
	return;
}

//文字列送信
void clcd_str (char *str) 
{
	while (*str != '\0') 
		clcd_ch (*(str++));
	return;
}

//コマンド送信 *8bitモード
uint8_t clcd_cmd (uint8_t cmd)
{
	CLCD_RPORT &= ~(CLCD_RW | CLCD_RS);
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (cmd);
	CLCD_DPORT = CLCD_TRANS (cmd);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	return clcd_bf ();
}

//コマンド送信 (BFなし) *8bitモード
void clcd_nbf_cmd (uint8_t cmd)
{
	CLCD_RPORT &= ~(CLCD_RW | CLCD_RS);
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (cmd);
	CLCD_DPORT = CLCD_TRANS (cmd);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	_delay_ms (1);
	return;
}

//文字登録
void clcd_make_ch (uint8_t add, char *data)
{
	uint8_t i;
	clcd_make ((add | 0x07) << 3);
	for (i = 0; i < 8; i++)
		clcd_ch (*(data++));
	return;
}

//8文字登録
void clcd_make_8ch (char *data)
{
	uint8_t i;
	clcd_make (0);
	for (i =0 ; i < CLCD_MAKE; i++)
		clcd_ch (*(data++));
	return;
}


//Busy Frag 確認
uint8_t clcd_bf ()
{
	uint8_t add;

	CLCD_DPORT &= ~CLCD_ADB;
	CLCD_DDDR &= ~CLCD_ADB;
	CLCD_RPORT &= ~CLCD_RS;
	CLCD_RPORT |= CLCD_RW;
	do
	{
		clcd_epd ();
		CLCD_RPORT |= CLCD_E;
		clcd_epd ();
		add = CLCD_DPIN;
		CLCD_RPORT &= ~CLCD_E;
	}
	while ((add & CLCD_DB7) > 0);

	CLCD_DDDR |= CLCD_ADB;
	CLCD_RPORT &= ~CLCD_RW;
	clcd_epd ();
	return add;
}

//LCD初期化
void clcd_init (uint8_t func, uint8_t scr, uint8_t ent)
{
	//ポート設定
	CLCD_DDDR |= CLCD_ADB;
	CLCD_RDDR |= CLCD_ARB;
	CLCD_DPORT &= ~CLCD_ADB;
	CLCD_RPORT &= ~CLCD_ARB;

	_delay_ms (50);

	//強制8bitモード設定
	clcd_nbf_cmd (CLCD_FUNCTION | MODE_8BIT);
	_delay_ms (5);
	clcd_nbf_cmd (CLCD_FUNCTION | MODE_8BIT);
	_delay_us (500);
	clcd_nbf_cmd (CLCD_FUNCTION | MODE_8BIT);
	_delay_us (100);

	//ファンクションセット
	clcd_function (func);

	//スクリーン設定
	clcd_screen (scr);

	//ディスプレイクリア
	clcd_clear ();

	//エントリーモードセット
	clcd_entry (ent);

	return;
}

