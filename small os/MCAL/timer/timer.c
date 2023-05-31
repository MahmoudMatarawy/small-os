/*
 * timer.c
 *
 * Created: 5/28/2023 2:02:53 PM
 *  Author: Mahmoud Sarhan
 */ 


#include "timer.h"
#include "timer_private_reg.h"
#include "timer_pre_linking_cfg.h"
#include "../../STD_LIB/interrupt.h"
#include "../../STD_LIB/bit_math.h"

#define NOT_INIT			0x00
#define INIT				0x01


extern st_timer_config_t st_timer_0_config;
extern st_timer_config_t st_timer_1_config;
extern st_timer_config_t st_timer_2_config;

static uint8_t u8_gs_timer_0_state = NOT_INIT;
static uint8_t u8_gs_timer_1_state = NOT_INIT;
static uint8_t u8_gs_timer_2_state = NOT_INIT;

/* Global pointers to function to hold the address of the call back function in the upper layers */
static timerCallBack v_gs_arr_ptr_Timer_callBack[INVALID_TIMER_NUM+1] = {NULL};






ISR(TIMER0_OVF)
{
	if(NULL != v_gs_arr_ptr_Timer_callBack[TIMER_0])
	{
		//Call the Call Back function in the upper layer after the timer overflow
		(v_gs_arr_ptr_Timer_callBack[TIMER_0])();
		
		// reset the timer value with the configured value
		TCNT0 = st_timer_0_config.u16_timer_InitialValue & U8_BIT_REG_MASK;
	}
}


ISR(TIMER1_OVF)
{
	if(NULL != v_gs_arr_ptr_Timer_callBack[TIMER_1])
	{
		// Call the Call Back function in the upper layer after the timer overflow
		(v_gs_arr_ptr_Timer_callBack[TIMER_1])();
		// reset the timer value with the configured value
		TCNT1 = st_timer_1_config.u16_timer_InitialValue;
	}
}



ISR(TIMER2_OVF)
{
	if(NULL != v_gs_arr_ptr_Timer_callBack[TIMER_2])
	{
		// Call the Call Back function in the upper layer after the timer overflow
		(v_gs_arr_ptr_Timer_callBack[TIMER_2])();
		// reset the timer value with the configured value
		TCNT2 = st_timer_2_config.u16_timer_InitialValue & U8_BIT_REG_MASK;
	}
}



u8_timerErrors_t TIMER_init(en_timer_num_t en_timerNum)
{
	u8_timerErrors_t u8_timerErrors_retVal = TIMER_E_OK;
	
	if (INVALID_TIMER_NUM > en_timerNum)
	{
		switch(en_timerNum)
		{
			case  TIMER_0:
			{
				if (INVALID_TIMER_CLK == st_timer_0_config.u8_timerClock || NO_CLOCK == st_timer_0_config.u8_timerClock)
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					/*Configure initial value in TCNT0 for Timer0 to start count from it*/
					TCNT0 = st_timer_0_config.u16_timer_InitialValue & U8_BIT_REG_MASK;
					/*Make FOC0 to be Active as it is overflow mode(for non-PWM mode)*/
					SET_BIT(TCCR0,FOC0);
					if(TIMER_INTERRUPT_FEATURE_ENABLE==st_timer_0_config.en_timer_ovf_int_enable)
					{
						/* Enable Timer0 overflow interrupt*/
						SET_BIT(TIMSK,TOIE0);
					}
					else
					{
						// DO NOTHING
					}
					u8_gs_timer_0_state = INIT;
				}
				break;
			}
			case TIMER_1:
			{
				if (INVALID_TIMER_CLK == st_timer_1_config.u8_timerClock || NO_CLOCK == st_timer_1_config.u8_timerClock)
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					/*Configure initial value in TCNT1(high&low) for Timer0 to start count from it*/
					TCNT1 = st_timer_1_config.u16_timer_InitialValue;
					/*Configure the TIMER1 with normal  mode value and enable the interrupt for this mode if interrupt feature activated */
					/*Make FOC1A,FOC1B to be Active as it is overflow mode(for non-PWM mode)*/
					SET_BIT(TCCR1A,FOC1A);
					SET_BIT(TCCR1A,FOC1B);
					if(TIMER_INTERRUPT_FEATURE_ENABLE==st_timer_1_config.en_timer_ovf_int_enable)
					{
						/* Enable Timer1 overflow interrupt*/
						SET_BIT(TIMSK,TOIE1);
					}
					else
					{
						// DO NOTHING
					}
					u8_gs_timer_1_state = INIT;
				}
				break;
			}
			case TIMER_2:
			{
				if (INVALID_TIMER_CLK == st_timer_2_config.u8_timerClock || TIMER_2_NO_CLOCK == st_timer_2_config.u8_timerClock)
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					/*Configure initial value in TCNT for Timer2 to start count from it*/
					TCNT2 = st_timer_2_config.u16_timer_InitialValue & U8_BIT_REG_MASK;
					/*Make FOC2 to be Active as it is overflow mode(for non-PWM mode)*/
					SET_BIT(TCCR2,FOC2);
					if(TIMER_INTERRUPT_FEATURE_ENABLE== st_timer_2_config.en_timer_ovf_int_enable)
					{
						/* Enable Timer2 overflow interrupt*/
						SET_BIT(TIMSK,TOIE2);
					}
					else
					{
						// DO NOTHING
					}
					u8_gs_timer_2_state = INIT;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		u8_timerErrors_retVal = TIMER_E_NOT_OK;
	}
	return u8_timerErrors_retVal;
}
u8_timerErrors_t TIMER_start(en_timer_num_t en_timerNum)
{
	u8_timerErrors_t u8_timerErrors_retVal = TIMER_E_OK;
	
	if (INVALID_TIMER_NUM > en_timerNum)
	{
		switch(en_timerNum)
		{
			case TIMER_0:
			{
				if (NOT_INIT == u8_gs_timer_0_state || NO_CLOCK == st_timer_0_config.u8_timerClock )
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					TCCR0 = st_timer_0_config.u8_timerClock;
				}
				break;
			}
			case TIMER_1:
			{
				if (NOT_INIT == u8_gs_timer_1_state || NO_CLOCK == st_timer_1_config.u8_timerClock )
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					TCCR1B = st_timer_1_config.u8_timerClock;
				}
				break;
			}
			case TIMER_2:
			{
				if (NOT_INIT == u8_gs_timer_2_state || TIMER_2_NO_CLOCK == st_timer_2_config.u8_timerClock )
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					TCCR2 = st_timer_2_config.u8_timerClock;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		u8_timerErrors_retVal = TIMER_E_NOT_OK;
	}
	return u8_timerErrors_retVal;
}
u8_timerErrors_t TIMER_stop(en_timer_num_t en_timerNum)
{
	u8_timerErrors_t u8_timerErrors_retVal = TIMER_E_OK;
	if (INVALID_TIMER_NUM > en_timerNum)
	{
		switch(en_timerNum)
		{
			case TIMER_0:
			{
				if (NOT_INIT == u8_gs_timer_0_state || NO_CLOCK == st_timer_0_config.u8_timerClock )
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					TCCR0 = NO_CLOCK;
				}
				break;
			}
			case TIMER_1:
			{
				if (NOT_INIT == u8_gs_timer_1_state || NO_CLOCK == st_timer_1_config.u8_timerClock )
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					TCCR1B = NO_CLOCK;
				}
				break;
			}
			case TIMER_2:
			{
				if (NOT_INIT == u8_gs_timer_2_state || TIMER_2_NO_CLOCK == st_timer_2_config.u8_timerClock )
				{
					u8_timerErrors_retVal = TIMER_E_NOT_OK;
				}
				else
				{
					TCCR2 = TIMER_2_NO_CLOCK;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		u8_timerErrors_retVal = TIMER_E_NOT_OK;
	}
	return u8_timerErrors_retVal;
}



u8_timerErrors_t TIMER_set_cbk(timerCallBack callBackFunction_ptr,en_timer_num_t en_timerNum)
{
	u8_timerErrors_t u8_timerErrors_retVal = TIMER_E_OK;
	if (INVALID_TIMER_NUM > en_timerNum && NULL != callBackFunction_ptr)
	{
		v_gs_arr_ptr_Timer_callBack[en_timerNum] = callBackFunction_ptr;
	}
	else
	{
		u8_timerErrors_retVal = TIMER_E_NOT_OK;
	}
	return u8_timerErrors_retVal;
}


