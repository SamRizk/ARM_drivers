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
                                                [APP1] = {
                                                            .name = APP1,
                                                            .period = 1200,
                                                            .cbf = APP1_Runnable,
                                                            .startDelay = 0
                                                         },

                                                [APP2] = {
                                                            .name = APP2,
                                                            .period = 1300,
                                                            .cbf = APP2_Runnable,
                                                            .startDelay = 0
                                                         },

                                                [APP3] = {
                                                            .name = APP3,
                                                            .period = 1100,
                                                            .cbf = APP3_Runnable,
                                                            .startDelay = 0
                                                         },

			                                       [APP4] = {
			                                                   .name = APP3,
			                                                   .period = 1100,
			                                                   .cbf = APP4_Runnable,
			                                                   .startDelay = 0
			                                                },
   
											               [SWC_APP]={
												            	   	   .name = SWC_APP,
												            		      .period = 5,
												            		      .cbf = SWC_Task,
												            		      .startDelay =0
                                                      	},
                                                [LCD_APP]={
                                                            .name =LCD_APP,
                                                            .period = 2,
                                                            .cbf = LCD_Task,
                                                            .startDelay =30,

                                                         }


                                            };

