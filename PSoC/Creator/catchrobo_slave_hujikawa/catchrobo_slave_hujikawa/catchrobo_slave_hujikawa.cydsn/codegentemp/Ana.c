/*******************************************************************************
* File Name: Ana.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Ana.h"


/*******************************************************************************
* Function Name: Ana_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Ana_Write(uint8 value) 
{
    uint8 staticBits = (Ana_DR & (uint8)(~Ana_MASK));
    Ana_DR = staticBits | ((uint8)(value << Ana_SHIFT) & Ana_MASK);
}


/*******************************************************************************
* Function Name: Ana_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Ana_DM_STRONG     Strong Drive 
*  Ana_DM_OD_HI      Open Drain, Drives High 
*  Ana_DM_OD_LO      Open Drain, Drives Low 
*  Ana_DM_RES_UP     Resistive Pull Up 
*  Ana_DM_RES_DWN    Resistive Pull Down 
*  Ana_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Ana_DM_DIG_HIZ    High Impedance Digital 
*  Ana_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Ana_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Ana_0, mode);
}


/*******************************************************************************
* Function Name: Ana_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Ana_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Ana_Read(void) 
{
    return (Ana_PS & Ana_MASK) >> Ana_SHIFT;
}


/*******************************************************************************
* Function Name: Ana_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Ana_ReadDataReg(void) 
{
    return (Ana_DR & Ana_MASK) >> Ana_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Ana_INTSTAT) 

    /*******************************************************************************
    * Function Name: Ana_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Ana_ClearInterrupt(void) 
    {
        return (Ana_INTSTAT & Ana_MASK) >> Ana_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
