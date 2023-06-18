/*
**@file     : gpio_private.h
**@brief    : this is header file for GPIO registers usage 
**@author   : sharpel
**@date     : 14 june 2023
**@version  : 0.1
*/


#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/*GPIO REGISTERS*/

#define GPIO_APB

#ifdef  GPIO_APB
#define GPIO_OFFSET(x)         (x<4?((0x40004000)+((x)*0x1000)):((0x40024000)+((x-4)*0x1000)))
#elif   GPIO_AHB
#error  "Not Supported"
#else
#error  "Please Choose Bus for GPIOs"
#endif

#define GPIODATA(x)            (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x3FC))) 
#define GPIODIR(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x400)))
#define GPIOIS(x)              (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x404)))
#define GPIOIBE(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x408)))
#define GPIOIEV(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x40C)))
#define GPIOIM(x)              (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x410)))
#define GPIORIS(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x414)))
#define GPIOMIS(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x418)))
#define GPIOICR(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x41C)))
#define GPIOAFSEL(x)           (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x420)))
#define GPIODR2R(x)            (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x500)))
#define GPIODR4R(x)            (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x504)))	
#define GPIODR8R(x)            (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x508)))	
#define GPIOODR(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x50C)))	
#define GPIOPUR(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x510)))	
#define GPIOPDR(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x514)))
#define GPIOSLR(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x518)))	
#define GPIODEN(x)             (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x51C)))	
#define GPIOLOCK(x)            (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x520)))	
#define GPIOCR(x)              (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x524)))	
#define GPIOAMSEL(x)           (*(volatile uint32_t*)(GPIO_OFFSET(x)+(0x528)))		
	
// GPIO RUN MODE GATING CONTROL REGISTER

#define RCGCGPIO               (*(volatile uint32_t*)(0x400FE608))


#endif


