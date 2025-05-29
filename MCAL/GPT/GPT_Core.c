/*
 * GPT_Core.c
 *
 * Created: 10/20/2023 11:24:21 AM
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
#include "GPT_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint32 TIMER0_Number_OVRflows_g = 0;
uint32 TIMER0_Init_Value_g = 0;
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
void GPT_Init(void)
{
  #if (Timer0_State == TIMER_ENABLE)	
    #if (TIMER0_MODE == NORMAL_MODE)
	 CLR_BIT(TCCR0 , 3);
	 CLR_BIT(TCCR0 , 6);
	  #if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)
	   SET_BIT(TIMSK,0);
	   #elif (TIMER0_INTERRUPT_STATE == INTERRUPT_DISABLED)
	   CLR_BIT(TIMSK,0);	 
	  #endif /*if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)
*/
	 
	#elif (TIMER0_MODE == CTC_MODE)
	
		 #if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)
		 
		 #endif /*if (TIMER0_MODE == NORMAL_MODE)*/
	#endif /*if (TIMER0_MODE == NORMAL_MODE)*/
	
	#if (TIMER0_PRESCALER == CLK_SRC_WITH_NO_PRESCALING	 )
	TCCR0 |= 0X01;
	#elif (TIMER0_PRESCALER == CLK_SRC_PRESCALING_8		 )
	TCCR0 |= 0X02;
	#elif (TIMER0_PRESCALER == CLK_SRC_PRESCALING_64    )
	TCCR0 |= 0X03;
	#elif (TIMER0_PRESCALER == CLK_SRC_PRESCALING_256	)
	TCCR0 |= 0X04;
	#elif (TIMER0_PRESCALER == CLK_SRC_PRESCALING_1024	)
	TCCR0 |= 0X05;
	#endif /*if(TIMER0_PRESCALER == CLK_SRC_WITH_NO_PRESCALING	 )*/
  #endif /*if (Timer0_State == TIMER_ENABLE)*/
  
  #if (Timer1_State == TIMER_ENABLE)
    #if (TIMER1_MODE == NORMAL_MODE) 
	 CLR_BIT(TCCR1A,0); 
	 CLR_BIT(TCCR1A,1);
	 CLR_BIT(TCCR1B,3);
	 CLR_BIT(TCCR1B,4);

  	   	  #if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)
			SET_BIT(TIMSK, 2);   
  	   	  #elif (TIMER0_INTERRUPT_STATE == INTERRUPT_DISABLED)
			CLR_BIT(TIMSK, 2);    
  	   	  #endif /*if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)*/

    #elif (TIMER1_MODE == CTC_MODE)
	 CLR_BIT(TCCR1A,0);
	 CLR_BIT(TCCR1A,1);
	 SET_BIT(TCCR1B,3);
	 CLR_BIT(TCCR1B,4);

	      	  #if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)
			  SET_BIT(TIMSK, 4);  
	      	  #elif (TIMER0_INTERRUPT_STATE == INTERRUPT_DISABLED)
	      	  CLR_BIT(TIMSK, 4);  
	      	  #endif /*if (TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED)*/
    	  #endif /*if (TIMER1_MODE == NORMAL_MODE)*/
  #if (TIMER1_PRESCALER == CLK_SRC_WITH_NO_PRESCALING	 )
  TCCR1B |=0X01;
#elif (TIMER1_PRESCALER == CLK_SRC_PRESCALING_8		 )
TCCR1B |=0X02;
#elif (TIMER1_PRESCALER == CLK_SRC_PRESCALING_64    )
TCCR1B |=0X03;
#elif (TIMER1_PRESCALER == CLK_SRC_PRESCALING_256	)
TCCR1B |=0X04;
#elif (TIMER1_PRESCALER == CLK_SRC_PRESCALING_1024	)
TCCR1B |=0X05;

#endif /*if(TIMER0_PRESCALER == CLK_SRC_WITH_NO_PRESCALING	 )*/
  #endif /*if (Timer1_State == TIMER_ENABLE)*/
	
  #if (Timer2_State == TIMER_ENABLE)
	  
  #endif /*if (Timer2_State == TIMER_ENABLE)*/
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
void GPT_SetTime(void)
{
	uint8 MCU_CLK_us = 16;
	
	#if (Timer0_State == TIMER_ENABLE)
	 uint8 Timer0Tick_Time_us = TIMER0_PRESCALER / MCU_CLK_us;
	 uint32 Time_ms = TIMER0_COUNTED_MS;
	 uint32 Timer0Total_Ticks = (Time_ms*1000) / Timer0Tick_Time_us;
	 TIMER0_Number_OVRflows_g = Timer0Total_Ticks / 256 ;
	 TIMER0_Init_Value_g = 256 -( Timer0Total_Ticks % 256) ;
	 
	 TCNT0 = TIMER0_Init_Value_g ;
	 
	 if(( Timer0Total_Ticks % 256) != 0)
	 {
		TIMER0_Number_OVRflows_g++; 
	 }
	 
	#endif /*if (Timer0_State == TIMER_ENABLE) */
	
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
