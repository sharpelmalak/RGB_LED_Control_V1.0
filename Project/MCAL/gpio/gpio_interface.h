/*
**@file     : gpio_interface.h
**@brief    : this is header file to interface with GPIO 
**@author   : sharpel
**@date     : 14 june 2023
**@version  : 0.1
*/


#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/*INCLUDES*/
#include "common.h"

/*TYPEDEFS*/
typedef void (*ptr_GPIO_cb_t)(void);

// GPIO PORTS
typedef enum
{
	PORTA = 0,
	PORTB = 1,
	PORTC = 2,
	PORTD = 3,
	PORTE = 4,
	PORTF = 5,
	INVALID_PORT
}enu_GPIO_port_num_t;

// GPIO PINS
typedef enum
{
	PIN0 = 0,
	PIN1 = 1,
	PIN2 = 2,
	PIN3 = 3,
	PIN4 = 4,
	PIN5 = 5,
	PIN6 = 6,
	PIN7 = 7,
	INVALID_PIN
}enu_GPIO_pin_num_t;

// GPIO PIN DIRECTION
typedef enum
{
	INPUT_PIN  = 0,
	OUTPUT_PIN = 1,
	INVALID_DIRECTION
}enu_GPIO_pin_direction_t;

// GPIO PIN LEVEL
typedef enum
{
	LOW_LEVEL  = 0,
	HIGH_LEVEL = 1,
	INVALID_LEVEL
}enu_GPIO_pin_level_t;

// GPIO PIN MODE
typedef enum
{
	DIGITAL_PIN  = 0,
	ANALOG_PIN   = 1,
	INVALID_MODE
}enu_GPIO_pin_mode_t;

// GPIO PIN OUT CURRENT 
typedef enum
{
	PIN_2MA_CURRENT  = 0,
	PIN_4MA_CURRENT  = 1,
	PIN_8MA_CURRENT  = 2,
	INVALID_OUT_CURRENT
}enu_GPIO_pin_out_current_t;

// GPIO PIN INTERNAL ATTACH 
typedef enum
{
	OPEN_DRAIN  = 0,
	PULL_UP     = 1,
	PULL_DOWN   = 2,
	INVALID_INTERNAL_TYPE
}enu_GPIO_pin_internal_type_t;

// GPIO PIN EVENT TRIGGER FOR INTERRUPTS
typedef enum
{
	TRIGGER_FALLING_EDGE                  = 0,
	TRIGGER_RISING_EDGE                      ,
	TRIGGER_BOTH_RISING_FALLING_EDGES        ,
	TRIGGER_LOW_LEVEL               				 ,
	TRIGGER_HIGH_LEVEL              				 ,
	INVALID_TRIGGER
}enu_GPIO_pin_event_trigger_t;

typedef struct
{
	// for common direction usage [Required]
	enu_GPIO_port_num_t          enu_port_num;
	enu_GPIO_pin_num_t           enu_pin_num;
	enu_GPIO_pin_direction_t     enu_pin_direction;       // this field selects one from two options (input,output)
	enu_GPIO_pin_mode_t          enu_pin_mode;
	// for output direction usage  [if direction is output]
	enu_GPIO_pin_level_t         enu_pin_level;            //in case the pin configured as output this field must set 
	enu_GPIO_pin_out_current_t   enu_pin_out_current;      //in case the pin configured as output this field must set
	// for input direction usage   [if direction is input]
	enu_GPIO_pin_internal_type_t enu_pin_internal_type;     //in case the pin configured as input this field must set 
	boolean                      bool_use_interrupt;        //optional    
	enu_GPIO_pin_event_trigger_t enu_GPIO_pin_event_trigger;//in case you make interrupt true this field must set
	ptr_GPIO_cb_t                ptr_GPIO_cb;               //in case you make interrupt true this field must set
}str_GPIO_configs_t;	

// GPIO ERROR STATUS
typedef enum
{
	GPIO_OKAY  = 0,
	GPIO_NULL_REF,
	GPIO_PORT_ERROR,
	GPIO_PIN_ERROR,
	GPIO_DIRECTION_ERROR,
	GPIO_MODE_ERROR,
	GPIO_OUT_CURRENT_ERROR,
	GPIO_INTERNAL_TYPE_ERROR,
	GPIO_LEVEL_ERROR,
	GPIO_EVENT_TRIGGER_ERROR,
	GPIO_NULL_CB_REF
}enu_GPIO_status_t;

/*PROTOTYPES (APIS)*/

/*
*@name       : GPIO_init
*@berif      : this function initialies GPIO pin as ( OUTPUT , INPUT OR INTERRUPT )
*@param[in]  : pointer to str_GPIO_configs_t type with desired option 
               [REQUIRED OPTOINS]
								- enu_port_num               : Select Port Number 
								- enu_pin_num                : Select Pin Number
								- enu_pin_direction          : Select Pin Direction
								- enu_pin_mode               : Select Pin Mode
               [Case Output]                 
								- enu_pin_level              : Select Output level
								- enu_pin_out_current        : Select output current
               [Case Input]                  
								- enu_pin_internal_type      : Select Internal attach type
								- bool_use_interrupt         : Select if it is interrupt or not
								- enu_GPIO_pin_event_trigger : Select sense trigger
								- ptr_GPIO_cb                : Set call back to upper layer
					
*@return     : GPIO_OKAY                     (In case of success initialization)
							 GPIO_NULL_REF                 (In case of Null pointer argument )
							 GPIO_PORT_ERROR               (In case of Invalid port number   )
							 GPIO_PIN_ERROR                (In case of Invalid pin nimber    )
							 GPIO_DIRECTION_ERROR          (In case of Invalid pin direction )
							 GPIO_MODE_ERROR               (In case of Invalid mode selection)
							 GPIO_OUT_CURRENT_ERROR        (In case of Invalid output current)
							 GPIO_INTERNAL_TYPE_ERROR      (In case of Invalid internal type )
							 GPIO_LEVEL_ERROR              (In case of Invalid output level  )
							 GPIO_EVENT_TRIGGER_ERROR      (In case of Invalid sense trigger )
							 GPIO_NULL_CB_REF              (In case of Null pointer to cbf   )
*/
enu_GPIO_status_t GPIO_init (str_GPIO_configs_t *ptr_GPIO_configs);

/*
*@name       : GPIO_write
*@berif      : this function write desired level on specific pin 
*@param[in]  :  - enu_port_num_t               : Select Port Number 
								- enu_pin_num_t                : Select Pin Number
								- enu_pin_level_t              : Select Output level
					
*@return     : GPIO_OKAY                     (In case of success operation     )
							 GPIO_PORT_ERROR               (In case of Invalid port number   )
							 GPIO_PIN_ERROR                (In case of Invalid pin nimber    )
							 GPIO_LEVEL_ERROR              (In case of Invalid output level  )
*/
enu_GPIO_status_t GPIO_write(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num, enu_GPIO_pin_level_t arg_level);
/*
*@name       : GPIO_read
*@berif      : this function read value from specific pin
*@param[in]  :  - pointer to boolean to store value
								- enu_port_num               : Select Port Number 
								- enu_pin_num                : Select Pin Number
					
*@return     : GPIO_OKAY                     (In case of success initialization)
							 GPIO_NULL_REF                 (In case of Null pointer argument )
							 GPIO_PORT_ERROR               (In case of Invalid port number   )
							 GPIO_PIN_ERROR                (In case of Invalid pin nimber    )
*/
enu_GPIO_status_t GPIO_read(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num, boolean *ptr_value);
/*
*@name       : GPIO_toggle
*@berif      : this function toggle desired pin 
*@param[in]  :  - enu_port_num_t             : Select Port Number 
								- enu_pin_num_t              : Select Pin Number
					
*@return     : GPIO_OKAY                     (In case of success operation     )
							 GPIO_PORT_ERROR               (In case of Invalid port number   )
							 GPIO_PIN_ERROR                (In case of Invalid pin nimber    )
*/
enu_GPIO_status_t GPIO_toggle(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num);
/*
*@name       : GPIO_enable_interrupt
*@berif      : this function enable interrupt for desired initialized pin
*@param[in]  :  - enu_port_num_t             : Select Port Number 
								- enu_pin_num_t              : Select Pin Number
					
*@return     : Void
*/
void GPIO_enable_interrupt(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num);
/*
*@name       : GPIO_disable_interrupt
*@berif      : this function disable interrupt for desired initialized pin
*@param[in]  :  - enu_port_num_t             : Select Port Number 
								- enu_pin_num_t              : Select Pin Number
					
*@return     : Void
*/
void GPIO_disable_interrupt(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num);




#endif




