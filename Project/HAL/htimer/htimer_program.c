
#include "htimer_interface.h"



enu_handler_error_status_t HANDLER_init(str_GPT_configs_t *str_GPT_configs)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_init(str_GPT_configs);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}


enu_handler_error_status_t HANDLER_start_timer(enu_GPT_timer_select_t enu_arg_GPT_timer_select ,uint32_t u32_arg_time,enu_time_unit_t enu_arg_time_unit)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_start_timer(enu_arg_GPT_timer_select,u32_arg_time,enu_arg_time_unit);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}
enu_handler_error_status_t HANDLER_enable_interrupt(enu_GPT_timer_select_t enu_arg_GPT_timer_select)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_enable_interrupt(enu_arg_GPT_timer_select);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}
enu_handler_error_status_t HANDLER_disable_interrupt(enu_GPT_timer_select_t enu_arg_GPT_timer_select)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_disable_interrupt(enu_arg_GPT_timer_select);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}
enu_handler_error_status_t HANDLER_stop_timer(enu_GPT_timer_select_t enu_arg_GPT_timer_select)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_stop_timer(enu_arg_GPT_timer_select);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}

enu_handler_error_status_t HANDLER_get_elapsed_time(enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_get_elapsed_time(enu_arg_GPT_timer_select,u32_ptr_time);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}
enu_handler_error_status_t HANDLER_get_remaining_time (enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_get_remaining_time(enu_arg_GPT_timer_select,u32_ptr_time);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}
enu_handler_error_status_t HANDLER_set_pwm(enu_GPT_timer_select_t enu_arg_GPT_timer_select,uint16_t u16_arg_signal_duration_ms ,uint8_t u8_arg_duty_cycle)
{
	enu_handler_error_status_t enu_handler_error_status = HANDLER_OK;
	enu_GPT_status_t enu_GPT_status_return              = GPT_OKAY;
	enu_GPT_status_return = GPT_set_pwm(enu_arg_GPT_timer_select,u16_arg_signal_duration_ms,u8_arg_duty_cycle);
	if(enu_GPT_status_return != GPT_OKAY)
	{
		enu_handler_error_status = HANDLER_ERROR;
	}
	else
	{
		//do nothing
	}
	
	return enu_handler_error_status;
}
