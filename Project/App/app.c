

#include "app.h"

uint8_t gl_app_state  = FALSE;
boolean gl_lock_state = FALSE;
str_GPT_configs_t str_gl_GPT_timer0 =
{
	.enu_GPT_timer_select = GPT_WIDE_TIMER0_SELECT,
	.enu_GPT_mode         = GPT_ONE_SHOT_MODE,
	.enu_GPT_type         = GPT_INDIVIDUAL_TYPE,
	.bool_use_interrupt   = TRUE,
	.ptrf_call_back       = switch_cycle_pwm
};

void app_init(void)
{
	(void)LED_init();
	(void)BUTTON_init();
	(void)GPT_init(&str_gl_GPT_timer0);
	(void)GPT_enable_interrupt(GPT_WIDE_TIMER0_SELECT);
}

void app_start(void)
{
	boolean val = TRUE;


	while(1)
	{
		(void)BUTTON_read(BUTTON_0,&val);
		if(val == FALSE)
		{
			while(val == FALSE)
			{
				(void)BUTTON_read(BUTTON_0,&val);
			}
			
			debouncing_handler();
			gl_lock_state = TRUE;
			gl_app_state++;
		  

		}
		else
		{
			if(gl_app_state == 0)
			{
				// DO NOTHING
			}
			else if(gl_app_state == 1)
			{
				if(gl_lock_state == TRUE)
				{
					LED_off(LED_GREEN);
					GPT_set_pwm(GPT_WIDE_TIMER0_SELECT,500,30);
					gl_lock_state = FALSE;
				}
				
			}
			else if(gl_app_state == 2)
			{
				if(gl_lock_state == TRUE)
				{
					LED_off(LED_GREEN);
					GPT_set_pwm(GPT_WIDE_TIMER0_SELECT,500,60);
					gl_lock_state = FALSE;
				}
			}
			else if(gl_app_state == 3)
			{
				if(gl_lock_state == TRUE)
				{
					LED_off(LED_GREEN);
					GPT_set_pwm(GPT_WIDE_TIMER0_SELECT,500,90);
					gl_lock_state = FALSE;
				}
			}
			else
			{
				GPT_stop_timer(GPT_WIDE_TIMER0_SELECT);
			  LED_off(LED_GREEN);
				gl_app_state = 0;
			}
		}
	}
}

void debouncing_handler(void)
{
		volatile uint32_t uint8_loc_counter = FALSE;
		for(uint8_loc_counter=FALSE;uint8_loc_counter<MAX_DELAY;uint8_loc_counter++);
}


void switch_cycle_pwm(void)
{
	LED_toggle(LED_GREEN);
}