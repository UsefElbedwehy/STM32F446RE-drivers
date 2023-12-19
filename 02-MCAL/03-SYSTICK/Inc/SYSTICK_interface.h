#ifndef  SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_
/*@CSR_t*/
typedef enum{
	ENABLE=0,
	TICKINT,
	CLKSOURCE,
	COUNTFLAG=16
}CSR_t;

#define READY_FLAG 1
#define INITIAL_LOAD_VAL	0
#define GET_NUM				0x01
#define SET_BIT				1
#define CLR_BIT				1

void SYSTICK_DelayMs(uint32_t Copy_u32TimeMs);
void SYSTICK_DelayUs(uint32_t Copy_u32TimeUs);


#endif
