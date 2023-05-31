/*
 * ext_interrupt_pre_linking_cfg.h
 *
 * Created: 5/30/2023 12:18:15 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef EXT_INTERRUPT_PRE_LINKING_CFG_H_
#define EXT_INTERRUPT_PRE_LINKING_CFG_H_

#include "ext_interrupt_types.h"

const en_edge_detection_t arr_en_gc_edge_detection[INVALID_EXT_INT] = {
	FALLING_EDGE,
	FALLING_EDGE,
	FALLING_EDGE
};

#endif /* EXT_INTERRUPT_PRE_LINKING_CFG_H_ */