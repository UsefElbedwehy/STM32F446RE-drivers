#ifndef  DMA_PRV_H_
#define DMA_PRV_H_

#define DATA_LENGTH_REG_MASK	0xFFFF0000

#define CLR_FLAG_REG_VAL 0x0F7D0F7D

#define LOW_INT_FLAG_CLR_REG	0
#define High_INT_FLAG_CLR_REG	1

#define LENGTH_MASK		0x0000FFFF

#define STREAM_NUM 7
#define CALLBACK_INT_NUM 5

#define EN_DISABLED 0

#define TIMEOUT 40000

#define SET   1
#define RESET 0

#endif
