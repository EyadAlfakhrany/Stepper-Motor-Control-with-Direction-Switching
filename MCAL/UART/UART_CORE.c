/*
 * UART_CORE.c
 *
 * Created: 11/15/2023 8:37:19 PM
 *  Author: eiadA
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
#include "UART_CORE.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 UART_TRASMITE_DATA[TX_BUFFER_SIZE];
uint8 UART_RECEIVED_DATA[7];
uint8 TX_STATUS_FLAG =0;
uint8 TX_Cnt =0;
uint8 RX_STATUS_FLAG =0;
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
void UART_Init(void)
{
	uint8 BaudRate_Value_1 =0;
	
	
	#if ( UART_PARiTY_STATE == ENABLE )
	
	  #if (UART_PARiTY_TYPE  == PARITY_ODD)
	  UCSRC |= 0xD0 ; 
	  #elif (UART_PARiTY_TYPE  == PARITY_EVEN)
	  UCSRC |= 0xA0 ; 
	  #endif  /*#if (UART_PARiTY_TYPE  == PARITY_ODD)*/
	  
	#endif /*#if ( UART_PARiTY_STATE == DISABLE )*/
	
	#if ( UART_DATA_BYTES == UART_DATA_BYTES_5 )
	UCSRC |=0x80;
	#elif ( UART_DATA_BYTES == UART_DATA_BYTES_6 )
	UCSRC |=0x82;
	#elif ( UART_DATA_BYTES == UART_DATA_BYTES_7 )  
	UCSRC |=0x84;
	#elif ( UART_DATA_BYTES == UART_DATA_BYTES_8 )
	UCSRC |=0x86;
	#endif  /*#if ( UART_DATA_BYTES == UART_DATA_BYTES_5 )*/
	
	#if (UART_INTERRUPT  ==  ENABLE)
	SET_BIT(UCSRB,7);  /*RX INT*/
	SET_BIT(UCSRB,6);  /*TX INT*/

	#elif (UART_INTERRUPT  ==  DISABLE)
    CLR_BIT(UCSRB,7); /*RX INT*/
    CLR_BIT(UCSRB,6);  /*TX INT*/
	
	#endif /*#if (UART_INTERRUPT  ==  ENABLE)*/
	/* Enable RX */
	SET_BIT(UCSRC , 3);
	/* Enable TX */
	SET_BIT(UCSRC , 4);
	/*BaudRate Equation*/
    BaudRate_Value_1 =((16000000U)/(UART_BAUD_RATE *16)) -1 ;
    
	UBRRL=BaudRate_Value_1;
}


void UART_InitTX(void)
{
	/*Enable TX INT*/
	SET_BIT(UCSRB , 6);
	TX_STATUS_FLAG = 1;
}
void UART_SendData(void)
{

 if(TX_Cnt == TX_BUFFER_SIZE)
 {
	TX_Cnt =0;
	TX_STATUS_FLAG=0;
	CLR_BIT(UCSRB , 6);
 }
 if(TX_STATUS_FLAG ==1)	
 {
	UDR = UART_TRASMITE_DATA[TX_Cnt];
	TX_STATUS_FLAG =0;
 }
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
