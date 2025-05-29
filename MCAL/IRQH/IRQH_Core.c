/*
 * IRQH_Core.c
 *
 * Created: 10/7/2023 10:33:17 AM
 *  Author: Eyad
 */ 
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IRQH_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define  NULL     (void*)(0)
void(*ptr)(void) = NULL;
void(*GPT_ptr)(void) = NULL;

extern uint32 ADC_Vin_Value_mv;

extern uint32 TIMER0_Number_OVRflows_g ;
extern uint32 TIMER0_Init_Value_g ;

 uint32 TIMER1_Number_OVRflows_g ;


extern volatile uint32 Capture_Readings_1_g;
extern volatile uint32 Capture_Readings_2_g;
extern volatile uint32 Capture_Flag_g;


extern  uint8 TX_STATUS_FLAG ;
extern  uint8 TX_Cnt ;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void IRQH_SetGlobalInterrupts(uint8 G_INT_State)
{
	switch(G_INT_State)
	{
		case INTERRUPT_ENABLE :
		SET_BIT(SREG , 7);
		break;
		case INTERRUPT_DISABLE :
		CLR_BIT(SREG,7);
		break;
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void IRQH_SetExternalInterrupts(void)
{
#if    (EXT_INT0_STATE == INTERRUPT_ENABLE)
 SET_BIT(GICR , 6);
 
    #if   (EXT_INT0_TRIGGER == RISING_EDGE_TRIGGER)
     SET_BIT(MCUCR , 0);
     SET_BIT(MCUCR , 1);    
    #elif (EXT_INT0_TRIGGER == FALLING_EDGE_TRIGGER)
     CLR_BIT(MCUCR , 0);
     SET_BIT(MCUCR , 1);    
    #elif (EXT_INT0_TRIGGER == LOW_LEVEL_TRIGGER)
     CLR_BIT(MCUCR , 0);
	 CLR_BIT(MCUCR , 1);
    #elif (EXT_INT0_TRIGGER == ANY_LOGICAL_CHANGE_TRIGGER)
     SET_BIT(MCUCR , 0);
     CLR_BIT(MCUCR , 1); 
    #endif /*if  (EXT_INT0_TRIGGER == RISING_EDGE_TRIGGER) */
 
#elif  (EXT_INT1_STATE == INTERRUPT_ENABLE)
 SET_BIT(GICR , 7);
 
    #if   (EXT_INT0_TRIGGER == RISING_EDGE_TRIGGER)
    SET_BIT(MCUCR , 2);
    SET_BIT(MCUCR , 3);
    #elif (EXT_INT0_TRIGGER == FALLING_EDGE_TRIGGER)
    CLR_BIT(MCUCR , 2);
    SET_BIT(MCUCR , 3);
    #elif (EXT_INT0_TRIGGER == LOW_LEVEL_TRIGGER)
    CLR_BIT(MCUCR , 2);
    CLR_BIT(MCUCR , 3);
    #elif (EXT_INT0_TRIGGER == ANY_LOGICAL_CHANGE_TRIGGER)
    SET_BIT(MCUCR , 2);
    CLR_BIT(MCUCR , 3);
    #endif /*if  (EXT_INT1_TRIGGER == RISING_EDGE_TRIGGER) */
	
#elif  (EXT_INT2_STATE == INTERRUPT_ENABLE)
 SET_BIT(GICR , 5);
 
    #if   (EXT_INT0_TRIGGER == RISING_EDGE_TRIGGER)
    SET_BIT(MCUCSR , 6);
    #elif (EXT_INT0_TRIGGER == FALLING_EDGE_TRIGGER)
    CLR_BIT(MCUCSR , 6);
	#endif /*if  (EXT_IN2_TRIGGER == RISING_EDGE_TRIGGER) */
	
#endif /*if (EXT_INT0_STATE == INTERRUPT_ENABLE)*/
}

void IRQH_SetCallBack(void(*p)(void))
{
	ptr = p;
}

ISR(INT0_vect)
{
	(*ptr)();
}

ISR(ADC_vect)
{


	
}

ISR(TIMER0_OVF_vect)
{
	static uint8 OVF_INT_CNT = 0;
	OVF_INT_CNT++;
	
	if(OVF_INT_CNT == TIMER0_Number_OVRflows_g)
	{
		(*ptr)();
		OVF_INT_CNT = 0;
		TCNT0 = TIMER0_Init_Value_g ;
	}
}
ISR(TIMER1_COMPA_vect)
{
	(*ptr)();
}
ISR(TIMER1_OVF_vect)
{
TIMER1_Number_OVRflows_g+=1;	
}

ISR(TIMER1_CAPT_vect)
{
	
	Capture_Flag_g++;
	if(Capture_Flag_g ==1)
	{
		
		Capture_Readings_1_g   = ICR1;
		TIMER1_Number_OVRflows_g=0;
		//detect falling edge
		CLR_BIT(TCCR1B,6);
	}
	else if (Capture_Flag_g ==2)
	{
	
		Capture_Readings_2_g= ICR1 + (TIMER1_Number_OVRflows_g * 65536);
		//detect rising edge
		TCCR1B |=0x40;
		/*Disable ICU Interrupt*/
	//	CLR_BIT(TIMSK,5); 
        

		
	}
}
ISR(USART_TXC_vect)
{
	TX_Cnt++;
	TX_STATUS_FLAG =1;
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
