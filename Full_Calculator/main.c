#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "PORT_interface.h"
#include "KPD_interface.h"
#include "KPD_config.h"
u32 ReturnValue(u8 *ptr, u8 size);

void main(){
	u8 Local_u8Value;
	PORT_voidInit();
	 CLCD_voidInit();
	 u8 Local_u8Arr1[15];
	 u8 Local_u8It1=0;
	 u8 Local_u8Arr2[15];
	 u8 Local_u8It2=0;
	 u8 Local_u8Operand=0;
	 u8 Local_u32Number1;
	 u8 Local_u32Number2;
	 u8 Local_u32Result;
	while(1){
		do
		{Local_u8Value= KPD_u8GetPressedKey();

		}while(Local_u8Value==0xff);
		if(Local_u8Value<10){

			CLCD_voidSendData(Local_u8Value+'0');
		}
			if(Local_u8Operand==0){
				Local_u8Arr1[Local_u8It1]=Local_u8Value;
				Local_u8It1+=1;
			}
			if(Local_u8Operand>0){
				Local_u8Arr2[Local_u8It2]=Local_u8Value;
				Local_u8It2+=1;
		}
		else if(Local_u8Value<Equal && Local_u8Value>10){
			CLCD_voidSendData(Local_u8Value);
			Local_u8Operand=Local_u8Value;
		}
		else if(Local_u8Value==Equal){
			Local_u32Number1 = ReturnValue(&Local_u8Arr1[0],Local_u8It1);
			Local_u32Number2 = ReturnValue(&Local_u8Arr2[0],Local_u8It2);
			switch (Local_u8Operand){
			case Plus:
				Local_u32Result= Local_u32Number1 + Local_u32Number2;
				break;
			case Minus:
				Local_u32Result= Local_u32Number1 - Local_u32Number2;
				break;
			case Divide:
				Local_u32Result= Local_u32Number1 / Local_u32Number2;
				break;
			case Multiply:
				Local_u32Result= Local_u32Number1 * Local_u32Number2;
				break;
			}
			CLCD_voidSendNumber(Local_u32Result);
		}

	}
}



u32 ReturnValue(u8 *ptr, u8 size){
	u8 Local_u8I;
	u32 Local_u32Result=0;
	u8 Local_u8place;
	u8 Local_u8Val;
	for (Local_u8I=0;Local_u8I<=size;Local_u8I++){
		Local_u8Val=0;
		Local_u8place=Local_u8I;
		Local_u8Val = ptr[size-Local_u8I];
		while (Local_u8place>0){
		Local_u8Val *=10;
		Local_u8place-=1;
		}
		Local_u32Result+=Local_u8Val;
	}
}
