/*****************************************************************************
* File Name: InterruptRoutine.c
*
* Version: 1.0
*
* Description:
* The file contains user ISR (as opposed to auto-generated ISRs) for the GPIO 
* interrupt. In the ISR, Logic 0 is written at LED pin (port P0[2]) on the rising  
* edge interrupt and Logic 1 is written on falling edge interrupt. For testing  
* purposes, both the interrupt pins - P0[0] and P0[1] can be shorted externally  
* and driven with the same signal.
*
* Related Document: Code example CE210558
*
* Hardware Dependency: See code example CE210558
*
******************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation.
******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/

#include "InterruptRoutine.h"

CY_ISR(GPIO_ISR)
{
	/* Read the GPIO interrupt status and clear the interrupt */
    
    uint8 rowsOut = Rows_Read();
    uint8 columnsOut = Columns_Read();
    
    if ( rowsOut > 0 && columnsOut > 0 )
    {
        Notification_Write(1);
    }
    else
    {
        Notification_Write(0);
    }
    
	//uint8 InterruptState = Pins_ClearInterrupt();
	
	/* If "ON" pin has triggered interrupt */
	/*if(InterruptState == ON_PIN)
	{
		Turn ON the LED
		Pin_LED_Write(LED_ON);
	}
	else
	If "OFF" pin has triggered interrupt
	if(InterruptState == OFF_PIN)
	{
		Turn OFF the LED
		Pin_LED_Write(LED_OFF);
	}*/
}

/* [] END OF FILE */
