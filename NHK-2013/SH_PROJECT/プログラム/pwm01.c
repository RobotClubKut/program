/**************************************************

							The coll of a distant star. for me?
																			by中原
**************************************************/

/****************************************
	インクルードファイル
****************************************/
#include <7125.h>
#include <math.h>

/****************************************
	マクロ設定
****************************************/
#define whit while(Wheit_i)Wheit_i-=1
#define PWM0_0 PE.DRL.BIT.B0
#define PWM0_1 PE.DRL.BIT.B1
#define PWM1_0 PE.DRL.BIT.B2
#define PWM1_1 PE.DRL.BIT.B3
#define PWM2_0 PE.DRL.BIT.B4
#define PWM2_1 PE.DRL.BIT.B5
/****************************************
	グローバル変数
****************************************/
char TXD1[30],RXD1[10];
signed int W0,WR0;
/****************************************
		SH_INIT SH初期化
****************************************/
void SH_INIT(unsigned int Wheit_i){
	whit;		//初期起動待ち
	//	割り込み不許可
	SetSRReg(0xf);
	
	// PFC
	PFC.PBCRL1.BIT.PB2MD=1;;
	
	// IO
	PFC.PACRL4.BIT.PA14MD=0;
	PFC.PAIORL.BIT.B14=0;
	
	/*
	PFC.PACRL1.BIT.PA0MD=0;	//IO設定と入力設定。これと下の行は初期値がゼロなので設定する必要はない。
	PFC.PAIORL.BIT.B0=0;
	PFC.PECRL1.BIT.PE0MD=0;		//IOポートに設定
	PFC.PECRL1.BIT.PE1MD=0;
	PFC.PEIORL.BIT.B0=1;			//出力ポートに設定
	PFC.PEIORL.BIT.B1=1;
	*/
	//	IRQ
	INTC.IRQCR.BIT.IRQ0S=3;
	INTC.IPRA.BIT._IRQ0=10;

	
	//	CMT
	/*
	STB.CR4.BIT._CMT=0;
	CMT.CMSTR.BIT.STR0=0;	//カウント停止
	CMT0.CMCNT=0;
	CMT0.CMCSR.BIT.CMF=0;	//フラグクリア
	INTC.IPRJ.BIT._CMT0=10;	//割り込み順位
	CMT0.CMCSR.BIT.CMIE=1;	//割り込み許可
	CMT0.CMCSR.BIT.CKS=0x1;	//φ/32
	CMT0.CMCOR=16384;
	*/
	//	MTU2		MP=25e6
	STB.CR4.BIT._MTU2=0;
	//	MTU20
	MTU2.TSTR.BIT.CST0=0;
	MTU20.TCR.BIT.TPSC=1;	//MP/4
	MTU20.TMDR.BIT.MD=0;
	MTU20.TIER.BIT.TGIEA=1;
	MTU20.TIER.BIT.TGIED=1;
	MTU20.TCR.BIT.CCLR=6;		//D
	MTU20.TGRA=1;
	MTU20.TGRD=62500;
	INTC.IPRF.BIT._MTU240=8;
	MTU2.TSTR.BIT.CST0=1;
	//	MTU23
	MTU2.TSTR.BIT.CST3=0;
	MTU23.TCR.BIT.TPSC=5;
	MTU23.TMDR.BIT.MD=0;
	MTU23.TIER.BIT.TGIEA=0;
	MTU23.TCR.BIT.CCLR=0;
	MTU23.TGRA=0xff;
	INTC.IPRE.BIT._MTU23G=10;
	MTU2.TSTR.BIT.CST3=1;
	//	MTU24
	MTU2.TSTR.BIT.CST4=0;
	MTU24.TCR.BIT.TPSC=3;
	MTU24.TMDR.BIT.MD=0;
	MTU24.TIER.BIT.TGIEA=1;
	MTU24.TCR.BIT.CCLR=1;
	MTU24.TGRA=39063;
	INTC.IPRF.BIT._MTU24G=10;
	MTU2.TSTR.BIT.CST4=0;

	//	SCI1
	SCI1_INIT(br115200,0xc,TXD1,sizeof(TXD1),RXD1,sizeof(RXD1));
	PFC.PACRL1.BIT.PA3MD = 1;//PA3:001-RXD1入力
	PFC.PACRL2.BIT.PA4MD = 1;//PA4:001-TXD1出力
	
}
/***************************************
		cmi0
***************************************/
void _int_cmt0(void){
	SCI1_PRINTF("Go!!\n");
	
	CMT0.CMCSR.BIT.CMF=0;	//フラグクリア
}

unsigned int a;

/****************************************
		メイン
****************************************/
void main(){

	SH_INIT(1<<20);
	SetSRReg(0x0);
	CMT.CMSTR.BIT.STR0=1;	//カウント開始
	
	a=0;
	WR0=0;

	SCI1_PRINTF("kimura\n");
	SCI1_PRINTF("%d\n",CMT0.CMCNT);
	
	while(1){
//		if(CMT0.CMCSR.BIT.CMF){
//			SCI1_PRINTF("HEY\n");
//			CMT0.CMCSR.BIT.CMF=0;
//		}
	}

}

/***************************************
		int_tgi2d0
***************************************/
void int_tgi2d0(){
	
	
	PWM0_0
	
	MTU20.TSR.BIT.TGFD=0;

}

/***************************************
		int_tgi2a3
***************************************/
void int_tgi2a3(){
	
	MTU23.TIER.BIT.TGIEA=0;
	W0=1<<16;
//	if(WR)
//	WR0++;
	MTU23.TSR.BIT.TGFA=0;

}

/***************************************
		int_tgi2a3
***************************************/
void int_tgi2a3(){
	
	MTU23.TIER.BIT.TGIEA=0;
	W0=1<<16;
//	if(WR)
//	WR0++;
	MTU23.TSR.BIT.TGFA=0;

}
/***************************************
		int_tgi2a4
***************************************/
void int_tgi2a4(){
//	static signed short AAAAA=0;
	SCI1_PRINTF("%d\n",a++);
	MTU24.TSR.BIT.TGFA=0;

}
/***************************************
		int_irq0
***************************************/
void int_irq0 (){
	double w;
	if(PA.DRL.BIT.B13){
	if(MTU23.TIER.BIT.TGIEA){
		MTU23.TIER.BIT.TGIEA=0;
		W0=MTU23.TCNT-MTU23.TGRA;
	}
	if(W0<0)
		W0+=(1<<16);
//	W0+=WR0*(1<<16);
//	WR0=0;
	if(INTC.IRQSR.BIT.IRQ0L)
		W0*=-1;
	
	w=W0*1024.0/25.0e6*5;
	
	
	SCI1_PRINTF("%d%d\t%8d\t%c%1d.%3d[rps]\n",INTC.IRQSR.BIT.IRQ0L,PA.DRL.BIT.B13,W0,(w<0?'-':' '),abs((int)w),abs((int)(w*1000)-((int)w)*1000));

	MTU23.TGRA=(MTU23.TCNT==0?65535:MTU23.TCNT-1);
	MTU23.TIER.BIT.TGIEA=1;
	INTC.IRQSR.BIT.IRQ0F=0;
	}
}
