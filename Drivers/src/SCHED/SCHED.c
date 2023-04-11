/*
 * SCHED.c
 *
 *  Created on: Mar 18, 2023
 *      Author: samir
 */



/*====================================================================================================*/
/******************************************** includes ************************************************/
/*====================================================================================================*/
#include "SYSTICK/SYSTICK.h"

#include "SCHED/SCHED.h"



/******************************************** End of includes *****************************************/
/*====================================================================================================*/




/*====================================================================================================*/
/********************************************* defines ************************************************/
/*====================================================================================================*/

#define FLAG_H          1
#define FLAG_L          0

/********************************************* End Of defines *****************************************/
/*====================================================================================================*/



/*====================================================================================================*/
/********************************************** types *************************************************/
/*====================================================================================================*/
typedef struct 
{
	taskInfo_t* Task_info;
    u32 Remain; 
}Task_t;

static Task_t Tasks[NUM_OF_Runnables] ;



/********************************************* End Of types *******************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/********************************************** variables *********************************************/
/*====================================================================================================*/
u32 GLO_schedFlag = FLAG_L;

/********************************************** End variables *****************************************/
/*====================================================================================================*/




/*====================================================================================================*/
/*************************************** Static Function Prototypes ***********************************/
/*====================================================================================================*/
static void Sched(void);
static void tickCbf(void);
/***************************************** End Static Function ***************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/************************************* implementation of APIs *****************************************/
/*====================================================================================================*/
void SCHED_init(void)
{
    u32 idx;
    SYSTICK_init(25);
    SYSTICK_enableINT();
    SYSTICK_setCallBackFunc(&tickCbf);
    SYSTICK_setTick_ms(TICK_T);
    for ( idx = 0; idx < NUM_OF_Runnables; idx++)
    {
        Tasks[idx].Task_info = &TaskInfo[idx];
        Tasks[idx].Remain = TaskInfo[idx].startDelay;
    }
    

}


void SCHED_start (void)
{
    SYSTICK_start();
    while(1)
    {
        if (GLO_schedFlag)
        {
            Sched();
            GLO_schedFlag = FLAG_L;
        }   
    }
    
}

/****************************************** End Of APIs ***********************************************/
/*====================================================================================================*/


/*====================================================================================================*/
/************************************* Static Function implementation *********************************/
/*====================================================================================================*/

static void Sched()
{
    u32 idx;
    for ( idx = 0; idx < NUM_OF_Runnables; idx++)
    {
        if(Tasks[idx].Task_info)
        {
            if(Tasks[idx].Remain==0)
            {
                Tasks[idx].Task_info->cbf();
                Tasks[idx].Remain = Tasks[idx].Task_info->period;

            }
            Tasks[idx].Remain -= TICK_T;
        }
    }
    
}

static void tickCbf(void)
{
    if(GLO_schedFlag == 0)
    {
    	GLO_schedFlag = FLAG_H;
    }
    else
    {
        #warning "Cpu load 100%";
    	GLO_schedFlag = FLAG_H;

    }
}


/************************************ End Static Function implementation ******************************/
/*====================================================================================================*/




