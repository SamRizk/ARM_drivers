/*
 * SCHED_CFG.c
 *
 *  Created on: Mar 18, 2023
 *      Author: samir
 */

#include "SCHED/SCHED.h"
//extern void APP1_Runnable(void);
//extern void APP2_Runnable(void);
//extern void APP3_Runnable(void);
//extern void APP4_Runnable(void);


const taskInfo_t TaskInfo[NUM_OF_Runnables]= {

                                                [LCD_APP]={
                                                            .name =LCD_APP,
                                                            .period = 2,
                                                            .cbf = LCD_Task,
                                                            .startDelay =30

                                                         },

											[LCD_writeString]={
                                                            .name =LCD_writeString,
                                                            .period = 10,
                                                            .cbf = LCD_Write,
                                                            .startDelay =70

                                                         },
											[UART_rec]={
				                                                  .name =UART_rec,
				                                                  .period = 10,
			                                                      .cbf = UART_re,
	                                                              .startDelay =50

				                                                         }


                                            };

