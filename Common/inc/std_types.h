/*
 * IncFile1.h
 *
 * Created: 10/21/2019 3:05:45 PM
 *  Author: AVE-LAP-064
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#define NULL  (void*) (0)

/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/
typedef unsigned char uint8;
typedef unsigned char STATUS;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg_type;
typedef void (*pointer_ToFunciton_t) (void);


/************************************************************************/
/*				 enum for defining bit numbers                          */
/************************************************************************/
typedef enum EN_bits
{
	BIT0 = 0x01,	// defines BIT0 in a register
	BIT1 = 0x02,	// defines BIT1 in a register
	BIT2 = 0x04,	// defines BIT2 in a register
	BIT3 = 0x08,	// defines BIT3 in a register
	BIT4 = 0x10,	// defines BIT4 in a register
	BIT5 = 0x20,	// defines BIT5 in a register
	BIT6 = 0x40,	// defines BIT6 in a register
	BIT7 = 0x80	// defines BIT7 in a register
}EN_bits;

/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0	// defines LOW value for a bit
#define HIGH 1	// defines HIGH value for a bit


/************************************************************************/
/*				 Bits' Manipulation Macros	                            */
/************************************************************************/
#define SET_BIT(reg,bit)	reg|=(1<<bit)
#define CLR_BIT(reg,bit)	reg&=~(1<<bit)
#define READ_BIT(reg,bit)	(reg&(1<<bit))
#define TOGGLE_BIT(reg,bit)	reg^=(1<<bit)



#define OK      1
#define NOT_OK  0

#endif /* INCFILE1_H_ */
