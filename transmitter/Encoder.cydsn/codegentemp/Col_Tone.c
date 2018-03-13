/*******************************************************************************
* File Name: Col_Tone.c
* Version 2.10
*
* Description:
*  This file provides the source code for the 8-bit Waveform DAC 
*  (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Col_Tone.h"

uint8  Col_Tone_initVar = 0u;

const uint8 CYCODE Col_Tone_wave1[Col_Tone_WAVE1_LENGTH] = { 128u,143u,159u,174u,188u,201u,213u,224u,233u,241u,246u,250u,252u,252u,250u,246u,241u,233u,224u,213u,201u,188u,174u,159u,143u,128u,112u,96u,81u,67u,54u,42u,31u,22u,14u,9u,5u,3u,3u,5u,9u,14u,22u,31u,42u,54u,67u,81u,96u,112u };
const uint8 CYCODE Col_Tone_wave2[Col_Tone_WAVE2_LENGTH] = { 128u,132u,138u,143u,148u,152u,158u,162u,168u,172u,178u,182u,188u,192u,198u,202u,208u,213u,218u,222u,228u,232u,238u,242u,248u,252u,248u,242u,238u,232u,228u,222u,218u,212u,208u,202u,198u,192u,188u,182u,178u,173u,168u,162u,158u,152u,148u,143u,138u,132u,128u,122u,118u,112u,107u,102u,97u,93u,88u,83u,78u,73u,68u,62u,57u,52u,47u,42u,37u,33u,28u,23u,18u,13u,8u,3u,8u,13u,18u,23u,28u,33u,37u,42u,47u,52u,57u,62u,68u,73u,78u,83u,88u,93u,97u,102u,107u,112u,118u,122u };

static uint8  Col_Tone_Wave1Chan;
static uint8  Col_Tone_Wave2Chan;
static uint8  Col_Tone_Wave1TD;
static uint8  Col_Tone_Wave2TD;


/*******************************************************************************
* Function Name: Col_Tone_Init
********************************************************************************
*
* Summary:
*  Initializes component with parameters set in the customizer.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void Col_Tone_Init(void) 
{
	Col_Tone_VDAC8_Init();
	Col_Tone_VDAC8_SetSpeed(Col_Tone_HIGHSPEED);
	Col_Tone_VDAC8_SetRange(Col_Tone_DAC_RANGE);

	#if(Col_Tone_DAC_MODE == Col_Tone_CURRENT_MODE)
		Col_Tone_IDAC8_SetPolarity(Col_Tone_DAC_POL);
	#endif /* Col_Tone_DAC_MODE == Col_Tone_CURRENT_MODE */

	#if(Col_Tone_OUT_MODE == Col_Tone_BUFFER_MODE)
	   Col_Tone_BuffAmp_Init();
	#endif /* Col_Tone_OUT_MODE == Col_Tone_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	Col_Tone_Wave1TD = CyDmaTdAllocate();
	Col_Tone_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	Col_Tone_Wave1Setup(Col_Tone_wave1, Col_Tone_WAVE1_LENGTH) ;
	Col_Tone_Wave2Setup(Col_Tone_wave2, Col_Tone_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(Col_Tone_DacClk_PHASE)
	   Col_Tone_DacClk_SetPhase(Col_Tone_CLK_PHASE_0nS);
	#endif /* defined(Col_Tone_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: Col_Tone_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void Col_Tone_Enable(void) 
{
	Col_Tone_VDAC8_Enable();

	#if(Col_Tone_OUT_MODE == Col_Tone_BUFFER_MODE)
	   Col_Tone_BuffAmp_Enable();
	#endif /* Col_Tone_OUT_MODE == Col_Tone_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(Col_Tone_Wave1Chan, 1u);
	(void)CyDmaChEnable(Col_Tone_Wave2Chan, 1u);
	
	/* set the initial value */
	Col_Tone_SetValue(0u);
	
	#if(Col_Tone_CLOCK_SRC == Col_Tone_CLOCK_INT)  	
	   Col_Tone_DacClk_Start();
	#endif /* Col_Tone_CLOCK_SRC == Col_Tone_CLOCK_INT */
}


/*******************************************************************************
* Function Name: Col_Tone_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void Col_Tone_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(Col_Tone_initVar == 0u)
	{
		Col_Tone_Init();
		Col_Tone_initVar = 1u;
	}
	
	Col_Tone_Enable();
}


/*******************************************************************************
* Function Name: Col_Tone_StartEx
********************************************************************************
*
* Summary:
*  The StartEx function sets pointers and sizes for both waveforms
*  and then starts the component.
*
* Parameters:  
*   uint8 * wavePtr1:     Pointer to the waveform 1 array.
*   uint16  sampleSize1:  The amount of samples in the waveform 1.
*   uint8 * wavePtr2:     Pointer to the waveform 2 array.
*   uint16  sampleSize2:  The amount of samples in the waveform 2.
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void Col_Tone_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	Col_Tone_Wave1Setup(wavePtr1, sampleSize1);
	Col_Tone_Wave2Setup(wavePtr2, sampleSize2);
	Col_Tone_Start();
}


/*******************************************************************************
* Function Name: Col_Tone_Stop
********************************************************************************
*
* Summary:
*  Stops the clock (if internal), disables the DMA channels
*  and powers down the DAC.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
*******************************************************************************/
void Col_Tone_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(Col_Tone_CLOCK_SRC == Col_Tone_CLOCK_INT)  	
	   Col_Tone_DacClk_Stop();
	#endif /* Col_Tone_CLOCK_SRC == Col_Tone_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(Col_Tone_Wave1Chan);
	(void)CyDmaChDisable(Col_Tone_Wave2Chan);

	/* Disable power to DAC */
	Col_Tone_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: Col_Tone_Wave1Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 1.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None 
*
*******************************************************************************/
void Col_Tone_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (Col_Tone_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		Col_Tone_Wave1Chan = Col_Tone_Wave1_DMA_DmaInitialize(
		Col_Tone_Wave1_DMA_BYTES_PER_BURST, Col_Tone_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		Col_Tone_Wave1Chan = Col_Tone_Wave1_DMA_DmaInitialize(
		Col_Tone_Wave1_DMA_BYTES_PER_BURST, Col_Tone_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(Col_Tone_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(Col_Tone_Wave1TD, sampleSize, Col_Tone_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)Col_Tone_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(Col_Tone_Wave1TD, LO16((uint32)wavePtr), LO16(Col_Tone_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(Col_Tone_Wave1Chan, Col_Tone_Wave1TD);
}


/*******************************************************************************
* Function Name: Col_Tone_Wave2Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 2.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None
*
*******************************************************************************/
void Col_Tone_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (Col_Tone_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		Col_Tone_Wave2Chan = Col_Tone_Wave2_DMA_DmaInitialize(
		Col_Tone_Wave2_DMA_BYTES_PER_BURST, Col_Tone_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		Col_Tone_Wave2Chan = Col_Tone_Wave2_DMA_DmaInitialize(
		Col_Tone_Wave2_DMA_BYTES_PER_BURST, Col_Tone_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(Col_Tone_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(Col_Tone_Wave2TD, sampleSize, Col_Tone_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)Col_Tone_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(Col_Tone_Wave2TD, LO16((uint32)wavePtr), LO16(Col_Tone_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(Col_Tone_Wave2Chan, Col_Tone_Wave2TD);
}


/* [] END OF FILE */
