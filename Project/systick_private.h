/*
**@file     : systick_private.h
**@brief    : this is header file for systick registers usage 
**@author   : sharpel
**@date     : 19 june 2023
**@version  : 0.1
*/


// Systick Registers

#define STCTRL               (*(volatile uint32_t*)(0xE000E010))
#define STRELOAD             (*(volatile uint32_t*)(0xE000E014))
#define STCURRENT            (*(volatile uint32_t*)(0xE000E018))	
	

// Systick STCTRL values and bit names

#define STCTRL_RESET               0x00000004
#define STCTRL_SYNC                0x05
#define STCTRL_ASYNC               0x07
#define STCTRL_ENABLE              (0)
#define STCTRL_INTEN               (1)
#define STCTRL_CLK_SRC             (2)
#define STCTRL_COUNT               (16)

#define CLK_FREQ                   16000000UL
#define MILLI_SEC_CONV             1000U
#define MAX_RELOAD_VALUE          0x00FFFFFF
