/*
 * DMA.h
 *
 *  Created on: Apr 3, 2023
 *      Author: samir
 */

#ifndef MCLA_DMA_DMA_H_
#define MCLA_DMA_DMA_H_

/*******************************************Includes*******************************************************/
#include "Bit_math.h"
#include "Std_types.h"


/*******************************************************************************************************/
/******************************************* Macros ****************************************************/
/******************************************************************************************************/

/***************************************** DMA Channal ********************************************/
#define DMA_1                     ((void*)0x40026000)   /*Don't change the value*/
#define DMA_2                     ((void*)0x40026400)   /*Don't change the value*/




/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/


/******************************************************************************************************/
/******************************************* Types ****************************************************/
/******************************************************************************************************/


/*********************************************    ENUMS    ********************************************/
/*                                                                                                    */



/********************************************* ErrorStatus ********************************************/
typedef enum
{
    DMA_Ok,
    DMA_NOTOK,
	DMA_UndifinedValue,
	DMA_NullPtr

}DMA_ErrorStatus_t;

typedef enum
{
	DMA1,
	DMA2

}DMA_Id_t;

typedef enum
{
	DMA_Stream0 ,
	DMA_Stream1 ,
	DMA_Stream2 ,
	DMA_Stream3 ,
	DMA_Stream4 ,
	DMA_Stream5 ,
	DMA_Stream6 ,
	DMA_Stream7 

}DMA_Stream_t;


typedef enum 
{
    Dma_Channel0 ,
	Dma_Channel1 ,
	Dma_Channel2 ,
	Dma_Channel3 ,
	Dma_Channel4 ,
	Dma_Channel5 ,
	Dma_Channel6 ,
	Dma_Channel7 
    
}DMA_Channel_t;

typedef struct
{
    struct
    {
    	DMA_DIR_PeripheralToMemory,
    	DMA_DIR_MemoryToPeripheral,
    }DMA1_Direction_t;

    struct
    {
    	DMA_DIR_PeripheralToMemory,
    	DMA_DIR_MemoryToPeripheral,
    	DMA_DIR_MemoryToMemory
    }DMA2_Direction_t;

}DMA_Direction_t;


typedef enum
{
	Dma_Low ,
	Dma_Medium,
	Dma_High,
	Dma_VeryHigh

}DMA_Priority_t;


typedef enum
{
    DMA_DateSize_Byte ,
	DMA_DateSize_HalfWord,
	DMA_DateSize_Word
}DMA_size_t;

typedef enum
{
    DMA_FlowCtrl_Memory,
    DMA_FlowCtrl_Peripheral
}DMA_FlowController_t; 

typedef enum{

	DMA_DISABLE ,
	DMA_ENABLE

}DMA_State_t;

typedef enum
{
	DMA_MemoryBurst_Single ,
	DMA_MemoryBurst_INC4,
	DMA_MemoryBurst_INC8,
	DMA_MemoryBurst_INC16
}DMA_Burst_t;

typedef enum
{
    DMA_Mode_Normal,
    DMA_Mode_Circular
}DMA_Mode_t;

typedef enum
{
    DMA_PeripheralInc_Disable,
    DMA_PeripheralInc_Enable
}DMA_PeripheralInc_t;

typedef enum
{
    DMA_MemoryInc_Disable,
    DMA_MemoryInc_Enable
}DMA_MemoryInc_t;
typedef enum
{
    DMA_FIFOMode_Enable,
    DMA_FIFOMode_Disable
}DMA_FIFO_Mode_t;

typedef enum
{
    DMA_FIFOThreshold_1QuarterFull,
    DMA_FIFOThreshold_HalfFull,
    DMA_FIFOThreshold_3QuartersFull,
    DMA_FIFOThreshold_Full
}DMA_FIFO_Threshold_t;

typedef enum 
{
    Direct_ModeError,
    TransferError,
    Half-transfer,
    Transfer_Complete,
    FIFO_overrun_underrun
}DMA_INT_t;
/*********************************************   CFG Struct    ***************************************/
typedef struct  
{
    void* DMA_Peripheral;
    void* DMA_PeripheralBaseAddr;
    void* DMA_MemoryBaseAddr; 
    DMA_Direction_t DMA_DIR ;
    DMA_Channel_t DMA_Channel ;
    DMA_Stream_t DMA_Stream;
    DMA_PeripheralInc_t DMA_PeripheralInc;
    DMA_MemoryInc_t DMA_MemoryInc ;
    DMA_size_t DMA_PeripheralDataSize;
    DMA_size_t DMA_MemoryDataSize;
    DMA_Mode_t DMA_Mode;
    DMA_Priority_t DMA_PriorityLevel;
    DMA_FIFO_Mode_t DMA_FIFOMode;
    DMA_FIFO_Threshold_t DMA_FIFOThreshold;
    DMA_Burst_t DMA_MemoryBurst;
    DMA_Burst_t DMA_PeripheralBurst;
    u32 DMA_BufferSize; 
    struct 
    {
        DMA_State_t Direct_ModeError;
		DMA_State_t TransferError;
		DMA_State_t Half-transfer;
		DMA_State_t Transfer_Complete;
        DMA_State_t FIFO_overrun_underrun;
    }INT_t;
    
}DMA_CFG_t;


/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/
typedef void (*DMA_Cbf)(void);

/************************************************ APIs ***************************************************/
/*                                                                                                      */



/***************************************************************************************/
/*                                DMA_init     function                                */
/***************************************************************************************/
/*  Description: used to initialize DMA configuration                                  */
/* 	input:       DMA_CFG_t                                                             */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuInitCFG(const DMA_CFG_t* DMA_InitStruct);

/***************************************************************************************/
/*                                DMA_registerCallFunction     function                */
/***************************************************************************************/
/*  Description: used to register  DMA call back functions                             */
/* 	input:       dmaID, stream, cbf                                                    */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_registerCallFunction(DMA_Id_t dma, DMA_Stream_t stream, DMA_Cbf cbf);

/***************************************************************************************/
/*                                DMA_enuEnableStream     function                     */
/***************************************************************************************/
/*  Description: used to Enable  DMA stream configuration                              */
/* 	input:       DMA_Stream_t                                                          */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuEnableStream(DMA_Stream_t stream, void* dma);

/***************************************************************************************/
/*                                DMA_enuDisableStream     function                    */
/***************************************************************************************/
/*  Description: used to disable  DMA stream configuration                             */
/* 	input:       DMA_Stream_t                                                          */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuDisableStream(DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                                DMA_enuEnableINT        function                     */
/***************************************************************************************/
/*  Description: used to Enable  DMA stream INTerrupt                                  */
/* 	input:       DMA_Stream_t , INTFlag                                                */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuEnableINT(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                                DMA_enuDisableINT        function                    */
/***************************************************************************************/
/*  Description: used to Disable DMA stream INTerrupt                                  */
/* 	input:       DMA_Stream_t  , INTFlag                                               */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuDisableINT(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma);


/***************************************************************************************/
/*                                DMA_enuGitFlagStatus        function                 */
/***************************************************************************************/
/*  Description: used to Git DMA stream INTerrupt  flag status                         */
/* 	input:       DMA_Stream_t, INTFlag                                                 */
/* 	return:      DMA_State_t                                                           */
/***************************************************************************************/
extern DMA_State_t DMA_enuGitFlagStatus(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                                DMA_enuClearFlag            function                 */
/***************************************************************************************/
/*  Description: used to Clear DMA stream INTerrupt  flag                              */
/* 	input:       DMA_Stream_t, INTFlag                                                 */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuClearFlag(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                             DMA_enuSetCurrDataCounter            function           */
/***************************************************************************************/
/*  Description: used to Set DMA stream counter Date                                   */
/* 	input:       DMA_Stream_t, counterSize                                             */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuSetCurrDataCounter(u32 counterSize,DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                             DMA_enuGetCurrDataCounter            function           */
/***************************************************************************************/
/*  Description: used to Get DMA stream current counter Date                           */
/* 	input:       DMA_Stream_t,                                                         */
/* 	return:      u32                                                                   */
/***************************************************************************************/
extern u32 DMA_enuGetCurrDataCounter(DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                             DMA_enuDoubleBufferModeEnable            function       */
/***************************************************************************************/
/*  Description: used to Get DMA stream current counter Date                           */
/* 	input:       DMA_Stream_t,secondBufferAdd                                          */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuDoubleBufferModeEnable(DMA_Stream_t stream,void *secondBufferAdd,void* dma);

/***************************************************************************************/
/*                             DMA_enuDoubleBufferModeDisable       function           */
/***************************************************************************************/
/*  Description: used to Get DMA stream current counter Date                           */
/* 	input:       DMA_Stream_t,                                                         */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuDoubleBufferModeDisable(DMA_Stream_t stream,void* dma);

/***************************************************************************************/
/*                             DMA_enuPeripheralIncOffsetSizeConfig       function     */
/***************************************************************************************/
/*  Description: This function configures the increment mode and                       */ 
/*               size of the peripheral address for the specified DMA stream.          */
/* 	input:       DMA_Stream_t,DMA_PeripheralInc_t, DMA_size_t, voidAdrrTo DMA          */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuPeripheralIncOffsetSizeConfig(DMA_Stream_t stream,void* dma,DMA_PeripheralInc_t incMode, DMA_size_t phSize);


/***************************************************************************************/
/*                             DMA_enuMemoryIncOffsetSizeConfig       function         */
/***************************************************************************************/
/*  Description: This function configures the increment mode and                       */ 
/*               memory  address for the specified DMA stream.                         */
/* 	input:       DMA_Stream_t,DMA_PeripheralInc_t, DMA_size_t, voidAdrrTo DMA          */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuMemoryIncOffsetSizeConfig(DMA_Stream_t stream,void* dma,DMA_PeripheralInc_t incMode, DMA_size_t phSize);

/***************************************************************************************/
/*                             DMA_enuMemoryIncOffsetSizeConfig       function         */
/***************************************************************************************/
/*  Description: This function configures the flow controller                          */ 
/*               for the specified DMA stream.                                         */
/* 	input:       DMA_Stream_t,DMA_FlowController_t, voidAdrrTo DMA                     */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuFlowControllerConfig(void* dma,DMA_Stream_t stream,DMA_FlowController_t mode);

/***************************************************************************************/
/*                             DMA_enuFIFOThresholdConfig       function               */
/***************************************************************************************/
/*  Description: This function configures the threshold level of                       */ 
/*               the FIFO buffer for the specified DMA stream.                         */
/* 	input:       DMA_Stream_t,DMA_FIFO_Threshold_t, voidAdrrTo DMA                     */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuFIFOThresholdConfig(void* dma,DMA_Stream_t stream,DMA_FIFO_Threshold_t level);

/***************************************************************************************/
/*                             DMA_enuSetPrioConfig       function                     */
/***************************************************************************************/
/*  Description: This function configures the priority mode                            */ 
/*               for the specified DMA stream.                                         */
/* 	input:       DMA_Stream_t,DMA_FIFO_Threshold_t, voidAdrrTo DMA                     */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuSetPrioConfig(void* dma, DMA_Stream_t stream, DMA_Priority_t Priority);

/***************************************************************************************/
/*                          DMA_enuSetPeriphAddress       function                     */
/***************************************************************************************/
/*  Description: This function sets the peripheral address                             */ 
/*               for the specified DMA stream.                                         */
/* 	input:       DMA_Stream_t,voidADDrTo periph, voidAdrrTo DMA                        */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuSetPeriphAddress(void* dma, DMA_Stream_t stream, void* PeripheralAdd);

/***************************************************************************************/
/*                          DMA_enuSetMemoryAddress       function                     */
/***************************************************************************************/
/*  Description: This function sets the memory address                                 */ 
/*               for the specified DMA stream.                                         */
/* 	input:       DMA_Stream_t,voidADDrTo memory, voidAdrrTo DMA                        */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuSetMemoryAddress(void* dma, DMA_Stream_t stream, void* memoryAdd);

/***************************************************************************************/
/*                          DMA_enuSetPeriphBurst       function                       */
/***************************************************************************************/
/*  Description: This function sets the burst mode for the peripheral                  */ 
/*               data transfers for the specified DMA stream.                          */
/* 	input:       DMA_Stream_t,voidADDrTo memory, voidAdrrTo DMA                        */
/* 	return:      DMA_ErrorStatus_t                                                     */
/***************************************************************************************/
extern DMA_ErrorStatus_t DMA_enuSetPeriphBurst(void* dma, DMA_Stream_t stream, DMA_Burst_t burstMode);



#endif /* MCLA_DMA_DMA_H_ */
