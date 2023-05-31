/*
 * button_pre_linking_cfg.h
 *
 * Created: 5/30/2023 2:46:59 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef BUTTON_PRE_LINKING_CFG_H_
#define BUTTON_PRE_LINKING_CFG_H_

#include "button_types.h"

const st_btnConfig_t arr_st_gc_btnConfig[INVALID_BUTTON_ID] = {
	{
		.u8_a_ID = 1,
		.u8_a_pin = pin3,
		.u8_a_port = portd,
		.u8_a_debounceThreshold = 20,
		.u8_a_holdThreshold = 20,
		.u8_a_btnState = BT_PRE_PUSH
	}
};



#endif /* BUTTON_PRE_LINKING_CFG_H_ */