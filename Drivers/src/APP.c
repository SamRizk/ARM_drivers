#include "SCHED.h"
#include "LED.h"
#include "SWITCH.h"

void APP1_Runnable(void)
{
    LED_toggleState(LED_1);
}

void APP2_Runnable(void)
{
    LED_toggleState(LED_2);
} 


void APP3_Runnable(void)
{
    LED_toggleState(LED_3);
} 

void APP4_Runnable(void)
{   
    u32 RES;
    SWC_getState(SWC_Alarm,&RES);
    if(RES == SWC_STATUS_PREESED)
    {
        LED_setState(LED_4,LED_STATUS_ON);
    }
    else
    {
        LED_setState(LED_4,LED_STATUS_OFF);
    }
} 
