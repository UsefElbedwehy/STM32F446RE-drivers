#ifndef  DMA_INTERFACE_H_
#define DMA_INTERFACE_H_
/********************************************************************************
 ******************************* ### Registers ### *******************************
 ********************************************************************************/
/*
 * DMA SxCR Register bit number
 * */
typedef enum{
	EN,
	DMEIE,
	TEIE,
	HTIE,
	TCIE,
	PFCTRL,
	DIR0,
	DIR1,
	CIRC,
	PINC,
	MINC,
	PSIZE0,
	PSIZE1,
	MSIZE0,
	MSIZE1,
	PINCOS,
	PL0,
	PL1,
	DBM,
	CT,
	PBURST0=21,
	PBURST1,
	MBURST0,
	MBURST1,
	CHSEL0,
	CHSEL1,
	CHSEL2
}DMA_SxCR_t;

/*
 * DMA SxFCR Register bit number
 * */
typedef enum{
	FTH0,
	FTH1,
	DMDIS,
	FS0,
	FS1,
	FS2,
	FEIE=7
}DMA_SxFCR_t;


/********************************************************************************
 *************************** ### Configurations ### *****************************
 ********************************************************************************/
/*DMA CONTROLLER : DMA1 or DMA2
 * */
typedef enum{
	DMA1_CONTROLLER,
	DMA2_CONTROLLER
}DMA_CONTROLLER_t;

/*
 * CHANNEL SELECTION
 * These bits are protected and can be written only if EN is 0.
 * */
typedef enum{
	DMA_CHANNEL_0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
	DMA_NUMBEROFCHANNELS

}DMA_ChannelNum_t;

/*
 * CALLBACK ID
 * */
typedef enum{
FIFO_ERROR_CALLBACK_ID=0,
DIRECT_MODE_ERROR_CALLBACK_ID=2,
TRANSFER_ERROR_CALLBACK_ID=3,
HALF_TRANSFER_CALLBACK_ID=4,
TRANSFER_COMPLETE_CALLBACK_ID=5

}DMA_CALLBACKINT_ID_t;

/*
 * STREAM SELECTION
 * */
typedef enum{
	DMA_STREAM_0,
	DMA_STREAM_1,
	DMA_STREAM_2,
	DMA_STREAM_3,
	DMA_STREAM_4,
	DMA_STREAM_5,
	DMA_STREAM_6,
	DMA_STREAM_7,
	DMA_NUMBEROFSTREAMS

}DMA_StreamNum_t;

/*
 * MEMORY BURST TRANSFER CONFIGURATION
 * These bits are protected and can be written only if EN = 0.
	In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN = 1
 * */
typedef enum{
	DMA_SINGLE_MEM_TRANSFER,
	DMA_INCREMENT_MEM_4_BEATS,
	DMA_INCREMENT_MEM_8_BEATS,
	DMA_INCREMENT_MEM_16_BEATS

}DMA_MEM_BURST_t;

/*
 * PERIPHERAL BURST TRANSFER CONFIGURATION
 * These bits are protected and can be written only if EN = 0.
 * */
typedef enum{
	DMA_SINGLE_PERIPH_TRANSFER,
	DMA_INCREMENT_PERIPH_4_BEATS,
	DMA_INCREMENT_PERIPH_8_BEATS,
	DMA_INCREMENT_PERIPH_16_BEATS

}DMA_P_BURST_t;

/*
 * CURRENT TARGET (Only in double-buffer Mode)
 * This bit can be written only if EN = 0 to indicate the target memory area of the first transfer.
 * */
typedef enum{
	DMA_CT_MEM0,
	DMA_CT_MEM1
}DMA_CT_t;

/*
 * DOUBLE BUFFER MODE
 * This bit is protected and can be written only if EN = 0.
 * */
typedef enum{
	DMA_DBM_NOBUFFER,   /*no buffer switching at the end of transfer*/
	DMA_DBM_MEMTARGET	/* memory target switched at the end of the DMA transfer*/
}DMA_DOUBLE_BUFFER_MODE_t;

/* PRIORITY LEVEL
 * These bits are protected and can be written only if EN = 0
 * */
typedef enum{
	DMA_LOW_PRIO,
	DMA_MEDUIM_PRIO,
	DMA_HIGH_PRIO,
	DMA_VERYHIGH_PRIO
}DMA_PRIO_t;

/* PERIPHERAL INCREMENT OFFSET SIZE
 * This bit has no meaning if bit PINC = 0.
 * This bit is protected and can be written only if EN = 0.
   This bit is forced low by hardware when the stream is enabled (EN = 1) if the direct mode is
   selected or if PBURST are different from 00.
 * */
typedef enum{
	DMA_LINKED_PSIZE,
	DMA_FIXED_32BIT
}DMA_P_INC_OFFSET_SIZE_t;

/* MEMORY DATA SIZE
 * These bits are protected and can be written only if EN = 0.
   In direct mode, MSIZE is forced by hardware to the same value as PSIZE as soon as EN = 1.
 * */
typedef enum{
	DMA_MSIZE_BYTE_8BIT,
	DMA_MSIZE_HALFWORD_16BIT,
	DMA_MSIZE_WORD_32BIT,
	DMA_MSIZE_RESRVED
}DMA_M_SIZE_t;

/* PERIPHERAL DATA SIZE
 * These bits are protected and can be written only if EN = 0.
 * */
typedef enum{
	DMA_PSIZE_BYTE_8BIT,
	DMA_PSIZE_HALFWORD_16BIT,
	DMA_PSIZE_WORD_32BIT,
	DMA_PSIZE_RESRVED
}DMA_P_SIZE_t;
/**********************************************/
/* MEMORY INCREMENT MODE
 * This bit is protected and can be written only if EN = 0.
 * */
typedef enum{
	DMA_MEM_ADDRESS_PTR_FIXED,
	DMA_MEM_ADDRESS_PTR_INC
}DMA_M_INC_t;

/* PERIPHERAL INCREMENT MODE
 * This bit is protected and can be written only if EN = 0.
 * */
typedef enum{
	DMA_PERIPH_ADDRESS_PTR_FIXED,
	DMA_PERIPH_ADDRESS_PTR_INC
}DMA_P_INC_t;

/* CIRCULAR MODE
 * When the peripheral is the flow controller (bit PFCTRL = 1) and the stream is enabled
   (EN = 1), then this bit is automatically forced by hardware to 0.
   It is automatically forced by hardware to 1 if the DBM bit is set, as soon as the stream is
   enabled (EN = 1).
 * */
typedef enum{
	DMA_CIRCULAR_MODE_ENABLE,
	DMA_CIRCULAR_MODE_DISABLE
}DMA_CIRC_MODE_t;

/*DATA TRANSFER DIRECTION
 * These bits are protected and can be written only if EN = 0.
 * */
typedef enum{
	DMA_P2M,
	DMA_M2P,
	DMA_M2M,
	DMA_DIR_RESERVED
}DMA_DIRECTION_t;

/*PERIPHERAL FLOW CONTROLLER
 * This bit is protected and can be written only if EN = 0.
	When the memory-to-memory mode is selected (bits DIR[1:0]=10), then this bit is
	automatically forced to 0 by hardware
 * */
typedef enum{
	DMA_DMA_FLOW_CONTROLLER,
	DMA_PERIPH_FLOW_CONTROLLER
}DMA_PERIPH_FLOW_CONTROLLER_t;

/*  TRANSFER COMPLETE INTERRUPT ENABLE
 */
typedef enum{
	DMA_TC_INT_DISABLE,
	DMA_TC_INT_ENABLE
}DMA_TRANS_COMP_INT_t;

/*  HALF TRANSFER INTERRUPT ENABLE
 */
typedef enum{
	DMA_HT_INT_DISABLE,
	DMA_HT_INT_ENABLE
}DMA_HALF_TRANS_INT_t;

/*  TRANSFER ERROR INTERRUPT ENABLE
 */
typedef enum{
	DMA_T_INT_DISABLE,
	DMA_T_INT_ENABLE
}DMA_TRANS_ERROR_INT_t;

/*  DIRECT MODE ERROR INTERRUPT ENABLE
 */
typedef enum{
	DMA_DME_INT_DISABLE,
	DMA_DME_INT_ENABLE
}DMA_DIRECTMODE_ERROR_INT_t;

/*  STREAM ENABLE / FLAG STREAM READY WHEN READ LOW
 */
typedef enum{
	DMA_STREAM_DISABLE,
	DMA_STREAM_ENABLE
}DMA_STREAM_State_t;

/* FIFO ERROR INTERRUPT ENABLE
 * */
typedef enum{
	DMA_FE_INT_DISABLE,
	DMA_FE_INT_ENABLE
}DMA_FIFO_INT_EN_t;

/* DIRECT MODE DISABLE
 * This bit is protected and can be written only if EN = 0
 * */
typedef enum{
	DMA_DIRECT_MODE_ENABLE,
	DMA_DIRECT_MODE_DISABLE
}DMA_DIRECTMODE_DISABLE_t;

/* FIFO THRESHOLD SELECTION
 * These bits are not used in the direct mode when the DMIS = 0.
These bits are protected and can be written only if EN = 0.
 *
 * */
typedef enum{
	DMA_1_OVER_4_FULL_FIFO,
	DMA_1_OVER_2_FULL_FIFO,
	DMA_3_OVER_4_FULL_FIFO,
	DMA_FULL_FIFO
}DMA_FIFO_THRESHOLD_SEL_t;

typedef enum{
	DMA_DIRECT_MODE,
	DMA_FIFO_MODE
}DMA_MODE_t;

/* DMA CONFIGURATIONS REGISTER
 * */
typedef struct{
	DMA_CONTROLLER_t 					DMA_CONTROLLER;
	DMA_ChannelNum_t 					Channel_No;
	DMA_StreamNum_t 					Stream_No;

	DMA_MODE_t							MODE;

	DMA_MEM_BURST_t 					Mem_Burst;
	DMA_P_BURST_t 						Periph_Burst;

	//DMA_CT_t	 						Current_Target;
	//DMA_DOUBLE_BUFFER_MODE_t 			Double_Buffer_Mode;
	DMA_PRIO_t	 						Priority_Level;

	//DMA_P_INC_OFFSET_SIZE_t	 			Periph_Inc_OffsetSize;

	DMA_M_SIZE_t	 					Mem_Data_Size;
	DMA_P_SIZE_t	 					Periph_Data_Size;

	DMA_M_INC_t	 						Memory_Increment_Mode;
	DMA_P_INC_t	 						Periph_Increment_Mode;
	DMA_CIRC_MODE_t	 					Circular_Mode;
	DMA_DIRECTION_t						Data_Trasfer_Direction;

	//DMA_PERIPH_FLOW_CONTROLLER_t	 	Periph_Flow_Controller;
	//DMA_TRANS_COMP_INT_t	 			Transfer_Complete_Int_En;
	//DMA_HALF_TRANS_INT_t	 			Half_Transfer_Int_En;
	//DMA_TRANS_ERROR_INT_t   			Transfer_Err_Int_En;
	//DMA_DIRECTMODE_ERROR_INT_t  		Direct_Mode_Err_Int_En;

	DMA_STREAM_State_t					Stream_State;

	DMA_FIFO_INT_EN_t	 				FIFO_Err_Int_En;

	//DMA_DIRECTMODE_DISABLE_t			Direct_Mode_disable;

	DMA_FIFO_THRESHOLD_SEL_t			FIFO_Threshold_Selection;

}DMA_InitConfig_t;

/********************************************************************************
 ***************** ### FUNCTION DECLARATION SECTION ### *************************
 ********************************************************************************/
/*
@func		DMA_Init
@breif		to initiate the DMA Comfiguration
@param	CopyDMA_Config_t (type: enum  DMA_Config_t )
@retval		Local_ErrorState		(type:  ErrorState_t )
 */
ErrorState_t DMA_Init(const DMA_InitConfig_t* Init);

/*
@func		DMA_Start
@breif		to Start the DMA Transferring data
@param	Copy_u8Src 	 (type:  uint32_t* )
@param	Copy_u8Dest		(type:  uint32_t )
@retval		Local_ErrorState		(type:  ErrorState_t )
 */
ErrorState_t DMA_Start(const DMA_InitConfig_t* Init, uint32_t *Copy_u32Src, uint32_t *Copy_u32Dest ,uint32_t Copy_u32Length);

/*
 * @fn		DMA_Start_IT
 * @brief	Start the DMA Transfer with interrupt enabled
 * @param:	Init 				(const pointer to struct)
 * @param  	Copy_u32Src 		pointer to the source memory Buffer address
 * @param  	Copy_u32Dest 		pointer to the destination memory Buffer address
 * @param  	Copy_u32Length 		pointer to the length of data to be transferred from source to destination
 * @retval: Local_ErrorState 	(enum: @ErrorState_t)
 * */
ErrorState_t DMA_Start_IT(const DMA_InitConfig_t* Init, uint32_t *Copy_u32Src, uint32_t *Copy_u32Dest ,uint32_t Copy_u32Length);

/* @func:DMA_StreamEnable
 * @brief:Enable the stream
 * @param:Init (const pointer to struct)
 * @retval:Local_ErrorState (enum: @ErrorState_t)
 * */
ErrorState_t DMA_StreamEnable(const DMA_InitConfig_t* Init);

/* @func:DMA_StreamDisable
 * @brief:Disable the stream
 * @param:Init (const pointer to struct)
 * @retval:Local_ErrorState (enum: @ErrorState_t)
 * */
ErrorState_t DMA_StreamDisable(const DMA_InitConfig_t* Init);

/*
 *@fn:		DMA_Abort
 *@brief:	Aborts the DMA Transfer
 *@param:  	Init   pointer to a DMA_InitConfig_t enums that have
 *                 the configuration information for the specified DMA Stream.
 *@retval:	Local_ErrorState (enum @ErrorState_t) DMA status
 * */
ErrorState_t DMA_Abort(const DMA_InitConfig_t* Init);

//ErrorState_t DMA_DeInit(const DMA_InitConfig_t* Init);

/*
 * @fn:	DMA_GetFlag
 * @brief: 	Get DMA interrupt flag status
 * @param:	Copy_Controller  DMA controller number 	(enum: DMA_CONTROLLER_t)
 * @param:	Copy_StreamNum   DMA Stream number 		(enum: DMA_StreamNum_t)
 * @param:	Copy_ID 		 flag ID	  		  	(enum: DMA_CALLBACKINT_ID_t)
 * @param[out]: Copy_Flag    pointer to (uint8_t)variable to store flag status
 * @retval:	DMA status : Local_ErrorState 			(enum: ErrorState_t)
 * */
ErrorState_t DMA_GetFlag(DMA_CONTROLLER_t Copy_Controller ,DMA_StreamNum_t Copy_StreamNum,DMA_CALLBACKINT_ID_t Copy_ID ,uint8_t* Copy_Flag);

/*
 * @fn:	DMA_ClearFlag
 * @brief: 	Clear DMA interrupt flag
 * @param:	Copy_Controller  DMA controller number 	(enum: DMA_CONTROLLER_t)
 * @param:	Copy_StreamNum   DMA Stream number 		(enum: DMA_StreamNum_t)
 * @param:	Copy_ID 		 flag ID	  		  	(enum: DMA_CALLBACKINT_ID_t)
 * @retval:	DMA status : Local_ErrorState 			(enum: ErrorState_t)
 * */
ErrorState_t DMA_ClearFlag(DMA_CONTROLLER_t Copy_Controller ,DMA_StreamNum_t Copy_StreamNum,DMA_CALLBACKINT_ID_t Copy_ID);

/*
 * @fn	DMA_SetCallBack
 * @brief Set the callback functions related to the ID
 * @param	Init 				pointer to the struct of DMA configurations
 * @param:	Copy_CALLBACKID 	flag ID	  	(enum: DMA_CALLBACKINT_ID_t)
 * @param:  Copy_pvCallBack		pointer to function
 * @retval:	DMA status : Local_ErrorState 	(enum: ErrorState_t)
 * */
ErrorState_t DMA_SetCallBack(const DMA_InitConfig_t* Init ,DMA_CALLBACKINT_ID_t Copy_CALLBACKID ,void (*Copy_pvCallBack)(void));

/*
 * @fn	DMA_IRQ_HANDLER
 * @brief	Hnadle the IRQ of the interrupts
 * @param:	Copy_Controller  DMA controller number 	(enum: DMA_CONTROLLER_t)
 * @param:	Copy_StreamNum   DMA Stream number 		(enum: DMA_StreamNum_t)
 * @retval:	DMA status : Local_ErrorState 			(enum: ErrorState_t)
 * */
ErrorState_t DMA_IRQ_HANDLER(DMA_CONTROLLER_t Copy_ControllerNum ,DMA_StreamNum_t Copy_StreamNum);
/*****************End of FUNCTION DECLARATION SECTION********************************/


#endif
