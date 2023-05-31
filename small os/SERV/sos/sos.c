/*
 * sos.c
 *
 * Created: 5/28/2023 8:04:18 PM
 *  Author: Mahmoud Sarhan
 */ 
#include "sos.h"
#include "../../HAL/timer_manager/timer_manager.h"

#define NOT_INIT		0
#define INIT			1
#define INVALID_TASK_ID	100
#define INVALID_TASK_PERIORITY	100
#define INVALID_TASK_PERIOD		65536
#define WAITING_STACK_SIZE		5


static st_task_config_t arr_st_gs_task_config[INVALID_TASK_ID] = {NULL};
static uint8_t u8_gs_arr_index_id[INVALID_TASK_ID]={NOT_INIT};
static uint8_t u8_gs_arr_index_periority[INVALID_TASK_PERIORITY]={NOT_INIT};
static uint8_t u8_gs_max_count_of_tasks = 1;
static uint8_t u8_gs_sos_module_state = NOT_INIT;
static uint16_t u16_sos_task_tick[100] = {NOT_INIT};
ptr_function_name_t ptr_function_wake_up_routine = NULL;




enu_system_status_t SOS_token_config_param(ptr_function_name_t ptr_function_name , uint8_t u8_task_id , uint8_t u8_task_periority);
void SOS_tick_cbf(void);
void SOS_rearrange_tasks(void);



enu_system_status_t SOS_init(void)
{
	enu_system_status_t enu_system_status_retVal = SOS_STATUS_SUCCESS;
	if (NOT_INIT == u8_gs_sos_module_state)
	{
		enu_system_status_retVal = TIMER_MANAGER_init(TIMER_0);
		enu_system_status_retVal = TIMER_MANAGER_set_cbk(SOS_tick_cbf,TIMER_0);
		u8_gs_sos_module_state = INIT;
		SOS_rearrange_tasks();
	}
	else
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	if (enu_system_status_retVal)
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	else
	{
		// do nothing
	}
	return enu_system_status_retVal;
}
enu_system_status_t SOS_deinit (void)
{
	enu_system_status_t enu_system_status_retVal = SOS_STATUS_SUCCESS;
	if (INIT == u8_gs_sos_module_state)
	{
		for(uint8_t i = 1 ; i < u8_gs_max_count_of_tasks ; i++)
		{
			//SOS_delete_task(i);
			u8_gs_arr_index_periority[arr_st_gs_task_config[i].u8_task_periority]=NOT_INIT;
			arr_st_gs_task_config[i].ptr_function_name = NULL;
			arr_st_gs_task_config[i].u8_task_periority = NOT_INIT;
			arr_st_gs_task_config[i].u16_task_period = NOT_INIT;
			u8_gs_arr_index_id[arr_st_gs_task_config[i].u8_task_id] = NOT_INIT;
			arr_st_gs_task_config[i].u8_task_id = NOT_INIT;
			u16_sos_task_tick[i] = NOT_INIT;
		}
		u8_gs_max_count_of_tasks = NOT_INIT;
		u8_gs_sos_module_state = NOT_INIT;
	}
	else
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	return enu_system_status_retVal;
}
enu_system_status_t SOS_create_task(ptr_function_name_t ptr_function_name , uint8_t u8_task_id , uint8_t u8_task_periority,uint16_t u16_task_period)
{
	enu_system_status_t enu_system_status_retVal = SOS_STATUS_SUCCESS;
	if ((NULL != ptr_function_name) && (INVALID_TASK_ID > u8_task_id) && (INVALID_TASK_PERIORITY > u8_task_periority) 
		&& (INVALID_TASK_PERIOD > u16_task_period) && (NULL == arr_st_gs_task_config[u8_gs_max_count_of_tasks].ptr_function_name) 
		&& (SOS_STATUS_INVALID_STATE != SOS_token_config_param(ptr_function_name,u8_task_id,u8_task_periority)))
	{
		
		arr_st_gs_task_config[u8_gs_max_count_of_tasks].ptr_function_name = ptr_function_name;
		arr_st_gs_task_config[u8_gs_max_count_of_tasks].u8_task_periority = u8_task_periority;
		arr_st_gs_task_config[u8_gs_max_count_of_tasks].u16_task_period = u16_task_period;
		arr_st_gs_task_config[u8_gs_max_count_of_tasks].u16_remain_time = u16_task_period;
		arr_st_gs_task_config[u8_gs_max_count_of_tasks].u8_task_id = u8_task_id;
		u8_gs_arr_index_periority[u8_task_periority]= u8_gs_max_count_of_tasks;
		u8_gs_arr_index_id[u8_task_id] = u8_gs_max_count_of_tasks;
		u8_gs_max_count_of_tasks++;
	}
	else
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	return enu_system_status_retVal;
}
enu_system_status_t SOS_delete_task(uint8_t u8_task_id)
{
	enu_system_status_t enu_system_status_retVal = SOS_STATUS_SUCCESS;
	if ((INIT == u8_gs_sos_module_state) && (NOT_INIT != u8_gs_arr_index_id[u8_task_id]))
	{
		u8_gs_arr_index_periority[arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].u8_task_periority]=NOT_INIT;
		arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].ptr_function_name = NULL;
		arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].u8_task_periority = NOT_INIT;
		arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].u16_task_period = NOT_INIT;
		arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].u8_task_id = NOT_INIT;
		u8_gs_arr_index_id[u8_task_id] = NOT_INIT;
		
		SOS_rearrange_tasks();
		
		u8_gs_max_count_of_tasks--;
	}
	else
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	return enu_system_status_retVal;
}
enu_system_status_t SOS_modify_task(uint8_t u8_task_id , uint8_t u8_task_periority,uint16_t u16_task_period)
{
	enu_system_status_t enu_system_status_retVal = SOS_STATUS_SUCCESS;
	if ((INIT == u8_gs_sos_module_state) && (NOT_INIT != u8_gs_arr_index_id[u8_task_id]) 
		&& (NOT_INIT == u8_gs_arr_index_periority[u8_task_periority]))
	{
		arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].u8_task_periority = u8_task_periority;
		arr_st_gs_task_config[u8_gs_arr_index_id[u8_task_id]].u16_task_period = u16_task_period;
		u8_gs_arr_index_periority[u8_task_periority]= u8_gs_arr_index_id[u8_task_id];
	}
	else
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	return enu_system_status_retVal;
}
void SOS_run(void)
{
	TIMER_MANAGER_start(TIMER_0);
	while(INIT == u8_gs_sos_module_state)
	{
		for(uint8_t i = 1 ; i  < u8_gs_max_count_of_tasks ; i++)
		{
			if (arr_st_gs_task_config[i].u16_task_period == u16_sos_task_tick[i])
			{
				(arr_st_gs_task_config[i].ptr_function_name)();
				u16_sos_task_tick[i] = 0;
			}
		}
	}
}
void SOS_disable(void)
{
	TIMER_MANAGER_stop(TIMER_0);
	while(NOT_INIT == u8_gs_sos_module_state)
	{
		(ptr_function_wake_up_routine)();
	}
}



enu_system_status_t SOS_token_config_param(ptr_function_name_t ptr_function_name , uint8_t u8_task_id , uint8_t u8_task_periority)
{
	enu_system_status_t enu_system_status_retVal = SOS_STATUS_SUCCESS;
	if ((NOT_INIT != u8_gs_arr_index_id[u8_task_id]) || (NOT_INIT != u8_gs_arr_index_periority[u8_task_periority]))
	{
		enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
	}
	else
	{
		for (uint8_t i = 0 ; i < u8_gs_max_count_of_tasks ; i++)
		{
			if (arr_st_gs_task_config[i].ptr_function_name == ptr_function_name)
			{
				enu_system_status_retVal = SOS_STATUS_INVALID_STATE;
				break;
			}
			else
			{
				// do nothing
			}
		}
	}
	return enu_system_status_retVal;
}



void SOS_rearrange_tasks(void)
{
	static st_task_config_t st_task_config;
	static uint8_t u8_s_tick_index = 0;
	for(uint8_t i = 1 ; i < u8_gs_max_count_of_tasks ; i++)
	{
		for(uint8_t j = i+1 ; j < u8_gs_max_count_of_tasks ; j++)
		{
			if ((arr_st_gs_task_config[i].u8_task_periority < arr_st_gs_task_config[j].u8_task_periority))
			{
				st_task_config.ptr_function_name = arr_st_gs_task_config[i].ptr_function_name;
				arr_st_gs_task_config[i].ptr_function_name = arr_st_gs_task_config[j].ptr_function_name;
				arr_st_gs_task_config[j].ptr_function_name = st_task_config.ptr_function_name;
				st_task_config.ptr_function_name = NULL;
				u8_s_tick_index = u16_sos_task_tick[i];
				u16_sos_task_tick[i] = u16_sos_task_tick[j];
				u16_sos_task_tick[j] = u8_s_tick_index;
				u8_s_tick_index = 0;
				
				st_task_config.u16_task_period = arr_st_gs_task_config[i].u16_task_period;
				arr_st_gs_task_config[i].u16_task_period = arr_st_gs_task_config[j].u16_task_period;
				arr_st_gs_task_config[j].u16_task_period = st_task_config.u16_task_period;
				st_task_config.u16_task_period = NOT_INIT;
				
				st_task_config.u8_task_id = arr_st_gs_task_config[i].u8_task_id;
				arr_st_gs_task_config[i].u8_task_id = arr_st_gs_task_config[j].u8_task_id;
				arr_st_gs_task_config[j].u8_task_id = st_task_config.u8_task_id;
				u8_gs_arr_index_id[arr_st_gs_task_config[i].u8_task_id] = i;
				u8_gs_arr_index_id[arr_st_gs_task_config[j].u8_task_id] = j;
				st_task_config.u8_task_id = NOT_INIT;
				
				st_task_config.u8_task_periority = arr_st_gs_task_config[i].u8_task_periority;
				arr_st_gs_task_config[i].u8_task_periority = arr_st_gs_task_config[j].u8_task_periority;
				arr_st_gs_task_config[j].u8_task_periority = st_task_config.u8_task_periority;
				st_task_config.u8_task_periority = NOT_INIT;
				
			}
		}
	}
}


void SOS_tick_cbf(void)
{
	for (uint8_t i = 1 ; i < u8_gs_max_count_of_tasks; i++)
	{
		if (u16_sos_task_tick[i] != arr_st_gs_task_config[i].u16_task_period)
		{
			u16_sos_task_tick[i]++;
		}
	}
}

void SOS_change_state(uint8_t u8_state)
{
	u8_gs_sos_module_state = u8_state;
}


void SOS_wake_up(ptr_function_name_t ptr_function_name)
{
	ptr_function_wake_up_routine = ptr_function_name;
}
void SOS_idle(void)
{
	
}