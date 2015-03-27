#pragma once


//1サイクル待つ
#define NOP() __asm__ __volatile__ ("nop")


//220ns 待つ
#ifndef delE
#define delE() NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP()
#endif



/********ピン設定***********************************************************************************************************************/

//LCDのポート
#if !defined(LCD_PORT) && !defined(LCD_PORTR) && !defined(LCD_PIN)
	#warning "not defined LCD_PORT so defined PORTB"
	#define LCD_PORT PORTB
	#define LCD_PORTR DDRB
	#define LCD_PIN PINB
#elif !defined(LCD_PORT) || !defined(LCD_PORTR) || !defined(LCD_PIN)
	#error "not defined all LCD_PORT"
#endif


#if !defined(LCD_RPORT) && !defined(LCD_RPORTR)
	#warning "not defined LCD_RPORT so defined PORTD"
	#define LCD_RPORT PORTD
	#define LCD_RPORTR DDRD
#elif !defined(LCD_RPORT) || !defined(LCD_RPORTR)
	#error "not defined all LCD_RPORT"
#endif


//LCDのピン

#if !defined(LCD_DB0) && !defined(LCD_DB1) && !defined(LCD_DB2) && !defined(LCD_DB3) && !defined(LCD_DB4) && !defined(LCD_DB5) && !defined(LCD_DB6) && !defined(LCD_DB7)
	#warning "not defined LCD_DB so define default set"
	#define LCD_DB0 0x01
	#define LCD_DB1 0x02
	#define LCD_DB2 0x04
	#define LCD_DB3 0x08
	#define LCD_DB4 0x10
	#define LCD_DB5 0x20
	#define LCD_DB6 0x40
	#define LCD_DB7 0x80
	#define LCD_ADB 0xff
	#define TRANS_PORT(i) (i)
#elif !defined(LCD_DB0) || !defined(LCD_DB1) || !defined(LCD_DB2) || !defined(LCD_DB3) || !defined(LCD_DB4) || !defined(LCD_DB5) || !defined(LCD_DB6) || !defined(LCD_DB7)
	#error "not defined all LCD_DB"	
#elif !defined(TRANS_PORT)
	#warning "if define good TRANS_PORT, become speed up"
	//送信bit変換
	#define TRANS_PORT(i) (((i & 0x01) * LCD_BD0) | (((i >> 1) & 0x01) * LCD_BD1) | ((i >> 2) & 0x01) * LCD_BD2) | ((i >> 3) & 0x01) * LCD_BD3) | ((i >> 4) & 0x01) * LCD_BD4) | ((i >> 5) & 0x01) * LCD_BD5) | ((i >> 6) & 0x01) * LCD_BD6) | ((i >> 7) & 0x01) * LCD_BD7))
#endif

#if !defined(LCD_RS) && !defined(LCD_RW) && !defined(LCD_E)
	#warning "not defined LCD_RS & LCD_RW & LCD_E so define default set"
	#define LCD_RS 0x20
	#define LCD_RW 0x40
	#define LCD_E 0x80
#elif !defined(LCD_RS) || !defined(LCD_RW) || !defined(LCD_E)
	#error "not defined LCD_RS | LCD_RW | LCD_E"
#endif

#ifndef LCD_ADB
	#define LCD_ADB (LCD_DB0 | LCD_DB1 | LCD_DB2 | LCD_DB3 | LCD_DB4 | LCD_DB5 | LCD_DB6 | LCD_DB7)
#endif




/******コマンドマクロ***********************************************************************************************************************/


//ディスプレイクリア
#define LCD_CLEAR 0x01
#define lcd_clear() lcd_cmd(LCD_CLEAR)


//カーソルホーム
#define LCD_HOME 0x02
#define lcd_home() lcd_cmd(LCD_HOME)


//エントリーモードセット
#define LCD_ENTRY 0x03
#define lcd_entry(cmd) lcd_cmd(LCD_ENTRY | (cmd))

//アドレスカウンタ インクリメント
#define AC_INC 0x02

//アドレスカウンタ デクリメント
#define AC_DEC 0x00

//カーソルオートシフトon
#define COS_ON 0x01

//カーソルオートシフトoff
#define COS_OFF 0x00

//スクリーン設定
#define LCD_SCREEN 0x08
#define lcd_screen(cmd) lcd_cmd(LCD_SCREEN | (cmd))

//表示on
#define DISPLAY_ON 0x04

//表示off
#define DISPLAY_OFF 0x00

//カーソルon
#define CURSOR_ON 0x02

//カーソルoff
#define CURSOR_OFF 0x00

//カーソル点滅on
#define BLINK_ON 0x01

//カーソル点滅off
#define BLINK_OFF 0x00


//シフト設定
#define LCD_SHIFT 0x10
#define lcd_shift(cmd) lcd_cmd(LCD_SHIFT | (cmd))

//ディスプレイシフト
#define DISPLAY 0x80

//カーソルシフト
#define CURSOR 0x00

//右シフト
#define RIGHT 0x04

//左シフト
#define LEFT 0x00


//ファンクションセット
#define LCD_FUNCTION 0x20
#define lcd_function(cmd) lcd_cmd(LCD_FUNCTION | (cmd))

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
#define LCD_MAKE 0x40
#define lcd_make(add) lcd_cmd(LCD_MAKE | (add))


//カーソル位置設定
#define LCD_POSITION 0x80
#define lcd_position(xp) lcd_cmd(LCD_POSITION | (xp))

//1行目
#define LINE1 0x00

//2行目
#define LINE2 0x40

//3行目
#define LINE3 0x14

//4行目
#define LINE4 0x54




/***********関数*****************************************************************************************************************/


uint8_t lcd_ch (char);
void lcd_nbf_ch (char);
void lcd_str (char *);
uint8_t lcd_cmd (uint8_t);
void lcd_nbf_cmd (uint8_t);
void lcd_make_ch (uint8_t, char *);
void lcd_make_8ch (char *);
void lcd_init (uint8_t, uint8_t, uint8_t);
uint8_t lcd_bf (void);



//文字送信 8bitモード
uint8_t lcd_ch (char ch)
{
	LCD_RPORT &= ~LCD_RW;
	LCD_RPORT |= LCD_RS;
	LCD_RPORT |= LCD_E;
	LCD_PORT = TRANS_PORT (ch);
	delE ();
	LCD_RPORT &= ~LCD_E;
	return lcd_bf ();
}

//Busy flag を使わない文字送信 8bitモード
void lcd_nbf_ch (char ch)
{
	LCD_RPORT &= ~LCD_RW;
	LCD_RPORT |= LCD_RS;
	LCD_RPORT |= LCD_E;
	LCD_PORT = TRANS_PORT (ch);
	delE ();
	LCD_RPORT &= ~LCD_E;
	_delay_ms (1);
	return;
}

//文字列送信
void lcd_str (char *str) 
{
	while (*str != '\0') 
		lcd_ch (*(str++));
	return;
}

//コマンド送信 8bitモード
uint8_t lcd_cmd (uint8_t cmd)
{
	LCD_RPORT &= ~(LCD_RW | LCD_RS);
	LCD_RPORT |= LCD_E;
	LCD_PORT = TRANS_PORT (cmd);
	delE ();
	LCD_RPORT &= ~LCD_E;
	return lcd_bf ();
}

//Busy flag を使わないコマンド送信 8bitモード
void lcd_nbf_cmd (uint8_t cmd)
{
	LCD_RPORT &= ~(LCD_RW | LCD_RS);
	LCD_RPORT |= LCD_E;
	LCD_PORT = TRANS_PORT (cmd);
	delE ();
	LCD_RPORT &= ~LCD_E;
	_delay_ms (2);
	return;
}

//文字登録
void lcd_make_ch (uint8_t add, char *data)
{
	uint8_t i;
	lcd_entry (AC_DEC | COS_ON);
	lcd_make ((add << 3) & 0x38);
	for (i = 0; i < 8; i++)
		lcd_ch (*(data++));
	return;
}

//8文字登録
void lcd_make_8ch (char *data)
{
	uint8_t i;
	lcd_entry (AC_DEC | COS_ON);
	lcd_make (0);
	for (i = LCD_MAKE; i < 0x80; i++)
		lcd_ch (*(data++));
	return;
}

//Busy flag 確認
uint8_t lcd_bf (void)
{
	uint8_t add;

	//ポートを読み取りに設定
	LCD_PORTR = (uint8_t)~LCD_ADB;
	LCD_PORT = (uint8_t)~LCD_ADB;

	LCD_RPORT |= LCD_RW;
	LCD_RPORT &= ~LCD_RS;
	LCD_RPORT |= LCD_E;
	delE ();
	while (((add = LCD_PIN) & LCD_DB7) > 0);
	LCD_PORT &= ~LCD_E;
	LCD_RPORT &= ~LCD_RW;

	//ポートを書き込みに設定
	LCD_PORTR = LCD_ADB;
	delE ();
	return (add &= ~LCD_DB7);
}

//LCD初期化
void lcd_init (uint8_t func, uint8_t scr, uint8_t ent)
{
	//ポート設定
	LCD_PORTR |= LCD_ADB;
	LCD_RPORTR |= (LCD_RS | LCD_RW | LCD_E);
	LCD_RPORT &= ~(LCD_RS | LCD_RW | LCD_E);

	_delay_ms (1000);

	//強制8bitモード設定
	lcd_nbf_cmd (LCD_FUNCTION | MODE_8BIT);
	_delay_ms (5);
	_delay_ms (1);
	lcd_nbf_cmd (LCD_FUNCTION | MODE_8BIT);
	_delay_us (500);
	_delay_ms (1);
	lcd_nbf_cmd (LCD_FUNCTION | MODE_8BIT);
	_delay_us (100);
	_delay_ms (1);

	//ファンクションセット
	lcd_function (func);

	//スクリーン設定
	lcd_screen (scr);

	//ディスプレイクリア
	lcd_clear ();

	//エントリーモードセット
	lcd_entry (ent);



	return;
}
