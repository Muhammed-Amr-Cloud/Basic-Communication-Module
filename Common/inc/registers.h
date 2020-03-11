/*
 * registers.h
 *
 * Created: 10/21/2019 3:26:58 PM
 *  Author: AVE-LAP-064
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_


/*****************************************************************************************
 * 									Register MACROS										 *
 *****************************************************************************************/


/*
 * GPIO Registers Mapping
 */

// PORTA
#define PORTA_DIR    *((reg_type)(0x3A))
#define PORTA_DATA	 *((reg_type)(0x3B))
#define PORTA_PIN	 *((reg_type)(0x39))

// PORTB
#define PORTB_DIR	 *((reg_type)(0x37))
#define PORTB_DATA	 *((reg_type)(0x38))
#define PORTB_PIN	 *((reg_type)(0x36))

// PORTC
#define PORTC_DIR	 *((reg_type)(0x34))
#define PORTC_DATA	 *((reg_type)(0x35))
#define PORTC_PIN	 *((reg_type)(0x33))

// PORTD
#define PORTD_DIR	 *((reg_type)(0x31))
#define PORTD_DATA	 *((reg_type)(0x32))
#define PORTD_PIN	 *((reg_type)(0x30))




/*
 * Timers Register Mapping
 *
 */

#define SREG	 *((reg_type)(0x5F))
#define TIMSK	 *((reg_type)(0x59))

// Timer 0


#define OCR0	 *((reg_type)(0x5C))
#define TIFR	 *((reg_type)(0x58))
#define TCCR0	 *((reg_type)(0x53))
#define TCNT0	 *((reg_type)(0x52))



// Timer 1


#define TCCR1A	 *((reg_type)(0x4F))
#define TCCR1B	 *((reg_type)(0x4E))
#define TCNT1H	 *((reg_type)(0x4D))
#define TCNT1L	 *((reg_type)(0x4C))
#define TCNT1	 *((volatile uint16* const)(0x4C))
#define OCR1AH	 *((reg_type)(0x4B))
#define OCR1AL	 *((reg_type)(0x4A))
#define OCR1	 *((volatile uint16* const)(0x4A))
#define OCR1BH	 *((reg_type)(0x49))
#define OCR1BL	 *((reg_type)(0x48))
#define ICR1H	 *((reg_type)(0x47))
#define ICR1L	 *((reg_type)(0x46))
#define ICR1	 *((volatile uint16* const)(0x46))



// Timer 2



#define TCCR2	 *((reg_type)(0x45))
#define TCNT2	 *((reg_type)(0x44))
#define OCR2	 *((reg_type)(0x43))
#define ASSR	 *((reg_type)(0x42))


// EX interrupts

#define MCUCR	 *((reg_type)(0x55))
#define MCUCSR	 *((reg_type)(0x54))
#define GICR	 *((reg_type)(0x5B))


#define UART_UDR	*((reg_type)(0x2C))
#define UART_UCSRA	*((reg_type)(0x2B))
#define UART_UCSRB	*((reg_type)(0x2A))
#define UART_UBRRL	*((reg_type)(0x29))
#define UART_UBRRH	*((reg_type)(0x40))
#define UART_UCSRC	*((reg_type)(0x40))



#define SPI_SPDR	*((reg_type)(0x2F))	
#define SPI_SPSR	*((reg_type)(0x2E))	
#define SPI_SPCR	*((reg_type)(0x2D))	

#endif /* REGISTERS_H_ */
