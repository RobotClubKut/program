/*******************************************************************************
* File Name: DOWN.c  
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
#include "DOWN.h"


/*******************************************************************************
* Function Name: DOWN_Write
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
void DOWN_Write(uint8 value) 
{
    uint8 staticBits = (DOWN_DR & (uint8)(~DOWN_MASK));
    DOWN_DR = staticBits | ((uint8)(value << DOWN_SHIFT) & DOWN_MASK);
}


/*******************************************************************************
* Function Name: DOWN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DOWN_DM_STRONG     Strong Drive 
*  DOWN_DM_OD_HI      Open Drain, Drives High 
*  DOWN_DM_OD_LO      Open Drain, Drives Low 
*  DOWN_DM_RES_UP     Resistive Pull Up 
*  DOWN_DM_RES_DWN    Resistive Pull Down 
*  DOWN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DOWN_DM_DIG_HIZ    High Impedance Digital 
*  DOWN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DOWN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DOWN_0, mode);
}


/*******************************************************************************
* Function Name: DOWN_Read
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
*  Macro DOWN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DOWN_Read(void) 
{
    return (DOWN_PS & DOWN_MASK) >> DOWN_SHIFT;
}


/*******************************************************************************
* Function Name: DOWN_ReadDataReg
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
uint8 DOWN_ReadDataReg(void) 
{
    return (DOWN_DR & DOWN_MASK) >> DOWN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DOWN_INTSTAT) 

    /*******************************************************************************
    * Function Name: DOWN_ClearInterrupt
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
    uint8 DOWN_ClearInterrupt(void) 
    {
        return (DOWN_INTSTAT & DOWN_MASK) >> DOWN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
