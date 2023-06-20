/*
**@file     : systick_pogram.c
**@brief    : this file implements all Systick APIs 
**@author   : sharpel
**@date     : 19 june 2023
**@version  : 0.1
*/



#include "TM4C123.h"
#include "systick_private.h"
#include "systick_interface.h"

ptrf_systick_cb_t gl_systick_cb = NULL;

enu_systick_status_t SYSTICK_init (void)
{
	enu_systick_status_t enu_systick_status_return = SYSTICK_OKAY;
	if(GET_BIT(STCTRL,STCTRL_ENABLE) == TRUE)
	{
		enu_systick_status_return = INVALID_OPERATION;
	}
	else
	{
		SET_BIT(STCTRL,STCTRL_ENABLE);
	}
	
	return enu_systick_status_return;
}


enu_systick_status_t SYSTICK_enable_interrupt (void)
{
	enu_systick_status_t enu_systick_status_return = SYSTICK_OKAY;
	if(GET_BIT(STCTRL,STCTRL_INTEN) == TRUE)
	{
		enu_systick_status_return = INVALID_OPERATION;
	}
	else
	{
		SET_BIT(STCTRL,STCTRL_INTEN);
	}
	
	return enu_systick_status_return;
}

enu_systick_status_t SYSTICK_disable_interrupt (void)
{enu_systick_status_t enu_systick_status_return = SYSTICK_OKAY;
	if(GET_BIT(STCTRL,STCTRL_INTEN) == FALSE)
	{
		enu_systick_status_return = INVALID_OPERATION;
	}
	else
	{
		CLEAR_BIT(STCTRL,STCTRL_INTEN);
	}
	
	return enu_systick_status_return;
}
enu_systick_status_t SYSTICK_synchronous_time_ms (uint32_t arg_time_ms)
{
	uint32_t             uint32_loc_reload_value   = FALSE;
	enu_systick_status_t enu_systick_status_return = SYSTICK_OKAY;
	uint32_loc_reload_value = (CLK_FREQ/(arg_time_ms/MILLI_SEC_CONV))-1;
	if( uint32_loc_reload_value == FALSE || (uint32_loc_reload_value>MAX_RELOAD_VALUE))
	{
		enu_systick_status_return = INVALID_ARGUMENT_TIME;
	}
	else
	{
		STRELOAD   = uint32_loc_reload_value;
		STCTRL     = STCTRL_SYNC;
		STCURRENT  = FALSE;
		while(GET_BIT(STCTRL,STCTRL_COUNT) != TRUE); // poll until counter reaches 0
		SYSTICK_stop();
	}
	
	return enu_systick_status_return;
}
enu_systick_status_t SYSTICK_Asynchronous_time_ms(uint32_t arg_time_ms,ptrf_systick_cb_t ptrf_arg_systick_cb)
{
	uint32_t             uint32_loc_reload_value   = FALSE;
	enu_systick_status_t enu_systick_status_return = SYSTICK_OKAY;
	if(ptrf_arg_systick_cb == NULL)
	{
		enu_systick_status_return = NULL_CB_REF;
	}
	else
	{
		uint32_loc_reload_value = (CLK_FREQ/(arg_time_ms/MILLI_SEC_CONV))-1;
		if( uint32_loc_reload_value == FALSE || (uint32_loc_reload_value>MAX_RELOAD_VALUE))
		{
			enu_systick_status_return = INVALID_ARGUMENT_TIME;
		}
		else
		{
			gl_systick_cb = ptrf_arg_systick_cb; // set cb
			NVIC_EnableIRQ(SysTick_IRQn);        //enable irq
			__enable_irq();
			STRELOAD      = uint32_loc_reload_value;
			STCTRL        = STCTRL_ASYNC;
			STCURRENT     = FALSE;
		}
	}
	
	return enu_systick_status_return;
}
enu_systick_status_t SYSTICK_stop(void)
{
	enu_systick_status_t enu_systick_status_return = SYSTICK_OKAY;
	if(STCTRL == STCTRL_RESET)
	{
		enu_systick_status_return = INVALID_OPERATION;
	}
	else
	{
		 STRELOAD   = FALSE;
		 STCURRENT  = FALSE;
		 STCTRL     = STCTRL_RESET;
	}
	
	return enu_systick_status_return;
}

void SysTick_Handler (void)
{ 
	if(gl_systick_cb != NULL)
	{
		gl_systick_cb();
	}
	else
	{
		//do nothing
	}
}

