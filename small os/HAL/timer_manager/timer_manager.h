/*
 * timer_manager.h
 *
 * Created: 5/28/2023 10:30:07 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_
#include "../../MCAL/timer/timer_types.h"



u8_timerErrors_t TIMER_MANAGER_init(en_timer_num_t en_timerNum);
u8_timerErrors_t TIMER_MANAGER_start(en_timer_num_t en_timerNum);
u8_timerErrors_t TIMER_MANAGER_stop(en_timer_num_t en_timerNum);
u8_timerErrors_t TIMER_MANAGER_set_cbk(timerCallBack callBackFunction_ptr,en_timer_num_t en_timerNum);



#endif /* TIMER_MANAGER_H_ */