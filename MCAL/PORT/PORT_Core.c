/*
 * PORT_Core.c
 *
 * Created: 9/16/2023 12:06:21 PM
 *  Author: Eyad
 */ 
#include "PORT_Core.h"


void PORT_Init(void)
{
	uint8 Cnt = 0 , Port = 0 , PIN = 0 , DIR = 0;
	
	for(Cnt = 0 ; Cnt < DEFINED_PINS ; Cnt++)
	{
		Port = PORT_Intialization[Cnt].PIN_NUM / NUMBER_OF_PORT_PINS ;
		PIN = PORT_Intialization[Cnt].PIN_NUM % NUMBER_OF_PORT_PINS ;
		DIR = PORT_Intialization[Cnt].DIR ;
		
		switch(DIR)
		{
			case PIN_DIR_OUTPUT :
			 switch(Port)
			 {
				 case 0 :
				   SET_BIT(DDRA , PIN);
				 break;
				 case 1 :
				  SET_BIT(DDRB , PIN);
				 break;
				 case 2 :
				  SET_BIT(DDRC , PIN);
				 break;
				 case 3 :
				  SET_BIT(DDRD , PIN);
				 break;
			 }
			
			break;
			
			case PIN_DIR_INPUT :
			  switch(Port)
			  {
				 case 0 :
				 CLR_BIT(DDRA , PIN);
				 break;
				 case 1 :
				 CLR_BIT(DDRB , PIN);
				 break;
				 case 2 :
				 CLR_BIT(DDRC , PIN);
				 break;
				 case 3 :
				 CLR_BIT(DDRD , PIN);
				 break;
			  }
			break;
			
			default:
			break;
		}
	}
}