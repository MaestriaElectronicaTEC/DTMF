/******************************************************************************
* Project Name		: CE95277 ADC and UART
* File Name			: main.c
* Version 			: **
* Device Used		: CY8C5888LTI-LP097
* Software Used		: PSoC Creator 3.1 SP2
* Compiler    		: ARM GCC 4.8.4, ARM RVDS Generic, ARM MDK Generic
* Related Hardware	: CY8CKIT059 PSoC 5 LP Prototyping Kit 
* Owner				: KLMZ
*
********************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
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
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
*******************************************************************************/

#include <device.h>
#include "stdio.h"

/* Project Defines */
#define FALSE  0
#define TRUE   1
#define TRANSMIT_BUFFER_SIZE  16
#define TONE_DURATION_MS 65 /* Duration of tone in mSec */
#define TONE_SPACE_MS 65 /* Duration of space between tones in mSec */
#define TONE_PAUSE_MS 100 /* Pause caused by invalid code */

/* Function prototypes */
void DialNumber( char * number );
void PlayTones( char key );
int8 KeyIndex(char * keyString, char key);

char keyCodes[] = "123A456B789C*0#D"; /* Valid character array */
/* The tables below store the dividers loaded into */
/* the counter period register to generate the row */
/* and column tones. */

/* Row Tones (Hz) 697  770  852  941      */
uint8 rowDiv[] = {214, 194, 175, 158};

/* Col Tones (Hz) 1209  1336  1477  1633  */
uint8 colDiv[] = { 198,  179,  161,  146};

/* Transmit Buffer */
char TransmitBuffer[TRANSMIT_BUFFER_SIZE];

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  main() performs following functions:
*  1: Starts the ADC and UART components.
*  2: Checks for ADC end of conversion.  Stores latest result in output
*     if conversion complete.
*  3: Checks for UART input.
*     On 'C' or 'c' received: transmits the last sample via the UART.
*     On 'S' or 's' received: continuously transmits samples as they are completed.
*     On 'X' or 'x' received: stops continuously transmitting samples.
*     On 'E' or 'e' received: transmits a dummy byte of data.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    /* Variable to store UART received character */
    uint8 Ch;
    
    /* Start the components */
    UART_1_Start();
    ToneClock_Stop();
	Row_Divider_Start();
	Col_Divider_Start();
	Row_Tone_Start();
	Col_Tone_Start();
	DTMF_Buffer_Start();
    
    /* Send message to verify COM port is connected properly */
    UART_1_PutString("COM Port Open\r\n");
    
    for(;;)
    {        
        /* Non-blocking call to get the latest data recieved  */
        Ch = UART_1_GetChar();
        
        /* Set flags based on UART command */
        switch(Ch)
        {
            case 0:
                /* No new data was recieved */
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '*':
            case '#':
                sprintf(TransmitBuffer, "Key pressed: %s\r\n", (char*)&Ch);
                UART_1_PutString(TransmitBuffer);
                DialNumber((char*)&Ch);
                break;
            default:
                /* Place error handling code here */
                break;    
        }
        
    }
}

/*******************************************************************************
* Function Name: DialNumber( char * number )
********************************************************************************
*
* Summary:
* This function dials the number passed to it in a character string. After
* the number has been dialed the funtions returns.
*
* Parameters:
* char * number: Pointer to phone number string.
*
* Return:
* void
*
*******************************************************************************/
void DialNumber( char * number )
{
    uint8 c = 0;
    while( number[c] != 0 ) /* Step through the dial string */
    {
        PlayTones( number[c] ); /* Play tone for each digit */
        CyDelay(TONE_SPACE_MS); /* Wait minimum space between tones */
        c++;
    }
}

/*******************************************************************************
* Function Name: PlayTones( )
********************************************************************************
*
* Summary:
* Generates the two tones required to dial the given key code. The valid
* dial characters are "1 2 3 4 5 6 7 8 9 0 A B C D * #". Any invalid
* character will generate a pause.
*
* Parameters:
* char key: Keypad character to be dialed.
*
* Return:
* void
*
*******************************************************************************/
void PlayTones( char key )
{
    int8 idx;
    uint8 row_div, col_div;

    idx = KeyIndex(keyCodes, key); /* Convert key to "keyCodes" array index */
    if (idx >= 0 ) /* Is key valid */
    { /* Valid Key */
        col_div = colDiv[(uint8)(idx & 0x03)]; /* Get divider for column tone */
        row_div = rowDiv[(uint8)((idx >> 2)& 0x03)];/* Get divider for row tone */

        Row_Divider_WritePeriod(row_div);             /* Set both dividers  */
        Col_Divider_WritePeriod(col_div);
        ToneClock_Start();                            /* Turn on clock */
        CyDelay(TONE_DURATION_MS);                    /* Wait for the tone duration */
        ToneClock_Stop();                             /* Turn off clock */
        
        UART_1_PutString("Stop tone \r\n");
    }
    else /* Invalid key, just pause for set period of time. */
    {
        CyDelay(TONE_PAUSE_MS);
    }
}

/*******************************************************************************
* Function Name: KeyIndex( )
********************************************************************************
*
* Summary:
* This function finds the location of a character in a string and returns
* the index. If the character is not found a -1 is returned.
*
* Parameters:
* char * keyString: String to search through. This strings should be null
* terminated and less than 255 characters in lenth.
* char key: Character to find in "String".
*
* Return:
* int8: Index of "key" in "keyString". If not found, return -1.
*
*******************************************************************************/
int8 KeyIndex(char * keyString, char key)
{
    int8 i; /* String index */
    int8 charLoc = -1; /* Location of character in string */

    /* Search through string for character match */
    for(i=0; (keyString[i] != 0); i++)
    {
        /* If character is found return index in string */
        if (key == keyString[i])
        {
            charLoc = i;
            break;
        }
    }
    return charLoc;
}

/* [] END OF FILE */
