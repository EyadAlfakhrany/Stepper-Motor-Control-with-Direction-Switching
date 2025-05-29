/*
 * DIO_Core.c
 *
 * Created: 9/22/2023 11:09:42 AM
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
#include "DIO_Core.h"

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
void DIO_WriteChannel(uint8 Pin_Num , PIN_VAL_e Pin_value )
{
	uint8 Port = 0 , Pin = 0;
	
	Port = Pin_Num / NUMBER_OF_PORT_PINS ;
	Pin  = Pin_Num % NUMBER_OF_PORT_PINS ;
	
	switch(Pin_value)
	{
		case PIN_HIGH :
		switch(Port)
		{
			case 0 :
			SET_BIT(PORTA , Pin);
			break;
			case 1 :
			SET_BIT(PORTB , Pin);
			break;
			case 2 :
			SET_BIT(PORTC , Pin);
			break;
			case 3 :
			SET_BIT(PORTD , Pin);
			break;
		}
		break;
		
		case PIN_LOW:
		switch(Port)
		{
			case 0 :
			CLR_BIT(PORTA , Pin);
			break;
			case 1 :
			CLR_BIT(PORTB , Pin);
			break;
			case 2 :
			CLR_BIT(PORTC , Pin);
			break;
			case 3 :
			CLR_BIT(PORTD , Pin);
			break;
		}		
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
PIN_VAL_e DIO_ReadChannel(uint8 Pin_Num )
{
	uint8 Port = 0 , Pin = 0 , Output_Val = 0;
	Port = Pin_Num / NUMBER_OF_PORT_PINS ;
	Pin  = Pin_Num % NUMBER_OF_PORT_PINS ;
	
	switch(Port)
	{
		case 0:
		 Output_Val = GET_BIT(PINA , Pin);
		break;
		case 1:
		Output_Val = GET_BIT(PINB , Pin);
		break;
		case 2:
		Output_Val = GET_BIT(PINC , Pin);
		break;
		case 3:
		Output_Val = GET_BIT(PIND , Pin);
		break;		
	}
	
	return Output_Val;
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
void DIO_FlipChannel(uint8 Pin_Num)
{
	uint8 Port = 0 , Pin = 0 ;
	Port = Pin_Num / NUMBER_OF_PORT_PINS ;
	Pin  = Pin_Num % NUMBER_OF_PORT_PINS ;
	
		switch(Port)
		{
			case 0:
			 TOGGLE_BIT(PORTA , Pin);
			break;
			case 1:
			 TOGGLE_BIT(PORTA , Pin);
			break;
			case 2:
			 TOGGLE_BIT(PORTA , Pin);
			break;
			case 3:
			 TOGGLE_BIT(PORTA , Pin);
			break;
		}
	
}
void DIO_WritePort(uint8 Pin_Num , uint8 Port_Val)
{
	uint8 Port = 0;
	Port = Pin_Num / NUMBER_OF_PORT_PINS ;
	
	
	switch(Port)
	{
		case 0:
		PORTA = Port_Val;
		break;
		case 1:
		PORTB = Port_Val;
		break;
		case 2:
		PORTC = Port_Val;
		break;
		case 3:
		PORTD = Port_Val;
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
uint8 DIO_ReadPort(uint8 Pin_Num  )
{
	uint8 Port = 0 ,Output_Value = 0;
	Port = Pin_Num / NUMBER_OF_PORT_PINS ;
	
	
	switch(Port)
	{
		case 0:
		Output_Value = PINA;
		break;
		case 1:
		Output_Value = PINB;
		break;
		case 2:
		Output_Value = PINC;
		break;
		case 3:
		Output_Value = PIND;
		break;
	}
	return Output_Value ;
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
