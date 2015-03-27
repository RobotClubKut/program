//
// SH2-7125(48MHz) 用SCIモジュール
//
//
// 2007.02.15 K.Nishimura
//
#include <stdarg.h>
#include "iodefine.h"

void SCI_init(void);
short SCI_write(unsigned char c);
short SCI_read(unsigned char *c);


#define SCI_RX_BUF_SHIFT   3
#define SCI_RX_BUF_SIZE   (1<<SCI_RX_BUF_SHIFT)
#define SCI_RX_BUF_MASK   (SCI_RX_BUF_SIZE-1)

volatile static struct stSCI_RX{
	unsigned short rdptr;                // リードポインタ
	unsigned short wrptr;                // ライトポインタ
	unsigned short dataNum;              // バッファ内データ数
	unsigned char buf[SCI_RX_BUF_SIZE];  // 受信バッファ
}SCI_RX;

// --------------------------------------------------------
// SCI 初期化
// --------------------------------------------------------
void SCI_init(void){

	SCI_RX.rdptr = 0;
	SCI_RX.wrptr = 0;
	SCI_RX.dataNum = 0;

	// スタンバイ機能の解除
	STB.CR3.BIT._SCI1 = 0;       // SCI1 start

	// SCI動作停止
	SCI1.SCSCR.BIT.TIE = 0;      // 送信割込み:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.RIE = 0;      // 受信割込み:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.TE  = 0;      // 送信動作:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.RE  = 0;      // 受信動作:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.MPIE = 0;     // MP割込みイネーブル
	SCI1.SCSCR.BIT.TEIE = 0;     // 送信終了割込み:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.CKE  = 0;     // クロックソース選択

	// SCI設定
	SCI1.SCSMR.BIT.CA   = 0;      // 0:調歩同期、1:クロック同期
	SCI1.SCSMR.BIT.CHR  = 0;      // 0:8ビットデータ、1:7ビットデータ
	SCI1.SCSMR.BIT._PE  = 0;      // 0:パリティ禁止、1:パリティ許可
	SCI1.SCSMR.BIT.OE   = 0;      // 0:偶数パリティ、1:奇数パリティ
	SCI1.SCSMR.BIT.STOP = 0;      // 0:1ストップビット、1:2ストップビット
	SCI1.SCSMR.BIT.MP   = 0;      // マルチプロセッサモード 0:禁止,1:許可
	SCI1.SCSMR.BIT.CKS  = 0;      // クロックセレクト 00:1/1 , 01:1/4 , 10:1/16 , 11:1/64

	// ボーレート設定
	SCI1.SCBRR = 19;             // 38400 bps

	// SSR初期設定
	SCI1.SCSSR.BIT.TDRE = 0;     // TDRエンプティ
	SCI1.SCSSR.BIT.RDRF = 0;     // RDRフル
	SCI1.SCSSR.BIT.ORER = 0;     // オーバーランエラー
	SCI1.SCSSR.BIT.FER  = 0;     // フレーミングエラー
	SCI1.SCSSR.BIT.PER  = 0;     // パリティエラー

	// TXD端子設定
	PFC.PACRL2.BIT.PA4MD = 1;    // 000:PA4,001:TXD1,111:IRQ2

	// RXD端子設定
	PFC.PACRL1.BIT.PA3MD = 1;    // 000:PA3,001:RXD1,111:IRQ1

	SCI1.SCSCR.BIT.RIE = 1;      // 受信割込み:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.TE  = 1;      // 送信動作:許可(1)/禁止(0)
	SCI1.SCSCR.BIT.RE  = 1;      // 受信動作:許可(1)/禁止(0)

}

// --------------------------------------------------------
// SCI 1バイト送信
//   引数   - unsigned char c : 送信データ
//   戻り値 - 0:送信失敗、1:送信成功
// --------------------------------------------------------
short SCI_write(unsigned char c){
	unsigned long i;
	unsigned short flag;
	
	// 送信バッファが解放されるのをポーリングで待機
	// タイムアウトあり
	flag = 0;
	for(i=0;i<0x00200000;i++){
		if(SCI1.SCSSR.BIT.TDRE){
			flag = 1;
			break;
		}
	}
	
	if(flag){
		SCI1.SCTDR = c;  // 送信バッファにデータセット
		SCI1.SCSSR.BIT.TDRE = 0;
		return 1;
	}
	return 0;
}

// --------------------------------------------------------
// 受信割込み
//   設定
//     intprg.c の先頭部分に以下を追加
//       extern void intprg_rxi1(void);
//     intprg.c 内のSCI割込み部を以下のように修正
//       void INT_SCI1_RXI1(void){intprg_rxi1();}
//   割込み設定
//	   INTC.IPRL.BIT._SCI1 = 0xF;    // 割り込みレベル設定(SCI1)
//	   set_imask(14);                // 割り込みマスククリア
// --------------------------------------------------------
#pragma regsave(intprg_rxi1)
void intprg_rxi1(void){
	unsigned char c;

	SCI1.SCSSR.BIT.ORER = 0;     // オーバーランエラー
	SCI1.SCSSR.BIT.FER  = 0;     // フレーミングエラー
	SCI1.SCSSR.BIT.PER  = 0;     // パリティエラー

	// 受信バッファにデータ格納
	if(SCI1.SCSSR.BIT.RDRF){                      // 受信フラグチェック
		SCI1.SCSSR.BIT.RDRF = 0;                  // 受信フラグクリア
		c = SCI1.SCRDR;                           // 受信データ取得
		if(SCI_RX.dataNum != SCI_RX_BUF_SIZE){    // 受信バッファの空きチェック
			SCI_RX.buf[SCI_RX.wrptr] = c;         // 受信バッファに格納
			SCI_RX.wrptr = (SCI_RX.wrptr + 1 ) & SCI_RX_BUF_MASK;  // ライトポインタの更新
			SCI_RX.dataNum++;                     // データ数のインクリメント
		}
	}
}

// --------------------------------------------------------
// SCI 1バイト受信
//   引数   - unsigned char *c : 受信データ(ポインタ渡し)
//   戻り値 - 0:受信なし、1:受信成功
// --------------------------------------------------------
short SCI_read(unsigned char *c){
	// 受信バッファからデータ取り出し
	if(SCI_RX.dataNum != 0){                    // データ数チェック
		*c = SCI_RX.buf[SCI_RX.rdptr];          // 受信バッファからデータ取得
		SCI_RX.rdptr = (SCI_RX.rdptr + 1 ) & SCI_RX_BUF_MASK;  // リードポインタの更新
		SCI_RX.dataNum--;                       // データ数のデクリメント
		return 1;
	}
	
	*c = 0;
	return 0;
}

// --------------------------------------------------------
// 1文字受信
//   引数   - 
//   戻り値 - 
// --------------------------------------------------------
short s_read(unsigned char *c){
	short ret=0;

	// 受信バッファにデータ格納
	if(SCI1.SCSSR.BIT.RDRF){             // 受信フラグチェック
		SCI1.SCSSR.BIT.RDRF = 0;         // 受信フラグクリア
		*c = SCI1.SCRDR;                 // 受信データ取得
		// 改行コードの変換
		if(*c == 0x0D) *c = '\n';
		ret = 1;
	}
	return ret;
}
