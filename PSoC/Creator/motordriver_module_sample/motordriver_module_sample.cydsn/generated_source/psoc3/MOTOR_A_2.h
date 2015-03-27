/*******************************************************************************
* File Name: MOTOR_A_2.h  
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

#if !defined(CY_PINS_MOTOR_A_2_H) /* Pins MOTOR_A_2_H */
#define CY_PINS_MOTOR_A_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOTOR_A_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MOTOR_A_2_Write(uint8 value) ;
void    MOTOR_A_2_SetDriveMode(uint8 mode) ;
uint8   MOTOR_A_2_ReadDataReg(void) ;
uint8   MOTOR_A_2_Read(void) ;
uint8   MOTOR_A_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MOTOR_A_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MOTOR_A_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MOTOR_A_2_DM_RES_UP          PIN_DM_RES_UP
#define MOTOR_A_2_DM_RES_DWN         PIN_DM_RES_DWN
#define MOTOR_A_2_DM_OD_LO           PIN_DM_OD_LO
#define MOTOR_A_2_DM_OD_HI           PIN_DM_OD_HI
#define MOTOR_A_2_DM_STRONG          PIN_DM_STRONG
#define MOTOR_A_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MOTOR_A_2_MASK               MOTOR_A_2__MASK
#define MOTOR_A_2_SHIFT              MOTOR_A_2__SHIFT
#define MOTOR_A_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOTOR_A_2_PS                     (* (reg8 *) MOTOR_A_2__PS)
/* Data Register */
#define MOTOR_A_2_DR                     (* (reg8 *) MOTOR_A_2__DR)
/* Port Number */
#define MOTOR_A_2_PRT_NUM                (* (reg8 *) MOTOR_A_2__PRT) 
/* Connect to Analog Globals */                                                  
#define MOTOR_A_2_AG                     (* (reg8 *) MOTOR_A_2__AG)                       
/* Analog MUX bux enable */
#define MOTOR_A_2_AMUX                   (* (reg8 *) MOTOR_A_2__AMUX) 
/* Bidirectional Enable */                                                        
#define MOTOR_A_2_BIE                    (* (reg8 *) MOTOR_A_2__BIE)
/* Bit-mask for Aliased Register Access */
#define MOTOR_A_2_BIT_MASK               (* (reg8 *) MOTOR_A_2__BIT_MASK)
/* Bypass Enable */
#define MOTOR_A_2_BYP                    (* (reg8 *) MOTOR_A_2__BYP)
/* Port wide control signals */                                                   
#define MOTOR_A_2_CTL                    (* (reg8 *) MOTOR_A_2__CTL)
/* Drive Modes */
#define MOTOR_A_2_DM0                    (* (reg8 *) MOTOR_A_2__DM0) 
#define MOTOR_A_2_DM1                    (* (reg8 *) MOTOR_A_2__DM1)
#define MOTOR_A_2_DM2                    (* (reg8 *) MOTOR_A_2__DM2) 
/* Input Buffer Disable Override */
#define MOTOR_A_2_INP_DIS                (* (reg8 *) MOTOR_A_2__INP_DIS)
/* LCD Common or Segment Drive */
#define MOTOR_A_2_LCD_COM_SEG            (* (reg8 *) MOTOR_A_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOTOR_A_2_LCD_EN                 (* (reg8 *) MOTOR_A_2__LCD_EN)
/* Slew Rate Control */
#define MOTOR_A_2_SLW                    (* (reg8 *) MOTOR_A_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOTOR_A_2_PRTDSI__CAPS_SEL       (* (reg8 *) MOTOR_A_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOTOR_A_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOTOR_A_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOTOR_A_2_PRTDSI__OE_SEL0        (* (reg8 *) MOTOR_A_2__PRTDSI__OE_SEL0) 
#define MOTOR_A_2_PRTDSI__OE_SEL1        (* (reg8 *) MOTOR_A_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOTOR_A_2_PRTDSI__OUT_SEL0       (* (reg8 *) MOTOR_A_2__PRTDSI__OUT_SEL0) 
#define MOTOR_A_2_PRTDSI__OUT_SEL1       (* (reg8 *) MOTOR_A_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOTOR_A_2_PRTDSI__SYNC_OUT       (* (reg8 *) MOTOR_A_2__PRTDSI__SYNC_OUT) 


#if defined(MOTOR_A_2__INTSTAT)  /* Interrupt Registers */

    #define MOTOR_A_2_INTSTAT                (* (reg8 *) MOTOR_A_2__INTSTAT)
    #define MOTOR_A_2_SNAP                   (* (reg8 *) MOTOR_A_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins MOTOR_A_2_H */


/* [] END OF FILE */
