/*
**@file     : gpt_pogram.c
**@brief    : this file implements all GPT APIs 
**@author   : sharpel
**@date     : 21 june 2023
**@version  : 0.1
*/



#include "TM4C123.h"
#include "gpt_private.h"
#include "gpt_interface.h"

// initially all timers are not initialized
static boolean    bool_gs_is_timer_init[GPT_INVALID_TIMER_SELECT] = {FALSE};
static ptrf_cb_t  ptrf_gs_array[GPT_INVALID_TIMER_SELECT]         = {NULL};
static uint16_t   u16_gs_high_period                              = FALSE;
static uint16_t   u16_gs_low_period                               = FALSE;
static boolean    bool_gs_is_high_period                          = FALSE; 


enu_GPT_status_t GPT_init(str_GPT_configs_t *ptr_GPT_configs)
{
	enu_GPT_status_t         enu_GPT_status_return  = GPT_OKAY;
	enu_GPT_timer_select_t   enu_loc_selected_timer = ptr_GPT_configs->enu_GPT_timer_select;
	if(ptr_GPT_configs == NULL)
	{
		enu_GPT_status_return = GPT_NULL_REF_ERROR;
	}
	else
	{
		// check on selected timer range
		if(enu_loc_selected_timer < GPT_INVALID_TIMER_SELECT)
		{
			// check if selected timer initilized before or not
			if(bool_gs_is_timer_init[enu_loc_selected_timer] == FALSE)
			{
				// 1 - the appropriate TIMERn bit must be set in the RCGCTIMER or RCGCWTIMER register
				if(enu_loc_selected_timer < GPT_WIDE_TIMER0_SELECT)
				{
					// Case of not wide timer
					SET_BIT(RCGCTIMER,enu_loc_selected_timer);
				}
				else 
				{
					// Case wide timer subtract offset 6 to make the bits from 0 to 5
					SET_BIT(RCGCWTIMER,(enu_loc_selected_timer - GPT_WIDE_TIMER0_SELECT));
				}
				
				// 2 - Ensure the timer is disabled
        CLEAR_BIT(GPTMCTL(enu_loc_selected_timer),GPTMCTL_TAEN);


        // check on mode range	
        if(ptr_GPT_configs->enu_GPT_mode < GPT_INVALID_MODE)
				{
					if(ptr_GPT_configs->enu_GPT_mode < GPT_RTC_MODE)
					{
						 // check on type 	
						if(ptr_GPT_configs->enu_GPT_type == GPT_INDIVIDUAL_TYPE)
						{
							GPTMCFG(enu_loc_selected_timer) = GPTMCFG_SINGLE; 
						}
						else if (ptr_GPT_configs->enu_GPT_type == GPT_CONCATENATED_TYPE)
						{
							GPTMCFG(enu_loc_selected_timer) = GPTMCFG_DOUBLE; 
						}
						else
						{
							enu_GPT_status_return = GPT_TYPE_SELECT_ERROR;
						}
						
						//check all cases have passed
						 if(enu_GPT_status_return == GPT_OKAY)
						 {
							 // 3 - Configure the TnMR field in the GPTM Timer n Mode Register
							 // case one shot mode  
							 if(ptr_GPT_configs->enu_GPT_mode == GPT_ONE_SHOT_MODE)
							 {
								 GPTMTAMR(enu_loc_selected_timer) = ONE_SHOT_VALUE;
							 }
							 // case periodic mode (interrupt based)
							 else if(ptr_GPT_configs->enu_GPT_mode == GPT_PERIODIC_MODE) 
							 {
								 GPTMTAMR(enu_loc_selected_timer) = PERIODIC_VALUE;
							 }
							 else
							 {
							 	// do nothing
							 }
							 
							 // 4 - TODO configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
							 // 5 - Load the start value into the GPTM Timer n Interval Load Register(configure it in GPT_start_timer API)
							 // 6 - If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
               if (ptr_GPT_configs->bool_use_interrupt == TRUE)
							 {
								 if(ptr_GPT_configs->ptrf_call_back == NULL)
								 {
									 enu_GPT_status_return = GPT_NULL_REF_CB_ERROR;
								 }
								 else
								 {
									 // mask interrupt //// the user of this module must call GPT_interrupt_enable to unmask interrupt
								   CLEAR_BIT(GPTMIMR(enu_loc_selected_timer),GPTMIMR_TATOIM);
									 ptrf_gs_array[enu_loc_selected_timer] = ptr_GPT_configs->ptrf_call_back;
								 }
								 
							 }
               else
							 {
								 // case of polling initilaization
							 }
               // 7 - Set the TnEN bit in the GPTMCTL register to enable the timer and start counting	(configure it in GPT_start_timer API)
							 
							 // set selected timer as initilized 
               bool_gs_is_timer_init[enu_loc_selected_timer] = TRUE;							 
						 }
						 else
						 {
							 // do nothing
						 }
						
					}
					else if(ptr_GPT_configs->enu_GPT_mode == GPT_RTC_MODE)
					{
						//TODO support RTC_MODE
					}
					else if(ptr_GPT_configs->enu_GPT_mode == GPT_INPUT_EDGE_COUNT_MODE)
					{
						//TODO support INPUT_EDGE_COUNT_MODE
					}
					else if(ptr_GPT_configs->enu_GPT_mode == GPT_INPUT_EDGE_TIME_MODE)
					{
						//TODO support INPUT_EDGE_TIME_MODE
					}
					else if(ptr_GPT_configs->enu_GPT_mode == GPT_PWM_MODE)
					{
						//TODO support PWM_MODE
					}
					else
					{
						// do nothing
					}
					
				}	
        else
				{
					enu_GPT_status_return = GPT_MODE_SELECT_ERROR;
				}					
			}
			else
			{
				enu_GPT_status_return = GPT_INVALID_OPERATION_ERROR;
			}
		}
		else
		{
			enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
		}
	}
	
	return enu_GPT_status_return;
}





enu_GPT_status_t GPT_start_timer(enu_GPT_timer_select_t enu_arg_GPT_timer_select ,uint32_t u32_arg_time,enu_time_unit_t enu_arg_time_unit)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
  double f64_tick_time   = ONE_F/CLK_FREQ;
  double f64_total_ticks = ZERO_F;	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
		// check if selected timer is initialized or not
		if(bool_gs_is_timer_init[enu_arg_GPT_timer_select] == TRUE)
		{
			if(enu_arg_time_unit < TIME_UNIT_INVALID)
			{
				
				if(enu_arg_time_unit == TIME_IN_MICROSECONDS)
				{
					f64_total_ticks = ((u32_arg_time/MICRO_CONVERTER)/(f64_tick_time));
				}
				else if(enu_arg_time_unit == TIME_IN_MILLIOSECONDS)
				{
					f64_total_ticks = ((u32_arg_time/MILLI_CONVERTER)/(f64_tick_time));
				}
				else 
				{
					f64_total_ticks = ((u32_arg_time/ONE_F)/(f64_tick_time));
				}
				
				GPTMTAILR(enu_arg_GPT_timer_select) = f64_total_ticks;
				SET_BIT(GPTMCTL(enu_arg_GPT_timer_select),GPTMCTL_TAEN);
				
				// case of interrupt
				if(GET_BIT(GPTMIMR(enu_arg_GPT_timer_select),GPTMIMR_TATOIM) == TRUE)
				{
					// do nothing
				}
				else
				{
					//STOP UNTIL TIME OUT OCCURES
					while (GET_BIT(GPTMRIS(enu_arg_GPT_timer_select),GPTMRIS_TATORIS) != TRUE);
					SET_BIT(GPTMICR(enu_arg_GPT_timer_select),GPTMICR_TATOCINT);
					GPT_stop_timer(enu_arg_GPT_timer_select);
				}
				
			}
			else
			{
				enu_GPT_status_return = GPT_INVALID_UNIT_ERROR;
			}
		}
		else
		{
			// case of uninitialized timer selection
			enu_GPT_status_return = GPT_INVALID_OPERATION_ERROR;
		}
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}
enu_GPT_status_t GPT_get_elapsed_time(enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time_ms)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
		*u32_ptr_time_ms = (GPTMTAILR(enu_arg_GPT_timer_select) - GPTMTAR(enu_arg_GPT_timer_select))/(CLK_FREQ*MILLI_CONVERTER);
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}
enu_GPT_status_t GPT_get_remaining_time(enu_GPT_timer_select_t enu_arg_GPT_timer_select , uint32_t *u32_ptr_time_ms)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
		*u32_ptr_time_ms = GPTMTAR(enu_arg_GPT_timer_select)/(CLK_FREQ*MILLI_CONVERTER);
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}
enu_GPT_status_t GPT_enable_interrupt(enu_GPT_timer_select_t enu_arg_GPT_timer_select)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
		// case of re enable interrupt
    if(GET_BIT(GPTMIMR(enu_arg_GPT_timer_select),GPTMIMR_TATOIM) == TRUE)
		{
			enu_GPT_status_return = GPT_INVALID_OPERATION_ERROR;
		}
		else
		{
			SET_BIT(GPTMIMR(enu_arg_GPT_timer_select),GPTMIMR_TATOIM);
			if(enu_arg_GPT_timer_select == GPT_TIMER0_SELECT)
			{
				NVIC_EnableIRQ(TIMER0A_IRQn);
			}
			else if(enu_arg_GPT_timer_select == GPT_WIDE_TIMER0_SELECT)
			{
				NVIC_EnableIRQ(WTIMER0A_IRQn);
			}
			else
			{
				// TODO SUPPORT ALL REST INTERRUPTS
			}
			__enable_irq();
			
		}
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}
enu_GPT_status_t GPT_disable_interrupt(enu_GPT_timer_select_t enu_arg_GPT_timer_select)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
		// case of re enable interrupt
    if(GET_BIT(GPTMIMR(enu_arg_GPT_timer_select),GPTMIMR_TATOIM) != TRUE)
		{
			enu_GPT_status_return = GPT_INVALID_OPERATION_ERROR;
		}
		else
		{
			CLEAR_BIT(GPTMIMR(enu_arg_GPT_timer_select),GPTMIMR_TATOIM);
			if(enu_arg_GPT_timer_select == GPT_TIMER0_SELECT)
			{
				NVIC_DisableIRQ(TIMER0A_IRQn);
			}
			else if(enu_arg_GPT_timer_select == GPT_WIDE_TIMER0_SELECT)
			{
				NVIC_DisableIRQ(WTIMER0A_IRQn);
			}
			else
			{
				// TODO SUPPORT ALL REST INTERRUPTS
			}
		}
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}




enu_GPT_status_t GPT_set_pwm(enu_GPT_timer_select_t enu_arg_GPT_timer_select,uint16_t u16_arg_signal_duration_ms ,uint8_t u8_arg_duty_cycle)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
		// case of UN enable interrupt or un initialized timer
    if((GET_BIT(GPTMIMR(enu_arg_GPT_timer_select),GPTMIMR_TATOIM) != TRUE) || (bool_gs_is_timer_init[enu_arg_GPT_timer_select] != TRUE))
		{
			enu_GPT_status_return = GPT_INVALID_OPERATION_ERROR;
		}
		else
		{

			  bool_gs_is_high_period = FALSE;
			
				u16_gs_high_period = (u16_arg_signal_duration_ms*u8_arg_duty_cycle)/100;
				u16_gs_low_period  = u16_arg_signal_duration_ms - u16_gs_high_period;
			  GPT_start_timer(enu_arg_GPT_timer_select,u16_gs_low_period,TIME_IN_MILLIOSECONDS);
		}
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}

enu_GPT_status_t GPT_stop_timer (enu_GPT_timer_select_t enu_arg_GPT_timer_select)
{
	enu_GPT_status_t enu_GPT_status_return = GPT_OKAY;
	
	// check on selected timer range
	if(enu_arg_GPT_timer_select < GPT_INVALID_TIMER_SELECT)
	{
	  CLEAR_BIT(GPTMCTL(enu_arg_GPT_timer_select),GPTMCTL_TAEN);
	}
	
	else
	{
		enu_GPT_status_return = GPT_TIMER_SELECT_ERROR;
	}
		
		
	return enu_GPT_status_return;
}

void TIMER0A_Handler(void)
{
	if(ptrf_gs_array[GPT_TIMER0_SELECT] != NULL)
	{
		CLEAR_BIT(GPTMCTL(GPT_TIMER0_SELECT),GPTMCTL_TAEN);
		ptrf_gs_array[GPT_TIMER0_SELECT]();
	}
	else
	{
		//do nothig
	}
}



void WTIMER0A_Handler(void)
{
	if(ptrf_gs_array[GPT_WIDE_TIMER0_SELECT] != NULL)
	{
		ptrf_gs_array[GPT_WIDE_TIMER0_SELECT]();
		SET_BIT(GPTMICR(GPT_WIDE_TIMER0_SELECT),GPTMICR_TATOCINT);
		GPT_stop_timer(GPT_WIDE_TIMER0_SELECT);
		if(bool_gs_is_high_period == TRUE)
		{
			GPT_start_timer(GPT_WIDE_TIMER0_SELECT,u16_gs_low_period,TIME_IN_MILLIOSECONDS);
			bool_gs_is_high_period = FALSE;
		}
		else
		{
			GPT_start_timer(GPT_WIDE_TIMER0_SELECT,u16_gs_high_period,TIME_IN_MILLIOSECONDS);
			bool_gs_is_high_period = TRUE;
		}
		
		
	}
	else
	{
		//do nothig
	}
}



