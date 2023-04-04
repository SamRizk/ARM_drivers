/*
 * SWITCH.c
 *
 *  Created on: Feb 23, 2023
 *      Author: samir
 */


/*******************************************Includes*******************************************************/
#include "SWITCH.h"
/*******************************************************************************************************/
/******************************************* Macros ****************************************************/
/******************************************************************************************************/
#define SWC_TRILERS    5



/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/


/******************************************************************************************************/
/******************************************* Types ****************************************************/
/******************************************************************************************************/
static u32 SWC_state[SWCS_COUNT];
static u32 SWC_counter[SWCS_COUNT];
static u32 SWC_prev[SWCS_COUNT];

/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/

/********************************************** Static Function Prototypes ********************************/
//static void Delay_ms(volatile int time_ms);

/********************************************** End Static Function ***************************************/

/************************************************ APIs ***************************************************/
/*                                                                                                       */



SWITCH_ErrorStatus_t SWC_init(void)
{
	SWITCH_ErrorStatus_t LOC_state = SWC_OK;
    GPIO_CFG_t LOC_gpiocfg;
    u32 LOC_loopCounter = 0;
    for (;LOC_loopCounter < SWCS_COUNT; LOC_loopCounter++)
    {
        LOC_gpiocfg.GPIO_Port = SWC_cfg[LOC_loopCounter].port;
        LOC_gpiocfg.GPIO_Pin  = SWC_cfg[LOC_loopCounter].pin;
        LOC_gpiocfg.GPIO_Mode = SWC_cfg[LOC_loopCounter].mode;
        LOC_state = GPIO_init(&LOC_gpiocfg);
        

    }
    return LOC_state;
}


void SWC_Task()
{
	u32 LOC_idx,current;
	for(LOC_idx=0;LOC_idx<SWCS_COUNT;LOC_idx++)
	{
        GPIO_readPhysVal(SWC_cfg[LOC_idx].port, SWC_cfg[LOC_idx].pin,&current);
        if(current == SWC_prev[LOC_idx])
        {
        	SWC_counter[LOC_idx]++;
        }
        else
        {
        	SWC_counter[LOC_idx]=0;
		}
        if(SWC_counter[LOC_idx] == 5)
        {
        	SWC_state[LOC_idx] = (current ^ SWC_cfg[LOC_idx].pull);
        	SWC_counter[LOC_idx]= 0;
        }
        SWC_prev[LOC_idx]= current;
	}

}




SWITCH_ErrorStatus_t SWC_getState(SWITCH_names_t SWC,u32* state)
{
	SWITCH_ErrorStatus_t LOC_state = SWC_OK;
	if(state == NULL)
	{
		LOC_state = SWC_NULLPOINTER;
	}
	else
	{
		*state = SWC_state[SWC];
	}

    return LOC_state;
}




/********************************************** Static Function imp **************************************/

//static void Delay_ms(volatile int time_ms)
//{
//	    int j;
//        for(j = 0; j < time_ms*4000; j++)
//            {}  /* excute NOP for 1ms */
//}

/********************************************** End Static Function ***************************************/


/*

SWITCH_ErrorStatus_t LOC_state = SWC_OK;
u32 LOC_GetPressed = SWC_STATUS_NOTPREESED;
// u8 LOC_LoopCounter = 0;
if(state != NULL)
{

        GPIO_readPhysVal(SWC_cfg[SWC].port, SWC_cfg[SWC].pin,state);
        if((*state ^ SWC_cfg[SWC].pull) == SWC_STATUS_PREESED )
        {
            LOC_GetPressed = SWC_STATUS_PREESED;
        }
        else
        {
            LOC_GetPressed = SWC_STATUS_NOTPREESED;
        }


    *state = LOC_GetPressed;

}
else
{
    LOC_state = SWC_NULLPOINTER;
}*/
