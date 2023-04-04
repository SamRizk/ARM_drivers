/*
 * CHAT.c
 *
 *  Created on: Apr 3, 2023
 *      Author: samir
 */

/*******************************************Includes*******************************************************/

#include "CHAT.h"






/*====================================================================================================*/
/*************************************** Static Function Prototypes ***********************************/
/*====================================================================================================*/
static void INIT_PINS(u32 stream);


/***************************************** End Static Function ***************************************/
/*====================================================================================================*/









/*====================================================================================================*/
/************************************* implementation of APIs *****************************************/
/*====================================================================================================*/



CHAT_Status_t CAHT_send_msg(u32 stream,const pu8 msg,u32 size,CallBack Cbf)
{
    CHAT_Status_t status = CHAT_Ok;
    switch (stream)
    {
    case UART1:
        INIT_PINS(UART1);
        status= UART_SetTXCallback(UART1,Cbf);
        status= UART_Init(&UART_COM[UART1]);
        status= UART_SendBufferAsynZeroCopy(UART1,msg,size);
        break;
    case UART2:
        INIT_PINS(UART2);
        status= UART_SetTXCallback(UART2,Cbf);
        status= UART_Init(&UART_COM[UART2]);
        status= UART_SendBufferAsynZeroCopy(UART2,msg,size);
        break;
    case UART6:
        INIT_PINS(UART6);
        status= UART_SetTXCallback(UART6,Cbf);
        status= UART_Init(&UART_COM[UART6]);
        status= UART_SendBufferAsynZeroCopy(UART6,msg,size);
        break;    

    }
    return status;
}


CHAT_Status_t CAHT_recec_msg(u32 stream,const pu8 buffer,u32 size,CallBack Cbf)
{
    CHAT_Status_t status = CHAT_Ok;
    switch (stream)
    {
    case UART1:
       INIT_PINS(UART1);
       status= UART_SetRXCallback(UART1,Cbf);
       status= UART_Init(&UART_COM[UART1]);
       status= UART_ReceiveBuffer(UART1,buffer,size);
        break;
    case UART2:
       INIT_PINS(UART2);
       status= UART_SetRXCallback(UART2,Cbf);
       status= UART_Init(&UART_COM[UART2]);
       status= UART_ReceiveBuffer(UART2,buffer,size);
       break;
    case UART6:
       INIT_PINS(UART6);
       status= UART_SetRXCallback(UART6,Cbf);
       status= UART_Init(&UART_COM[UART6]);
       status= UART_ReceiveBuffer(UART6,buffer,size);
       break;    

    }
    return status;
}

/*====================================================================================================*/
/************************************* Static Function implementation *********************************/
/*====================================================================================================*/

static void INIT_PINS(u32 stream)
{
    switch (stream)
    {
    case UART1:
                GPIO_setPinDir(PORTA_GPIO,GPIO_PIN9,GPIO_MODE_AF_PP_HS);
	            GPIO_setPinDir(PORTA_GPIO,GPIO_PIN10,GPIO_MODE_AF_PP_PU_HS);
	            GPIO_selectAF(GPIO_AF7_USART1,GPIO_PIN10,PORTA_GPIO);
	            GPIO_selectAF(GPIO_AF7_USART1,GPIO_PIN9,PORTA_GPIO);
        break;
    case UART2:
                GPIO_setPinDir(PORTA_GPIO,GPIO_PIN2,GPIO_MODE_AF_PP_HS);
	            GPIO_setPinDir(PORTA_GPIO,GPIO_PIN3,GPIO_MODE_AF_PP_PU_HS);
	            GPIO_selectAF(GPIO_AF7_USART2,GPIO_PIN10,PORTA_GPIO);
	            GPIO_selectAF(GPIO_AF7_USART2,GPIO_PIN9,PORTA_GPIO);
        break;
    case UART6:
                GPIO_setPinDir(PORTA_GPIO,GPIO_PIN11,GPIO_MODE_AF_PP_HS);
	            GPIO_setPinDir(PORTA_GPIO,GPIO_PIN12,GPIO_MODE_AF_PP_PU_HS);
	            GPIO_selectAF(GPIO_AF8_USART6,GPIO_PIN10,PORTA_GPIO);
	            GPIO_selectAF(GPIO_AF8_USART6,GPIO_PIN9,PORTA_GPIO);
        break;    

    }   
}
