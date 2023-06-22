/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: HAL				  ******************/
/***************		SWC: Keypad				  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/
 #include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8ColIdx;
	u8 Local_u8RowIdx;
	u8 Local_u8PressedKey=NO_PRESSED_KEY;
	u8 Local_u8PinState;
	u8 Local_u8KPDArr[KPD_ROW_NUMBER][KPD_COLUMN_NUMBER]= KPD_BUTTONS_VAL;
	u8 Local_u8ColumnArr[KPD_COLUMN_NUMBER]={KPD_COLUMN_PIN0,KPD_COLUMN_PIN1,KPD_COLUMN_PIN2,KPD_COLUMN_PIN3};
	u8 Local_u8RowArr[KPD_ROW_NUMBER]={KPD_ROW_PIN0,KPD_ROW_PIN1,KPD_ROW_PIN2,KPD_ROW_PIN3  };

	for(Local_u8ColIdx=0;Local_u8ColIdx<KPD_COLUMN_NUMBER;Local_u8ColIdx++)
	{
		/* Activating the column LOW  */
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColIdx],DIO_u8PIN_LOW);

		for(Local_u8RowIdx=0;Local_u8RowIdx<KPD_ROW_NUMBER;Local_u8RowIdx++)
		   {
			/* READING the ROW VALUE  */
			DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);

			if(Local_u8PinState==DIO_u8PIN_LOW)
			  {
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIdx][Local_u8ColIdx];

				/* Polling (busy waiting) until the key is released */
                while(Local_u8PinState==DIO_u8PIN_LOW)
			         {
					   DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
				     }
				return Local_u8PressedKey;
			  }
		   }

		/* Deactivate the column to  HIGH  */
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColIdx],DIO_u8PIN_HIGH);
	 }

	return Local_u8PressedKey;
}

