/*
 * Button_Core.c
 *
 * Created: 9/15/2023 10:06:59 AM
 *  Author: Eyad
 */ 

#include "Button_Core.h"

void Button_Init(void)
{
	CLR_BIT(DDRD , 2);
}

uint8 Button_GetValue(void)
{
	uint8 Button = 1 ;
	uint8 Temp = 0;
	
	Button = GET_BIT(PIND , 2);
	
	while(Temp == 0)
	{
		Temp = GET_BIT(PIND , 2);
	}
	
	_delay_ms(200);
	
	return Button;
}