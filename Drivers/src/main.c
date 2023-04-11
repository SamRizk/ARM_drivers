
#include "RCC/RCC.h"
#include "SWITCH.h"
#include "LED.h"
#include "APP.h"
#include "LCD.h"
#include "SCHED/SCHED.h"
#include "CHAT.h"
#include "DMA/DMA.h"

int
main(void)
{
	RCC_setHSESystemClock();
	RCC_enableAHB1Peripheral(Peripheral_GPIOA);
	RCC_enableAHB1Peripheral(Peripheral_GPIOB);
//	RCC_enableAHB1Peripheral(Peripheral_GPIOC);
//	// SWC_init();
	// LED_init();
	LCD_PinInit();
	CAHT_Init();
	SCHED_init();
	SCHED_start();


	// u8 name[5] ;
	// CAHT_recec_msg(UART1,name,5,uartcp);
//  while (1)
//    {

//       // Add your code here.


//    }
	return 0;
}


