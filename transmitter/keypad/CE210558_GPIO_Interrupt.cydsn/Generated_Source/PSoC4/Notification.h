/*******************************************************************************
* File Name: Notification.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Notification_H) /* Pins Notification_H */
#define CY_PINS_Notification_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Notification_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Notification_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Notification_Read(void);
void    Notification_Write(uint8 value);
uint8   Notification_ReadDataReg(void);
#if defined(Notification__PC) || (CY_PSOC4_4200L) 
    void    Notification_SetDriveMode(uint8 mode);
#endif
void    Notification_SetInterruptMode(uint16 position, uint16 mode);
uint8   Notification_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Notification_Sleep(void); 
void Notification_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Notification__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Notification_DRIVE_MODE_BITS        (3)
    #define Notification_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Notification_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Notification_SetDriveMode() function.
         *  @{
         */
        #define Notification_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Notification_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Notification_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Notification_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Notification_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Notification_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Notification_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Notification_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Notification_MASK               Notification__MASK
#define Notification_SHIFT              Notification__SHIFT
#define Notification_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Notification_SetInterruptMode() function.
     *  @{
     */
        #define Notification_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Notification_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Notification_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Notification_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Notification__SIO)
    #define Notification_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Notification__PC) && (CY_PSOC4_4200L)
    #define Notification_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Notification_USBIO_DISABLE              ((uint32)(~Notification_USBIO_ENABLE))
    #define Notification_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Notification_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Notification_USBIO_ENTER_SLEEP          ((uint32)((1u << Notification_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Notification_USBIO_SUSPEND_DEL_SHIFT)))
    #define Notification_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Notification_USBIO_SUSPEND_SHIFT)))
    #define Notification_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Notification_USBIO_SUSPEND_DEL_SHIFT)))
    #define Notification_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Notification__PC)
    /* Port Configuration */
    #define Notification_PC                 (* (reg32 *) Notification__PC)
#endif
/* Pin State */
#define Notification_PS                     (* (reg32 *) Notification__PS)
/* Data Register */
#define Notification_DR                     (* (reg32 *) Notification__DR)
/* Input Buffer Disable Override */
#define Notification_INP_DIS                (* (reg32 *) Notification__PC2)

/* Interrupt configuration Registers */
#define Notification_INTCFG                 (* (reg32 *) Notification__INTCFG)
#define Notification_INTSTAT                (* (reg32 *) Notification__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Notification_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Notification__SIO)
    #define Notification_SIO_REG            (* (reg32 *) Notification__SIO)
#endif /* (Notification__SIO_CFG) */

/* USBIO registers */
#if !defined(Notification__PC) && (CY_PSOC4_4200L)
    #define Notification_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Notification_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Notification_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Notification_DRIVE_MODE_SHIFT       (0x00u)
#define Notification_DRIVE_MODE_MASK        (0x07u << Notification_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Notification_H */


/* [] END OF FILE */
