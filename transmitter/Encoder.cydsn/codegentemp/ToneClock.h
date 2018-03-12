/*******************************************************************************
* File Name: ToneClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ToneClock_H)
#define CY_CLOCK_ToneClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void ToneClock_Start(void) ;
void ToneClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ToneClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ToneClock_StandbyPower(uint8 state) ;
void ToneClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ToneClock_GetDividerRegister(void) ;
void ToneClock_SetModeRegister(uint8 modeBitMask) ;
void ToneClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 ToneClock_GetModeRegister(void) ;
void ToneClock_SetSourceRegister(uint8 clkSource) ;
uint8 ToneClock_GetSourceRegister(void) ;
#if defined(ToneClock__CFG3)
void ToneClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 ToneClock_GetPhaseRegister(void) ;
#endif /* defined(ToneClock__CFG3) */

#define ToneClock_Enable()                       ToneClock_Start()
#define ToneClock_Disable()                      ToneClock_Stop()
#define ToneClock_SetDivider(clkDivider)         ToneClock_SetDividerRegister(clkDivider, 1u)
#define ToneClock_SetDividerValue(clkDivider)    ToneClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define ToneClock_SetMode(clkMode)               ToneClock_SetModeRegister(clkMode)
#define ToneClock_SetSource(clkSource)           ToneClock_SetSourceRegister(clkSource)
#if defined(ToneClock__CFG3)
#define ToneClock_SetPhase(clkPhase)             ToneClock_SetPhaseRegister(clkPhase)
#define ToneClock_SetPhaseValue(clkPhase)        ToneClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ToneClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ToneClock_CLKEN              (* (reg8 *) ToneClock__PM_ACT_CFG)
#define ToneClock_CLKEN_PTR          ((reg8 *) ToneClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ToneClock_CLKSTBY            (* (reg8 *) ToneClock__PM_STBY_CFG)
#define ToneClock_CLKSTBY_PTR        ((reg8 *) ToneClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ToneClock_DIV_LSB            (* (reg8 *) ToneClock__CFG0)
#define ToneClock_DIV_LSB_PTR        ((reg8 *) ToneClock__CFG0)
#define ToneClock_DIV_PTR            ((reg16 *) ToneClock__CFG0)

/* Clock MSB divider configuration register. */
#define ToneClock_DIV_MSB            (* (reg8 *) ToneClock__CFG1)
#define ToneClock_DIV_MSB_PTR        ((reg8 *) ToneClock__CFG1)

/* Mode and source configuration register */
#define ToneClock_MOD_SRC            (* (reg8 *) ToneClock__CFG2)
#define ToneClock_MOD_SRC_PTR        ((reg8 *) ToneClock__CFG2)

#if defined(ToneClock__CFG3)
/* Analog clock phase configuration register */
#define ToneClock_PHASE              (* (reg8 *) ToneClock__CFG3)
#define ToneClock_PHASE_PTR          ((reg8 *) ToneClock__CFG3)
#endif /* defined(ToneClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ToneClock_CLKEN_MASK         ToneClock__PM_ACT_MSK
#define ToneClock_CLKSTBY_MASK       ToneClock__PM_STBY_MSK

/* CFG2 field masks */
#define ToneClock_SRC_SEL_MSK        ToneClock__CFG2_SRC_SEL_MASK
#define ToneClock_MODE_MASK          (~(ToneClock_SRC_SEL_MSK))

#if defined(ToneClock__CFG3)
/* CFG3 phase mask */
#define ToneClock_PHASE_MASK         ToneClock__CFG3_PHASE_DLY_MASK
#endif /* defined(ToneClock__CFG3) */

#endif /* CY_CLOCK_ToneClock_H */


/* [] END OF FILE */
