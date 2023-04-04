/*
 * RCC.h
 *
 *  Created on: Jan 30, 2023
 *      Author: samir
 */

#ifndef RCC_H_
#define RCC_H_

#include "Bit_math.h"
#include "Std_types.h"

/*******************************************************************************************************/
/******************************************* Macros ****************************************************/
/******************************************************************************************************/

/*******************************************************************/
/*                                                                  */
/*                       System clock  Maybe be:                    */
/*                       1-HSI                                      */
/*                       2-HSE                                      */
/*                       3-PPL                                      */
/*******************************************************************/
#define SYSCLK_HSI  0x00000300
#define SYSCLK_HSE  0x00000301
#define SYSCLK_PLL  0x00000302
 
/*******************************************************************/
/*                                                                 */
/*                       ClockType Maybe :                         */
/*                       1-HSI                                     */
/*                       2-HSE                                     */
/*                       3-PLL                                     */
/*                       4-HSE_BYPASS                              */
/*                                                                 */
/*******************************************************************/


#define CLOCK_HSI                           (u32)(0x5)            
#define CLOCK_HSE                           (u32)(0x00010004)
#define CLOCK_PLL                           (u32)(0x01000004) 
#define CLOCK_HSE_BY_PASS                   (u32)(0x00040004)

/*******************************************************************/
/*                                                                 */
/*                       PeripheralBus  Maybe :                    */
/*                       1-AHB1                                    */
/*                       2-AHB2                                    */
/*                       3-APB1                                    */
/*                       3-APB2                                    */
/*******************************************************************/
#define    BUS_AHB1       0
#define    BUS_AHB2       1
#define    BUS_APB1       2
#define    BUS_APB2       3


/*******************************************************************/
/*                                                                 */
/*                      APB high-speed prescaler(APB1)             */
/*                       1- clock not divided                      */
/*                       2- AHB clock divided by 2                 */
/*                       3- AHB clock divided by 4                 */
/*                       3- AHB clock divided by 8                 */
/*                       3- AHB clock divided by 16                */
/*******************************************************************/
#define PRESCALER_APB1_CLOCK_NOT_DIVIDED    0x00000300 
#define PRESCALER_APB1_CLOCK_DIVIDED_BY_2   0x00001300
#define PRESCALER_APB1_CLOCK_DIVIDED_BY_4   0x00001700
#define PRESCALER_APB1_CLOCK_DIVIDED_BY_8   0x00001B00
#define PRESCALER_APB1_CLOCK_DIVIDED_BY_16  0x00001F00

/*******************************************************************/
/*                                                                 */
/*                      APB Low speed prescaler (APB2)             */
/*                       1- clock not divided                      */
/*                       2- AHB clock divided by 2                 */
/*                       3- AHB clock divided by 4                 */
/*                       3- AHB clock divided by 8                 */
/*                       3- AHB clock divided by 16                */
/*******************************************************************/
#define PRESCALER_APB2_CLOCK_NOT_DIVIDED    0x00000300 
#define PRESCALER_APB2_CLOCK_DIVIDED_BY_2   0x00008300
#define PRESCALER_APB2_CLOCK_DIVIDED_BY_4   0x0000A300
#define PRESCALER_APB2_CLOCK_DIVIDED_BY_8   0x0000C300
#define PRESCALER_APB2_CLOCK_DIVIDED_BY_16  0x0000E300


/**********************************************************************/
/*                                                                    */
/*                      high-speed prescaler(AHB)                     */
/*                       1- system Clock not divided                  */
/*                       2- system clock divided by 2                 */
/*                       3- system clock divided by 4                 */
/*                       4- system clock divided by 8                 */
/*                       5- system clock divided by 16                */
/*                       6- system clock divided by 64                */
/*                       7- system clock divided by 128               */
/*                       8- system clock divided by 256               */
/*                       9- system clock divided by 512               */
/**********************************************************************/

#define PRESCALER_AHB_CLOCK_NOT_DIVIDED      0x00000300
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_2     0x00000380
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_4     0x00000390
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_8     0x000003A0
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_16    0x000003B0
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_64    0x000003C0
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_128   0x000003D0
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_256   0x000003E0
#define PRESCALER_AHB_CLOCK_DIVIDED_BY_512   0x000003F0




/**********************************************************************/
/*                                                                    */
/*                 Clock Security System May be                       */
/*                 1-Enable:                                          */
/* 				   To Set HSI By H.W When There are Failure In HSE    */
/* 				   To Set HSI By H.W When Leaving Stop Or Standby     */
/* 				   2-Disable                                          */
/* 				   The Previouse To Feature Doesnot Happen            */
/*                                                                    */
/**********************************************************************/

#define SECURITY_DISABLE_CLOCK_SYSTEM             (1<<19)
#define SECURITY_ENABLE_CLOCK_SYSTEM              (1<<19)

/********************************************************************************************/
/*                                                                                           */
/*                   ClockFactor For PLLN  Should be 192 ≤ PLLN ≤ 432                        */
/*                    any other Factor would be wrong configuration                          */
/*                                PLL_CLOCKk_MULTIPLE_BY_192                                 */
/*                                        .....                                              */
/*                                        .....                                              */
/*                                 PLL_CLOCKk_MULTIPLE_BY_433                                */
/*                                                                                           */
/********************************************************************************************/

#define PLLN_CLOCK_MULTIP_BY_192          0xF0006000
#define PLLN_CLOCK_MULTIP_BY_193          0xF0006040
#define PLLN_CLOCK_MULTIP_BY_200          0xF0006400
#define PLLN_CLOCK_MULTIP_BY_432          0xF0006C00
/********************************************************************************************/
/*                                                                                           */
/*                   ClockFactor For PLLM  Should be 2 ≤ PLLM ≤ 63                           */
/*                    any other Factor would be wrong configuration                          */
/*                                PLL_CLOCKk_DIVIED_BY_2                                     */
/*                                        .....                                              */
/*                                        .....                                              */
/*                                 PLL_CLOCKk_DIVIED_BY_63                                   */
/*                                                                                           */
/********************************************************************************************/
#define PLLM_DIVIED_CLOCK_BY_2           0xF0000002
#define PLLM_DIVIED_CLOCK_BY_3           0xF0000003
#define PLLM_DIVIED_CLOCK_BY_4           0xF0000004
#define PLLM_DIVIED_CLOCK_BY_5           0xF0000005
#define PLLM_DIVIED_CLOCK_BY_6           0xF0000006
#define PLLM_DIVIED_CLOCK_BY_7           0xF0000007
#define PLLM_DIVIED_CLOCK_BY_8           0xF0000008
#define PLLM_DIVIED_CLOCK_BY_30          0xF0000030
#define PLLM_DIVIED_CLOCK_BY_63          0xF0000063


/********************************************************************************************/
/*                                                                                           */
/*                   ClockFactor For PLLQ  Should be 2 ≤ PLLQ ≤ 15                           */
/*                    any other Factor would be wrong configuration                          */
/*                                 PLLQ_CLOCK_DIVIED_BY_2                                    */
/*                                        .....                                              */
/*                                        .....                                              */
/*                                 PLLQ_CLOCk_DIVIED_BY_15                                   */
/*                                                                                           */
/********************************************************************************************/
#define PLLQ_CLOCK_DIVIED_BY_2            0xF2000000   
#define PLLQ_CLOCK_DIVIED_BY_3            0xF3000000 
#define PLLQ_CLOCK_DIVIED_BY_4            0xF4000063 
#define PLLQ_CLOCK_DIVIED_BY_5            0xF5000000                         
#define PLLQ_CLOCK_DIVIED_BY_6            0xF6000000                            
#define PLLQ_CLOCK_DIVIED_BY_7            0xF7000000                    
#define PLLQ_CLOCK_DIVIED_BY_8            0xF8000000            
#define PLLQ_CLOCK_DIVIED_BY_9            0xF9000000            
#define PLLQ_CLOCK_DIVIED_BY_10           0xFA000000             
#define PLLQ_CLOCK_DIVIED_BY_11           0xFB000000             
#define PLLQ_CLOCK_DIVIED_BY_12           0xFC000000             
#define PLLQ_CLOCK_DIVIED_BY_13           0xFD000000             
#define PLLQ_CLOCK_DIVIED_BY_14           0xFE000000             
#define PLLQ_CLOCK_DIVIED_BY_15           0xFF000000             



/********************************************************************************************/
/*                                                                                           */
/*                   division factor for main system clock 2 ≤ PLLP ≤ 8                      */
/*                    any other Factor would be wrong configuration                          */
/*                                PLLP_CLOCK_DIVIED_BY_2                                     */
/*                                PLLP_CLOCK_DIVIED_BY_4                                     */
/*                                PLLP_CLOCK_DIVIED_BY_6                                     */
/*                                PLLP_CLOCK_DIVIED_BY_8                                     */
/********************************************************************************************/
#define PLLP_DIVIED_CLOCK_BY_2            0xF0000000        
#define PLLP_DIVIED_CLOCK_BY_4            0xF0010000
#define PLLP_DIVIED_CLOCK_BY_6            0xF0020000
#define PLLP_DIVIED_CLOCK_BY_8            0xF0030000

#define PLL_HSE_CLOCK_SOURCE                    (1<<22)
#define PLL_HSI_CLOCK_SOURCE                   ~(1<<22)
/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/


/******************************************************************************************************/
/******************************************* Types ****************************************************/
/******************************************************************************************************/


/********************************************* ErrorStatus ********************************************/
typedef enum 
{
    RCC_OK,
    RCC_NOTOK,
    RCC_clockRDY,
    RCC_clockNotRDY,
    RCC_InvalidClockType,
	RCC_InvalidPreScaler,
    RCC_InvalidPLLsource,
    RCC_TimeOut,
    RCC_InvalidPeripheral,
    RCC_Wrong_Clock_Security_System_Configuration_Choice,
    RCC_Wrong_PLL_Configuration_Choice,
    RCC_parameter_error,
}RCC_enuErrorStatus_t;
/*                                                                                */
/**********************************END*********************************************/

/****************************************** Bus's Peripherals  ********************************************/

/*********************************** AHB1 Peripheral Enable/Disable/Reset *********************************/
typedef enum
{
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH=7,
    Peripheral_CRC=12,
    Peripheral_DMA1=21,
    Peripheral_DAM2
}RCC_AHB1_Peripheral_t;

/*********************************** AHB2 Peripheral Enable/Disable/Reset *********************************/

typedef enum
{
    Peripheral_OTGFS =7
}RCC_AHB2_Peripheral_t;

/*********************************** APB1 Peripheral Enable/Disable/Reset *********************************/

typedef enum
{
    Peripheral_TIM2,
    Peripheral_TIM3,
    Peripheral_TIM4,
    Peripheral_TIM5,
    Peripheral_WWDG=11,
    Peripheral_SPI2=14,
    Peripheral_SPI3,
    Peripheral_USART2=17,
    Peripheral_I2C1=21,
    Peripheral_I2C2,
    Peripheral_I2C3,
    Peripheral_PWR=28
}RCC_APB1_Peripheral_t;

/*********************************** AHB2 Peripheral Enable/Disable/Reset *********************************/

typedef enum
{
    Peripheral_TIM1,
    Peripheral_USART1=4,
    Peripheral_USART6,
    Peripheral_ADC1=8,
    Peripheral_SDIO=11,
    Peripheral_SPI1,
    Peripheral_SPI4,
    Peripheral_SYSCFG,
    Peripheral_TIM9=16,
    Peripheral_TIM10,
    Peripheral_TIM11
}RCC_APB2_Peripheral_t;
/*                                                                                */
/**********************************END*********************************************/

/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/



/************************************************ APIs ***************************************************/
/*                                                                                                       */



/**********************************************************************************/
/*                            set system clock                                   */

/***************************************************************************************/
/*                       RCC_setHSISystemClock  function                               */
/***************************************************************************************/
/*  Description: used to set HSI as  system clock                                      */
/* 	input:       void                                                                  */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setHSISystemClock(void);

/***************************************************************************************/
/*                       RCC_setHSESystemClock  function                               */
/***************************************************************************************/
/*  Description: used to set HSE as  system clock                                      */
/* 	input:       void                                                                  */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setHSESystemClock(void);

/***************************************************************************************/
/*                       RCC_setPLLSystemClock  function                               */
/***************************************************************************************/
/*  Description: used to set PLL as  system clock                                      */
/*               make sure before set PLL as system clock to do the following :        */
/*              - set the PLL configuration using RCC_PLLConfigurationClock() function */
/* 	input:       void                                                                  */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setPLLSystemClock(void);


/**********************************************************************************/
/*                            change system clock                                */

/***************************************************************************************/
/*                       RCC_setPLLSystemClock  function                               */
/***************************************************************************************/
/*  Description: used to cahnge the system clock                                       */
/*               make sure before change to  PLL as system clock to do the following : */
/*              - set the PLL configuration using RCC_PLLConfigurationClock() function */
/* 	input:       clock(CLOCK_HSE,CLOCK_HSE,CLOCK_PLL)                                  */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_changeSystemClock(u32 clock);

/*                                                                                */
/**********************************END*********************************************/



/**********************************************************************************/
/*                            set clocks on                                      */

/***************************************************************************************/
/*                       RCC_setHSEOn  function                                        */
/***************************************************************************************/
/*  Description: used to on or off clock  of HSE.                                      */
/* 	input:      (void)                                                                 */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/*                                                                                     */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setHSEOn(void);

/***************************************************************************************/
/*                       RCC_setHSIOn  function                                        */
/***************************************************************************************/
/*  Description: used to on or off clock  of HSI.                                      */
/* 	input:      (void)                                                                 */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/*                                                                                     */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setHSIOn(void);

/***************************************************************************************/
/*                       RCC_setPLLOn  function                                        */
/***************************************************************************************/
/*  Description: used to on or off clock  of PLL.                                      */
/* 	input:      (void)                                                                 */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/*                                                                                     */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setPLLOn(void);

/***************************************************************************************/
/*                       RCC_setHSEBypassOn  function                                  */
/***************************************************************************************/
/*  Description: used to on or off clock  of HSEBypass.                                */
/* 	input:      (void)                                                                 */
/* 	return:      RCC_enuErrorStatus_t( RCC_OK ,RCC_NOTOK )                             */
/*                                                                                     */
/***************************************************************************************/
RCC_enuErrorStatus_t RCC_setHSEbypassOn(void);

/*                                                                                */
/**********************************END*********************************************/





/**********************************************************************************/
/*                         RCC_getClockStatus function                           */

/**********************************************************************************/
/*                    RCC_getHSERDY function                                      */
/**********************************************************************************/
/*  Description:  return RDY or not clock of HSE.                                 */
/*  input:        void                                                            */
/*  return:       RCC_clockRDY,RCC_clockNotRDY                                    */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_getHSERDY(void);

/**********************************************************************************/
/*                    RCC_getHSIRDY function                                      */
/**********************************************************************************/
/*  Description:  return RDY or not clock of HSI.                                 */
/*  input:        void                                                            */
/*  return:       RCC_clockRDY,RCC_clockNotRDY                                    */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_getHSIRDY(void);

/**********************************************************************************/
/*                    RCC_getPLLRDY function                                       */
/**********************************************************************************/
/*  Description:  return RDY or not clock of PLL.                                 */
/*  input:         void                                                           */
/*  return:         RCC_clockRDY,RCC_clockNotRDY                                  */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_getPLLRDY(void);

/*                                                                                 */
/**********************************END*********************************************/


/**********************************************************************************/
/*                         RCC_getSystemClocks function                           */
/**********************************************************************************/
/*  Description:  return the runing system clock.                                 */
/*  input:         void                                                           */
/*  return:        CLOCK_HSE CLOCK_HSI CLOCK_PLL                                  */
/**********************************************************************************/
u32 RCC_getSystemClocks(void);


/***********************************************************************************/
/*                         RCC_PLLConfigurationClock function                      */
/***********************************************************************************/
/*  Description:  Set the PLL Factors and PLL source.                              */
/*  input:          PLLP_DIVIED_CLOCK_BY_X   (  2<= X <=8    ),                    */     
/*                  PLLM_DIVIED__CLOCK_BY_X  (  2<= X <=63   ),                    */
/*                  PLLN_CLOCK_MULTIP_BY_X   ( 192<= X <=433 ),                    */     
/*                  PLLQ_CLOCK_DIVIED_BY_2   ( 2<= X <=15    ),                    */
/*                  CLOCK_Source             ( HSI , HSE     )                     */
/*  return:         RCC_OK,RCC_InvalidClockType,RCC_parameter_error                */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_PLLConfigurationClock(u32 clock, u32 PLLQ, u32 PLLM, u32 PLLN,u32 PLLP);




/**********************************************************************************/
/*                         RCC_clockSystemSecurity function                       */
/**********************************************************************************/
/*  Description:   set  clock System Security on/off.                             */
/*  input:         clockSecurityState(SECURITY_DISABLE_CLOCK_SYSTEM,              */
/*                                      SECURITY_ENABLE_CLOCK_SYSTEM)             */
/*  return:        RCC_OK, RCC_NOTOK                                              */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_clockSystemSecurity(u32 clockSecurityState); 



/**********************************************************************************/
/*                  Enable  Peripheral's Clock                                    */

/**********************************************************************************/
/*                         RCC_enableAHB1Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to enable the clock to the Peripheral on AHB1 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_enableAHB1Peripheral( RCC_AHB1_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_enableAHB2Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to enable the clock to the Peripheral on AHB2 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_enableAHB2Peripheral( RCC_AHB2_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_enableAPB1Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to enable the clock to the Peripheral on APB1 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_enableAPB1Peripheral( RCC_APB1_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_enableAPB2Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to enable the clock to the Peripheral on APB2 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_enableAPB2Peripheral( RCC_APB2_Peripheral_t Peripheral);

/*                                                                                 */
/**********************************END*********************************************/





/**********************************************************************************/
/*                  disable  Peripheral's Clock                                   */

/**********************************************************************************/
/*                         RCC_disableAHB1Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to disable the clock to the Peripheral on AHB1 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_disableAHB1Peripheral( RCC_AHB1_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_disableAHB2Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to disable the clock to the Peripheral on AHB2 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_disableAHB2Peripheral( RCC_AHB2_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_disableAPB1Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to disable the clock to the Peripheral on APB1 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_disableAPB1Peripheral( RCC_APB1_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_disableAPB2Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to disable the clock to the Peripheral on APB2 bus          */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_disableAPB2Peripheral( RCC_APB2_Peripheral_t Peripheral);

/*                                                                                 */
/**********************************END*********************************************/



/**********************************************************************************/
/*                         Reset  Peripherals ABIs                                */

/**********************************************************************************/
/*                         RCC_resetAHB1Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to reset the Peripheral on AHB1 bus                        */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_resetAHB1Peripheral( RCC_AHB1_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_resetAHB2Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to reset the Peripheral on AHB2 bus                        */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_resetAHB2Peripheral( RCC_AHB2_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_resetAPB1Peripheral function                      */
/**********************************************************************************/
/*  Description:  used to reset the Peripheral on APB1 bus                        */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_resetAPB1Peripheral( RCC_APB1_Peripheral_t Peripheral);

/**********************************************************************************/
/*                         RCC_resetAPB2Peripheral function                       */
/**********************************************************************************/
/*  Description:  used to reset the Peripheral on APB2 bus                        */
/*  input:        RCC_periphreals (RCC_AHB1_Peripheral_t)                         */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPeripheral )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_resetAPB2Peripheral( RCC_APB2_Peripheral_t Peripheral);

/*                                                                                 */
/**********************************END*********************************************/

/**********************************************************************************/
/*                         set  BUSs prescalers                                   */

/**********************************************************************************/
/*                         RCC_setAPB2Prescaler function                          */
/**********************************************************************************/
/*  Description:  used to set  the pre scaler for APB2(high speed)                */
/*  input:        u8  (PRESCALER_CLOCK_NOT_DIVIDED,                               */
/*                    PRESCALER_AHB_CLOCK_DIVIDED_BY_X (2<= X <= 16) )            */  
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPreScaler )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_setAPB2Prescaler(u32 prescaler );

/**********************************************************************************/
/*                         RCC_setAPB1Prescaler function                          */
/**********************************************************************************/
/*  Description:  used to set  the pre scaler for APB1(Low speed)                 */
/*  input:        u8  (PRESCALER_CLOCK_NOT_DIVIDED,                               */
/*                    PRESCALER_AHB_CLOCK_DIVIDED_BY_X (2<= X <= 16) )            */                                    
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPreScaler )           */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_setAPB1Prescaler(u32 prescaler );


/**********************************************************************************/
/*                         RCC_setAHBPrescaler function                          */
/**********************************************************************************/
/*  Description:  used to set  the pre scaler for AHB                             */
/*  input:        u8  (PRESCALER_CLOCK_NOT_DIVIDED,                               */
/*                    PRESCALER_AHB_CLOCK_DIVIDED_BY_X X=(2,4,8,16,64,128,256,512)*/  
/* 	output:       RCC_enuErrorStatus_t( RCC_OK ,RCC_InvalidPreScaler )            */
/**********************************************************************************/
RCC_enuErrorStatus_t RCC_setAHBPrescaler(u32 prescaler );


/**********************************************************************************/
/*                                GET PLL CONFIG FUNC                             */

u32 RCC_GETPLLSource(void);

u32 RCC_GetFactor_P(void);

u32 RCC_GetFactor_M(void);

u32 RCC_GetFactor_N(void);

u32 RCC_GETPrescaler(void);
/*                                                                                 */
/**********************************END*********************************************/






#endif /* RCC_H_ */
