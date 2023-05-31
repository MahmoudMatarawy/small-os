/*
 * led.h
 *
 * Created: 5/25/2023 10:07:43 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../STD_LIB/std_types.h"


typedef uint8_t u8_ledError_t;

#define LED_ERROR_OK			((u8_ledError_t)0x00)
#define LED_ERROR_NOT_OK		((u8_ledError_t)0x05)

typedef enum
{
	LED_0 = 0,
	LED_1,
	INVALID_LED
	}en_ledNum_t;

u8_ledError_t LED_init(en_ledNum_t ledNum);
u8_ledError_t LED_on(en_ledNum_t ledNum);
u8_ledError_t LED_off(en_ledNum_t ledNum);
u8_ledError_t LED_toggle(en_ledNum_t ledNum);

#endif /* LED_H_ */