/*******************************************************************************
* File Name: Row_Tone_1_VDAC8_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Row_Tone_1_VDAC8.h"

static Row_Tone_1_VDAC8_backupStruct Row_Tone_1_VDAC8_backup;


/*******************************************************************************
* Function Name: Row_Tone_1_VDAC8_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Row_Tone_1_VDAC8_SaveConfig(void) 
{
    if (!((Row_Tone_1_VDAC8_CR1 & Row_Tone_1_VDAC8_SRC_MASK) == Row_Tone_1_VDAC8_SRC_UDB))
    {
        Row_Tone_1_VDAC8_backup.data_value = Row_Tone_1_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: Row_Tone_1_VDAC8_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Row_Tone_1_VDAC8_RestoreConfig(void) 
{
    if (!((Row_Tone_1_VDAC8_CR1 & Row_Tone_1_VDAC8_SRC_MASK) == Row_Tone_1_VDAC8_SRC_UDB))
    {
        if((Row_Tone_1_VDAC8_Strobe & Row_Tone_1_VDAC8_STRB_MASK) == Row_Tone_1_VDAC8_STRB_EN)
        {
            Row_Tone_1_VDAC8_Strobe &= (uint8)(~Row_Tone_1_VDAC8_STRB_MASK);
            Row_Tone_1_VDAC8_Data = Row_Tone_1_VDAC8_backup.data_value;
            Row_Tone_1_VDAC8_Strobe |= Row_Tone_1_VDAC8_STRB_EN;
        }
        else
        {
            Row_Tone_1_VDAC8_Data = Row_Tone_1_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Row_Tone_1_VDAC8_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Row_Tone_1_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Row_Tone_1_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Row_Tone_1_VDAC8_ACT_PWR_EN == (Row_Tone_1_VDAC8_PWRMGR & Row_Tone_1_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Row_Tone_1_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Row_Tone_1_VDAC8_backup.enableState = 0u;
    }
    
    Row_Tone_1_VDAC8_Stop();
    Row_Tone_1_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Row_Tone_1_VDAC8_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Row_Tone_1_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Row_Tone_1_VDAC8_Wakeup(void) 
{
    Row_Tone_1_VDAC8_RestoreConfig();
    
    if(Row_Tone_1_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Row_Tone_1_VDAC8_Enable();

        /* Restore the data register */
        Row_Tone_1_VDAC8_SetValue(Row_Tone_1_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
