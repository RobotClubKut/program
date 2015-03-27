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
export LoadConfigTBL_catchrobo_dcm
AREA psoc_config(rom, rel)
LoadConfigTBL_catchrobo_dcm:
	M8C_SetBank0
;  Global Register values Bank 0
	mov	reg[60h], 28h		; AnalogColumnInputSelect register (AMX_IN)
	mov	reg[66h], 00h		; AnalogComparatorControl1 register (CMP_CR1)
	mov	reg[63h], 05h		; AnalogReferenceControl register (ARF_CR)
	mov	reg[65h], 00h		; AnalogSyncControl register (ASY_CR)
	mov	reg[e6h], 00h		; DecimatorControl_0 register (DEC_CR0)
	mov	reg[e7h], 00h		; DecimatorControl_1 register (DEC_CR1)
	mov	reg[d6h], 04h		; I2CConfig register (I2C_CFG)
	mov	reg[b0h], 00h		; Row_0_InputMux register (RDI0RI)
	mov	reg[b1h], 00h		; Row_0_InputSync register (RDI0SYN)
	mov	reg[b2h], 00h		; Row_0_LogicInputAMux register (RDI0IS)
	mov	reg[b3h], 33h		; Row_0_LogicSelect_0 register (RDI0LT0)
	mov	reg[b4h], 33h		; Row_0_LogicSelect_1 register (RDI0LT1)
	mov	reg[b5h], 00h		; Row_0_OutputDrive_0 register (RDI0SRO0)
	mov	reg[b6h], 00h		; Row_0_OutputDrive_1 register (RDI0SRO1)
	mov	reg[b8h], 55h		; Row_1_InputMux register (RDI1RI)
	mov	reg[b9h], 00h		; Row_1_InputSync register (RDI1SYN)
	mov	reg[bah], 10h		; Row_1_LogicInputAMux register (RDI1IS)
	mov	reg[bbh], 33h		; Row_1_LogicSelect_0 register (RDI1LT0)
	mov	reg[bch], 33h		; Row_1_LogicSelect_1 register (RDI1LT1)
	mov	reg[bdh], 00h		; Row_1_OutputDrive_0 register (RDI1SRO0)
	mov	reg[beh], 0ch		; Row_1_OutputDrive_1 register (RDI1SRO1)
	mov	reg[c0h], 00h		; Row_2_InputMux register (RDI2RI)
	mov	reg[c1h], 00h		; Row_2_InputSync register (RDI2SYN)
	mov	reg[c2h], 20h		; Row_2_LogicInputAMux register (RDI2IS)
	mov	reg[c3h], 33h		; Row_2_LogicSelect_0 register (RDI2LT0)
	mov	reg[c4h], 33h		; Row_2_LogicSelect_1 register (RDI3LT1)
	mov	reg[c5h], 30h		; Row_2_OutputDrive_0 register (RDI2SRO0)
	mov	reg[c6h], 00h		; Row_2_OutputDrive_1 register (RDI2SRO1)
	mov	reg[c8h], 55h		; Row_3_InputMux register (RDI3RI)
	mov	reg[c9h], 00h		; Row_3_InputSync register (RDI3SYN)
	mov	reg[cah], 30h		; Row_3_LogicInputAMux register (RDI3IS)
	mov	reg[cbh], 33h		; Row_3_LogicSelect_0 register (RDI3LT0)
	mov	reg[cch], 33h		; Row_3_LogicSelect_1 register (RDI3LT1)
	mov	reg[cdh], 00h		; Row_3_OutputDrive_0 register (RDI3SRO0)
	mov	reg[ceh], 20h		; Row_3_OutputDrive_1 register (RDI3SRO1)
	mov	reg[6ch], 00h		; TMP_DR0 register (TMP_DR0)
	mov	reg[6dh], 00h		; TMP_DR1 register (TMP_DR1)
	mov	reg[6eh], 00h		; TMP_DR2 register (TMP_DR2)
	mov	reg[6fh], 00h		; TMP_DR3 register (TMP_DR3)
;  Instance name EzI2Cs_1, User Module EzI2Cs
;  Instance name LCD_1, User Module LCD
;  Instance name MBM_1, User Module MBM
;  Instance name PRS32_1, User Module PRS32
;       Instance name PRS32_1, Block Name PRS32_ISB1(DBB11)
	mov	reg[37h], 00h		;PRS32_1_CONTROL_REG_ISB1(DBB11CR0)
	mov	reg[35h], 00h		;PRS32_1_POLY_REG_ISB1   (DBB11DR1)
	mov	reg[36h], 00h		;PRS32_1_SEED_REG_ISB1   (DBB11DR2)
;       Instance name PRS32_1, Block Name PRS32_ISB2(DCB12)
	mov	reg[3bh], 00h		;PRS32_1_CONTROL_REG_ISB2(DCB12CR0)
	mov	reg[39h], 00h		;PRS32_1_POLY_REG_ISB2   (DCB12DR1)
	mov	reg[3ah], 00h		;PRS32_1_SEED_REG_ISB2   (DCB12DR2)
;       Instance name PRS32_1, Block Name PRS32_LSB(DBB10)
	mov	reg[33h], 00h		;PRS32_1_CONTROL_REG_LSB (DBB10CR0)
	mov	reg[31h], 00h		;PRS32_1_POLY_REG_LSB    (DBB10DR1)
	mov	reg[32h], 00h		;PRS32_1_SEED_REG_LSB    (DBB10DR2)
;       Instance name PRS32_1, Block Name PRS32_MSB(DCB13)
	mov	reg[3fh], 00h		;PRS32_1_CONTROL_REG_MSB (DCB13CR0)
	mov	reg[3dh], 00h		;PRS32_1_POLY_REG_MSB    (DCB13DR1)
	mov	reg[3eh], 00h		;PRS32_1_SEED_REG_MSB    (DCB13DR2)
;  Instance name PRS32_2, User Module PRS32
;       Instance name PRS32_2, Block Name PRS32_ISB1(DBB21)
	mov	reg[47h], 00h		;PRS32_2_CONTROL_REG_ISB1(DBB21CR0)
	mov	reg[45h], 00h		;PRS32_2_POLY_REG_ISB1   (DBB21DR1)
	mov	reg[46h], 00h		;PRS32_2_SEED_REG_ISB1   (DBB21DR2)
;       Instance name PRS32_2, Block Name PRS32_ISB2(DCB22)
	mov	reg[4bh], 00h		;PRS32_2_CONTROL_REG_ISB2(DCB22CR0)
	mov	reg[49h], 00h		;PRS32_2_POLY_REG_ISB2   (DCB22DR1)
	mov	reg[4ah], 00h		;PRS32_2_SEED_REG_ISB2   (DCB22DR2)
;       Instance name PRS32_2, Block Name PRS32_LSB(DBB20)
	mov	reg[43h], 00h		;PRS32_2_CONTROL_REG_LSB (DBB20CR0)
	mov	reg[41h], 00h		;PRS32_2_POLY_REG_LSB    (DBB20DR1)
	mov	reg[42h], 00h		;PRS32_2_SEED_REG_LSB    (DBB20DR2)
;       Instance name PRS32_2, Block Name PRS32_MSB(DCB23)
	mov	reg[4fh], 00h		;PRS32_2_CONTROL_REG_MSB (DCB23CR0)
	mov	reg[4dh], 00h		;PRS32_2_POLY_REG_MSB    (DCB23DR1)
	mov	reg[4eh], 00h		;PRS32_2_SEED_REG_MSB    (DCB23DR2)
;  Instance name PRS32_3, User Module PRS32
;       Instance name PRS32_3, Block Name PRS32_ISB1(DBB31)
	mov	reg[57h], 00h		;PRS32_3_CONTROL_REG_ISB1(DBB31CR0)
	mov	reg[55h], 00h		;PRS32_3_POLY_REG_ISB1   (DBB31DR1)
	mov	reg[56h], 00h		;PRS32_3_SEED_REG_ISB1   (DBB31DR2)
;       Instance name PRS32_3, Block Name PRS32_ISB2(DCB32)
	mov	reg[5bh], 00h		;PRS32_3_CONTROL_REG_ISB2(DCB32CR0)
	mov	reg[59h], 00h		;PRS32_3_POLY_REG_ISB2   (DCB32DR1)
	mov	reg[5ah], 00h		;PRS32_3_SEED_REG_ISB2   (DCB32DR2)
;       Instance name PRS32_3, Block Name PRS32_LSB(DBB30)
	mov	reg[53h], 00h		;PRS32_3_CONTROL_REG_LSB (DBB30CR0)
	mov	reg[51h], 00h		;PRS32_3_POLY_REG_LSB    (DBB30DR1)
	mov	reg[52h], 00h		;PRS32_3_SEED_REG_LSB    (DBB30DR2)
;       Instance name PRS32_3, Block Name PRS32_MSB(DCB33)
	mov	reg[5fh], 00h		;PRS32_3_CONTROL_REG_MSB (DCB33CR0)
	mov	reg[5dh], 00h		;PRS32_3_POLY_REG_MSB    (DCB33DR1)
	mov	reg[5eh], 00h		;PRS32_3_SEED_REG_MSB    (DCB33DR2)
;  Instance name SHADOWREGS_1, User Module SHADOWREGS
;  Instance name SHADOWREGS_2, User Module SHADOWREGS
;  Instance name SHADOWREGS_3, User Module SHADOWREGS
;  Instance name Timer8_1, User Module Timer8
;       Instance name Timer8_1, Block Name TIMER8(DCB03)
	mov	reg[2fh], 04h		;Timer8_1_CONTROL_REG(DCB03CR0)
	mov	reg[2dh], f9h		;Timer8_1_PERIOD_REG(DCB03DR1)
	mov	reg[2eh], 00h		;Timer8_1_COMPARE_REG(DCB03DR2)
	M8C_SetBank1
;  Global Register values Bank 1
	mov	reg[61h], 00h		; AnalogClockSelect1 register (CLK_CR1)
	mov	reg[69h], 00h		; AnalogClockSelect2 register (CLK_CR2)
	mov	reg[60h], 00h		; AnalogColumnClockSelect register (CLK_CR0)
	mov	reg[62h], 00h		; AnalogIOControl_0 register (ABF_CR0)
	mov	reg[67h], 33h		; AnalogLUTControl0 register (ALT_CR0)
	mov	reg[68h], 33h		; AnalogLUTControl1 register (ALT_CR1)
	mov	reg[63h], 00h		; AnalogModulatorControl_0 register (AMD_CR0)
	mov	reg[66h], 00h		; AnalogModulatorControl_1 register (AMD_CR1)
	mov	reg[d1h], 00h		; GlobalDigitalInterconnect_Drive_Even_Input register (GDI_E_IN)
	mov	reg[d3h], 00h		; GlobalDigitalInterconnect_Drive_Even_Output register (GDI_E_OU)
	mov	reg[d0h], 00h		; GlobalDigitalInterconnect_Drive_Odd_Input register (GDI_O_IN)
	mov	reg[d2h], 00h		; GlobalDigitalInterconnect_Drive_Odd_Output register (GDI_O_OU)
	mov	reg[e1h], 53h		; OscillatorControl_1 register (OSC_CR1)
	mov	reg[e2h], 00h		; OscillatorControl_2 register (OSC_CR2)
	mov	reg[dfh], 3fh		; OscillatorControl_3 register (OSC_CR3)
	mov	reg[deh], 00h		; OscillatorControl_4 register (OSC_CR4)
	mov	reg[ddh], 00h		; OscillatorGlobalBusEnableControl register (OSC_GO_EN)
	mov	reg[e7h], 00h		; Type2Decimator_Control register (DEC_CR2)
;  Instance name EzI2Cs_1, User Module EzI2Cs
;  Instance name LCD_1, User Module LCD
;  Instance name MBM_1, User Module MBM
;  Instance name PRS32_1, User Module PRS32
;       Instance name PRS32_1, Block Name PRS32_ISB1(DBB11)
	mov	reg[34h], 0ah		;PRS32_1_FUNC_REG_ISB1   (DBB11FN)
	mov	reg[35h], 35h		;PRS32_1_INPUT_REG_ISB1  (DBB11IN)
	mov	reg[36h], 40h		;PRS32_1_OUTPUT_REG_ISB1 (DBB11OU)
;       Instance name PRS32_1, Block Name PRS32_ISB2(DCB12)
	mov	reg[38h], 0ah		;PRS32_1_FUNC_REG_ISB2   (DCB12FN)
	mov	reg[39h], 35h		;PRS32_1_INPUT_REG_ISB2  (DCB12IN)
	mov	reg[3ah], 40h		;PRS32_1_OUTPUT_REG_ISB2 (DCB12OU)
;       Instance name PRS32_1, Block Name PRS32_LSB(DBB10)
	mov	reg[30h], 0ah		;PRS32_1_FUNC_REG_LSB    (DBB10FN)
	mov	reg[31h], 05h		;PRS32_1_INPUT_REG_LSB   (DBB10IN)
	mov	reg[32h], 40h		;PRS32_1_OUTPUT_REG_LSB  (DBB10OU)
;       Instance name PRS32_1, Block Name PRS32_MSB(DCB13)
	mov	reg[3ch], 2ah		;PRS32_1_FUNC_REG_MSB    (DCB13FN)
	mov	reg[3dh], 35h		;PRS32_1_INPUT_REG_MSB   (DCB13IN)
	mov	reg[3eh], 70h		;PRS32_1_OUTPUT_REG_MSB  (DCB13OU)
;  Instance name PRS32_2, User Module PRS32
;       Instance name PRS32_2, Block Name PRS32_ISB1(DBB21)
	mov	reg[44h], 0ah		;PRS32_2_FUNC_REG_ISB1   (DBB21FN)
	mov	reg[45h], 35h		;PRS32_2_INPUT_REG_ISB1  (DBB21IN)
	mov	reg[46h], 40h		;PRS32_2_OUTPUT_REG_ISB1 (DBB21OU)
;       Instance name PRS32_2, Block Name PRS32_ISB2(DCB22)
	mov	reg[48h], 0ah		;PRS32_2_FUNC_REG_ISB2   (DCB22FN)
	mov	reg[49h], 35h		;PRS32_2_INPUT_REG_ISB2  (DCB22IN)
	mov	reg[4ah], 40h		;PRS32_2_OUTPUT_REG_ISB2 (DCB22OU)
;       Instance name PRS32_2, Block Name PRS32_LSB(DBB20)
	mov	reg[40h], 0ah		;PRS32_2_FUNC_REG_LSB    (DBB20FN)
	mov	reg[41h], 05h		;PRS32_2_INPUT_REG_LSB   (DBA20IN)
	mov	reg[42h], 40h		;PRS32_2_OUTPUT_REG_LSB  (DBA20OU)
;       Instance name PRS32_2, Block Name PRS32_MSB(DCB23)
	mov	reg[4ch], 2ah		;PRS32_2_FUNC_REG_MSB    (DCB23FN)
	mov	reg[4dh], 35h		;PRS32_2_INPUT_REG_MSB   (DCB23IN)
	mov	reg[4eh], 68h		;PRS32_2_OUTPUT_REG_MSB  (DCB23OU)
;  Instance name PRS32_3, User Module PRS32
;       Instance name PRS32_3, Block Name PRS32_ISB1(DBB31)
	mov	reg[54h], 0ah		;PRS32_3_FUNC_REG_ISB1   (DBB31FN)
	mov	reg[55h], 35h		;PRS32_3_INPUT_REG_ISB1  (DBB31IN)
	mov	reg[56h], 40h		;PRS32_3_OUTPUT_REG_ISB1 (DBB31OU)
;       Instance name PRS32_3, Block Name PRS32_ISB2(DCB32)
	mov	reg[58h], 0ah		;PRS32_3_FUNC_REG_ISB2   (DCB32FN)
	mov	reg[59h], 35h		;PRS32_3_INPUT_REG_ISB2  (DCB32IN)
	mov	reg[5ah], 40h		;PRS32_3_OUTPUT_REG_ISB2 (DCB32OU)
;       Instance name PRS32_3, Block Name PRS32_LSB(DBB30)
	mov	reg[50h], 0ah		;PRS32_3_FUNC_REG_LSB    (DBB30FN)
	mov	reg[51h], 05h		;PRS32_3_INPUT_REG_LSB   (DBB30IN)
	mov	reg[52h], 40h		;PRS32_3_OUTPUT_REG_LSB  (DBB30OU)
;       Instance name PRS32_3, Block Name PRS32_MSB(DCB33)
	mov	reg[5ch], 2ah		;PRS32_3_FUNC_REG_MSB    (DCB33FN)
	mov	reg[5dh], 35h		;PRS32_3_INPUT_REG_MSB   (DCB33IN)
	mov	reg[5eh], 78h		;PRS32_3_OUTPUT_REG_MSB  (DCB33OU)
;  Instance name SHADOWREGS_1, User Module SHADOWREGS
;  Instance name SHADOWREGS_2, User Module SHADOWREGS
;  Instance name SHADOWREGS_3, User Module SHADOWREGS
;  Instance name Timer8_1, User Module Timer8
;       Instance name Timer8_1, Block Name TIMER8(DCB03)
	mov	reg[2ch], 20h		;Timer8_1_FUNC_REG(DCB03FN)
	mov	reg[2dh], 01h		;Timer8_1_INPUT_REG(DCB03IN)
	mov	reg[2eh], 40h		;Timer8_1_OUTPUT_REG(DCB03OU)
	M8C_SetBank0
;  Ordered Global Register values
	M8C_SetBank0
	mov	reg[00h], 00h		; Port_0_Data register (PRT0DR)
	M8C_SetBank1
	mov	reg[00h], ffh		; Port_0_DriveMode_0 register (PRT0DM0)
	mov	reg[01h], 00h		; Port_0_DriveMode_1 register (PRT0DM1)
	M8C_SetBank0
	mov	reg[03h], 00h		; Port_0_DriveMode_2 register (PRT0DM2)
	mov	reg[02h], 80h		; Port_0_GlobalSelect register (PRT0GS)
	M8C_SetBank1
	mov	reg[02h], 00h		; Port_0_IntCtrl_0 register (PRT0IC0)
	mov	reg[03h], 00h		; Port_0_IntCtrl_1 register (PRT0IC1)
	M8C_SetBank0
	mov	reg[01h], 00h		; Port_0_IntEn register (PRT0IE)
	mov	reg[04h], a0h		; Port_1_Data register (PRT1DR)
	M8C_SetBank1
	mov	reg[04h], fch		; Port_1_DriveMode_0 register (PRT1DM0)
	mov	reg[05h], a3h		; Port_1_DriveMode_1 register (PRT1DM1)
	M8C_SetBank0
	mov	reg[07h], a0h		; Port_1_DriveMode_2 register (PRT1DM2)
	mov	reg[06h], 44h		; Port_1_GlobalSelect register (PRT1GS)
	M8C_SetBank1
	mov	reg[06h], 00h		; Port_1_IntCtrl_0 register (PRT1IC0)
	mov	reg[07h], 00h		; Port_1_IntCtrl_1 register (PRT1IC1)
	M8C_SetBank0
	mov	reg[05h], 00h		; Port_1_IntEn register (PRT1IE)
	mov	reg[08h], 00h		; Port_2_Data register (PRT2DR)
	M8C_SetBank1
	mov	reg[08h], efh		; Port_2_DriveMode_0 register (PRT2DM0)
	mov	reg[09h], 10h		; Port_2_DriveMode_1 register (PRT2DM1)
	M8C_SetBank0
	mov	reg[0bh], 10h		; Port_2_DriveMode_2 register (PRT2DM2)
	mov	reg[0ah], a2h		; Port_2_GlobalSelect register (PRT2GS)
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