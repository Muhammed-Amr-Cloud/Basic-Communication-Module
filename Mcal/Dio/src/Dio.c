/*
 * gpio.c
 *
 * Created: 10/21/2019 3:23:25 PM
 *  Author: AVE-LAP-064
 */ 

/************************************************************************/
/*								INCLUDES	                            */
/************************************************************************/
#include "std_types.h"
#include "registers.h"
#include "Dio.h"


/************************************************************************/
/*				 GPIO functions Definitions	                            */
/************************************************************************/
void gpioPortDirection(uint8 port, uint8 direction){
	
	/**
 * Description: The function takes the port and the Direction, for initializing the port.
 * 	PORT: are selected with: PORTA, PORTB, PORTC, PORTD
 * 	direction : INPUT, OUTPUT
 * @param port
 * @param direction
 */
	switch (port)
	{
		case PORTA :
			PORTA_DIR = direction;
			break;
			
		case PORTB :
			PORTB_DIR = direction;
			break;
			
		case PORTC :
			PORTC_DIR = direction;	
			break;
			
		case PORTD :
			PORTD_DIR = direction;
			break;
			
			
		default :
			break;		
		
	}	
	
}




void gpioPortWrite(uint8 port, uint8 value){
	
	/**
 * Description: the function takes the port and the value , to Write in the port
 * PORT: are selected with: PORTA, PORTB, PORTC, PORTD.
 * value: HIGH, LOW
 * @param port
 * @param value
 */
	
	switch (port)
	{
		case PORTA :
		PORTA_DATA = value;
		break;
		
		case PORTB :
		PORTB_DATA = value;
		break;
		
		case PORTC :
		PORTC_DATA = value;
		break;
		
		case PORTD :
		PORTD_DATA = value;
		break;
		
		
		default :
		break;
		
	}
	
	
	
	
}

void gpioPortToggle(uint8 port){
	
	/**
 * Description: Function is used to write to the port
 * @param port
 */
	
	switch (port)
	{
		case PORTA :
			PORTA_DATA ^= OUTPUT;
			break;
		
		case PORTB :
			PORTB_DATA ^= OUTPUT;
			break;
		
		case PORTC :
			PORTC_DATA ^= OUTPUT;
			break;
		
		case PORTD :
			PORTD_DATA ^= OUTPUT;
			break;
			
		default :
			break;
		
	}
	
}




uint8 gpioPortRead(uint8 port){
	
	/**
 * Description: the function is used to Read the port.
 * @param port
 * @return
 */
	
	switch (port)
	{
		case PORTA :
			return PORTA_PIN ; 
			break;
		
		case PORTB :
			return PORTB_PIN;
			break;
		
		case PORTC :
			return PORTC_PIN;
			break;
			
		case PORTD :
			return PORTD_PIN;
			break;
		
		default :
			return -1;
			break;
		
	}
	
	
}



void gpioPinDirection(uint8 port, uint8 pins, uint8 direction){
	
	/**
 * Description: Function is used to initialize a pin.
 * The user Should select between PORTA,B,C,D
 * @param port
 * @param pins
 * @param direction : OUTPUT,INPUT
 */
	switch (port)
	{
		case PORTA :
			if(direction == OUTPUT)
				PORTA_DIR |= pins ;
			else
				PORTA_DIR &= ~(pins);
					
			break;
		
		case PORTB :
			if(direction == OUTPUT)
				PORTB_DIR |= pins ;
			else
				PORTB_DIR &= ~(pins);
			break;
			
		case PORTC :
			if(direction == OUTPUT)
				PORTC_DIR |= pins ;
			else
				PORTC_DIR &= ~(pins);
			break;
		case PORTD :
			if(direction == OUTPUT)
				PORTD_DIR |= pins ;
			else
				PORTD_DIR &= ~(pins);
			break;
		
		default :
			break;
		
	}
		
}


void gpioPinWrite(uint8 port, uint8 pins, uint8 value){
		
		/**
 * Description: Function is used to write to a single pin
 * @param port : PORTA,B,C,D
 * @param pins
 * @param value : HIGH, LOW
 */
		switch (port)
		{
			case PORTA :
			if(value == HIGH)
				PORTA_DATA |= pins ;
			else
				PORTA_DATA &= ~(pins);
			break;
			
			case PORTB :
			if(value == HIGH)
				PORTB_DATA |= pins ;
			else
				PORTB_DATA &= ~(pins);
			break;
			
			case PORTC :
			if(value == HIGH)
				PORTC_DATA |= pins ;
			else
				PORTC_DATA &= ~(pins);
			break;
			case PORTD :
			if(value == HIGH)
				PORTD_DATA |= pins ;
			else
				PORTD_DATA &= ~(pins);
			break;
			
			default :
			break;
		
	}
	
	
	
}


void gpioPinToggle(uint8 port, uint8 pins){
	/**
 * Description: Toggle A single pin.
 * @param port : PORTA,B,C,D
 * @param pins : required Pin.
 */
	
	
	switch (port)
	{
		case PORTA :
			PORTA_DATA ^= pins ;
			break;
			
		case PORTB :
			PORTB_DATA ^= pins;
			break;
		
		case PORTC :
			PORTC_DATA ^=pins;
			break;
		
		case PORTD :
			PORTD_DATA ^= pins;
			break;
		
		default :
			break;
		
	}
	
	
	
	
}




uint8 gpioPinRead(uint8 port, uint8 pin){
	
	/**
 * Description:  Function is used to read the Pin.
 * @param port
 * @param pin
 * @return
 */
	switch (port)
	{
		case PORTA :
			return (READ_BIT(PORTA_PIN,pin) >> pin );
		break;
		
		case PORTB :
			return (READ_BIT(PORTB_PIN,pin) >> pin );
		break;
		
		case PORTC :
			return (READ_BIT(PORTC_PIN,pin) >> pin );
		break;
		
		case PORTD :
			return (READ_BIT(PORTD_PIN,pin) >> pin );
		break;
		
		default :
		break;
		
	}
	return (READ_BIT(port,pin) >> pin );
}



void gpioUpperNibbleDirection(uint8 port, uint8 direction){
	
	/**
 * Description: function is used to initialize the upper nibble of the port.
 * @param port
 * @param direction : OUTPUT, INPUT
 */
	switch (port)
	{
		case PORTA :
			if(direction == OUTPUT)
				PORTA_DIR = ((PORTA_DIR & (0x0F)) | (0xF0)) ;
			else
				PORTA_DIR = (PORTA_DIR & (0x0F)) ;	
			
			break;
		
		case PORTB :
			if(direction == OUTPUT)
				PORTB_DIR = ((PORTA_DIR & (0x0F)) | (0xF0)) ;
			else
				PORTB_DIR = (PORTA_DIR & (0x0F)) ;
			break;
		
		case PORTC :
			if(direction == OUTPUT)
				PORTC_DIR = ((PORTA_DIR & (0x0F)) | (0xF0)) ;
			else
				PORTC_DIR = (PORTA_DIR & (0x0F)) ;
			break;
		
		case PORTD :
			if(direction == OUTPUT)
				PORTD_DIR = ((PORTA_DIR & (0x0F)) | (0xF0)) ;
			else
				PORTD_DIR = (PORTA_DIR & (0x0F)) ;
			break;
		
		default :
			break;
	}
	
}




void gpioUpperNibbleWrite(uint8 port, uint8 value){
	
	/**
 * Description: Function is Used to Write to the Upper nibble of the port.
 * @param port
 * @param value : High, LOw
 */
	switch (port)
	{
		case PORTA :
		if(value == HIGH)
			PORTA_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
			PORTA_DATA = (PORTA_DATA & (0x0F)) ;
		
		break;
		
		case PORTB :
		if(value == HIGH)
			PORTB_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
			PORTB_DATA = (PORTA_DATA & (0x0F)) ;
		break;
		
		case PORTC :
		if(value == HIGH)
			PORTC_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
			PORTC_DATA = (PORTA_DATA & (0x0F)) ;
		break;
		
		case PORTD :
		if(value == HIGH)
			PORTD_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
			PORTD_DATA = (PORTA_DATA & (0x0F)) ;
		break;
		
		default :
		break;
	}
			
}

void gpioUpperNibbleToggle(uint8 port){
	
	/**
 * Description: Function is used to Toggle the Upper nibble of the port.
 * @param port
 */
	switch (port)
	{
		case PORTA :
			PORTA_DATA ^=  (0xF0) ;
		break;
		
		case PORTB :
			PORTB_DATA ^=  (0xF0) ;
		break;
		
		case PORTC :
			PORTC_DATA ^=  (0xF0) ;
		break;
		
		case PORTD :
			PORTD_DATA ^=  (0xF0) ;
		break;
		
		default :
		break;
	}
	
}


uint8 gpioUpperNibbleRead(uint8 port){
	
	/**
 * Description: function is used to read the upper nibble of the port.
 * @param port
 * @return
 */
	switch (port)
	{
		case PORTA :
			return ((PORTA_PIN & (0xF0))>> 4) ;
			break;
		
		case PORTB :
			return ((PORTB_PIN & (0xF0))>> 4) ;
			break;
		
		case PORTC :
			return ((PORTC_PIN & (0xF0))>> 4) ;
			break;
		
		case PORTD :
			return ((PORTD_PIN & (0xF0))>> 4) ;
			break;
			
		default :
			return -1;
			break;
	}
	
}


void gpioLowerNibbleDirection(uint8 port, uint8 direction){
	/**
 * Description: function is used to initialize the lower nibble of the port.
 * @param port
 * @param direction
 */
	switch (port)
	{
		case PORTA :
		if(direction == OUTPUT)
			PORTA_DIR = ((PORTA_DIR & (0x0F)) | (0x0F)) ;
		else
			PORTA_DIR = (PORTA_DIR & (0x0F)) ;
		
		break;
		
		case PORTB :
		if(direction == OUTPUT)
			PORTB_DIR = ((PORTA_DIR & (0x0F)) | (0x0F)) ;
		else
			PORTB_DIR = (PORTA_DIR & (0x0F)) ;
		break;
		
		case PORTC :
		if(direction == OUTPUT)
			PORTC_DIR = ((PORTA_DIR & (0x0F)) | (0x0F)) ;
		else
			PORTC_DIR = (PORTA_DIR & (0x0F)) ;
		break;
		
		case PORTD :
		if(direction == OUTPUT)
			PORTD_DIR = ((PORTA_DIR & (0x0F)) | (0x0F)) ;
		else
			PORTD_DIR = (PORTA_DIR & (0x0F)) ;
		break;
		
		default :
		break;
	}
}


void gpioLowerNibbleWrite(uint8 port, uint8 value){
	
	/**
 * Description: function is used to write to the lower nibble of the port.
 * @param port
 * @param value
 */
	switch (port)
	{
		case PORTA :
		if(value == HIGH)
			PORTA_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
			PORTA_DATA = (PORTA_DATA & (0x0F)) ;
		
		break;
		
		case PORTB :
		if(value == HIGH)
		PORTB_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
		PORTB_DATA = (PORTA_DATA & (0x0F)) ;
		break;
		
		case PORTC :
		if(value == HIGH)
		PORTC_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
		PORTC_DATA = (PORTA_DATA & (0x0F)) ;
		break;
		
		case PORTD :
		if(value == HIGH)
		PORTD_DATA = ((PORTA_DATA & (0x0F)) | (0xF0)) ;
		else
		PORTD_DATA = (PORTA_DATA & (0x0F)) ;
		break;
		
		default :
		break;
	}
	
	switch (port)
	{
		case PORTA :
			PORTA_DATA = (PORTA_DIR & (0xF0)) | (value & (0x0F)) ;
			break;
		
		case PORTB :
			PORTB_DATA = (PORTB_DIR & (0xF0)) | (value & (0x0F)) ;
			break;
		
		case PORTC :
			PORTC_DATA = (PORTC_DIR & (0xF0)) | (value & (0x0F)) ;
			break;
		
		case PORTD :
			PORTD_DATA = (PORTD_DIR & (0xF0)) | (value & (0x0F)) ;
			break;
		
		default :
			break;
	}
}


void gpioLowerNibbleToggle(uint8 port){
	
	/**
 * Description: Function is used to toggle the lower nibble of the port.
 * @param port
 */
	switch (port)
	{
		case PORTA :
			PORTA_DATA ^=  (0x0F) ;
			break;
		
		case PORTB :
			PORTB_DATA ^=  (0x0F) ;
			break;
		
		case PORTC :
			PORTC_DATA ^=  (0x0F) ;
			break;
		
		case PORTD :
			PORTD_DATA ^=  (0x0F) ;
			break;
		
		default :
			break;
	}
}


uint8 Ave_gpioLowerNibbleRead(uint8 port){
	
	
/**
 * Description: function is used to read the lower nibble of the port.
 * @param port
 * @return
 */
	switch (port)
	{
		case PORTA :
			return PORTA_PIN & (0x0F) ;
			break;
		
		case PORTB :
			return PORTB_PIN & (0x0F) ;
			break;
		
		case PORTC :
			return PORTC_PIN & (0x0F) ;
			break;
		
		case PORTD :
			return PORTD_PIN & (0x0F) ;
			break;
		
		default :
			return -1;
			break;
	}
	
	
	
	
}
