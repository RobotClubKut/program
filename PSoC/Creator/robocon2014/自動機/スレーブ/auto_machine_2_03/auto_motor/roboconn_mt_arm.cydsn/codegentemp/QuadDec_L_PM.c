/*******************************************************************************
* File Name: QuadDec_L_PM.c
* Version 2.30
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec_L.h"

static QuadDec_L_BACKUP_STRUCT QuadDec_L_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec_L_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_L_SaveConfig(void) 
{
    #if (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_8_BIT)
        QuadDec_L_Cnt8_SaveConfig();
    #else 
        /* (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_32_BIT)
         */
        QuadDec_L_Cnt16_SaveConfig();
    #endif /* (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_L_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_L_RestoreConfig(void) 
{
    #if (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_8_BIT)
        QuadDec_L_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_32_BIT) 
         */
        QuadDec_L_Cnt16_RestoreConfig();
    #endif /* (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_L_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_L_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_L_Sleep(void) 
{
    if (0u != (QuadDec_L_SR_AUX_CONTROL & QuadDec_L_INTERRUPTS_ENABLE))
    {
        QuadDec_L_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec_L_backup.enableState = 0u;
    }

    QuadDec_L_Stop();
    QuadDec_L_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_L_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_L_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec_L_Wakeup(void) 
{
    QuadDec_L_RestoreConfig();

    if (QuadDec_L_backup.enableState != 0u)
    {
        #if (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_8_BIT)
            QuadDec_L_Cnt8_Enable();
        #else 
            /* (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_32_BIT) 
            */
            QuadDec_L_Cnt16_Enable();
        #endif /* (QuadDec_L_COUNTER_SIZE == QuadDec_L_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec_L_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

