/*******************************************************************************
* File Name: Rows.h  
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

#if !defined(CY_PINS_Rows_ALIASES_H) /* Pins Rows_ALIASES_H */
#define CY_PINS_Rows_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Rows_0			(Rows__0__PC)
#define Rows_0_PS		(Rows__0__PS)
#define Rows_0_PC		(Rows__0__PC)
#define Rows_0_DR		(Rows__0__DR)
#define Rows_0_SHIFT	(Rows__0__SHIFT)
#define Rows_0_INTR	((uint16)((uint16)0x0003u << (Rows__0__SHIFT*2u)))

#define Rows_1			(Rows__1__PC)
#define Rows_1_PS		(Rows__1__PS)
#define Rows_1_PC		(Rows__1__PC)
#define Rows_1_DR		(Rows__1__DR)
#define Rows_1_SHIFT	(Rows__1__SHIFT)
#define Rows_1_INTR	((uint16)((uint16)0x0003u << (Rows__1__SHIFT*2u)))

#define Rows_2			(Rows__2__PC)
#define Rows_2_PS		(Rows__2__PS)
#define Rows_2_PC		(Rows__2__PC)
#define Rows_2_DR		(Rows__2__DR)
#define Rows_2_SHIFT	(Rows__2__SHIFT)
#define Rows_2_INTR	((uint16)((uint16)0x0003u << (Rows__2__SHIFT*2u)))

#define Rows_3			(Rows__3__PC)
#define Rows_3_PS		(Rows__3__PS)
#define Rows_3_PC		(Rows__3__PC)
#define Rows_3_DR		(Rows__3__DR)
#define Rows_3_SHIFT	(Rows__3__SHIFT)
#define Rows_3_INTR	((uint16)((uint16)0x0003u << (Rows__3__SHIFT*2u)))

#define Rows_INTR_ALL	 ((uint16)(Rows_0_INTR| Rows_1_INTR| Rows_2_INTR| Rows_3_INTR))


#endif /* End Pins Rows_ALIASES_H */


/* [] END OF FILE */
