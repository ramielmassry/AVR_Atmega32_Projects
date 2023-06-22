/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: HAL				  ******************/
/***************		SWC: SSD				  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/

#ifndef SSD_CONFIG_H_
#define SSD_CONFIG_H_

typedef struct ssd {
	                u8 type;
	                u8 data_port;
	                u8 enable_pin;
	                u8 enable_port;
                   }SSD_t;


#define SSD_PORTA			DIO_u8PORTA
#define SSD_PORTB			DIO_u8PORTB
#define SSD_PORTC			DIO_u8PORTC
#define SSD_PORTD			DIO_u8PORTD

#define SSD_ENABLE_PORT		DIO_u8PORTD
#define SSD_ENABLE_PIN		DIO_u8PIN0

#define COM_ANODE			     1
#define COM_CATHODE			     0
#define SSD_TYPE			COM_CATHODE


#endif
