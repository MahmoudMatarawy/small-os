/*
 * sos_types.h
 *
 * Created: 5/28/2023 10:07:32 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef SOS_TYPES_H_
#define SOS_TYPES_H_
#include "../../STD_LIB/std_types.h"
typedef enum
{
	SOS_STATUS_SUCCESS = 0,
	SOS_STATUS_INVALID_STATE = 7
}enu_system_status_t;

typedef  void (*ptr_function_name_t) (void);

typedef struct
{
	ptr_function_name_t ptr_function_name;
	uint8_t u8_task_id;
	uint8_t u8_task_periority;
	uint16_t u16_task_period;
	uint16_t u16_remain_time;
}st_task_config_t;



#endif /* SOS_TYPES_H_ */