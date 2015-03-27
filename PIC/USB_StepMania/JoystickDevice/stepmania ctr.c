#include "./USB/usb.h"
#include "HardwareProfile.h"
#include "./USB/usb_function_hid.h"

// �R���t�B�O���[�V����
#pragma config CPUDIV = NOCLKDIV,USBDIV = OFF,PCLKEN = ON
#pragma config FOSC = HS,PLLEN = ON,HFOFST = OFF
#pragma config PWRTEN = ON,BOREN = OFF,MCLRE = OFF,BORV = OFF
#pragma config WDTEN = OFF,LVP = OFF,FCMEN = OFF,IESO = OFF
#pragma config CP0 = OFF,XINST = OFF

// USB�֘A�o�b�t�@,�ϐ���`
#pragma udata usbram2
unsigned char ReceivedDataBuffer = 0;
unsigned char SendBuf[64];
#pragma udata
USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
BOOL blinkStatusValid = TRUE;

// �O���[�o���ϐ���`
BYTE counter;
BOOL blinkDtatusValid;

// �R�}���h�萔��`
typedef enum
{
	CHECK = 0x30,
	POUT  = 0x31,
	PIN   = 0x32,
	AIN   = 0x33,
	RESET = 0xFF
	
}TYPE_CMD;

// �֐��v���g�^�C�s���O
void BlinkUSBStatus(void);
void ProcessIO(void);
void YourHighProorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);

// ���荞�݃x�N�^��`
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

// ���荞�ݏ����֐�
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

// ���C���֐�
#pragma code
void main(void)
{
	// IO�s�������ݒ�
	ANSEL = 0x00;
	ANSELH= 0x00;
	TERISA = 0xFF;
	TERISB = 0x00;
	TERISC = 0x00;
	LATB = 0x00;
	LATC = 0x00;
	
	// USB�֘A
	USBDeviceInit();
	USBInHandle = 0;
	USBOutHandle = 0;
	blinkStatusValid = TRUE;
	USBDeviceAttach();
	
	// ���C�����[�v
	while(1)
	{
		// USB�ڈ�LED�_��
		if(blinkStatusValid)
			BlinkUSBStatus();
			
		// USB�ڑ����Ȃ瑗��M���s
		if((USBDeviceStatus >= CONFIGURED_STATE)&&(USBSuspendControl!=1))
			ProcessIO();
	} 
}

