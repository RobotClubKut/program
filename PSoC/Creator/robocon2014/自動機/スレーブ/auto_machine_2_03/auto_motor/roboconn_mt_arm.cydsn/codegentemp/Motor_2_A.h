/*******************************************************************************
* File Name: Motor_2_A.h  
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

#if !defined(CY_PINS_Motor_2_A_H) /* Pins Motor_2_A_H */
#define CY_PINS_Motor_2_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Motor_2_A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Motor_2_A_Write(uint8 value) ;
void    Motor_2_A_SetDriveMode(uint8 mode) ;
uint8   Motor_2_A_ReadDataReg(void) ;
uint8   Motor_2_A_Read(void) ;
uint8   Motor_2_A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Motor_2_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Motor_2_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Motor_2_A_DM_RES_UP          PIN_DM_RES_UP
#define Motor_2_A_DM_RES_DWN         PIN_DM_RES_DWN
#define Motor_2_A_DM_OD_LO           PIN_DM_OD_LO
#define Motor_2_A_DM_OD_HI           PIN_DM_OD_HI
#define Motor_2_A_DM_STRONG          PIN_DM_STRONG
#define Motor_2_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Motor_2_A_MASK               Motor_2_A__MASK
#define Motor_2_A_SHIFT              Motor_2_A__SHIFT
#define Motor_2_A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Motor_2_A_PS                     (* (reg8 *) Motor_2_A__PS)
/* Data Register */
#define Motor_2_A_DR                     (* (reg8 *) Motor_2_A__DR)
/* Port Number */
#define Motor_2_A_PRT_NUM                (* (reg8 *) Motor_2_A__PRT) 
/* Connect to Analog Globals */                                                  
#define Motor_2_A_AG                     (* (reg8 *) Motor_2_A__AG)                       
/* Analog MUX bux enable */
#define Motor_2_A_AMUX                   (* (reg8 *) Motor_2_A__AMUX) 
/* Bidirectional Enable */                                                        
#define Motor_2_A_BIE                    (* (reg8 *) Motor_2_A__BIE)
/* Bit-mask for Aliased Register Access */
#define Motor_2_A_BIT_MASK               (* (reg8 *) Motor_2_A__BIT_MASK)
/* Bypass Enable */
#define Motor_2_A_BYP                    (* (reg8 *) Motor_2_A__BYP)
/* Port wide control signals */                                                   
#define Motor_2_A_CTL                    (* (reg8 *) Motor_2_A__CTL)
/* Drive Modes */
#define Motor_2_A_DM0                    (* (reg8 *) Motor_2_A__DM0) 
#define Motor_2_A_DM1                    (* (reg8 *) Motor_2_A__DM1)
#define Motor_2_A_DM2                    (* (reg8 *) Motor_2_A__DM2) 
/* Input Buffer Disable Override */
#define Motor_2_A_INP_DIS                (* (reg8 *) Motor_2_A__INP_DIS)
/* LCD Common or Segment Drive */
#define Motor_2_A_LCD_COM_SEG            (* (reg8 *) Motor_2_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Motor_2_A_LCD_EN                 (* (reg8 *) Motor_2_A__LCD_EN)
/* Slew Rate Control */
#define Motor_2_A_SLW                    (* (reg8 *) Motor_2_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Motor_2_A_PRTDSI__CAPS_SEL       (* (reg8 *) Motor_2_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Motor_2_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Motor_2_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Motor_2_A_PRTDSI__OE_SEL0        (* (reg8 *) Motor_2_A__PRTDSI__OE_SEL0) 
#define Motor_2_A_PRTDSI__OE_SEL1        (* (reg8 *) Motor_2_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Motor_2_A_PRTDSI__OUT_SEL0       (* (reg8 *) Motor_2_A__PRTDSI__OUT_SEL0) 
#define Motor_2_A_PRTDSI__OUT_SEL1       (* (reg8 *) Motor_2_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Motor_2_A_PRTDSI__SYNC_OUT       (* (reg8 *) Motor_2_A__PRTDSI__SYNC_OUT) 


#if defined(Motor_2_A__INTSTAT)  /* Interrupt Registers */

    #define Motor_2_A_INTSTAT                (* (reg8 *) Motor_2_A__INTSTAT)
    #define Motor_2_A_SNAP                   (* (reg8 *) Motor_2_A__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Motor_2_A_H */


/* [] END OF FILE */
