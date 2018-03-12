/*******************************************************************************
* File Name: Row_Divider.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Row_Divider_H)
#define CY_PWM_Row_Divider_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Row_Divider_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Row_Divider_Resolution                     (8u)
#define Row_Divider_UsingFixedFunction             (0u)
#define Row_Divider_DeadBandMode                   (0u)
#define Row_Divider_KillModeMinTime                (0u)
#define Row_Divider_KillMode                       (0u)
#define Row_Divider_PWMMode                        (1u)
#define Row_Divider_PWMModeIsCenterAligned         (0u)
#define Row_Divider_DeadBandUsed                   (0u)
#define Row_Divider_DeadBand2_4                    (0u)

#if !defined(Row_Divider_PWMUDB_genblk8_stsreg__REMOVED)
    #define Row_Divider_UseStatus                  (1u)
#else
    #define Row_Divider_UseStatus                  (0u)
#endif /* !defined(Row_Divider_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Row_Divider_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Row_Divider_UseControl                 (1u)
#else
    #define Row_Divider_UseControl                 (0u)
#endif /* !defined(Row_Divider_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Row_Divider_UseOneCompareMode              (0u)
#define Row_Divider_MinimumKillTime                (1u)
#define Row_Divider_EnableMode                     (0u)

#define Row_Divider_CompareMode1SW                 (0u)
#define Row_Divider_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Row_Divider__B_PWM__DISABLED 0
#define Row_Divider__B_PWM__ASYNCHRONOUS 1
#define Row_Divider__B_PWM__SINGLECYCLE 2
#define Row_Divider__B_PWM__LATCHED 3
#define Row_Divider__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Row_Divider__B_PWM__DBMDISABLED 0
#define Row_Divider__B_PWM__DBM_2_4_CLOCKS 1
#define Row_Divider__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Row_Divider__B_PWM__ONE_OUTPUT 0
#define Row_Divider__B_PWM__TWO_OUTPUTS 1
#define Row_Divider__B_PWM__DUAL_EDGE 2
#define Row_Divider__B_PWM__CENTER_ALIGN 3
#define Row_Divider__B_PWM__DITHER 5
#define Row_Divider__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Row_Divider__B_PWM__LESS_THAN 1
#define Row_Divider__B_PWM__LESS_THAN_OR_EQUAL 2
#define Row_Divider__B_PWM__GREATER_THAN 3
#define Row_Divider__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Row_Divider__B_PWM__EQUAL 0
#define Row_Divider__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Row_Divider_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!Row_Divider_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!Row_Divider_PWMModeIsCenterAligned) */
        #if (Row_Divider_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Row_Divider_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_256_CLOCKS || \
            Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Row_Divider_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Row_Divider_KillModeMinTime) */

        /* Backup control register */
        #if(Row_Divider_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Row_Divider_UseControl) */

    #endif /* (!Row_Divider_UsingFixedFunction) */

}Row_Divider_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Row_Divider_Start(void) ;
void    Row_Divider_Stop(void) ;

#if (Row_Divider_UseStatus || Row_Divider_UsingFixedFunction)
    void  Row_Divider_SetInterruptMode(uint8 interruptMode) ;
    uint8 Row_Divider_ReadStatusRegister(void) ;
#endif /* (Row_Divider_UseStatus || Row_Divider_UsingFixedFunction) */

#define Row_Divider_GetInterruptSource() Row_Divider_ReadStatusRegister()

#if (Row_Divider_UseControl)
    uint8 Row_Divider_ReadControlRegister(void) ;
    void  Row_Divider_WriteControlRegister(uint8 control)
          ;
#endif /* (Row_Divider_UseControl) */

#if (Row_Divider_UseOneCompareMode)
   #if (Row_Divider_CompareMode1SW)
       void    Row_Divider_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Row_Divider_CompareMode1SW) */
#else
    #if (Row_Divider_CompareMode1SW)
        void    Row_Divider_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Row_Divider_CompareMode1SW) */
    #if (Row_Divider_CompareMode2SW)
        void    Row_Divider_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Row_Divider_CompareMode2SW) */
#endif /* (Row_Divider_UseOneCompareMode) */

#if (!Row_Divider_UsingFixedFunction)
    uint8   Row_Divider_ReadCounter(void) ;
    uint8 Row_Divider_ReadCapture(void) ;

    #if (Row_Divider_UseStatus)
            void Row_Divider_ClearFIFO(void) ;
    #endif /* (Row_Divider_UseStatus) */

    void    Row_Divider_WriteCounter(uint8 counter)
            ;
#endif /* (!Row_Divider_UsingFixedFunction) */

void    Row_Divider_WritePeriod(uint8 period)
        ;
uint8 Row_Divider_ReadPeriod(void) ;

#if (Row_Divider_UseOneCompareMode)
    void    Row_Divider_WriteCompare(uint8 compare)
            ;
    uint8 Row_Divider_ReadCompare(void) ;
#else
    void    Row_Divider_WriteCompare1(uint8 compare)
            ;
    uint8 Row_Divider_ReadCompare1(void) ;
    void    Row_Divider_WriteCompare2(uint8 compare)
            ;
    uint8 Row_Divider_ReadCompare2(void) ;
#endif /* (Row_Divider_UseOneCompareMode) */


#if (Row_Divider_DeadBandUsed)
    void    Row_Divider_WriteDeadTime(uint8 deadtime) ;
    uint8   Row_Divider_ReadDeadTime(void) ;
#endif /* (Row_Divider_DeadBandUsed) */

#if ( Row_Divider_KillModeMinTime)
    void Row_Divider_WriteKillTime(uint8 killtime) ;
    uint8 Row_Divider_ReadKillTime(void) ;
#endif /* ( Row_Divider_KillModeMinTime) */

void Row_Divider_Init(void) ;
void Row_Divider_Enable(void) ;
void Row_Divider_Sleep(void) ;
void Row_Divider_Wakeup(void) ;
void Row_Divider_SaveConfig(void) ;
void Row_Divider_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Row_Divider_INIT_PERIOD_VALUE          (255u)
#define Row_Divider_INIT_COMPARE_VALUE1        (127u)
#define Row_Divider_INIT_COMPARE_VALUE2        (63u)
#define Row_Divider_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Row_Divider_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Row_Divider_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Row_Divider_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Row_Divider_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Row_Divider_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Row_Divider_CTRL_CMPMODE2_SHIFT)
#define Row_Divider_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Row_Divider_CTRL_CMPMODE1_SHIFT)
#define Row_Divider_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Row_Divider_UsingFixedFunction)
   #define Row_Divider_PERIOD_LSB              (*(reg16 *) Row_Divider_PWMHW__PER0)
   #define Row_Divider_PERIOD_LSB_PTR          ( (reg16 *) Row_Divider_PWMHW__PER0)
   #define Row_Divider_COMPARE1_LSB            (*(reg16 *) Row_Divider_PWMHW__CNT_CMP0)
   #define Row_Divider_COMPARE1_LSB_PTR        ( (reg16 *) Row_Divider_PWMHW__CNT_CMP0)
   #define Row_Divider_COMPARE2_LSB            (0x00u)
   #define Row_Divider_COMPARE2_LSB_PTR        (0x00u)
   #define Row_Divider_COUNTER_LSB             (*(reg16 *) Row_Divider_PWMHW__CNT_CMP0)
   #define Row_Divider_COUNTER_LSB_PTR         ( (reg16 *) Row_Divider_PWMHW__CNT_CMP0)
   #define Row_Divider_CAPTURE_LSB             (*(reg16 *) Row_Divider_PWMHW__CAP0)
   #define Row_Divider_CAPTURE_LSB_PTR         ( (reg16 *) Row_Divider_PWMHW__CAP0)
   #define Row_Divider_RT1                     (*(reg8 *)  Row_Divider_PWMHW__RT1)
   #define Row_Divider_RT1_PTR                 ( (reg8 *)  Row_Divider_PWMHW__RT1)

#else
   #if (Row_Divider_Resolution == 8u) /* 8bit - PWM */

       #if(Row_Divider_PWMModeIsCenterAligned)
           #define Row_Divider_PERIOD_LSB      (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define Row_Divider_PERIOD_LSB_PTR  ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define Row_Divider_PERIOD_LSB      (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define Row_Divider_PERIOD_LSB_PTR  ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (Row_Divider_PWMModeIsCenterAligned) */

       #define Row_Divider_COMPARE1_LSB        (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define Row_Divider_COMPARE1_LSB_PTR    ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define Row_Divider_COMPARE2_LSB        (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define Row_Divider_COMPARE2_LSB_PTR    ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define Row_Divider_COUNTERCAP_LSB      (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define Row_Divider_COUNTERCAP_LSB_PTR  ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define Row_Divider_COUNTER_LSB         (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define Row_Divider_COUNTER_LSB_PTR     ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define Row_Divider_CAPTURE_LSB         (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define Row_Divider_CAPTURE_LSB_PTR     ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Row_Divider_PWMModeIsCenterAligned)
               #define Row_Divider_PERIOD_LSB      (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define Row_Divider_PERIOD_LSB_PTR  ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define Row_Divider_PERIOD_LSB      (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define Row_Divider_PERIOD_LSB_PTR  ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (Row_Divider_PWMModeIsCenterAligned) */

            #define Row_Divider_COMPARE1_LSB       (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define Row_Divider_COMPARE1_LSB_PTR   ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define Row_Divider_COMPARE2_LSB       (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define Row_Divider_COMPARE2_LSB_PTR   ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define Row_Divider_COUNTERCAP_LSB     (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define Row_Divider_COUNTERCAP_LSB_PTR ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define Row_Divider_COUNTER_LSB        (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define Row_Divider_COUNTER_LSB_PTR    ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define Row_Divider_CAPTURE_LSB        (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define Row_Divider_CAPTURE_LSB_PTR    ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(Row_Divider_PWMModeIsCenterAligned)
               #define Row_Divider_PERIOD_LSB      (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define Row_Divider_PERIOD_LSB_PTR  ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Row_Divider_PERIOD_LSB      (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define Row_Divider_PERIOD_LSB_PTR  ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Row_Divider_PWMModeIsCenterAligned) */

            #define Row_Divider_COMPARE1_LSB       (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define Row_Divider_COMPARE1_LSB_PTR   ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define Row_Divider_COMPARE2_LSB       (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define Row_Divider_COMPARE2_LSB_PTR   ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define Row_Divider_COUNTERCAP_LSB     (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define Row_Divider_COUNTERCAP_LSB_PTR ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define Row_Divider_COUNTER_LSB        (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define Row_Divider_COUNTER_LSB_PTR    ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define Row_Divider_CAPTURE_LSB        (*(reg16 *) Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define Row_Divider_CAPTURE_LSB_PTR    ((reg16 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Row_Divider_AUX_CONTROLDP1          (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define Row_Divider_AUX_CONTROLDP1_PTR      ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Row_Divider_Resolution == 8) */

   #define Row_Divider_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define Row_Divider_AUX_CONTROLDP0          (*(reg8 *)  Row_Divider_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define Row_Divider_AUX_CONTROLDP0_PTR      ((reg8 *)   Row_Divider_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Row_Divider_UsingFixedFunction) */

#if(Row_Divider_KillModeMinTime )
    #define Row_Divider_KILLMODEMINTIME        (*(reg8 *)  Row_Divider_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Row_Divider_KILLMODEMINTIME_PTR    ((reg8 *)   Row_Divider_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Row_Divider_KillModeMinTime ) */

#if(Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_256_CLOCKS)
    #define Row_Divider_DEADBAND_COUNT         (*(reg8 *)  Row_Divider_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Row_Divider_DEADBAND_COUNT_PTR     ((reg8 *)   Row_Divider_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Row_Divider_DEADBAND_LSB_PTR       ((reg8 *)   Row_Divider_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Row_Divider_DEADBAND_LSB           (*(reg8 *)  Row_Divider_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Row_Divider_UsingFixedFunction)
        #define Row_Divider_DEADBAND_COUNT         (*(reg8 *)  Row_Divider_PWMHW__CFG0)
        #define Row_Divider_DEADBAND_COUNT_PTR     ((reg8 *)   Row_Divider_PWMHW__CFG0)
        #define Row_Divider_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Row_Divider_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Row_Divider_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Row_Divider_DEADBAND_COUNT         (*(reg8 *)  Row_Divider_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Row_Divider_DEADBAND_COUNT_PTR     ((reg8 *)   Row_Divider_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Row_Divider_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Row_Divider_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Row_Divider_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Row_Divider_UsingFixedFunction) */
#endif /* (Row_Divider_DeadBandMode == Row_Divider__B_PWM__DBM_256_CLOCKS) */



#if (Row_Divider_UsingFixedFunction)
    #define Row_Divider_STATUS                 (*(reg8 *) Row_Divider_PWMHW__SR0)
    #define Row_Divider_STATUS_PTR             ((reg8 *) Row_Divider_PWMHW__SR0)
    #define Row_Divider_STATUS_MASK            (*(reg8 *) Row_Divider_PWMHW__SR0)
    #define Row_Divider_STATUS_MASK_PTR        ((reg8 *) Row_Divider_PWMHW__SR0)
    #define Row_Divider_CONTROL                (*(reg8 *) Row_Divider_PWMHW__CFG0)
    #define Row_Divider_CONTROL_PTR            ((reg8 *) Row_Divider_PWMHW__CFG0)
    #define Row_Divider_CONTROL2               (*(reg8 *) Row_Divider_PWMHW__CFG1)
    #define Row_Divider_CONTROL3               (*(reg8 *) Row_Divider_PWMHW__CFG2)
    #define Row_Divider_GLOBAL_ENABLE          (*(reg8 *) Row_Divider_PWMHW__PM_ACT_CFG)
    #define Row_Divider_GLOBAL_ENABLE_PTR      ( (reg8 *) Row_Divider_PWMHW__PM_ACT_CFG)
    #define Row_Divider_GLOBAL_STBY_ENABLE     (*(reg8 *) Row_Divider_PWMHW__PM_STBY_CFG)
    #define Row_Divider_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Row_Divider_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Row_Divider_BLOCK_EN_MASK          (Row_Divider_PWMHW__PM_ACT_MSK)
    #define Row_Divider_BLOCK_STBY_EN_MASK     (Row_Divider_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Row_Divider_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Row_Divider_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Row_Divider_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Row_Divider_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Row_Divider_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Row_Divider_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Row_Divider_CTRL_ENABLE            (uint8)((uint8)0x01u << Row_Divider_CTRL_ENABLE_SHIFT)
    #define Row_Divider_CTRL_RESET             (uint8)((uint8)0x01u << Row_Divider_CTRL_RESET_SHIFT)
    #define Row_Divider_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Row_Divider_CTRL_CMPMODE2_SHIFT)
    #define Row_Divider_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Row_Divider_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Row_Divider_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Row_Divider_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Row_Divider_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Row_Divider_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Row_Divider_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Row_Divider_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Row_Divider_STATUS_TC_INT_EN_MASK_SHIFT            (Row_Divider_STATUS_TC_SHIFT - 4u)
    #define Row_Divider_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Row_Divider_STATUS_CMP1_INT_EN_MASK_SHIFT          (Row_Divider_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Row_Divider_STATUS_TC              (uint8)((uint8)0x01u << Row_Divider_STATUS_TC_SHIFT)
    #define Row_Divider_STATUS_CMP1            (uint8)((uint8)0x01u << Row_Divider_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Row_Divider_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Row_Divider_STATUS_TC >> 4u)
    #define Row_Divider_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Row_Divider_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Row_Divider_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Row_Divider_RT1_MASK              (uint8)((uint8)0x03u << Row_Divider_RT1_SHIFT)
    #define Row_Divider_SYNC                  (uint8)((uint8)0x03u << Row_Divider_RT1_SHIFT)
    #define Row_Divider_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Row_Divider_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Row_Divider_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Row_Divider_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Row_Divider_SYNCDSI_SHIFT)


#else
    #define Row_Divider_STATUS                (*(reg8 *)   Row_Divider_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Row_Divider_STATUS_PTR            ((reg8 *)    Row_Divider_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Row_Divider_STATUS_MASK           (*(reg8 *)   Row_Divider_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Row_Divider_STATUS_MASK_PTR       ((reg8 *)    Row_Divider_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Row_Divider_STATUS_AUX_CTRL       (*(reg8 *)   Row_Divider_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Row_Divider_CONTROL               (*(reg8 *)   Row_Divider_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Row_Divider_CONTROL_PTR           ((reg8 *)    Row_Divider_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Row_Divider_CTRL_ENABLE_SHIFT      (0x07u)
    #define Row_Divider_CTRL_RESET_SHIFT       (0x06u)
    #define Row_Divider_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Row_Divider_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Row_Divider_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Row_Divider_CTRL_ENABLE            (uint8)((uint8)0x01u << Row_Divider_CTRL_ENABLE_SHIFT)
    #define Row_Divider_CTRL_RESET             (uint8)((uint8)0x01u << Row_Divider_CTRL_RESET_SHIFT)
    #define Row_Divider_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Row_Divider_CTRL_CMPMODE2_SHIFT)
    #define Row_Divider_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Row_Divider_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Row_Divider_STATUS_KILL_SHIFT          (0x05u)
    #define Row_Divider_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Row_Divider_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Row_Divider_STATUS_TC_SHIFT            (0x02u)
    #define Row_Divider_STATUS_CMP2_SHIFT          (0x01u)
    #define Row_Divider_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Row_Divider_STATUS_KILL_INT_EN_MASK_SHIFT          (Row_Divider_STATUS_KILL_SHIFT)
    #define Row_Divider_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Row_Divider_STATUS_FIFONEMPTY_SHIFT)
    #define Row_Divider_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Row_Divider_STATUS_FIFOFULL_SHIFT)
    #define Row_Divider_STATUS_TC_INT_EN_MASK_SHIFT            (Row_Divider_STATUS_TC_SHIFT)
    #define Row_Divider_STATUS_CMP2_INT_EN_MASK_SHIFT          (Row_Divider_STATUS_CMP2_SHIFT)
    #define Row_Divider_STATUS_CMP1_INT_EN_MASK_SHIFT          (Row_Divider_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Row_Divider_STATUS_KILL            (uint8)((uint8)0x00u << Row_Divider_STATUS_KILL_SHIFT )
    #define Row_Divider_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Row_Divider_STATUS_FIFOFULL_SHIFT)
    #define Row_Divider_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Row_Divider_STATUS_FIFONEMPTY_SHIFT)
    #define Row_Divider_STATUS_TC              (uint8)((uint8)0x01u << Row_Divider_STATUS_TC_SHIFT)
    #define Row_Divider_STATUS_CMP2            (uint8)((uint8)0x01u << Row_Divider_STATUS_CMP2_SHIFT)
    #define Row_Divider_STATUS_CMP1            (uint8)((uint8)0x01u << Row_Divider_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Row_Divider_STATUS_KILL_INT_EN_MASK            (Row_Divider_STATUS_KILL)
    #define Row_Divider_STATUS_FIFOFULL_INT_EN_MASK        (Row_Divider_STATUS_FIFOFULL)
    #define Row_Divider_STATUS_FIFONEMPTY_INT_EN_MASK      (Row_Divider_STATUS_FIFONEMPTY)
    #define Row_Divider_STATUS_TC_INT_EN_MASK              (Row_Divider_STATUS_TC)
    #define Row_Divider_STATUS_CMP2_INT_EN_MASK            (Row_Divider_STATUS_CMP2)
    #define Row_Divider_STATUS_CMP1_INT_EN_MASK            (Row_Divider_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Row_Divider_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Row_Divider_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Row_Divider_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Row_Divider_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Row_Divider_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Row_Divider_UsingFixedFunction */

#endif  /* CY_PWM_Row_Divider_H */


/* [] END OF FILE */
