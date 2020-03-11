/*
 * Uart.h
 *
 * Created: 11/12/2019 11:20:40 AM
 *  Author: Mohamed
 */ 


#ifndef UART_H_
#define UART_H_

/*****************************************************************************************
 * 										INCLUDES										 *
 *****************************************************************************************/
#include "Uart_Lcfg.h"
#include "registers.h"
#include "std_types.h"

/*****************************************************************************************
 * 								Function Prototypes										 *
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

STATUS Uart_Init(uart_Cfg_S* uart_Configuration);

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

STATUS Uart_Send(uint8 byte);
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

uint8 Uart_Recieve(void);


void uart_TxSetCallBack(void (*ptr_Function) (void));

void uart_RxSetCallBack(void (*ptr_Function) (void));

#endif /* UART_H_ */