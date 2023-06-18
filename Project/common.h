/*
**@file     : common.h
**@brief    : this is header file for common usage macros and definations
**@author   : sharpel
**@date     : 13 june 2023
**@version  : 0.1
*/


#ifndef COMMON_H_
#define COMMON_H_

/* INCLUDES*/

#include "stdint.h"


/* MACROS*/

#define SUCCESS               (0)
#define ERROR                 (-1)
#define INVALID_INPUT         (-2)
#define NULL                  ((void *)0)
											        
#ifndef TRUE                  
#define TRUE                  (1)
#endif                        
											        
#ifndef FALSE                 
#define FALSE                 (0)
#endif                   
											   
/* TYPEDEFS*/            
											   
											   
typedef unsigned char          boolean;


/* BIT MATH OPERATIONS*/


#define GET_BIT(reg,bit_num)    ((reg>>bit_num)&1)
#define SET_BIT(reg,bit_num)    (reg|=(1<<bit_num))
#define CLEAR_BIT(reg,bit_num)  (reg&=(~(1<<bit_num)))
#define TOGGLE_BIT(reg,bit_num) (reg^=(1<<bit_num))
#endif

