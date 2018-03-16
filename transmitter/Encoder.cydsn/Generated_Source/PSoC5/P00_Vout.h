/*******************************************************************************
* File Name: P00_Vout.h  
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

#if !defined(CY_PINS_P00_Vout_H) /* Pins P00_Vout_H */
#define CY_PINS_P00_Vout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P00_Vout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P00_Vout__PORT == 15 && ((P00_Vout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P00_Vout_Write(uint8 value);
void    P00_Vout_SetDriveMode(uint8 mode);
uint8   P00_Vout_ReadDataReg(void);
uint8   P00_Vout_Read(void);
void    P00_Vout_SetInterruptMode(uint16 position, uint16 mode);
uint8   P00_Vout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P00_Vout_SetDriveMode() function.
     *  @{
     */
        #define P00_Vout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P00_Vout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P00_Vout_DM_RES_UP          PIN_DM_RES_UP
        #define P00_Vout_DM_RES_DWN         PIN_DM_RES_DWN
        #define P00_Vout_DM_OD_LO           PIN_DM_OD_LO
        #define P00_Vout_DM_OD_HI           PIN_DM_OD_HI
        #define P00_Vout_DM_STRONG          PIN_DM_STRONG
        #define P00_Vout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P00_Vout_MASK               P00_Vout__MASK
#define P00_Vout_SHIFT              P00_Vout__SHIFT
#define P00_Vout_WIDTH              1u

/* Interrupt constants */
#if defined(P00_Vout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P00_Vout_SetInterruptMode() function.
     *  @{
     */
        #define P00_Vout_INTR_NONE      (uint16)(0x0000u)
        #define P00_Vout_INTR_RISING    (uint16)(0x0001u)
        #define P00_Vout_INTR_FALLING   (uint16)(0x0002u)
        #define P00_Vout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P00_Vout_INTR_MASK      (0x01u) 
#endif /* (P00_Vout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P00_Vout_PS                     (* (reg8 *) P00_Vout__PS)
/* Data Register */
#define P00_Vout_DR                     (* (reg8 *) P00_Vout__DR)
/* Port Number */
#define P00_Vout_PRT_NUM                (* (reg8 *) P00_Vout__PRT) 
/* Connect to Analog Globals */                                                  
#define P00_Vout_AG                     (* (reg8 *) P00_Vout__AG)                       
/* Analog MUX bux enable */
#define P00_Vout_AMUX                   (* (reg8 *) P00_Vout__AMUX) 
/* Bidirectional Enable */                                                        
#define P00_Vout_BIE                    (* (reg8 *) P00_Vout__BIE)
/* Bit-mask for Aliased Register Access */
#define P00_Vout_BIT_MASK               (* (reg8 *) P00_Vout__BIT_MASK)
/* Bypass Enable */
#define P00_Vout_BYP                    (* (reg8 *) P00_Vout__BYP)
/* Port wide control signals */                                                   
#define P00_Vout_CTL                    (* (reg8 *) P00_Vout__CTL)
/* Drive Modes */
#define P00_Vout_DM0                    (* (reg8 *) P00_Vout__DM0) 
#define P00_Vout_DM1                    (* (reg8 *) P00_Vout__DM1)
#define P00_Vout_DM2                    (* (reg8 *) P00_Vout__DM2) 
/* Input Buffer Disable Override */
#define P00_Vout_INP_DIS                (* (reg8 *) P00_Vout__INP_DIS)
/* LCD Common or Segment Drive */
#define P00_Vout_LCD_COM_SEG            (* (reg8 *) P00_Vout__LCD_COM_SEG)
/* Enable Segment LCD */
#define P00_Vout_LCD_EN                 (* (reg8 *) P00_Vout__LCD_EN)
/* Slew Rate Control */
#define P00_Vout_SLW                    (* (reg8 *) P00_Vout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P00_Vout_PRTDSI__CAPS_SEL       (* (reg8 *) P00_Vout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P00_Vout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P00_Vout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P00_Vout_PRTDSI__OE_SEL0        (* (reg8 *) P00_Vout__PRTDSI__OE_SEL0) 
#define P00_Vout_PRTDSI__OE_SEL1        (* (reg8 *) P00_Vout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P00_Vout_PRTDSI__OUT_SEL0       (* (reg8 *) P00_Vout__PRTDSI__OUT_SEL0) 
#define P00_Vout_PRTDSI__OUT_SEL1       (* (reg8 *) P00_Vout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P00_Vout_PRTDSI__SYNC_OUT       (* (reg8 *) P00_Vout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P00_Vout__SIO_CFG)
    #define P00_Vout_SIO_HYST_EN        (* (reg8 *) P00_Vout__SIO_HYST_EN)
    #define P00_Vout_SIO_REG_HIFREQ     (* (reg8 *) P00_Vout__SIO_REG_HIFREQ)
    #define P00_Vout_SIO_CFG            (* (reg8 *) P00_Vout__SIO_CFG)
    #define P00_Vout_SIO_DIFF           (* (reg8 *) P00_Vout__SIO_DIFF)
#endif /* (P00_Vout__SIO_CFG) */

/* Interrupt Registers */
#if defined(P00_Vout__INTSTAT)
    #define P00_Vout_INTSTAT            (* (reg8 *) P00_Vout__INTSTAT)
    #define P00_Vout_SNAP               (* (reg8 *) P00_Vout__SNAP)
    
	#define P00_Vout_0_INTTYPE_REG 		(* (reg8 *) P00_Vout__0__INTTYPE)
#endif /* (P00_Vout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P00_Vout_H */


/* [] END OF FILE */
