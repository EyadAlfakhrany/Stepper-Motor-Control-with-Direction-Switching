/*
 * First LED Lab.c
 *
 * Created: 9/9/2023 1:43:45 PM
 * Author : Eyad
 */ 


#include "LED_Core.h"
#include "Button_Core.h"
#include "SevSeg_Core.h"
#include "PORT_Core.h"
#include "DIO_Core.h"
#include "LCD_Core.h"
#include "KeyPad_Core.h"
#include "IRQH_Core.h"
#include "ADC_Core.h"
#include "GPT_Core.h"
#include "PWM_Core.h"
#include "DcMotor_Core.h"
#include "WDT.h"
#include "STEPMOTOR_CORE.h"
extern uint32 ADC_Vin_Value_mv ;

int main (void)
{
	
	PORT_Init();
	while(1)
	{
	STEPMOTOR(COUNTER_CLOCK_WISE);
	STEPMOTOR(CLOCK_WISE);
	LED_ON();
	}
}

