/*
 * oled.h
 *
 * Created: 2012/12/24 (月) AM 1:17:07
 *  Author: hikari
 */

#ifndef OLED_H_
#define OLED_H_

/*****ピン設定 ※ピン設定は変更してね!**********/

//データピンのポート
#define OLED_DPORT PORTB
#define OLED_DDDR DDRB
#define OLED_DPIN PINB

//レジスタピンのポート
#define OLED_RPORT PORTD
#define OLED_RDDR DDRD
#define OLED_RPIN PIND

//データビット設定
#define OLED_DB0 0x01
#define OLED_DB1 0x02
#define OLED_DB2 0x04
#define OLED_DB3 0x08
#define OLED_DB4 0x10
#define OLED_DB5 0x20
#define OLED_DB6 0x40
#define OLED_DB7 0x80

//全データビット
#define OLED_ADB 0xff

//送信ビット変換
#define OLED_TRANS(data) (data)

//レジスタピン設定
#define OLED_RS 0x10
#define OLED_RW 0x20
#define OLED_E 0x40

//全レジスタビット
#define OLED_ARB (OLED_RS | OLED_RW | OLED_E)





/*****delay設定*********************************/

//1サイクル待つ (50ns)
#define nop() __asm__ __volatile__ ("nop")

//250ns 待つ
#define oled_ep() nop();nop();nop();nop();nop();nop()





/*****関数プロトタイプ**************************/

//コマンド送信 (cmd : コマンド)
uint8_t oled_cmd (uint8_t cmd);

//コマンド送信 ※Busy Flag チェックなし (cmd : コマンド)
uint8_t oled_nbf_cmd (uint8_t cmd);

//LCD初期化 (func : ファンクションセット, scr : スクリーン設定, ent : エントリーモード)
uint8_t oled_init (uint8_t func, uint8_t scr, uint8_t ent);

//文字送信 (ch : 文字)
uint8_t oled_ch (char ch);

//文字送信 ※Busy Flag チェックなし (ch : 文字)
uint8_t oled_nbf_ch (char ch);

//文字列送信 (str : 文字列)
uint8_t oled_str (char *str);

//Busy Flag チェック
uint8_t oled_bf (void);

//文字登録 (add : アドレス, data : 文字データ)
uint8_t oled_make_ch (uint8_t add, uint8_t *data);

//8文字登録 (data : 文字データ)
uint8_t oled_make_8ch (uint8_t *data);





/*****コマンドマクロ****************************/

//ディスプレイクリア
#define OLED_CLEAR 0x01
#define oled_clear() oled_cmd(OLED_CLEAR)


//カーソルホーム
#define OLED_HOME 0x02
#define oled_home() oled_cmd(OLED_HOME)


//エントリーモードセット
#define OLED_ENTRY 0x04
#define oled_entry(cmd) oled_cmd(OLED_ENTRY | (cmd))

//アドレスカウンタ インクリメント
#define AC_INC 0x02

//アドレスカウンタ デクリメント
#define AC_DEC 0x00

//カーソルシフトon
#define CS_ON 0x01

//カーソルシフトoff
#define CS_OFF 0x00


//スクリーン設定
#define OLED_SCREEN 0x08
#define oled_screen(cmd) oled_cmd(OLED_SCREEN | (cmd))

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
#define OLED_SHIFT 0x10
#define oled_shift(cmd) oled_cmd(OLED_SHIFT | (cmd))

//ディスプレイシフト
#define SHIFT_DISPLAY 0x80

//カーソルシフト
#define SHIFT_CURSOR 0x00

//右シフト
#define SHIFT_RIGHT 0x04

//左シフト
#define SHIFT_LEFT 0x00


//ファンクションセット
#define OLED_FUNCTION 0x20
#define oled_function(cmd) oled_cmd(OLED_FUNCTION | (cmd))

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
#define OLED_MAKE 0x40
#define oled_make(add) oled_cmd(OLED_MAKE | (add))


//カーソル位置設定
#define OLED_POSITION 0x80
#define oled_position(xp) oled_cmd(OLED_POSITION | (xp))

//2行目
#define LINE2 0x40

//1行目
#define LINE1 0x00


#endif /* OLED_H_ */
