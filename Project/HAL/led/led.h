/*
 * led.h
 * Created: 18/6/2023 4:14:40 AM
 *  Author: Mahmoud Mowafey
 */ 

/** @file led.h
 * @brief This module contains interface definitions for the
 * LED APIs. 
*/

#ifndef LED_H_
#define LED_H_
/**********************************************************************
* Includes
**********************************************************************/
#include "gpio_interface.h"
#include "led_cfg.h"            /* For this modules definitions */

/**********************************************************************
* Module Typedefs
**********************************************************************/
// enum definition for Errors types
typedef enum LED_error {
	LED_OK = 0,
	LED_WRONG
}enu_led_error_status_t;

/**
 * Defines the possible states for a the LED pin.
 */
// typedef enum
// {
//	 LED_LOW, /** Defines digital state ground */
//	 LED_HIGH, /** Defines digital state power */
//	 LED_PIN_STATE_MAX /** Defines the maximum digital state */
// }enu_led_state_t;

/**********************************************************************
* Function Prototypes
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
* @return An enumeration for the LED_error status.
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
enu_led_error_status_t LED_init(void);

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
enu_led_error_status_t LED_on(enu_led_id_t ledPin);

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
enu_led_error_status_t LED_off(enu_led_id_t ledPin);

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

enu_led_error_status_t LED_toggle(enu_led_id_t ledPin);



#endif /* LED_H_ */
/***End of File****************************************************/

