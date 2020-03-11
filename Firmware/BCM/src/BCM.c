/*
 * BCM.c
 *
 * Created: 11/17/2019 6:47:42 PM
 *  Author: Mohamed
 */

/*****************************************************************************************
 * 										INCLUDES										 *
 *****************************************************************************************/
#include "Uart.h"
#include "BCM.h"
#include "Dio.h"

/*****************************************************************************************
 * 										MACROS											 *
 *****************************************************************************************/

#define ZERO         (0)
#define ONE          (1)
#define IS_SET		 (1)
#define EIGHT		 (8)



/*
	DET ARRAY to receive Errors
*/

volatile uint8 error_Logs_Buffer[10] = {ZERO};
volatile uint8 g_Error_Buff_Index    = ZERO  ;

/*****************************************************************************************
 * 							LOCAL FUNTIONS Prototypes									 *
 *****************************************************************************************/
#if 0 
	static uint16 calculate_Size(void) ;
#endif	
	static void detecting_Frame(void)  ;
	static void Recieving_Frame(void)  ;
/*****************************************************************************************
 * 								Global Variables										 *
 *****************************************************************************************/

static volatile pointer_ToFunciton_t g_BCM_CallBack ;		
		
/*************************************
 *	Global Variables Used for TX	 *
 *									 *
 *************************************/
		
TX_EnmState_t current_State = TX_IDLE_STATE;
		
static volatile uint8 g_sendFirstByte		    = ZERO  ;
static volatile uint8 g_received_Data			= ZERO  ;
static volatile uint8 g_id_Sent_Flag			= ZERO  ; 
static volatile uint8 g_data_Is_Sent		    = ZERO  ;
static volatile uint8 g_Length_Counter			= ZERO  ;
static volatile uint8 g_Idle_State_Flag		    = ZERO  ;
static volatile uint8 TX_Arr_Index_Count		= ZERO  ;

FrameType_t frame_Type = ID_FRAME;


/*************************************
 *	Global Variables Used for RX	 *
 *									 *
 *************************************/

RX_EnmState_t RX_current_State = RX_IDLE_STATE;

static volatile uint8 g_Rx_Complete      = ZERO ;
//static volatile uint8* g_Rx_Data_Sent    = NULL ;
static volatile uint8 g_RX_count         = ZERO ;
static volatile uint8 g_DIS_RX_count     = ZERO ;

RX_FrameType_t RX_FrameType = RX_ID_FRAME ;




/*****************************************************************************************
 * 							Structures Declaration of TX and RX							 *
 *****************************************************************************************/

/*************************************
 *	Structure Used for TX			 *
 *									 *
 *************************************/
typedef struct
{
	uint8  TX_Id_Byte       ;
	uint8  TX_Checksum      ;
	uint8* TX_gPtr_Data_Sent;
	uint8  Tx_Complete      ;
	uint16 Tx_Data_Length   ;
	uint8 Tx_Lock_Flag      ;
}TX_dataFrame_s;


static TX_dataFrame_s TX_Frame = {'#',ZERO,NULL,ZERO,ZERO,ZERO};
	

/*************************************
 *	Structure Used for RX			 *
 *									 *
 *************************************/
typedef struct  
{
	uint16 RX_Buffer_Length  ;
	uint8  RX_Checksum       ;
	uint8  Rx_Lock_Flag		 ;
	uint8* Rx_Data_Sent      ;
	
}RX_Data_Frame_s;
	

static RX_Data_Frame_s RX_Frame = {ZERO,ZERO,ZERO,NULL};



/*****************************************************************************************
 * 							LOCAL FUNTIONS	IMPLEMENTATION								 *
 *****************************************************************************************/


/*************************************
 *	Local Functions Used for TX		 *
 *									 *
 *************************************/

static void detecting_Frame(void)
{
	switch (frame_Type)
	{
		case ID_FRAME:
			Uart_Send(TX_Frame.TX_Id_Byte);
			frame_Type = LENGTH_FRAME;
		break;
		
		case LENGTH_FRAME:
			if(g_Length_Counter == ZERO)
			{
				Uart_Send(TX_Frame.Tx_Data_Length);
				g_Length_Counter++;
			}
			else if(g_Length_Counter == ONE )
			{
				Uart_Send((TX_Frame.Tx_Data_Length>>EIGHT));
				frame_Type = DATA_FRAME;
				
			}
			else
			{
				
			}
			break;
		
		case DATA_FRAME:
			if (TX_Arr_Index_Count < TX_Frame.Tx_Data_Length)
			{
				Uart_Send(*(TX_Frame.TX_gPtr_Data_Sent+TX_Arr_Index_Count));
				TX_Frame.TX_Checksum += *(TX_Frame.TX_gPtr_Data_Sent + TX_Arr_Index_Count);
				TX_Arr_Index_Count++;
			}
			else
			{
				Uart_Send(TX_Frame.TX_Checksum);
				frame_Type = ID_FRAME;
			
				TX_Frame.Tx_Lock_Flag= ZERO ;
				TX_Arr_Index_Count   = ZERO ;
				TX_Frame.TX_Checksum = ZERO ;
				g_data_Is_Sent       = ZERO ;
				g_Length_Counter     = ZERO ;
				g_Idle_State_Flag    = ZERO ;
			
			}
		break;
		
		default:
		break;
	}
	
}




/*************************************
 *	Local Functions Used for RX 	 *
 *									 *
 *************************************/
static void report_Error(void)
{
	
	error_Logs_Buffer[g_Error_Buff_Index] = RX_Frame.Rx_Data_Sent[g_DIS_RX_count];
	g_Error_Buff_Index++;
	g_DIS_RX_count = ZERO ;
	RX_current_State = RX_IDLE_STATE;
}


static void Recieving_Frame(void)
{
	
	switch(RX_FrameType)
	{
		case RX_ID_FRAME :
		
		if(RX_Frame.Rx_Data_Sent != NULL)
		{
			
			if(g_DIS_RX_count < g_RX_count)
			{
				
				if( RX_Frame.Rx_Data_Sent[g_DIS_RX_count] != 'a')
				{
				/* DEBUGGING !
					gpioPinDirection(PORTA,0x04,OUTPUT);
					gpioPinToggle(PORTA,0x04);
				*/
					report_Error();
				}
				else
				{
					
					Uart_Send(RX_Frame.Rx_Data_Sent[g_DIS_RX_count]);
					g_DIS_RX_count++ ;
					RX_FrameType = RX_LENGTH_FRAME ;
				}
			}
		}
		else
		{
			report_Error();
		}
		
		break;
		
		case RX_LENGTH_FRAME :
		if(g_DIS_RX_count < g_RX_count)
		{
			if(RX_Frame.Rx_Data_Sent[g_DIS_RX_count] == (uint8)RX_Frame.RX_Buffer_Length)
			{
				/* DEBUGGING !
				gpioPinDirection(PORTA,0x04,OUTPUT);
				gpioPinToggle(PORTA,0x04);
				*/
				Uart_Send(RX_Frame.Rx_Data_Sent[g_DIS_RX_count]);
				g_DIS_RX_count++;
			}
			else if (RX_Frame.Rx_Data_Sent[g_DIS_RX_count] == (uint8)(RX_Frame.RX_Buffer_Length>>8))
			{
				
				RX_FrameType = RX_DATA_FRAME ;
				Uart_Send(RX_Frame.Rx_Data_Sent[g_DIS_RX_count]);
				g_DIS_RX_count++;
			}
			else
			{
				report_Error();
			}
		}
		break;
		
		case RX_DATA_FRAME :
		
		if(g_DIS_RX_count <RX_Frame.RX_Buffer_Length)
		{
			Uart_Send(RX_Frame.Rx_Data_Sent[g_DIS_RX_count]);
			TX_Frame.TX_Checksum += RX_Frame.Rx_Data_Sent[g_DIS_RX_count];
			g_DIS_RX_count++;
			
		}
		else
		{
		}
		break;
		
		default:
		break;
	}
	
	
	
	
}


#if 0
static uint16 calculate_Size (void)
{
	
	return (g_Rx_Data_Sent[1] | (8<<g_Rx_Data_Sent[2]));
}
#endif


/*****************************************************************************************
 * 								Function Implementation									 *
 *****************************************************************************************/

/*************************************
 * Functions Implementation for TX	 *
 *									 *
 *************************************/


/*
 * Function: TX_Flag.																		
 *																							
 *@definition:	The Function that will be Called through the Call_back of the UART.								
 *																																											
 *@param IN: void.		
 *																							
 *@return: void																			
 *			
 */
void TX_Flag(void)
{	
#if 0
	gpioPinDirection(PORTA,0x01,OUTPUT);
	gpioPinToggle(PORTA,0x01);
#endif	
	TX_Frame.Tx_Complete = IS_SET;
}


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
STATUS BCM_Send(uint8* ptrBuffer_array,uint16 length)
{	
	uint8 state = OK ;
	
	if(ptrBuffer_array == NULL || length <= ZERO)
	{
		report_Error();
		state = NOT_OK;
	}
	
	else
	{
		if(TX_Frame.Tx_Lock_Flag == ZERO)
		{
			TX_Frame.TX_gPtr_Data_Sent = ptrBuffer_array  ;
			TX_Frame.Tx_Data_Length    = length           ;
			TX_Frame.Tx_Lock_Flag      = IS_SET           ;
			current_State              = TX_TRANSMIT_STATE;
			frame_Type                 = ID_FRAME         ;
		}		
	}
	return state ;	
}

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
void BCM_TxDispatcher(void)
{
	switch (current_State)
	{
		case TX_IDLE_STATE:
		break;
		
		case TX_TRANSMIT_STATE:
		
			detecting_Frame();
			if(TX_Frame.Tx_Lock_Flag == ZERO)
			{
				current_State = TX_IDLE_STATE;
			}
			else
			{
				current_State = TX_SENDING_STATE;
			}	
		break;
		
		case TX_SENDING_STATE:
			if(TX_Frame.Tx_Complete == ONE)
			{
				TX_Frame.Tx_Complete = ZERO             ;
				current_State = TX_TRANSMIT_STATE       ;
			}
			else
			{
				
			}
		break;
		
		
		default:
		break;
	}
}


/*************************************
 * Functions Implementation for RX	 *
 *									 *
 *************************************/

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


STATUS BCM_Setup_Receive(uint8* ptrBuffer_array,uint16 length)
{	
	uint8 state = OK;
	if(ptrBuffer_array == NULL || length <= ZERO )
	{
		report_Error();
		state = NOT_OK ;
	}
	if(RX_Frame.Rx_Lock_Flag == ZERO)
	{
		RX_Frame.Rx_Data_Sent		= ptrBuffer_array    ;
		RX_Frame.RX_Buffer_Length	= length             ;
		RX_current_State		    = RX_RECEIVE_STATE   ;
		RX_Frame.Rx_Lock_Flag	    = IS_SET		     ;        	
	}
	
	return state;
}

/*
 * Function: RX_Flag.																		
 *																							
 *@definition:	the function that is going to be called by the CB function of the UART.							
 *																						
 *																							
 *@param IN: void.
 *																							
 *@return: void.
 */
void RX_Flag (void)
{
	 
	if(g_RX_count <RX_Frame.RX_Buffer_Length)
	{
		RX_Frame.Rx_Data_Sent[g_RX_count] = Uart_Recieve() ;
		gpioPinDirection(PORTA,0x01,OUTPUT)                ;
		gpioPinToggle(PORTA,0x01)                          ;
		g_RX_count++                                       ;
		g_Rx_Complete = ONE                                ;	
	}
	
}

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

void BCM_RxDispatcher (void)
{
	
	switch (RX_current_State)
	{
		
		case RX_IDLE_STATE:
			break;
			
		case RX_RECEIVE_STATE:
				
			Recieving_Frame();	
			
			if (g_DIS_RX_count >= RX_Frame.RX_Buffer_Length)
			{
				Uart_Send(RX_Frame.Rx_Data_Sent[g_DIS_RX_count]);
				
				g_BCM_CallBack();
				RX_current_State        = RX_IDLE_STATE  ;
				g_DIS_RX_count          =   ZERO		 ;
				g_RX_count              =   ZERO         ;
				RX_Frame.Rx_Lock_Flag   =   ZERO         ;
			}
			else
			{
				RX_current_State = RX_RECEIVE_IN_PROGRESS_STATE;
			}	
			break;
			
		case RX_RECEIVE_IN_PROGRESS_STATE:
			if(g_Rx_Complete == ONE)
			{
				RX_current_State = RX_RECEIVE_STATE;
				g_Rx_Complete = ZERO;
			}
			else
			{			
			}
			break;		
		default:
			break;
		
	}
		
	
}

/*
 * Function: BCM_Init.																		
 *																							
 *@definition:	The function Initialize BCM module.						
 *																						
 *																							
 *@param IN: void.		
 *																							
 *@return: STATUS																			
 *					OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */

void BCM_Init(void)
{	
	
	uart_TxSetCallBack(TX_Flag);
	uart_RxSetCallBack(RX_Flag);
	Uart_Init(&myUART);
	
}



void BCM_Set_CallBack(void(*ptrTo_Function)(void))
{
	g_BCM_CallBack =  ptrTo_Function ;
	
}




