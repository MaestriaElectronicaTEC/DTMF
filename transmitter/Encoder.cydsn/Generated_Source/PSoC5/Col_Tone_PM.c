/*******************************************************************************
* File Name: Col_Tone_PM.c  
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

#include "Col_Tone.h"

static Col_Tone_BACKUP_STRUCT  Col_Tone_backup;


/*******************************************************************************
* Function Name: Col_Tone_Sleep
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
*  Col_Tone_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Col_Tone_Sleep(void) 
{
	/* Save DAC8's enable state */

	Col_Tone_backup.enableState = (Col_Tone_VDAC8_ACT_PWR_EN == 
		(Col_Tone_VDAC8_PWRMGR_REG & Col_Tone_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	Col_Tone_Stop();
	Col_Tone_SaveConfig();
}


/*******************************************************************************
* Function Name: Col_Tone_Wakeup
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
*  Col_Tone_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Col_Tone_Wakeup(void) 
{
	Col_Tone_RestoreConfig();

	if(Col_Tone_backup.enableState == 1u)
	{
		Col_Tone_Enable();
	}
}


/* [] END OF FILE */
