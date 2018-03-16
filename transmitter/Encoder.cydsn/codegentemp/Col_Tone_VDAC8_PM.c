/*******************************************************************************
* File Name: Col_Tone_VDAC8_PM.c  
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

#include "Col_Tone_VDAC8.h"

static Col_Tone_VDAC8_backupStruct Col_Tone_VDAC8_backup;


/*******************************************************************************
* Function Name: Col_Tone_VDAC8_SaveConfig
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
void Col_Tone_VDAC8_SaveConfig(void) 
{
    if (!((Col_Tone_VDAC8_CR1 & Col_Tone_VDAC8_SRC_MASK) == Col_Tone_VDAC8_SRC_UDB))
    {
        Col_Tone_VDAC8_backup.data_value = Col_Tone_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: Col_Tone_VDAC8_RestoreConfig
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
void Col_Tone_VDAC8_RestoreConfig(void) 
{
    if (!((Col_Tone_VDAC8_CR1 & Col_Tone_VDAC8_SRC_MASK) == Col_Tone_VDAC8_SRC_UDB))
    {
        if((Col_Tone_VDAC8_Strobe & Col_Tone_VDAC8_STRB_MASK) == Col_Tone_VDAC8_STRB_EN)
        {
            Col_Tone_VDAC8_Strobe &= (uint8)(~Col_Tone_VDAC8_STRB_MASK);
            Col_Tone_VDAC8_Data = Col_Tone_VDAC8_backup.data_value;
            Col_Tone_VDAC8_Strobe |= Col_Tone_VDAC8_STRB_EN;
        }
        else
        {
            Col_Tone_VDAC8_Data = Col_Tone_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Col_Tone_VDAC8_Sleep
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
*  Col_Tone_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Col_Tone_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Col_Tone_VDAC8_ACT_PWR_EN == (Col_Tone_VDAC8_PWRMGR & Col_Tone_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Col_Tone_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Col_Tone_VDAC8_backup.enableState = 0u;
    }
    
    Col_Tone_VDAC8_Stop();
    Col_Tone_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Col_Tone_VDAC8_Wakeup
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
*  Col_Tone_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Col_Tone_VDAC8_Wakeup(void) 
{
    Col_Tone_VDAC8_RestoreConfig();
    
    if(Col_Tone_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Col_Tone_VDAC8_Enable();

        /* Restore the data register */
        Col_Tone_VDAC8_SetValue(Col_Tone_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
