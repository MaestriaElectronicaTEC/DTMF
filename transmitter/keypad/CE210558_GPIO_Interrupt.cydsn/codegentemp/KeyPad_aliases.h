/*******************************************************************************
* File Name: KeyPad.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_KeyPad_ALIASES_H) /* Pins KeyPad_ALIASES_H */
#define CY_PINS_KeyPad_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define KeyPad_0			(KeyPad__0__PC)
#define KeyPad_0_INTR	((uint16)((uint16)0x0001u << KeyPad__0__SHIFT))

#define KeyPad_1			(KeyPad__1__PC)
#define KeyPad_1_INTR	((uint16)((uint16)0x0001u << KeyPad__1__SHIFT))

#define KeyPad_2			(KeyPad__2__PC)
#define KeyPad_2_INTR	((uint16)((uint16)0x0001u << KeyPad__2__SHIFT))

#define KeyPad_3			(KeyPad__3__PC)
#define KeyPad_3_INTR	((uint16)((uint16)0x0001u << KeyPad__3__SHIFT))

#define KeyPad_4			(KeyPad__4__PC)
#define KeyPad_4_INTR	((uint16)((uint16)0x0001u << KeyPad__4__SHIFT))

#define KeyPad_5			(KeyPad__5__PC)
#define KeyPad_5_INTR	((uint16)((uint16)0x0001u << KeyPad__5__SHIFT))

#define KeyPad_6			(KeyPad__6__PC)
#define KeyPad_6_INTR	((uint16)((uint16)0x0001u << KeyPad__6__SHIFT))

#define KeyPad_7			(KeyPad__7__PC)
#define KeyPad_7_INTR	((uint16)((uint16)0x0001u << KeyPad__7__SHIFT))

#define KeyPad_INTR_ALL	 ((uint16)(KeyPad_0_INTR| KeyPad_1_INTR| KeyPad_2_INTR| KeyPad_3_INTR| KeyPad_4_INTR| KeyPad_5_INTR| KeyPad_6_INTR| KeyPad_7_INTR))

#endif /* End Pins KeyPad_ALIASES_H */


/* [] END OF FILE */
