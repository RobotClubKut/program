SCI関数
lib_SCI_buff_101217.c
lib_SCI_buff_101217.h
	for SH7125 @ HEW
	Wrote by conpe_


SH7125のSCI1用の送受信関数です。



【使い方】

初めに
void SCI1_setup(int br);
を呼び出してSCI周りを初期化します。引数はボーレート。4800～115200bpsまで行けるっぽいです。


[送信]

バッファを使って順次割り込みにより送信します。
なので送信待ちを極力しません。

intprg.cのINT_SCI1_TXI1からintSCI1_tx_buff()を呼び出すようにしてください。
resetprg.cの#define SR_Initは0x00000000にする。

バッファサイズはlib_SCI_buff_101217.hの方で指定。


基本的には、
 void SCI1_printf(char *, ...);
で送信していけばおっけーです。普通のprintfと同じ使い方。
変換仕様は%d,%x,%X,%c,%sのみ対応しています。小数対応めんどい。

数字,文字(列)だけ出力すればいいんだけどってときは、
 char SCI1_tx_char(char);
 void SCI1_tx_str(char *);
 void SCI1_tx_d(long);
 void SCI1_tx_x(long);
 void SCI1_tx_X(long);
ここらへん使ってみてください。SCI1_printf使うよりもちょっぴり速いはずです。



[受信]
1文字受信するまで待つときはこれ
 unsigned char SCI1_rx_char(void);

待たないときはこれ
 unsigned char SCI1_rx_char_nowait(void);

数字を受信したいときはこれ
 unsigned int SCI1_rx_d(void);
複数ケタ対応。
エンターが来るまで受信を続けます。
数字以外が来たときは読み飛ばします。




最終更新
2010/12/17
