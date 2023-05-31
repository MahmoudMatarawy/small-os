/*
 * dio.c
 *
 * Created: 5/25/2023 10:09:40 PM
 *  Author: Mahmoud Sarhan
 */ 

#include "dio_private_reg.h"
#include "dio.h"



u8_dioErrors_t DIO_init (en_dioPorts_t port, en_dioPins_t pin, u8_dioDir_t direction)
{
	
	if (pin < DIO_MAX_PINS)
	{
		if (port == porta)
		{
			DATA_DIRECTION_PORTA |= direction << pin;
			return DIO_E_OK;
		}
		else if (port == portb)
		{
			DATA_DIRECTION_PORTB |= direction << pin;
			return DIO_E_OK;
		}
		else if (port == portc)
		{
			DATA_DIRECTION_PORTC |= direction << pin;
			return DIO_E_OK;
		}
		else if (port == portd)
		{
			DATA_DIRECTION_PORTD |= direction << pin;
			return DIO_E_OK;
		}
		else
		{
			return DIO_InvalidPort;
		}
		
	}
	else{
		return DIO_InvalidPin;
	}
}
u8_dioErrors_t DIO_writePIN (en_dioPorts_t port, en_dioPins_t pin, u8_dioLevel_t state)
{
	if (pin < DIO_MAX_PINS)
	{
		if (port == porta)
		{
			if (state == STD_HIGH)
			{
				WR_PORT_A |= (1U << pin);
			}
			else{
				WR_PORT_A &= ~(1U << pin);
			}
			return DIO_E_OK;
		}
		else if (port == portb)
		{
			if (state == STD_HIGH)
			{
				WR_PORT_B |= (1U << pin);
			}
			else{
				WR_PORT_B &= ~(1U << pin);
			}
			return DIO_E_OK;
		}
		else if (port == portc)
		{
			if (state == STD_HIGH)
			{
				WR_PORT_C |= (1U << pin);
			}
			else{
				WR_PORT_C &= ~(1U << pin);
			}
			return DIO_E_OK;
		}
		else if (port == portd)
		{
			if (state == STD_HIGH)
			{
				WR_PORT_D |= (1U << pin);
			}
			else{
				WR_PORT_D &= ~(1U << pin);
			}
			return DIO_E_OK;
		}
		else
		{
			return DIO_InvalidPort;
		}
		
	}
	else{
		return DIO_InvalidPin;
	}
}
u8_dioErrors_t DIO_readPIN (en_dioPorts_t port, en_dioPins_t pin, u8_dioLevel_t* value)
{
	if (pin < DIO_MAX_PINS)
	{
		if (port == porta)
		{
			*value = ((RE_PORT_A & (1U<<pin))>>pin);
			return DIO_E_OK;
		}
		else if (port == portb)
		{
			*value = ((RE_PORT_B & (1U<<pin))>>pin);
			return DIO_E_OK;
		}
		else if (port == portc)
		{
			*value = ((RE_PORT_C & (1U<<pin))>>pin);
			return DIO_E_OK;
		}
		else if (port == portd)
		{
			*value = ((RE_PORT_D & (1U<<pin))>>pin);
			return DIO_E_OK;
		}
		else
		{
			return DIO_InvalidPort;
		}
		
	}
	else{
		return DIO_InvalidPin;
	}
}