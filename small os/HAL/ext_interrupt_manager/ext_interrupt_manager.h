/*
 * ext_interrupt_manager.h
 *
 * Created: 5/30/2023 12:57:59 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef EXT_INTERRUPT_MANAGER_H_
#define EXT_INTERRUPT_MANAGER_H_

#include "../../MCAL/ext_interrupt/ext_interrupt.h"

u8_interruptError_t EXT_INTERRUPT_MANAGER_init(en_ext_interrupt_num_t en_ext_interrupt_num,void(*callback)(void));
u8_interruptError_t EXT_INTERRUPT_MANAGER_enable(en_ext_interrupt_num_t en_ext_interrupt_num);
u8_interruptError_t EXT_INTERRUPT_MANAGER_disable(en_ext_interrupt_num_t en_ext_interrupt_num);


#endif /* EXT_INTERRUPT_MANAGER_H_ */