

#include "app.h"

uint8_t gl_app_state    = FALSE; //to control app sequence
uint8_t gl_app_isfinish = FALSE; //to control non repeating intrance 

int main(void)
{
	
	boolean val = TRUE;
	(void)LED_init();
	(void)BUTTON_init();
	 SYSTICK_init();

	while(1)
	{
		(void)BUTTON_read(BUTTON_0,&val);
		if(val == FALSE)
		{
			while(val == FALSE)
			{
				(void)BUTTON_read(BUTTON_0,&val);
			}
	  // handle debouncing		
			SYSTICK_synchronous_time_ms(200);
			gl_app_state++;
		  

		}
		else
		{
			if(gl_app_state == INITIAL_STATE)
			{
				(void)LED_off(LED_RED);
				(void)LED_off(LED_GREEN);
				(void)LED_off(LED_BLUE);
			}
			else if(gl_app_state == RED_LED_STATE)
			{
				if(gl_app_isfinish == INITIAL_STATE)
				{
					(void)LED_on(LED_RED);
				  SYSTICK_synchronous_time_ms(ONE_SECOND);
				  (void)LED_off(LED_RED);
				  (void)LED_off(LED_GREEN);
				  (void)LED_off(LED_BLUE);
					gl_app_isfinish = RED_LED_STATE;
				}
				else
				{
					//do nothing
				}
				
				
			}
			else if(gl_app_state == GREEN_LED_STATE)
			{
				if(gl_app_isfinish == RED_LED_STATE)
				{
					(void)LED_off(LED_RED);
					(void)LED_on(LED_GREEN);
					SYSTICK_synchronous_time_ms(ONE_SECOND);
					(void)LED_off(LED_GREEN);
					(void)LED_off(LED_BLUE);
					gl_app_isfinish = GREEN_LED_STATE;
				}
				else
				{
					//donothing
				}
			}
			else if(gl_app_state == BLUE_LED_STATE)
			{
				if(gl_app_isfinish == GREEN_LED_STATE)
				{
				  (void)LED_off(LED_RED);
				  (void)LED_off(LED_GREEN);
				  (void)LED_on(LED_BLUE);
				  SYSTICK_synchronous_time_ms(ONE_SECOND);
				  (void)LED_off(LED_BLUE);
				  gl_app_isfinish = BLUE_LED_STATE;
				}
				else
				{
					// do nothing
				}
			}
			else if(gl_app_state == RGB_LED_STATE)
			{
				if(gl_app_isfinish == BLUE_LED_STATE)
				{
					(void)LED_on(LED_RED);
					(void)LED_on(LED_GREEN);
					(void)LED_on(LED_BLUE);
					SYSTICK_synchronous_time_ms(ONE_SECOND);
					(void)LED_off(LED_RED);
					(void)LED_off(LED_GREEN);
					(void)LED_off(LED_BLUE);
					gl_app_isfinish = RGB_LED_STATE;
				}
				else
				{
					//do nothing
				}
			}
			else
			{
				gl_app_state    = RED_LED_STATE;
				gl_app_isfinish = INITIAL_STATE;
			}
		}
	}
}	



