/*******************************************************************************
* File Name: Motor_1_r.h  
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

#if !defined(CY_PINS_Motor_1_r_H) /* Pins Motor_1_r_H */
#define CY_PINS_Motor_1_r_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Motor_1_r_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Motor_1_r_Write(uint8 value) ;
void    Motor_1_r_SetDriveMode(uint8 mode) ;
uint8   Motor_1_r_ReadDataReg(void) ;
uint8   Motor_1_r_Read(void) ;
uint8   Motor_1_r_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Motor_1_r_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Motor_1_r_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Motor_1_r_DM_RES_UP          PIN_DM_RES_UP
#define Motor_1_r_DM_RES_DWN         PIN_DM_RES_DWN
#define Motor_1_r_DM_OD_LO           PIN_DM_OD_LO
#define Motor_1_r_DM_OD_HI           PIN_DM_OD_HI
#define Motor_1_r_DM_STRONG          PIN_DM_STRONG
#define Motor_1_r_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Motor_1_r_MASK               Motor_1_r__MASK
#define Motor_1_r_SHIFT              Motor_1_r__SHIFT
#define Motor_1_r_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Motor_1_r_PS                     (* (reg8 *) Motor_1_r__PS)
/* Data Register */
#define Motor_1_r_DR                     (* (reg8 *) Motor_1_r__DR)
/* Port Number */
#define Motor_1_r_PRT_NUM                (* (reg8 *) Motor_1_r__PRT) 
/* Connect to Analog Globals */                                                  
#define Motor_1_r_AG                     (* (reg8 *) Motor_1_r__AG)                       
/* Analog MUX bux enable */
#define Motor_1_r_AMUX                   (* (reg8 *) Motor_1_r__AMUX) 
/* Bidirectional Enable */                                                        
#define Motor_1_r_BIE                    (* (reg8 *) Motor_1_r__BIE)
/* Bit-mask for Aliased Register Access */
#define Motor_1_r_BIT_MASK               (* (reg8 *) Motor_1_r__BIT_MASK)
/* Bypass Enable */
#define Motor_1_r_BYP                    (* (reg8 *) Motor_1_r__BYP)
/* Port wide control signals */                                                   
#define Motor_1_r_CTL                    (* (reg8 *) Motor_1_r__CTL)
/* Drive Modes */
#define Motor_1_r_DM0                    (* (reg8 *) Motor_1_r__DM0) 
#define Motor_1_r_DM1                    (* (reg8 *) Motor_1_r__DM1)
#define Motor_1_r_DM2                    (* (reg8 *) Motor_1_r__DM2) 
/* Input Buffer Disable Override */
#define Motor_1_r_INP_DIS                (* (reg8 *) Motor_1_r__INP_DIS)
/* LCD Common or Segment Drive */
#define Motor_1_r_LCD_COM_SEG            (* (reg8 *) Motor_1_r__LCD_COM_SEG)
/* Enable Segment LCD */
#define Motor_1_r_LCD_EN                 (* (reg8 *) Motor_1_r__LCD_EN)
/* Slew Rate Control */
#define Motor_1_r_SLW                    (* (reg8 *) Motor_1_r__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Motor_1_r_PRTDSI__CAPS_SEL       (* (reg8 *) Motor_1_r__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Motor_1_r_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Motor_1_r__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Motor_1_r_PRTDSI__OE_SEL0        (* (reg8 *) Motor_1_r__PRTDSI__OE_SEL0) 
#define Motor_1_r_PRTDSI__OE_SEL1        (* (reg8 *) Motor_1_r__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Motor_1_r_PRTDSI__OUT_SEL0       (* (reg8 *) Motor_1_r__PRTDSI__OUT_SEL0) 
#define Motor_1_r_PRTDSI__OUT_SEL1       (* (reg8 *) Motor_1_r__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Motor_1_r_PRTDSI__SYNC_OUT       (* (reg8 *) Motor_1_r__PRTDSI__SYNC_OUT) 


#if defined(Motor_1_r__INTSTAT)  /* Interrupt Registers */

    #define Motor_1_r_INTSTAT                (* (reg8 *) Motor_1_r__INTSTAT)
    #define Motor_1_r_SNAP                   (* (reg8 *) Motor_1_r__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Motor_1_r_H */


/* [] END OF FILE */
