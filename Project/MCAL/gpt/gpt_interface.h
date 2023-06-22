/*
**@file     : gpt_interface.h
**@brief    : this is header file to interface with GPT 
**@author   : sharpel
**@date     : 21 june 2023
**@version  : 0.1
*/


#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_

/*Includes*/

#include "common.h"
#include "gpio_interface.h"


/*Typedefs*/


typedef void(*ptrf_cb_t)(void);

typedef enum
{
	GPT_TIMER0_SELECT         = 0,
  GPT_TIMER1_SELECT            ,
  GPT_TIMER2_SELECT            ,
  GPT_TIMER3_SELECT	           ,
	GPT_TIMER4_SELECT            ,
	GPT_TIMER5_SELECT            ,
	GPT_WIDE_TIMER0_SELECT       ,
	GPT_WIDE_TIMER1_SELECT       ,
	GPT_WIDE_TIMER2_SELECT       ,
	GPT_WIDE_TIMER3_SELECT       ,
	GPT_WIDE_TIMER4_SELECT       ,
	GPT_WIDE_TIMER5_SELECT       ,
	GPT_INVALID_TIMER_SELECT      
	
}enu_GPT_timer_select_t;



typedef enum
{
	GPT_ONE_SHOT_MODE         = 0,
  GPT_PERIODIC_MODE            ,
  GPT_RTC_MODE                 ,
  GPT_INPUT_EDGE_COUNT_MODE	   ,
	GPT_INPUT_EDGE_TIME_MODE	   ,
	GPT_PWM_MODE                 ,
	GPT_INVALID_MODE
	
}enu_GPT_mode_t;

typedef enum
{
	GPT_INDIVIDUAL_TYPE         = 0,
  GPT_CONCATENATED_TYPE          ,
	GPT_INVALID_TYPE
	
}enu_GPT_type_t;



typedef struct 
{
	enu_GPT_timer_select_t      enu_GPT_timer_select;
	enu_GPT_mode_t              enu_GPT_mode;
	enu_GPT_type_t              enu_GPT_type;
	boolean                     bool_use_interrupt;
	ptrf_cb_t                   ptrf_call_back;
}str_GPT_configs_t;



typedef enum
{
	GPT_OKAY      = 0           ,
	GPT_TIMER_SELECT_ERROR      ,
	GPT_MODE_SELECT_ERROR       ,
	GPT_TYPE_SELECT_ERROR       ,
	GPT_NULL_REF_ERROR          ,
	GPT_INVALID_OPERATION_ERROR ,
	GPT_NULL_REF_CB_ERROR       ,
	GPT_INVALID_UNIT_ERROR
	
	
}enu_GPT_status_t;

typedef enum
{
	TIME_IN_MICROSECONDS  = 0 ,
	TIME_IN_MILLIOSECONDS     ,
	TIME_IN_SECONDS           ,
	TIME_UNIT_INVALID
}enu_time_unit_t;



enu_GPT_status_t GPT_init               (str_GPT_configs_t *ptr_GPT_configs);
enu_GPT_status_t GPT_start_timer        (enu_GPT_timer_select_t enu_arg_GPT_timer_select ,uint32_t u32_arg_time,enu_time_unit_t enu_arg_time_unit);
enu_GPT_status_t GPT_get_elapsed_time   (enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time);
enu_GPT_status_t GPT_get_remaining_time (enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time);
enu_GPT_status_t GPT_enable_interrupt   (enu_GPT_timer_select_t enu_arg_GPT_timer_select);
enu_GPT_status_t GPT_disable_interrupt  (enu_GPT_timer_select_t enu_arg_GPT_timer_select);
enu_GPT_status_t GPT_stop_timer         (enu_GPT_timer_select_t enu_arg_GPT_timer_select);
enu_GPT_status_t GPT_set_pwm            (enu_GPT_timer_select_t enu_arg_GPT_timer_select,uint16_t u16_arg_signal_duration_ms ,uint8_t u8_arg_duty_cycle);

#endif




