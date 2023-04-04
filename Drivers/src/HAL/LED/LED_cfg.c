/*
 * LED_cfg.c
 *
 *  Created on: Feb 23, 2023
 *      Author: samir
 */


#include "LED.h"

 const LED_cfg_t LED_cfg[LEDS_COUNT]={  [LED_1]     = {
		 	 	 	 	 	 	 	 	 	 	 	 	                               .pin   = GPIO_PIN0,
                                                           .color = LED_RED,
                                                           .inti_state = LED_STATUS_OFF,
                                                           .mode = GPIO_MODE_OUTPUT_PP_HS,
                                                           .port = PORTA_GPIO,
                                                           .name = LED_1,
                                                           .connection = CONEC_ACTIVE_HIGH
    
                                                         },
                                        [LED_2]     = {
                                        				   .pin   = GPIO_PIN1,
                                                           .color = LED_GREEN,
                                                           .inti_state = LED_STATUS_OFF,
                                                           .mode = GPIO_MODE_OUTPUT_PP_HS,
                                                           .port = PORTA_GPIO,
                                                           .name = LED_2,
                                                           .connection = CONEC_ACTIVE_HIGH
    
                                                         },
                                        [LED_3] = {
                                        				   .pin   = GPIO_PIN2,
                                                           .color = LED_GREEN,
                                                           .inti_state = LED_STATUS_OFF,
                                                           .mode = GPIO_MODE_OUTPUT_PP_HS,
                                                           .port = PORTA_GPIO,
                                                           .name = LED_3,
                                                           .connection = CONEC_ACTIVE_HIGH
                                                     },

                                        [LED_4] = {
                                        				   .pin   = GPIO_PIN13,
                                                           .color = LED_GREEN,
                                                           .inti_state = LED_STATUS_OFF,
                                                           .mode = GPIO_MODE_OUTPUT_PP_HS,
                                                           .port = PORTC_GPIO,
                                                           .name = LED_4,
                                                           .connection = CONEC_ACTIVE_LOW
                                                     }

                                       };
