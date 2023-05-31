/*
 * dio.h
 *
 * Created: 5/25/2023 10:09:18 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../STD_LIB/std_types.h"


typedef enum 
{
	porta, portb, portc, portd
} en_dioPorts_t;
typedef enum 
{
	pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7
} en_dioPins_t;


// DIO Level type ENUM
typedef uint8_t u8_dioLevel_t;

#define STD_LOW					((u8_dioLevel_t)0x00)
#define STD_HIGH				((u8_dioLevel_t)0x01)


// DIO Errors 
typedef uint8_t u8_dioErrors_t;

#define DIO_E_OK				((u8_dioErrors_t)0x00)
#define DIO_InvalidPin			((u8_dioErrors_t)0x01)
#define DIO_InvalidPort			((u8_dioErrors_t)0x02)


// DIO DIR type 
typedef uint8_t u8_dioDir_t;

#define STD_INPUT					((u8_dioDir_t)0x00)
#define STD_OUTPUT					((u8_dioDir_t)0x01)

u8_dioErrors_t DIO_init (en_dioPorts_t port, en_dioPins_t pin, u8_dioDir_t direction);
u8_dioErrors_t DIO_writePIN (en_dioPorts_t port, en_dioPins_t pin, u8_dioLevel_t state);
u8_dioErrors_t DIO_readPIN (en_dioPorts_t port, en_dioPins_t pin, u8_dioLevel_t* value);



#endif /* DIO_H_ */