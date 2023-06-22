/*******************************************************************/
/*******************************************************************/
/***************		Author: RAMI EL MASSRY	  ******************/
/***************		Layer: MCAL	    		  ******************/
/***************		SWC: EXTI   			  ******************/
/***************		Version: 1.00			  ******************/
/*******************************************************************/
/*******************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void EXTI_voidINT0Init(void);
void EXTI_voidINT1Init(void);
void EXTI_voidINT2Init(void);

#define EXTI_INT0				0
#define EXTI_INT1				1
#define EXTI_INT2				2

#define LOW_LEVEL				1  //Don't put it 0 cause of pre-build configuration
#define ON_CHANGE				2
#define FALLING_EDGE			3
#define RISING_EDGE				4

u8 EXTI_u8INTSetSenseControl(u8 Copy_u8Sense,u8 Copy_u8IntNumber);

/* Description : the function sets the required sense control for the available 3 external interrupts
 * Inputs:1 - Copy_u8Sense : this is the required sense control
 * 		   		Options : 1- LOW-LEVEL
 * 						  2- ON_CHANGE
 * 						  3- FALLING_EDGE
 * 						  4- RISING_EDGE
 *		  2 -  Copy_u8Number : this is the interrupt number required to set sense control
 *		  		Options : 1- EXTI_INT0
 *		  				  2- EXTI_INT1
 *		  				  3- EXTI_INT2
 * Output :Error State : to indicate for the function works correctly
 *				Options:  1- OK
 *						  2- NOK
 */

u8 EXTI_u8EnableINT(u8 Copy_u8IntNumber);
u8 EXTI_u8DisableINT(u8 Copy_u8IntNumber);

u8 EXTI_u8INT0SetCallBack(void (*Copy_pvCallBackFunc)(void), u8 Copy_u8IntNumber);

#endif
