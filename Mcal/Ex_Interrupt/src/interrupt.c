/*
 * interrupt.c
 *
 *  Created on: Oct 25, 2019
 *      Author: Mohamed
 */


/********************************************************************************************
 * 										INCLUDES											*
 ********************************************************************************************/
#include "interrupt.h"
#include "registers.h"
#include "Dio.h"




/********************************************************************************************
 * 									USED GLOBAL VARIABLES									*
 ********************************************************************************************/
volatile uint32 timer0_OVF_Flag = 0 ;
volatile uint8 EX_Int_Flag = 0 ;
volatile uint32 capture = 0 ;
volatile uint32 last_Ticks = 0 ;


/********************************************************************************************
 * 									Function Definitions									*
 ********************************************************************************************/

void Ex_Interrupt_Zero(edge_Config edge)
{

	/*
		 * Function: Ex_Interrupt_Zero.
		 *
		 *@definition:	Function to set the Triggiring edge of the External Interrupt 1. FALLING - RISING etc..
		 *
		 * @param IN: Name: edge.
		 * 			  type: Enum.
		 * 			  DESC: choosing from 4 different Triggering situations " FALLING EDGE - RISING EDGE - HIGH - LOW"
		 *
		 @return: void
		 */

	MCUCR = (MCUCR & 0xFC) | (edge & (0x03));
	SREG |= PIN_SEVEN; // Enable Global interrupt
	GICR |= PIN_SIX; // interrupt zero Enable

}

void Ex_Interrupt_Disable(void){

	/*
		 * Function: Ex_Interrupt_Disable.
		 *
		 *@definition:	the function disable the interrupts.
		 *
		 * @param IN: void.
		 *
		 * @return: void.
		 */
	GICR &= ~PIN_SIX;
}



ISR(INT0_vect){

	EX_Int_Flag++;

	if(EX_Int_Flag == 1)
	{

		Ex_Interrupt_Zero(FALLING_EDGE);
		TCNT0 = CLEARED;
		timer0_OVF_Flag = CLEARED ;


	}

	else if (EX_Int_Flag >=2)
	{


		EX_Int_Flag = CLEARED ;
		capture = TCNT0;
		last_Ticks = timer0_OVF_Flag;
		Ex_Interrupt_Zero(RISING_EDGE);

	}
	else
	{
		
	}



}

#if 0 
ISR(TIMER0_OVF_vect){

	timer0_OVF_Flag++;
	gpioPinDirection(PORTA, 0x31, OUTPUT);

	if(timer0_OVF_Flag == 2000){
		
		gpioPinToggle(PORTA, 0x31);		
		timer0_OVF_Flag = 0;
		
	}

}
#endif