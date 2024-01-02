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

/*
@fn SCB_SetPriorityGroup
@brief set the priority group
@param[in] Copy_PRIOGroup
@retval Local_u8ErrorState
 */
uint8_t SCB_SetPriorityGroup(PRIOGroup_t Copy_PRIOGroup);



#endif
