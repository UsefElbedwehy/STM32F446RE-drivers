/* * * * * * * * * * * * * * * * * * * * * * * * *
 * @file  : EXTI_prog.c
 * @Author: Usef_Elbedwehy
 * @Layer:  MCAL
 * @Driver:	EXTI
 * @Family: Cortex-M4 (Stm32F446)
 * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
#include "ErrType.h"
#include "Stm32F446xx.h"

#include "EXTI_prv.h"
#include "EXTI_interface.h"

/* * * Global array of functions to store ISR Function address * * * * * * * * */
void (*EXTI_pvIntCallBack[LINES_NUMBER])(void)={NULL};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * @fn EXTI_u8Init
 * @brief initialize the external interrupt setting
 * @param[in] Copy_Config (type: pointer to struct)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_u8Init(const EXTI_Config_t* Copy_Config)
{
	uint8_t local_u8ErrorState=OK;
	if(Copy_Config!=NULL)
	{
		if((EXTI_LINE<=EXTI_22) && (EXTI_LINE>=EXTI_0) &&
				(TriggerState<=RISING_FALLING) && (TriggerState>=RISING) &&
				(EnableState<=DISABLE) && (EnableState>=ENABLE) && ((*CallBackFunc)!=NULL) )
		{
			/* * * * *     Trigger selection   * * * * */
			switch(Copy_Config->TriggerState)
			{
			case RISING :
				EXTI_voidDisableFallingTrigger(Copy_Config->EXTI_LINE);
				EXTI_voidEnableRisingTrigger(Copy_Config->EXTI_LINE);
				break;
			case FALLING :
				EXTI_voidDisableRisingTrigger(Copy_Config->EXTI_LINE);
				EXTI_voidEnableFallingTrigger(Copy_Config->EXTI_LINE);
				break;
			case RISING_FALLING :
				EXTI_voidEnableRisingTrigger(Copy_Config->EXTI_LINE);
				EXTI_voidEnableFallingTrigger(Copy_Config->EXTI_LINE);
				break;
			default : local_u8ErrorState=NOK;
			break;
			}
			/* * * * * Initialize CallBack Function * * * * */
			EXTI_pvIntCallBack[Copy_Config->EXTI_LINE] = Copy_Config->CallBackFunc;
			/* * * * *     Initialize Int Status    * * * * */
			/*clear bit*/
			EXTI->EXTI_IMR &=~ (1<<Copy_Config->EXTI_LINE);
			/*set the bit with the int status*/
			EXTI->EXTI_IMR &=~ ((Copy_Config->EnableState) << (Copy_Config->EXTI_LINE));
		}
		else
		{
			local_u8ErrorState=NOK;
		}
	}
	else
	{
		local_u8ErrorState=NULL_POINTER;
	}
	return local_u8ErrorState;
}

/* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ */
/* ^ ^ ^ ^ Trigger selection functions ^ ^ ^ ^ ^ ^ */

/*
 * @fn EXTI_voidEnableRisingTrigger
 * @brief Enable rising trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidEnableRisingTrigger(EXTI_LINE_t Copy_LINE)
{
	/*Enable Rising trigger*/
	EXTI->EXTI_RTSR |= (1<<Copy_LINE);
}

/*
 * @fn EXTI_voidDisableRisingTrigger
 * @brief Disable rising trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidDisableRisingTrigger(EXTI_LINE_t Copy_LINE)
{
	/*Disable Rising trigger*/
	EXTI->EXTI_RTSR &=~ (1<<Copy_LINE);
}

/*
 * @fn EXTI_voidEnableFallingTrigger
 * @brief Enable falling trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidEnableFallingTrigger(EXTI_LINE_t Copy_LINE)
{
	/*Enable Falling trigger*/
	EXTI->EXTI_FTSR |= (1<<Copy_LINE);
}

/*
 * @fn EXTI_voidDisableFallingTrigger
 * @brief Disable falling trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidDisableFallingTrigger(EXTI_LINE_t Copy_LINE)
{
	/*Disable Falling trigger*/
	EXTI->EXTI_FTSR &=~ (1<<Copy_LINE);
}
/* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ */

/*
 * @fn EXTI_voidClearPendingFlag
 * @brief is to clear pending flag (This bit is cleared by programming it to ‘1’)
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_ClearPendingFlag(EXTI_LINE_t Copy_LINE)
{
	uint8_t Copy_u8ErrorState=OK;
	if((Copy_LINE<=EXTI_22) && (Copy_LINE>=EXTI_0))
	{
		EXTI->EXTI_PR |= (1<<Copy_LINE);
	}
	else
	{
		Copy_u8ErrorState=NOK;
	}
	return Copy_u8ErrorState;
}

/*
 * @fn EXTI_voidReadPendingFlag
 * @brief is to Get pending flag
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t) , Copy_u8PendingFlagVal (type: pointer uint8_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_ReadPendingFlag(EXTI_LINE_t Copy_LINE,uint8_t* Copy_u8PendingFlagVal)
{
	uint8_t Copy_u8ErrorState=OK;
	if((Copy_LINE<=EXTI_22) && (Copy_LINE>=EXTI_0))
	{
		*Copy_u8PendingFlagVal = ( ( EXTI->EXTI_PR >> Copy_LINE )&0x01 );
	}
	else
	{
		Copy_u8ErrorState=NOK;
	}
	return Copy_u8ErrorState;
}

/*
 * @fn EXTI_EnableInt
 * @brief is to Enable Interrupt
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_EnableInt(EXTI_LINE_t Copy_LINE)
{
	uint8_t Copy_u8ErrorState=OK;

	if((Copy_LINE<=EXTI_22) && (Copy_LINE>=EXTI_0))
	{
		/* * * * * Interrupt request from line x is not masked * * * * */
		EXTI->EXTI_IMR |= (1<<(Copy_LINE));
	}
	else
	{
		Copy_u8ErrorState=NOK;
	}
	return Copy_u8ErrorState;
}

/*
 * @fn EXTI_EnableInt
 * @brief is to Disable Interrupt
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_DisableInt(EXTI_LINE_t Copy_LINE)
{
	uint8_t Copy_u8ErrorState=OK;

	if((Copy_LINE<=EXTI_22) && (Copy_LINE>=EXTI_0))
	{
		/* * * * * Interrupt request from line x is masked * * * * */
		EXTI->EXTI_IMR &=~ (1<<(Copy_LINE));
	}
	else
	{
		Copy_u8ErrorState=NOK;
	}
	return Copy_u8ErrorState;
}


/* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ */
/* ^ ^ ^ ^ ^ IRQn Handlers ^ ^ ^ ^ ^ */
void EXTI0_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_0);

	EXTI_pvIntCallBack[EXTI_0]();

}

void EXTI1_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_1);

	EXTI_pvIntCallBack[EXTI_1]();

}

void EXTI2_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_2);

	EXTI_pvIntCallBack[EXTI_2]();

}

void EXTI3_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_3);

	EXTI_pvIntCallBack[EXTI_3]();

}

void EXTI4_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_4);

	EXTI_pvIntCallBack[EXTI_4]();

}

void EXTI9_5_IRQHandler(void)
{

	if(( ( EXTI->EXTI_PR >> EXTI_5 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_5);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_5] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_5]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_6 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_6);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_6] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_6]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_7 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_7);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_7] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_7]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_8 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_8);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_8] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_8]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_9 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_9);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_9] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_9]();
		}
	}

}

void EXTI15_10_IRQHandler(void)
{

	if(( ( EXTI->EXTI_PR >> EXTI_10 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_10);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_10] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_10]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_11EXTI_11 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_11);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_11] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_11]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_12 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_12);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_12] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_12]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_13 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_13);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_13] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_13]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_14 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_14);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_14] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_14]();
		}
	}
	else if(( ( EXTI->EXTI_PR >> EXTI_15 )&0x01 )==PENDING)
	{
		/*Clear Int pending flag*/
		EXTI_voidClearPendingFlag(EXTI_15);

		/*Call global function for notification*/
		if(	EXTI_pvIntCallBack[EXTI_15] != NULL)
		{
			EXTI_pvIntCallBack[EXTI_15]();
		}
	}

}

/* EXTI line 16 Handler which is connected to the PVD output */
void PVD_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_16);

	/*Call global function for notification*/
	if(	EXTI_pvIntCallBack[EXTI_16] != NULL)
	{
		EXTI_pvIntCallBack[EXTI_16]();
	}

}

/* EXTI line 17 Handler which is connected to the RTC Alarm event */
void RTC_Alarm_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_17);

	/*Call global function for notification*/
	if(	EXTI_pvIntCallBack[EXTI_17] != NULL)
	{
		EXTI_pvIntCallBack[EXTI_17]();
	}

}

/* EXTI line 18 Handler which is connected to the USB OTG FS Wakeup event */
void OTG_FS_WKUP_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_18);

	/*Call global function for notification*/
	if(	EXTI_pvIntCallBack[EXTI_18] != NULL)
	{
		EXTI_pvIntCallBack[EXTI_18]();
	}

}

/* EXTI line 20 Handler which is connected to the USB OTG HS (configured in FS) Wakeup event */
void OTG_HS_WKUP_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_20);

	/*Call global function for notification*/
	if(	EXTI_pvIntCallBack[EXTI_20] != NULL)
	{
		EXTI_pvIntCallBack[EXTI_20]();
	}

}

/* EXTI line 21 Handler which is connected to the RTC Tamper and TimeStamp events */
void TAMP_STAMP_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_21);

	/*Call global function for notification*/
	if(	EXTI_pvIntCallBack[EXTI_21] != NULL)
	{
		EXTI_pvIntCallBack[EXTI_21]();
	}

}

/* EXTI line 22 Handler which is connected to the RTC Wakeup event */
void RTC_WKUP_IRQHandler(void)
{
	/*Clear Int pending flag*/
	EXTI_voidClearPendingFlag(EXTI_22);

	/*Call global function for notification*/
	if(	EXTI_pvIntCallBack[EXTI_22] != NULL)
	{
		EXTI_pvIntCallBack[EXTI_22]();
	}

}

/****************************************************************************/




