/*
 * PWM_Core.c
 *
 * Created: 10/24/2023 8:51:01 PM
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
#include "PWM_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

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
void PWM_Init(void)
{
	#if (PWM0_STATE ==  PWM_ENABLE)
	 #if (PWM0_TYPE ==  PWM_FAST)
	  SET_BIT(TCCR0 , 3);
	  SET_BIT(TCCR0 , 6);
	 #elif (PWM0_TYPE ==  PWM_PHASE_CORRECT)
	  CLR_BIT(TCCR0 , 3);
	  SET_BIT(TCCR0 , 6);	 
	 #endif /*(PWM0_TYPE ==  PWM_FAST)*/
	 
	 #if (PWM0_MODE ==  PWM_NONINVERTED)
	  CLR_BIT(TCCR0 , 4);
	  SET_BIT(TCCR0 , 5);
	 #elif (PWM0_MODE ==  PWM_INVERTED)
	  SET_BIT(TCCR0 , 4);
	  SET_BIT(TCCR0 , 5);
	 #endif /*if (PWM0_MODE ==  PWM_NONINVERTED)*/
	#endif /*if (PWM0_STATE ==  PWM_ENABLE)*/
		#if (PWM1_STATE ==  PWM_ENABLE)
    	TCCR1A |=0X02;
	    TCCR1B |=0X18;
	    TCCR1A |=0X80;

		 #endif /*if (PWM1_MODE == PWM_ENABEL)*/
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
void PWM0_Generate(uint8 Duty_Cycle)
{
	#if (PWM0_STATE ==  PWM_ENABLE)
	 #if (PWM0_TYPE  == PWM_FAST)
	 
	  #if (PWM0_MODE  == PWM_NONINVERTED)
	    OCR0 = ((Duty_Cycle * 256) / 100) - 1;
	  #elif (PWM0_MODE  == PWM_INVERTED)
	    OCR0 = 255 - ((Duty_Cycle * 256) / 100) ; 
	  #endif /*if (PWM0_MODE  == PWM_NONINVERTED)*/
	  
	 #elif (PWM0_TYPE  == PWM_PHASE_CORRECT)
	 
	   #if (PWM0_MODE  == PWM_NONINVERTED)
	   OCR0 = ((Duty_Cycle * 255) / 100);
	   #elif (PWM0_MODE  == PWM_INVERTED)
	   OCR0 = 255 - ((Duty_Cycle * 255) / 100) ;
	   #endif /*if (PWM0_MODE  == PWM_NONINVERTED)*/
	   
	 #endif /*if (PWM0_TYPE  == PWM_FAST)*/
	 
	 #if (PWM0_PRESC ==  PWM_PRESC8)
	  TCCR0 |= 0X02;
	 #elif (PWM0_PRESC ==  PWM_PRESC64)
	  TCCR0 |= 0X03;
	 #elif (PWM0_PRESC ==  PWM_PRESC256)
	  TCCR0 |= 0X04;
	 #elif (PWM0_PRESC ==  PWM_PRESC1024)
	  TCCR0 |= 0X05;
	 #endif /*if (PWM0_PRESC ==  PWM_PRESC8)*/
	#endif /*if (PWM0_STATE ==  PWM_ENABLE)*/
} 
/*void PWM0_Generate(uint8 Frequency , uint8 Duty_Cycle)
{
	ICR1_16BIT_access+ (16000000 /(Frequency *PWM1_PRESC));
	OCR1A_16BIT_ACCESS + ((Duty_Cycle *(ICR1_16BIT_ACCESS+1))/100)-1;
	TCCR1B |=0X05;
}*/
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
