/*******************************************************************************
* File Name: Rows.h  
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

#if !defined(CY_PINS_Rows_H) /* Pins Rows_H */
#define CY_PINS_Rows_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rows_aliases.h"


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
} Rows_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Rows_Read(void);
void    Rows_Write(uint8 value);
uint8   Rows_ReadDataReg(void);
#if defined(Rows__PC) || (CY_PSOC4_4200L) 
    void    Rows_SetDriveMode(uint8 mode);
#endif
void    Rows_SetInterruptMode(uint16 position, uint16 mode);
uint8   Rows_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Rows_Sleep(void); 
void Rows_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Rows__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Rows_DRIVE_MODE_BITS        (3)
    #define Rows_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rows_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Rows_SetDriveMode() function.
         *  @{
         */
        #define Rows_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Rows_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Rows_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Rows_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Rows_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Rows_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Rows_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Rows_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Rows_MASK               Rows__MASK
#define Rows_SHIFT              Rows__SHIFT
#define Rows_WIDTH              4u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Rows_SetInterruptMode() function.
     *  @{
     */
        #define Rows_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Rows_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Rows_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Rows_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Rows__SIO)
    #define Rows_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Rows__PC) && (CY_PSOC4_4200L)
    #define Rows_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Rows_USBIO_DISABLE              ((uint32)(~Rows_USBIO_ENABLE))
    #define Rows_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Rows_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Rows_USBIO_ENTER_SLEEP          ((uint32)((1u << Rows_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Rows_USBIO_SUSPEND_DEL_SHIFT)))
    #define Rows_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Rows_USBIO_SUSPEND_SHIFT)))
    #define Rows_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Rows_USBIO_SUSPEND_DEL_SHIFT)))
    #define Rows_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Rows__PC)
    /* Port Configuration */
    #define Rows_PC                 (* (reg32 *) Rows__PC)
#endif
/* Pin State */
#define Rows_PS                     (* (reg32 *) Rows__PS)
/* Data Register */
#define Rows_DR                     (* (reg32 *) Rows__DR)
/* Input Buffer Disable Override */
#define Rows_INP_DIS                (* (reg32 *) Rows__PC2)

/* Interrupt configuration Registers */
#define Rows_INTCFG                 (* (reg32 *) Rows__INTCFG)
#define Rows_INTSTAT                (* (reg32 *) Rows__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Rows_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Rows__SIO)
    #define Rows_SIO_REG            (* (reg32 *) Rows__SIO)
#endif /* (Rows__SIO_CFG) */

/* USBIO registers */
#if !defined(Rows__PC) && (CY_PSOC4_4200L)
    #define Rows_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Rows_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Rows_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Rows_DRIVE_MODE_SHIFT       (0x00u)
#define Rows_DRIVE_MODE_MASK        (0x07u << Rows_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Rows_H */


/* [] END OF FILE */
