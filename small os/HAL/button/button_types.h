/*
 * button_types.h
 *
 * Created: 5/30/2023 2:41:14 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef BUTTON_TYPES_H_
#define BUTTON_TYPES_H_


#include "../../STD_LIB/std_types.h"

// Create Button Level ENUM
typedef enum
{
	BT_PUSH_LEVEL = 0,
	BT_RELEASE_LEVEL
	}en_btnLevel_t;



// Create ButtonID ENUM
typedef enum
{
	Button_Start = 0,
	INVALID_BUTTON_ID
	}en_btnId_t;



// Create Button State ENUM
typedef enum
{
	BT_PRE_PUSH = 0 ,
	BT_PUSHED,
	BT_PRE_HOLD,
	BT_HOLD,
	BT_PRE_RELEASE,
	BT_RELEASED,
	BT_UNDEFINED
	}en_btnState_t;


typedef struct{
	uint8_t u8_a_port;
	uint8_t u8_a_pin;
	uint8_t u8_a_ID;
	uint8_t u8_a_debounceThreshold;
	uint8_t u8_a_holdThreshold;
	en_btnState_t u8_a_btnState;
}st_btnConfig_t;



#endif /* BUTTON_TYPES_H_ */