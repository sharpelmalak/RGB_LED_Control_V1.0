/*
 * led.c
 * Created: 18/6/2023 4:13:56 AM
 *  Author: Mahmoud Mowafey
 */ 
/** @file led.c
 * @brief The implementation for the led.
 */
/**********************************************************************
* Includes
**********************************************************************/
#include "led.h" /* For this modules definitions */

/**********************************************************************
* Module Variable Definitions
**********************************************************************/

extern const str_led_confige_t gl_Led_Config[MAX_LEDS];

/**********************************************************************
* Function Definitions
**********************************************************************/
/**********************************************************************
* Function : LED_init()
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
* @parameters :  [in] led_id.
*				 [in] led_configuration.
* \b Example Example:
* @code
* LED_Init(str_led_confige_t *LedConfig);
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
enu_led_error_status_t LED_init(void)
{
	uint8_t error_state      = LED_OK;
	uint8_t uint8_loc_conter = FALSE;
	for(uint8_loc_conter=FALSE;uint8_loc_conter<MAX_LEDS;uint8_loc_conter++)
	{
		if(gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_direction != OUTPUT_PIN)
		{
			error_state = LED_WRONG;
		  break;
		}
		else
		{
			error_state = (enu_led_error_status_t) GPIO_init(&gl_Led_Config[uint8_loc_conter].gpio_for_led_confige); 	
			if(error_state != LED_OK)
			{
			error_state = LED_WRONG;
			break;
			}
			else
			{
				//do nothing
			}
		}
	  
	}
	
	return (enu_led_error_status_t)error_state;
}

/**********************************************************************
* Function : LED_on()
*//**
* \b Description:
*
* This function is used to Turn the LED on.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0)
* PRE-CONDITION: LED_ID needs to be passed
*
* POST-CONDITION: Output a logic high on the LED_pin.
*
* @return an enumeration for the LED_error status.
*
* @parameters :  [in] led_id.
*				 [in] led_configuration.
* \b Example Example:
* @code
* LED_on(enu_led_id_t ledPin, str_led_confige_t *LedConfig);
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
enu_led_error_status_t LED_on(enu_led_id_t ledPin)
{
	uint8_t error_state = LED_OK;
	uint8_t uint8_loc_conter = FALSE;
	for(uint8_loc_conter=FALSE;uint8_loc_conter<MAX_LEDS;uint8_loc_conter++)
	{
		if(gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_direction != OUTPUT_PIN)
		{
			error_state = LED_WRONG;
		  break;
		}
		else
		{
			if(ledPin == gl_Led_Config[uint8_loc_conter].led_id)
			{
				
				error_state = (enu_led_error_status_t) GPIO_write(  gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_port_num, 
													    gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_num, 
													   HIGH_LEVEL ); 
				break;
				
			}
			else
			{
				//do nothing
			}
			if(error_state != LED_OK)
			{
			error_state = LED_WRONG;
			break;
			}
			else
			{
				//do nothing
			}
		}
	  
	}
	
	return (enu_led_error_status_t)error_state;
	
}

/**********************************************************************
* Function : LED_off()
*//**
* \b Description:
*
* This function is used to Turn the LED on.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0)
* PRE-CONDITION: LED_ID needs to be passed
*
* POST-CONDITION: Output a logic low on the LED_pin.
*
* @return an enumeration for the LED_error status.
*
* @parameters :  [in] led_id.
*				 [in] led_configuration.
* \b Example Example:
* @code
* LED_off(enu_led_id_t ledPin, str_led_confige_t *LedConfig);
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
enu_led_error_status_t LED_off(enu_led_id_t ledPin)
{
	uint8_t error_state = LED_OK;
	uint8_t uint8_loc_conter = FALSE;
	for(uint8_loc_conter=FALSE;uint8_loc_conter<MAX_LEDS;uint8_loc_conter++)
	{
		if(gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_direction != OUTPUT_PIN)
		{
			error_state = LED_WRONG;
		  break;
		}
		else
		{
			if(ledPin == gl_Led_Config[uint8_loc_conter].led_id)
			{
				
				error_state = (enu_led_error_status_t) GPIO_write(  gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_port_num, 
													    gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_num, 
													   LOW_LEVEL ); 
				break;
				
			}
			else
			{
				//do nothing
			}
			if(error_state != LED_OK)
			{
			error_state = LED_WRONG;
			break;
			}
			else
			{
				//do nothing
			}
		}
	  
	}
	
	return (enu_led_error_status_t)error_state;
}

/**********************************************************************
* Function : LED_toggle()
*//**
* \b Description:
*
* This function is used to Turn the LED on.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0)
* PRE-CONDITION: LED_ID needs to be passed
*
* POST-CONDITION: Toggle the logic level on the LED_pin.
*
* @return an enumeration for the LED_error status.
*
* @parameters :  [in] led_id.
*				 [in] led_configuration.
*	
* \b Example Example:
* @code
* LED_toggle(enu_led_id_t ledPin, str_led_confige_t *LedConfig);
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

enu_led_error_status_t LED_toggle(enu_led_id_t ledPin)
{
	uint8_t error_state = LED_OK;
	uint8_t uint8_loc_conter = FALSE;
	for(uint8_loc_conter=FALSE;uint8_loc_conter<MAX_LEDS;uint8_loc_conter++)
	{
		if(gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_direction != OUTPUT_PIN)
		{
			error_state = LED_WRONG;
		  break;
		}
		else
		{
			if(ledPin == gl_Led_Config[uint8_loc_conter].led_id)
			{
				
				error_state = (enu_led_error_status_t) GPIO_toggle(gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_port_num, 
													    gl_Led_Config[uint8_loc_conter].gpio_for_led_confige.enu_pin_num); 
				break;
				
			}
			else
			{
				//do nothing
			}
			if(error_state != LED_OK)
			{
			error_state = LED_WRONG;
			break;
			}
			else
			{
				//do nothing
			}
		}
	  
	}
	
	return (enu_led_error_status_t)error_state;
}


/***End of File****************************************************/