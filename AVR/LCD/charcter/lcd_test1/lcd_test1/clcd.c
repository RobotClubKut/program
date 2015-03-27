/*
 * clcd.c
 *
 * Created: 2012/12/24 (月) AM 3:56:16
 *  Author: hikari
 */ 


#include "stdafx.h"


//文字送信 (ch : 文字)
uint8_t clcd_ch (char ch)
{
	CLCD_RPORT &= ~CLCD_RW;
	CLCD_RPORT |= CLCD_RS;
	CLCD_RPORT |= CLCD_E;
	CLCD_DPORT = CLCD_TRANS (ch);
	clcd_ep ();
	CLCD_RPORT &= ~CLCD_E;
	return clcd_bf ();
}

//Busy flag を使わない文字送信 (ch : 文字)
uint8_t clcd_nbf_ch (char ch)
{
	CLCD_RPORT &= ~CLCD_RW;
	CLCD_RPORT |= CLCD_RS;
	CLCD_RPORT |= CLCD_E;
	CLCD_DPORT = CLCD_TRANS (ch);
	clcd_ep ();
	CLCD_RPORT &= ~CLCD_E;
	_delay_ms (1);
	return 0;
}

//文字列送信 (str : 文字列)
uint8_t clcd_str (char *str)
{
	uint8_t add = 0;
	while (*str != '\0')
	add = clcd_ch (*(str++));
	return add;
}

//コマンド送信 8bitモード
uint8_t clcd_cmd (uint8_t cmd)
{
	CLCD_RPORT &= ~(CLCD_RW | CLCD_RS);
	CLCD_RPORT |= CLCD_E;
	CLCD_DPORT = CLCD_TRANS (cmd);
	clcd_ep ();
	CLCD_RPORT &= ~CLCD_E;
	return clcd_bf ();
}

//Busy flag を使わないコマンド送信 8bitモード
uint8_t clcd_nbf_cmd (uint8_t cmd)
{
	CLCD_RPORT &= ~(CLCD_RW | CLCD_RS);
	CLCD_RPORT |= CLCD_E;
	CLCD_DPORT = CLCD_TRANS (cmd);
	clcd_ep ();
	CLCD_RPORT &= ~CLCD_E;
	_delay_ms (2);
	return 0;
}

//文字登録
uint8_t clcd_make_ch (uint8_t add, uint8_t *data)
{
	uint8_t i, bf;
	clcd_make ((add << 3) & 0x38);
	for (i = 0; i < 8; i++)
		bf = clcd_ch (*(data++));
	return bf;
}

//8文字登録
uint8_t clcd_make_8ch (uint8_t *data)
{
	uint8_t i, add;
	clcd_make (0);
	for (i = CLCD_MAKE; i < 0x80; i++)
		add = clcd_ch (*(data++));
	return add;
}

//Busy flag 確認
uint8_t clcd_bf (void)
{
	uint8_t add;

	//ポートを読み取りに設定
	CLCD_DPORT &= ~CLCD_ADB;
	CLCD_DDDR &= ~CLCD_ADB;
	
	CLCD_RPORT |= CLCD_RW;
	CLCD_RPORT &= ~CLCD_RS;
	CLCD_RPORT |= CLCD_E;
	clcd_ep ();
	while (((add = CLCD_DPIN) & CLCD_DB7) > 0);
	CLCD_DPORT &= ~CLCD_E;
	CLCD_RPORT &= ~CLCD_RW;

	//ポートを書き込みに設定
	CLCD_DDDR = CLCD_ADB;
	
	clcd_ep ();
	return (add &= ~CLCD_DB7);
}

//CLCD初期化
uint8_t clcd_init (uint8_t func, uint8_t scr, uint8_t ent)
{
	//ポート設定
	CLCD_DDDR |= CLCD_ADB;
	CLCD_RDDR |= CLCD_ARB;
	CLCD_RPORT &= ~CLCD_ARB;

	_delay_ms (16);

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

	//エントリーモードセット
	clcd_entry (ent);

	//ディスプレイクリア
	return clcd_clear ();
}
