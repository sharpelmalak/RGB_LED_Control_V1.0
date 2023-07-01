

#include "app.h"

uint8_t gl_app_state  = FALSE;
boolean gl_lock_state = FALSE;
str_GPT_configs_t str_gl_pwm =
{
	.enu_GPT_timer_select = GPT_WIDE_TIMER0_SELECT,
	.enu_GPT_mode         = GPT_ONE_SHOT_MODE,
	.enu_GPT_type         = GPT_INDIVIDUAL_TYPE,
	.bool_use_interrupt   = TRUE,
	.ptrf_call_back       = switch_cycle_pwm
};

str_GPT_configs_t str_gl_timer_debouncing =
{
	.enu_GPT_timer_select = GPT_TIMER0_SELECT,
	.enu_GPT_mode         = GPT_ONE_SHOT_MODE,
	.enu_GPT_type         = GPT_INDIVIDUAL_TYPE,
	.bool_use_interrupt   = FALSE,
};

void app_init(void)
{
	(void)LED_init();
	(void)BUTTON_init();
	(void)HANDLER_init(&str_gl_pwm);
	(void)HANDLER_init(&str_gl_timer_debouncing);
	(void)HANDLER_enable_interrupt(GPT_WIDE_TIMER0_SELECT);
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
			
			HANDLER_start_timer(GPT_TIMER0_SELECT,DEBOUNCING_DELAY,TIME_IN_MILLIOSECONDS);
			gl_lock_state = TRUE;
			gl_app_state++;
		  

		}
		else
		{
			if(gl_app_state == APP_STATE_ZERO)
			{
				// DO NOTHING
			}
			else if(gl_app_state == APP_STATE_ONE)
			{
				if(gl_lock_state == TRUE)
				{
					LED_off(LED_GREEN);
					HANDLER_set_pwm(GPT_WIDE_TIMER0_SELECT,SIGNAL_DURATION_MS,DUTY_CYCLE_30);
					gl_lock_state = FALSE;
				}
				
			}
			else if(gl_app_state == APP_STATE_TWO)
			{
				if(gl_lock_state == TRUE)
				{
					LED_off(LED_GREEN);
					GPT_set_pwm(GPT_WIDE_TIMER0_SELECT,SIGNAL_DURATION_MS,DUTY_CYCLE_60);
					gl_lock_state = FALSE;
				}
			}
			else if(gl_app_state == APP_STATE_THREE)
			{
				if(gl_lock_state == TRUE)
				{
					LED_off(LED_GREEN);
					GPT_set_pwm(GPT_WIDE_TIMER0_SELECT,SIGNAL_DURATION_MS,DUTY_CYCLE_90);
					gl_lock_state = FALSE;
				}
			}
			else
			{
				HANDLER_stop_timer(GPT_WIDE_TIMER0_SELECT);
			  LED_off(LED_GREEN);
				gl_app_state = APP_STATE_ZERO;
			}
		}
	}
}


void switch_cycle_pwm(void)
{
	LED_toggle(LED_GREEN);
}

