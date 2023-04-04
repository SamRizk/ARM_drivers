/*
 * LCD_cfg.c
 *
 *  Created on: Mar 24, 2023
 *      Author: samir
 */


#include "LCD.h"
const LCD_CFG_t LCD_CFG = {
                            .operation.mode                = EightBitMode,
                            .pins.Enable.GPIO_Mode         = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Enable.GPIO_Port         = PORTB_GPIO,
                            .pins.Enable.GPIO_Pin          = GPIO_PIN0,
                            .pins.RS.GPIO_Mode             = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.RS.GPIO_Port             = PORTB_GPIO,
                            .pins.RS.GPIO_Pin              = GPIO_PIN1,
                            .pins.RW.GPIO_Mode             = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.RW.GPIO_Port             = PORTB_GPIO,
                            .pins.RW.GPIO_Pin              = GPIO_PIN2,
                            .pins.Data[DataPin0].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin1].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin2].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin3].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin4].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin5].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin6].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin7].GPIO_Mode = GPIO_MODE_OUTPUT_PP_HS,
                            .pins.Data[DataPin0].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin1].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin2].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin3].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin4].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin5].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin6].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin7].GPIO_Port = PORTB_GPIO,
                            .pins.Data[DataPin0].GPIO_Pin  = GPIO_PIN3 ,
                            .pins.Data[DataPin1].GPIO_Pin  = GPIO_PIN4 ,
                            .pins.Data[DataPin2].GPIO_Pin  = GPIO_PIN5 ,
                            .pins.Data[DataPin3].GPIO_Pin  = GPIO_PIN6 ,
                            .pins.Data[DataPin4].GPIO_Pin  = GPIO_PIN7 ,
                            .pins.Data[DataPin5].GPIO_Pin  = GPIO_PIN8 ,
                            .pins.Data[DataPin6].GPIO_Pin  = GPIO_PIN9 ,
                            .pins.Data[DataPin7].GPIO_Pin  = GPIO_PIN10
                            
                            };