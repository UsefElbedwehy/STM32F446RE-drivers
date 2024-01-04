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


/*
@fn SCB_u8EnableMemMangeFaultEx
@brief Enable Memory Management Fault Exception
@param[in] void
@retval void
 */
void SCB_u8EnableMemMangeFaultEx(void)
{
	SCB->SCB_SHCRS |= (1<<MEMFAULTENA);
}
/*
@fn SCB_u8DisableMemMangeFaultEx
@brief Disable Memory Management Fault Exception
@param[in] void
@retval void
 */
void SCB_u8DisableMemMangeFaultEx(void)
{
	SCB->SCB_SHCRS &=~ (1<<MEMFAULTENA);
}

/*
@fn SCB_u8EnableBusFaultEx
@brief Enable Bus Fault Exception
@param[in] void
@retval Local_u8voidErrorState
 */
void SCB_u8EnableBusFaultEx(void)
{
	SCB->SCB_SHCRS |= (1<<BUSFAULTENA);
}
/*
@fn SCB_u8DisableBusFaultEx
@brief Disable Bus Fault Exception
@param[in] void
@retval void
 */
void SCB_u8DisableBusFaultEx(void)
{
	SCB->SCB_SHCRS &=~ (1<<BUSFAULTENA);
}

/*
@fn SCB_u8EnableUsageFaultEx
@brief Enable Usage Fault Exception
@param[in] void
@retval void
 */
void SCB_u8EnableUsageFaultEx(void)
{
	SCB->SCB_SHCRS |= (1<<USGFAULTENA);
}
/*
@fn SCB_u8DisableUsageFaultEx
@brief Disable Usage Fault Exception
@param[in] void
@retval void
 */
void SCB_u8DisableUsageFaultEx(void)
{
	SCB->SCB_SHCRS &=~ (1<<USGFAULTENA);
}

/*
@fn SCB_u8EnableDivByZero
@brief Enable the Division by zero Exception
@param[in] void
@retval void
 */
void SCB_u8EnableDivByZero(void)
{
	SCB->SCB_UFSR |= (1 << DIVBYZERO);
}
/*
@fn SCB_u8DisableUsageFaultEx
@brief Disable the Division by zero Exception
@param[in] void
@retval void
 */
void SCB_u8DisableDivByZero(void)
{
	SCB->SCB_UFSR &=~ (1 << DIVBYZERO);
}

/*
@fn SCB_u8SetSysHandlerCtrlSts
@brief Set system handler control and status registers
@param[in] Copy_SHCSR_Reg (type: @SHCSR_Reg_t)
@retval Local_u8ErrorState
 */
uint8_t SCB_u8SetSysHandlerCtrlSts(SHCSR_Reg_t Copy_SHCSR_Reg)
{
	uint8_t Local_u8ErrorState=OK;

	if(( Copy_SHCSR_Reg >= MEMFAULTACT ) && (Copy_SHCSR_Reg <= USGFAULTENA))
	{
		SCB->SCB_SHCRS |= (1 << Copy_SHCSR_Reg);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
/*
@fn SCB_u8ClrSysHandlerCtrlSts
@brief Clear system handler control and status registers
@param[in] Copy_SHCSR_Reg (type: @SHCSR_Reg_t)
@retval Local_u8ErrorState
 */
uint8_t SCB_u8ClrSysHandlerCtrlSts(SHCSR_Reg_t Copy_SHCSR_Reg)
{
	uint8_t Local_u8ErrorState=OK;

	if(( Copy_SHCSR_Reg >= MEMFAULTACT ) && (Copy_SHCSR_Reg <= USGFAULTENA))
	{
		SCB->SCB_SHCRS &=~ (1 << Copy_SHCSR_Reg);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

