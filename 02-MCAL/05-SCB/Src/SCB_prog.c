#include <stdint.h>

#include "Stm32F446xx.h"
#include "ErrType.h"

#include "SCB_prv.h"
#include "SCB_interface.h"

/*
@fn SCB_SetPriorityGroup
@brief set the priority group
@param[in] Copy_PRIOGroup
@retval Local_u8ErrorState
 */
uint8_t SCB_SetPriorityGroup(PRIOGroup_t Copy_PRIOGroup)
{
	uint8_t Local_u8ErrorState=OK;

	if((Copy_PRIOGroup >= _16G_0SG) && (Copy_PRIOGroup <= _0G_16SG))
	{
		SCB->SCB_AIRCR &= (VECTKEY<< VECTKEY_BIT);
		SCB->SCB_AIRCR = ((VECTKEY<< VECTKEY_BIT) | (Copy_PRIOGroup << PRIOGROUP_BIT)) ;
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
