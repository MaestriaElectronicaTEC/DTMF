/*******************************************************************************
* File Name: Notification.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
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
#include "cypins.h"
#include "Notification_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Notification__PORT == 15 && ((Notification__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Notification_Write(uint8 value);
void    Notification_SetDriveMode(uint8 mode);
uint8   Notification_ReadDataReg(void);
uint8   Notification_Read(void);
void    Notification_SetInterruptMode(uint16 position, uint16 mode);
uint8   Notification_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Notification_SetDriveMode() function.
     *  @{
     */
        #define Notification_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Notification_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Notification_DM_RES_UP          PIN_DM_RES_UP
        #define Notification_DM_RES_DWN         PIN_DM_RES_DWN
        #define Notification_DM_OD_LO           PIN_DM_OD_LO
        #define Notification_DM_OD_HI           PIN_DM_OD_HI
        #define Notification_DM_STRONG          PIN_DM_STRONG
        #define Notification_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Notification_MASK               Notification__MASK
#define Notification_SHIFT              Notification__SHIFT
#define Notification_WIDTH              1u

/* Interrupt constants */
#if defined(Notification__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Notification_SetInterruptMode() function.
     *  @{
     */
        #define Notification_INTR_NONE      (uint16)(0x0000u)
        #define Notification_INTR_RISING    (uint16)(0x0001u)
        #define Notification_INTR_FALLING   (uint16)(0x0002u)
        #define Notification_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Notification_INTR_MASK      (0x01u) 
#endif /* (Notification__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Notification_PS                     (* (reg8 *) Notification__PS)
/* Data Register */
#define Notification_DR                     (* (reg8 *) Notification__DR)
/* Port Number */
#define Notification_PRT_NUM                (* (reg8 *) Notification__PRT) 
/* Connect to Analog Globals */                                                  
#define Notification_AG                     (* (reg8 *) Notification__AG)                       
/* Analog MUX bux enable */
#define Notification_AMUX                   (* (reg8 *) Notification__AMUX) 
/* Bidirectional Enable */                                                        
#define Notification_BIE                    (* (reg8 *) Notification__BIE)
/* Bit-mask for Aliased Register Access */
#define Notification_BIT_MASK               (* (reg8 *) Notification__BIT_MASK)
/* Bypass Enable */
#define Notification_BYP                    (* (reg8 *) Notification__BYP)
/* Port wide control signals */                                                   
#define Notification_CTL                    (* (reg8 *) Notification__CTL)
/* Drive Modes */
#define Notification_DM0                    (* (reg8 *) Notification__DM0) 
#define Notification_DM1                    (* (reg8 *) Notification__DM1)
#define Notification_DM2                    (* (reg8 *) Notification__DM2) 
/* Input Buffer Disable Override */
#define Notification_INP_DIS                (* (reg8 *) Notification__INP_DIS)
/* LCD Common or Segment Drive */
#define Notification_LCD_COM_SEG            (* (reg8 *) Notification__LCD_COM_SEG)
/* Enable Segment LCD */
#define Notification_LCD_EN                 (* (reg8 *) Notification__LCD_EN)
/* Slew Rate Control */
#define Notification_SLW                    (* (reg8 *) Notification__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Notification_PRTDSI__CAPS_SEL       (* (reg8 *) Notification__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Notification_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Notification__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Notification_PRTDSI__OE_SEL0        (* (reg8 *) Notification__PRTDSI__OE_SEL0) 
#define Notification_PRTDSI__OE_SEL1        (* (reg8 *) Notification__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Notification_PRTDSI__OUT_SEL0       (* (reg8 *) Notification__PRTDSI__OUT_SEL0) 
#define Notification_PRTDSI__OUT_SEL1       (* (reg8 *) Notification__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Notification_PRTDSI__SYNC_OUT       (* (reg8 *) Notification__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Notification__SIO_CFG)
    #define Notification_SIO_HYST_EN        (* (reg8 *) Notification__SIO_HYST_EN)
    #define Notification_SIO_REG_HIFREQ     (* (reg8 *) Notification__SIO_REG_HIFREQ)
    #define Notification_SIO_CFG            (* (reg8 *) Notification__SIO_CFG)
    #define Notification_SIO_DIFF           (* (reg8 *) Notification__SIO_DIFF)
#endif /* (Notification__SIO_CFG) */

/* Interrupt Registers */
#if defined(Notification__INTSTAT)
    #define Notification_INTSTAT            (* (reg8 *) Notification__INTSTAT)
    #define Notification_SNAP               (* (reg8 *) Notification__SNAP)
    
	#define Notification_0_INTTYPE_REG 		(* (reg8 *) Notification__0__INTTYPE)
#endif /* (Notification__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Notification_H */


/* [] END OF FILE */
