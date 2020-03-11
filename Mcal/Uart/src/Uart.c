/*
 * Uart.c
 *
 * Created: 11/12/2019 11:20:56 AM
 *  Author: Mohamed
 */ 


/*****************************************************************************************
 * 									INCLUDES											 *
 *****************************************************************************************/
#include "interrupt.h"
#include "Uart.h"
#include "Dio.h"

/*****************************************************************************************
 * 									USED MACROS											 *
 *****************************************************************************************/

#define UCSRA_MASK			0xFD
#define DOUBLE_SPEED		(1<<1)
#define USEL_ENABLE			(1<<7)
#define TX_RX_MASK			(0xE7)
#define ONE						1
#define SHIFT_BY_ONE			1
#define SHIFT_BY_TWO			2
#define SHIFT_BY_FOUR			4
#define SHIFT_BY_THREE			3
#define SHIFT_BY_SIX			6
#define SHIFT_BY_SEVEN			7
#define CHARACTER_MASK		(0xFB)
#define CHARACTER_TWO_MASK	(0xF9)
#define MODE_MASK			(0xBF)
#define PARITY_MASK			(0xCF)
#define STOP_MASK			(0xF7)
#define TX_INT_MASK			(1<<6)
#define RX_INT_MASK			(1<<7)

/* bit masking for data */

#define BIT_THREE_MASK		(0x04)
#define ONE_TWO_BIT_MASK	(0x03)

#define F_CPU			   (8000000UL)
#define CONSTANT_SIXTEEN		(16UL)
#define CONSTANT_ONE			(1)


volatile uint8 g_data = 0 ;

 static volatile pointer_ToFunciton_t g_ptr_UART_TxCallBack = NULL ;
 static volatile pointer_ToFunciton_t g_ptr_UART_RxCallBack = NULL ;

/*****************************************************************************************
 * 									USFunction Definition								 *
 *****************************************************************************************/

/*
 * Function: Uart_Init.																		
 *																							
 *@definition:	The function Initialize the UART Communication.								
 *																						
 *																							
 * @param IN: uart_Configuration: Is a Pointer to Structure of the UAR CONFIGURATION.		
 *																							
 @return: STATUS																			
 *					OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */
STATUS Uart_Init(uart_Cfg_S* uart_Configuration)
{
	
	SREG |= (1<<7);
	//UART_UCSRB |= (UART_UCSRB & TX_RX_MASK)  |( (uart_Configuration->uart_Recieve)<<SHIFT_BY_FOUR )| ((uart_Configuration->uart_Transmit)<<SHIFT_BY_THREE) ;
	//
	UART_UCSRB |= (UART_UCSRB & CHARACTER_MASK) | (((uart_Configuration->uart_Character_Size) & (BIT_THREE_MASK))<< SHIFT_BY_TWO)| (ONE<<SHIFT_BY_SEVEN) | (ONE<<SHIFT_BY_SIX);
	
	
	
	UART_UCSRC = USEL_ENABLE | ((uart_Configuration->uart_Mode)<< SHIFT_BY_SIX)|((uart_Configuration->uart_Character_Size & (ONE_TWO_BIT_MASK)) <<SHIFT_BY_ONE)| ((uart_Configuration->uart_Parity)<<SHIFT_BY_FOUR)| ((uart_Configuration->uart_Stop_Bits)<<SHIFT_BY_THREE)  ;
	
	//UART_UCSRB |= (1<<3) | (1<<4) |(1<<7) | (1<<6);
	
	/*
	 *	BAUD RATE Register Equation:
	 *		USING : U2X = 0
	 *	DESC: UBRR = (CLOCKFREQUENCY/16*REQUIRED BAUD RATE)-1 
	 *		USING U2x = 1
	 *	DESC: UBRR = (CLOCKFREQUENCY / 8*REQUIRED BAUD RATE)-1
	 */
	UART_UBRRL = (uint8)((((uint32)F_CPU) / ((uint32)(CONSTANT_SIXTEEN*(uart_Configuration->uart_Baud_Rate)))) - CONSTANT_ONE);
	
	UART_UBRRH = (uint8)((((uint32)F_CPU) / ((uint32)(CONSTANT_SIXTEEN*(uart_Configuration->uart_Baud_Rate)))) - CONSTANT_ONE)>>8;
#if 0
	UART_UCSRC = (UART_UCSRC & MODE_MASK) | ((uart_Configuration->uart_Mode)<< SHIFT_BY_SIX);
	
	UART_UCSRC = (UART_UCSRC & CHARACTER_TWO_MASK) | ((uart_Configuration->uart_Character_Size & (ONE_TWO_BIT_MASK)) <<SHIFT_BY_ONE);
	
	UART_UCSRC = (UART_UCSRC & PARITY_MASK) | ((uart_Configuration->uart_Parity)<<SHIFT_BY_FOUR);
	
	UART_UCSRC = (UART_UCSRC & STOP_MASK) | ((uart_Configuration->uart_Stop_Bits)<<SHIFT_BY_THREE);
	
#endif
	
	return OK;
}

/*
 * Function: Uart_Send.
 *
 *@definition: The Function Sends A required 8 Bit Value
 *
 * @param IN: Name: byte
 *			  type: uint8
			DESC: The 8 bit value that its going to be sent			
 *
 @return: STATUS
 *					OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */


STATUS Uart_Send(unsigned char byte){
	//if(interrupt_flag == 0)
	{
		UART_UDR = byte;	
	}
	

	//while(!(UART_UCSRA & TX_INT_MASK));
	return OK;
}

/*
 * Function: Uart_Recieve.
 *
 *@definition: The function receives a 8 bit value
 *
 * @param IN:void
 *
 @return: uint8
 DESC: the Value read from RX
 */
uint8 Uart_Recieve(void)
{
	
	//while(!(UART_UCSRA & RX_INT_MASK));
	
	return UART_UDR;
}

void uart_TxSetCallBack(pointer_ToFunciton_t Tx_Flag)
{	
	if( Tx_Flag != NULL)
	{
		g_ptr_UART_TxCallBack = Tx_Flag ;
		
	}
	
}

void uart_RxSetCallBack(pointer_ToFunciton_t Rx_Flag)
{	
	if( Rx_Flag != NULL)
	{
		g_ptr_UART_TxCallBack = Rx_Flag ;
		
	}
}


ISR(USART_TXC_vect)
{
	
	g_ptr_UART_TxCallBack();	
}


ISR(USART_RXC_vect)
{
	g_ptr_UART_RxCallBack();
	
}
