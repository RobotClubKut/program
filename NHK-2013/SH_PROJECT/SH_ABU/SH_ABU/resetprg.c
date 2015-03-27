/***********************************************************************/
/*                                                                     */
/*  FILE        :resetprg.c                                            */
/*  DATE        :Sun, Jan 06, 2013                                     */
/*  DESCRIPTION :Reset Program                                         */
/*  CPU TYPE    :SH7125                                                */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.18).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/***********************************************************************/
/*********************************************************************
*
* Device     : SH-1
*
* File Name  : resetprg.c
*
* Abstract   : Initialize for C/C++ language.
*
* History    : 1.00  (2007-02-15)
*              1.10  (2010-06-22)
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2007 (2010) Renesas Electronics Corporation and
* Renesas Solutions Corp. All rights reserved.
*
*********************************************************************/

#include	<machine.h>
#include	<_h_c_lib.h>
//#include	<stddef.h>					// Remove the comment when you use errno
//#include 	<stdlib.h>					// Remove the comment when you use rand()
#include	"typedefine.h"
#include	"stacksct.h"

#define SR_Init    0x000000F0
#define INT_OFFSET 0x10

extern _UINT INT_Vectors;

#ifdef __cplusplus
extern "C" {
#endif
void PowerON_Reset_PC(void);
void Manual_Reset_PC(void);
void main(void);
#ifdef __cplusplus
}
#endif

//#ifdef __cplusplus				// Enable I/O in the application(both SIM I/O and hardware I/O)
//extern "C" {
//#endif
//extern void _INIT_IOLIB(void);
//extern void _CLOSEALL(void);
//#ifdef __cplusplus
//}
//#endif

//extern void srand(_UINT);		// Remove the comment when you use rand()
//extern _SBYTE *_s1ptr;				// Remove the comment when you use strtok()
		
//#ifdef __cplusplus				// Use Hardware Setup
//extern "C" {
//#endif
//extern void HardwareSetup(void);
//#ifdef __cplusplus
//}
//#endif
	
//#ifdef __cplusplus			// Remove the comment when you use global class object
//extern "C" {					// Sections C$INIT and C$END will be generated
//#endif
//extern void _CALL_INIT(void);
//extern void _CALL_END(void);
//#ifdef __cplusplus
//}
//#endif

#pragma section ResetPRG

#pragma entry PowerON_Reset_PC

void PowerON_Reset_PC(void)
{
	set_vbr((void *)((_UBYTE *)&INT_Vectors - INT_OFFSET));

//	HardwareSetup();				// Use Hardware Setup

	_INITSCT();

//	_CALL_INIT();					// Remove the comment when you use global class object

//	_INIT_IOLIB();					// Enable I/O in the application(both SIM I/O and hardware I/O)

//	errno=0;						// Remove the comment when you use errno
//	srand((_UINT)1);					// Remove the comment when you use rand()
//	_s1ptr=NULL;					// Remove the comment when you use strtok()

	set_cr(SR_Init);

	main();

//	_CLOSEALL();					// Close I/O in the application(both SIM I/O andhardware I/O)

//	_CALL_END();					// Remove the comment when you use global class object

	while(1);
}

//#pragma entry Manual_Reset_PC		// Remove the comment when you use Manual Reset
void Manual_Reset_PC(void)	
{
}
