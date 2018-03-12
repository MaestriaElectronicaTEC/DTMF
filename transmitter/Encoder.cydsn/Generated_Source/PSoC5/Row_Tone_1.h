/*******************************************************************************
* File Name: Row_Tone_1.h  
* Version 2.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_Row_Tone_1_H) 
#define CY_WaveDAC8_Row_Tone_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include <Row_Tone_1_Wave1_DMA_dma.h>
#include <Row_Tone_1_Wave2_DMA_dma.h>
#include <Row_Tone_1_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define Row_Tone_1_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define Row_Tone_1_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define Row_Tone_1_SINE_WAVE      (0u)
#define Row_Tone_1_SQUARE_WAVE    (1u)
#define Row_Tone_1_TRIANGLE_WAVE  (2u)
#define Row_Tone_1_SAWTOOTH_WAVE  (3u)
#define Row_Tone_1_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define Row_Tone_1_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define Row_Tone_1_WAVE1_LENGTH   (100u)   /* Length for wave1 */
#define Row_Tone_1_WAVE2_LENGTH   (100u)   /* Length for wave2 */
	
#define Row_Tone_1_DEFAULT_RANGE    (0u) /* Default DAC range */
#define Row_Tone_1_DAC_RANGE_1V     (0u)
#define Row_Tone_1_DAC_RANGE_1V_BUF (16u)
#define Row_Tone_1_DAC_RANGE_4V     (1u)
#define Row_Tone_1_DAC_RANGE_4V_BUF (17u)
#define Row_Tone_1_VOLT_MODE        (0u)
#define Row_Tone_1_CURRENT_MODE     (1u)
#define Row_Tone_1_DAC_MODE         (((Row_Tone_1_DEFAULT_RANGE == Row_Tone_1_DAC_RANGE_1V) || \
									  (Row_Tone_1_DEFAULT_RANGE == Row_Tone_1_DAC_RANGE_4V) || \
							  		  (Row_Tone_1_DEFAULT_RANGE == Row_Tone_1_DAC_RANGE_1V_BUF) || \
									  (Row_Tone_1_DEFAULT_RANGE == Row_Tone_1_DAC_RANGE_4V_BUF)) ? \
									   Row_Tone_1_VOLT_MODE : Row_Tone_1_CURRENT_MODE)

#define Row_Tone_1_DACMODE Row_Tone_1_DAC_MODE /* legacy definition for backward compatibility */

#define Row_Tone_1_DIRECT_MODE (0u)
#define Row_Tone_1_BUFFER_MODE (1u)
#define Row_Tone_1_OUT_MODE    (((Row_Tone_1_DEFAULT_RANGE == Row_Tone_1_DAC_RANGE_1V_BUF) || \
								 (Row_Tone_1_DEFAULT_RANGE == Row_Tone_1_DAC_RANGE_4V_BUF)) ? \
								  Row_Tone_1_BUFFER_MODE : Row_Tone_1_DIRECT_MODE)

#if(Row_Tone_1_OUT_MODE == Row_Tone_1_BUFFER_MODE)
    #include <Row_Tone_1_BuffAmp.h>
#endif /* Row_Tone_1_OUT_MODE == Row_Tone_1_BUFFER_MODE */

#define Row_Tone_1_CLOCK_INT      (1u)
#define Row_Tone_1_CLOCK_EXT      (0u)
#define Row_Tone_1_CLOCK_SRC      (0u)

#if(Row_Tone_1_CLOCK_SRC == Row_Tone_1_CLOCK_INT)  
	#include <Row_Tone_1_DacClk.h>
	#if defined(Row_Tone_1_DacClk_PHASE)
		#define Row_Tone_1_CLK_PHASE_0nS (1u)
	#endif /* defined(Row_Tone_1_DacClk_PHASE) */
#endif /* Row_Tone_1_CLOCK_SRC == Row_Tone_1_CLOCK_INT */

#if (CY_PSOC3)
	#define Row_Tone_1_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define Row_Tone_1_Wave1_DMA_BYTES_PER_BURST      (1u)
#define Row_Tone_1_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define Row_Tone_1_Wave2_DMA_BYTES_PER_BURST      (1u)
#define Row_Tone_1_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}Row_Tone_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void Row_Tone_1_Start(void)             ;
void Row_Tone_1_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void Row_Tone_1_Init(void)              ;
void Row_Tone_1_Enable(void)            ;
void Row_Tone_1_Stop(void)              ;

void Row_Tone_1_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void Row_Tone_1_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void Row_Tone_1_Sleep(void)             ;
void Row_Tone_1_Wakeup(void)            ;

#define Row_Tone_1_SetSpeed       Row_Tone_1_VDAC8_SetSpeed
#define Row_Tone_1_SetRange       Row_Tone_1_VDAC8_SetRange
#define Row_Tone_1_SetValue       Row_Tone_1_VDAC8_SetValue
#define Row_Tone_1_DacTrim        Row_Tone_1_VDAC8_DacTrim
#define Row_Tone_1_SaveConfig     Row_Tone_1_VDAC8_SaveConfig
#define Row_Tone_1_RestoreConfig  Row_Tone_1_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 Row_Tone_1_initVar;

extern const uint8 CYCODE Row_Tone_1_wave1[Row_Tone_1_WAVE1_LENGTH];
extern const uint8 CYCODE Row_Tone_1_wave2[Row_Tone_1_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(Row_Tone_1_DAC_MODE == Row_Tone_1_VOLT_MODE)
    #define Row_Tone_1_RANGE_1V       (0x00u)
    #define Row_Tone_1_RANGE_4V       (0x04u)
#else /* current mode */
    #define Row_Tone_1_RANGE_32uA     (0x00u)
    #define Row_Tone_1_RANGE_255uA    (0x04u)
    #define Row_Tone_1_RANGE_2mA      (0x08u)
    #define Row_Tone_1_RANGE_2048uA   Row_Tone_1_RANGE_2mA
#endif /* Row_Tone_1_DAC_MODE == Row_Tone_1_VOLT_MODE */

/* Power setting for SetSpeed API */
#define Row_Tone_1_LOWSPEED       (0x00u)
#define Row_Tone_1_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define Row_Tone_1_DAC8__D Row_Tone_1_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define Row_Tone_1_HS_MASK        (0x02u)
#define Row_Tone_1_HS_LOWPOWER    (0x00u)
#define Row_Tone_1_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define Row_Tone_1_MODE_MASK      (0x10u)
#define Row_Tone_1_MODE_V         (0x00u)
#define Row_Tone_1_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define Row_Tone_1_RANGE_MASK     (0x0Cu)
#define Row_Tone_1_RANGE_0        (0x00u)
#define Row_Tone_1_RANGE_1        (0x04u)
#define Row_Tone_1_RANGE_2        (0x08u)
#define Row_Tone_1_RANGE_3        (0x0Cu)
#define Row_Tone_1_IDIR_MASK      (0x04u)

#define Row_Tone_1_DAC_RANGE      ((uint8)(0u << 2u) & Row_Tone_1_RANGE_MASK)
#define Row_Tone_1_DAC_POL        ((uint8)(0u >> 1u) & Row_Tone_1_IDIR_MASK)


#endif /* CY_WaveDAC8_Row_Tone_1_H  */

/* [] END OF FILE */
