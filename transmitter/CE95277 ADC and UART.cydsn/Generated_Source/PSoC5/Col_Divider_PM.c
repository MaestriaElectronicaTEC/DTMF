/*******************************************************************************
* File Name: Col_Divider_PM.c
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

#include "Col_Divider.h"

static Col_Divider_backupStruct Col_Divider_backup;


/*******************************************************************************
* Function Name: Col_Divider_SaveConfig
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
*  Col_Divider_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Col_Divider_SaveConfig(void) 
{

    #if(!Col_Divider_UsingFixedFunction)
        #if(!Col_Divider_PWMModeIsCenterAligned)
            Col_Divider_backup.PWMPeriod = Col_Divider_ReadPeriod();
        #endif /* (!Col_Divider_PWMModeIsCenterAligned) */
        Col_Divider_backup.PWMUdb = Col_Divider_ReadCounter();
        #if (Col_Divider_UseStatus)
            Col_Divider_backup.InterruptMaskValue = Col_Divider_STATUS_MASK;
        #endif /* (Col_Divider_UseStatus) */

        #if(Col_Divider_DeadBandMode == Col_Divider__B_PWM__DBM_256_CLOCKS || \
            Col_Divider_DeadBandMode == Col_Divider__B_PWM__DBM_2_4_CLOCKS)
            Col_Divider_backup.PWMdeadBandValue = Col_Divider_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Col_Divider_KillModeMinTime)
             Col_Divider_backup.PWMKillCounterPeriod = Col_Divider_ReadKillTime();
        #endif /* (Col_Divider_KillModeMinTime) */

        #if(Col_Divider_UseControl)
            Col_Divider_backup.PWMControlRegister = Col_Divider_ReadControlRegister();
        #endif /* (Col_Divider_UseControl) */
    #endif  /* (!Col_Divider_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Col_Divider_RestoreConfig
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
*  Col_Divider_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Col_Divider_RestoreConfig(void) 
{
        #if(!Col_Divider_UsingFixedFunction)
            #if(!Col_Divider_PWMModeIsCenterAligned)
                Col_Divider_WritePeriod(Col_Divider_backup.PWMPeriod);
            #endif /* (!Col_Divider_PWMModeIsCenterAligned) */

            Col_Divider_WriteCounter(Col_Divider_backup.PWMUdb);

            #if (Col_Divider_UseStatus)
                Col_Divider_STATUS_MASK = Col_Divider_backup.InterruptMaskValue;
            #endif /* (Col_Divider_UseStatus) */

            #if(Col_Divider_DeadBandMode == Col_Divider__B_PWM__DBM_256_CLOCKS || \
                Col_Divider_DeadBandMode == Col_Divider__B_PWM__DBM_2_4_CLOCKS)
                Col_Divider_WriteDeadTime(Col_Divider_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Col_Divider_KillModeMinTime)
                Col_Divider_WriteKillTime(Col_Divider_backup.PWMKillCounterPeriod);
            #endif /* (Col_Divider_KillModeMinTime) */

            #if(Col_Divider_UseControl)
                Col_Divider_WriteControlRegister(Col_Divider_backup.PWMControlRegister);
            #endif /* (Col_Divider_UseControl) */
        #endif  /* (!Col_Divider_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Col_Divider_Sleep
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
*  Col_Divider_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Col_Divider_Sleep(void) 
{
    #if(Col_Divider_UseControl)
        if(Col_Divider_CTRL_ENABLE == (Col_Divider_CONTROL & Col_Divider_CTRL_ENABLE))
        {
            /*Component is enabled */
            Col_Divider_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Col_Divider_backup.PWMEnableState = 0u;
        }
    #endif /* (Col_Divider_UseControl) */

    /* Stop component */
    Col_Divider_Stop();

    /* Save registers configuration */
    Col_Divider_SaveConfig();
}


/*******************************************************************************
* Function Name: Col_Divider_Wakeup
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
*  Col_Divider_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Col_Divider_Wakeup(void) 
{
     /* Restore registers values */
    Col_Divider_RestoreConfig();

    if(Col_Divider_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Col_Divider_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
