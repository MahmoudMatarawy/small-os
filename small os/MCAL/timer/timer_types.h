/*
 * timer_types.h
 *
 * Created: 5/28/2023 2:15:32 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef TIMER_TYPES_H_
#define TIMER_TYPES_H_

#include "../../STD_LIB/std_types.h"


typedef uint8_t u8_timerErrors_t;

#define  TIMER_E_OK				((u8_timerErrors_t)0x00)
#define  TIMER_E_NOT_OK			((u8_timerErrors_t)0x03)


typedef enum
{
	TIMER_0,TIMER_1,TIMER_2,INVALID_TIMER_NUM
}en_timer_num_t;

typedef enum
{
	TIMER_2_NO_CLOCK,TIMER_2_F_CPU_CLOCK,TIMER_2_F_CPU_8,TIMER_2_F_CPU_32,TIMER_2_F_CPU_64,TIMER_2_F_CPU_128,TIMER_2_F_CPU_256,TIMER_2_F_CPU_1024,
	TIMER_2_INVALID_TIMER_CLK
}en_timer_2_clock_t;


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,
	TIMER_EXTERNAL_CLK_FALLING_EDGE,TIMER_EXTERNAL_CLK_RISING_EDGE,
	INVALID_TIMER_CLK
}en_timer_clock_t;

typedef enum
{
	TIMER_INTERRUPT_FEATURE_DISABLE = 0,
	TIMER_INTERRUPT_FEATURE_ENABLE
}en_timer_interrupt_feature_t;


typedef  void (*timerCallBack) (void);

typedef struct
{
	uint8_t u8_timerClock;		
	uint16_t u16_timer_InitialValue;			/* the pre-loaded value on Timer/Counter Register*/
	en_timer_interrupt_feature_t en_timer_ovf_int_enable;	/*timer interrupt mask-ability*/
}st_timer_config_t;


#endif /* TIMER_TYPES_H_ */