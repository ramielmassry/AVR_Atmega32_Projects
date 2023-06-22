/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: HAL				  ******************/
/***************		SWC: Keypad				  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_ROW_NUMBER			4
#define KPD_COLUMN_NUMBER		4

#define KPD_ROW_PIN0			DIO_u8PIN0
#define KPD_ROW_PIN1			DIO_u8PIN1
#define KPD_ROW_PIN2			DIO_u8PIN2
#define KPD_ROW_PIN3			DIO_u8PIN3

#define KPD_COLUMN_PIN0			DIO_u8PIN4
#define KPD_COLUMN_PIN1			DIO_u8PIN5
#define KPD_COLUMN_PIN2			DIO_u8PIN6
#define KPD_COLUMN_PIN3			DIO_u8PIN7

#define Plus					43
#define Minus					45
#define Divide					47
#define Multiply				42
#define Equal					61

#define KPD_BUTTONS_VAL 		{{7,8,9,Divide},{4,5,6,Multiply},{1,2,3,Minus},{Equal,0,Equal,Plus}}
#define KPD_PORT  				DIO_u8PORTD

#define NO_PRESSED_KEY      	0xff

#endif
