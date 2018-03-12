/*******************************************************************************
* File Name: Row_Tone_1_PM.c  
* Version 2.10
*
* Description:
*  This file provides the power manager source code to the API for 
*  the WaveDAC8 component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Row_Tone_1.h"

static Row_Tone_1_BACKUP_STRUCT  Row_Tone_1_backup;


/*******************************************************************************
* Function Name: Row_Tone_1_Sleep
********************************************************************************
*
* Summary:
*  Stops the component and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Row_Tone_1_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Row_Tone_1_Sleep(void) 
{
	/* Save DAC8's enable state */

	Row_Tone_1_backup.enableState = (Row_Tone_1_VDAC8_ACT_PWR_EN == 
		(Row_Tone_1_VDAC8_PWRMGR_REG & Row_Tone_1_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	Row_Tone_1_Stop();
	Row_Tone_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Row_Tone_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  Row_Tone_1_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Row_Tone_1_Wakeup(void) 
{
	Row_Tone_1_RestoreConfig();

	if(Row_Tone_1_backup.enableState == 1u)
	{
		Row_Tone_1_Enable();
	}
}


/* [] END OF FILE */
