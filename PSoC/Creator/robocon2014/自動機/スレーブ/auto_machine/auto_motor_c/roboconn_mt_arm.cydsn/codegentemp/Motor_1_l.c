/*******************************************************************************
* File Name: Motor_1_l.c  
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
#include "Motor_1_l.h"


/*******************************************************************************
* Function Name: Motor_1_l_Write
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
void Motor_1_l_Write(uint8 value) 
{
    uint8 staticBits = (Motor_1_l_DR & (uint8)(~Motor_1_l_MASK));
    Motor_1_l_DR = staticBits | ((uint8)(value << Motor_1_l_SHIFT) & Motor_1_l_MASK);
}


/*******************************************************************************
* Function Name: Motor_1_l_SetDriveMode
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
void Motor_1_l_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Motor_1_l_0, mode);
}


/*******************************************************************************
* Function Name: Motor_1_l_Read
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
*  Macro Motor_1_l_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Motor_1_l_Read(void) 
{
    return (Motor_1_l_PS & Motor_1_l_MASK) >> Motor_1_l_SHIFT;
}


/*******************************************************************************
* Function Name: Motor_1_l_ReadDataReg
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
uint8 Motor_1_l_ReadDataReg(void) 
{
    return (Motor_1_l_DR & Motor_1_l_MASK) >> Motor_1_l_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Motor_1_l_INTSTAT) 

    /*******************************************************************************
    * Function Name: Motor_1_l_ClearInterrupt
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
    uint8 Motor_1_l_ClearInterrupt(void) 
    {
        return (Motor_1_l_INTSTAT & Motor_1_l_MASK) >> Motor_1_l_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
