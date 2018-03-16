/*******************************************************************************
* File Name: Columns.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Columns.h"

static Columns_BACKUP_STRUCT  Columns_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Columns_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Columns_SUT.c usage_Columns_Sleep_Wakeup
*******************************************************************************/
void Columns_Sleep(void)
{
    #if defined(Columns__PC)
        Columns_backup.pcState = Columns_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Columns_backup.usbState = Columns_CR1_REG;
            Columns_USB_POWER_REG |= Columns_USBIO_ENTER_SLEEP;
            Columns_CR1_REG &= Columns_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Columns__SIO)
        Columns_backup.sioState = Columns_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Columns_SIO_REG &= (uint32)(~Columns_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Columns_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Columns_Sleep() for an example usage.
*******************************************************************************/
void Columns_Wakeup(void)
{
    #if defined(Columns__PC)
        Columns_PC = Columns_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Columns_USB_POWER_REG &= Columns_USBIO_EXIT_SLEEP_PH1;
            Columns_CR1_REG = Columns_backup.usbState;
            Columns_USB_POWER_REG &= Columns_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Columns__SIO)
        Columns_SIO_REG = Columns_backup.sioState;
    #endif
}


/* [] END OF FILE */
