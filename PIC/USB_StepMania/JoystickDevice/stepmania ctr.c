#include "./USB/usb.h"
#include "HardwareProfile.h"
#include "./USB/usb_function_hid.h"

// コンフィグレーション
#pragma config CPUDIV = NOCLKDIV,USBDIV = OFF,PCLKEN = ON
#pragma config FOSC = HS,PLLEN = ON,HFOFST = OFF
#pragma config PWRTEN = ON,BOREN = OFF,MCLRE = OFF,BORV = OFF
#pragma config WDTEN = OFF,LVP = OFF,FCMEN = OFF,IESO = OFF
#pragma config CP0 = OFF,XINST = OFF

// USB関連バッファ,変数定義
#pragma udata usbram2
unsigned char ReceivedDataBuffer = 0;
unsigned char SendBuf[64];
#pragma udata
USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
BOOL blinkStatusValid = TRUE;

// グローバル変数定義
BYTE counter;
BOOL blinkDtatusValid;

// コマンド定数定義
typedef enum
{
	CHECK = 0x30,
	POUT  = 0x31,
	PIN   = 0x32,
	AIN   = 0x33,
	RESET = 0xFF
	
}TYPE_CMD;

// 関数プロトタイピング
void BlinkUSBStatus(void);
void ProcessIO(void);
void YourHighProorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);

// 割り込みベクタ定義
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = 0x08
void Remapped_High_ISR(void)
{
	_asm goto YourHighPriorityISRCode _endasm
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = 0x18
void Remapped_Low_ISR(void)
{
	_asm goto YourLowPriorityISRCode _endasm
}

// 割り込み処理関数
#pragma code
#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()
{
	USBDeviceTasks();
}
#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()
{
}

// メイン関数
#pragma code
void main(void)
{
	// IOピン初期設定
	ANSEL = 0x00;
	ANSELH= 0x00;
	TERISA = 0xFF;
	TERISB = 0x00;
	TERISC = 0x00;
	LATB = 0x00;
	LATC = 0x00;
	
	// USB関連
	USBDeviceInit();
	USBInHandle = 0;
	USBOutHandle = 0;
	blinkStatusValid = TRUE;
	USBDeviceAttach();
	
	// メインループ
	while(1)
	{
		// USB目印LED点滅
		if(blinkStatusValid)
			BlinkUSBStatus();
			
		// USB接続中なら送受信実行
		if((USBDeviceStatus >= CONFIGURED_STATE)&&(USBSuspendControl!=1))
			ProcessIO();
	} 
}

