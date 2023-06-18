/*
 * led_cfg.h
 * Created: 18/6/2023 4:14:40 AM
 *  Author: Mahmoud Mowafey
 */ 

/** @file led_cfg.h
 * @brief This module contains interface definitions for the
 * LED configuration. This is the header file for the definition of the
 * interface for retrieving the LED configuration table.
*/

#ifndef LED_CFG_H_
#define LED_CFG_H_

/**********************************************************************
* Includes
**********************************************************************/
#include "gpio_interface.h" /* For this modules definitions */

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Module Typedefs
**********************************************************************/
/**
 * Defines an enumerated list of the LEDs. 
 * The last element is used to specify the maximum number of
 * enumerated labels.
 */
 
 #define MAX_LEDS      3
 
 
typedef enum LED_ID {
	LED_RED = 0,
	LED_BLUE,
	LED_GREEN,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
	LED_8,
	LED_9,
	LED_10,
	LED_MAX
}enu_led_id_t;

/**
 * Defines the LED configuration table's elements that are used
 * by LED_Init to configure the LEDs.
 */
typedef struct led{
	str_GPIO_configs_t 	 gpio_for_led_confige;
	enu_led_id_t led_id;
}str_led_confige_t;

///**********************************************************************
//* Module Function Prototypes
//**********************************************************************/
//const str_led_confige_t *const LED_ConfigGet(void);
///***End of File****************************************************/

#endif





