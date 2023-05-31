/*
 * bit_math.h
 *
 * Created: 5/25/2023 10:17:44 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#include "std_types.h"

/*mask 1-bit (LSB)*/
#define BIT_MASK  (uint8_t)1
/*mask 8-bit_reg*/
#define U8_BIT_REG_MASK           ((uint8_t)0xFF)
#define U16_BIT_REG_MASK          ((uint16_t)0xFFFF)

#define  FLAG_IS_SET	    (uint8_t)1
#define  U8_ZERO_INITIALIZE (uint8_t)0

/*set a certain bit in a 8-bit register*/
#define SET_BIT(REG,BIT_POSN)    (REG |=  (BIT_MASK << BIT_POSN))
/*reset a certain bit in a 8-bit register*/
#define CLEAR_BIT(REG,BIT_POSN)  (REG &= ~(BIT_MASK << BIT_POSN))
/*toggle a certain bit in a 8-bit register*/
#define TOGGLE_BIT(REG,BIT_POS)  (REG ^=  (BIT_MASK << BIT_POS) )
/*read a certain bit in a 8-bit register*/
//#define READ_BIT(REG,BIT_POS)    ((REG >> BIT_POS) & (BIT_MASK) )
#define READ_BIT(REG,BIT_POS)    ((REG & (BIT_MASK<<BIT_POS)) >> BIT_POS)

#define CLEAR_REG(REG)		(REG = ((uint8_t)0x00))

#endif /* BIT_MATH_H_ */