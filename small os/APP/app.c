/*
 * app.c
 *
 * Created: 5/28/2023 8:04:42 PM
 *  Author: Mahmoud Sarhan
 */ 
//#include <avr/io.h>
#include "app.h"
#include "../SERV/sos/sos.h"
#include "../HAL/led/led.h"
#include "../STD_LIB/interrupt.h"
#include "../HAL/ext_interrupt_manager/ext_interrupt_manager.h"
#include "../HAL/button/button.h"

#define NOT_INIT	0
#define INIT		1


typedef void (* APP_runing_task_t) (void);

static APP_runing_task_t APP_runing_task = SOS_run;


void APP_ext_int0_cbf(void);
void APP_wake_up_cbf(void);
 
void TASK_1(void)
{
	LED_toggle(LED_0);
}

void TASK_2(void)
{
	LED_toggle(LED_1);
}

void TASK_3(void)
{
	SOS_deinit();
	//SOS_delete_task(2);
	//LED_off(LED_1);
}

void APP_init(void)
{
	LED_init(LED_0);
	LED_init(LED_1);
	SOS_create_task(
	TASK_1,						// Function name
	1,							// ID
	1,							// priority
	300							// period
	);
	
	SOS_create_task(
	TASK_2,						// Function name
	2,							// ID
	3,							// priority
	500							// period
	);
	
	/*SOS_create_task(
	TASK_3,						// Function name
	3,							// ID
	2,							// priority
	5000							// period
	);*/
	SOS_init();
	EXT_INTERRUPT_MANAGER_init(EXT_0,APP_ext_int0_cbf);
	sei();
	EXT_INTERRUPT_MANAGER_enable(EXT_0);
	BUTTON_init(Button_Start);
	SOS_wake_up(APP_wake_up_cbf);
	//PORTB = 7;
}

void APP_start(void)
{
	while(1)
	{
		(APP_runing_task)();
	}
}



void APP_ext_int0_cbf(void)
{
	//x++;
	APP_runing_task = SOS_disable;
	SOS_change_state(NOT_INIT);
	EXT_INTERRUPT_MANAGER_disable(EXT_0);
	LED_off(LED_0);
	LED_off(LED_1);
}


void APP_wake_up_cbf(void)
{
	static uint8_t u8_btn_state = 0;
	BUTTON_mainTask();
	u8_btn_state = BUTTON_getState(Button_Start);
	if (u8_btn_state == BT_RELEASED)
	{
		APP_runing_task = SOS_run;
		SOS_change_state(INIT);
		EXT_INTERRUPT_MANAGER_enable(EXT_0);
	}
}
