/*******************************************************************************
* File Name: Row_Divider_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Row_Divider.h"

static Row_Divider_backupStruct Row_Divider_backup;


/*******************************************************************************
* Function Name: Row_Divider_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Row_Divider_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Row_Divider_SaveConfig(void) 
{

    #if(!Row_Divider_UsingFixedFunction)
        #if(!Row_Divider_PWMModeIsCenterAligned)
            Row_Divider_backup.PWMPeriod = Row_Divider_ReadPeriod();
        #endif /* (!Row_Divider_PWMModeIsCenterAligned) */
        Row_Divider_backup.PWMUdb = Row_Divider_ReadCounter();
        #if (Row_Divider_UseStatus)
            Row_Divider_backup.InterruptMaskValue = Row_Divider_STATUS_MASK;
        #endif /* (Row_Divider_UseStatus) */

        #if(Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_256_CLOCKS || \
            Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_2_4_CLOCKS)
            Row_Divider_backup.PWMdeadBandValue = Row_Divider_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Row_Divider_KillModeMinTime)
             Row_Divider_backup.PWMKillCounterPeriod = Row_Divider_ReadKillTime();
        #endif /* (Row_Divider_KillModeMinTime) */

        #if(Row_Divider_UseControl)
            Row_Divider_backup.PWMControlRegister = Row_Divider_ReadControlRegister();
        #endif /* (Row_Divider_UseControl) */
    #endif  /* (!Row_Divider_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Row_Divider_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Row_Divider_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Row_Divider_RestoreConfig(void) 
{
        #if(!Row_Divider_UsingFixedFunction)
            #if(!Row_Divider_PWMModeIsCenterAligned)
                Row_Divider_WritePeriod(Row_Divider_backup.PWMPeriod);
            #endif /* (!Row_Divider_PWMModeIsCenterAligned) */

            Row_Divider_WriteCounter(Row_Divider_backup.PWMUdb);

            #if (Row_Divider_UseStatus)
                Row_Divider_STATUS_MASK = Row_Divider_backup.InterruptMaskValue;
            #endif /* (Row_Divider_UseStatus) */

            #if(Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_256_CLOCKS || \
                Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_2_4_CLOCKS)
                Row_Divider_WriteDeadTime(Row_Divider_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Row_Divider_KillModeMinTime)
                Row_Divider_WriteKillTime(Row_Divider_backup.PWMKillCounterPeriod);
            #endif /* (Row_Divider_KillModeMinTime) */

            #if(Row_Divider_UseControl)
                Row_Divider_WriteControlRegister(Row_Divider_backup.PWMControlRegister);
            #endif /* (Row_Divider_UseControl) */
        #endif  /* (!Row_Divider_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Row_Divider_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Row_Divider_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Row_Divider_Sleep(void) 
{
    #if(Row_Divider_UseControl)
        if(Row_Divider_CTRL_ENABLE == (Row_Divider_CONTROL & Row_Divider_CTRL_ENABLE))
        {
            /*Component is enabled */
            Row_Divider_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Row_Divider_backup.PWMEnableState = 0u;
        }
    #endif /* (Row_Divider_UseControl) */

    /* Stop component */
    Row_Divider_Stop();

    /* Save registers configuration */
    Row_Divider_SaveConfig();
}


/*******************************************************************************
* Function Name: Row_Divider_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Row_Divider_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Row_Divider_Wakeup(void) 
{
     /* Restore registers values */
    Row_Divider_RestoreConfig();

    if(Row_Divider_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Row_Divider_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
