/*
 * button_cfg.c
 * Created: 18/6/2023 4:13:56 AM
 *  Author: Mahmoud Mowafey
 */ 
/** @file button_cfg.c
 * @brief The implementation for the button.
 */
/**********************************************************************
* Includes
**********************************************************************/
#include "button_cfg.h" /* For this modules definitions */
/**********************************************************************
* Module Variable Definitions
**********************************************************************/
/**
* Defines a table of structure to the configuration of the LED 
*/
const str_button_confige_t gl_button_Config[MAX_BUTTONS] =
{
	{
	  {
      	.enu_port_num          = PORTF ,
       	.enu_pin_num           = PIN4 , 
	      .enu_pin_direction     = INPUT_PIN , 
	      .enu_pin_mode          = DIGITAL_PIN,
        .enu_pin_internal_type = PULL_UP
	  }
	  , BUTTON_0 
	},
	{
	  {
      	.enu_port_num          = PORTF ,
       	.enu_pin_num           = PIN0 , 
	      .enu_pin_direction     = INPUT_PIN , 
	      .enu_pin_mode          = DIGITAL_PIN,
        .enu_pin_internal_type = PULL_UP
	  }
	  , BUTTON_1 
	}
};


/***End of File****************************************************/

