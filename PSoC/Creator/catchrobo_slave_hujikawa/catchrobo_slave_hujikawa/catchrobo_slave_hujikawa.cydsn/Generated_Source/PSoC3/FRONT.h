/*******************************************************************************
* File Name: FRONT.h  
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

#if !defined(CY_PINS_FRONT_H) /* Pins FRONT_H */
#define CY_PINS_FRONT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FRONT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    FRONT_Write(uint8 value) ;
void    FRONT_SetDriveMode(uint8 mode) ;
uint8   FRONT_ReadDataReg(void) ;
uint8   FRONT_Read(void) ;
uint8   FRONT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FRONT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define FRONT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define FRONT_DM_RES_UP          PIN_DM_RES_UP
#define FRONT_DM_RES_DWN         PIN_DM_RES_DWN
#define FRONT_DM_OD_LO           PIN_DM_OD_LO
#define FRONT_DM_OD_HI           PIN_DM_OD_HI
#define FRONT_DM_STRONG          PIN_DM_STRONG
#define FRONT_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define FRONT_MASK               FRONT__MASK
#define FRONT_SHIFT              FRONT__SHIFT
#define FRONT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FRONT_PS                     (* (reg8 *) FRONT__PS)
/* Data Register */
#define FRONT_DR                     (* (reg8 *) FRONT__DR)
/* Port Number */
#define FRONT_PRT_NUM                (* (reg8 *) FRONT__PRT) 
/* Connect to Analog Globals */                                                  
#define FRONT_AG                     (* (reg8 *) FRONT__AG)                       
/* Analog MUX bux enable */
#define FRONT_AMUX                   (* (reg8 *) FRONT__AMUX) 
/* Bidirectional Enable */                                                        
#define FRONT_BIE                    (* (reg8 *) FRONT__BIE)
/* Bit-mask for Aliased Register Access */
#define FRONT_BIT_MASK               (* (reg8 *) FRONT__BIT_MASK)
/* Bypass Enable */
#define FRONT_BYP                    (* (reg8 *) FRONT__BYP)
/* Port wide control signals */                                                   
#define FRONT_CTL                    (* (reg8 *) FRONT__CTL)
/* Drive Modes */
#define FRONT_DM0                    (* (reg8 *) FRONT__DM0) 
#define FRONT_DM1                    (* (reg8 *) FRONT__DM1)
#define FRONT_DM2                    (* (reg8 *) FRONT__DM2) 
/* Input Buffer Disable Override */
#define FRONT_INP_DIS                (* (reg8 *) FRONT__INP_DIS)
/* LCD Common or Segment Drive */
#define FRONT_LCD_COM_SEG            (* (reg8 *) FRONT__LCD_COM_SEG)
/* Enable Segment LCD */
#define FRONT_LCD_EN                 (* (reg8 *) FRONT__LCD_EN)
/* Slew Rate Control */
#define FRONT_SLW                    (* (reg8 *) FRONT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FRONT_PRTDSI__CAPS_SEL       (* (reg8 *) FRONT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FRONT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FRONT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FRONT_PRTDSI__OE_SEL0        (* (reg8 *) FRONT__PRTDSI__OE_SEL0) 
#define FRONT_PRTDSI__OE_SEL1        (* (reg8 *) FRONT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FRONT_PRTDSI__OUT_SEL0       (* (reg8 *) FRONT__PRTDSI__OUT_SEL0) 
#define FRONT_PRTDSI__OUT_SEL1       (* (reg8 *) FRONT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FRONT_PRTDSI__SYNC_OUT       (* (reg8 *) FRONT__PRTDSI__SYNC_OUT) 


#if defined(FRONT__INTSTAT)  /* Interrupt Registers */

    #define FRONT_INTSTAT                (* (reg8 *) FRONT__INTSTAT)
    #define FRONT_SNAP                   (* (reg8 *) FRONT__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins FRONT_H */


/* [] END OF FILE */
