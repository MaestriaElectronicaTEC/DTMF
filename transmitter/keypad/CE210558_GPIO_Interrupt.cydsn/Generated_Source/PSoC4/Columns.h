/*******************************************************************************
* File Name: Columns.h  
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

#if !defined(CY_PINS_Columns_H) /* Pins Columns_H */
#define CY_PINS_Columns_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Columns_aliases.h"


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
} Columns_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Columns_Read(void);
void    Columns_Write(uint8 value);
uint8   Columns_ReadDataReg(void);
#if defined(Columns__PC) || (CY_PSOC4_4200L) 
    void    Columns_SetDriveMode(uint8 mode);
#endif
void    Columns_SetInterruptMode(uint16 position, uint16 mode);
uint8   Columns_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Columns_Sleep(void); 
void Columns_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Columns__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Columns_DRIVE_MODE_BITS        (3)
    #define Columns_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Columns_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Columns_SetDriveMode() function.
         *  @{
         */
        #define Columns_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Columns_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Columns_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Columns_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Columns_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Columns_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Columns_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Columns_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Columns_MASK               Columns__MASK
#define Columns_SHIFT              Columns__SHIFT
#define Columns_WIDTH              4u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Columns_SetInterruptMode() function.
     *  @{
     */
        #define Columns_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Columns_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Columns_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Columns_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Columns__SIO)
    #define Columns_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Columns__PC) && (CY_PSOC4_4200L)
    #define Columns_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Columns_USBIO_DISABLE              ((uint32)(~Columns_USBIO_ENABLE))
    #define Columns_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Columns_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Columns_USBIO_ENTER_SLEEP          ((uint32)((1u << Columns_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Columns_USBIO_SUSPEND_DEL_SHIFT)))
    #define Columns_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Columns_USBIO_SUSPEND_SHIFT)))
    #define Columns_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Columns_USBIO_SUSPEND_DEL_SHIFT)))
    #define Columns_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Columns__PC)
    /* Port Configuration */
    #define Columns_PC                 (* (reg32 *) Columns__PC)
#endif
/* Pin State */
#define Columns_PS                     (* (reg32 *) Columns__PS)
/* Data Register */
#define Columns_DR                     (* (reg32 *) Columns__DR)
/* Input Buffer Disable Override */
#define Columns_INP_DIS                (* (reg32 *) Columns__PC2)

/* Interrupt configuration Registers */
#define Columns_INTCFG                 (* (reg32 *) Columns__INTCFG)
#define Columns_INTSTAT                (* (reg32 *) Columns__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Columns_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Columns__SIO)
    #define Columns_SIO_REG            (* (reg32 *) Columns__SIO)
#endif /* (Columns__SIO_CFG) */

/* USBIO registers */
#if !defined(Columns__PC) && (CY_PSOC4_4200L)
    #define Columns_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Columns_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Columns_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Columns_DRIVE_MODE_SHIFT       (0x00u)
#define Columns_DRIVE_MODE_MASK        (0x07u << Columns_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Columns_H */


/* [] END OF FILE */
