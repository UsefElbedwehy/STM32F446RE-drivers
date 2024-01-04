#ifndef	EXTI_INTERFACE_H_
#define	EXTI_INTERFACE_H_


/*@EXTI_Pending_t*/
typedef enum
{
	NO_PENDING=0,
	PENDING
}EXTI_Pending_t;


/*@EXTI_LINE_t*/
typedef enum{
	EXTI_0=0,
	EXTI_1,
	EXTI_2,
	EXTI_3,
	EXTI_4,
	EXTI_5,
	EXTI_6,
	EXTI_7,
	EXTI_8,
	EXTI_9,
	EXTI_10,
	EXTI_11,
	EXTI_12,
	EXTI_13,
	EXTI_14,
	EXTI_15,
	EXTI_16,			/*connected to the PVD output*/
	EXTI_17,			/*connected to the RTC Alarm event*/
	EXTI_18,			/*connected to the USB OTG FS Wakeup event*/
	EXTI_20=20,			/* connected to the USB OTG HS (configured in FS) Wakeup event*/
	EXTI_21,			/*connected to the RTC Tamper and TimeStamp events*/
	EXTI_22,			/*connected to the RTC Wakeup event*/
	LINES_NUMBER

}EXTI_LINE_t;


/*@Trigger_Conf_t*/
typedef enum{
	RISING=0,
	FALLING,
	RISING_FALLING
}Trigger_Conf_t;


/*@Enable_Conf_t*/
typedef enum{
	ENABLE=0,
	DISABLE
}Enable_Conf_t;


/*@EXTI_Config_t*/
typedef struct{
	EXTI_LINE_t		EXTI_LINE;
	Trigger_Conf_t TriggerState;
	Enable_Conf_t	EnableState;
	void (*CallBackFunc)(void);
}EXTI_Config_t;


/* * * * * * * * Functions Implementation * * * * * * * * */


/*
 * @fn EXTI_u8Init
 * @brief initialize the external interrupt setting
 * @param[in] Copy_Config (type: pointer to struct)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_u8Init(const EXTI_Config_t* Copy_Config);


/*
 * @fn EXTI_EnableInt
 * @brief is to Enable Interrupt
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_EnableInt(EXTI_LINE_t Copy_LINE);


/*
 * @fn EXTI_EnableInt
 * @brief is to Disable Interrupt
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_DisableInt(EXTI_LINE_t Copy_LINE);


/*
 * @fn EXTI_voidClearPendingFlag
 * @brief is to clear pending flag (This bit is cleared by programming it to ‘1’)
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_ClearPendingFlag(EXTI_LINE_t Copy_LINE);


/*
 * @fn EXTI_voidReadPendingFlag
 * @brief is to Get pending flag
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t) , Copy_u8PendingFlagVal (type: pointer uint8_t)
 * @retval Copy_u8ErrorState
 * */
uint8_t EXTI_ReadPendingFlag(EXTI_LINE_t Copy_LINE,uint8_t* Copy_u8PendingFlagVal);


/* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ */
/* ^ ^ ^ ^ Trigger selection functions ^ ^ ^ ^ ^ ^ */

/*
 * @fn EXTI_voidEnableRisingTrigger
 * @brief Enable rising trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidEnableRisingTrigger(EXTI_LINE_t Copy_LINE);


/*
 * @fn EXTI_voidDisableRisingTrigger
 * @brief Disable rising trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidDisableRisingTrigger(EXTI_LINE_t Copy_LINE);


/*
 * @fn EXTI_voidEnableFallingTrigger
 * @brief Enable falling trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidEnableFallingTrigger(EXTI_LINE_t Copy_LINE);


/*
 * @fn EXTI_voidDisableFallingTrigger
 * @brief Disable falling trigger event
 * @param[in]	Copy_LINE (type: enum @EXTI_LINE_t)
 * @retval void
 * */
void EXTI_voidDisableFallingTrigger(EXTI_LINE_t Copy_LINE);
/* ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ */

#endif
