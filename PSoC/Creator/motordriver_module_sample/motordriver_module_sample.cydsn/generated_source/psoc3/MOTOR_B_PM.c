/*******************************************************************************
* File Name: MOTOR_B_PM.c
* Version 3.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "MOTOR_B.h"

static MOTOR_B_backupStruct MOTOR_B_backup;


/*******************************************************************************
* Function Name: MOTOR_B_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_B_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MOTOR_B_SaveConfig(void) 
{
    
    #if(!MOTOR_B_UsingFixedFunction)
        #if(!MOTOR_B_PWMModeIsCenterAligned)
            MOTOR_B_backup.PWMPeriod = MOTOR_B_ReadPeriod();
        #endif /* (!MOTOR_B_PWMModeIsCenterAligned) */
        MOTOR_B_backup.PWMUdb = MOTOR_B_ReadCounter();
        #if (MOTOR_B_UseStatus)
            MOTOR_B_backup.InterruptMaskValue = MOTOR_B_STATUS_MASK;
        #endif /* (MOTOR_B_UseStatus) */
        
        #if(MOTOR_B_DeadBandMode == MOTOR_B__B_PWM__DBM_256_CLOCKS || \
            MOTOR_B_DeadBandMode == MOTOR_B__B_PWM__DBM_2_4_CLOCKS)
            MOTOR_B_backup.PWMdeadBandValue = MOTOR_B_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(MOTOR_B_KillModeMinTime)
             MOTOR_B_backup.PWMKillCounterPeriod = MOTOR_B_ReadKillTime();
        #endif /* (MOTOR_B_KillModeMinTime) */
        
        #if(MOTOR_B_UseControl)
            MOTOR_B_backup.PWMControlRegister = MOTOR_B_ReadControlRegister();
        #endif /* (MOTOR_B_UseControl) */
    #endif  /* (!MOTOR_B_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MOTOR_B_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_B_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_B_RestoreConfig(void) 
{
        #if(!MOTOR_B_UsingFixedFunction)
            #if(!MOTOR_B_PWMModeIsCenterAligned)
                MOTOR_B_WritePeriod(MOTOR_B_backup.PWMPeriod);
            #endif /* (!MOTOR_B_PWMModeIsCenterAligned) */
            MOTOR_B_WriteCounter(MOTOR_B_backup.PWMUdb);
            #if (MOTOR_B_UseStatus)
                MOTOR_B_STATUS_MASK = MOTOR_B_backup.InterruptMaskValue;
            #endif /* (MOTOR_B_UseStatus) */
            
            #if(MOTOR_B_DeadBandMode == MOTOR_B__B_PWM__DBM_256_CLOCKS || \
                MOTOR_B_DeadBandMode == MOTOR_B__B_PWM__DBM_2_4_CLOCKS)
                MOTOR_B_WriteDeadTime(MOTOR_B_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(MOTOR_B_KillModeMinTime)
                MOTOR_B_WriteKillTime(MOTOR_B_backup.PWMKillCounterPeriod);
            #endif /* (MOTOR_B_KillModeMinTime) */
            
            #if(MOTOR_B_UseControl)
                MOTOR_B_WriteControlRegister(MOTOR_B_backup.PWMControlRegister); 
            #endif /* (MOTOR_B_UseControl) */
        #endif  /* (!MOTOR_B_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MOTOR_B_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_B_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MOTOR_B_Sleep(void) 
{
    #if(MOTOR_B_UseControl)
        if(MOTOR_B_CTRL_ENABLE == (MOTOR_B_CONTROL & MOTOR_B_CTRL_ENABLE))
        {
            /*Component is enabled */
            MOTOR_B_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MOTOR_B_backup.PWMEnableState = 0u;
        }
    #endif /* (MOTOR_B_UseControl) */

    /* Stop component */
    MOTOR_B_Stop();
    
    /* Save registers configuration */
    MOTOR_B_SaveConfig();
}


/*******************************************************************************
* Function Name: MOTOR_B_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  MOTOR_B_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_B_Wakeup(void) 
{
     /* Restore registers values */
    MOTOR_B_RestoreConfig();
    
    if(MOTOR_B_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MOTOR_B_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
