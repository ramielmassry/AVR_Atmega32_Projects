/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: MCAL	    		  ******************/
/***************		SWC: EXTI   			  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

#define MCUCR 				*((volatile u8*)0x55)    // MCU Control register
#define MCUCR_ISC11			3						 //INT1 Sense Control BIT1
#define MCUCR_ISC10			2						 //INT1 Sense Control BIT0
#define MCUCR_ISC01			1					     //INT0 Sense Control BIT1
#define MCUCR_ISC00			0					     //INT0 Sense Control BIT0


#define MCUCSR 				*((volatile u8*)0x54)	 // MCU Control and status register
#define MCUCSR_ISC2			6						 //INT2 Sense Control BIT


#define GICR 				*((volatile u8*)0x5B)	 // General Interrupt control register
#define GICR_INT1			7						 //INT1 PIE
#define GICR_INT0			6						 //INT0 PIE
#define GICR_INT2			5						 //INT2 PIE

#endif 