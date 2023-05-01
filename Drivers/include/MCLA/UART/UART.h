/*
 * UART.h
 *
 *  Created on: Mar 30, 2023
 *      Author: samir
 */

#ifndef UART_H_
#define UART_H_

/*******************************************Includes*******************************************************/
#include "Bit_math.h"
#include "Std_types.h"

/*******************************************************************************************************/
/******************************************* Macros ****************************************************/
/******************************************************************************************************/

/***************************************** UART Channal ********************************************/
#define UART_1      ((void *)0x40011000)  /*Don't change the value*/      
#define UART_2      ((void *)0x40004400)  /*Don't change the value*/
#define UART_6      ((void *)0x40011400)  /*Don't change the value*/


/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/


/******************************************************************************************************/
/******************************************* Types ****************************************************/
/******************************************************************************************************/


/*********************************************    ENUMS    ********************************************/
/**                                                                                                  **/
enum
{
	Uart_DISABLE ,
	Uart_ENABLE
};

/*Uart Channel*/
typedef enum
{
	UART1,
	UART2,
	UART6

}Uart_Channel_t;
/********************************************* ErrorStatus ********************************************/
typedef enum
{
	Uart_IDEL,
	Uart_Ok ,
    Uart_NOTOK,
	Uart_NullPointer,
	Uart_BUSY


}Uart_enuStatus_t;






/*********************************************   CFG Struct    ***************************************/

/*Uart Configuration*/
typedef struct
{
    void* UART_Channal;
    u8    Oversampling;
	u8    UartEnable;
	u8    WordLength;
	u8    ParityControl;
	u16   BaudRate;
}UART_CFG_t;

typedef void(*CallBack)(void);


/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/


/************************************************ APIs ***************************************************/
/*                                                                                                      */

/***************************************************************************************/
/*                                UART_init     function                               */
/***************************************************************************************/
/*  Description: used to initialize UART configuration                                 */
/* 	input:       UART_CFG_t                                                            */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_Init(const UART_CFG_t* copy_pCfg);


/***************************************************************************************/
/*                                UART_SendBufferAsynZeroCopy     function             */
/***************************************************************************************/
/*  Description: used to send buffer Asynchronosly in zeroCopy style                   */
/* 	input:       buffer ,size of the buffer                                            */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_SendBufferAsynZeroCopy(Uart_Channel_t UartChannel,const pu8 buffer, u32 size);


/***************************************************************************************/
/*                                UART_ReceiveBuffer     function                      */
/***************************************************************************************/
/*  Description: used to receive buffer Asynchronosly                                  */
/* 	input:       buffer ,size of the buffer                                            */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_ReceiveBuffer(Uart_Channel_t UartChannel, pu8 buffer, u32 size);

/***************************************************************************************/
/*                                UART_SetTXCallback     function                      */
/***************************************************************************************/
/*  Description: used to set callback for TX                                           */
/* 	input:       buffer ,size of the buffer                                            */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_SetTXCallback(Uart_Channel_t uartChannal, CallBack tx_callback);

/***************************************************************************************/
/*                                UART_SetRXCallback     function                      */
/***************************************************************************************/
/*  Description: used to set callback for RX                                           */
/* 	input:       Uart_Channel_t ,CallBack                                              */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_SetRXCallback(Uart_Channel_t uartChannal,CallBack rx_callback);



/*
 * How to configure UART using DMA
 *
 *  					-------------
 * 						| Receiving |
 * 						-------------
 * Uart Module
 * -------------
 *
 * ========================== Uart_ConfigType ======================
 * --> enable the receiving bit (ReceiveEnable) in the Uart configuration
 * --> enable the Uart
 * --> Disable all interrupt in case no need for any parity or idle checking
 * --> Initialize your baudrate
 *
 *
 * Dma Module
 * -------------
 *
 * =======================  Dma_config_t ==========================
 * --> Enable Stream 5 (for RX UART1)
 * --> Enable Channel 4 (for RX UART1)
 * --> Initialize whether you need it circular or not (used with double buffering if you want too)
 * --> Data direction to Peripheral to memory  {Data_Direction = Per_to_Mem}
 * --> Memory to be auto increment
 * --> Peripheral disable auto increment (as you only need to focus on DR register)
 * --> Initialize the memory size to be 1 byte in case of using 8 bit
 * --> Initialize the pheripheral size to be 1 byte as well
 * --> Initialize the priority level required
 * --> enable the interrupt required as example (Interrupt.Transfer_Complete = Dma_Enable)
 *
 *
 * ======================== Criteria_t =========================
 *
 * --> Initialize the Stream 5
 * --> Initialize the address of your buffer (Memory_0_Address = (u32)MemoryDestination)
 * --> Initialize the address of your DR Register of the Uart used in our
 * 		example is UART1 (Peripheral_Address = 0x40011004)
 *
 * Initialization
 * ---------------
 *
 * --> Enable Clocks
 * --> Enable DMA interrupt from NVIC
 * --> Register the call back function
 *
 * ======> Use Uart_ReceiveBufferDma --> to start Receiving
 * How to configure UART using DMA
 *
 *
 *
 *
 *
 *  					----------------
 * 						| Transmitting |
 * 						----------------
 * Uart Module
 * -------------
 *
 * ========================== Uart_ConfigType ======================
 * --> enable the Transmitting bit (TransmitEnable) in the Uart configuration
 * --> enable the Uart
 * --> Disable all interrupt in case no need for any parity or idle checking
 * --> Initialize your baudrate
 *
 *
 * Dma Module
 * -------------
 *
 * =======================  Dma_config_t ==========================
 * --> Enable Stream 7 (for TX UART1)
 * --> Enable Channel 4 (for TX UART1)
 * --> Initialize whether you need it circular or not (used with double buffering if you want too)
 * --> Data direction to Memory to Peripheral  {Data_Direction = Mem_to_Per}
 * --> Memory to be auto increment
 * --> Peripheral disable auto increment (as you only need to focus on DR register)
 * --> Initialize the memory size to be 1 byte in case of using 8 bit
 * --> Initialize the pheripheral size to be 1 byte as well
 * --> Initialize the priority level required
 * --> enable the interrupt required as example (Interrupt.Transfer_Complete = Dma_Enable)
 *
 *
 * ======================== Criteria_t =========================
 *
 * --> Initialize the Stream 7
 * --> Initialize the address of your buffer (Memory_0_Address = (u32)MemoryDestination)
 * --> Initialize the address of your DR Register of the Uart used in our
 * 		example is UART1 (Peripheral_Address = 0x40011004)
 *
 * Initialization
 * ---------------
 *
 * --> Enable Clocks
 * --> Enable DMA interrupt from NVIC
 * --> Register the call back function
 *
 * ======> Use Uart_ReceiveBufferDma --> to start Receiving
 *
 * */

 
/***************************************************************************************/
/*                                UART_SendBufferDMA     function                      */
/***************************************************************************************/
/*  Description: This function to Receive data using DMA                               */
/* 	input:       Uart_Channel_t ,CallBack                                              */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_ReceiveBufferDMA(Uart_Channel_t UartChannel);


/***************************************************************************************/
/*                                UART_SendBufferDMA     function                      */
/***************************************************************************************/
/*  Description: This function to send data using DMA                 	               */
/* 	input:       Uart_Channel_t ,CallBack                                              */
/* 	return:      Uart_enuStatus_t                                                      */
/***************************************************************************************/
extern Uart_enuStatus_t UART_SendBufferDMA(Uart_Channel_t UartChannel);

#endif /* MCLA_UART_UART_H_ */
