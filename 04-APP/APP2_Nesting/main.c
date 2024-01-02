/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Usef Elbedwehy
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "Stm32F446xx.h"
#include "ErrType.h"

#include "RCC_Private.h"
#include "RCC_Interface.h"

#include "GPIO_prv.h"
#include "GPIO_interface.h"


#include "NVIC_prv.h"
#include "NVIC_interface.h"

#include "SCB_prv.h"
#include "SCB_interface.h"


/*
 * @brief: the idea is to show nesting
 * USART3(higher priority) will interrupt UART5(lower priority)
 * */
int main(void)
{
	/*GPIO PIN CONFIGURATIONS*/
	PinConfig_t Local_PinConfig={
			.Port=PORTA,
			.PinNum=PIN5,
			.Mode=OUTPUT,
			.Speed=LOW_SPEED,
			.OutputType=PUSH_PULL,
			.PullType=PULLUP,
			.AltFunc=AF0
	};
	/*enable HSE*/
	RCC_SetClkSts(HSE, ON);
	/*Set HSE as system clock*/
	RCC_SetSysClk(HSE);
	/*Enable AHB1*/
	RCC_AHB1EnableClock(GPIOAEN);

	/*GPIO initialization*/
	GPIO_u8PinInit(&Local_PinConfig);
	/*Initial led state: LOW*/
	GPIO_u8SetPinValue(PORTA, PIN5, PIN_LOW);
	/*Choose Priority Group 5 (2-bits for Group priority and 2-bits for sub group priority)*/
	SCB_SetPriorityGroup(_4G_4SG);
	/*set USART3 priority: 2*/
	NVIC_SetIRQPriority(USART3, 0b0001);
	/*set UART5 priority: 3*/
	NVIC_SetIRQPriority(UART5, 0b0110);

	NVIC_EnableIRQ(USART3);
	NVIC_EnableIRQ(UART5);

	NVIC_SetPendingFlag(UART5);

	NVIC_DisableIRQ(USART3);
	NVIC_DisableIRQ(UART5);
	while(1)
	{

	}

}

void UART5_IRQHandler(void)
{

	NVIC_SetPendingFlag(USART3);
	GPIO_u8SetPinValue(PORTA, PIN5, PIN_LOW);
}

void USART3_IRQHandler(void)
{
	GPIO_u8SetPinValue(PORTA, PIN5, PIN_HIGH);
}


