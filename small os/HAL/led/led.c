/*
 * led.c
 *
 * Created: 5/25/2023 10:07:29 PM
 *  Author: Mahmoud Sarhan
 */ 

#include "led.h"
#include "led_cfg.h"
#include "../../MCAL/dio/dio.h"



#define NOT_INIT	0
#define ON			2
#define OFF			3

extern const st_ledConfig_t st_gc_ledConfig[2];

static uint8_t u8_ledState[INVALID_LED] = {NOT_INIT,NOT_INIT};
	
	
u8_ledError_t LED_init(en_ledNum_t ledNum)
{
	uint8_t u8_retVal = LED_ERROR_OK;
	if (ledNum < INVALID_LED)
	{
		u8_retVal = DIO_init(st_gc_ledConfig[ledNum].port , st_gc_ledConfig[ledNum].pin , STD_OUTPUT);
		u8_ledState[ledNum] = OFF;
	}
	else{
		u8_retVal = LED_ERROR_NOT_OK;
	}
	
	return u8_retVal;
}
u8_ledError_t LED_on(en_ledNum_t ledNum)
{
	uint8_t u8_retVal = LED_ERROR_OK;
	if (ledNum < INVALID_LED)
	{
		if (u8_ledState[ledNum] == OFF)
		{
			u8_retVal = DIO_writePIN(st_gc_ledConfig[ledNum].port , st_gc_ledConfig[ledNum].pin , STD_HIGH);
			u8_ledState[ledNum] = ON ;
		}
		else if (u8_ledState[ledNum] == ON)
		{
			// Do nothing
		}
		else{
			u8_retVal = LED_ERROR_NOT_OK;
		}
	}
	else{
		u8_retVal = LED_ERROR_NOT_OK;
	}
	return u8_retVal;
}
u8_ledError_t LED_off(en_ledNum_t ledNum)
{
	uint8_t u8_retVal = LED_ERROR_OK;
	if (ledNum < INVALID_LED)
	{
		if (u8_ledState[ledNum] == ON)
		{
			u8_retVal = DIO_writePIN(st_gc_ledConfig[ledNum].port , st_gc_ledConfig[ledNum].pin , STD_LOW);
			u8_ledState[ledNum] = OFF ;
		}
		else if (u8_ledState[ledNum] == OFF)
		{
			// Do nothing
		}
		else{
			u8_retVal = LED_ERROR_NOT_OK;
		}
	}
	else{
		u8_retVal = LED_ERROR_NOT_OK;
	}
	return u8_retVal;
}

u8_ledError_t LED_toggle(en_ledNum_t ledNum)
{
	uint8_t u8_retVal = LED_ERROR_OK;
	if (ledNum < INVALID_LED)
	{
		if (u8_ledState[ledNum] == ON)
		{
			u8_retVal = DIO_writePIN(st_gc_ledConfig[ledNum].port , st_gc_ledConfig[ledNum].pin , STD_LOW);
			u8_ledState[ledNum] = OFF ;
		}
		else if (u8_ledState[ledNum] == OFF)
		{
			u8_retVal = DIO_writePIN(st_gc_ledConfig[ledNum].port , st_gc_ledConfig[ledNum].pin , STD_HIGH);
			u8_ledState[ledNum] = ON ;
		}
		else{
			u8_retVal = LED_ERROR_NOT_OK;
		}
	}
	else{
		u8_retVal = LED_ERROR_NOT_OK;
	}
	return u8_retVal;
}