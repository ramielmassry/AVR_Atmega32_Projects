/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: HAL	    		  ******************/
/***************		SWC: CLCD   			  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*1- Set RS low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/*2- Set RW low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/*3- Send the command to LCD*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	/*4- Send enable pulse to LCD*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);


}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*1- Set RS high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);

	/*2- Set RW low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/*3- Send data to LCD*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	/*4- Send enable pulse to LCD*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

}

void CLCD_voidInit(void)
{
	_delay_ms(40);
	/*1- Function set command:2 lines, 5x7 font*/
	CLCD_voidSendCommand(0b00111000);

	/*2- Display on/off control:display on, blink cursor off*/
	CLCD_voidSendCommand(0b00001100);

	/*3- Display clear*/
	CLCD_voidSendCommand(0b00000001);

}

void CLCD_voidSendString(const char* Copy_u8String)
{
	u8 i = 0;
	while(Copy_u8String[i]!=NULL)
	{
		CLCD_voidSendData(Copy_u8String[i]);
	    i++;
	}
}

void CLCD_voidSendNumber(u32 Copy_u32Number)
{
	u8 Local_u8Iterator=10;
	u32 Local_u8ValueHolder=0;
	u8 Local_u8Flag=0;
	u32 Local_u32Check=1000000000;

	for(Local_u8Iterator=10;Local_u8Iterator>=0;Local_u8Iterator--)
	{
		if(Copy_u32Number/(Local_u32Check)>0||Local_u8Flag==1)
		{
			Local_u8Flag=1;
			Local_u8ValueHolder= (Copy_u32Number/(Local_u32Check));
			if(Local_u8ValueHolder<0 ||Local_u8ValueHolder>9 )
			    {
				break;
		    	}
			CLCD_voidSendData(Local_u8ValueHolder+48);
			Copy_u32Number= Copy_u32Number%(Local_u8ValueHolder*(Local_u32Check));

		}
		Local_u32Check/=10;
	}

}

void CLCD_voidGotoXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8DDRAMAddress;
	if(Copy_u8YPos == 0)
	{
		/*Check if in first line*/
		Local_u8DDRAMAddress = Copy_u8XPos;
	}
	else if(Copy_u8YPos == 1)
	{
		/*Check if in second line*/
		Local_u8DDRAMAddress = 0x40+Copy_u8XPos;
	}

	/*Set bit number 7 for setDDRAM Address then send the command*/
	CLCD_voidSendCommand(Local_u8DDRAMAddress+128);

}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress,Local_u8Counter;

	/*1- Calculate CGRAM address knowing that every pattern consumes 8 bytes*/
	Local_u8CGRAMAddress = Copy_u8PatternNumber*8;

	/*2- Send setCGRAM address command to LCD with setting bit_6 and clearing bit_7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/*3- Write pattern into CGRAM*/
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}

	/*4- Back to DDRAM to display the special pattern*/
	CLCD_voidGotoXY(Copy_u8XPos, Copy_u8YPos);

	/*5- Display the special pattern*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}
