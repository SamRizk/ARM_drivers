/*
 * LCD.c
 *
 *  Created on: Mar 24, 2023
 *      Author: samir
 */


/*******************************************Includes*******************************************************/
#include "LCD.h"
/*******************************************************************************************************/
/******************************************* Macros ****************************************************/
/******************************************************************************************************/
#define  LCD_OK     			8
#define  Max_Screen_Length      15
#define  Init_1					0
#define  Init_2					1
#define  NoReq  				0
#define  Write  				1
#define  Clear  				2
#define  GoXY   				3




/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/


/******************************************************************************************************/
/******************************************* Types ****************************************************/
/******************************************************************************************************/

typedef enum {
	Clear_Screen 		= 0x01,		// clears the entire screen content
	Return_Home  		= 0x02,		// Sets DDRAM to the entry point 00H and returns the cursor as well
	lcd_EntryMode		= 0x06,		// To enable the shift of the screen when cursor moves left or right
	Display_Off  		= 0x08,		// Display off and cursor as well
	Display_On   		= 0x0C,		// Set the display and Cursor off
	Cursor_On_Display_On= 0x0E,		// display on and cursor on
	Shift_Left   		= 0x18,		// Moves display to the left
	Shift_Right  		= 0x1C,		// Moves display to right
	Function_Sets 		= 0x38,		// 8-bit data, 2-line display, 5 x 7 font
	LCD_SetAddressCGRAM = 0x40,		// Set the CGRAM's address in Address Counter{AC}
	LCD_SetAddressDDRAM = 0x80,		// Set the DDRAM's address in Address Counter{AC}
	First_Row_Address   = 0x80,
	Second_Row_Address	= 0xC0
}LCD_inst_t;


typedef struct
{
	const u8 * str;
	u8 len;
	u8 currentPos;
}user_req_t;

/**********************************************************************************************************/
/***************************************************END****************************************************/
/**********************************************************************************************************/
u8 init_Done = 0;
static u8 state = Init_1;
u8 Req = NoReq;
user_req_t requestData;	
/*************************************** Static Function Prototypes ********************************/

static void LCD_WriteSeq();
static void LCD_ClearSeq(void);
/************************************** ** End Static Function ***************************************/

/************************************************ APIs ***************************************************/
/*                                                                                                       */

void LCD_PinInit(void)
{
	GPIO_init(&LCD_CFG.pins.Enable);
	GPIO_init(&LCD_CFG.pins.RS);
	GPIO_init(&LCD_CFG.pins.RW);
	GPIO_init(&LCD_CFG.pins.Data[DataPin0]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin1]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin2]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin3]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin4]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin5]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin6]);
	GPIO_init(&LCD_CFG.pins.Data[DataPin7]);
	
}

static void LCD_vidSendCommand(u8 cmd)
{
	u8 idx;
	GPIO_setReset(LCD_CFG.pins.Enable.GPIO_Port,LCD_CFG.pins.Enable.GPIO_Pin,GPIO_LOW);
	GPIO_setReset(LCD_CFG.pins.RS.GPIO_Port,LCD_CFG.pins.RS.GPIO_Pin,GPIO_LOW);
	GPIO_setReset(LCD_CFG.pins.RW.GPIO_Port,LCD_CFG.pins.RW.GPIO_Pin,GPIO_LOW);
	for ( idx = 0; idx < DataPinCount; idx++)
	{
		u8 tmp_cmd = ((cmd>>idx)&1);
		GPIO_setReset(LCD_CFG.pins.Data[idx].GPIO_Port,LCD_CFG.pins.Data[idx].GPIO_Pin,tmp_cmd);
	}
	
	GPIO_setReset(LCD_CFG.pins.Enable.GPIO_Port,LCD_CFG.pins.Enable.GPIO_Pin,GPIO_HIGH);

}

static void LCD_voiWriteData(u8 Data)
{
	u8 idx;
	GPIO_setReset(LCD_CFG.pins.Enable.GPIO_Port,LCD_CFG.pins.Enable.GPIO_Pin,GPIO_LOW);
	GPIO_setReset(LCD_CFG.pins.RS.GPIO_Port,LCD_CFG.pins.RS.GPIO_Pin,GPIO_HIGH);
	GPIO_setReset(LCD_CFG.pins.RW.GPIO_Port,LCD_CFG.pins.RW.GPIO_Pin,GPIO_LOW);
	for ( idx = 0; idx < DataPinCount; idx++)
	{
		u8 tmp_Data = ((Data>>idx)&1);
		GPIO_setReset(LCD_CFG.pins.Data[idx].GPIO_Port,LCD_CFG.pins.Data[idx].GPIO_Pin,tmp_Data);
	}

	GPIO_setReset(LCD_CFG.pins.Enable.GPIO_Port,LCD_CFG.pins.Enable.GPIO_Pin,GPIO_HIGH);
}

LCD_status_t LCD_enuSetPosition(u8 Copy_u8Row, u8 Copy_u8Col)
{
	u8 LOC_u8Address ;
	LCD_status_t status =LCD_OK;
    if(Copy_u8Row == LCD_ROW_1)
    {
    	LOC_u8Address = Copy_u8Col;
    }
    else if (Copy_u8Row == LCD_ROW_2)
    {
        LOC_u8Address = Copy_u8Col + Second_Row_Address;
    }
    else
    {
        status = LCD_Parameters_Error;
    }

    LCD_vidSendCommand(LOC_u8Address | (1<<7));  // + (128) ,  | (0x80)
	return status;
}

LCD_status_t LCD_FunctionInit(void)	
{
	switch(state)
	{
	case Init_1:
		LCD_vidSendCommand(Function_Sets);
		state = Init_2;
		break;

	case Init_2:
		LCD_vidSendCommand(Cursor_On_Display_On);
		state = LCD_NOT_INITIALIZED;
		break;

	case LCD_NOT_INITIALIZED:
		LCD_vidSendCommand(Clear_Screen);
		state = LCD_OK;
		break;

	case LCD_OK:
		LCD_vidSendCommand(lcd_EntryMode);
		init_Done = 1;
		state = LCD_IDEL;
		break;
	}
	return state;
}

LCD_status_t LCD_writeStringAsynchronously(const u8* str,u8 size,u8 pos_X,u8 pos_Y)
{
	LCD_status_t status = LCD_BUSY;
	if(state == LCD_IDEL)
	{
		state = LCD_BUSY;
		status = LCD_OK;
		Req =   Write;
		requestData.str 	   = str;
		requestData.len 	   = size;
		LCD_enuSetPosition(pos_X ,pos_Y);
		requestData.currentPos = 0;
		

	}
	else if(state == LCD_NOT_INITIALIZED)
	{
		status = LCD_NOT_INITIALIZED;
	}
	return status;
}

void LCD_Task(void)
{
	if(init_Done != 1)
	{
		LCD_FunctionInit();
	}
	else
	{
		switch(Req)
		{
		case Write:
			LCD_WriteSeq();		
			break;
		case Clear:
			LCD_ClearSeq();
		break;
		}
	}
}

void LCD_ClearReq()
{
	Req = Clear;
}

static void LCD_WriteSeq()
{
	if(requestData.currentPos==requestData.len)
	{
		state = LCD_IDEL;
		Req   = NoReq;
	}
	else if(requestData.currentPos==Max_Screen_Length)
	{
		LCD_enuSetPosition(LCD_ROW_2,0);
	}
	else
	{
		LCD_voiWriteData(requestData.str[requestData.currentPos++]);
	}
}

static void LCD_ClearSeq(void)
{
	LCD_vidSendCommand(Clear_Screen);
}
