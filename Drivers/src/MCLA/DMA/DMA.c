/*
 * DMA.c
 *
 *  Created on: Apr 3, 2023
 *      Author: samir
 */


/*====================================================================================================*/
/******************************************** includes ************************************************/
/*====================================================================================================*/
#include "DMA/DMA.h"

/******************************************** End of includes *****************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/********************************************* defines ************************************************/
/*====================================================================================================*/
#define DMA_Disable_Masks   ((u32)0xFFFFFFFEUL)

#define DMA_Enable_Masks   ((u32)0X00000001UL)

#define DMA_Double_Buffer_Enable ((u32)(1<<18))

#define DMA_Per_Inc_Off_Size_Enable ((u32)(1<<15))

#define DMA_Peripheral_Inc_ENABLE ((u32)(1<<9))

#define DMA_Memory_Inc_Enable ((u32)(1<<10))

#define DMA_Flow_Control_ENABLE ((u32)(1<<5))
#define NUMBER_OF_DMA				2

/********************************************* End Of defines *****************************************/
/*====================================================================================================*/



/*====================================================================================================*/
/********************************************** types *************************************************/
/*====================================================================================================*/

/*********************************************    REG    ********************************************/
typedef struct
{
	u32	LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;

	struct
	{
		u32 SxCR;
		u32 SxNDTR;
		u32 SxPAR;
		u32 SxM0AR;
		u32 SxM1AR;
		u32 SxFCR;

	}CFG_Reg[8];

}DMA_Reg_t;



/********************************************* End Of types *******************************************/
/*====================================================================================================*/



/*====================================================================================================*/
/********************************************** variables *********************************************/
/*====================================================================================================*/

static DMA_cbf CallbackFunction[NUMBER_OF_DMA][DMA_NumberOfStreams];


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
DMA_ErrorStatus_t DMA_enuInitCFG(const DMA_CFG_t* DMA_InitStruct)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    u32 tmp_reg;
    void* tmp_address = DMA_InitStruct->DMA_Peripheral;
    if(DMA_InitStruct)
    {
        tmp_reg = ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxCR;
        tmp_reg |= (DMA_InitStruct->DMA_Channel<<25)| (DMA_InitStruct->DMA_PeripheralBurst<<21)         |
                   (DMA_InitStruct->DMA_MemoryBurst<<23)| (DMA_InitStruct->DMA_MemoryDataSize<<13)      |
                   (DMA_InitStruct->DMA_PriorityLevel<<16)| (DMA_InitStruct->DMA_DoubleBuffer<<18)      |
                   (DMA_InitStruct->DMA_PeripheralDataSize<<11)|(DMA_InitStruct->DMA_MemoryInc<<10)     |
                   (DMA_InitStruct->DMA_PeripheralInc<<9)|
                   (DMA_InitStruct->DMA_CircularMode<<8)|(DMA_InitStruct->DMA_DIR<<6)                   |
                   (DMA_InitStruct->INT_t.Transfer_Complete<<4)|(DMA_InitStruct->INT_t.Half_transfer<<3)|
                   (DMA_InitStruct->INT_t.TransferError<<2)|(DMA_InitStruct->INT_t.Direct_ModeError<<1) |
                   (DMA_InitStruct->DMA_FlowControl<<5)|(DMA_InitStruct->DMA_PerIncOffSize<<15);
        ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxCR = tmp_reg;

        ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxNDTR = DMA_InitStruct->DMA_numberOfDataRegister;
        ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxPAR  = DMA_InitStruct->DMA_PeripheralBaseAddr;
        ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxM0AR = DMA_InitStruct->DMA_Memory_0_BaseAddr;
        
        if(DMA_InitStruct->DMA_DoubleBuffer)
        {
            ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxM1AR = DMA_InitStruct->DMA_Memory_1_BaseAddr;

        }
        
        tmp_reg = ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxFCR;
        tmp_reg |= (DMA_InitStruct->DMA_DirectMode << 7) | (DMA_InitStruct->DMA_FIFOThreshold<<1);
        ((DMA_Reg_t*)tmp_address)->CFG_Reg[DMA_InitStruct->DMA_Stream].SxFCR = tmp_reg;
        
    }
    else
    {
        status = DMA_NullPtr;
    }

    return status;
}


DMA_ErrorStatus_t DMA_registerCallFunction(DMA_Id_t dma, DMA_Stream_t stream, DMA_cbf CallbackF)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream <= DMA_NumberOfStreams)
    {
        if(CallbackF)
        {
            CallbackFunction[dma][stream] = CallbackF;
        }
        else
        {
            status = DMA_NullPtr;
        }
    }
    else
    {
        status = DMA_UndifinedValue;
    }
    return status;
}


DMA_ErrorStatus_t DMA_enuEnableStream(DMA_Stream_t stream, void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
    if(stream  <= DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;

        if(dma)
        {
            tmp_reg |= DMA_Enable_Masks;
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR = tmp_reg;

        }
        else
        {
            status = DMA_NullPtr;
        }
    }
    else
    {
        status = DMA_UndifinedValue;
    }
    return status;
}

DMA_ErrorStatus_t DMA_enuDisableStream(DMA_Stream_t stream,void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;

        if(dma)
        {
            tmp_reg &= DMA_Disable_Masks;
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR = tmp_reg;

        }
        else
        {
            status = DMA_NullPtr;
        }
    }
    return status;  
}

DMA_ErrorStatus_t DMA_enuEnableINT(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(INTFlag != 7)
        {
            tmp_reg |= (1<<INTFlag);
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR = tmp_reg;
        }
        else 
        {
            tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxFCR;
            tmp_reg |= (1<<INTFlag);
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxFCR = tmp_reg;
        }

    }
    return status;
}

DMA_ErrorStatus_t DMA_enuDisableINT(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;

        if(INTFlag != 7)
        {
            tmp_reg &= ~(1<<INTFlag);
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR = tmp_reg;
        }
        else 
        {
            tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxFCR;
            tmp_reg &= ~(1<<INTFlag);
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxFCR = tmp_reg;
        }

    }
    return status;
}

DMA_ErrorStatus_t DMA_enuGitFlagStatus(DMA_INT_t INTFlag,DMA_Stream_t stream,void* dma,u32* FlagStatus)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {
            if(stream < 4)
            {
                
                switch (stream)
                {
                case  DMA_Stream0:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,0);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,2);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,3);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,4);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,5);
                    break;
                    }
                break;
                case  DMA_Stream1:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,6);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,8);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,9);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,10);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,11);
                    break;
                    }
                break;
                case  DMA_Stream2:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,16);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,18);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,19);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,20);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,21);
                    break;
                    }
                break;
                case  DMA_Stream3:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,22);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,24);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,25);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,26);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->LISR,27);
                    break;
                    }
                break;
              
                }

            }
            else
            {
                switch (stream)
                {
                case  DMA_Stream4:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,0);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,2);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,3);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,4);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,5);
                    break;
                    }
                break;
                case  DMA_Stream5:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,6);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,8);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,9);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,10);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,11);
                    break;
                    }
                break;
                case  DMA_Stream6:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,16);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,18);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,19);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,20);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,21);
                    break;
                    }
                break;
                case  DMA_Stream7:
                    switch (INTFlag)
                    {
                    case FEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,22);
                    break;
                    case DMEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,24);
                    break;
                    case TEIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,25);
                    break;
                    case HTIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,26);
                    break;
                    case TCIFx:
                    *FlagStatus = GET_BIT(((DMA_Reg_t*)dma)->HISR,27);
                    break;
                    }
                break;
              
                }
                
            }
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;
}

DMA_ErrorStatus_t DMA_enuSetCurrDataCounter(u16 counterSize,DMA_Stream_t stream,void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {

        ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR = counterSize;
        
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;
}
u16 DMA_enuGetCurrDataCounter(DMA_Stream_t stream,void* dma)
{

    return ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR ;
        

}


DMA_ErrorStatus_t DMA_enuDoubleBufferModeEnable(DMA_Stream_t stream,void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
            tmp_reg |= DMA_Double_Buffer_Enable;

            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
        
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;
}

DMA_ErrorStatus_t DMA_enuDoubleBufferModeDisable(DMA_Stream_t stream,void* dma)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
            tmp_reg &= ~DMA_Double_Buffer_Enable;

            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
        
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;
}

DMA_ErrorStatus_t DMA_enuPeripheralIncOffsetSizeConfig(DMA_Stream_t stream,void* dma,DMA_PeripheralInc_t incMode)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg;
            if(incMode)
            {
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
                tmp_reg |= DMA_Per_Inc_Off_Size_Enable | DMA_Peripheral_Inc_ENABLE;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
            }
            else
            {
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
                tmp_reg &= ~DMA_Per_Inc_Off_Size_Enable;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
            }
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;
}


DMA_ErrorStatus_t DMA_enuMemoryIncOffsetSizeConfig(DMA_Stream_t stream,void* dma,DMA_State_t incMode)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg;
            if(incMode)
            {
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
                tmp_reg |= DMA_Memory_Inc_Enable ;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
            }
            else
            {
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
                tmp_reg &= ~DMA_Memory_Inc_Enable;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
            }
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;
}


DMA_ErrorStatus_t DMA_enuFlowControllerConfig(void* dma,DMA_Stream_t stream,DMA_FlowController_t mode)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg;
            if(mode == DMA_FlowCtrl_Peripheral)
            {
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
                tmp_reg |= DMA_Flow_Control_ENABLE ;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
            }
            else
            {
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
                tmp_reg &= ~DMA_Flow_Control_ENABLE;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxNDTR  = tmp_reg;
            }
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;    
}


DMA_ErrorStatus_t DMA_enuFIFOThresholdConfig(void* dma,DMA_Stream_t stream,DMA_FIFO_Threshold_t level)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
                u32 tmp_reg;
                tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxFCR;
                tmp_reg |= (level<<1) ;
                ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxFCR  = tmp_reg;
           
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;    
}



DMA_ErrorStatus_t DMA_enuSetPrioConfig(void* dma, DMA_Stream_t stream, DMA_Priority_t Priority)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg;
            tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
            tmp_reg |= (Priority<<16) ;
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR  = tmp_reg;
           
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;        
}


DMA_ErrorStatus_t DMA_enuSetPeriphAddress(void* dma, DMA_Stream_t stream, u32 PeripheralAdd)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxPAR = PeripheralAdd;
           
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;        

}

DMA_ErrorStatus_t DMA_enuSetMemoryAddress(void* dma, DMA_Stream_t stream, u32 memory0Add,u32 memory1Add)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxM0AR = memory0Add;
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxM0AR = memory1Add;
           
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;     
}


DMA_ErrorStatus_t DMA_enuSetPeriphBurst(void* dma, DMA_Stream_t stream, DMA_Burst_t burstMode)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
            tmp_reg= burstMode << 21;
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR = tmp_reg;
           
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status; 
}

DMA_ErrorStatus_t DMA_enuSetMemoryBurst(void* dma, DMA_Stream_t stream, DMA_Burst_t burstMode)
{
    DMA_ErrorStatus_t status = DMA_Ok;
    if(stream > DMA_NumberOfStreams)
    {
        status = DMA_UndifinedValue;
    }
    else
    {
        if(dma)
        {   
            u32 tmp_reg = ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR;
            tmp_reg= burstMode << 23;
            ((DMA_Reg_t*)dma)->CFG_Reg[stream].SxCR = tmp_reg;
           
        }
        else
        {
            status = DMA_NullPtr;
        }

    }
    return status;   
}
/****************************************** End Of APIs ***********************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/************************************* Static Function implementation *********************************/
/*====================================================================================================*/





/************************************ End Static Function implementation ******************************/
/*====================================================================================================*/



\
