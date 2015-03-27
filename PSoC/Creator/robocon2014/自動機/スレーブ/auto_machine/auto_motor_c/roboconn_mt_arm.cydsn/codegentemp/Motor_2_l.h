/*******************************************************************************
* File Name: Motor_2_l.h  
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

#if !defined(CY_PINS_Motor_2_l_H) /* Pins Motor_2_l_H */
#define CY_PINS_Motor_2_l_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Motor_2_l_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Motor_2_l_Write(uint8 value) ;
void    Motor_2_l_SetDriveMode(uint8 mode) ;
uint8   Motor_2_l_ReadDataReg(void) ;
uint8   Motor_2_l_Read(void) ;
uint8   Motor_2_l_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Motor_2_l_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Motor_2_l_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Motor_2_l_DM_RES_UP          PIN_DM_RES_UP
#define Motor_2_l_DM_RES_DWN         PIN_DM_RES_DWN
#define Motor_2_l_DM_OD_LO           PIN_DM_OD_LO
#define Motor_2_l_DM_OD_HI           PIN_DM_OD_HI
#define Motor_2_l_DM_STRONG          PIN_DM_STRONG
#define Motor_2_l_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Motor_2_l_MASK               Motor_2_l__MASK
#define Motor_2_l_SHIFT              Motor_2_l__SHIFT
#define Motor_2_l_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Motor_2_l_PS                     (* (reg8 *) Motor_2_l__PS)
/* Data Register */
#define Motor_2_l_DR                     (* (reg8 *) Motor_2_l__DR)
/* Port Number */
#define Motor_2_l_PRT_NUM                (* (reg8 *) Motor_2_l__PRT) 
/* Connect to Analog Globals */                                                  
#define Motor_2_l_AG                     (* (reg8 *) Motor_2_l__AG)                       
/* Analog MUX bux enable */
#define Motor_2_l_AMUX                   (* (reg8 *) Motor_2_l__AMUX) 
/* Bidirectional Enable */                                                        
#define Motor_2_l_BIE                    (* (reg8 *) Motor_2_l__BIE)
/* Bit-mask for Aliased Register Access */
#define Motor_2_l_BIT_MASK               (* (reg8 *) Motor_2_l__BIT_MASK)
/* Bypass Enable */
#define Motor_2_l_BYP                    (* (reg8 *) Motor_2_l__BYP)
/* Port wide control signals */                                                   
#define Motor_2_l_CTL                    (* (reg8 *) Motor_2_l__CTL)
/* Drive Modes */
#define Motor_2_l_DM0                    (* (reg8 *) Motor_2_l__DM0) 
#define Motor_2_l_DM1                    (* (reg8 *) Motor_2_l__DM1)
#define Motor_2_l_DM2                    (* (reg8 *) Motor_2_l__DM2) 
/* Input Buffer Disable Override */
#define Motor_2_l_INP_DIS                (* (reg8 *) Motor_2_l__INP_DIS)
/* LCD Common or Segment Drive */
#define Motor_2_l_LCD_COM_SEG            (* (reg8 *) Motor_2_l__LCD_COM_SEG)
/* Enable Segment LCD */
#define Motor_2_l_LCD_EN                 (* (reg8 *) Motor_2_l__LCD_EN)
/* Slew Rate Control */
#define Motor_2_l_SLW                    (* (reg8 *) Motor_2_l__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Motor_2_l_PRTDSI__CAPS_SEL       (* (reg8 *) Motor_2_l__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Motor_2_l_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Motor_2_l__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Motor_2_l_PRTDSI__OE_SEL0        (* (reg8 *) Motor_2_l__PRTDSI__OE_SEL0) 
#define Motor_2_l_PRTDSI__OE_SEL1        (* (reg8 *) Motor_2_l__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Motor_2_l_PRTDSI__OUT_SEL0       (* (reg8 *) Motor_2_l__PRTDSI__OUT_SEL0) 
#define Motor_2_l_PRTDSI__OUT_SEL1       (* (reg8 *) Motor_2_l__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Motor_2_l_PRTDSI__SYNC_OUT       (* (reg8 *) Motor_2_l__PRTDSI__SYNC_OUT) 


#if defined(Motor_2_l__INTSTAT)  /* Interrupt Registers */

    #define Motor_2_l_INTSTAT                (* (reg8 *) Motor_2_l__INTSTAT)
    #define Motor_2_l_SNAP                   (* (reg8 *) Motor_2_l__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Motor_2_l_H */


/* [] END OF FILE */
