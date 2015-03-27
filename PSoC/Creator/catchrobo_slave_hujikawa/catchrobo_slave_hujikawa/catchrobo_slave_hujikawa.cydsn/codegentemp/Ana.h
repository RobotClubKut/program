/*******************************************************************************
* File Name: Ana.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ana_H) /* Pins Ana_H */
#define CY_PINS_Ana_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ana_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Ana_Write(uint8 value) ;
void    Ana_SetDriveMode(uint8 mode) ;
uint8   Ana_ReadDataReg(void) ;
uint8   Ana_Read(void) ;
uint8   Ana_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Ana_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Ana_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Ana_DM_RES_UP          PIN_DM_RES_UP
#define Ana_DM_RES_DWN         PIN_DM_RES_DWN
#define Ana_DM_OD_LO           PIN_DM_OD_LO
#define Ana_DM_OD_HI           PIN_DM_OD_HI
#define Ana_DM_STRONG          PIN_DM_STRONG
#define Ana_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Ana_MASK               Ana__MASK
#define Ana_SHIFT              Ana__SHIFT
#define Ana_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ana_PS                     (* (reg8 *) Ana__PS)
/* Data Register */
#define Ana_DR                     (* (reg8 *) Ana__DR)
/* Port Number */
#define Ana_PRT_NUM                (* (reg8 *) Ana__PRT) 
/* Connect to Analog Globals */                                                  
#define Ana_AG                     (* (reg8 *) Ana__AG)                       
/* Analog MUX bux enable */
#define Ana_AMUX                   (* (reg8 *) Ana__AMUX) 
/* Bidirectional Enable */                                                        
#define Ana_BIE                    (* (reg8 *) Ana__BIE)
/* Bit-mask for Aliased Register Access */
#define Ana_BIT_MASK               (* (reg8 *) Ana__BIT_MASK)
/* Bypass Enable */
#define Ana_BYP                    (* (reg8 *) Ana__BYP)
/* Port wide control signals */                                                   
#define Ana_CTL                    (* (reg8 *) Ana__CTL)
/* Drive Modes */
#define Ana_DM0                    (* (reg8 *) Ana__DM0) 
#define Ana_DM1                    (* (reg8 *) Ana__DM1)
#define Ana_DM2                    (* (reg8 *) Ana__DM2) 
/* Input Buffer Disable Override */
#define Ana_INP_DIS                (* (reg8 *) Ana__INP_DIS)
/* LCD Common or Segment Drive */
#define Ana_LCD_COM_SEG            (* (reg8 *) Ana__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ana_LCD_EN                 (* (reg8 *) Ana__LCD_EN)
/* Slew Rate Control */
#define Ana_SLW                    (* (reg8 *) Ana__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ana_PRTDSI__CAPS_SEL       (* (reg8 *) Ana__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ana_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ana__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ana_PRTDSI__OE_SEL0        (* (reg8 *) Ana__PRTDSI__OE_SEL0) 
#define Ana_PRTDSI__OE_SEL1        (* (reg8 *) Ana__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ana_PRTDSI__OUT_SEL0       (* (reg8 *) Ana__PRTDSI__OUT_SEL0) 
#define Ana_PRTDSI__OUT_SEL1       (* (reg8 *) Ana__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ana_PRTDSI__SYNC_OUT       (* (reg8 *) Ana__PRTDSI__SYNC_OUT) 


#if defined(Ana__INTSTAT)  /* Interrupt Registers */

    #define Ana_INTSTAT                (* (reg8 *) Ana__INTSTAT)
    #define Ana_SNAP                   (* (reg8 *) Ana__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Ana_H */


/* [] END OF FILE */
