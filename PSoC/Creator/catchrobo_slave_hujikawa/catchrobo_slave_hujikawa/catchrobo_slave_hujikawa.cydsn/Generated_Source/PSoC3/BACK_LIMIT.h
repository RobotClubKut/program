/*******************************************************************************
* File Name: BACK_LIMIT.h  
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

#if !defined(CY_PINS_BACK_LIMIT_H) /* Pins BACK_LIMIT_H */
#define CY_PINS_BACK_LIMIT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BACK_LIMIT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BACK_LIMIT_Write(uint8 value) ;
void    BACK_LIMIT_SetDriveMode(uint8 mode) ;
uint8   BACK_LIMIT_ReadDataReg(void) ;
uint8   BACK_LIMIT_Read(void) ;
uint8   BACK_LIMIT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BACK_LIMIT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BACK_LIMIT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BACK_LIMIT_DM_RES_UP          PIN_DM_RES_UP
#define BACK_LIMIT_DM_RES_DWN         PIN_DM_RES_DWN
#define BACK_LIMIT_DM_OD_LO           PIN_DM_OD_LO
#define BACK_LIMIT_DM_OD_HI           PIN_DM_OD_HI
#define BACK_LIMIT_DM_STRONG          PIN_DM_STRONG
#define BACK_LIMIT_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BACK_LIMIT_MASK               BACK_LIMIT__MASK
#define BACK_LIMIT_SHIFT              BACK_LIMIT__SHIFT
#define BACK_LIMIT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BACK_LIMIT_PS                     (* (reg8 *) BACK_LIMIT__PS)
/* Data Register */
#define BACK_LIMIT_DR                     (* (reg8 *) BACK_LIMIT__DR)
/* Port Number */
#define BACK_LIMIT_PRT_NUM                (* (reg8 *) BACK_LIMIT__PRT) 
/* Connect to Analog Globals */                                                  
#define BACK_LIMIT_AG                     (* (reg8 *) BACK_LIMIT__AG)                       
/* Analog MUX bux enable */
#define BACK_LIMIT_AMUX                   (* (reg8 *) BACK_LIMIT__AMUX) 
/* Bidirectional Enable */                                                        
#define BACK_LIMIT_BIE                    (* (reg8 *) BACK_LIMIT__BIE)
/* Bit-mask for Aliased Register Access */
#define BACK_LIMIT_BIT_MASK               (* (reg8 *) BACK_LIMIT__BIT_MASK)
/* Bypass Enable */
#define BACK_LIMIT_BYP                    (* (reg8 *) BACK_LIMIT__BYP)
/* Port wide control signals */                                                   
#define BACK_LIMIT_CTL                    (* (reg8 *) BACK_LIMIT__CTL)
/* Drive Modes */
#define BACK_LIMIT_DM0                    (* (reg8 *) BACK_LIMIT__DM0) 
#define BACK_LIMIT_DM1                    (* (reg8 *) BACK_LIMIT__DM1)
#define BACK_LIMIT_DM2                    (* (reg8 *) BACK_LIMIT__DM2) 
/* Input Buffer Disable Override */
#define BACK_LIMIT_INP_DIS                (* (reg8 *) BACK_LIMIT__INP_DIS)
/* LCD Common or Segment Drive */
#define BACK_LIMIT_LCD_COM_SEG            (* (reg8 *) BACK_LIMIT__LCD_COM_SEG)
/* Enable Segment LCD */
#define BACK_LIMIT_LCD_EN                 (* (reg8 *) BACK_LIMIT__LCD_EN)
/* Slew Rate Control */
#define BACK_LIMIT_SLW                    (* (reg8 *) BACK_LIMIT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BACK_LIMIT_PRTDSI__CAPS_SEL       (* (reg8 *) BACK_LIMIT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BACK_LIMIT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BACK_LIMIT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BACK_LIMIT_PRTDSI__OE_SEL0        (* (reg8 *) BACK_LIMIT__PRTDSI__OE_SEL0) 
#define BACK_LIMIT_PRTDSI__OE_SEL1        (* (reg8 *) BACK_LIMIT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BACK_LIMIT_PRTDSI__OUT_SEL0       (* (reg8 *) BACK_LIMIT__PRTDSI__OUT_SEL0) 
#define BACK_LIMIT_PRTDSI__OUT_SEL1       (* (reg8 *) BACK_LIMIT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BACK_LIMIT_PRTDSI__SYNC_OUT       (* (reg8 *) BACK_LIMIT__PRTDSI__SYNC_OUT) 


#if defined(BACK_LIMIT__INTSTAT)  /* Interrupt Registers */

    #define BACK_LIMIT_INTSTAT                (* (reg8 *) BACK_LIMIT__INTSTAT)
    #define BACK_LIMIT_SNAP                   (* (reg8 *) BACK_LIMIT__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins BACK_LIMIT_H */


/* [] END OF FILE */
