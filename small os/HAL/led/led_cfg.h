/*
 * led_cfg.h
 *
 * Created: 5/25/2023 10:08:04 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef LED_CFG_H_
#define LED_CFG_H_

#include "../../MCAL/dio/dio.h"


typedef struct
{
	en_dioPorts_t port;
	en_dioPins_t pin;
}st_ledConfig_t;

const st_ledConfig_t st_gc_ledConfig[2]={
	{
		.port = porta,
		.pin = pin0
	},
	{
		.port = porta,
		.pin = pin1
	}
};


#endif /* LED_CFG_H_ */