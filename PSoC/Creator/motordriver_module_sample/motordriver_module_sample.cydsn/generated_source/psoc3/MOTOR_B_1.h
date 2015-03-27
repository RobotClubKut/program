/*******************************************************************************
* File Name: MOTOR_B_1.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MOTOR_B_1_H) /* Pins MOTOR_B_1_H */
#define CY_PINS_MOTOR_B_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOTOR_B_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MOTOR_B_1_Write(uint8 value) ;
void    MOTOR_B_1_SetDriveMode(uint8 mode) ;
uint8   MOTOR_B_1_ReadDataReg(void) ;
uint8   MOTOR_B_1_Read(void) ;
uint8   MOTOR_B_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MOTOR_B_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MOTOR_B_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MOTOR_B_1_DM_RES_UP          PIN_DM_RES_UP
#define MOTOR_B_1_DM_RES_DWN         PIN_DM_RES_DWN
#define MOTOR_B_1_DM_OD_LO           PIN_DM_OD_LO
#define MOTOR_B_1_DM_OD_HI           PIN_DM_OD_HI
#define MOTOR_B_1_DM_STRONG          PIN_DM_STRONG
#define MOTOR_B_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MOTOR_B_1_MASK               MOTOR_B_1__MASK
#define MOTOR_B_1_SHIFT              MOTOR_B_1__SHIFT
#define MOTOR_B_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOTOR_B_1_PS                     (* (reg8 *) MOTOR_B_1__PS)
/* Data Register */
#define MOTOR_B_1_DR                     (* (reg8 *) MOTOR_B_1__DR)
/* Port Number */
#define MOTOR_B_1_PRT_NUM                (* (reg8 *) MOTOR_B_1__PRT) 
/* Connect to Analog Globals */                                                  
#define MOTOR_B_1_AG                     (* (reg8 *) MOTOR_B_1__AG)                       
/* Analog MUX bux enable */
#define MOTOR_B_1_AMUX                   (* (reg8 *) MOTOR_B_1__AMUX) 
/* Bidirectional Enable */                                                        
#define MOTOR_B_1_BIE                    (* (reg8 *) MOTOR_B_1__BIE)
/* Bit-mask for Aliased Register Access */
#define MOTOR_B_1_BIT_MASK               (* (reg8 *) MOTOR_B_1__BIT_MASK)
/* Bypass Enable */
#define MOTOR_B_1_BYP                    (* (reg8 *) MOTOR_B_1__BYP)
/* Port wide control signals */                                                   
#define MOTOR_B_1_CTL                    (* (reg8 *) MOTOR_B_1__CTL)
/* Drive Modes */
#define MOTOR_B_1_DM0                    (* (reg8 *) MOTOR_B_1__DM0) 
#define MOTOR_B_1_DM1                    (* (reg8 *) MOTOR_B_1__DM1)
#define MOTOR_B_1_DM2                    (* (reg8 *) MOTOR_B_1__DM2) 
/* Input Buffer Disable Override */
#define MOTOR_B_1_INP_DIS                (* (reg8 *) MOTOR_B_1__INP_DIS)
/* LCD Common or Segment Drive */
#define MOTOR_B_1_LCD_COM_SEG            (* (reg8 *) MOTOR_B_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOTOR_B_1_LCD_EN                 (* (reg8 *) MOTOR_B_1__LCD_EN)
/* Slew Rate Control */
#define MOTOR_B_1_SLW                    (* (reg8 *) MOTOR_B_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOTOR_B_1_PRTDSI__CAPS_SEL       (* (reg8 *) MOTOR_B_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOTOR_B_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOTOR_B_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOTOR_B_1_PRTDSI__OE_SEL0        (* (reg8 *) MOTOR_B_1__PRTDSI__OE_SEL0) 
#define MOTOR_B_1_PRTDSI__OE_SEL1        (* (reg8 *) MOTOR_B_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOTOR_B_1_PRTDSI__OUT_SEL0       (* (reg8 *) MOTOR_B_1__PRTDSI__OUT_SEL0) 
#define MOTOR_B_1_PRTDSI__OUT_SEL1       (* (reg8 *) MOTOR_B_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOTOR_B_1_PRTDSI__SYNC_OUT       (* (reg8 *) MOTOR_B_1__PRTDSI__SYNC_OUT) 


#if defined(MOTOR_B_1__INTSTAT)  /* Interrupt Registers */

    #define MOTOR_B_1_INTSTAT                (* (reg8 *) MOTOR_B_1__INTSTAT)
    #define MOTOR_B_1_SNAP                   (* (reg8 *) MOTOR_B_1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins MOTOR_B_1_H */


/* [] END OF FILE */
