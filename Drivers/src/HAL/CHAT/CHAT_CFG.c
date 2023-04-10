 /*  Created on: Apr 3, 2023
 *      Author: samir
 */

#include "CHAT.h"


/***************** UART CFG *******************/
const UART_CFG_t UART_COM[UART_COUNT] = {

                            [UART1]={.BaudRate =9600 ,
                                     .Oversampling =0,
                                     .ParityControl =0,
                                     .UART_Channal = UART_1,
                                     .UartEnable= 1,
                                     .WordLength=0
                                     },
                            [UART2]= {.BaudRate =9600 ,
                                      .Oversampling =0,
                                      .ParityControl =0,
                                      .UART_Channal = UART_2,
                                      .UartEnable= 0,
                                      .WordLength=0
                                     },           
                            [UART6]= {.BaudRate =9600 ,
                                      .Oversampling =0,
                                      .ParityControl =0,
                                      .UART_Channal = UART_6,
                                      .UartEnable= 1,
                                      .WordLength=0
                                     }                                         
                                        };
/********************************************* End  **************************************************/
/*====================================================================================================*/

/***************** SPI CFG ********************/


