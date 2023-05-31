/*
 * timer_manager.c
 *
 * Created: 5/28/2023 10:30:24 PM
 *  Author: Mahmoud Sarhan
 */ 
#include "timer_manager.h"
#include "../../MCAL/timer/timer.h"




u8_timerErrors_t TIMER_MANAGER_init(en_timer_num_t en_timerNum)
{
	return TIMER_init(en_timerNum);
}
u8_timerErrors_t TIMER_MANAGER_start(en_timer_num_t en_timerNum)
{
	return TIMER_start(en_timerNum);
}
u8_timerErrors_t TIMER_MANAGER_stop(en_timer_num_t en_timerNum)
{
	return TIMER_stop(en_timerNum);
}
u8_timerErrors_t TIMER_MANAGER_set_cbk(timerCallBack callBackFunction_ptr,en_timer_num_t en_timerNum)
{
	return TIMER_set_cbk(callBackFunction_ptr,en_timerNum);
}