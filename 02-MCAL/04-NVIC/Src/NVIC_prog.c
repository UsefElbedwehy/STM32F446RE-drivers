
#include <stdint.h>

#include "ErrType.h"
#include "Stm32F446xx.h"

#include "NVIC_prv.h"
#include "NVIC_interface.h"


/*
@fn NVIC_EnableIRQ
@brief enable interrupts
@param[in] IRQNum
@retval Local_u8ErrorState
 */
uint8_t NVIC_EnableIRQ(IRQn_t Copy_IRQn)
{
	uint8_t Local_u8ErrorState=OK;
	/*calculate Register number*/
	uint8_t RegNum= ( Copy_IRQn / 32);
	/*calculate Bit number*/
	uint8_t BitNum= ( Copy_IRQn % 32);

	if(Copy_IRQn<=FMPI2C1_ERROR)
	{
		/*Enable interrupt*/
		(NVIC->NVIC_ISER[RegNum]) = (1<<BitNum);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

/*
@fn NVIC_DisableIRQ
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState
 */
uint8_t NVIC_DisableIRQ(IRQn_t Copy_IRQn)
{
	uint8_t Local_u8ErrorState=OK;
	/*calculate Register number*/
	uint8_t RegNum= ( Copy_IRQn / 32);
	/*calculate Bit number*/
	uint8_t BitNum= ( Copy_IRQn % 32);

	if(Copy_IRQn<=FMPI2C1_ERROR)
	{
		/*Disable interrupt*/
		(NVIC->NVIC_ICER[RegNum]) = (1<<BitNum);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/*
@fn NVIC_SetPendingFlag
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState
 */
uint8_t NVIC_SetPendingFlag(IRQn_t Copy_IRQn)
{
	uint8_t Local_u8ErrorState=OK;
	/*calculate Register number*/
	uint8_t RegNum= ( Copy_IRQn / 32);
	/*calculate Bit number*/
	uint8_t BitNum= ( Copy_IRQn % 32);

	if(Copy_IRQn<=FMPI2C1_ERROR)
	{
		/*changes interrupt state to pending*/
		(NVIC->NVIC_ISPR[RegNum]) = (1<<BitNum);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/*
@fn NVIC_ClearPendingFlag
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState
 */
uint8_t NVIC_ClearPendingFlag(IRQn_t Copy_IRQn)
{
	uint8_t Local_u8ErrorState=OK;
	/*calculate Register number*/
	uint8_t RegNum= ( Copy_IRQn / 32);
	/*calculate Bit number*/
	uint8_t BitNum= ( Copy_IRQn % 32);

	if(Copy_IRQn<=FMPI2C1_ERROR)
	{
		/*removes pending state an interrupt*/
		(NVIC->NVIC_ICPR[RegNum]) = (1<<BitNum);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/*
@fn NVIC_GetActiveFlag
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState ,*Copy_u8PtrActiveFlag
 */
uint8_t NVIC_GetPendingFlag(IRQn_t Copy_IRQn ,uint8_t* Copy_u8PtrActiveFlag)
{
	uint8_t Local_u8ErrorState=OK;
	/*calculate Register number*/
	uint8_t RegNum= ( Copy_IRQn / 32);
	/*calculate Bit number*/
	uint8_t BitNum= ( Copy_IRQn % 32);

	if(Copy_IRQn<=FMPI2C1_ERROR)
	{
		/*Get pending flag value*/
		*Copy_u8PtrActiveFlag =(((NVIC->NVIC_ISPR[RegNum])>>BitNum) & 0x01);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/*
@fn NVIC_GetActiveFlag
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState , *Copy_u8PtrActiveFlag
 */
uint8_t NVIC_GetActiveFlag(IRQn_t Copy_IRQn ,uint8_t* Copy_u8PtrActiveFlag)
{
	uint8_t Local_u8ErrorState=OK;
	/*calculate Register number*/
	uint8_t RegNum= ( Copy_IRQn / 32);
	/*calculate Bit number*/
	uint8_t BitNum= ( Copy_IRQn % 32);

	if(Copy_IRQn<=FMPI2C1_ERROR)
	{
		/*Get pending flag value*/
		*Copy_u8PtrActiveFlag=(((NVIC->NVIC_IABR[RegNum])>>BitNum) & 0x01);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/*
@fn SCB_SetPriorityGroup
@brief set the priority group
@param[in] Copy_IRQn ,Copy_priority
@retval Local_u8ErrorState
 */
uint8_t	NVIC_SetIRQPriority(IRQn_t Copy_IRQn,uint8_t Copy_priority)
{
	uint8_t Local_u8ErrorState=OK;
	if(Copy_IRQn <= FMPI2C1_ERROR)
	{
		NVIC->NVIC_IPR[Copy_IRQn] &= ~(0xF0);
		NVIC->NVIC_IPR[Copy_IRQn] = (Copy_priority<<4);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
