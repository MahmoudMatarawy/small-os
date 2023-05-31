/*
 * dio_cfg.h
 *
 * Created: 5/25/2023 10:13:50 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef DIO_PRIVATE_REG_H_
#define DIO_PRIVATE_REG_H_

//#include <avr/io.h>

#define DIO_MAX_PINS	8
#define DIO_MAX_PORTS	4

#define  DATA_DIRECTION_PORTA	(*((volatile uint8_t *) 0x3A))
#define  DATA_DIRECTION_PORTB	(*((volatile uint8_t *) 0x37))
#define  DATA_DIRECTION_PORTC	(*((volatile uint8_t *) 0x34))
#define  DATA_DIRECTION_PORTD	(*((volatile uint8_t *) 0x31))


#define  WR_PORT_A					(*((volatile uint8_t *) 0x3B))
#define  WR_PORT_B					(*((volatile uint8_t *) 0x38))
#define  WR_PORT_C					(*((volatile uint8_t *) 0x35))
#define  WR_PORT_D					(*((volatile uint8_t *) 0x32))




#define  RE_PORT_A					(*((volatile uint8_t *) 0x39))
#define  RE_PORT_B					(*((volatile uint8_t *) 0x36))
#define  RE_PORT_C					(*((volatile uint8_t *) 0x33))
#define  RE_PORT_D					(*((volatile uint8_t *) 0x30))

#endif /* DIO_PRIVATE_REG_H_ */