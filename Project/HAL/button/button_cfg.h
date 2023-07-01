/*
 * button_cfg.h
 * Created: 18/6/2023 4:14:40 AM
 *  Author: Mahmoud Mowafey
 */ 

/** @file button_cfg.h
 * @brief This module contains interface definitions for the
 * button configuration. This is the header file for the definition of the
 * interface for retrieving the button configuration table.
*/


#ifndef BUTTON_CFG_H_ 
#define BUTTON_CFG_H_
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
 
#define MAX_BUTTONS      2
 
 
typedef enum BUTTON_ID {
	BUTTON_0 = 0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_10,
	BUTTON_MAX
}enu_button_id_t;

/**
 * Defines the Button configuration table's elements that are used
 * by Button_init to configure the Buttons.
 */
typedef struct button{
	str_GPIO_configs_t 	 gpio_for_button_confige;
	enu_button_id_t      button_id;
}str_button_confige_t;



#endif



