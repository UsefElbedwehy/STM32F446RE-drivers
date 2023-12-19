#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/*
@fn NVIC_EnableIRQ
@brief 
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_EnableIRQ(IRQn_t Copy_IRQn);
/*
@fn NVIC_DisableIRQ
@brief 
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_DisableIRQ(IRQn_t Copy_IRQn);

/*
@fn NVIC_SetPendingFlag
@brief 
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_SetPendingFlag(IRQn_t Copy_IRQn);
/*
@fn NVIC_ClearPendingFlag
@brief 
@param[in] Copy_IRQn
@retval Local_u8ErrorState
*/
uint8_t NVIC_ClearPendingFlag(IRQn_t Copy_IRQn);
/*
@fn NVIC_GetActiveFlag
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState ,*Copy_u8PtrActiveFlag
*/
uint8_t NVIC_GetPendingFlag(IRQn_t Copy_IRQn ,uint8_t* Copy_u8PtrActiveFlag);
/*
@fn NVIC_GetActiveFlag
@brief 
@param[in] IRQNum
@retval Local_u8ErrorState , *Copy_u8PtrActiveFlag
*/
uint8_t NVIC_GetActiveFlag(IRQn_t Copy_IRQn ,uint8_t* Copy_u8PtrActiveFlag);


#endif
