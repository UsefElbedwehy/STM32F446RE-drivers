/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	DMA_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of DMA
 * @layer	:	MCAL
 * @Date	:	14 February 2024
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************
   ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Enable and configure the peripheral to be connected to the DMA Stream
       (except for internal SRAM/FLASH memories: no initialization is
       necessary) please refer to Reference manual for connection between peripherals
       and DMA requests.

   (#) For a given Stream, program the required configuration through the following parameters:
       Transfer Direction, Source and Destination data formats,
       Circular, Normal or peripheral flow control mode, Stream Priority level,
       Source and Destination Increment mode, FIFO mode and its Threshold (if needed),
       Burst mode for Source and/or Destination (if needed) using HAL_DMA_Init() function.
 */
/*------------------------------INCLUDE SECTION----------------------------------*/
#include <stdint.h>
#include "Stm32F446xx.h"
#include "ErrType.h"
#include "DMA_prv.h"
#include "DMA_interface.h"
/*------------------------------------------------------------------------------*/

/*--------------------------GLOBAL VARIALES SECTION-----------------------------*/
/*DMA1*/
static void (*DMA1_GFUNC[STREAM_NUM][CALLBACK_INT_NUM])(void)={NULL};

/*DMA2*/
static void (*DMA2_GFUNC[STREAM_NUM][CALLBACK_INT_NUM])(void)={NULL};


DMA_Reg_t* DMA[2]={DMA1,DMA2};
/*------------------------------------------------------------------------------*/


/********************************************************************************
 *************** ### FUCTION IMPLEMENTATION SECTION ### *************************
 ********************************************************************************/
/*
@func		DMA_Init
@breif		to initiate the DMA Comfiguration
@param	CopyDMA_Config_t (type: enum  DMA_Config_t )
@retval		Local_ErrorState		(type:  ErrorState_t )
 */
ErrorState_t DMA_Init(const DMA_InitConfig_t* Init)
{
	ErrorState_t Local_ErrorState=OK;
	if(Init == NULL)
	{
		Local_ErrorState=NULL_POINTER;
		return Local_ErrorState;
	}
	if((Init->Channel_No < DMA_NUMBEROFCHANNELS) && (Init->Channel_No >= DMA_CHANNEL_0)
			&& (Init->Stream_No < DMA_NUMBEROFSTREAMS) && (Init->Stream_No < DMA_STREAM_0)
			&& (Init->MODE <= DMA_FIFO_MODE) && (Init->MODE < DMA_DIRECT_MODE)
			&& (Init->Mem_Burst <= DMA_INCREMENT_MEM_16_BEATS) && (Init->Mem_Burst <= DMA_SINGLE_MEM_TRANSFER)
			&& (Init->Periph_Burst <= DMA_INCREMENT_PERIPH_16_BEATS) && (Init->Periph_Burst <= DMA_SINGLE_PERIPH_TRANSFER)
			&& (Init->DMA_CONTROLLER <= DMA2_CONTROLLER ) && (Init->DMA_CONTROLLER <= DMA1_CONTROLLER)
			&& (Init->Priority_Level <= DMA_VERYHIGH_PRIO) && (Init->Priority_Level <= DMA_LOW_PRIO)
			&& (Init->Mem_Data_Size <= DMA_MSIZE_RESRVED) && (Init->Mem_Data_Size <= DMA_MSIZE_BYTE_8BIT)
			&& (Init->Periph_Data_Size <= DMA_PSIZE_RESRVED) && (Init->Periph_Data_Size <= DMA_PSIZE_BYTE_8BIT)
			&& (Init->Memory_Increment_Mode <= DMA_MEM_ADDRESS_PTR_INC) && (Init->Memory_Increment_Mode <= DMA_MEM_ADDRESS_PTR_FIXED)
			&& (Init->Periph_Increment_Mode <= DMA_PERIPH_ADDRESS_PTR_INC) && (Init->Periph_Increment_Mode <= DMA_PERIPH_ADDRESS_PTR_FIXED)
			&& (Init->Circular_Mode <= DMA_CIRCULAR_MODE_DISABLE) && (Init->Circular_Mode <= DMA_CIRCULAR_MODE_ENABLE)
			&& (Init->Data_Trasfer_Direction <= DMA_DIR_RESERVED) && (Init->Data_Trasfer_Direction <= DMA_P2M)
			&& (Init->Stream_State <= DMA_STREAM_ENABLE) && (Init->Stream_State <= DMA_STREAM_DISABLE)
			&& (Init->FIFO_Err_Int_En <= DMA_FE_INT_ENABLE) && (Init->FIFO_Err_Int_En <= DMA_FE_INT_DISABLE)
			&& (Init->FIFO_Threshold_Selection <= DMA_FULL_FIFO) && (Init->FIFO_Threshold_Selection <= DMA_1_OVER_4_FULL_FIFO))
	{
		/*Disable Stream (EN=0) for protected bits*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_STREAM_ENABLE<<EN);

		/*CHANNEL SELECTION*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_CHANNEL_7<<CHSEL0);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Channel_No<<CHSEL0);

		/*TRANSFER DIRECTION*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_DIR_RESERVED<<DIR0);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Data_Trasfer_Direction<<DIR0);

		/*CIRCULAR or DIRECT MODE SELECTION*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_CIRCULAR_MODE_DISABLE<<CIRC);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Circular_Mode <<CIRC);


		/*MEMORY DATA SIZE*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_MSIZE_RESRVED<<MSIZE0);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Mem_Data_Size <<MSIZE0);

		/*PERIPHERAL DATA SIZE*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_PSIZE_RESRVED<<PSIZE0);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Periph_Data_Size <<PSIZE0);

		/*MEMORY INCREMENT MODE*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_MEM_ADDRESS_PTR_INC<<MINC);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Memory_Increment_Mode <<MINC);

		/*PERIPHERAL INCREMENT MODE*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_PERIPH_ADDRESS_PTR_INC<<PINC);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Periph_Increment_Mode <<PINC);

		/*PRIORITY*/
		/*Clear*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_VERYHIGH_PRIO<<PL0);
		/*Set*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Priority_Level <<PL0);

		/*IF FIFO MODE*/
		if(Init->MODE == DMA_FIFO_MODE){
			/*Memory burst transfer configuration*/
			/*Clear*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_INCREMENT_MEM_16_BEATS<<MBURST0);
			/*Set*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Mem_Burst <<MBURST0);
			/* peripheral burst transfer configuration*/
			/*Clear*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~(DMA_INCREMENT_PERIPH_16_BEATS<<PBURST0);
			/*Set*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |=(Init->Periph_Burst <<PBURST0);

			/*DIRECT MODE DISABLE*/
			/*Clear*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR |=(DMA_DIRECT_MODE_DISABLE<< FEIE);


			/*FIFO ERROR INTERRUPT CONFIGURATIONS*/
			/*Clear*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR &=~(DMA_FE_INT_ENABLE<< FEIE);
			/*Set*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR |=(Init->FIFO_Err_Int_En <<FEIE);
			/* FIFO threshold selection*/
			/*Clear*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR &=~(DMA_FULL_FIFO<< FTH0);
			/*Set*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR |=(Init->FIFO_Threshold_Selection << FTH0);

		}else{
			/*DIRECT MODE ENABLE*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR &=~(DMA_DIRECT_MODE_DISABLE<< FEIE);

		}
		/*CLEAR all interrupt flags*/
		/*Reset value: 0x0000 0000*/
		DMA[Init->DMA_CONTROLLER]->DMA_IFCR[LOW_INT_FLAG_CLR_REG] |= CLR_FLAG_REG_VAL;
		DMA[Init->DMA_CONTROLLER]->DMA_IFCR[High_INT_FLAG_CLR_REG] |= CLR_FLAG_REG_VAL;

	}
	else{
		Local_ErrorState=NOK;
	}
	return Local_ErrorState;
}

/*
@func		DMA_Start
@breif		to Start the DMA Transferring data
@param	Copy_u8Src 	 (type:  uint32_t* )
@param	Copy_u8Dest		(type:  uint32_t )
@retval		Local_ErrorState		(type:  ErrorState_t )
 */
ErrorState_t DMA_Start(const DMA_InitConfig_t* Init, uint32_t *Copy_u32Src, uint32_t *Copy_u32Dest ,uint32_t Copy_u32Length)
{
	ErrorState_t Local_ErrorState=OK;
	if(Copy_u32Src == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else
	{
		/*Disable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR&=~(DMA_STREAM_ENABLE<<EN);
		/*Source and Destination*/
		switch(Init->Data_Trasfer_Direction)
		{
		case DMA_P2M:
			/*P is source*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxPAR = (uint32_t)Copy_u32Src;
			/*M is Destination*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxM0AR = (uint32_t)Copy_u32Dest;
			break;
		case DMA_M2P:
			/*M is source*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxM0AR = (uint32_t)Copy_u32Src;
			/*P is Destination*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxPAR = (uint32_t)Copy_u32Dest;
			break;
		case DMA_M2M:
			/*M is source*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxM0AR = (uint32_t)Copy_u32Src;
			/*P is Destination*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxPAR = (uint32_t)Copy_u32Dest;
			break;
		default : Local_ErrorState=NOK; break;
		}
		/*Length*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxNDTR=(Copy_u32Length & LENGTH_MASK);
		/*Enable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR|=(DMA_STREAM_ENABLE<<EN);


	}
	return Local_ErrorState;
}

/* @func:DMA_StreamEnable
 * @brief:Enable the stream
 * @param:Init (const pointer to struct)
 * @retval:Local_ErrorState (enum: @ErrorState_t)
 * */
ErrorState_t DMA_StreamEnable(const DMA_InitConfig_t* Init)
{
	ErrorState_t Local_ErrorState=OK;

	if(Init == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else{
		/*Enable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR|=(DMA_STREAM_ENABLE<<EN);

	}

	return Local_ErrorState;
}

/* @func:DMA_StreamDisable
 * @brief:Disable the stream
 * @param:Init (const pointer to struct)
 * @retval:Local_ErrorState (enum: @ErrorState_t)
 * */
ErrorState_t DMA_StreamDisable(const DMA_InitConfig_t* Init)
{
	ErrorState_t Local_ErrorState=OK;
	uint16_t	Local_u16TimeOut=0;
	if(Init == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else{
		/*Disable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR&=~(DMA_STREAM_ENABLE<<EN);
		/*Wait till be disabled*/
		while( (((DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR) & 0x01 ) != EN_DISABLED) || (Local_u16TimeOut == TIMEOUT) )
		{
			Local_u16TimeOut++;
		}
	}

	return Local_ErrorState;
}

/*
 * @fn		DMA_Start_IT
 * @brief	Start the DMA Transfer with interrupt enabled
 * @param:	Init 				(const pointer to struct)
 * @param  	Copy_u32Src 		pointer to the source memory Buffer address
 * @param  	Copy_u32Dest 		pointer to the destination memory Buffer address
 * @param  	Copy_u32Length 		pointer to the length of data to be transferred from source to destination
 * @retval: Local_ErrorState 	(enum: @ErrorState_t)
 * */
ErrorState_t DMA_Start_IT(const DMA_InitConfig_t* Init, uint32_t *Copy_u32Src, uint32_t *Copy_u32Dest ,uint32_t Copy_u32Length)
{
	ErrorState_t Local_ErrorState=OK;

	if(Init == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else
	{
		/*Disable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR&=~(DMA_STREAM_ENABLE<<EN);
		/*Source and Destination*/
		switch(Init->Data_Trasfer_Direction)
		{
		case DMA_P2M:
			/*P is source*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxPAR = (uint32_t)Copy_u32Src;
			/*M is Destination*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxM0AR = (uint32_t)Copy_u32Dest;
			break;
		case DMA_M2P:
			/*M is source*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxM0AR = (uint32_t)Copy_u32Src;
			/*P is Destination*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxPAR = (uint32_t)Copy_u32Dest;
			break;
		case DMA_M2M:
			/*M is source*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxM0AR = (uint32_t)Copy_u32Src;
			/*P is Destination*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxPAR = (uint32_t)Copy_u32Dest;
			break;
		default : Local_ErrorState=NOK; break;
		}
		/*Length*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxNDTR=(Copy_u32Length & LENGTH_MASK);
		/*CLEAR all interrupt flags*/
		/*Reset value: 0x0000 0000*/
		DMA[Init->DMA_CONTROLLER]->DMA_IFCR[LOW_INT_FLAG_CLR_REG] |= CLR_FLAG_REG_VAL;
		DMA[Init->DMA_CONTROLLER]->DMA_IFCR[High_INT_FLAG_CLR_REG] |= CLR_FLAG_REG_VAL;
		/*Enable Interrupts*/
		/*Transfer complete interrupt enable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |= (DMA_TC_INT_ENABLE<<TCIE);
		/*Half Transfer interrupt enable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |= (DMA_HT_INT_ENABLE<<HTIE);
		/*Transfer error interrupt enable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |= (DMA_T_INT_ENABLE<<TEIE);
		/*Direct mode error interrupt enable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR |= (DMA_DME_INT_ENABLE<<DMEIE);
		if(Init->FIFO_Err_Int_En == DMA_FE_INT_ENABLE)
		{
			/*FIFI mode interrupt enable*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR |= (DMA_FE_INT_ENABLE<<FEIE);
		}
		/*Enable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR|=(DMA_STREAM_ENABLE<<EN);
	}
	return Local_ErrorState;
}
/*
 *@fn:		DMA_Abort
 *@brief:	Aborts the DMA Transfer
 *@param:  	Init   pointer to a DMA_InitConfig_t enums that have
 *                 the configuration information for the specified DMA Stream.
 *@retval:	Local_ErrorState (enum @ErrorState_t) DMA status
 * */
ErrorState_t DMA_Abort(const DMA_InitConfig_t* Init)
{
	ErrorState_t Local_ErrorState=OK;
	uint16_t Local_u16TimeOut=0;
	if(Init == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else{
		/*Disable all interrupts*/
		/*Transfer complete interrupt disable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~ (DMA_TC_INT_ENABLE<<TCIE);
		/*Half Transfer interrupt disable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~ (DMA_HT_INT_ENABLE<<HTIE);
		/*Transfer error interrupt disable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~ (DMA_T_INT_ENABLE<<TEIE);
		/*Direct mode error interrupt disable*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR &=~ (DMA_DME_INT_ENABLE<<DMEIE);
		if(Init->FIFO_Err_Int_En == DMA_FE_INT_ENABLE)
		{
			/*FIFI mode interrupt disable*/
			DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxFCR &=~ (DMA_FE_INT_ENABLE<<FEIE);
		}
		/*Disable Stream*/
		DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR&=~(DMA_STREAM_ENABLE<<EN);

		while( (((DMA[Init->DMA_CONTROLLER]->STREAM_REG[Init->Stream_No].DMA_SxCR) & 0x01 ) != EN_DISABLED) || (Local_u16TimeOut == TIMEOUT) )
		{
			Local_u16TimeOut++;
		}
		/*CLEAR all interrupt flags*/
		DMA[Init->DMA_CONTROLLER]->DMA_IFCR[LOW_INT_FLAG_CLR_REG] |= CLR_FLAG_REG_VAL;
		DMA[Init->DMA_CONTROLLER]->DMA_IFCR[High_INT_FLAG_CLR_REG] |= CLR_FLAG_REG_VAL;
	}

	return Local_ErrorState;
}

/*
 * @fn:	DMA_ClearFlag
 * @brief: 	Clear DMA interrupt flag
 * @param:	Copy_Controller  DMA controller number 	(enum: DMA_CONTROLLER_t)
 * @param:	Copy_StreamNum   DMA Stream number 		(enum: DMA_StreamNum_t)
 * @param:	Copy_ID 		 flag ID	  		  	(enum: DMA_CALLBACKINT_ID_t)
 * @retval:	DMA status : Local_ErrorState 			(enum: ErrorState_t)
 * */
ErrorState_t DMA_ClearFlag(DMA_CONTROLLER_t Copy_Controller ,DMA_StreamNum_t Copy_StreamNum,DMA_CALLBACKINT_ID_t Copy_ID)
{
	ErrorState_t Local_ErrorState=OK;

	switch(Copy_StreamNum)
	{
	case DMA_STREAM_0:
		DMA[Copy_Controller]->DMA_IFCR[0] |= (1 << Copy_ID);		break;

	case DMA_STREAM_1:
		DMA[Copy_Controller]->DMA_IFCR[0] |= (1 << (Copy_ID + 6));	break;

	case DMA_STREAM_2:
		DMA[Copy_Controller]->DMA_IFCR[0] |= (1 << (Copy_ID + 16));	break;

	case DMA_STREAM_3:
		DMA[Copy_Controller]->DMA_IFCR[0] |= (1 << (Copy_ID + 22));	break;

	case DMA_STREAM_4:
		DMA[Copy_Controller]->DMA_IFCR[1] |= (1 << Copy_ID);		break;

	case DMA_STREAM_5:
		DMA[Copy_Controller]->DMA_IFCR[1] |= (1 << (Copy_ID + 6));	break;

	case DMA_STREAM_6:
		DMA[Copy_Controller]->DMA_IFCR[1] |= (1 << (Copy_ID + 16));	break;

	case DMA_STREAM_7:
		DMA[Copy_Controller]->DMA_IFCR[1] |= (1 << (Copy_ID + 22));	break;
	case DMA_NUMBEROFSTREAMS:
		Local_ErrorState=NOK;	break;
	default:
		Local_ErrorState=NOK;	break;
	}
	return Local_ErrorState;
}

/*
 * @fn:	DMA_GetFlag
 * @brief: 	Get DMA interrupt flag status
 * @param:	Copy_Controller  DMA controller number 	(enum: DMA_CONTROLLER_t)
 * @param:	Copy_StreamNum   DMA Stream number 		(enum: DMA_StreamNum_t)
 * @param:	Copy_ID 		 flag ID	  		  	(enum: DMA_CALLBACKINT_ID_t)
 * @param[out]: Copy_Flag    pointer to (uint8_t)variable to store flag status
 * @retval:	DMA status : Local_ErrorState 			(enum: ErrorState_t)
 * */
ErrorState_t DMA_GetFlag(DMA_CONTROLLER_t Copy_Controller ,DMA_StreamNum_t Copy_StreamNum,DMA_CALLBACKINT_ID_t Copy_ID ,uint8_t* Copy_Flag)
{
	ErrorState_t Local_ErrorState=OK;

	if(Copy_Flag == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else
	{
		switch(Copy_StreamNum)
		{
		case DMA_STREAM_0:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[0]>>(Copy_ID)) & (0x01) );		break;

		case DMA_STREAM_1:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[0]>>(Copy_ID + 6)) & (0x01) );	break;

		case DMA_STREAM_2:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[0]>>(Copy_ID + 16)) & (0x01) );	break;

		case DMA_STREAM_3:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[0]>>(Copy_ID + 22)) & (0x01) );	break;

		case DMA_STREAM_4:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[1]>>(Copy_ID)) & (0x01) );		break;

		case DMA_STREAM_5:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[1]>>(Copy_ID + 6)) & (0x01) );	break;

		case DMA_STREAM_6:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[1]>>(Copy_ID + 16)) & (0x01) );	break;

		case DMA_STREAM_7:
			*Copy_Flag = ( (DMA[Copy_Controller]->DMA_IFCR[1]>>(Copy_ID + 22)) & (0x01) );	break;
		case DMA_NUMBEROFSTREAMS:
			Local_ErrorState=NOK;	break;
		default:
			Local_ErrorState=NOK;	break;
		}

	}
	return Local_ErrorState;
}

/*
 * @fn	DMA_SetCallBack
 * @brief Set the callback functions related to the ID
 * @param	Init 				pointer to the struct of DMA configurations
 * @param:	Copy_CALLBACKID 	flag ID	  	(enum: DMA_CALLBACKINT_ID_t)
 * @param:  Copy_pvCallBack		pointer to function
 * @retval:	DMA status : Local_ErrorState 	(enum: ErrorState_t)
 * */
ErrorState_t DMA_SetCallBack(const DMA_InitConfig_t* Init ,DMA_CALLBACKINT_ID_t Copy_CALLBACKID ,void (*Copy_pvCallBack)(void))
{
	ErrorState_t Local_ErrorState=OK;

	if((Copy_CALLBACKID <= TRANSFER_COMPLETE_CALLBACK_ID) && (Copy_CALLBACKID >= FIFO_ERROR_CALLBACK_ID) && (Copy_pvCallBack != NULL))
	{
		switch(Init->DMA_CONTROLLER)
		{
		case DMA1_CONTROLLER:
			DMA1_GFUNC[Init->Stream_No][Copy_CALLBACKID]=Copy_pvCallBack;
			break;
		case DMA2_CONTROLLER:
			DMA2_GFUNC[Init->Stream_No][Copy_CALLBACKID]=Copy_pvCallBack;
			break;
		default: Local_ErrorState=NOK; break;
		}
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn	DMA_IRQ_HANDLER
 * @brief	Hnadle the IRQ of the interrupts
 * @param:	Copy_Controller  DMA controller number 	(enum: DMA_CONTROLLER_t)
 * @param:	Copy_StreamNum   DMA Stream number 		(enum: DMA_StreamNum_t)
 * @retval:	DMA status : Local_ErrorState 			(enum: ErrorState_t)
 * */
ErrorState_t DMA_IRQ_HANDLER(DMA_CONTROLLER_t Copy_ControllerNum ,DMA_StreamNum_t Copy_StreamNum)
{
	ErrorState_t Local_ErrorState=OK;
	uint8_t Local_FlagStatus=0;


	if((Copy_ControllerNum >= DMA1_CONTROLLER) && (Copy_ControllerNum <= DMA2_CONTROLLER)
			&& (Copy_StreamNum>=DMA_STREAM_0) && (Copy_StreamNum <= DMA_STREAM_7))
	{
		DMA_GetFlag(Copy_ControllerNum, Copy_StreamNum, FIFO_ERROR_CALLBACK_ID, &Local_FlagStatus);
		if(Local_FlagStatus == SET)
		{
			DMA_ClearFlag(Copy_ControllerNum, Copy_StreamNum, FIFO_ERROR_CALLBACK_ID);
			if((DMA1_GFUNC[Copy_StreamNum][FIFO_ERROR_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA1_CONTROLLER))
			{
				DMA1_GFUNC[Copy_StreamNum][FIFO_ERROR_CALLBACK_ID]();
			}
			else if((DMA2_GFUNC[Copy_StreamNum][FIFO_ERROR_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA2_CONTROLLER))
			{
				DMA2_GFUNC[Copy_StreamNum][FIFO_ERROR_CALLBACK_ID]();
			}
		}

		DMA_GetFlag(Copy_ControllerNum, Copy_StreamNum, DIRECT_MODE_ERROR_CALLBACK_ID, &Local_FlagStatus);
		if(Local_FlagStatus == SET)
		{
			DMA_ClearFlag(Copy_ControllerNum, Copy_StreamNum, DIRECT_MODE_ERROR_CALLBACK_ID);
			if((DMA1_GFUNC[Copy_StreamNum][DIRECT_MODE_ERROR_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA1_CONTROLLER))
			{
				DMA1_GFUNC[Copy_StreamNum][DIRECT_MODE_ERROR_CALLBACK_ID]();
			}
			else if((DMA2_GFUNC[Copy_StreamNum][DIRECT_MODE_ERROR_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA2_CONTROLLER))
			{
				DMA2_GFUNC[Copy_StreamNum][DIRECT_MODE_ERROR_CALLBACK_ID]();
			}
		}

		DMA_GetFlag(Copy_ControllerNum, Copy_StreamNum, TRANSFER_ERROR_CALLBACK_ID, &Local_FlagStatus);
		if(Local_FlagStatus == SET)
		{
			DMA_ClearFlag(Copy_ControllerNum, Copy_StreamNum, TRANSFER_ERROR_CALLBACK_ID);
			if((DMA1_GFUNC[Copy_StreamNum][TRANSFER_ERROR_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA1_CONTROLLER))
			{
				DMA1_GFUNC[Copy_StreamNum][TRANSFER_ERROR_CALLBACK_ID]();
			}
			else if((DMA2_GFUNC[Copy_StreamNum][TRANSFER_ERROR_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA2_CONTROLLER))
			{
				DMA2_GFUNC[Copy_StreamNum][TRANSFER_ERROR_CALLBACK_ID]();
			}
		}

		DMA_GetFlag(Copy_ControllerNum, Copy_StreamNum, HALF_TRANSFER_CALLBACK_ID, &Local_FlagStatus);
		if(Local_FlagStatus == SET)
		{
			DMA_ClearFlag(Copy_ControllerNum, Copy_StreamNum, HALF_TRANSFER_CALLBACK_ID);
			if((DMA1_GFUNC[Copy_StreamNum][HALF_TRANSFER_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA1_CONTROLLER))
			{
				DMA1_GFUNC[Copy_StreamNum][HALF_TRANSFER_CALLBACK_ID]();
			}
			else if((DMA2_GFUNC[Copy_StreamNum][HALF_TRANSFER_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA2_CONTROLLER))
			{
				DMA2_GFUNC[Copy_StreamNum][HALF_TRANSFER_CALLBACK_ID]();
			}
		}

		DMA_GetFlag(Copy_ControllerNum, Copy_StreamNum, TRANSFER_COMPLETE_CALLBACK_ID, &Local_FlagStatus);
		if(Local_FlagStatus == SET)
		{
			DMA_ClearFlag(Copy_ControllerNum, Copy_StreamNum, TRANSFER_COMPLETE_CALLBACK_ID);
			if((DMA1_GFUNC[Copy_StreamNum][TRANSFER_COMPLETE_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA1_CONTROLLER))
			{
				DMA1_GFUNC[Copy_StreamNum][TRANSFER_COMPLETE_CALLBACK_ID]();
			}
			else if((DMA2_GFUNC[Copy_StreamNum][TRANSFER_COMPLETE_CALLBACK_ID] != NULL) && (Copy_ControllerNum == DMA2_CONTROLLER))
			{
				DMA2_GFUNC[Copy_StreamNum][TRANSFER_COMPLETE_CALLBACK_ID]();
			}
		}
	}
	else
	{
		Local_ErrorState=NOK;
	}
	return Local_ErrorState;
}

/*------------------------------------------------------------------------------*/

/*----------------------------HANDLER SECTION-----------------------------------*/
/*DMA1*/
void DMA1_Stream0_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_0);
}
void DMA1_Stream1_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_1);
}
void DMA1_Stream2_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_2);
}
void DMA1_Stream3_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_3);
}
void DMA1_Stream4_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_4);
}
void DMA1_Stream5_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_5);
}
void DMA1_Stream6_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_6);
}
void DMA1_Stream7_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA1_CONTROLLER , DMA_STREAM_7);
}
/*DMA2*/
void DMA2_Stream0_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_0);
}
void DMA2_Stream1_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_1);
}
void DMA2_Stream2_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_2);
}
void DMA2_Stream3_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_3);
}
void DMA2_Stream4_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_4);
}
void DMA2_Stream5_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_5);
}
void DMA2_Stream6_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_6);
}
void DMA2_Stream7_IRQHandler()
{
	DMA_IRQ_HANDLER( DMA2_CONTROLLER , DMA_STREAM_7);
}
/*------------------------------------------------------------------------------*/
