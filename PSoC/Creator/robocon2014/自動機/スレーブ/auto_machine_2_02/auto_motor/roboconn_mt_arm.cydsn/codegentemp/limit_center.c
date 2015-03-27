/*******************************************************************************
* File Name: limit_center.c  
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
#include "limit_center.h"


/*******************************************************************************
* Function Name: limit_center_Write
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
void limit_center_Write(uint8 value) 
{
    uint8 staticBits = (limit_center_DR & (uint8)(~limit_center_MASK));
    limit_center_DR = staticBits | ((uint8)(value << limit_center_SHIFT) & limit_center_MASK);
}


/*******************************************************************************
* Function Name: limit_center_SetDriveMode
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
void limit_center_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(limit_center_0, mode);
}


/*******************************************************************************
* Function Name: limit_center_Read
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
*  Macro limit_center_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 limit_center_Read(void) 
{
    return (limit_center_PS & limit_center_MASK) >> limit_center_SHIFT;
}


/*******************************************************************************
* Function Name: limit_center_ReadDataReg
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
uint8 limit_center_ReadDataReg(void) 
{
    return (limit_center_DR & limit_center_MASK) >> limit_center_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(limit_center_INTSTAT) 

    /*******************************************************************************
    * Function Name: limit_center_ClearInterrupt
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
    uint8 limit_center_ClearInterrupt(void) 
    {
        return (limit_center_INTSTAT & limit_center_MASK) >> limit_center_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
