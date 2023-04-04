
#include "RCC/RCC.h"
#include "SWITCH.h"
#include "LED.h"
#include "APP.h"
#include "LCD.h"
#include "SCHED/SCHED.h"
#include "CHAT.h"
void uartcp(void);

int
main(void)
{
	//RCC_setHSESystemClock();
	RCC_enableAHB1Peripheral(Peripheral_GPIOA);
	RCC_enableAHB1Peripheral(Peripheral_GPIOB);
	RCC_enableAHB1Peripheral(Peripheral_GPIOC);
	// SWC_init();
	// LED_init();
	// LCD_PinInit();
	// SCHED_init();
	// LCD_writeStringAsynchronously("Hello world",11,0,0);
	// SCHED_start();


	pu8 name = "SAMIR";
	CAHT_send_msg(UART1,name,6,uartcp);
 while (1)
   {

      // Add your code here.


   }
	return 0;
}

void uartcp(void)
{
	trace_printf("Hi Form UART");
}

