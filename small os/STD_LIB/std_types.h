/*
 * std_types.h
 *
 * Created: 5/25/2023 10:17:31 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

#define NULL    ((void*)0)


#ifndef __STDINT_H_
#define __STDINT_H_
typedef unsigned char         uint8_t;          /*           0 .. 255             */
typedef signed char           sint8_t;          /*        -128 .. +127            */
typedef unsigned short        uint16_t;         /*           0 .. 65535           */
typedef signed short          sint16_t;         /*      -32768 .. +32767          */
typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
typedef signed long long      sint64_t;
typedef float                 float32_t;
typedef double                float64_t;
#endif



#endif /* STD_TYPES_H_ */