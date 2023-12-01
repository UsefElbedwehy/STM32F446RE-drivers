#ifndef  STM32F446XX_H_
#define  STM32F446XX_H_ 

/**************Various Memory Base Addresses***************/
#define SRAM_BASE_ADRRESS  					0x20000000UL
#define FLASH_BASE_ADRRESS 					0x08000000UL
#define  SYSTEM_MEMORY_BASE_ADRRESS 	    0x1FFF0000UL
/***************APB1 Peripherals Base Addresses****************/
#define GPIOA_BASE_ADDRESS					0x40020000U      /*GENERAL PURPOSE INPUT OUTPOT (PORTA) BASE ADDRESS*/
#define GPIOB_BASE_ADDRESS					0x40020400U      /*GENERAL PURPOSE INPUT OUTPOT (PORTB) BASE ADDRESS*/
#define GPIOC_BASE_ADDRESS					0x40020800U      /*GENERAL PURPOSE INPUT OUTPOT (PORTC) BASE ADDRESS*/
#define GPIOD_BASE_ADDRESS					0x40020C00U      /*GENERAL PURPOSE INPUT OUTPOT (PORTD) BASE ADDRESS*/
#define GPIOE_BASE_ADDRESS		    		0x40021000U      /*GENERAL PURPOSE INPUT OUTPOT (PORTE) BASE ADDRESS*/
#define GPIOF_BASE_ADDRESS		    		0x40021400U      /*GENERAL PURPOSE INPUT OUTPOT (PORTF) BASE ADDRESS*/
#define GPIOG_BASE_ADDRESS					0x40021800U      /*GENERAL PURPOSE INPUT OUTPOT (PORTG) BASE ADDRESS*/
#define GPIOH_BASE_ADDRESS					0x40021C00U      /*GENERAL PURPOSE INPUT OUTPOT (PORTH) BASE ADDRESS*/

#define RCC_BASE_ADDRESS          			0x40023800U      /*RESET AND CLOCK CONTROL BASE ADDRESS*/

#define USB_OTG_HS_BASE_ADDRESS				0x40040000U
#define DMA2_BASE_ADDRESS					0x40026400U
#define DMA1_BASE_ADDRESS					0x40026000U
#define BKPSRAM_BASE_ADDRESS				0x40024000U
#define FLASH_I_R_BASE_ADDRESS				0x40023C00U      /*FLASH INTERFACE REGISTER BASE ADDRESS*/
#define CRC_BASE_ADDRESS					0x40023000U	   /*CYCLIC REDUNDANCY CHECH BASE ADDRESS*/

/***************APB2 Peripherals Base Addresses****************/

/***************APB3 Peripherals Base Addresses****************/

/***************AHB1 Peripherals Base Addresses****************/

/***************AHB2 Peripherals Base Addresses****************/

/***************AHB3 Peripherals Base Addresses****************/

/***************GPIO Register Definition Structure****************/
typedef struct{
	volatile uint32_t GPIO_MODER;			  /*GPIO PORT Mode Register*/
	volatile uint32_t GPIO_OTYPE;             /*GPIO PORT Output Type Register*/
	volatile uint32_t GPIO_OSPEEDER;      /*GPIO PORT Output Speed Register*/
	volatile uint32_t GPIO_PUPDR;            /*GPIO PORT Pull Up/Down Register*/
	volatile uint32_t GPIO_IDR;                /*GPIO PORT Input Data Register*/
	volatile uint32_t GPIO_ODR;               /*GPIO PORT Output Data Register*/
	volatile uint32_t GPIO_BSRR;             /*GPIO PORT Bit Set/Reset Register*/
	volatile uint32_t GPIO_LCKR;             /*GPIO PORT Lock Register*/
	volatile uint32_t GPIO_AFR[2];          /*GPIO PORT Alternative Function Register*/

}GPIO_RegDef_t;

/***************GPIO Register Definition ****************/
#define GPIOA	   ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB      ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC      ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD      ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE      ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF      ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG      ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH      ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)

/***************RCC Register Definition Structure****************/
typedef struct{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t RCC_AHB3RSTR;
	volatile uint32_t RCC_Reserved1;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_Reserved2;
	volatile uint32_t RCC_Reserved3;
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RCC_Reserved4;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t Reserved5;
	volatile uint32_t Reserved6;
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RCC_Reserved7;
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	volatile uint32_t Reserved8;
	volatile uint32_t Reserved9;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t Reserved10;
	volatile uint32_t Reserved11 ;
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	volatile uint32_t RCC_PLLSAICFGR;
	volatile uint32_t RCC_DCKCFGR;
	volatile uint32_t RCC_CKGATENR;
	volatile uint32_t RCC_DCKCFGR2;

}RCC_RegDef_t;
/***************RCC Register Definition ****************/
#define RCC 		 ((RCC_RegDef_t*)RCC_BASE_ADDRESS)

#endif
