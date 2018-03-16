/*******************************************************************************
* File Name: KeyPad.h  
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

#if !defined(CY_PINS_KeyPad_H) /* Pins KeyPad_H */
#define CY_PINS_KeyPad_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "KeyPad_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 KeyPad__PORT == 15 && ((KeyPad__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    KeyPad_Write(uint8 value);
void    KeyPad_SetDriveMode(uint8 mode);
uint8   KeyPad_ReadDataReg(void);
uint8   KeyPad_Read(void);
void    KeyPad_SetInterruptMode(uint16 position, uint16 mode);
uint8   KeyPad_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the KeyPad_SetDriveMode() function.
     *  @{
     */
        #define KeyPad_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define KeyPad_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define KeyPad_DM_RES_UP          PIN_DM_RES_UP
        #define KeyPad_DM_RES_DWN         PIN_DM_RES_DWN
        #define KeyPad_DM_OD_LO           PIN_DM_OD_LO
        #define KeyPad_DM_OD_HI           PIN_DM_OD_HI
        #define KeyPad_DM_STRONG          PIN_DM_STRONG
        #define KeyPad_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define KeyPad_MASK               KeyPad__MASK
#define KeyPad_SHIFT              KeyPad__SHIFT
#define KeyPad_WIDTH              8u

/* Interrupt constants */
#if defined(KeyPad__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in KeyPad_SetInterruptMode() function.
     *  @{
     */
        #define KeyPad_INTR_NONE      (uint16)(0x0000u)
        #define KeyPad_INTR_RISING    (uint16)(0x0001u)
        #define KeyPad_INTR_FALLING   (uint16)(0x0002u)
        #define KeyPad_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define KeyPad_INTR_MASK      (0x01u) 
#endif /* (KeyPad__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define KeyPad_PS                     (* (reg8 *) KeyPad__PS)
/* Data Register */
#define KeyPad_DR                     (* (reg8 *) KeyPad__DR)
/* Port Number */
#define KeyPad_PRT_NUM                (* (reg8 *) KeyPad__PRT) 
/* Connect to Analog Globals */                                                  
#define KeyPad_AG                     (* (reg8 *) KeyPad__AG)                       
/* Analog MUX bux enable */
#define KeyPad_AMUX                   (* (reg8 *) KeyPad__AMUX) 
/* Bidirectional Enable */                                                        
#define KeyPad_BIE                    (* (reg8 *) KeyPad__BIE)
/* Bit-mask for Aliased Register Access */
#define KeyPad_BIT_MASK               (* (reg8 *) KeyPad__BIT_MASK)
/* Bypass Enable */
#define KeyPad_BYP                    (* (reg8 *) KeyPad__BYP)
/* Port wide control signals */                                                   
#define KeyPad_CTL                    (* (reg8 *) KeyPad__CTL)
/* Drive Modes */
#define KeyPad_DM0                    (* (reg8 *) KeyPad__DM0) 
#define KeyPad_DM1                    (* (reg8 *) KeyPad__DM1)
#define KeyPad_DM2                    (* (reg8 *) KeyPad__DM2) 
/* Input Buffer Disable Override */
#define KeyPad_INP_DIS                (* (reg8 *) KeyPad__INP_DIS)
/* LCD Common or Segment Drive */
#define KeyPad_LCD_COM_SEG            (* (reg8 *) KeyPad__LCD_COM_SEG)
/* Enable Segment LCD */
#define KeyPad_LCD_EN                 (* (reg8 *) KeyPad__LCD_EN)
/* Slew Rate Control */
#define KeyPad_SLW                    (* (reg8 *) KeyPad__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define KeyPad_PRTDSI__CAPS_SEL       (* (reg8 *) KeyPad__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define KeyPad_PRTDSI__DBL_SYNC_IN    (* (reg8 *) KeyPad__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define KeyPad_PRTDSI__OE_SEL0        (* (reg8 *) KeyPad__PRTDSI__OE_SEL0) 
#define KeyPad_PRTDSI__OE_SEL1        (* (reg8 *) KeyPad__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define KeyPad_PRTDSI__OUT_SEL0       (* (reg8 *) KeyPad__PRTDSI__OUT_SEL0) 
#define KeyPad_PRTDSI__OUT_SEL1       (* (reg8 *) KeyPad__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define KeyPad_PRTDSI__SYNC_OUT       (* (reg8 *) KeyPad__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(KeyPad__SIO_CFG)
    #define KeyPad_SIO_HYST_EN        (* (reg8 *) KeyPad__SIO_HYST_EN)
    #define KeyPad_SIO_REG_HIFREQ     (* (reg8 *) KeyPad__SIO_REG_HIFREQ)
    #define KeyPad_SIO_CFG            (* (reg8 *) KeyPad__SIO_CFG)
    #define KeyPad_SIO_DIFF           (* (reg8 *) KeyPad__SIO_DIFF)
#endif /* (KeyPad__SIO_CFG) */

/* Interrupt Registers */
#if defined(KeyPad__INTSTAT)
    #define KeyPad_INTSTAT            (* (reg8 *) KeyPad__INTSTAT)
    #define KeyPad_SNAP               (* (reg8 *) KeyPad__SNAP)
    
	#define KeyPad_0_INTTYPE_REG 		(* (reg8 *) KeyPad__0__INTTYPE)
	#define KeyPad_1_INTTYPE_REG 		(* (reg8 *) KeyPad__1__INTTYPE)
	#define KeyPad_2_INTTYPE_REG 		(* (reg8 *) KeyPad__2__INTTYPE)
	#define KeyPad_3_INTTYPE_REG 		(* (reg8 *) KeyPad__3__INTTYPE)
	#define KeyPad_4_INTTYPE_REG 		(* (reg8 *) KeyPad__4__INTTYPE)
	#define KeyPad_5_INTTYPE_REG 		(* (reg8 *) KeyPad__5__INTTYPE)
	#define KeyPad_6_INTTYPE_REG 		(* (reg8 *) KeyPad__6__INTTYPE)
	#define KeyPad_7_INTTYPE_REG 		(* (reg8 *) KeyPad__7__INTTYPE)
#endif /* (KeyPad__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_KeyPad_H */


/* [] END OF FILE */
