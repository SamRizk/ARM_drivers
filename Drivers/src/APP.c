#include "SCHED.h"
#include "LED.h"
#include "SWITCH.h"
#include "LCD.h"
#include "CHAT.h"

// void APP1_Runnable(void)
// {
//     LED_toggleState(LED_1);
// }

// void APP2_Runnable(void)
// {
//     LED_toggleState(LED_2);
// } 


// void APP3_Runnable(void)
// {
//     LED_toggleState(LED_3);
// } 

// void APP4_Runnable(void)
// {   
//     u32 RES;
//     SWC_getState(SWC_Alarm,&RES);
//     if(RES == SWC_STATUS_PREESED)
//     {
//         LED_setState(LED_4,LED_STATUS_ON);
//     }
//     else
//     {
//         LED_setState(LED_4,LED_STATUS_OFF);
//     }
// } 
void uartcp(void)
{
	trace_printf("Hi Form UART");
}

u8 msg[6];
void UART_re(void)
{
	CAHT_recec_msg(UART1,msg,6,uartcp);
}
void LCD_Write(void)
{
    static u8 idx=0;
    
    if (idx>=2)idx=0;
    LCD_writeStringAsynchronously(msg,6,0,(idx*6));
     
}
