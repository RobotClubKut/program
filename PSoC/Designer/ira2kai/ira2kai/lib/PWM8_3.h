//*****************************************************************************
//*****************************************************************************
//  FILENAME: PWM8_3.h
//   Version: 2.60, Updated on 2013/5/19 at 10:44:7
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: PWM8 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PWM8_3_INCLUDE
#define PWM8_3_INCLUDE

#include <m8c.h>

#pragma fastcall16 PWM8_3_EnableInt
#pragma fastcall16 PWM8_3_DisableInt
#pragma fastcall16 PWM8_3_Start
#pragma fastcall16 PWM8_3_Stop
#pragma fastcall16 PWM8_3_bReadCounter              // Read  DR0
#pragma fastcall16 PWM8_3_WritePeriod               // Write DR1
#pragma fastcall16 PWM8_3_bReadPulseWidth           // Read  DR2
#pragma fastcall16 PWM8_3_WritePulseWidth           // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 bPWM8_3_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 bPWM8_3_ReadPulseWidth           // Read  DR2 (Deprecated)


//-------------------------------------------------
// Prototypes of the PWM8_3 API.
//-------------------------------------------------

extern void PWM8_3_EnableInt(void);                        // Proxy Class 1
extern void PWM8_3_DisableInt(void);                       // Proxy Class 1
extern void PWM8_3_Start(void);                            // Proxy Class 1
extern void PWM8_3_Stop(void);                             // Proxy Class 1
extern BYTE PWM8_3_bReadCounter(void);                     // Proxy Class 2
extern void PWM8_3_WritePeriod(BYTE bPeriod);              // Proxy Class 1
extern BYTE PWM8_3_bReadPulseWidth(void);                  // Proxy Class 1
extern void PWM8_3_WritePulseWidth(BYTE bPulseWidth);      // Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern BYTE bPWM8_3_ReadCounter(void);            // Deprecated
extern BYTE bPWM8_3_ReadPulseWidth(void);         // Deprecated


//--------------------------------------------------
// Constants for PWM8_3 API's.
//--------------------------------------------------

#define PWM8_3_CONTROL_REG_START_BIT           ( 0x01 )
#define PWM8_3_INT_REG_ADDR                    ( 0x0df )
#define PWM8_3_INT_MASK                        ( 0x02 )


//--------------------------------------------------
// Constants for PWM8_3 user defined values
//--------------------------------------------------

#define PWM8_3_PERIOD                          ( 0xff )
#define PWM8_3_PULSE_WIDTH                     ( 0x00 )


//-------------------------------------------------
// Register Addresses for PWM8_3
//-------------------------------------------------

#pragma ioport  PWM8_3_COUNTER_REG: 0x044                  //DR0 Count register
BYTE            PWM8_3_COUNTER_REG;
#pragma ioport  PWM8_3_PERIOD_REG:  0x045                  //DR1 Period register
BYTE            PWM8_3_PERIOD_REG;
#pragma ioport  PWM8_3_COMPARE_REG: 0x046                  //DR2 Compare register
BYTE            PWM8_3_COMPARE_REG;
#pragma ioport  PWM8_3_CONTROL_REG: 0x047                  //Control register
BYTE            PWM8_3_CONTROL_REG;
#pragma ioport  PWM8_3_FUNC_REG:    0x144                  //Function register
BYTE            PWM8_3_FUNC_REG;
#pragma ioport  PWM8_3_INPUT_REG:   0x145                  //Input register
BYTE            PWM8_3_INPUT_REG;
#pragma ioport  PWM8_3_OUTPUT_REG:  0x146                  //Output register
BYTE            PWM8_3_OUTPUT_REG;
#pragma ioport  PWM8_3_INT_REG:       0x0df                //Interrupt Mask Register
BYTE            PWM8_3_INT_REG;


//-------------------------------------------------
// PWM8_3 Macro 'Functions'
//-------------------------------------------------

#define PWM8_3_Start_M \
   PWM8_3_CONTROL_REG |=  PWM8_3_CONTROL_REG_START_BIT

#define PWM8_3_Stop_M  \
   PWM8_3_CONTROL_REG &= ~PWM8_3_CONTROL_REG_START_BIT

#define PWM8_3_EnableInt_M   \
   M8C_EnableIntMask(PWM8_3_INT_REG, PWM8_3_INT_MASK)

#define PWM8_3_DisableInt_M  \
   M8C_DisableIntMask(PWM8_3_INT_REG, PWM8_3_INT_MASK)

#endif
// end of file PWM8_3.h
