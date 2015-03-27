/*
 * oled.c
 *
 * Created: 2012/12/24 (月) AM 3:56:16
 *  Author: hikari
 */


#include "stdafx.h"


//文字送信 (ch : 文字)
uint8_t oled_ch (char ch)
{
	OLED_RPORT &= ~OLED_RW;
	OLED_RPORT |= OLED_RS;
	OLED_DPORT = OLED_TRANS (ch);
	OLED_RPORT |= OLED_E;
	oled_ep ();
	OLED_RPORT &= ~OLED_E;
	return oled_bf ();
}

//Busy flag を使わない文字送信 (ch : 文字)
uint8_t oled_nbf_ch (char ch)
{
	OLED_RPORT &= ~OLED_RW;
	OLED_RPORT |= OLED_RS;
	OLED_DPORT = OLED_TRANS (ch);
	OLED_RPORT |= OLED_E;
	oled_ep ();
	OLED_RPORT &= ~OLED_E;
	_delay_ms (1);
	return 0;
}

//文字列送信 (str : 文字列)
uint8_t oled_str (char *str)
{
	uint8_t add = 0;
	while (*str != '\0')
	add = oled_ch (*(str++));
	return add;
}

//コマンド送信 8bitモード
uint8_t oled_cmd (uint8_t cmd)
{
	OLED_RPORT &= ~(OLED_RW | OLED_RS);
	OLED_DPORT = OLED_TRANS (cmd);
	OLED_RPORT |= OLED_E;
	oled_ep ();
	OLED_RPORT &= ~OLED_E;
	return oled_bf ();
}

//Busy flag を使わないコマンド送信 8bitモード
uint8_t oled_nbf_cmd (uint8_t cmd)
{
	OLED_RPORT &= ~(OLED_RW | OLED_RS);
	OLED_DPORT = OLED_TRANS (cmd);
	OLED_RPORT |= OLED_E;
	oled_ep ();
	OLED_RPORT &= ~OLED_E;
	_delay_ms (2);
	return 0;
}

//文字登録
uint8_t oled_make_ch (uint8_t add, uint8_t *data)
{
	uint8_t i, bf;
	oled_make ((add << 3) & 0x38);
	for (i = 0; i < 8; i++)
		bf = oled_ch (*(data++));
	return bf;
}

//8文字登録
uint8_t oled_make_8ch (uint8_t *data)
{
	uint8_t i, add;
	oled_make (0);
	for (i = OLED_MAKE; i < 0x80; i++)
		add = oled_ch (*(data++));
	return add;
}

//Busy flag 確認
uint8_t oled_bf (void)
{
	/*
	uint8_t add;
	oled_ep ();
	//ポートを読み取りに設定
	OLED_DPORT &= ~OLED_ADB;
	OLED_DDDR &= ~OLED_ADB;
	OLED_RPORT &= ~OLED_RS;
	OLED_RPORT |= OLED_RW;
		OLED_RPORT |= OLED_E;
		oled_ep ();
		add = OLED_DPIN;
		while ((add & OLED_DB7) != 0);
		OLED_DPORT &= ~OLED_E;
		oled_ep ();
	OLED_RPORT &= ~OLED_RW;
	//ポートを書き込みに設定
	OLED_DDDR = OLED_ADB;
	return (add &= ~OLED_DB7);
	*/
	_delay_us(320);
	return 0;
}

//OLED初期化
uint8_t oled_init (uint8_t func, uint8_t scr, uint8_t ent)
{
	//ポート設定
	OLED_DDDR |= OLED_ADB;
	OLED_RDDR |= OLED_ARB;
	OLED_RPORT &= ~OLED_ARB;

	_delay_ms (500);

	//ファンクションセット
	oled_function (func);

	//スクリーン設定
	oled_screen (scr);

	//ディスプレイクリア
	oled_clear ();
	
	oled_home ();

	//エントリーモードセット
	oled_entry (ent);

	//ディスプレイクリア
	return oled_clear ();
}
