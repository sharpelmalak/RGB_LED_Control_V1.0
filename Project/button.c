

#include "button.h"

extern const str_button_confige_t gl_button_Config[MAX_BUTTONS];

enu_button_error_status_t BUTTON_init(void)
{
	uint8_t error_state      = BUTTON_OK;
	uint8_t uint8_loc_conter = FALSE;
	for(uint8_loc_conter=FALSE;uint8_loc_conter<MAX_BUTTONS;uint8_loc_conter++)
	{
		if(gl_button_Config[uint8_loc_conter].gpio_for_button_confige.enu_pin_direction != INPUT_PIN)
		{
			error_state = BUTTON_WRONG;
		  break;
		}
		else
		{
			error_state = (enu_button_error_status_t) GPIO_init(&gl_button_Config[uint8_loc_conter].gpio_for_button_confige); 	
			if(error_state != BUTTON_OK)
			{
			error_state = BUTTON_WRONG;
			break;
			}
			else
			{
				//do nothing
			}
		}
	  
	}
	
	return (enu_button_error_status_t)error_state;
}
enu_button_error_status_t BUTTON_read(enu_button_id_t button_id,boolean *value)
{
		uint8_t error_state      = BUTTON_OK;
	uint8_t uint8_loc_conter = FALSE;
	for(uint8_loc_conter=FALSE;uint8_loc_conter<MAX_BUTTONS;uint8_loc_conter++)
	{
		if(gl_button_Config[uint8_loc_conter].gpio_for_button_confige.enu_pin_direction != INPUT_PIN)
		{
			error_state = BUTTON_WRONG;
		  break;
		}
		else
		{
			if(button_id == gl_button_Config[uint8_loc_conter].button_id)
			{
				error_state = (enu_button_error_status_t) GPIO_read(gl_button_Config[uint8_loc_conter].gpio_for_button_confige.enu_port_num,
				                                                     gl_button_Config[uint8_loc_conter].gpio_for_button_confige.enu_pin_num,
                                                              value); 	
				break;
			}
			else
			{
				//do nothing
			}
			if(error_state != BUTTON_OK)
				{
				error_state = BUTTON_WRONG;
				break;
				}
				else
				{
					//do nothing
				}
		}
	  
	}
	
	return (enu_button_error_status_t)error_state;
}