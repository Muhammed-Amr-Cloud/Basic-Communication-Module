/*
 * gpio.h
 *
 * Created: 10/21/2019 3:16:53 PM
 *  Author: Mohamed Amr
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#define	PORTA	 (0)
#define PORTB	 (1)
#define PORTC	 (2)
#define PORTD	 (3)

#define INPUT	 (0X00)
#define OUTPUT	 (0xFF)

#include "std_types.h"
/************************************************************************/
/*				 GPIO functions' prototypes	                            */
/************************************************************************/

/*===========================PORT Control===============================*/
/**
 * Description: The function takes the port and the Direction, for initializing the port.
 * 	PORT: are selected with: PORTA, PORTB, PORTC, PORTD
 * 	direction : INPUT, OUTPUT
 * @param port
 * @param direction
 */
void gpioPortDirection(uint8 port, uint8 direction);

/**
 * Description: the function takes the port and the value , to Write in the port
 * PORT: are selected with: PORTA, PORTB, PORTC, PORTD.
 * value: HIGH, LOW
 * @param port
 * @param value
 */
void gpioPortWrite(uint8 port, uint8 value);

/**
 * Description: Function is used to write to the port
 * @param port
 */
void gpioPortToggle(uint8 port);

/**
 * Description: the function is used to Read the port.
 * @param port
 * @return
 */
uint8 gpioPortRead(uint8 port);

/*===========================PIN Control===============================*/
/**
 * Description: Function is used to initialize a pin.
 * The user Should select between PORTA,B,C,D
 * @param port
 * @param pins
 * @param direction : OUTPUT,INPUT
 */
void gpioPinDirection(uint8 port, uint8 pins, uint8 direction);

/**
 * Description: Function is used to write to a single pin
 * @param port : PORTA,B,C,D
 * @param pins
 * @param value : HIGH, LOW
 */
void gpioPinWrite(uint8 port, uint8 pins, uint8 value);

/**
 * Description: Toggle A single pin.
 * @param port : PORTA,B,C,D
 * @param pins : required Pin.
 */
void gpioPinToggle(uint8 port, uint8 pins);

/**
 * Description:  Function is used to read the Pin.
 * @param port
 * @param pin
 * @return
 */
uint8 gpioPinRead(uint8 port, uint8 pin);

/*===========================Upper Nibble Control===============================*/
/**
 * Description: function is used to initialize the upper nibble of the port.
 * @param port
 * @param direction : OUTPUT, INPUT
 */
void gpioUpperNibbleDirection(uint8 port, uint8 direction);

/**
 * Description: Function is Used to Write to the Upper nibble of the port.
 * @param port
 * @param value : High, LOw
 */
void gpioUpperNibbleWrite(uint8 port, uint8 value);

/**
 * Description: Function is used to Toggle the Upper nibble of the port.
 * @param port
 */
void gpioUpperNibbleToggle(uint8 port);

/**
 * Description: function is used to read the upper nibble of the port.
 * @param port
 * @return
 */
uint8 gpioUpperNibbleRead(uint8 port);

/*===========================Lower Nibble Control===============================*/
/**
 * Description: function is used to initialize the lower nibble of the port.
 * @param port
 * @param direction
 */
void gpioLowerNibbleDirection(uint8 port, uint8 direction);

/**
 * Description: function is used to write to the lower nibble of the port.
 * @param port
 * @param value
 */
void gpioLowerNibbleWrite(uint8 port, uint8 value);

/**
 * Description: Function is used to toggle the lower nibble of the port.
 * @param port
 */
void gpioLowerNibbleToggle(uint8 port);

/**
 * Description: function is used to read the lower nibble of the port.
 * @param port
 * @return
 */
uint8 gpioLowerNibbleRead(uint8 port);

#endif /* GPIO_H_ */
