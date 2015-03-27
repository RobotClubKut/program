/**************************************
	UART on ARM LPC1114			by nakach
**************************************/

/*-------------------------------------
使い方
	   まずグローバル変数で適当なサイズ(数バイト～数十バイト程度)の配列を2つ宣言し
   ます．
    char txb[10], rxb[10];
   次に通信したい通信速度と，先に宣言した変数とそのサイズを各初期化関数の引数に
	 与えます．
	 次の例は38400[bps]で通信するとしています．

   uart_init (br38400, txb, sizeof(txb), rxb, sizeof(rxb));

   これでSCIの初期化と送受信に使用するリングバッファのポインタが初期化されます．
	 また、配列のサイズがバッファーサイズとなります。
	 バッファ上書きしないよう待機する仕様になっています。
	 一度に大量に送信する場合は、それだけバッファーを大きくしてください。
-------------------------------------*/
typedef struct {
  struct {
    char  *buf;
    short wp;
    short rp;
    short maxlen;
  } tx;
  struct {
    char  *buf;
    short wp;
    short rp;
    short maxlen;
  } rx;
} UARTFIFO;

volatile UARTFIFO FIFO;


// SCI初期化
void uart_init (uint32_t baudrate, char *txbuf, short txl, char *rxbuf, short rxl)
{
  uint32_t DL,i;                                      	// ボーレート分周比の変数定義

  // 受信データ用変数初期化
  FIFO.tx.buf = txbuf;
  FIFO.rx.buf = rxbuf;
  FIFO.tx.maxlen = txl;
  FIFO.rx.maxlen = rxl;
  FIFO.tx.wp = FIFO.tx.rp = 0;
  FIFO.rx.wp = FIFO.rx.rp = 0;

  LPC_IOCON->PIO1_6 |= 0x01;                        	// RXD機能に設定(FUNC=001)
  LPC_IOCON->PIO1_7 |= 0x01;                        	// TXD機能に設定(FUNC=001)
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);             	//UARTへクロック供給
  LPC_SYSCON->UARTCLKDIV = 0x01;                    	//ボーレート・ジェネレータへクロック供給
  DL = (SystemCoreClock * LPC_SYSCON->SYSAHBCLKDIV) 	// ボーレート分周比の算出
     / (16 * baudrate * LPC_SYSCON->UARTCLKDIV);
  LPC_UART->LCR |= (1<<7);                          	//ディバイザ・ラッチ・アクセス有効（DLAB=1)
  LPC_UART->DLM = DL / 256;                         	//ボーレートの設定（U0DLM)
  LPC_UART->DLL = DL % 256;                         	// ボーレートの設定（U0DLL)
  LPC_UART->LCR &= ~(1<<7);                         	//ディバイザ・ラッチ・アクセス無効（DLAB=0)
  LPC_UART->LCR = 0x03;                             	//データのフォーマット設定
  LPC_UART->FCR = 0x07;                             	//入出力バッファの初期化
	LPC_UART->IER |= (0x01);														//受信割り込みオン
	NVIC_EnableIRQ(UART_IRQn);
	NVIC_SetPriority(UART_IRQn,1);

	for(i=0;;i++)if(i==1300) break;

}

// 送信バッファチェック
short uart_tx_buff (void)
{
  short s;
  if ((s = (FIFO.tx.rp - FIFO.tx.wp)) <= 0)
    s += FIFO.tx.maxlen;
  return s - 1;
}

// 受信バッファチェック
short uart_rx_buff (void)
{
  short s;
  if ((s = (FIFO.rx.wp - FIFO.rx.rp)) < 0)
		s += FIFO.rx.maxlen;
  return s;
}

// 受信バッファクリア
void uart_rx_purge (void)
{
	LPC_UART->IER &= ~(0x01);	
  FIFO.rx.wp = FIFO.rx.rp = 0;
	LPC_UART->IER |= (0x01);	
}

// 送信バッファクリア
void uart_tx_purge (void)
{
	LPC_UART->IER &= ~(0x01);	
  FIFO.tx.wp = FIFO.tx.rp = 0;
}

// 1バイト送信
void uart_putc (char c)
{
  volatile short t;

  t = (FIFO.tx.wp + 1) % FIFO.tx.maxlen;
  while (t == FIFO.tx.rp) ;			//上書き待機
	if(LPC_UART->IER&0x02){
		FIFO.tx.buf[FIFO.tx.wp] = c;
		FIFO.tx.wp = t;
	}
	else{
		LPC_UART->THR=c;
	}
	LPC_UART->IER |= (0x02);	
}

// テキスト送信 (nullターミネーション)
void uart_puts (char *st)
{
  while (*st) {
    uart_putc (*st);
    if (*st++ == '\n') uart_putc ('\r');
  }
}

// バイナリ列送信 (サイズ指定)
void uart_putsb (char *st, short l)
{
  short i;

  for (i = 0; i < l; i++) uart_putc (*st++);
}

// 受信データバッファより1文字読み出し
char uart_getc(void)
{
  char c=0;

  while (FIFO.rx.rp == FIFO.rx.wp) ;
//	if(FIFO.rx.rp != FIFO.rx.wp)
	c = FIFO.rx.buf[FIFO.rx.rp++];
  FIFO.rx.rp %= FIFO.rx.maxlen;
  return c;
}

// 文字列受信
short uart_gets (char *s, short len)
{
  short i = 0;
  char c;
  while (1) {
    c = uart_getc ();
    if ((c == '\n') || (c == '\r')) {
      s[i] = '\0'; if (i != 0) i++;
      uart_putc ('\n');
      break;
    } else if ((i > 0) && (c == '\b')) {
      uart_puts ("\b \b");
      i--;
    } else if ((i < len) && (i >= 0) && (c >= ' ') && (c <= '~')) {
      s[i++] = (char)c;
      uart_putc (c);
    } else uart_putc ('\a');
  }
  return i;
}
//	実行ファイルサイズ注意
#ifdef UART_USE_PRINTF
#include <stdio.h>
#include <stdarg.h>
void uart_printf(char *format, ...)
{
	va_list vl;
	char buf[FIFO.tx.maxlen};

	va_start(vl,format);
	vsprintf(buf,format,vl);

	return uart_puts(buf);
}
#endif

// 割り込み関数
void UART_IRQHandler(void)
{
	char c;
  volatile short t;
	uint8_t iir=(uint8_t)(0xf&LPC_UART->IIR);
			
  // 受信
  if (iir&0x4) {
    c = LPC_UART->RBR;
    t = (FIFO.rx.wp + 1) % FIFO.rx.maxlen;
    FIFO.rx.buf[FIFO.rx.wp] = c;
    if (t != FIFO.rx.rp) FIFO.rx.wp = t;
	LPC_GPIO1->DATA^=(1<<5);
  }
  // 送信
  if (iir&0x2) {
    if (FIFO.tx.wp != FIFO.tx.rp) {
      LPC_UART->THR = FIFO.tx.buf[FIFO.tx.rp++];
      FIFO.tx.rp %= FIFO.tx.maxlen;
    } else
      LPC_UART->IER &= ~(1<<1)	;	
  }
//	LPC_UART->LSR &= ~(0xF);
}

