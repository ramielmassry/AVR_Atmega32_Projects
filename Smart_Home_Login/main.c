#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "PORT_config.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "SSD_config.h"
#include "SSD_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "KPD_interface.h"
#include "KPD_config.h"

void INT0_ISR(void);
void WELCOME(void);
void LOGIN(void);
void SHUTDOWN(void);
u8 flag = 0;

void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	EXTI_voidINT0Init();
	EXTI_u8INT0SetCallBack(&INT0_ISR, EXTI_INT0);
	GIE_voidEnableGlobal();

	while(1)
	{
		if (flag == 1)
		{
			WELCOME();
		}

		else if (flag == 2)
		{
			LOGIN();
		}

		else if (flag == 3)
		{
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN3, DIO_u8PIN_HIGH);
		}

		/*else if (flag == 4)
		{
			SHUTDOWN();
		}*/

	}
}

void INT0_ISR(void)
{
	flag = 1;
}

void WELCOME(void)
{
	CLCD_voidGotoXY(2, 0);
    CLCD_voidSendString("WELCOME HOME");
    _delay_ms(2000);
    CLCD_voidSendCommand(0b00000001);
    _delay_ms(1000);
    flag = 2;
}

void LOGIN(void)
{
	u8 Local_u8ValuePressed;
	u8 Local_u8Itterator;
	u8 Local_u8SSD_Itterator;
	u8 User_ID_Arr[3];
	u8 Password_Arr[3];
	SSD_t obj ={SSD_TYPE,SSD_PORTB,SSD_ENABLE_PIN,SSD_ENABLE_PORT};

	CLCD_voidGotoXY(0, 0);
	CLCD_voidSendString("Enter ID : ");

	for (Local_u8Itterator=0;Local_u8Itterator<3;Local_u8Itterator++)
	{
		Local_u8ValuePressed = KPD_u8GetPressedKey();
		while(Local_u8ValuePressed == 255)
		{
		 Local_u8ValuePressed = KPD_u8GetPressedKey();
		}
		User_ID_Arr[Local_u8Itterator] = Local_u8ValuePressed;
		CLCD_voidSendNumber(Local_u8ValuePressed);
	}

	if ((User_ID_Arr[0]!=1) || (User_ID_Arr[1]!=2) || (User_ID_Arr[2]!=3))       /* ID is INCORRECT */
	{
		_delay_ms(500);
	    CLCD_voidSendCommand(0b00000001);
	    CLCD_voidSendString("Wrong ID");
	    _delay_ms(1000);
	    CLCD_voidSendCommand(0b00000001);
	}

	if ((User_ID_Arr[0]==1) && (User_ID_Arr[1]==2) && (User_ID_Arr[2]==3))       /*ID is CORRECT */
	{
		_delay_ms(500);
	    CLCD_voidSendCommand(0b00000001);
	    CLCD_voidSendString("Correct ID");
	    _delay_ms(1000);
	    CLCD_voidSendCommand(0b00000001);
	    _delay_ms(500);

	    /* Check for Password with 3 trials */

	    for(Local_u8SSD_Itterator=3;Local_u8SSD_Itterator>0;Local_u8SSD_Itterator--)
	    {
	    	SSD_voidOn(&obj);
	    	SSD_voidSendNumber(&obj,Local_u8SSD_Itterator);
	    	CLCD_voidSendString("Enter Pass: ");
	    	for (Local_u8Itterator=0;Local_u8Itterator<3;Local_u8Itterator++)
	    	{
	    		Local_u8ValuePressed = KPD_u8GetPressedKey();
	    		while(Local_u8ValuePressed == 255)
	    		{
	    			Local_u8ValuePressed = KPD_u8GetPressedKey();
	    		}
	    		Password_Arr[Local_u8Itterator] = Local_u8ValuePressed;
	    	    CLCD_voidSendNumber(Local_u8ValuePressed);
	    	}

	    	if ((Password_Arr[0]==3) && (Password_Arr[1]==2) && (Password_Arr[2]==1))  /*Password CORRECT*/
	    	{
	    		_delay_ms(500);
	    		CLCD_voidSendCommand(0b00000001);
	    		CLCD_voidSendString("Correct Password");
	    		_delay_ms(1000);
	    		CLCD_voidSendCommand(0b00000001);
	    		break;
	    	}

	    	if ((Password_Arr[0]!=3) || (Password_Arr[1]!=2) || (Password_Arr[2]!=1))  /*Password INCORRECT*/
	    	{
	    		_delay_ms(500);
	    		CLCD_voidSendCommand(0b00000001);
	    		CLCD_voidSendString("Wrong Password");
	    		_delay_ms(1000);
	    		CLCD_voidSendCommand(0b00000001);
	    	}
	    }

	    SSD_voidOff(&obj);
        flag = 3;
	}
}

void SHUTDOWN(void)
{
	CLCD_voidSendCommand(0b00000001);
}
