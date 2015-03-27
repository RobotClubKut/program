/*******************************************************************************
* File Name: MOTOR_A_1.c  
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
#include "MOTOR_A_1.h"


/*******************************************************************************
* Function Name: MOTOR_A_1_Write
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
void MOTOR_A_1_Write(uint8 value) 
{
    uint8 staticBits = (MOTOR_A_1_DR & (uint8)(~MOTOR_A_1_MASK));
    MOTOR_A_1_DR = staticBits | ((uint8)(value << MOTOR_A_1_SHIFT) & MOTOR_A_1_MASK);
}


/*******************************************************************************
* Function Name: MOTOR_A_1_SetDriveMode
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
void MOTOR_A_1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MOTOR_A_1_0, mode);
}


/*******************************************************************************
* Function Name: MOTOR_A_1_Read
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
*  Macro MOTOR_A_1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MOTOR_A_1_Read(void) 
{
    return (MOTOR_A_1_PS & MOTOR_A_1_MASK) >> MOTOR_A_1_SHIFT;
}


/*******************************************************************************
* Function Name: MOTOR_A_1_ReadDataReg
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
uint8 MOTOR_A_1_ReadDataReg(void) 
{
    return (MOTOR_A_1_DR & MOTOR_A_1_MASK) >> MOTOR_A_1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MOTOR_A_1_INTSTAT) 

    /*******************************************************************************
    * Function Name: MOTOR_A_1_ClearInterrupt
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
    uint8 MOTOR_A_1_ClearInterrupt(void) 
    {
        return (MOTOR_A_1_INTSTAT & MOTOR_A_1_MASK) >> MOTOR_A_1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
