/*
 * BCM.c
 *
 * Created: 11/17/2019 4:48:02 PM
 * Author : Mohamed
 */ 

#include "Uart.h"
#include "BCM.h"
#include "std_types.h"
#include "util/delay.h"
#include "Dio.h"
#define DATA   9

int main(void)
{
			
	uint8 appBuffer[DATA]= {0,0,0,0,0,0,0,0,0};
	BCM_Init();
	gpioPinDirection(PORTA,0x01,OUTPUT);
	BCM_Setup_Receive(appBuffer,DATA);
    while (1) 
    {
		BCM_RxDispatcher();
    }
}

