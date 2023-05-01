/*
 * UART.c
 *
 *  Created on: Mar 30, 2023
 *      Author: samir
 */
/*====================================================================================================*/
/******************************************** includes ************************************************/
/*====================================================================================================*/
#include "GPIO/GPIO.h"
#include "UART/UART.h"
/******************************************** End of includes *****************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/********************************************* defines ************************************************/
/*====================================================================================================*/
#define F_CLK	        16000000
#define TransEnable     ((u32)1<<3)
#define ReceiveEnable   ((u32)1<<2)
#define TCIE            ((u32)1<<6)
#define RXNEIE          ((u32)1<<5)
/********************************************* End Of defines *****************************************/
/*====================================================================================================*/



/*====================================================================================================*/
/********************************************** types *************************************************/
/*====================================================================================================*/

/*********************************************    REG    ********************************************/
typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR[3];
	u32 GTPR;
}UART_Reg_t;

/*Uart Data storage to send*/
typedef struct
{
	pu8 Data;
	u32 Size;
	void* UART_Channal;
    u32 idx;

}UART_CFG_Buffer_t;

/********************************************* End Of types *******************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/********************************************** variables *********************************************/
/*====================================================================================================*/

static UART_CFG_Buffer_t user_SendData[3];
static UART_CFG_Buffer_t user_ReceData[3];
static CallBack cbfRX[3]={NULL};
static CallBack cbfTX[3]={NULL};
static u32 UART_TXstate[3]={Uart_IDEL,Uart_IDEL,Uart_IDEL};
static u32 UART_RXstate[3]={Uart_IDEL,Uart_IDEL,Uart_IDEL};



/********************************************** End variables *****************************************/
/*====================================================================================================*/




/*====================================================================================================*/
/*************************************** Static Function Prototypes ***********************************/
/*====================================================================================================*/



/***************************************** End Static Function ***************************************/
/*====================================================================================================*/




/*====================================================================================================*/
/************************************* implementation of APIs *****************************************/
/*====================================================================================================*/
Uart_enuStatus_t UART_Init(const UART_CFG_t* copy_pCfg)
{
    Uart_enuStatus_t LOC_Status= Uart_Ok;
    u32 Loc_tmpVal;
    u16	Loc_tmpMantissa;
	u16 Loc_tmpFraction;
    void* LOC_tmpRegisters;
    u32 LOC_tmpReg;
    if(copy_pCfg)
    {
        Loc_tmpVal = ((s64)F_CLK * 1000) / (copy_pCfg->BaudRate * (8 * (2 - copy_pCfg->Oversampling )));
        Loc_tmpFraction = (Loc_tmpVal % 1000) * (8 * (2 - copy_pCfg->Oversampling));
        Loc_tmpFraction = Loc_tmpFraction / 1000;
        if(Loc_tmpFraction > 0xF)
        {
            Loc_tmpMantissa += (Loc_tmpFraction & 0xF0); 
        }
        Loc_tmpMantissa = Loc_tmpVal / 1000;
        LOC_tmpRegisters = copy_pCfg->UART_Channal;
        /*Store the Baudrate*/
        ((UART_Reg_t*)LOC_tmpRegisters)->BRR = (Loc_tmpMantissa << 4) | (Loc_tmpFraction & 0x0F);
        /*Clear Control register for UART*/
        ((UART_Reg_t*)LOC_tmpRegisters)->CR[0] = 0;
        /*configure the UART*/
        LOC_tmpReg = ((UART_Reg_t*)LOC_tmpRegisters)->CR[0];
        LOC_tmpReg|= (copy_pCfg->Oversampling << 15) | (copy_pCfg->WordLength <<12) | (copy_pCfg->ParityControl<<9) |(copy_pCfg->UartEnable<<13);
        ((UART_Reg_t*)LOC_tmpRegisters)->CR[0] = LOC_tmpReg;

        /*clear the sr register*/
        ((UART_Reg_t*)LOC_tmpRegisters)->SR = 0;


    }
    else
    {
        LOC_Status = Uart_NullPointer;
    }
    return LOC_Status;

}


Uart_enuStatus_t UART_SendBufferAsynZeroCopy(Uart_Channel_t UartChannel,const pu8 buffer, u32 size)
{
    Uart_enuStatus_t LOC_Status = Uart_BUSY;
    u32 LOC_tmpReg;
    void *bufferTmp = (UartChannel == UART1) ? UART_1 : (UartChannel == UART2) ? UART_2 : UART_6;
    if(buffer)
    {
        if(UART_TXstate[UartChannel] == Uart_IDEL)
        {
            user_SendData[UartChannel].Data = buffer;
            user_SendData[UartChannel].Size = size;
            user_SendData[UartChannel].UART_Channal = bufferTmp;
            user_SendData[UartChannel].idx = 0;
            UART_TXstate[UartChannel] = Uart_BUSY;
            LOC_tmpReg = ((UART_Reg_t*)bufferTmp)->CR[0];
            LOC_tmpReg |= TransEnable |TCIE   ;
            ((UART_Reg_t*)bufferTmp)->CR[0] = LOC_tmpReg;
            ((UART_Reg_t*)bufferTmp)->DR = user_SendData[UartChannel].Data[user_SendData[UartChannel].idx];
            user_SendData[UartChannel].idx++;
            LOC_Status = Uart_Ok;
            
        }
    }
    else
    {
        LOC_Status = Uart_NullPointer;
    }
    return LOC_Status;
}


Uart_enuStatus_t UART_ReceiveBuffer(Uart_Channel_t UartChannel, pu8 buffer, u32 size)
{
    Uart_enuStatus_t LOC_Status = Uart_BUSY;
    u32 LOC_tmpReg;
    void *bufferTmp = (UartChannel == UART1) ? UART_1 : (UartChannel == UART2) ? UART_2 : UART_6;
    if(buffer)
    {
        if(UART_RXstate[UartChannel] == Uart_IDEL)
        {
            user_ReceData[UartChannel].Data = buffer;
            user_ReceData[UartChannel].Size = size;
            user_ReceData[UartChannel].UART_Channal = bufferTmp;
            user_ReceData[UartChannel].idx = 0;
            UART_RXstate[UartChannel] = Uart_BUSY;

            LOC_tmpReg = ((UART_Reg_t*)bufferTmp)->CR[0];
            LOC_tmpReg |= ReceiveEnable | RXNEIE ;
            ((UART_Reg_t*)bufferTmp)->CR[0] = LOC_tmpReg;
            ((UART_Reg_t*)user_SendData[UartChannel].UART_Channal)->SR= 0;

            LOC_Status = Uart_Ok;
            
        }
    }
    else
    {
        LOC_Status = Uart_NullPointer;
    }
    return LOC_Status;

}


Uart_enuStatus_t UART_SetTXCallback(Uart_Channel_t uartChannal, CallBack tx_callback)
{
    Uart_enuStatus_t LOC_status = Uart_Ok;
    if(tx_callback)
    {
        cbfTX[uartChannal] = tx_callback;
    }
    else
    {
        LOC_status = Uart_NullPointer;
    }
    return LOC_status;
}


Uart_enuStatus_t UART_SetRXCallback(Uart_Channel_t uartChannal,CallBack rx_callback)
{
    Uart_enuStatus_t LOC_status = Uart_Ok;
    if(rx_callback)
    {
        cbfRX[uartChannal] = rx_callback;
    }
    else
    {
        LOC_status = Uart_NullPointer;
    }
    return LOC_status;
}


Uart_enuStatus_t UART_SendBufferDMA(Uart_Channel_t UartChannel)
{
    Uart_enuStatus_t LOC_status = Uart_Ok;
    void *bufferTmp = (UartChannel == UART1) ? UART_1 : (UartChannel == UART2) ? UART_2 : UART_6;
    ((UART_Reg_t*)bufferTmp)->CR[3] |= 1<<7;
    return LOC_status;

}

Uart_enuStatus_t UART_ReceiveBufferDMA(Uart_Channel_t UartChannel)
{
    Uart_enuStatus_t LOC_status = Uart_Ok;
    void *bufferTmp = (UartChannel == UART1) ? UART_1 : (UartChannel == UART2) ? UART_2 : UART_6;
    ((UART_Reg_t*)bufferTmp)->CR[3] |= 1<<6;
    return LOC_status;
}


/****************************************** End Of APIs ***********************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/************************************* Static Function implementation *********************************/
/*====================================================================================================*/
void USART1_IRQHandler(void)
{
    if(cbfTX[UART1])
    {
        if((((UART_Reg_t*)UART_1)->SR >> 6) & 0x01)
        {
            if(user_SendData[UART1].idx < user_SendData[UART1].Size)
            {
                ((UART_Reg_t*)UART_1)->DR = user_SendData[UART1].Data[user_SendData[UART1].idx];
                user_SendData[UART1].idx++;

            }
            else
            {
                UART_TXstate[UART1] = Uart_IDEL;
                cbfTX[UART1]();
            }
        }
    }
    if(cbfRX[UART1])
    {
        if( ((((UART_Reg_t*)UART_1)->SR >>5) & 0x01) &&  UART_RXstate[UART1] == Uart_BUSY)
        {
            user_ReceData[UART1].Data[user_ReceData[UART1].idx] = ((UART_Reg_t*)UART_1)->DR;
            user_ReceData[UART1].idx++;
            if(user_ReceData[UART1].idx == user_ReceData[UART1].Size)
            {
                UART_RXstate[UART1] = Uart_IDEL;
                ((UART_Reg_t*)UART_1)->CR[0] &= ~(1<<5);
                cbfRX[UART1]();
            }
        } 
    }
}



void USART2_IRQHandler(void)
{
    if(cbfTX[UART2])
    {
        if((((UART_Reg_t*)UART_2)->SR >> 6) & 0x01)
        {
            if(user_SendData[UART2].idx < user_SendData[UART2].Size)
            {
                ((UART_Reg_t*)UART_2)->DR = user_SendData[UART2].Data[user_SendData[UART2].idx];
                user_SendData[UART2].idx++;

            }
            else
            {
                UART_TXstate[UART2] = Uart_IDEL;
                cbfTX[UART2]();
            }
        }
    }
    if(cbfRX[UART2])
    {
        if( ((((UART_Reg_t*)UART_2)->SR >>5) & 0x01) &&  UART_RXstate[UART2] == Uart_BUSY)
        {
            user_ReceData[UART2].Data[user_ReceData[UART2].idx] = ((UART_Reg_t*)UART_2)->DR;
            user_ReceData[UART2].idx++;
            if(user_ReceData[UART2].idx == user_ReceData[UART2].Size)
            {
                UART_RXstate[UART2] = Uart_IDEL;
                ((UART_Reg_t*)UART_2)->CR[0] &= ~(1<<5);
                cbfRX[UART2]();
            }
        } 
    }
}




void USART6_IRQHandler(void)
{
    if(cbfTX[UART6])
    {
        if((((UART_Reg_t*)UART_6)->SR >> 6) & 0x01)
        {
            if(user_SendData[UART6].idx < user_SendData[UART6].Size)
            {
                ((UART_Reg_t*)UART_6)->DR = user_SendData[UART6].Data[user_SendData[UART6].idx];
                user_SendData[UART6].idx++;

            }
            else
            {
                UART_TXstate[UART6] = Uart_IDEL;
                cbfTX[UART6]();
            }
        }
    }
    if(cbfRX[UART6])
    {
        if( ((((UART_Reg_t*)UART_6)->SR >>5) & 0x01) &&  UART_RXstate[UART6] == Uart_BUSY)
        {
            user_ReceData[UART6].Data[user_ReceData[UART6].idx] = ((UART_Reg_t*)UART_6)->DR;
            user_ReceData[UART6].idx++;
            if(user_ReceData[UART6].idx == user_ReceData[UART6].Size)
            {
                UART_RXstate[UART6] = Uart_IDEL;
                ((UART_Reg_t*)UART_6)->CR[0] &= ~(1<<5);
                cbfRX[UART6]();
            }
        } 
    }
}

/************************************ End Static Function implementation ******************************/
/*====================================================================================================*/









