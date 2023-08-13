

#ifndef HANDLER_H_
#define HANDLER_H_

#include "gpt_interface.h"


typedef enum
{
	HANDLER_OK = 0,
	HANDLER_ERROR
}enu_handler_error_status_t;	


enu_handler_error_status_t HANDLER_init(str_GPT_configs_t *str_GPT_configs);
enu_handler_error_status_t HANDLER_start_timer(enu_GPT_timer_select_t enu_arg_GPT_timer_select ,uint32_t u32_arg_time,enu_time_unit_t enu_arg_time_unit);
enu_handler_error_status_t HANDLER_enable_interrupt(enu_GPT_timer_select_t enu_arg_GPT_timer_select);
enu_handler_error_status_t HANDLER_disable_interrupt(enu_GPT_timer_select_t enu_arg_GPT_timer_select);
enu_handler_error_status_t HANDLER_stop_timer(enu_GPT_timer_select_t enu_arg_GPT_timer_select);
enu_handler_error_status_t HANDLER_get_elapsed_time   (enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time);
enu_handler_error_status_t HANDLER_get_remaining_time (enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time);
enu_handler_error_status_t HANDLER_set_pwm(enu_GPT_timer_select_t enu_arg_GPT_timer_select,uint16_t u16_arg_signal_duration_ms ,uint8_t u8_arg_duty_cycle);

#endif










