/*******************************************************************************
* File Name: rori_R_B.h  
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

#if !defined(CY_PINS_rori_R_B_H) /* Pins rori_R_B_H */
#define CY_PINS_rori_R_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rori_R_B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    rori_R_B_Write(uint8 value) ;
void    rori_R_B_SetDriveMode(uint8 mode) ;
uint8   rori_R_B_ReadDataReg(void) ;
uint8   rori_R_B_Read(void) ;
uint8   rori_R_B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define rori_R_B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define rori_R_B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define rori_R_B_DM_RES_UP          PIN_DM_RES_UP
#define rori_R_B_DM_RES_DWN         PIN_DM_RES_DWN
#define rori_R_B_DM_OD_LO           PIN_DM_OD_LO
#define rori_R_B_DM_OD_HI           PIN_DM_OD_HI
#define rori_R_B_DM_STRONG          PIN_DM_STRONG
#define rori_R_B_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define rori_R_B_MASK               rori_R_B__MASK
#define rori_R_B_SHIFT              rori_R_B__SHIFT
#define rori_R_B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rori_R_B_PS                     (* (reg8 *) rori_R_B__PS)
/* Data Register */
#define rori_R_B_DR                     (* (reg8 *) rori_R_B__DR)
/* Port Number */
#define rori_R_B_PRT_NUM                (* (reg8 *) rori_R_B__PRT) 
/* Connect to Analog Globals */                                                  
#define rori_R_B_AG                     (* (reg8 *) rori_R_B__AG)                       
/* Analog MUX bux enable */
#define rori_R_B_AMUX                   (* (reg8 *) rori_R_B__AMUX) 
/* Bidirectional Enable */                                                        
#define rori_R_B_BIE                    (* (reg8 *) rori_R_B__BIE)
/* Bit-mask for Aliased Register Access */
#define rori_R_B_BIT_MASK               (* (reg8 *) rori_R_B__BIT_MASK)
/* Bypass Enable */
#define rori_R_B_BYP                    (* (reg8 *) rori_R_B__BYP)
/* Port wide control signals */                                                   
#define rori_R_B_CTL                    (* (reg8 *) rori_R_B__CTL)
/* Drive Modes */
#define rori_R_B_DM0                    (* (reg8 *) rori_R_B__DM0) 
#define rori_R_B_DM1                    (* (reg8 *) rori_R_B__DM1)
#define rori_R_B_DM2                    (* (reg8 *) rori_R_B__DM2) 
/* Input Buffer Disable Override */
#define rori_R_B_INP_DIS                (* (reg8 *) rori_R_B__INP_DIS)
/* LCD Common or Segment Drive */
#define rori_R_B_LCD_COM_SEG            (* (reg8 *) rori_R_B__LCD_COM_SEG)
/* Enable Segment LCD */
#define rori_R_B_LCD_EN                 (* (reg8 *) rori_R_B__LCD_EN)
/* Slew Rate Control */
#define rori_R_B_SLW                    (* (reg8 *) rori_R_B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rori_R_B_PRTDSI__CAPS_SEL       (* (reg8 *) rori_R_B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rori_R_B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rori_R_B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rori_R_B_PRTDSI__OE_SEL0        (* (reg8 *) rori_R_B__PRTDSI__OE_SEL0) 
#define rori_R_B_PRTDSI__OE_SEL1        (* (reg8 *) rori_R_B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rori_R_B_PRTDSI__OUT_SEL0       (* (reg8 *) rori_R_B__PRTDSI__OUT_SEL0) 
#define rori_R_B_PRTDSI__OUT_SEL1       (* (reg8 *) rori_R_B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rori_R_B_PRTDSI__SYNC_OUT       (* (reg8 *) rori_R_B__PRTDSI__SYNC_OUT) 


#if defined(rori_R_B__INTSTAT)  /* Interrupt Registers */

    #define rori_R_B_INTSTAT                (* (reg8 *) rori_R_B__INTSTAT)
    #define rori_R_B_SNAP                   (* (reg8 *) rori_R_B__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins rori_R_B_H */


/* [] END OF FILE */
