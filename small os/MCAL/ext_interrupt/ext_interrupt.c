/*
 * ext_interrupt.c
 *
 * Created: 5/30/2023 12:02:47 AM
 *  Author: Mahmoud Sarhan
 */ 
#include "ext_interrupt.h"
#include "../../STD_LIB/interrupt.h"
#include "ext_interrupt_private_reg.h"
#include "ext_interrupt_pre_linking_cfg.h"

#define NOT_INIT		0
#define INIT			1

static void (*callback_EXT_0)(void);
static void (*callback_EXT_1)(void);
static void (*callback_EXT_2)(void);

extern const en_edge_detection_t arr_en_gc_edge_detection[INVALID_EXT_INT];

static uint8_t u8_gs_ext_int_state[INVALID_EXT_INT] = {NOT_INIT};

u8_interruptError_t EXT_INTERRUPT_init(en_ext_interrupt_num_t en_ext_interrupt_num)
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	if ((INVALID_EXT_INT == en_ext_interrupt_num) || (INVALID_EDGE == arr_en_gc_edge_detection[en_ext_interrupt_num]))
	{
		u8_interruptError_retVal = EXT_INT_E_NOK;
	}
	else
	{
		switch (en_ext_interrupt_num)
		{
			case EXT_0:
			{
				MCUCR_ADD |= arr_en_gc_edge_detection[EXT_0];
				SREG_ADD |= Globle_INT;
				u8_gs_ext_int_state[EXT_0] = INIT;
				break;
			}

			case EXT_1:
			{
				MCUCR_ADD |= (arr_en_gc_edge_detection[EXT_1]<<2);
				SREG_ADD |= (1<<Globle_INT);
				u8_gs_ext_int_state[EXT_1] = INIT;
				break;
			}

			case EXT_2:
			{
				/* code */
				break;
			}

			default:
			{
				break;
			}
		}
	}
	return u8_interruptError_retVal;
}




u8_interruptError_t EXT_INTERRUPT_enable(en_ext_interrupt_num_t en_ext_interrupt_num)
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	if ((INVALID_EXT_INT == en_ext_interrupt_num) || (NOT_INIT == u8_gs_ext_int_state[en_ext_interrupt_num]))
	{
		u8_interruptError_retVal = EXT_INT_E_NOK;
	}
	else
	{
		switch (en_ext_interrupt_num)
		{
			case EXT_0:
			{
				GICR_ADD |= (INIT<<INT0_Globle);
				break;
			}
			case EXT_1:
			{
				GICR_ADD |= (INIT<<INT1_Globle);
				break;
			}
			case EXT_2:
			{
				/* code */
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return u8_interruptError_retVal;
}



u8_interruptError_t EXT_INTERRUPT_disable(en_ext_interrupt_num_t en_ext_interrupt_num)
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	if ((INVALID_EXT_INT == en_ext_interrupt_num) || (NOT_INIT == u8_gs_ext_int_state[en_ext_interrupt_num]))
	{
		u8_interruptError_retVal = EXT_INT_E_NOK;
	}
	else
	{
		switch (en_ext_interrupt_num)
		{
			case EXT_0:
			{
				GICR_ADD &= ~(INIT<<INT0_Globle);
				break;
			}
			case EXT_1:
			{
				GICR_ADD &= ~(INIT<<INT1_Globle);
				break;
			}
			case EXT_2:
			{
				/* code */
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return u8_interruptError_retVal;
}




u8_interruptError_t EXT_INTERRUPT_set_callback_init(en_ext_interrupt_num_t en_ext_interrupt_num ,void(*callback)(void))
{
	u8_interruptError_t u8_interruptError_retVal = EXT_INT_E_OK;
	u8_interruptError_retVal = EXT_INTERRUPT_disable(en_ext_interrupt_num);
	if (u8_interruptError_retVal)
	{
		// do nothing
	}
	else
	{
		switch(en_ext_interrupt_num)
		{
			case EXT_0:
			{
				callback_EXT_0 = callback;
				break;
			}
			case EXT_1:
			{
				callback_EXT_1 = callback;
				break;
			}
			case EXT_2:
			{
				callback_EXT_2 = callback;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return u8_interruptError_retVal;
}



/*
*   -Description-
*-interrupt service routine for  external interrupt 0
*
*/
ISR(EXT_INT0)
{
	(callback_EXT_0)();
}


/*
*   -Description-
*-interrupt service routine for  external interrupt10
*
*/
ISR(EXT_INT1)
{
	(callback_EXT_1)();
}

/*
*   -Description-
*-interrupt service routine for  external interrupt 2
*
*/
ISR(EXT_INT2)
{
	(callback_EXT_2)();
}