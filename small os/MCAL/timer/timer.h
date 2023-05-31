/*
 * timer.h
 *
 * Created: 5/28/2023 2:02:39 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "timer_types.h"





u8_timerErrors_t TIMER_init(en_timer_num_t en_timerNum);
u8_timerErrors_t TIMER_start(en_timer_num_t en_timerNum);
u8_timerErrors_t TIMER_stop(en_timer_num_t en_timerNum);
u8_timerErrors_t TIMER_set_cbk(timerCallBack callBackFunction_ptr,en_timer_num_t en_timerNum);


#endif /* TIMER_H_ */