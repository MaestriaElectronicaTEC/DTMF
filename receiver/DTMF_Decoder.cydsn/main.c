/******************************************************************************
*******************************************************************************/

#include <device.h>
#include <stdio.h>
#include <math.h>

/* Project Defines */
#define FALSE  0
#define TRUE   1
#define TRANSMIT_BUFFER_SIZE  16

/* DTMF specifics */
#define DTMF_679 679.00
#define DTMF_770 770.00
#define DTMF_852 852.00
#define DTMF_941 941.00
#define DTMF_1209 1209.00
#define DTMF_1336 1336.00
#define DTMF_1477 1477.00
//
#define SAMPLING_FREQUENCY 8000.0
#define SAMPLES 2000

/* Variable to store ADC result */
uint16 Output;
/* Flags used to store transmit data commands */
uint8 ContinuouslySendData;
uint8 SendSingleByte;
uint8 SendEmulatedData;
/* Transmit Buffer */
char TransmitBuffer[TRANSMIT_BUFFER_SIZE];
/* Variable used to send emulated data */
uint8 EmulatedData;

uint16 internalCounter = 0;

//uint16 a_signal[SAMPLES];
uint16 a_signal[SAMPLES];

uint8 goertzel_compute();


CY_ISR_PROTO(Transmit);

CY_ISR(Transmit)
{
    
    /* Check to see if an ADC conversion has completed */
    if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS))
    {
        /* Use the GetResult16 API to get an 8 bit unsigned result in
         * single ended mode.  The API CountsTo_mVolts is then used
         * to convert the ADC counts into mV before transmitting via
         * the UART.  See the datasheet API description for more
         * details */
        //Output = ADC_DelSig_1_CountsTo_mVolts(ADC_DelSig_1_GetResult16());
        Output = ADC_DelSig_1_GetResult16();
  
        /* Send data based on last UART command */
        if(SendSingleByte || ContinuouslySendData)
        {
                
            //a_signal[internalCounter] = Output;
            
            // When the amount of samples be
            if(SAMPLES == internalCounter ) 
            {
                ContinuouslySendData = FALSE;
                goertzel_compute();
            }
            
            /* Reset the send once flag */
            SendSingleByte = FALSE;

            // Define the counter incremental
            internalCounter++;
    
        }    
    }
}


//
///**
//* Goertezel Algorithm
//*/
float goertzel_filter(uint16 in_signal[], float frecuency_detect, uint16 samples);

float goertzel_filter(uint16 in_signal[], float frecuency_detect, uint16 samples)
{
    float vk;
    float vk_1 = 0.0;
    float vk_2 = 0.0;
    float cos_coeff;
    float k;
    float power;
  
    int i;
    
    cos_coeff = 2.0*cos(2.0*M_PI*frecuency_detect/SAMPLING_FREQUENCY); 
    
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
float goertzel_coefficient(float xk, uint16 samples);

float goertzel_coefficient(float xk, uint16 samples)
{
    float ak;
    
    ak = (2.0/(float)samples) * sqrt(xk);
        
    return ak;     
}

/**
* Goertzel Init
*/
void goertzel_init();

//
uint8 goertzel_compute()
{
    float h18, h20, h22, h24, h31, h34, h38;
    float a18, a20, a22, a24, a31, a34, a38;
    float thr;
        
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
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 1\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
    } else if (a18 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 2\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 2\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
    } else if (a18 > thr && a38 > thr) {
        //ToDo: take action
        printf("The key is 3\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 3\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
        
    // Second row
    } else if (a20 > thr && a31 > thr) {
        //ToDo: take action
        printf("The key is 4\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 4\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
    } else if (a20 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 5\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 5\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
    } else if (a20 > thr && a38 > thr) {
        //ToDo: take action
        printf("The key is 6\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 6\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
      
    // Third row
    } else if (a22 > thr && a31 > thr) {
        //ToDo: take action
        printf("The key is 7\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 7\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
    } else if (a22 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 8\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 8\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
        
    } else if (a22 > thr && a38 > thr) {
        //ToDo: take action
        printf("The key is 9\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 9\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
       
        
    // Fourth row    
    } else if (a24 > thr && a34 > thr) {
        //ToDo: take action
        printf("The key is 0\n");
        
        /* Format ADC result for transmition */
        sprintf(TransmitBuffer, "%s\r\n", "The key is 0\n");
   
        /* Send out the data */
        UART_1_PutString(TransmitBuffer);
    } 
    
    return 0;
}

/* Synthesize some test data at a given frequency. */
void Generate(float frequency_sin, float frequency_cos)
{
    int	index;
    float step_sin, step_cos;

    step_sin = frequency_sin * ((2.0 * M_PI) / SAMPLING_FREQUENCY);
    step_cos = frequency_cos * ((2.0 * M_PI) / SAMPLING_FREQUENCY);

    /* Generate the test data */
    for (index = 0; index < 2000; index++)
    {
        a_signal[index] = (1000.0 * sin(index * step_sin) + 1000.0) + (1000.0 * cos(index * step_cos) + 1000.0);   
    }
}

///////////////////////////

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
    ADC_DelSig_1_Start();
    UART_1_Start();
    WaveDAC8_Start();
    
    /* Initialize Variables */
    ContinuouslySendData = FALSE;
    SendSingleByte = FALSE;
    SendEmulatedData = FALSE;
    EmulatedData = 0;
    
    /* Start the ADC conversion */
    ADC_DelSig_1_StartConvert();
    
    /* Send message to verify COM port is connected properly */
    UART_1_PutString("COM Port Open \r\n");
    
    Generate(674.0, 1331.0);
    
    Timer_Start();
    isr_StartEx(Transmit);
    CyGlobalIntEnable;
    
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
                
                //SendSingleByte = TRUE;
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
            default:
                /* Place error handling code here */
                break;    
        }
        
    }
}


/* [] END OF FILE */
