#include "ErrType.h"
#include "Stm32F446xx.h"

#include "SYSCFG_prv.h"
#include "SCB_interface.h"

/*
@fn SYSCFG_u8SetExtiPort
@brief 	to set the port of the external interrupt
@param[in]	Copy_line (type: enum @Line_t)  , Copy_port (type: enum @PORTx_t)
@retval    Copy_u8ErrorState
*/
uint8_t SYSCFG_u8SetExtiPort(Line_t Copy_line,PORTx_t Copy_port)
{
	uint8_t Copy_u8ErrorState=OK;
	if((Copy_line<=LINE15) && (Copy_line>=LINE0) && (Copy_port<=PORT_H) && (Copy_port>=PORT_A))
	{
		uint8_t RegNum  = Copy_line / 4 ;
		uint8_t BitsNum = (Copy_line % 4) * 4 ;
		SYSCFG->SYSCFG_EXTICR[RegNum] |= (Copy_port<<BitsNum);
	}
	else
	{
		Copy_u8ErrorState=NOK;
	}
	return Copy_u8ErrorState;
}
