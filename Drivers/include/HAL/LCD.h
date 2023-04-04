/*
 * LCD.h
 *
 *  Created on: Mar 24, 2023
 *      Author: samir
 */

#ifndef LCD_H_
#define LCD_H_

/*******************************************Includes*******************************************************/
#include "Bit_math.h"
#include "Std_types.h"

#include "GPIO/GPIO.h"
#include "LCD_cfg.h"
/*******************************************************************************************************/
/******************************************* Macros ****************************************************/
/******************************************************************************************************/
#define LCD_ROW_1 1
#define LCD_ROW_2 2




/**********************************************************************************************************/
/**********************************************END*********************************************************/
/**********************************************************************************************************/


/******************************************************************************************************/
/******************************************* Types ****************************************************/
/******************************************************************************************************/
typedef enum {
    LCD_OK,
    LCD_BUSY,
    LCD_IDEL,
    LCD_NOT_INITIALIZED,
    LCD_Parameters_Error
}LCD_status_t;

typedef enum {
    FourBitMode,
    EightBitMode
}LCD_Mode_t;

typedef struct 
{
     struct
    {
        LCD_Mode_t mode;
    }operation;

     struct
    {
        GPIO_CFG_t Enable;
        GPIO_CFG_t Data[8];
        GPIO_CFG_t RW;
        GPIO_CFG_t RS;
    }pins;

}LCD_CFG_t;


extern const LCD_CFG_t LCD_CFG;
/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/

/*************************************************** Varibles *********************************************/


/************************************************ APIs ********************************************/
/*                                                                                                */

/***************************************************************************************/
/*                                LCD_PinInit     function                             */
/***************************************************************************************/
/*  Description: used to initialize LCD pins                                           */
/* 	input:       void                                                                  */
/* 	return:      void                                                                  */
/***************************************************************************************/
void LCD_PinInit(void);

/***************************************************************************************/
/*                                LCD_FunctionInit     function                        */
/***************************************************************************************/
/*  Description: used to initialize LCD pins                                           */
/* 	input:       void                                                                  */
/* 	return:      void                                                                  */
/***************************************************************************************/
LCD_status_t LCD_FunctionInit(void);

/***************************************************************************************/
/*                 LCD_writeStringAsynchronously     function                          */
/***************************************************************************************/
/*  Description: used to write string on  LCD                                          */
/* 	input:       void                                                                  */
/* 	return:      LCD_status_t                                                          */
/***************************************************************************************/
LCD_status_t LCD_writeStringAsynchronously(const u8* str,u8 size,u8 pos_X,u8 pos_Y);

/***************************************************************************************/
/*                                LCD_Clear     function                               */
/***************************************************************************************/
/*  Description: used to clear LCD                                                     */
/* 	input:       void                                                                  */
/* 	return:      void                                                                  */
/***************************************************************************************/
void LCD_ClearReq(void);


/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
//void LCD_vidSendCommand(u8 cmd);


/***************************************************************************************/
/* Description! Interface to send the Data to the LCD Driver                           */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
//void LCD_voiWriteData(u8 Data);


/***************************************************************************************/
/* Description! Interface to start the writing process at certain digit in the LCD     */
/* Input      ! x = Column position , y = Row position                                 */
/* Output     ! LCD_Error_t                                                            */
/***************************************************************************************/
LCD_status_t LCD_enuSetPosition(u8 Copy_u8Row, u8 Copy_u8Col);

#endif /* HAL_LCD_LCD_H_ */