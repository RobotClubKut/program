/*******************************************************************************
* File Name: FRONT_LIMIT_1.h  
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

#if !defined(CY_PINS_FRONT_LIMIT_1_H) /* Pins FRONT_LIMIT_1_H */
#define CY_PINS_FRONT_LIMIT_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FRONT_LIMIT_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    FRONT_LIMIT_1_Write(uint8 value) ;
void    FRONT_LIMIT_1_SetDriveMode(uint8 mode) ;
uint8   FRONT_LIMIT_1_ReadDataReg(void) ;
uint8   FRONT_LIMIT_1_Read(void) ;
uint8   FRONT_LIMIT_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FRONT_LIMIT_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define FRONT_LIMIT_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define FRONT_LIMIT_1_DM_RES_UP          PIN_DM_RES_UP
#define FRONT_LIMIT_1_DM_RES_DWN         PIN_DM_RES_DWN
#define FRONT_LIMIT_1_DM_OD_LO           PIN_DM_OD_LO
#define FRONT_LIMIT_1_DM_OD_HI           PIN_DM_OD_HI
#define FRONT_LIMIT_1_DM_STRONG          PIN_DM_STRONG
#define FRONT_LIMIT_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define FRONT_LIMIT_1_MASK               FRONT_LIMIT_1__MASK
#define FRONT_LIMIT_1_SHIFT              FRONT_LIMIT_1__SHIFT
#define FRONT_LIMIT_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FRONT_LIMIT_1_PS                     (* (reg8 *) FRONT_LIMIT_1__PS)
/* Data Register */
#define FRONT_LIMIT_1_DR                     (* (reg8 *) FRONT_LIMIT_1__DR)
/* Port Number */
#define FRONT_LIMIT_1_PRT_NUM                (* (reg8 *) FRONT_LIMIT_1__PRT) 
/* Connect to Analog Globals */                                                  
#define FRONT_LIMIT_1_AG                     (* (reg8 *) FRONT_LIMIT_1__AG)                       
/* Analog MUX bux enable */
#define FRONT_LIMIT_1_AMUX                   (* (reg8 *) FRONT_LIMIT_1__AMUX) 
/* Bidirectional Enable */                                                        
#define FRONT_LIMIT_1_BIE                    (* (reg8 *) FRONT_LIMIT_1__BIE)
/* Bit-mask for Aliased Register Access */
#define FRONT_LIMIT_1_BIT_MASK               (* (reg8 *) FRONT_LIMIT_1__BIT_MASK)
/* Bypass Enable */
#define FRONT_LIMIT_1_BYP                    (* (reg8 *) FRONT_LIMIT_1__BYP)
/* Port wide control signals */                                                   
#define FRONT_LIMIT_1_CTL                    (* (reg8 *) FRONT_LIMIT_1__CTL)
/* Drive Modes */
#define FRONT_LIMIT_1_DM0                    (* (reg8 *) FRONT_LIMIT_1__DM0) 
#define FRONT_LIMIT_1_DM1                    (* (reg8 *) FRONT_LIMIT_1__DM1)
#define FRONT_LIMIT_1_DM2                    (* (reg8 *) FRONT_LIMIT_1__DM2) 
/* Input Buffer Disable Override */
#define FRONT_LIMIT_1_INP_DIS                (* (reg8 *) FRONT_LIMIT_1__INP_DIS)
/* LCD Common or Segment Drive */
#define FRONT_LIMIT_1_LCD_COM_SEG            (* (reg8 *) FRONT_LIMIT_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define FRONT_LIMIT_1_LCD_EN                 (* (reg8 *) FRONT_LIMIT_1__LCD_EN)
/* Slew Rate Control */
#define FRONT_LIMIT_1_SLW                    (* (reg8 *) FRONT_LIMIT_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FRONT_LIMIT_1_PRTDSI__CAPS_SEL       (* (reg8 *) FRONT_LIMIT_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FRONT_LIMIT_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FRONT_LIMIT_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FRONT_LIMIT_1_PRTDSI__OE_SEL0        (* (reg8 *) FRONT_LIMIT_1__PRTDSI__OE_SEL0) 
#define FRONT_LIMIT_1_PRTDSI__OE_SEL1        (* (reg8 *) FRONT_LIMIT_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FRONT_LIMIT_1_PRTDSI__OUT_SEL0       (* (reg8 *) FRONT_LIMIT_1__PRTDSI__OUT_SEL0) 
#define FRONT_LIMIT_1_PRTDSI__OUT_SEL1       (* (reg8 *) FRONT_LIMIT_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FRONT_LIMIT_1_PRTDSI__SYNC_OUT       (* (reg8 *) FRONT_LIMIT_1__PRTDSI__SYNC_OUT) 


#if defined(FRONT_LIMIT_1__INTSTAT)  /* Interrupt Registers */

    #define FRONT_LIMIT_1_INTSTAT                (* (reg8 *) FRONT_LIMIT_1__INTSTAT)
    #define FRONT_LIMIT_1_SNAP                   (* (reg8 *) FRONT_LIMIT_1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins FRONT_LIMIT_1_H */


/* [] END OF FILE */
