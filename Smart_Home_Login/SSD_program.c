/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: HAL				  ******************/
/***************		SWC: SSD				  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/

#include "STD_TYPES.h"
#include "util/delay.h"
#include "BCD.h"

#include "DIO_interface.h"
#include "SSD_config.h"

#include "SSD_private.h"
#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_register.h"


void SSD_voidSendNumber(SSD_t *ptr, u8 number){
	if (ptr->type== COM_ANODE){
		DIO_u8SetPinValue(ptr->enable_port,ptr->enable_pin,SSD_TYPE);
	}
	if(ptr->type==COM_CATHODE){
		DIO_u8SetPinValue(ptr->enable_port,ptr->enable_pin,SSD_TYPE);
		DIO_u8SetPortValue(ptr->data_port,BCD[number]);
	}
}

void SSD_voidOn(SSD_t * ptr){
	if (ptr->type== COM_ANODE){
		DIO_u8SetPinValue(ptr->enable_port,ptr->enable_pin,DIO_u8PIN_HIGH);

	}
	if(ptr->type==COM_CATHODE){
		DIO_u8SetPinValue(ptr->enable_port,ptr->enable_pin,DIO_u8PIN_LOW);
	}

}

void SSD_voidOff(SSD_t * ptr){
	if (ptr->type== COM_ANODE){
		DIO_u8SetPinValue(ptr->enable_port,ptr->enable_pin,DIO_u8PIN_LOW);
	}
	if(ptr->type==COM_CATHODE){
		DIO_u8SetPinValue(ptr->enable_port,ptr->enable_pin,DIO_u8PIN_HIGH);
	}
}
