#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/*@IRQn_t*/
typedef enum{
	WWDG=0,
	PVD,
	TAMP_STAMP,
	RTC_WKUP,
	FLASH,
	RCC_,
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	DMA1_Stream0,
	DMA1_Stream1,
	DMA1_Stream2,
	DMA1_Stream3,
	DMA1_Stream4,
	DMA1_Stream5,
	DMA1_Stream6,
	ADC,
	CAN1_TX,
	CAN1_RX0,
	CAN1_RX1,
	CAN1_SCE,
	EXTI9_5,
	TIM1_BRK_TIM9,
	TIM1_UP_TIM10,
	TIM1_TRG_COM_TIM11,
	TIM1_CC,
	TIM2,
	TIM3,
	TIM4,
	I2C1_EV,
	I2C1_ER,
	I2C2_EV,
	I2C2_ER,
	SPI1,
	SPI2,
	USART1,
	USART2,
	USART3,
	EXTI15_10,
	RTC_Alarm,
	OTG_FS_WKUP,
	TIM8_BRK_TIM12,
	TIM8_UP_TIM13,
	TIM8_TRG_COM_TIM14,
	TIM8_CC,
	DMA1_Stream7,
	FMC,
	SDIO,
	TIM5,
	SPI3,
	UART4,
	UART5,
	TIM6_DAC,
	TIM7,
	DMA2_Stream0,
	DMA2_Stream1,
	DMA2_Stream2,
	DMA2_Stream3,
	DMA2_Stream4,
	CAN2_TX=63,
	CAN2_RX0,
	CAN2_RX1,
	CAN2_SCE,
	OTG_FS,
	DMA2_Stream5,
	DMA2_Stream6,
	DMA2_Stream7,
	USART6,
	I2C3_EV,
	I2C3_ER,
	OTG_HS_EP1_OUT,
	OTG_HS_EP1_IN,
	OTG_HS_WKUP,
	OTG_HS,
	DCMI,
	FPU=81,
	SPI4=84,
	SAI1=87,
	SAI2=91,
	QuadSPI,
	HDMI_CEC,
	SPDIF_Rx,
	FMPI2C1,
	FMPI2C1_ERROR
}IRQn_t;
/*
@fn NVIC_EnableIRQ
@brief enable peripheral interrupt using NVIC
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_EnableIRQ(IRQn_t Copy_IRQn);
/*
@fn NVIC_DisableIRQ
@brief disable peripheral interrupt using NVIC
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_DisableIRQ(IRQn_t Copy_IRQn);

/*
@fn NVIC_SetPendingFlag
@brief set the pending flag of the peripheral
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_SetPendingFlag(IRQn_t Copy_IRQn);
/*
@fn NVIC_ClearPendingFlag
@brief Clear the pending flag of the peripheral
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_ClearPendingFlag(IRQn_t Copy_IRQn);
/*
@fn NVIC_GetActiveFlag
@brief get the pending flag value
@param[in] IRQNum
@retval Local_u8ErrorState ,*Copy_u8PtrActiveFlag
*/
uint8_t NVIC_GetPendingFlag(IRQn_t Copy_IRQn ,uint8_t* Copy_u8PtrActiveFlag);
/*
@fn NVIC_GetActiveFlag
@brief get the active flag value
@param[in] IRQNum
@retval Local_u8ErrorState , *Copy_u8PtrActiveFlag
*/
uint8_t NVIC_GetActiveFlag(IRQn_t Copy_IRQn ,uint8_t* Copy_u8PtrActiveFlag);
/*
@fn SCB_SetPriorityGroup
@brief set the priority group
@param[in] Copy_IRQn ,Copy_priority
@retval Local_u8ErrorState
*/
uint8_t	NVIC_SetIRQPriority(IRQn_t Copy_IRQn,uint8_t Copy_priority);


#endif
