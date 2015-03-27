/**************************************************
	ただシリアルで何か送るためのサンプルプログラム。
							The coll of a distant star. for me?
																			by中原
**************************************************/

/****************************************
	インクルードファイル
****************************************/
#include <7125.h>

/****************************************
	マクロ設定
****************************************/
#define whit while(Wheit_i)Wheit_i-=1
#define LED00 PE.DRL.BIT.B0
#define LED01 PE.DRL.BIT.B1
/****************************************
	グローバル変数
****************************************/
char TXD1[30],RXD1[10];

/****************************************
		SH_INIT SH初期化
****************************************/
void SH_INIT(unsigned int Wheit_i){
	whit;		//初期起動待ち
	//	割り込み不許可
	SetSRReg(0xf);
	
	// IO
	PFC.PECRL1.BIT.PE0MD=1;		//IOポートに設定
	PFC.PECRL1.BIT.PE1MD=1;		//IOポートに設定
	PFC.PEIORL.BIT.B0=1;			//出力ポートに設定
	PFC.PEIORL.BIT.B1=1;			//出力ポートに設定


	//	SCI1
	SCI1_INIT(br115200,0xa,TXD1,sizeof(TXD1),RXD1,sizeof(RXD1));
	PFC.PACRL1.BIT.PA3MD = 1;//PA3:001-RXD1入力
	PFC.PACRL2.BIT.PA4MD = 1;//PA4:001-TXD1出力

	//	MTU2
	STB.CR4.BIT._MTU2=0;		//スタンバイ復帰
	MTU2.TSTR.BIT.CST0=MTU2.TSTR.BIT.CST1=0;		//カウント停止
	
	
	//	MTU2 0＆1
	
	MTU2.TSTR.BIT.CST1 = MTU2.TSTR.BIT.CST0 = 0;     //MTU21,20カウント停止
	MTU21.TCR.BIT.TPSC = 0;     //クロック周波数φ/4
	MTU20.TCR.BIT.TPSC = 0;     //クロック周波数φ/4
	MTU21.TCR.BIT.CCLR = 1;     //TGRAコンペアマッチでTCNTクリア
	MTU20.TCR.BIT.CCLR = 7;     //同期クリア
	MTU2.TSYR.BYTE = 3;         //チャネル0，1同期動作
	MTU20.TIOR.BIT.IOA = 5;     //初期状態で1出力 コンペアマッチしたら0出力
	MTU20.TIOR.BIT.IOB = 5;     //初期状態で1出力 コンペアマッチしたら0出力
	MTU20.TIOR.BIT.IOC = 5;     //初期状態で1出力 コンペアマッチしたら0出力
	MTU20.TIOR.BIT.IOD = 5;     //初期状態で1出力 コンペアマッチしたら0出力

	MTU21.TGRA = 5000;
	MTU20.TGRA = 100;
	MTU20.TGRB = 5000;
	MTU20.TGRC = 100;
	MTU20.TGRD = 100;
	
	MTU20.TMDR.BIT.MD = 3;      //PWMモード2
	MTU21.TMDR.BIT.MD = 3;      //PWMモード2

}

/****************************************
		メイン
****************************************/
void main(){

	SH_INIT(1<<21);
	SetSRReg(0x0);
	MTU2.TSTR.BIT.CST0=MTU2.TSTR.BIT.CST1=1;		//カウント開始


	SCI1_PRINTF("レッツゴー\n");
	int i=5000;
	LED01=1;
	while(1){
		while(i--);
		i=500;
		MTU20.TGRA=(MTU20.TGRA==5000?0:MTU20.TGRA+1);
			
//		LED01=~LED01;
	
	}


}

