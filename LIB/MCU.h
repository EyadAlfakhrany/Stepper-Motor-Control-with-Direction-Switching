/*
   MCU.h
 *
 * Created: 9/15/2023 10:08:20 AM
 *  Author: Eyad
 */ 


#ifndef MCU_H_
#define MCU_H_

#include "STD.h"


/*********************** GPIO Registers ******************/
#define  PINA   *(volatile uint8*)(0x39 )
#define  DDRA   *(volatile uint8*)(0x3A )
#define  PORTA  *(volatile uint8*)(0x3B )

#define  PINB   *(volatile uint8*)(0x36 )
#define  DDRB   *(volatile uint8*)(0x37 )
#define  PORTB  *(volatile uint8*)(0x38 )

#define  PINC   *(volatile uint8*)(0x33 )
#define  DDRC   *(volatile uint8*)(0x34 )
#define  PORTC  *(volatile uint8*)(0x35 )

#define  PIND   *(volatile uint8*)(0x30 )
#define  DDRD   *(volatile uint8*)(0x31 )
#define  PORTD  *(volatile uint8*)(0x32 )
/*********************************************************/
/*************************************** EXTERNAL INT Registers ****************************************/
#define  SREG   (*(volatile uint8*)(0X5F))
#define  GICR   (*(volatile uint8*)(0X5B))
#define  MCUCR  (*(volatile uint8*)(0X55))
#define  MCUCSR (*(volatile uint8*)(0X54))
/*******************************************************************************************************/
/*************************************** ADC Registers ************************************************/
#define ADMUX                      (*(volatile uint8 *)(0x27))
#define ADCSRA                     (*(volatile uint8 *)(0x26))
#define ADCH                       (*(volatile uint8 *)(0x25))
#define ADCL                       (*(volatile uint8 *)(0x24))
#define ADC_INPUT_16BIT_ACCESS     (*(volatile uint16*)(0x24))
#define SFIOR                      (*(volatile uint8 *)(0x50))
#define WDTCR                      (*(volatile uint8 *)(0x41))
/*******************************************************************************************************/
/*******************************  Timer0  ***********************************************************************/

#define TCNT0  (*(volatile uint8*)(0x52))
#define TCCR0  (*(volatile uint8*)(0x53))
#define OCR0   (*(volatile uint8*)(0x5C))
#define TIMSK  (*(volatile uint8*)(0x59))
/***************************************timer1****************************************************************/
#define TCCR1A  (*(volatile uint8*)(0x4F))
#define TCCR1B  (*(volatile uint8*)(0x4E))
#define ICR1H (*(volatile uint16 *)(0x47))
#define ICR1L (*(volatile uint16 *)(0x46))
#define ICR1 (*(volatile uint16 *)(0x46))
/**************************************UART*******************************************************************/

#define UBRRH   (*((volatile uint8*)0x40))#define UBRRL   (*((volatile uint8*)0x29))#define UCSRA   (*((volatile uint8*)0x2B))#define UCSRB   (*((volatile uint8*)0x2A))#define UCSRC   (*((volatile uint8*)0x40))#define UDR     (*((volatile uint8*)0x2C))





#endif /* MCU_H_ */