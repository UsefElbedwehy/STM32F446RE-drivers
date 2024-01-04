#ifndef	SCB_INTERFACE_H_
#define	SCB_INTERFACE_H_

/*@PRIOGroup_t*/
typedef enum{
	_16G_0SG=0,
	_8G_2SG=4,
	_4G_4SG=5,
	_2G_8SG=6,
	_0G_16SG=7
}PRIOGroup_t;

#define VECTKEY_BIT   16
#define PRIOGROUP_BIT 8

/*@SHCSR_Reg_t*/
typedef enum{
	MEMFAULTACT=0,
	BUSFAULTACT,
	USGFAULTACT=3,
	SVCALLACT=7,
	MONITORACT,
	PENDSVACT=10,
	SYSTICKACT,
	USGFAULTPENDED,
	MEMFAULTPENDED,
	BUSFAULTPENDED,
	SVCALLPENDED,
	MEMFAULTENA,
	BUSFAULTENA,
	USGFAULTENA
}SHCSR_Reg_t;
/*@MemManageF_Reg_t*/
typedef enum{
	IACCVIOL=0,
	DACCVIOL,
	MUNSTKERR=3,
	MSTKERR,
	MLSPERR,
	MMARVALID=7,
}MemManageF_Reg_t;
/*@BusF_Reg_t*/
typedef enum{
	IBUSERR=0,
	PRECISERR,
	IMPRECISERR,
	UNSTKERR,
	STKERR,
	LSPERR,
	BFARVALID=7
}BusF_Reg_t;
/*@UsageF_Reg_t*/
typedef enum{
	UNDEFINSTR=0,
	INVSTATE,
	INVPC,
	NOCP,
	UNALIGNED=8,
	DIVBYZERO=9
}UsageF_Reg_t;

/*
@fn SCB_SetPriorityGroup
@brief set the priority group
@param[in] Copy_PRIOGroup
@retval Local_u8ErrorState
*/
uint8_t SCB_SetPriorityGroup(PRIOGroup_t Copy_PRIOGroup);

/*
@fn SCB_u8EnableMemMangeFaultEx
@brief Enable Memory Management Fault Exception
@param[in] void
@retval void
*/
void SCB_u8EnableMemMangeFaultEx(void);
/*
@fn SCB_u8DisableMemMangeFaultEx
@brief Disable Memory Management Fault Exception
@param[in] void
@retval void
*/
void SCB_u8DisableMemMangeFaultEx(void);

/*
@fn SCB_u8EnableBusFaultEx
@brief Enable Bus Fault Exception
@param[in] void
@retval void
*/
void SCB_u8EnableBusFaultEx(void);
/*
@fn SCB_u8DisableBusFaultEx
@brief Disable Bus Fault Exception
@param[in] void
@retval void
*/
void SCB_u8DisableBusFaultEx(void);

/*
@fn SCB_u8EnableUsageFaultEx
@brief Enable Usage Fault Exception
@param[in] void
@retval void
*/
void SCB_u8EnableUsageFaultEx(void);
/*
@fn SCB_u8DisableUsageFaultEx
@brief Disable Usage Fault Exception
@param[in] void
@retval void
*/
void SCB_u8DisableUsageFaultEx(void);

/*
@fn SCB_u8EnableDivByZero
@brief Enable the Division by zero Exception
@param[in] void
@retval void
*/
void SCB_u8EnableDivByZero(void);
/*
@fn SCB_u8DisableUsageFaultEx
@brief Disable the Division by zero Exception
@param[in] void
@retval void
*/
void SCB_u8DisableDivByZero(void);

/*
@fn SCB_u8SetSysHandlerCtrlSts
@brief Set system handler control and status registers
@param[in] Copy_SHCSR_Reg (type: @SHCSR_Reg_t)
@retval Local_u8ErrorState
*/
uint8_t SCB_u8SetSysHandlerCtrlSts(SHCSR_Reg_t Copy_SHCSR_Reg);
/*
@fn SCB_u8ClrSysHandlerCtrlSts
@brief Clear system handler control and status registers
@param[in] Copy_SHCSR_Reg (type: @SHCSR_Reg_t)
@retval Local_u8ErrorState
*/
uint8_t SCB_u8ClrSysHandlerCtrlSts(SHCSR_Reg_t Copy_SHCSR_Reg);

#endif
