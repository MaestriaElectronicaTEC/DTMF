/*******************************************************************************
* File Name: Col_Tone.h  
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

#if !defined(CY_WaveDAC8_Col_Tone_H) 
#define CY_WaveDAC8_Col_Tone_H

#include "cytypes.h"
#include "cyfitter.h"
#include <Col_Tone_Wave1_DMA_dma.h>
#include <Col_Tone_Wave2_DMA_dma.h>
#include <Col_Tone_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define Col_Tone_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define Col_Tone_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define Col_Tone_SINE_WAVE      (0u)
#define Col_Tone_SQUARE_WAVE    (1u)
#define Col_Tone_TRIANGLE_WAVE  (2u)
#define Col_Tone_SAWTOOTH_WAVE  (3u)
#define Col_Tone_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define Col_Tone_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define Col_Tone_WAVE1_LENGTH   (50u)   /* Length for wave1 */
#define Col_Tone_WAVE2_LENGTH   (50u)   /* Length for wave2 */
	
#define Col_Tone_DEFAULT_RANGE    (1u) /* Default DAC range */
#define Col_Tone_DAC_RANGE_1V     (0u)
#define Col_Tone_DAC_RANGE_1V_BUF (16u)
#define Col_Tone_DAC_RANGE_4V     (1u)
#define Col_Tone_DAC_RANGE_4V_BUF (17u)
#define Col_Tone_VOLT_MODE        (0u)
#define Col_Tone_CURRENT_MODE     (1u)
#define Col_Tone_DAC_MODE         (((Col_Tone_DEFAULT_RANGE == Col_Tone_DAC_RANGE_1V) || \
									  (Col_Tone_DEFAULT_RANGE == Col_Tone_DAC_RANGE_4V) || \
							  		  (Col_Tone_DEFAULT_RANGE == Col_Tone_DAC_RANGE_1V_BUF) || \
									  (Col_Tone_DEFAULT_RANGE == Col_Tone_DAC_RANGE_4V_BUF)) ? \
									   Col_Tone_VOLT_MODE : Col_Tone_CURRENT_MODE)

#define Col_Tone_DACMODE Col_Tone_DAC_MODE /* legacy definition for backward compatibility */

#define Col_Tone_DIRECT_MODE (0u)
#define Col_Tone_BUFFER_MODE (1u)
#define Col_Tone_OUT_MODE    (((Col_Tone_DEFAULT_RANGE == Col_Tone_DAC_RANGE_1V_BUF) || \
								 (Col_Tone_DEFAULT_RANGE == Col_Tone_DAC_RANGE_4V_BUF)) ? \
								  Col_Tone_BUFFER_MODE : Col_Tone_DIRECT_MODE)

#if(Col_Tone_OUT_MODE == Col_Tone_BUFFER_MODE)
    #include <Col_Tone_BuffAmp.h>
#endif /* Col_Tone_OUT_MODE == Col_Tone_BUFFER_MODE */

#define Col_Tone_CLOCK_INT      (1u)
#define Col_Tone_CLOCK_EXT      (0u)
#define Col_Tone_CLOCK_SRC      (0u)

#if(Col_Tone_CLOCK_SRC == Col_Tone_CLOCK_INT)  
	#include <Col_Tone_DacClk.h>
	#if defined(Col_Tone_DacClk_PHASE)
		#define Col_Tone_CLK_PHASE_0nS (1u)
	#endif /* defined(Col_Tone_DacClk_PHASE) */
#endif /* Col_Tone_CLOCK_SRC == Col_Tone_CLOCK_INT */

#if (CY_PSOC3)
	#define Col_Tone_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define Col_Tone_Wave1_DMA_BYTES_PER_BURST      (1u)
#define Col_Tone_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define Col_Tone_Wave2_DMA_BYTES_PER_BURST      (1u)
#define Col_Tone_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}Col_Tone_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void Col_Tone_Start(void)             ;
void Col_Tone_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void Col_Tone_Init(void)              ;
void Col_Tone_Enable(void)            ;
void Col_Tone_Stop(void)              ;

void Col_Tone_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void Col_Tone_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void Col_Tone_Sleep(void)             ;
void Col_Tone_Wakeup(void)            ;

#define Col_Tone_SetSpeed       Col_Tone_VDAC8_SetSpeed
#define Col_Tone_SetRange       Col_Tone_VDAC8_SetRange
#define Col_Tone_SetValue       Col_Tone_VDAC8_SetValue
#define Col_Tone_DacTrim        Col_Tone_VDAC8_DacTrim
#define Col_Tone_SaveConfig     Col_Tone_VDAC8_SaveConfig
#define Col_Tone_RestoreConfig  Col_Tone_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 Col_Tone_initVar;

extern const uint8 CYCODE Col_Tone_wave1[Col_Tone_WAVE1_LENGTH];
extern const uint8 CYCODE Col_Tone_wave2[Col_Tone_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(Col_Tone_DAC_MODE == Col_Tone_VOLT_MODE)
    #define Col_Tone_RANGE_1V       (0x00u)
    #define Col_Tone_RANGE_4V       (0x04u)
#else /* current mode */
    #define Col_Tone_RANGE_32uA     (0x00u)
    #define Col_Tone_RANGE_255uA    (0x04u)
    #define Col_Tone_RANGE_2mA      (0x08u)
    #define Col_Tone_RANGE_2048uA   Col_Tone_RANGE_2mA
#endif /* Col_Tone_DAC_MODE == Col_Tone_VOLT_MODE */

/* Power setting for SetSpeed API */
#define Col_Tone_LOWSPEED       (0x00u)
#define Col_Tone_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define Col_Tone_DAC8__D Col_Tone_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define Col_Tone_HS_MASK        (0x02u)
#define Col_Tone_HS_LOWPOWER    (0x00u)
#define Col_Tone_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define Col_Tone_MODE_MASK      (0x10u)
#define Col_Tone_MODE_V         (0x00u)
#define Col_Tone_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define Col_Tone_RANGE_MASK     (0x0Cu)
#define Col_Tone_RANGE_0        (0x00u)
#define Col_Tone_RANGE_1        (0x04u)
#define Col_Tone_RANGE_2        (0x08u)
#define Col_Tone_RANGE_3        (0x0Cu)
#define Col_Tone_IDIR_MASK      (0x04u)

#define Col_Tone_DAC_RANGE      ((uint8)(1u << 2u) & Col_Tone_RANGE_MASK)
#define Col_Tone_DAC_POL        ((uint8)(1u >> 1u) & Col_Tone_IDIR_MASK)


#endif /* CY_WaveDAC8_Col_Tone_H  */

/* [] END OF FILE */
