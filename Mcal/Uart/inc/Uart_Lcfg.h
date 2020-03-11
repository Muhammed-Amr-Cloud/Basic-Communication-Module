/*
 * Uart_Lcfg.h
 *
 * Created: 11/12/2019 11:20:16 AM
 *  Author: Mohamed
 */ 


#ifndef UART_LCFG_H_
#define UART_LCFG_H_


/*****************************************************************************************
 * 									Configuration 										 *
 *****************************************************************************************/

typedef enum{
	
	UDR_INTERRUPT_ENABLE = 0x20,
	TX_INTERRUPT_ENABLE = 0x40,
	RX_INTERRUPT_ENABLE	= 0x80,
	ALL_INTERRUPT_DISABLE = 0 
	}uart_Interrupt_E;
	

typedef enum{
	
	RECIEVE_DISABLE,
	RECIEVE_ENABLE 
	
}uart_Recieve_E;


typedef enum{
	
	TRANSMIT_DISABLE,
	TRANSMIT_ENABLE
	
}uart_Transmit_E;


typedef enum
{
	
	ASYNCHORONOUS,
	SYNCHRONOUS 
	
}uart_Mode_E;

typedef enum
{
	
	DISABLED,
	EVEN_PARITY,
	ODD_PARITY 
	
}uart_Parity_Mode_E;


typedef enum
{
	
	ONE_BIT,
	TWO_BIT 
}uart_Stop_Bits_E;

typedef enum
{
	
	FIVE_BITS ,
	SIX_BITS,
	SEVEN_BITS,
	EIGHT_BITS,
	NIGNE_BITS 
}uart_Character_Size_E;


typedef enum 
{
	BAUD_RATE_2400 = 2400,
	BAUDR_RATE_9600 = 9600,
	BAUD_RATE_4800 = 4800,
	BAUD_RATE_19200 = 19200,
	
}uart_Baud_Rate_E;


/*****************************************************************************************
 * 							Configuration Structure										 *
 *****************************************************************************************/
typedef struct{
	
	uart_Recieve_E		    uart_Recieve;
	uart_Transmit_E			uart_Transmit;
	uart_Mode_E				uart_Mode;
	uart_Parity_Mode_E		uart_Parity;
	uart_Stop_Bits_E		uart_Stop_Bits;
	uart_Character_Size_E	uart_Character_Size;
	uart_Interrupt_E        uart_Interrupt_Enable;
	uart_Baud_Rate_E		uart_Baud_Rate;
		
	}uart_Cfg_S;


/*****************************************************************************************
 * 							Structure Definition Extern									 *
 *****************************************************************************************/	


extern uart_Cfg_S myUART;


#endif /* UART_LCFG_H_ */