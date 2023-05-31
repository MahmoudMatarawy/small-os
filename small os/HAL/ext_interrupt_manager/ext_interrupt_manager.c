/*
 * ext_interrupt_manager.c
 *
 * Created: 5/30/2023 12:58:21 AM
 *  Author: Mahmoud Sarhan
 */ 
#include "ext_interrupt_manager.h"

u8_interruptError_t EXT_INTERRUPT_MANAGER_init(en_ext_interrupt_num_t en_ext_interrupt_num,void(*callback)(void))
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	u8_interruptError_retVal = EXT_INTERRUPT_init(en_ext_interrupt_num);
	u8_interruptError_retVal = EXT_INTERRUPT_set_callback_init(en_ext_interrupt_num,callback);
	return u8_interruptError_retVal;
}
u8_interruptError_t EXT_INTERRUPT_MANAGER_enable(en_ext_interrupt_num_t en_ext_interrupt_num)
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	u8_interruptError_retVal = EXT_INTERRUPT_enable(en_ext_interrupt_num);
	return u8_interruptError_retVal;
}
u8_interruptError_t EXT_INTERRUPT_MANAGER_disable(en_ext_interrupt_num_t en_ext_interrupt_num)
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	u8_interruptError_retVal = EXT_INTERRUPT_disable(en_ext_interrupt_num);
	return u8_interruptError_retVal;
}
