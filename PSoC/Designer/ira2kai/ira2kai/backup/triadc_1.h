//*****************************************************************************
//*****************************************************************************
//  FILENAME:  TRIADC_1.h
//  Version: 2.20, Updated on 2013/5/19 at 10:44:42
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION:  TriADC User Module C Language interface file.
//-----------------------------------------------------------------------------
//      Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef TRIADC_1_INCLUDE
#define TRIADC_1_INCLUDE

#include <m8C.h>

//-------------------------------------------------
// Constants for TRIADC_1 API's.
//-------------------------------------------------
#define TRIADC_1_OFF            0
#define TRIADC_1_LOWPOWER       1
#define TRIADC_1_MEDPOWER       2
#define TRIADC_1_HIGHPOWER      3

#define TRIADC_1_bNUMBITS  0x08

//-------------------------------------------------
// Function fastcall16 Pragmas
//-------------------------------------------------
#pragma fastcall16 TRIADC_1_Start
#pragma fastcall16 TRIADC_1_SetPower
#pragma fastcall16 TRIADC_1_GetSamples
#pragma fastcall16 TRIADC_1_StopAD
#pragma fastcall16 TRIADC_1_Stop
#pragma fastcall16 TRIADC_1_fIsData
#pragma fastcall16 TRIADC_1_fIsDataAvailable
#pragma fastcall16 TRIADC_1_iGetData1
#pragma fastcall16 TRIADC_1_iGetData1ClearFlag
#pragma fastcall16 TRIADC_1_iGetData2
#pragma fastcall16 TRIADC_1_iGetData2ClearFlag
#pragma fastcall16 TRIADC_1_iGetData3
#pragma fastcall16 TRIADC_1_iGetData3ClearFlag
#pragma fastcall16 TRIADC_1_ClearFlag
#pragma fastcall16 TRIADC_1_SetResolution

//-------------------------------------------------
// Prototypes of the TRIADC_1 API.
//-------------------------------------------------
extern void TRIADC_1_Start(BYTE bPower);
extern void TRIADC_1_SetPower(BYTE bPower);
extern void TRIADC_1_GetSamples(BYTE bNumSamples);
extern void TRIADC_1_StopAD(void);
extern void TRIADC_1_Stop(void);
extern CHAR TRIADC_1_fIsData(void);
extern CHAR TRIADC_1_fIsDataAvailable(void);
extern INT  TRIADC_1_iGetData1(void);
extern INT  TRIADC_1_iGetData2(void);
extern INT  TRIADC_1_iGetData3(void);
extern INT  TRIADC_1_iGetData1ClearFlag(void);
extern INT  TRIADC_1_iGetData2ClearFlag(void);
extern INT  TRIADC_1_iGetData3ClearFlag(void);
extern void TRIADC_1_ClearFlag(void);
extern void TRIADC_1_SetResolution(BYTE bResolution);


//-------------------------------------------------
// Register Addresses for TRIADC_1
//-------------------------------------------------
// ADC1 Integrator Block Register Definitions
#pragma ioport  TRIADC_1_bfADC1cr0: 0x080
BYTE            TRIADC_1_bfADC1cr0;
#pragma ioport  TRIADC_1_bfADC1cr1: 0x081
BYTE            TRIADC_1_bfADC1cr1;
#pragma ioport  TRIADC_1_bfADC1cr2: 0x082
BYTE            TRIADC_1_bfADC1cr2;
#pragma ioport  TRIADC_1_bfADC1cr3: 0x083
BYTE            TRIADC_1_bfADC1cr3;

// ADC2 Integrator Block Register Definitions
#pragma ioport  TRIADC_1_bfADC2cr0: 0x084
BYTE            TRIADC_1_bfADC2cr0;
#pragma ioport  TRIADC_1_bfADC2cr1: 0x085
BYTE            TRIADC_1_bfADC2cr1;
#pragma ioport  TRIADC_1_bfADC2cr2: 0x086
BYTE            TRIADC_1_bfADC2cr2;
#pragma ioport  TRIADC_1_bfADC2cr3: 0x087
BYTE            TRIADC_1_bfADC2cr3;

// ADC3 Integrator Block Register Definitions
#pragma ioport  TRIADC_1_bfADC3cr0: 0x088
BYTE            TRIADC_1_bfADC3cr0;
#pragma ioport  TRIADC_1_bfADC3cr1: 0x089
BYTE            TRIADC_1_bfADC3cr1;
#pragma ioport  TRIADC_1_bfADC3cr2: 0x08a
BYTE            TRIADC_1_bfADC3cr2;
#pragma ioport  TRIADC_1_bfADC3cr3: 0x08b
BYTE            TRIADC_1_bfADC3cr3;

// Counter 1 Block Register Definitions
#pragma ioport  TRIADC_1_fCounter1FN:   0x120
BYTE            TRIADC_1_fCounter1FN;
#pragma ioport  TRIADC_1_fCounter1SL:   0x121
BYTE            TRIADC_1_fCounter1SL;
#pragma ioport  TRIADC_1_fCounter1OS:   0x122
BYTE            TRIADC_1_fCounter1OS;
#pragma ioport  TRIADC_1_bCount1:   0x020
BYTE            TRIADC_1_bCount1;
#pragma ioport  TRIADC_1_bPeriod1:  0x021
BYTE            TRIADC_1_bPeriod1;
#pragma ioport  TRIADC_1_bCompare1: 0x022
BYTE            TRIADC_1_bCompare1;
#pragma ioport  TRIADC_1_bCounter1_CR0: 0x023
BYTE            TRIADC_1_bCounter1_CR0;

// Counter 2 Block Register Definitions
#pragma ioport  TRIADC_1_fCounter2FN:   0x12c
BYTE            TRIADC_1_fCounter2FN;
#pragma ioport  TRIADC_1_fCounter2SL:   0x12d
BYTE            TRIADC_1_fCounter2SL;
#pragma ioport  TRIADC_1_fCounter2OS:   0x12e
BYTE            TRIADC_1_fCounter2OS;
#pragma ioport  TRIADC_1_bCount2:   0x02c
BYTE            TRIADC_1_bCount2;
#pragma ioport  TRIADC_1_bPeriod2:  0x02d
BYTE            TRIADC_1_bPeriod2;
#pragma ioport  TRIADC_1_bCompare2: 0x02e
BYTE            TRIADC_1_bCompare2;
#pragma ioport  TRIADC_1_bCounter2_CR0: 0x02f
BYTE            TRIADC_1_bCounter2_CR0;

// Counter 3 Block Register Definitions
#pragma ioport  TRIADC_1_fCounter3FN:   0x130
BYTE            TRIADC_1_fCounter3FN;
#pragma ioport  TRIADC_1_fCounter3SL:   0x131
BYTE            TRIADC_1_fCounter3SL;
#pragma ioport  TRIADC_1_fCounter3OS:   0x132
BYTE            TRIADC_1_fCounter3OS;
#pragma ioport  TRIADC_1_bCount3:   0x030
BYTE            TRIADC_1_bCount3;
#pragma ioport  TRIADC_1_bPeriod3:  0x031
BYTE            TRIADC_1_bPeriod3;
#pragma ioport  TRIADC_1_bCompare3: 0x032
BYTE            TRIADC_1_bCompare3;
#pragma ioport  TRIADC_1_bCounter3_CR0: 0x033
BYTE            TRIADC_1_bCounter3_CR0;


// PWM16 Block Register Definitions
#pragma ioport  TRIADC_1_bfPWM_LSB_FN:  0x124
BYTE            TRIADC_1_bfPWM_LSB_FN;
#pragma ioport  TRIADC_1_bfPWM_MSB_FN:  0x128
BYTE            TRIADC_1_bfPWM_MSB_FN;
#pragma ioport  TRIADC_1_fPWM_LSB_CR0:  0x027
BYTE            TRIADC_1_fPWM_LSB_CR0;
#pragma ioport  TRIADC_1_fPWM_MSB_CR0:  0x02b
BYTE            TRIADC_1_fPWM_MSB_CR0;
#pragma ioport  TRIADC_1_bPWM_Count_MSB:    0x028
BYTE            TRIADC_1_bPWM_Count_MSB;
#pragma ioport  TRIADC_1_bPWM_Count_LSB:    0x024
BYTE            TRIADC_1_bPWM_Count_LSB;
#pragma ioport  TRIADC_1_bPWM_Period_MSB:   0x029
BYTE            TRIADC_1_bPWM_Period_MSB;
#pragma ioport  TRIADC_1_bPWM_Period_LSB:   0x025
BYTE            TRIADC_1_bPWM_Period_LSB;
#pragma ioport  TRIADC_1_bPWM_IntTime_MSB:  0x02a
BYTE            TRIADC_1_bPWM_IntTime_MSB;
#pragma ioport  TRIADC_1_bPWM_IntTime_LSB:  0x026
BYTE            TRIADC_1_bPWM_IntTime_LSB;
#pragma ioport  TRIADC_1_bfPWM_LSB_FN:  0x124
BYTE            TRIADC_1_bfPWM_LSB_FN;
#pragma ioport  TRIADC_1_bfPWM_MSB_FN:  0x128
BYTE            TRIADC_1_bfPWM_MSB_FN;

#endif
// end of file TRIADC_1.h
