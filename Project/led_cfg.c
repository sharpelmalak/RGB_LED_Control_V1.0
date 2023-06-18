/*
 * led_cfg.c
 * Created: 18/6/2023 4:13:56 AM
 *  Author: Mahmoud Mowafey
 */ 
/** @file led_cfg.c
 * @brief The implementation for the led.
 */
/**********************************************************************
* Includes
**********************************************************************/
#include "led_cfg.h" /* For this modules definitions */
/**********************************************************************
* Module Variable Definitions
**********************************************************************/
/**
* Defines a table of structure to the configuration of the LED 
*/
const str_led_confige_t gl_Led_Config[MAX_LEDS] =
{
	{
	  {
      	.enu_port_num        = PORTF ,
       	.enu_pin_num         = PIN1 , 
	      .enu_pin_direction   = OUTPUT_PIN , 
	      .enu_pin_mode        = DIGITAL_PIN,
	      .enu_pin_level       =  LOW_LEVEL ,           
	      .enu_pin_out_current = PIN_2MA_CURRENT 
	  }
	  , LED_RED 
	},
	{
	  {
      	.enu_port_num        = PORTF ,
       	.enu_pin_num         = PIN2 , 
	      .enu_pin_direction   = OUTPUT_PIN , 
	      .enu_pin_mode        = DIGITAL_PIN,
	      .enu_pin_level       =  LOW_LEVEL ,           
	      .enu_pin_out_current = PIN_2MA_CURRENT 
	  }
	  , LED_BLUE 
	},
	{
	  {
      	.enu_port_num        = PORTF ,
       	.enu_pin_num         = PIN3 , 
	      .enu_pin_direction   = OUTPUT_PIN , 
	      .enu_pin_mode        = DIGITAL_PIN,
	      .enu_pin_level       =  LOW_LEVEL ,           
	      .enu_pin_out_current = PIN_2MA_CURRENT 
	  }
	  , LED_GREEN 
	}
};

/**********************************************************************
* Function Definitions
**********************************************************************/
/**********************************************************************
* Function : LED_Config()
*//**
* \b Description:
*
* This function is used to initialize the LED based on the configuration
* table defined in led_cfg module.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0)
*
* POST-CONDITION: A constant pointer to the first member of the
* configuration table will be returned.
*
* @return A pointer to the configuration table.
*
* \b Example Example:
* @code
* const str_led_confige_t *LED_Config = LED_GetConfig();
*
* @endcode
*
* @see LED_Init
* @see LED_on
* @see LED_off
* @see LED_toggle
* @see LED_status
*
**********************************************************************/
//const str_led_confige_t *const LED_ConfigGet(void)
//{
///*
//* The cast is performed to ensure that the address of the first element
//* of configuration table is returned as a constant pointer and NOT a
//* pointer that can be modified.
//*/
// return (const *)LED_Config[0];
//}
/***End of File****************************************************/