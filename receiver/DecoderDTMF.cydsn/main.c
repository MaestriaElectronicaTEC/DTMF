/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include <stdio.h>
#include <math.h>

/* Project Defines */
#define FALSE  0
#define TRUE   1
#define TRANSMIT_BUFFER_SIZE  16

/* DMA Defines */
#define REQUEST_PER_BURST        (1u)
#define BYTES_PER_BURST          (1u)
#define UPPER_SRC_ADDRESS        CYDEV_PERIPH_BASE
#define UPPER_DEST_ADDRESS       CYDEV_PERIPH_BASE

    /* Flags used to store transmit data commands */
    uint8 ContinuouslySendData;
    uint8 SendSingleByte;
    uint8 SendEmulatedData;
    /* Transmit Buffer */
    char TransmitBuffer[TRANSMIT_BUFFER_SIZE];
    /* Variable used to send emulated data */
    uint8 EmulatedData;
    uint8 output;
    uint16 sampler_counter = 0;

void DMA_Config(void);

//UART transmit interrupt
CY_ISR_PROTO(Transmit);

CY_ISR(Transmit)
{   
    /* Send data based on last UART command */
    if(SendSingleByte || ContinuouslySendData)
    {
        sampler_counter++;
        
        if (2000 == sampler_counter) {
            ContinuouslySendData = FALSE;
            sampler_counter = 0;
        }
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%d\r\n", output);
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        /* Reset the send once flag */
        SendSingleByte = FALSE;
    }
    else if(SendEmulatedData)
    {
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%x\r\n", EmulatedData);
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        EmulatedData++;
        /* Reset the send once flag */
        SendEmulatedData = FALSE;   
    }        
}


/*******************************************************************************
* Interrupt
********************************************************************************
* Interrupt generated on Filter sample-ready. Interrupt handle:filterVDAC
*
* Summary:
*  The interrupt performs following functions:
*   1: Reads the left-justified register for Filter Channel A
*   2: Converts it into an unsigned value
*   3: Writes this value to VDAC
*
*******************************************************************************/
CY_ISR(filterVDAC)
{
    /* Convert the 2's complement value to an unsigned 8-bit value
     * The VDAC expects an unsigned 8-bit value as input.
     */
    output = Filter_Read8(Filter_CHANNEL_A)+32u;
	VDAC8_SetValue(output);
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1: Enables global interrupts
*   2: Start all components on the schematic
*   3: Calls a function to configure DMA

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

    /* Start all components used on schematic */
    ADC_DelSig_IRQ_Start();
    isr_StartEx(filterVDAC);
    isrTimer_StartEx(Transmit);
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();
    VDAC8_Start();
    WaveDAC8_Start();
    Filter_Start();
    Timer_Start();
    UART_1_Start();
    
    uint16 CLOCK_DIVIDER_VALUE = 48000;
    

    /* Initialize Variables */
    ContinuouslySendData = FALSE;
    SendSingleByte = FALSE;
    SendEmulatedData = FALSE;
    EmulatedData = 0;
    
    /* Send message to verify COM port is connected properly */
    UART_1_PutString("COM Port Open");
    
    /* User-implemented function to set-up DMA */
    DMA_Config();

    /* Enable Global Interrupts */
    CYGlobalIntEnable;

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
            case 'C':
            case 'c':
                SendSingleByte = TRUE;
                break;
            case 'S':
            case 's':
                ContinuouslySendData = TRUE;
                break;
            case 'X':
            case 'x':
                ContinuouslySendData = FALSE;
                break;
            case 'E':
            case 'e':
                SendEmulatedData = TRUE;
                break;
            
            case '0':
                WaveClock_SetDividerValue(48000);
                break;
            
            case '1':
                WaveClock_SetDividerValue(24000);
                break;
            
            case '2':
                WaveClock_SetDividerValue(12000);
                break;
            
            case '3':
                WaveClock_SetDividerValue(6000);
                break;
            
            case '4':
                WaveClock_SetDividerValue(3000);
                break;
            
            case '5':
                WaveClock_SetDividerValue(1500);
                break;
            
            case '6':
                WaveClock_SetDividerValue(750);
                break;
            
            case '7':
                WaveClock_SetDividerValue(375);
                break;
            
            case '8':
                WaveClock_SetDividerValue(187);
                break;
            
            case '9':
                WaveClock_SetDividerValue(94);
                break;
            
            
            
            
            default:
                /* Place error handling code here */
                break;    
        }
        
    }
} /* End of main */


///////////////////////////
uint16 goertezel_buffer;

#define DTMF_679 679
#define DTMF_770 770
#define DTMF_852 852
#define DTMF_941 941
#define DTMF_1209 1209
#define DTMF_1336 1336
#define DTMF_1477 1477

#define SAMPLE_FRECUENCY 8000
#define SAMPLES 8000

/**
* Goertezel Algorithm
*/
double goertzel_filter(double in_signal[], double frecuency_detect, uint16 samples);

double goertzel_filter(double in_signal[], double frecuency_detect, uint16 samples)
{
    double vk;
    double vk_1 = 0.0;
    double vk_2 = 0.0;
    double cos_coeff;
    double k;
    double power;
  
    int i;
    
    cos_coeff = 2*cos(2*M_PI*frecuency_detect/SAMPLE_FRECUENCY); 
    
    for (i = 0; i < samples; i++){
        vk = cos_coeff * vk_1 - vk_2 + in_signal[i];
        vk_2 = vk_1;
        vk_1 = vk;
    }
    
    power = (vk_1 * vk_1) + (vk_2 * vk_2) - (cos_coeff * vk_1 * vk_2);
    
    return power;    
}

/**
* Goertezel Coefficient Axx
*/
double goertzel_coefficient(double xk, uint16 samples);

double goertzel_coefficient(double xk, uint16 samples)
{
    double ak;
    
    ak = (2/samples) * sqrt(xk);
    
    return ak;     
}

/**
* Goertzel Init
*/
void goertzel_init();

// ToDo
double a_signal[8000];

void goertzel_compute()
{
    double h18, h20, h22, h24, h31, h34, h38;
    double a18, a20, a22, a24, a31, a34, a38;
    double thr;
    
    // each of the 7 filters with different frequencies to revise
    h18 = goertzel_filter(a_signal, DTMF_679, SAMPLES);
    h20 = goertzel_filter(a_signal, DTMF_770, SAMPLES);
    h22 = goertzel_filter(a_signal, DTMF_852, SAMPLES);
    h24 = goertzel_filter(a_signal, DTMF_941, SAMPLES);
    h31 = goertzel_filter(a_signal, DTMF_1209, SAMPLES);
    h34 = goertzel_filter(a_signal, DTMF_1336, SAMPLES);
    h38 = goertzel_filter(a_signal, DTMF_1477, SAMPLES);
    
    // each of the coefficientes Axx to retrieve the single-sided amplituded spectrum 
    a18 = goertzel_coefficient(h18, SAMPLES);
    a20 = goertzel_coefficient(h20, SAMPLES);
    a22 = goertzel_coefficient(h22, SAMPLES);
    a24 = goertzel_coefficient(h24, SAMPLES);
    a31 = goertzel_coefficient(h31, SAMPLES);
    a34 = goertzel_coefficient(h34, SAMPLES);
    a38 = goertzel_coefficient(h38, SAMPLES);
    
    // Threshold that needs to be overpassed to detect a tone
    thr = (a18 + a20 + a22 + a24 + a31 + a34 + a38)/4;
    
    // If-else statements
    
    // First row
    if (a18 > thr && a31 > thr) {
        //ToDo: take action
        printf("The key is 1\n");
        
    } else if (a18 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 2\n");
        
    } else if (a18 > thr && a38 > thr) {
        //ToDo: take action
        printf("The key is 3\n");
        
        
    // Second row
    } else if (a20 > thr && a31 > thr) {
        //ToDo: take action
        printf("The key is 4\n");
        
    } else if (a20 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 5\n");
        
    } else if (a20 > thr && a38 > thr) {
        //ToDo: take action
        printf("The key is 6\n");
        
      
    // Third row
    } else if (a22 > thr && a31 > thr) {
        //ToDo: take action
        printf("The key is 7\n");
        
    } else if (a22 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 8\n");
        
    } else if (a22 > thr && a38 > thr) {
        //ToDo: take action
        printf("The key is 9\n");
       
        
    // Fourth row    
    } else if (a24 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 0\n");
    }
}

///////////////////////////


/*******************************************************************************
* Function Name: DMA_Config
********************************************************************************
*
* Summary:
*  Initializes and sets up DMA for use (generated by DMA Wizard)
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DMA_Config(void)
{
    /* Declare variable to hold the handle for DMA channel */
    uint8 channelHandle;

    /* Declare DMA Transaction Descriptor for memory transfer into
     * Filter Channel.
     */
    uint8 tdChanA;

    /* Configure the DMA to Transfer the data in 1 burst with individual trigger
     * for each burst.
     */
    channelHandle = DMA_DmaInitialize(BYTES_PER_BURST, REQUEST_PER_BURST,
                                        HI16(UPPER_SRC_ADDRESS), HI16(UPPER_DEST_ADDRESS));

    /* This function allocates a TD for use with an initialized DMA channel */
    tdChanA = CyDmaTdAllocate();

    /* Configure the tdChanA to transfer 1 byte with no next TD */
    CyDmaTdSetConfiguration(tdChanA, 1u, DMA_INVALID_TD, 0u);

    /* Set the source address as ADC_DelSig and the destination as
     * Filter Channel A.
     */
    CyDmaTdSetAddress(tdChanA, LO16((uint32)ADC_DelSig_DEC_SAMP_PTR), LO16((uint32)Filter_STAGEAH_PTR));
    
    /* Set the source address as ADC_DelSig and the destination to be the Processing Unit
     */
    CyDmaTdSetAddress(tdChanA, LO16((uint32)ADC_DelSig_DEC_SAMP_PTR), goertezel_buffer);

    /* Set tdChanA to be the initial TD associated with channelHandle */
    CyDmaChSetInitialTd(channelHandle, tdChanA);

    /* Enable the DMA channel represented by channelHandle and preserve the TD */
    CyDmaChEnable(channelHandle, 1u);
}





/* [] END OF FILE */
