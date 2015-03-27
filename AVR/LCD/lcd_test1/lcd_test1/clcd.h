/*
 * clcd.h
 *
 * Created: 2012/12/24 (月) AM 1:17:07
 *  Author: hikari
 */

#include <avr/io.h>
#include <util/delay.h>

#ifndef CLCD_H_
#define CLCD_H_

/*****ピン設定 ※ピン設定は変更してね!**********/

//データピンのポート
#define CLCD_DPORT PORTB
#define CLCD_DDDR DDRB
#define CLCD_DPIN PINB

//レジスタピンのポート
#define CLCD_RPORT PORTD
#define CLCD_RDDR DDRD
#define CLCD_RPIN PIND

//データビット設定
#define CLCD_DB0 0x01
#define CLCD_DB1 0x02
#define CLCD_DB2 0x04
#define CLCD_DB3 0x08
#define CLCD_DB4 0x10
#define CLCD_DB5 0x20
#define CLCD_DB6 0x40
#define CLCD_DB7 0x80

//全データビット
#define CLCD_ADB 0xff

//送信ビット変換
#define CLCD_TRANS(data) (data)

//レジスタピン設定
#define CLCD_RS 0x10
#define CLCD_RW 0x20
#define CLCD_E 0x40

//全レジスタビット
#define CLCD_ARB (CLCD_RS | CLCD_RW | CLCD_E)





/*****delay設定*********************************/

//1サイクル待つ (50ns)
#ifndef nop()
#define nop() __asm__ __volatile__ ("nop")
#endif

//220ns 待つ
#define clcd_ep() nop();nop();nop();nop();nop()





/*****関数プロトタイプ**************************/

//コマンド送信 (cmd : コマンド)
uint8_t clcd_cmd (uint8_t cmd);

//コマンド送信 ※Busy Flag チェックなし (cmd : コマンド)
uint8_t clcd_nbf_cmd (uint8_t cmd);

//LCD初期化 (func : ファンクションセット, scr : スクリーン設定, ent : エントリーモード)
uint8_t clcd_init (uint8_t func, uint8_t scr, uint8_t ent);

//文字送信 (ch : 文字)
uint8_t clcd_ch (char ch);

//文字送信 ※Busy Flag チェックなし (ch : 文字)
uint8_t clcd_nbf_ch (char ch);

//文字列送信 (str : 文字列)
uint8_t clcd_str (char *str);

//Busy Flag チェック
uint8_t clcd_bf (void);

//文字登録 (add : アドレス, data : 文字データ)
uint8_t clcd_make_ch (uint8_t add, uint8_t *data);

//8文字登録 (data : 文字データ)
uint8_t clcd_make_8ch (uint8_t *data);





/*****コマンドマクロ****************************/

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

//カーソルシフトon
#define CS_ON 0x01

//カーソルシフトoff
#define CS_OFF 0x00


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
#define SHIFT_DISPLAY 0x80

//カーソルシフト
#define SHIFT_CURSOR 0x00

//右シフト
#define SHIFT_RIGHT 0x04

//左シフト
#define SHIFT_LEFT 0x00


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
#define clcd_position(xp) clcd_cmd(CLCD_POSITION | (xp))

//2行目
#define LINE2 0x40

//1行目
#define LINE1 0x00


#endif /* CLCD_H_ */
