//*****************************************************************************
//*****************************************************************************
//  FILENAME: PRS8_3.h
//   Version: 3.4, Updated on 2013/5/19 at 10:44:3
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: PRS8 User Module C Language interface file.
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PRS8_3_INCLUDE
#define PRS8_3_INCLUDE

#include <m8c.h>

#pragma fastcall16  PRS8_3_Start
#pragma fastcall16  PRS8_3_Stop
#pragma fastcall16  PRS8_3_WriteSeed
#pragma fastcall16  PRS8_3_WritePolynomial
#pragma fastcall16  PRS8_3_bReadPRS

//-------------------------------------------------
// Prototypes of the PRS8_3 API.
//-------------------------------------------------
extern void  PRS8_3_Start(void);
extern void  PRS8_3_Stop(void);
extern void  PRS8_3_WriteSeed(BYTE bSeed);
extern void  PRS8_3_WritePolynomial(BYTE bPolynomial);
extern BYTE  PRS8_3_bReadPRS(void);

//-------------------------------------------------
// Do not use! For backwards compatibility only.
#pragma fastcall16 bPRS8_3_ReadPRS
extern BYTE bPRS8_3_ReadPRS(void);
//-------------------------------------------------

//-------------------------------------------------
// Register Addresses for PRS8_3
//-------------------------------------------------
#pragma ioport  PRS8_3_CONTROL_REG: 0x02b                  //Control register LSB
BYTE            PRS8_3_CONTROL_REG;
#pragma ioport  PRS8_3_SHIFT_REG:   0x028                  //Shift register LSB
BYTE            PRS8_3_SHIFT_REG;
#pragma ioport  PRS8_3_POLY_REG:    0x029                  //Polynomial register LSB
BYTE            PRS8_3_POLY_REG;
#pragma ioport  PRS8_3_SEED_REG:    0x02a                  //Seed register LSB
BYTE            PRS8_3_SEED_REG;
#pragma ioport  PRS8_3_FUNC_REG:    0x128                  //Function register LSB
BYTE            PRS8_3_FUNC_REG;
#pragma ioport  PRS8_3_INPUT_REG:   0x129                  //Input register LSB
BYTE            PRS8_3_INPUT_REG;
#pragma ioport  PRS8_3_OUTPUT_REG:  0x12a                  //Output register LSB
BYTE            PRS8_3_OUTPUT_REG;

#endif
// end of file PRS8_3.h
