#ifndef	SYSCFG_INTERFACE_H_
#define	SYSCFG_INTERFACE_H_

typedef enum{
	PORT_A=0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G,
	PORT_H
}PORTx_t;

typedef enum{
	LINE0=0,
	LINE1,
	LINE2,
	LINE3,
	LINE4,
	LINE5,
	LINE6,
	LINE7,
	LINE8,
	LINE9,
	LINE10,
	LINE11,
	LINE12,
	LINE13,
	LINE14,
	LINE15
	
}Line_t;

/*
@fn SYSCFG_u8SetExtiPort
@brief 	to set the port of the external interrupt
@param[in]	Copy_line (type: enum @Line_t)  , Copy_port (type: enum @PORTx_t)
@retval    Copy_u8ErrorState
*/
uint8_t SYSCFG_u8SetExtiPort(Line_t Copy_line,PORTx_t Copy_port);


#endif
