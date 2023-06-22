#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_config.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();

	char text_1[]= "HI I'M HAMOKSHA";
	char text_2[]= "I CAN DANCE";
	char text_3[]= "I PLAY FOOTBALL";

	u8 hamoksha[8]={0b01110,0b01110,0b00100,0b11111,0b00100,0b00100,0b01010,0b10001};

	u8 hamo_dance_1 [8]={0b01110,0b01110,0b00100,0b11111,0b00100,0b00100,0b01010,0b10001};
	u8 hamo_dance_2 [8]={0b01110,0b01110,0b00101,0b11111,0b10100,0b00100,0b01010,0b10001};
	u8 hamo_dance_3 [8]={0b01110,0b01110,0b10100,0b11111,0b00101,0b00100,0b01010,0b10001};
	u8 hamo_dance_4 [8]={0b01110,0b01110,0b10101,0b11111,0b00100,0b00100,0b01010,0b10001};
	u8 hamo_dance_5 [8]={0b01110,0b01110,0b01001,0b01111,0b01000,0b01100,0b01010,0b01001};
	u8 hamo_dance_6 [8]={0b01110,0b01110,0b10010,0b11110,0b00010,0b00110,0b01010,0b10010};
	u8 hamo_dance_7 [8]={0b01110,0b01110,0b00101,0b00110,0b00101,0b01000,0b01100,0b10011};
	u8 hamo_dance_8 [8]={0b01110,0b01110,0b10100,0b01100,0b10100,0b00010,0b00110,0b11001};
    u8 * hamo_dance [8]={hamo_dance_1 ,hamo_dance_2 ,hamo_dance_3 ,hamo_dance_4 ,hamo_dance_5 ,hamo_dance_6 ,hamo_dance_7 ,hamo_dance_8};

    u8 hamo_football_1 [8]={0b00111,0b00111,0b00010,0b00010,0b00010,0b01010,0b00110,0b01010};
    u8 hamo_football_2 [8]={0b00111,0b00111,0b00010,0b00010,0b00010,0b00010,0b01110,0b01010};
    u8 hamo_football_3 [8]={0b00111,0b00111,0b00010,0b00010,0b01010,0b00110,0b01010,0b00010};
    u8 hamo_football_4 [8]={0b00111,0b00111,0b00010,0b01010,0b00010,0b00110,0b01010,0b00010};
    u8 hamo_football_5[8]={0b00111,0b00111,0b01010,0b00010,0b00010,0b01110,0b00010,0b00010};
    u8 * hamo_football [5]={hamo_football_1,hamo_football_2,hamo_football_3,hamo_football_4,hamo_football_5};

	while(1)
	{
		// Introduction
		CLCD_voidGotoXY(0,0);
		CLCD_voidSendString(&text_1[0]);
		_delay_ms(2000);
	    CLCD_voidGotoXY(7,1);
		CLCD_voidWriteSpecialCharacter(hamoksha, 0, 7, 1);
		_delay_ms(3000);
		CLCD_voidSendCommand(0b00000001);
		_delay_ms(1000);


		// Dancing
		CLCD_voidGotoXY(2,0);
		CLCD_voidSendString(&text_2[0]);
		_delay_ms(2000);

		for(u8 i=0;i<8;i++)
		{
			CLCD_voidWriteSpecialCharacter(hamo_dance[i], i, i+4, 1);
			_delay_ms(500);
			CLCD_voidGotoXY(i+4, 1);
			CLCD_voidSendData(' ');
		}
		CLCD_voidSendCommand(0b00000001);
		_delay_ms(1000);


		// Football
		CLCD_voidGotoXY(0,0);
		CLCD_voidSendString(&text_3[0]);
		_delay_ms(2000);

		for (u8 i=0;i<5;i++)
		{
			CLCD_voidWriteSpecialCharacter(hamo_football[i],0,7,1);
			_delay_ms(500);
		}
		for (s8 i=4;i>=0;i--)
		{
			CLCD_voidWriteSpecialCharacter(hamo_football[i],0,7,1);
			_delay_ms(500);
		}
		CLCD_voidSendCommand(0b00000001);
		_delay_ms(1000);

	}

}
