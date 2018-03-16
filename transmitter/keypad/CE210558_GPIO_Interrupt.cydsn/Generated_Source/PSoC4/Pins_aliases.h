/*******************************************************************************
* File Name: Pins.h  
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

#if !defined(CY_PINS_Pins_ALIASES_H) /* Pins Pins_ALIASES_H */
#define CY_PINS_Pins_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Pins_0			(Pins__0__PC)
#define Pins_0_PS		(Pins__0__PS)
#define Pins_0_PC		(Pins__0__PC)
#define Pins_0_DR		(Pins__0__DR)
#define Pins_0_SHIFT	(Pins__0__SHIFT)
#define Pins_0_INTR	((uint16)((uint16)0x0003u << (Pins__0__SHIFT*2u)))

#define Pins_1			(Pins__1__PC)
#define Pins_1_PS		(Pins__1__PS)
#define Pins_1_PC		(Pins__1__PC)
#define Pins_1_DR		(Pins__1__DR)
#define Pins_1_SHIFT	(Pins__1__SHIFT)
#define Pins_1_INTR	((uint16)((uint16)0x0003u << (Pins__1__SHIFT*2u)))

#define Pins_INTR_ALL	 ((uint16)(Pins_0_INTR| Pins_1_INTR))
#define Pins_ON			(Pins__ON__PC)
#define Pins_ON_PS		(Pins__ON__PS)
#define Pins_ON_PC		(Pins__ON__PC)
#define Pins_ON_DR		(Pins__ON__DR)
#define Pins_ON_SHIFT	(Pins__ON__SHIFT)
#define Pins_ON_INTR	((uint16)((uint16)0x0003u << (Pins__0__SHIFT*2u)))

#define Pins_OFF			(Pins__OFF__PC)
#define Pins_OFF_PS		(Pins__OFF__PS)
#define Pins_OFF_PC		(Pins__OFF__PC)
#define Pins_OFF_DR		(Pins__OFF__DR)
#define Pins_OFF_SHIFT	(Pins__OFF__SHIFT)
#define Pins_OFF_INTR	((uint16)((uint16)0x0003u << (Pins__1__SHIFT*2u)))


#endif /* End Pins Pins_ALIASES_H */


/* [] END OF FILE */
