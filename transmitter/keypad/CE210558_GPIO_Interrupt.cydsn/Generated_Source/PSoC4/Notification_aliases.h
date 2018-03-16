/*******************************************************************************
* File Name: Notification.h  
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

#if !defined(CY_PINS_Notification_ALIASES_H) /* Pins Notification_ALIASES_H */
#define CY_PINS_Notification_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Notification_0			(Notification__0__PC)
#define Notification_0_PS		(Notification__0__PS)
#define Notification_0_PC		(Notification__0__PC)
#define Notification_0_DR		(Notification__0__DR)
#define Notification_0_SHIFT	(Notification__0__SHIFT)
#define Notification_0_INTR	((uint16)((uint16)0x0003u << (Notification__0__SHIFT*2u)))

#define Notification_INTR_ALL	 ((uint16)(Notification_0_INTR))


#endif /* End Pins Notification_ALIASES_H */


/* [] END OF FILE */
