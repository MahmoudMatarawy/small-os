/*
 * timer_pre_linking_cfg.h
 *
 * Created: 5/28/2023 2:03:21 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef TIMER_PRE_LINKING_CFG_H_
#define TIMER_PRE_LINKING_CFG_H_

#include "timer_types.h"

st_timer_config_t st_timer_0_config = {
	.u8_timerClock = F_CPU_64,
	.u16_timer_InitialValue = 131,
	.en_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_ENABLE
};


st_timer_config_t st_timer_1_config = {
	.u8_timerClock = INVALID_TIMER_CLK,
	.u16_timer_InitialValue = 0,
	.en_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_DISABLE
};



st_timer_config_t st_timer_2_config = {
	.u8_timerClock = TIMER_2_INVALID_TIMER_CLK,
	.u16_timer_InitialValue = 0,
	.en_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_DISABLE
};
#endif /* TIMER_PRE_LINKING_CFG_H_ */