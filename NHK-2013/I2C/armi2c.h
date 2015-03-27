/*
 * armi2c.h
 *
 *  Created on: 2012/12/27
 *      Author: pnakach
 */



uint8_t I2CMODE;
typedef struct {
  struct {
    char  *buf;
    short wp;	//現在値
    short rp;	//目標値
    short maxlen;
  } mtx;
  struct {
    char  *buf;
    short wp;	//現在値
    short rp;	//目標値
    short maxlen;
  } stx;
  struct {
    char  *buf;
    short wp;
    short rp;
    short maxlen;
  } rx;
} i2cfifo;

volatile i2cfifo I2CFIFO;

void i2_init(uint8_t config,uint16_t fm,char *txbuf, short txl, char *rxbuf, short rxl){
//  uint32_t DL;

  LPC_SYSCON->PRESETCTRL |= (0x1<<1);
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);

	//
  I2CFIFO.mtx.buf = txbuf;
 // I2CFIFO.stx.buf = txbuf;
  I2CFIFO.rx.buf = rxbuf;
  I2CFIFO.mtx.maxlen = txl;
 // I2CFIFO.stx.maxlen = txl;
  I2CFIFO.rx.maxlen = rxl;
  I2CFIFO.mtx.wp = I2CFIFO.mtx.rp = 0;
 // I2CFIFO.stx.wp = I2CFIFO.stx.rp = 0;
  I2CFIFO.rx.wp = I2CFIFO.rx.rp = 0;
	I2CMODE=config;

	//ピン設定
  LPC_IOCON->PIO0_4 &= ~0x3F;	/*  I2C I/O config */
  LPC_IOCON->PIO0_4 |= 0x01;		/* I2C SCL */
  LPC_IOCON->PIO0_5 &= ~0x3F;
  LPC_IOCON->PIO0_5 |= 0x01;		/* I2C SDA */
	if(fm>400){		//Fast Mode Plus ファーストモードプラス
		LPC_IOCON->PIO0_4 |= (0x2<<8);
		LPC_IOCON->PIO0_5 |= (0x2<<8);
	}
	//状態レジスタクリア
	LPC_I2C->CONCLR=(0x6C);

	//サイクルクロック設定
//	DL=SystemCoreClock/1000/fm/2;
//	LPC_I2C->SCLL=DL;
//	LPC_I2C->SCLH=DL;
	LPC_I2C->SCLL=0x180;
	LPC_I2C->SCLH=0x180;

	if(!(I2CMODE&1)){	//スレイブモード
		//アドレス設定

	}

	//割り込みモード有効
  NVIC_EnableIRQ(I2C_IRQn);
  LPC_I2C->CONSET |= 0x44;

}
void I2C_IRQHandler(void) {
	static uint8_t lp,tp;
	uint8_t StatValue;
	StatValue = LPC_I2C->STAT;
	switch(StatValue){

		case(0x00):	//バスエラー
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x08):	//STARTビット送信済み
		case(0x10):  //RepeatedSTARTビット送信済み
		if(I2CFIFO.mtx.buf[I2CFIFO.mtx.rp]&0x01){		//rモード
			LPC_I2C->DAT = I2CFIFO.mtx.buf[I2CFIFO.mtx.rp];
		}else{																					//tモード
			tp=2;
			lp=I2CFIFO.mtx.buf[(I2CFIFO.mtx.rp)%I2CFIFO.mtx.maxlen];
			LPC_I2C->DAT = I2CFIFO.mtx.buf[I2CFIFO.mtx.rp];
		}
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x18):	//アドレス書き込み送信済み
		lp=I2CFIFO.mtx.buf[(I2CFIFO.mtx.rp+tp++)%I2CFIFO.mtx.maxlen];
		LPC_I2C->DAT = lp;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x20):	//NOTACK対応
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x28):	//1バイト送信済み
		if(lp+1==tp){				//最終バイト送信済み
			I2CFIFO.mtx.rp=(I2CFIFO.mtx.rp+lp+2)%I2CFIFO.mtx.maxlen;
			LPC_I2C->CONSET |= 0x14;
			LPC_I2C->CONCLR |= 0x08;
		}else{							//次バイト送信
			LPC_I2C->DAT = I2CFIFO.mtx.buf[(I2CFIFO.mtx.rp+tp++)%I2CFIFO.mtx.maxlen];
			LPC_I2C->CONSET |= 0x04;
			LPC_I2C->CONCLR |= 0x08;
		}
		break;

		case(0x30):	//1バイト送信済み NOTACK受信済み
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;			//もう一回送信するかどうか
		break;

		case(0x38):	//送信失敗
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;

	//	マスタレシーバ
		case(0x40):	//スレイブアドレス読み取り送信済み
		tp=0;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x48): //NOTACK 返された-
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;			//I2Cの初期化のときに再度要求するか設定
		break;

		case(0x50):	//データ受信済み
		if(tp){		//データ受信
			I2CFIFO.rx.buf[(I2CFIFO.rx.wp+tp++)%I2CFIFO.rx.maxlen] = LPC_I2C->DAT;
		}else{		//データ長受信
			lp = LPC_I2C->DAT;
			if(lp==0){		//データ長が0のとき
				LPC_I2C->CONSET |= 0x14;
				LPC_I2C->CONCLR |= 0x08;
				break;
			}
			I2CFIFO.rx.buf[(I2CFIFO.rx.wp+tp++)%I2CFIFO.rx.maxlen] = lp;
		}

		if(lp==tp){	//次で最終バイト
			LPC_I2C->CONCLR |= 0x0C;
		}else{						//データ続きまーす。
			LPC_I2C->CONSET |= 0x04;
			LPC_I2C->CONCLR |= 0x08;
		}
		break;

		case(0x58):	//データ受信済み　NOTACK送信済み
		I2CFIFO.rx.buf[(I2CFIFO.rx.wp+tp++)%I2CFIFO.rx.maxlen] = LPC_I2C->DAT;
		I2CFIFO.rx.wp+=tp+1;
		I2CFIFO.rx.wp%=I2CFIFO.rx.maxlen;
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;
		break;

	//	スレーブレシーバ
		case(0x60):	//スレーブアドレス+書き込みを受信済み
		tp=0;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x68):	//マスタから都落ち　そして自分がよばれた
		tp=0;
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x70):	//ゼネラルコール受信済み
		tp=0;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x78):	//マスタから都落ち そしてゼネラルコール
		tp=0;
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x80):	//スレーブアドレスでデータ受信済み ACK送信済み
		if(tp==0){		//データ長受信
			lp= LPC_I2C->DAT;
			if(lp==0){
				LPC_I2C->CONSET |= 0x04;
				LPC_I2C->CONCLR |= 0x08;
				break;
			}
			I2CFIFO.rx.buf[I2CFIFO.rx.wp]  = lp;
		}
		if(tp++==lp){		//最終バイト受信完了
		I2CFIFO.rx.wp+=tp;
		I2CFIFO.rx.wp%=I2CFIFO.rx.maxlen;
			////////////////////////////モードによってはNOTACKを返す
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		}else{
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		}
		break;

		case(0x88):	//スレーブアドレスでデータ受信済み NOTACK送信済み
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x90):	//ゼネラルコールでデータ受信済み ACK送信済み
		if(tp==0){		//データ長受信
			lp= LPC_I2C->DAT;
			if(lp==0){
					////////////////////////////モードによってはNOTACKを返す
				LPC_I2C->CONSET |= 0x04;
				LPC_I2C->CONCLR |= 0x08;
				break;
			}
			I2CFIFO.rx.buf[I2CFIFO.rx.wp]  = lp;
		}
		if(tp++==lp){		//最終バイト受信完了
		I2CFIFO.rx.wp+=tp;
		I2CFIFO.rx.wp%=I2CFIFO.rx.maxlen;
			////////////////////////////モードによってはNOTACKを返す
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		}else{
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		}
		break;

		case(0x98):	//ゼネラルコールでデータ受信済み NOTACK送信済み
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0xA0):	//STOPビットまたはRepeatedSTART受信
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

	//スレーブトランスミッタ
		case(0xA8):	//スレーブアドレス＋読み取り受信 ACKを送信済み
		tp=0;
		if(I2CFIFO.stx.rp==I2CFIFO.stx.wp){		//送信バッファーに何もないとき
			LPC_I2C->DAT = 0;									//データ長0送信
		}else{
			LPC_I2C->DAT = I2CFIFO.stx.buf[I2CFIFO.stx.rp];
		}
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0xB0):	// マスタから都落ち スレーブアドレスで呼び出し
		tp=0;
		if(I2CFIFO.stx.rp==I2CFIFO.stx.wp){		//送信バッファーに何もないとき
			LPC_I2C->DAT = 0;									//データ長0送信
		}else{
			LPC_I2C->DAT = I2CFIFO.stx.buf[I2CFIFO.stx.rp];
		}
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0xB8):	// データを送信済み　ACKを受信済み
		LPC_I2C->DAT = I2CFIFO.stx.buf[(I2CFIFO.stx.rp+tp++)%I2CFIFO.stx.maxlen];
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		if(lp==tp){		//全データ送信完了
			I2CFIFO.stx.rp+=tp+1;
			I2CFIFO.stx.rp%=I2CFIFO.stx.maxlen;
		}
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0xC0):	// データを送信済み　NOTACKを受信済み
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0xC8):	// 最終データ送信済みデータを送信済み　ACKを受信済み
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;		////////ここに入れるべきかも
		break;

		}

		if(I2CFIFO.mtx.rp != I2CFIFO.mtx.wp)
			LPC_I2C->CONSET |= 0x20;

}

// 送信バッファチェック
short i2cm_tx_buff (void)
{
  short s;
  if ((s = (I2CFIFO.mtx.rp - I2CFIFO.mtx.wp)) <= 0)
    s += I2CFIFO.mtx.maxlen;
  return s - 1;
}
short i2cs_tx_buff (void)
{
  short s;
  if ((s = (I2CFIFO.stx.rp - I2CFIFO.stx.wp)) <= 0)
    s += I2CFIFO.stx.maxlen;
  return s - 1;
}
// 受信バッファチェック
short i2c_rx_buff (void)
{
  short s;
  if ((s = (I2CFIFO.rx.wp - I2CFIFO.rx.rp)) < 0)
		s += I2CFIFO.rx.maxlen;
  return s;
}

// 受信バッファクリア
void i2c_rx_purge (void)
{
  I2CFIFO.rx.wp = I2CFIFO.rx.rp = 0;
}

// 送信バッファクリア
void i2cm_tx_purge (void)
{
  I2CFIFO.mtx.wp = I2CFIFO.mtx.rp = 0;
}
void i2cs_tx_purge (void)
{
  I2CFIFO.stx.wp = I2CFIFO.stx.rp = 0;
}
//	一文字バッファーつめつめ
void i2cm_txd(char c){
  volatile short t;
  t = (I2CFIFO.mtx.wp + 1) % I2CFIFO.mtx.maxlen;
  while (t == I2CFIFO.mtx.rp) ;			//上書き待機
	I2CFIFO.mtx.buf[I2CFIFO.mtx.wp] = c;
	I2CFIFO.mtx.wp = t;
	LPC_I2C->CONSET |= 0x20;
}
void i2cs_txd(char c){
  volatile short t;
  t = (I2CFIFO.stx.wp + 1) % I2CFIFO.stx.maxlen;
  while (t == I2CFIFO.stx.rp) ;			//上書き待機
	I2CFIFO.stx.buf[I2CFIFO.stx.wp] = c;
	I2CFIFO.stx.wp = t;
//	LPC_I2C->CONSET |= 0x20;
}
// 一文字送信
void i2cm_putc (char ad,char s){
	i2cm_txd(ad<<1);
	i2cm_txd(1);
  i2cm_txd (s);
}
// データ送信
void i2cm_puts (char ad,char *st){
	short l=0;
	i2cm_txd(ad<<1);
	while (*st++)	l++;
	i2cm_txd(l);
  while (*st) {
    i2cm_txd (*st);
    if (*st++ == '\n') i2cm_txd ('\r');
  }
}
/*
void i2cs_txd (char *st){
	i2cm_putc(ad<<1);
  while (*st) {
    i2cm_putc (*st);
    if (*st++ == '\n') i2cm_putc ('\r');
  }
}

// データ受信
void i2cm_rxb(char ad){
	i2cm_putc(ad<<1);
}
*/
// 受信データバッファより1文字読み出し
char i2c_getc(void){
  char c=0;
  while (I2CFIFO.rx.rp == I2CFIFO.rx.wp) ;
//	if(I2CFIFO.rx.rp != I2CFIFO.rx.wp)
	c = I2CFIFO.rx.buf[I2CFIFO.rx.rp++];
  I2CFIFO.rx.rp %= I2CFIFO.rx.maxlen;
  return c;
}
// 受信データバッファより1データ読み出し
