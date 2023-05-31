/*
 * sos.h
 *
 * Created: 5/28/2023 8:04:04 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef SOS_H_
#define SOS_H_


#include "sos_types.h"


enu_system_status_t SOS_init(void);
enu_system_status_t SOS_deinit (void);
enu_system_status_t SOS_create_task(ptr_function_name_t ptr_function_name , uint8_t u8_task_id , uint8_t u8_task_periority,uint16_t u16_task_period);
enu_system_status_t SOS_delete_task(uint8_t u8_task_id);
enu_system_status_t SOS_modify_task(uint8_t u8_task_id , uint8_t u8_task_periority,uint16_t u16_task_period);
void SOS_run(void);
void SOS_disable(void);
void SOS_change_state(uint8_t u8_state);
void SOS_wake_up(ptr_function_name_t ptr_function_name);
#endif /* SOS_H_ */