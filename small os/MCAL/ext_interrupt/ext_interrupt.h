/*
 * ext_interrupt.h
 *
 * Created: 5/30/2023 12:02:31 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_


#include "ext_interrupt_types.h"


u8_interruptError_t EXT_INTERRUPT_init(en_ext_interrupt_num_t en_ext_interrupt_num);
u8_interruptError_t EXT_INTERRUPT_enable(en_ext_interrupt_num_t en_ext_interrupt_num);
u8_interruptError_t EXT_INTERRUPT_disable(en_ext_interrupt_num_t en_ext_interrupt_num);
u8_interruptError_t EXT_INTERRUPT_set_callback_init(en_ext_interrupt_num_t en_ext_interrupt_num ,void(*callback)(void));
#endif /* EXT_INTERRUPT_H_ */