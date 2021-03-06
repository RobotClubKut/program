;  Generated by PSoC Designer 5.4.2946
;
; =============================================================================
; FILENAME: PSoCConfigTBL.asm
;  
; Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;  
; NOTES:
; Do not modify this file. It is generated by PSoC Designer each time the
; generate application function is run. The values of the parameters in this
; file can be modified by changing the values of the global parameters in the
; device editor.
;  
; =============================================================================
 
include "m8c.inc"
;  Personalization tables 
export LoadConfigTBL_ira2kai_Bank1
export LoadConfigTBL_ira2kai_Bank0
export LoadConfigTBL_ira2kai_Ordered
AREA lit(rom, rel)
LoadConfigTBL_ira2kai_Bank0:
;  Instance name PGA_1, User Module PGA
;       Instance name PGA_1, Block Name GAIN(ACB00)
	db		71h, feh		;PGA_1_GAIN_CR0(ACB00CR0)
	db		72h, 21h		;PGA_1_GAIN_CR1(ACB00CR1)
	db		73h, 20h		;PGA_1_GAIN_CR2(ACB00CR2)
	db		70h, 00h		;PGA_1_GAIN_CR3(ACB00CR3)
;  Instance name PGA_2, User Module PGA
;       Instance name PGA_2, Block Name GAIN(ACB01)
	db		75h, feh		;PGA_2_GAIN_CR0(ACB01CR0)
	db		76h, 21h		;PGA_2_GAIN_CR1(ACB01CR1)
	db		77h, 20h		;PGA_2_GAIN_CR2(ACB01CR2)
	db		74h, 00h		;PGA_2_GAIN_CR3(ACB01CR3)
;  Instance name PGA_3, User Module PGA
;       Instance name PGA_3, Block Name GAIN(ACB02)
	db		79h, feh		;PGA_3_GAIN_CR0(ACB02CR0)
	db		7ah, 21h		;PGA_3_GAIN_CR1(ACB02CR1)
	db		7bh, 20h		;PGA_3_GAIN_CR2(ACB02CR2)
	db		78h, 00h		;PGA_3_GAIN_CR3(ACB02CR3)
;  Instance name PWM16_1, User Module PWM16
;       Instance name PWM16_1, Block Name PWM16_LSB(DCB32)
	db		5bh, 00h		;PWM16_1_CONTROL_LSB_REG(DCB32CR0)
	db		59h, c0h		;PWM16_1_PERIOD_LSB_REG(DCB32DR1)
	db		5ah, 00h		;PWM16_1_COMPARE_LSB_REG(DCB32DR2)
;       Instance name PWM16_1, Block Name PWM16_MSB(DCB33)
	db		5fh, 00h		;PWM16_1_CONTROL_MSB_REG(DCB33CR0)
	db		5dh, 5dh		;PWM16_1_PERIOD_MSB_REG(DCB33DR1)
	db		5eh, 00h		;PWM16_1_COMPARE_MSB_REG(DCB33DR2)
;  Instance name PWM8_1, User Module PWM8
;       Instance name PWM8_1, Block Name PWM8(DBB11)
	db		37h, 00h		;PWM8_1_CONTROL_REG(DBB11CR0)
	db		35h, ffh		;PWM8_1_PERIOD_REG(DBB11DR1)
	db		36h, 00h		;PWM8_1_COMPARE_REG(DBB11DR2)
;  Instance name PWM8_2, User Module PWM8
;       Instance name PWM8_2, Block Name PWM8(DCB12)
	db		3bh, 00h		;PWM8_2_CONTROL_REG(DCB12CR0)
	db		39h, ffh		;PWM8_2_PERIOD_REG(DCB12DR1)
	db		3ah, 00h		;PWM8_2_COMPARE_REG(DCB12DR2)
;  Instance name PWM8_3, User Module PWM8
;       Instance name PWM8_3, Block Name PWM8(DBB21)
	db		47h, 00h		;PWM8_3_CONTROL_REG(DBB21CR0)
	db		45h, ffh		;PWM8_3_PERIOD_REG(DBB21DR1)
	db		46h, 00h		;PWM8_3_COMPARE_REG(DBB21DR2)
;  Instance name PWM8_4, User Module PWM8
;       Instance name PWM8_4, Block Name PWM8(DBB20)
	db		43h, 00h		;PWM8_4_CONTROL_REG(DBB20CR0)
	db		41h, ffh		;PWM8_4_PERIOD_REG(DBB20DR1)
	db		42h, 00h		;PWM8_4_COMPARE_REG(DBB20DR2)
;  Instance name PWM8_5, User Module PWM8
;       Instance name PWM8_5, Block Name PWM8(DBB31)
	db		57h, 00h		;PWM8_5_CONTROL_REG(DBB31CR0)
	db		55h, ffh		;PWM8_5_PERIOD_REG(DBB31DR1)
	db		56h, 00h		;PWM8_5_COMPARE_REG(DBB31DR2)
;  Instance name PWM8_6, User Module PWM8
;       Instance name PWM8_6, Block Name PWM8(DCB22)
	db		4bh, 00h		;PWM8_6_CONTROL_REG(DCB22CR0)
	db		49h, ffh		;PWM8_6_PERIOD_REG(DCB22DR1)
	db		4ah, 00h		;PWM8_6_COMPARE_REG(DCB22DR2)
;  Instance name TRIADC_1, User Module TRIADC
;       Instance name TRIADC_1, Block Name ADC1(ASC10)
	db		80h, 90h		;TRIADC_1_bfADC1cr0(ASC10CR0)
	db		81h, 00h		;TRIADC_1_bfADC1cr1(ASC10CR1)
	db		82h, 61h		;TRIADC_1_bfADC1cr2(ASC10CR2)
	db		83h, f0h		;TRIADC_1_bfADC1cr3(ASC10CR3)
;       Instance name TRIADC_1, Block Name ADC2(ASD11)
	db		84h, 90h		;TRIADC_1_bfADC2cr0(ASD11CR0)
	db		85h, 00h		;TRIADC_1_bfADC2cr1(ASD11CR1)
	db		86h, 60h		;TRIADC_1_bfADC2cr2(ASD11CR2)
	db		87h, f0h		;TRIADC_1_bfADC2cr3(ASD11CR3)
;       Instance name TRIADC_1, Block Name ADC3(ASC12)
	db		88h, 90h		;TRIADC_1_bfADC3cr0(ASC12CR0)
	db		89h, 00h		;TRIADC_1_bfADC3cr1(ASC12CR1)
	db		8ah, 60h		;TRIADC_1_bfADC3cr2(ASC12CR2)
	db		8bh, f0h		;TRIADC_1_bfADC3cr3(ASC12CR3)
;       Instance name TRIADC_1, Block Name CNT1(DBB00)
	db		23h, 00h		;TRIADC_1_bCounter1_CR0(DBB00CR0)
	db		21h, 00h		;TRIADC_1_bPeriod1(DBB00DR1)
	db		22h, 00h		;TRIADC_1_bCompare1(DBB00DR2)
;       Instance name TRIADC_1, Block Name CNT2(DCB03)
	db		2fh, 00h		;TRIADC_1_bCounter2_CR0(DCB03CR0)
	db		2dh, 00h		;TRIADC_1_bPeriod2(DCB03DR1)
	db		2eh, 00h		;TRIADC_1_bCompare2(DCB03DR2)
;       Instance name TRIADC_1, Block Name CNT3(DBB10)
	db		33h, 00h		;TRIADC_1_bCounter3_CR0(DBB10CR0)
	db		31h, 00h		;TRIADC_1_bPeriod3(DBB10DR1)
	db		32h, 00h		;TRIADC_1_bCompare3(DBB10DR2)
;       Instance name TRIADC_1, Block Name PWM16_LSB(DBB01)
	db		27h, 00h		;TRIADC_1_fPWM_LSB_CR0(DBB01CR0)
	db		25h, 00h		;TRIADC_1_bPWM_Period_LSB(DBB01DR1)
	db		26h, 00h		;TRIADC_1_bPWM_IntTime_LSB(DBB01DR2)
;       Instance name TRIADC_1, Block Name PWM16_MSB(DCB02)
	db		2bh, 00h		;TRIADC_1_fPWM_MSB_CR0(DCB02CR0)
	db		29h, 00h		;TRIADC_1_bPWM_Period_MSB(DCB02DR1)
	db		2ah, 00h		;TRIADC_1_bPWM_IntTime_MSB(DCB02DR2)
;  Global Register values Bank 0
	db		60h, 1ah		; AnalogColumnInputSelect register (AMX_IN)
	db		66h, 00h		; AnalogComparatorControl1 register (CMP_CR1)
	db		63h, 17h		; AnalogReferenceControl register (ARF_CR)
	db		65h, 00h		; AnalogSyncControl register (ASY_CR)
	db		e6h, 70h		; DecimatorControl_0 register (DEC_CR0)
	db		e7h, 00h		; DecimatorControl_1 register (DEC_CR1)
	db		d6h, 00h		; I2CConfig register (I2C_CFG)
	db		b0h, 00h		; Row_0_InputMux register (RDI0RI)
	db		b1h, 00h		; Row_0_InputSync register (RDI0SYN)
	db		b2h, 00h		; Row_0_LogicInputAMux register (RDI0IS)
	db		b3h, 33h		; Row_0_LogicSelect_0 register (RDI0LT0)
	db		b4h, 33h		; Row_0_LogicSelect_1 register (RDI0LT1)
	db		b5h, 00h		; Row_0_OutputDrive_0 register (RDI0SRO0)
	db		b6h, 00h		; Row_0_OutputDrive_1 register (RDI0SRO1)
	db		b8h, 55h		; Row_1_InputMux register (RDI1RI)
	db		b9h, 00h		; Row_1_InputSync register (RDI1SYN)
	db		bah, 10h		; Row_1_LogicInputAMux register (RDI1IS)
	db		bbh, 33h		; Row_1_LogicSelect_0 register (RDI1LT0)
	db		bch, 33h		; Row_1_LogicSelect_1 register (RDI1LT1)
	db		bdh, 11h		; Row_1_OutputDrive_0 register (RDI1SRO0)
	db		beh, 00h		; Row_1_OutputDrive_1 register (RDI1SRO1)
	db		c0h, 00h		; Row_2_InputMux register (RDI2RI)
	db		c1h, 00h		; Row_2_InputSync register (RDI2SYN)
	db		c2h, 20h		; Row_2_LogicInputAMux register (RDI2IS)
	db		c3h, 33h		; Row_2_LogicSelect_0 register (RDI2LT0)
	db		c4h, 33h		; Row_2_LogicSelect_1 register (RDI3LT1)
	db		c5h, 24h		; Row_2_OutputDrive_0 register (RDI2SRO0)
	db		c6h, 10h		; Row_2_OutputDrive_1 register (RDI2SRO1)
	db		c8h, 55h		; Row_3_InputMux register (RDI3RI)
	db		c9h, 00h		; Row_3_InputSync register (RDI3SYN)
	db		cah, 30h		; Row_3_LogicInputAMux register (RDI3IS)
	db		cbh, 33h		; Row_3_LogicSelect_0 register (RDI3LT0)
	db		cch, 33h		; Row_3_LogicSelect_1 register (RDI3LT1)
	db		cdh, 00h		; Row_3_OutputDrive_0 register (RDI3SRO0)
	db		ceh, 21h		; Row_3_OutputDrive_1 register (RDI3SRO1)
	db		6ch, 00h		; TMP_DR0 register (TMP_DR0)
	db		6dh, 00h		; TMP_DR1 register (TMP_DR1)
	db		6eh, 00h		; TMP_DR2 register (TMP_DR2)
	db		6fh, 00h		; TMP_DR3 register (TMP_DR3)
	db		ffh
LoadConfigTBL_ira2kai_Bank1:
;  Instance name PGA_1, User Module PGA
;       Instance name PGA_1, Block Name GAIN(ACB00)
;  Instance name PGA_2, User Module PGA
;       Instance name PGA_2, Block Name GAIN(ACB01)
;  Instance name PGA_3, User Module PGA
;       Instance name PGA_3, Block Name GAIN(ACB02)
;  Instance name PWM16_1, User Module PWM16
;       Instance name PWM16_1, Block Name PWM16_LSB(DCB32)
	db		58h, 11h		;PWM16_1_FUNC_LSB_REG(DCB32FN)
	db		59h, 16h		;PWM16_1_INPUT_LSB_REG(DCB32IN)
	db		5ah, 40h		;PWM16_1_OUTPUT_LSB_REG(DCB32OU)
;       Instance name PWM16_1, Block Name PWM16_MSB(DCB33)
	db		5ch, 39h		;PWM16_1_FUNC_MSB_REG(DCB33FN)
	db		5dh, 36h		;PWM16_1_INPUT_MSB_REG(DCB33IN)
	db		5eh, 46h		;PWM16_1_OUTPUT_MSB_REG(DCB33OU)
;  Instance name PWM8_1, User Module PWM8
;       Instance name PWM8_1, Block Name PWM8(DBB11)
	db		34h, 39h		;PWM8_1_FUNC_REG(DBB11FN)
	db		35h, 16h		;PWM8_1_INPUT_REG(DBB11IN)
	db		36h, 44h		;PWM8_1_OUTPUT_REG(DBB11OU)
;  Instance name PWM8_2, User Module PWM8
;       Instance name PWM8_2, Block Name PWM8(DCB12)
	db		38h, 39h		;PWM8_2_FUNC_REG(DCB12FN)
	db		39h, 16h		;PWM8_2_INPUT_REG(DCB12IN)
	db		3ah, 45h		;PWM8_2_OUTPUT_REG(DCB12OU)
;  Instance name PWM8_3, User Module PWM8
;       Instance name PWM8_3, Block Name PWM8(DBB21)
	db		44h, 39h		;PWM8_3_FUNC_REG(DBB21FN)
	db		45h, 16h		;PWM8_3_INPUT_REG(DBB21IN)
	db		46h, 44h		;PWM8_3_OUTPUT_REG(DBB21OU)
;  Instance name PWM8_4, User Module PWM8
;       Instance name PWM8_4, Block Name PWM8(DBB20)
	db		40h, 39h		;PWM8_4_FUNC_REG(DBB20FN)
	db		41h, 16h		;PWM8_4_INPUT_REG(DBA20IN)
	db		42h, 47h		;PWM8_4_OUTPUT_REG(DBA20OU)
;  Instance name PWM8_5, User Module PWM8
;       Instance name PWM8_5, Block Name PWM8(DBB31)
	db		54h, 39h		;PWM8_5_FUNC_REG(DBB31FN)
	db		55h, 16h		;PWM8_5_INPUT_REG(DBB31IN)
	db		56h, 47h		;PWM8_5_OUTPUT_REG(DBB31OU)
;  Instance name PWM8_6, User Module PWM8
;       Instance name PWM8_6, Block Name PWM8(DCB22)
	db		48h, 39h		;PWM8_6_FUNC_REG(DCB22FN)
	db		49h, 16h		;PWM8_6_INPUT_REG(DCB22IN)
	db		4ah, 45h		;PWM8_6_OUTPUT_REG(DCB22OU)
;  Instance name TRIADC_1, User Module TRIADC
;       Instance name TRIADC_1, Block Name ADC1(ASC10)
;       Instance name TRIADC_1, Block Name ADC2(ASD11)
;       Instance name TRIADC_1, Block Name ADC3(ASC12)
;       Instance name TRIADC_1, Block Name CNT1(DBB00)
	db		20h, 21h		;TRIADC_1_fCounter1FN(DBB00FN)
	db		21h, 45h		;TRIADC_1_fCounter1SL(DBB00IN)
	db		22h, 40h		;TRIADC_1_fCounter1OS(DBB00OU)
;       Instance name TRIADC_1, Block Name CNT2(DCB03)
	db		2ch, 21h		;TRIADC_1_fCounter2FN(DCB03FN)
	db		2dh, 55h		;TRIADC_1_fCounter2SL(DCB03IN)
	db		2eh, 40h		;TRIADC_1_fCounter2OS(DCB03OU)
;       Instance name TRIADC_1, Block Name CNT3(DBB10)
	db		30h, 21h		;TRIADC_1_fCounter3FN(DBB10FN)
	db		31h, 65h		;TRIADC_1_fCounter3SL(DBB10IN)
	db		32h, 40h		;TRIADC_1_fCounter3OS(DBB10OU)
;       Instance name TRIADC_1, Block Name PWM16_LSB(DBB01)
	db		24h, 01h		;TRIADC_1_bfPWM_LSB_FN(DBB01FN)
	db		25h, 15h		;TRIADC_1_(DBB01IN)
	db		26h, 40h		;TRIADC_1_(DBB01OU)
;       Instance name TRIADC_1, Block Name PWM16_MSB(DCB02)
	db		28h, 21h		;TRIADC_1_bfPWM_MSB_FN(DCB02FN)
	db		29h, 35h		;TRIADC_1_(DCB02IN)
	db		2ah, 40h		;TRIADC_1_(DCB02OU)
;  Global Register values Bank 1
	db		61h, 00h		; AnalogClockSelect1 register (CLK_CR1)
	db		69h, 00h		; AnalogClockSelect2 register (CLK_CR2)
	db		60h, 00h		; AnalogColumnClockSelect register (CLK_CR0)
	db		62h, 00h		; AnalogIOControl_0 register (ABF_CR0)
	db		67h, 33h		; AnalogLUTControl0 register (ALT_CR0)
	db		68h, 33h		; AnalogLUTControl1 register (ALT_CR1)
	db		63h, 00h		; AnalogModulatorControl_0 register (AMD_CR0)
	db		66h, 00h		; AnalogModulatorControl_1 register (AMD_CR1)
	db		d1h, 00h		; GlobalDigitalInterconnect_Drive_Even_Input register (GDI_E_IN)
	db		d3h, 00h		; GlobalDigitalInterconnect_Drive_Even_Output register (GDI_E_OU)
	db		d0h, 00h		; GlobalDigitalInterconnect_Drive_Odd_Input register (GDI_O_IN)
	db		d2h, 00h		; GlobalDigitalInterconnect_Drive_Odd_Output register (GDI_O_OU)
	db		e1h, 19h		; OscillatorControl_1 register (OSC_CR1)
	db		e2h, 00h		; OscillatorControl_2 register (OSC_CR2)
	db		dfh, ffh		; OscillatorControl_3 register (OSC_CR3)
	db		deh, 02h		; OscillatorControl_4 register (OSC_CR4)
	db		ddh, 00h		; OscillatorGlobalBusEnableControl register (OSC_GO_EN)
	db		e7h, 00h		; Type2Decimator_Control register (DEC_CR2)
	db		ffh
AREA psoc_config(rom, rel)
LoadConfigTBL_ira2kai_Ordered:
;  Ordered Global Register values
	M8C_SetBank0
	mov	reg[00h], 00h		; Port_0_Data register (PRT0DR)
	M8C_SetBank1
	mov	reg[00h], 04h		; Port_0_DriveMode_0 register (PRT0DM0)
	mov	reg[01h], fbh		; Port_0_DriveMode_1 register (PRT0DM1)
	M8C_SetBank0
	mov	reg[03h], fbh		; Port_0_DriveMode_2 register (PRT0DM2)
	mov	reg[02h], 04h		; Port_0_GlobalSelect register (PRT0GS)
	M8C_SetBank1
	mov	reg[02h], 00h		; Port_0_IntCtrl_0 register (PRT0IC0)
	mov	reg[03h], 00h		; Port_0_IntCtrl_1 register (PRT0IC1)
	M8C_SetBank0
	mov	reg[01h], 00h		; Port_0_IntEn register (PRT0IE)
	mov	reg[04h], 00h		; Port_1_Data register (PRT1DR)
	M8C_SetBank1
	mov	reg[04h], 01h		; Port_1_DriveMode_0 register (PRT1DM0)
	mov	reg[05h], 00h		; Port_1_DriveMode_1 register (PRT1DM1)
	M8C_SetBank0
	mov	reg[07h], 00h		; Port_1_DriveMode_2 register (PRT1DM2)
	mov	reg[06h], 01h		; Port_1_GlobalSelect register (PRT1GS)
	M8C_SetBank1
	mov	reg[06h], 00h		; Port_1_IntCtrl_0 register (PRT1IC0)
	mov	reg[07h], 00h		; Port_1_IntCtrl_1 register (PRT1IC1)
	M8C_SetBank0
	mov	reg[05h], 00h		; Port_1_IntEn register (PRT1IE)
	mov	reg[08h], 00h		; Port_2_Data register (PRT2DR)
	M8C_SetBank1
	mov	reg[08h], abh		; Port_2_DriveMode_0 register (PRT2DM0)
	mov	reg[09h], 54h		; Port_2_DriveMode_1 register (PRT2DM1)
	M8C_SetBank0
	mov	reg[0bh], 54h		; Port_2_DriveMode_2 register (PRT2DM2)
	mov	reg[0ah], abh		; Port_2_GlobalSelect register (PRT2GS)
	M8C_SetBank1
	mov	reg[0ah], 00h		; Port_2_IntCtrl_0 register (PRT2IC0)
	mov	reg[0bh], 00h		; Port_2_IntCtrl_1 register (PRT2IC1)
	M8C_SetBank0
	mov	reg[09h], 00h		; Port_2_IntEn register (PRT2IE)
	mov	reg[0ch], 00h		; Port_3_Data register (PRT3DR)
	M8C_SetBank1
	mov	reg[0ch], 00h		; Port_3_DriveMode_0 register (PRT3DM0)
	mov	reg[0dh], 00h		; Port_3_DriveMode_1 register (PRT3DM1)
	M8C_SetBank0
	mov	reg[0fh], 00h		; Port_3_DriveMode_2 register (PRT3DM2)
	mov	reg[0eh], 00h		; Port_3_GlobalSelect register (PRT3GS)
	M8C_SetBank1
	mov	reg[0eh], 00h		; Port_3_IntCtrl_0 register (PRT3IC0)
	mov	reg[0fh], 00h		; Port_3_IntCtrl_1 register (PRT3IC1)
	M8C_SetBank0
	mov	reg[0dh], 00h		; Port_3_IntEn register (PRT3IE)
	mov	reg[10h], 00h		; Port_4_Data register (PRT4DR)
	M8C_SetBank1
	mov	reg[10h], 00h		; Port_4_DriveMode_0 register (PRT4DM0)
	mov	reg[11h], 00h		; Port_4_DriveMode_1 register (PRT4DM1)
	M8C_SetBank0
	mov	reg[13h], 00h		; Port_4_DriveMode_2 register (PRT4DM2)
	mov	reg[12h], 00h		; Port_4_GlobalSelect register (PRT4GS)
	M8C_SetBank1
	mov	reg[12h], 00h		; Port_4_IntCtrl_0 register (PRT4IC0)
	mov	reg[13h], 00h		; Port_4_IntCtrl_1 register (PRT4IC1)
	M8C_SetBank0
	mov	reg[11h], 00h		; Port_4_IntEn register (PRT4IE)
	mov	reg[14h], 00h		; Port_5_Data register (PRT5DR)
	M8C_SetBank1
	mov	reg[14h], 00h		; Port_5_DriveMode_0 register (PRT5DM0)
	mov	reg[15h], 00h		; Port_5_DriveMode_1 register (PRT5DM1)
	M8C_SetBank0
	mov	reg[17h], 00h		; Port_5_DriveMode_2 register (PRT5DM2)
	mov	reg[16h], 00h		; Port_5_GlobalSelect register (PRT5GS)
	M8C_SetBank1
	mov	reg[16h], 00h		; Port_5_IntCtrl_0 register (PRT5IC0)
	mov	reg[17h], 00h		; Port_5_IntCtrl_1 register (PRT5IC1)
	M8C_SetBank0
	mov	reg[15h], 00h		; Port_5_IntEn register (PRT5IE)
	mov	reg[18h], 00h		; Port_6_Data register (PRT6DR)
	M8C_SetBank1
	mov	reg[18h], 00h		; Port_6_DriveMode_0 register (PRT6DM0)
	mov	reg[19h], 00h		; Port_6_DriveMode_1 register (PRT6DM1)
	M8C_SetBank0
	mov	reg[1bh], 00h		; Port_6_DriveMode_2 register (PRT6DM2)
	mov	reg[1ah], 00h		; Port_6_GlobalSelect register (PRT6GS)
	M8C_SetBank1
	mov	reg[1ah], 00h		; Port_6_IntCtrl_0 register (PRT6IC0)
	mov	reg[1bh], 00h		; Port_6_IntCtrl_1 register (PRT6IC1)
	M8C_SetBank0
	mov	reg[19h], 00h		; Port_6_IntEn register (PRT6IE)
	mov	reg[1ch], 00h		; Port_7_Data register (PRT7DR)
	M8C_SetBank1
	mov	reg[1ch], 00h		; Port_7_DriveMode_0 register (PRT7DM0)
	mov	reg[1dh], 00h		; Port_7_DriveMode_1 register (PRT7DM1)
	M8C_SetBank0
	mov	reg[1fh], 00h		; Port_7_DriveMode_2 register (PRT7DM2)
	mov	reg[1eh], 00h		; Port_7_GlobalSelect register (PRT7GS)
	M8C_SetBank1
	mov	reg[1eh], 00h		; Port_7_IntCtrl_0 register (PRT7IC0)
	mov	reg[1fh], 00h		; Port_7_IntCtrl_1 register (PRT7IC1)
	M8C_SetBank0
	mov	reg[1dh], 00h		; Port_7_IntEn register (PRT7IE)
	M8C_SetBank0
	ret


; PSoC Configuration file trailer PsocConfig.asm
