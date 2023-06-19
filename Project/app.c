

#include "app.h"

uint8_t gl_app_state = FALSE;

int main(void)
{
	boolean val = TRUE;
	(void)LED_init();
	(void)BUTTON_init();

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
			gl_app_state++;
		  

		}
		else
		{
			if(gl_app_state == 0)
			{
				(void)LED_off(LED_RED);
				(void)LED_off(LED_GREEN);
				(void)LED_off(LED_BLUE);
			}
			else if(gl_app_state == 1)
			{
				(void)LED_on(LED_RED);
				(void)LED_off(LED_GREEN);
				(void)LED_off(LED_BLUE);
			}
			else if(gl_app_state == 2)
			{
				(void)LED_off(LED_RED);
				(void)LED_on(LED_GREEN);
				(void)LED_off(LED_BLUE);
			}
			else if(gl_app_state == 3)
			{
				(void)LED_off(LED_RED);
				(void)LED_off(LED_GREEN);
				(void)LED_on(LED_BLUE);
			}
			else if(gl_app_state == 4)
			{
				(void)LED_on(LED_RED);
				(void)LED_on(LED_GREEN);
				(void)LED_on(LED_BLUE);
			}
			else
			{
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


