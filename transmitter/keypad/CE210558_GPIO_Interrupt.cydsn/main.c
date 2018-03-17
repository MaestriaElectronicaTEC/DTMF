/*****************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
* In this project, custom ISR is created for the GPIO interrupt. The file -  
* "InterruptRoutine.c" contains user ISR for the interrupt. Pin P0[0] is  
* configured with rising edge interrupt and P0[1] is configured with falling 
* edge interrupt. In the ISR, Logic 0  is written at LED pin (port P0[2]) on 
* the rising edge interrupt and Logic 1 is written on falling edge interrupt. 
* For testing purposes, both the interrupt pins - P0[0] and P0[1] can be shorted 
* externally and driven with the same signal.
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

#include <project.h>
#include <stdio.h>
#include "cyfitter.h"

/* Project Defines */
//#define TRANSMIT_BUFFER_SIZE  16

    /* Transmit Buffers */
    /*char rowsBuffer[TRANSMIT_BUFFER_SIZE];
    char columnsBuffer[TRANSMIT_BUFFER_SIZE];*/
    //char keyPadBuffer[TRANSMIT_BUFFER_SIZE];
    /* Variables for output data */
    /*uint8 rowsOutput;
    uint8 columnsOutput;*/
    //uint8 keyPadOutput;

//UART transmit interrupt for rows and columns
/*CY_ISR_PROTO(Transmit_Rows);
CY_ISR_PROTO(Transmit_Columns);*/
/*CY_ISR_PROTO(Transmit_KeyPad);

CY_ISR_PROTO(Transmit_KeyPad)
{
    CyDelay(50);
    char8 keyPressed;					
		
	keyPressed = KeyPad_GetButton();		//Value recieved from Matrix
    UART_1_PutChar(keyPressed);
}*/

/*CY_ISR_PROTO(Transmit_Rows)
{
    CyDelay(50);
    rowsOutput = Rows_Read();
    
    if (rowsOutput > 0)
    {
        sprintf(rowsBuffer, "%d\r\n", rowsOutput);
        UART_1_PutString(rowsBuffer);
    }
}

CY_ISR_PROTO(Transmit_Columns)
{
    CyDelay(50);
    columnsOutput = Columns_Read();
    
    if (columnsOutput > 0)
    {
        sprintf(columnsBuffer, "%d\r\n", columnsOutput);
        UART_1_PutString(columnsBuffer);
    }
}*/
char8 KeyPad_Key[4][4] = {
					{'1','2','3','A'},		//Row 0
					
					{'4','5','6','B'},		//Row 1
										
					{'7','8','9','C'},		//Row 2
					
					{'*','0','#','D'}		//Row 3
				  };
    
uint8 KeyPad_GetCol(void)
{
	uint8 column;
		
	while(!(KeyPad_Read() & 0x10));	//Wait for a valid press of button
	
	if(KeyPad_Read() & 0x10)			//Check for a valid press of button
	{
		column = KeyPad_Read();
	}
	
	column = (column & 0x03);										//Extract correct Column
	
	return (column);
}

uint8 KeyPad_GetRow(void)
{
	uint8 row;
	
	while(!(KeyPad_Read() & 0x10));	//Wait for a valid press of button
	
	if(KeyPad_Read() & 0x10)			//Check for a valid press of button
	{
		row = KeyPad_Read();
	}
		
	row = (row & 0x0C) >> 2;								//Extract correct Row
	
	return row;
}

char8 KeyPad_GetButton(void)
{
	char8 button;
	
	uint8 row,col;
	
	row = KeyPad_GetRow();
    
    col = KeyPad_GetCol();

	button = KeyPad_Key[row][col];										//Assign correct Character
	
	while(!(KeyPad_Read() & 0x10));	//Wait for a valid press of button
	
	return button;
}

/*CY_ISR_PROTO(Transmit_KeyPad);

CY_ISR(Transmit_KeyPad)
{
    //CyDelay(50);
    char8 keyPressed;					
		
	keyPressed = KeyPad_GetButton();		//Value recieved from Matrix
    UART_1_PutChar(keyPressed);
}*/


int main()
{	
    /* Disable global interrupt */
    //CyGlobalIntDisable;
    
    /* Start all components used on schematic */
    /*isr_rows_StartEx(Transmit_Rows);
    isr_columns_StartEx(Transmit_Columns);*/
    //isr_keypad_StartEx(Transmit_KeyPad);
    UART_1_Start();
    
    /* Send message to verify COM port is connected properly */
    UART_1_PutString("COM Port Open");

	/* Enable global interrupt */
    CyGlobalIntEnable;

    for(;;)
    {
		/* wait here */
        /*CyDelay(500);
        keyPadOutput = KeyPad_Read();
        if (keyPadOutput > 0)
        {
            sprintf(keyPadBuffer, "%d\r\n", keyPadOutput);
            UART_1_PutString(keyPadBuffer);
        }*/
        /*char8 keyPressed;						
	    keyPressed = KeyPad_GetButton();		//Value recieved from Matrix
        sprintf(keyPadBuffer, "%c\r\n", keyPressed);
        UART_1_PutString(keyPadBuffer);*/
        char8 keyPressed;					
		
	    keyPressed = KeyPad_GetButton();		//Value recieved from Matrix
        UART_1_PutChar(keyPressed);
    }
}

/* [] END OF FILE */
