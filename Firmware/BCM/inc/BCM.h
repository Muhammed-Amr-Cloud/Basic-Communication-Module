/*
 * BCM.h
 *
 * Created: 11/17/2019 6:46:58 PM
 *  Author: Mohamed
 */ 


#ifndef BCM_H_
#define BCM_H_

/*****************************************************************************************
 * 									INCLUDES											 *
 *****************************************************************************************/

#include "std_types.h"



/*****************************************************************************************
 * 									Enum												 *
 *****************************************************************************************/

typedef enum
{
	TX_IDLE_STATE,
	TX_TRANSMIT_STATE,
	TX_SENDING_STATE,
	
}TX_EnmState_t;


typedef enum
{
	RX_IDLE_STATE,
	RX_RECEIVE_STATE,
	RX_RECEIVE_IN_PROGRESS_STATE
	
}RX_EnmState_t;


typedef enum
{
	ID_FRAME,
	LENGTH_FRAME,
	DATA_FRAME
}FrameType_t;


typedef enum
{
	RX_ID_FRAME,
	RX_LENGTH_FRAME,
	RX_DATA_FRAME
}RX_FrameType_t;


/*****************************************************************************************
 * 									Function Prototypes									 *
 *****************************************************************************************/




void BCM_Init(void);

/*
 * Function: BCM_Send.																		
 *																							
 *@definition:Sends the Address of the buffer thats going to be Transmitted.							
 *																						
 *																							
 * @param IN: Name: 
 *			 type: uint8*
 *			 DESC: The Buffer Address that is going to be transmitted.
 *
 * @param IN: Name:	length
 *			  type:	uint16
 *			  length: length of the Data sent.																			
 @return: STATUS																			
 *					OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */
STATUS BCM_Send(uint8* ptrBuffer_array,uint16 size);


/*
 * Function: BCM_TxDispatcher.																		
 *																							
 *@definition: The Alternating Dispatcher that will check if the Data is Sent or not.					
 *																						
 *																							
 *@param IN: void.
 *																							
 *@return:void.
 *		
 */

void BCM_TxDispatcher(void);

/*
 * Function: BCM_RxDispatcher.																		
 *																							
 *@definition: The Alternating Dispatcher that checks if the Data is Received or not.								
 *																						
 *																							
 *@param IN: void.		
 *																							
 *@return: void																			
 */				


void BCM_RxDispatcher (void);

/*
 * Function: BCM_Setup_Receive.																		
 *																							
 *@definition:	The function Initialize the UART Communication.								
 *																						
 *																							
 * @param IN: Name:		
 *			  type:
 *			  DESC:
 *			  
 *			  																			
 @return: STATUS																			
 *					OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */

STATUS BCM_Setup_Receive(uint8* ptrBuffer_array,uint16 length);

void uart_SetCallBack(void (*ptr_Function) (void));






#endif /* BCM_H_ */