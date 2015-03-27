/*******************************************************************************
* File Name: UP_LIMIT.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
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
#include "UP_LIMIT.h"


/*******************************************************************************
* Function Name: UP_LIMIT_Write
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
void UP_LIMIT_Write(uint8 value) 
{
    uint8 staticBits = (UP_LIMIT_DR & (uint8)(~UP_LIMIT_MASK));
    UP_LIMIT_DR = staticBits | ((uint8)(value << UP_LIMIT_SHIFT) & UP_LIMIT_MASK);
}


/*******************************************************************************
* Function Name: UP_LIMIT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void UP_LIMIT_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(UP_LIMIT_0, mode);
}


/*******************************************************************************
* Function Name: UP_LIMIT_Read
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
*  Macro UP_LIMIT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 UP_LIMIT_Read(void) 
{
    return (UP_LIMIT_PS & UP_LIMIT_MASK) >> UP_LIMIT_SHIFT;
}


/*******************************************************************************
* Function Name: UP_LIMIT_ReadDataReg
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
uint8 UP_LIMIT_ReadDataReg(void) 
{
    return (UP_LIMIT_DR & UP_LIMIT_MASK) >> UP_LIMIT_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(UP_LIMIT_INTSTAT) 

    /*******************************************************************************
    * Function Name: UP_LIMIT_ClearInterrupt
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
    uint8 UP_LIMIT_ClearInterrupt(void) 
    {
        return (UP_LIMIT_INTSTAT & UP_LIMIT_MASK) >> UP_LIMIT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
