/***********************************************************************/
/* I do not desire anything.                                           */
/* And I decided to create everything.                                 */
/* From here, I will do what I can.                                    */
/***********************************************************************/

/*  シリアルについて
http://www.geocities.jp/in_subaru/shrslib/index7125.html*/
//#define SHRS_SENDBUFFERSIZE1 500
//#define SHRS_BRR1 19
//#define SHRS_USE_PRINTF

/****************************************
	マクロ設定
****************************************/
#define MD0AL PE.DRL.BIT.B0
#define MD1AL PE.DRL.BIT.B1
#define MD0BL PE.DRL.BIT.B2
#define MD1BL PE.DRL.BIT.B3
#define MD0BH PE.DRL.BIT.B4
#define MD1BH PE.DRL.BIT.B5
#define MD0AH PE.DRL.BIT.B6
#define MD1AH PE.DRL.BIT.B7
#define MD0ALT MTU20.TGRA
#define MD1ALT MTU20.TGRB
#define MD0BLT MTU20.TGRC
#define MD1BLT MTU20.TGRD
#define	MD0ALS PFC.PECRL1.BIT.PE0MD
#define	MD1ALS PFC.PECRL1.BIT.PE1MD
#define	MD0BLS PFC.PECRL1.BIT.PE2MD
#define	MD1BLS PFC.PECRL1.BIT.PE3MD
/****************************************
	グローバル変数
****************************************/
signed int R,L;
signed int X,Y;
signed int D;

/****************************************
	インクルードファイル
****************************************/
#include "iodefine.h"
#include <machine.h>
//#include <stdarg.h>
//#include "sci_mod.h"
#include "sh7125rslib.h"

/****************************************
		プロトタイプ宣言
****************************************/
void md0pwr(signed short);
void md1pwr(signed short);
/****************************************
		SH_INIT SH初期化
****************************************/
void SH_INIT(void){

//	割り込み不許可
	set_imask(15);                // 割り込みマスククリア
//	SCI1
 	SHRS_Open(1);
	
	INTC.IPRL.BIT._SCI1 = 0xF;    // 割り込みレベル設定(SCI1)

	//	IRQ0 & IRQ3
	INTC.IRQCR.BIT.IRQ0S=3;
	INTC.IRQCR.BIT.IRQ3S=3;
	INTC.IPRA.BIT._IRQ0=15;
	INTC.IPRA.BIT._IRQ3=15;
	INTC.IRQSR.BIT.IRQ0F=0;
	INTC.IRQSR.BIT.IRQ3F=0;
	PFC.PACRL2.BIT.PA5MD=7;		//IRQ3
	PFC.PBCRL1.BIT.PB2MD=1;		//IRQ0

/*
	//	AD
	STB.CR4.BIT._AD0=0;//ADスタンバイ復帰
	AD0.ADCR.BIT.ADST=0;//ADストップ
	AD0.ADCSR.BIT.ADF=0;//エンドフラグクリア
	AD0.ADCSR.BIT.ADIE=0;//割り込み許可
	AD0.ADCSR.BIT.CKSL=3;//超高速
	AD0.ADCSR.BIT.ADM=3;//2chスキャンモード
	AD0.ADCSR.BIT.ADCS=0;//サイクルスキャン
	AD0.ADCSR.BIT.CH=1;//AN0&AN1
	//INTC.IPRK.BIT._AD01=0xc;

	//	CMT0
	STB.CR4.BIT._CMT=0;
	CMT.CMSTR.BIT.STR0=0;
	CMT.CMSTR.BIT.STR1=0;
	CMT0.CMCSR.BIT.CMIE=1;
	CMT0.CMCSR.BIT.CKS=3;
	CMT0.CMCNT=1;
	CMT0.CMCOR=10000;
	CMT1.CMCSR.BIT.CMIE=1;
	CMT1.CMCSR.BIT.CKS=2;
	CMT1.CMCNT=1;
	CMT1.CMCOR=24414;
	INTC.IPRJ.BIT._CMT0 =6;
	INTC.IPRJ.BIT._CMT1 =6;
	CMT.CMSTR.BIT.STR0=1;
	CMT.CMSTR.BIT.STR1=1;
*/
	
		
	
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
	MTU20.TIOR.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOB = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOD = 2;     //初期状態で0出力 コンペアマッチしたら1出力

	MTU21.TGRA = 2500;
	MTU20.TGRA = 2500;
	MTU20.TGRB = 2500;
	MTU20.TGRC = 2500;
	MTU20.TGRD = 2500;
	
	MTU20.TMDR.BIT.MD = 3;      //PWMモード2
	MTU21.TMDR.BIT.MD = 3;      //PWMモード2
	md0pwr(0);
	md1pwr(0);
	MTU2.TSTR.BIT.CST0=MTU2.TSTR.BIT.CST1=1;		//カウント開始


/*
	// MTU2 5  100ms  両エッジカウント
	MTU25.TSTR.BIT.CSTU = 0;
	MTU25.TSTR.BIT.CSTV = 0;
	MTU25.TSTR.BIT.CSTW = 0;
	MTU25.TSR.BIT.CMFW = 0;		//フラグクリア
	MTU25.TCRW.BIT.TPSC = 3;		//φ/64
//	MTU25.TIORU.BIT.IOC = 17;
//	MTU25.TIORV.BIT.IOC = 17;
	MTU25.TIER.BIT.TGIEW = 1;		//Wコンペアマッチインタラプト
	MTU25.TGRW = 39062;
	MTU25.TCCR.BIT.CLRW = 1; //Wマッチでタイマクリア
	MTU25.TSR.BIT.CMFW = 0;		//フラグクリア
	INTC.IPRF.BIT._MTU25 =7;
*/
	// IO
	PFC.PECRL1.BIT.PE0MD=1;		//タイマーポートに設定
	PFC.PECRL1.BIT.PE1MD=1;		//タイマーポートに設定
	PFC.PECRL1.BIT.PE2MD=1;		//タイマーポートに設定
	PFC.PECRL1.BIT.PE3MD=1;		//タイマーポートに設定
	PFC.PECRL2.BIT.PE4MD=0;		//IOポートに設定
	PFC.PECRL2.BIT.PE5MD=0;		//IOポートに設定
	PFC.PECRL2.BIT.PE6MD=0;		//IOポートに設定
	PFC.PECRL2.BIT.PE7MD=0;		//IOポートに設定
	
	PFC.PEIORL.WORD=0x00FF;		//出力ポートに設定
	PE.DRL.WORD=0x0000;		//出力ポートに設定

	
	PFC.PACRL2.BIT.PA5MD=7;		//IRQ3
	PFC.PBCRL1.BIT.PB2MD=1;		//IRQ0
	PFC.PBCRL1.BIT.PB3MD=3;		//TIC5V
	PFC.PBCRL2.BIT.PB5MD=3;		//TIC5U

	

}

void main(void){
	int i=100000;
	while(i--);
	SH_INIT();
	set_imask(5);
	X=0;
	Y=0;
	D=0;
	
	
	while(1);
}

void md0pwr(signed short pwr){
	if(pwr>0){
		if(pwr>100) pwr=100;
		MD0ALS=0;
		MD0BH=0;
		MD0BLT=25*(100-pwr);
		MD0BLS=1;
		MD0AH=1;
	}else if(pwr<0){
		if(pwr<-100) pwr=-100;
		MD0BLS=0;
		MD0AH=0;
		MD0ALT=25*(100+pwr);
		MD0ALS=1;
		MD0BH=1;
	}else{
		MD0ALS=0;
		MD0BLS=0;
		MD0AH=0;
		MD0BH=0;
	}
}
void md1pwr(signed short pwr){
	if(pwr>0){
		if(pwr>100) pwr=100;
		MD1ALS=0;
		MD1BH=0;
		MD1BLT=25*(100-pwr);
		MD1BLS=1;
		MD1AH=1;
	}else if(pwr<0){
		if(pwr<-100) pwr=-100;
		MD1BLS=0;
		MD1AH=0;
		MD1ALT=25*(100+pwr);
		MD1ALS=1;
		MD1BH=1;
	}else{
		MD1ALS=0;
		MD1BLS=0;
		MD1AH=0;
		MD1BH=0;
	}
}
