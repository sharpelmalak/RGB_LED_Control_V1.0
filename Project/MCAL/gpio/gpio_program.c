/*
**@file     : gpio_pogram.c
**@brief    : this file implements all GPIO APIs 
**@author   : sharpel
**@date     : 14 june 2023
**@version  : 0.1
*/



#include "TM4C123.h"
#include "gpio_private.h"
#include "gpio_interface.h"

#define UNLOCK_VALUE    0x4C4F434B

// global array of call back functions for 6 ports [ A , B , C , D , E , F ]
static ptr_GPIO_cb_t  gl_arr_pf_gpio_cb[INVALID_PORT][INVALID_PIN]  =
{
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//PORT A
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//PORT B
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//PORT C
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//PORT D
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//PORT E
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//PORT F 
};

static boolean gl_bool_is_port_init[INVALID_PORT]       ={FALSE};
static boolean gl_bool_is_interrupt_enable[INVALID_PORT]={FALSE};
static boolean gl_bool_is_irq_enable                    = FALSE;

enu_GPIO_status_t GPIO_init (str_GPIO_configs_t *ptr_GPIO_configs)
{
	enu_GPIO_status_t enu_GPIO_status_return = GPIO_OKAY;
	
	// check on null pointer
	if(ptr_GPIO_configs == NULL)
	{
		enu_GPIO_status_return = GPIO_NULL_REF;
	}
  else
	{
		// check on port number
		if(ptr_GPIO_configs->enu_port_num < INVALID_PORT)
		{
			if(gl_bool_is_port_init[ptr_GPIO_configs->enu_port_num] != TRUE)
			{
				// enable and provide clock to GPIO portx in run mode
			  SET_BIT(RCGCGPIO,ptr_GPIO_configs->enu_port_num);
			/* TODO : the SCGCGPIO and DCGCGPIO registers can be programmed in the
                same manner to enable clocking in Sleep and Deep-Sleep modes.*/
				gl_bool_is_port_init[ptr_GPIO_configs->enu_port_num] = TRUE ;
			}
			else
			{
				GPIOLOCK(ptr_GPIO_configs->enu_port_num) = UNLOCK_VALUE;
				SET_BIT(GPIOCR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num); 
				GPIOLOCK(ptr_GPIO_configs->enu_port_num) = FALSE;
			}
			
			
			// check on pin number
			if(ptr_GPIO_configs->enu_pin_num < INVALID_PIN)
			{
				//check on pin direcction
				if(ptr_GPIO_configs->enu_pin_direction == INPUT_PIN)
				{
					//set direction of pin input
					CLEAR_BIT(GPIODIR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					 // select internal attach type
					if(ptr_GPIO_configs->enu_pin_internal_type == OPEN_DRAIN)
					{
						SET_BIT(GPIOODR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIOPUR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIOPDR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else if(ptr_GPIO_configs->enu_pin_internal_type == PULL_UP)
					{
						SET_BIT(GPIOPUR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIOODR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIOPDR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else if(ptr_GPIO_configs->enu_pin_internal_type == PULL_DOWN)
					{
						SET_BIT(GPIOPDR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIOODR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIOPUR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else
					{
						enu_GPIO_status_return = GPIO_INTERNAL_TYPE_ERROR;
					}
					
					// check all cases are passed
					if(enu_GPIO_status_return == GPIO_OKAY)
					{
						//case user initilaizes pin as interrupt
						if(ptr_GPIO_configs->bool_use_interrupt == TRUE)
						{
							if(ptr_GPIO_configs->ptr_GPIO_cb == NULL)
							{
								enu_GPIO_status_return = GPIO_NULL_CB_REF;
							}
							else
							{
								//check on selected event trigger
								if(ptr_GPIO_configs->enu_GPIO_pin_event_trigger < INVALID_TRIGGER)
								{
									// mask interrupt
							   	CLEAR_BIT(GPIOIM(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
									// set callback in global 2D array of callbacks
									gl_arr_pf_gpio_cb[ptr_GPIO_configs->enu_port_num][ptr_GPIO_configs->enu_pin_num] = ptr_GPIO_configs->ptr_GPIO_cb;
									// case (edge-sensitive)
									if(ptr_GPIO_configs->enu_GPIO_pin_event_trigger < TRIGGER_LOW_LEVEL)
									{
										CLEAR_BIT(GPIOIS(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
										
										//check on both edges selection
										if(ptr_GPIO_configs->enu_GPIO_pin_event_trigger == TRIGGER_BOTH_RISING_FALLING_EDGES)
										{
											SET_BIT(GPIOIBE(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
										} 
										else
										{
											// case falling edge
											if(ptr_GPIO_configs->enu_GPIO_pin_event_trigger == TRIGGER_FALLING_EDGE)
											{
												CLEAR_BIT(GPIOIBE(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
												CLEAR_BIT(GPIOIEV(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
											}
											// case rising edge
											else
											{
												CLEAR_BIT(GPIOIBE(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
												SET_BIT(GPIOIEV(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
											}
										}
									}
									//case (level-sensitive)
									else
									{
										SET_BIT(GPIOIS(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
										// case low level
										if(ptr_GPIO_configs->enu_GPIO_pin_event_trigger == TRIGGER_LOW_LEVEL)
										{
											CLEAR_BIT(GPIOIBE(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
											CLEAR_BIT(GPIOIEV(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
										}
										// case high level
										else
										{
											CLEAR_BIT(GPIOIBE(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
											SET_BIT(GPIOIEV(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
										}
									}
							}
							else
							{
								enu_GPIO_status_return = GPIO_EVENT_TRIGGER_ERROR;
							}
							}
							
						}
						else
						{
							// do nothing
						}
					}
					else
					{
						//do nothing
					}
					
				}
				else if(ptr_GPIO_configs->enu_pin_direction == OUTPUT_PIN)
				{
					// set direction of pin to output
				  SET_BIT(GPIODIR(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					//Set the drive strength for pin
					if(ptr_GPIO_configs->enu_pin_out_current == PIN_2MA_CURRENT)
					{
						SET_BIT(GPIODR2R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIODR4R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIODR8R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else if(ptr_GPIO_configs->enu_pin_out_current == PIN_4MA_CURRENT)
					{
						SET_BIT(GPIODR4R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIODR2R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIODR8R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else if(ptr_GPIO_configs->enu_pin_out_current == PIN_8MA_CURRENT)
					{
						SET_BIT(GPIODR8R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIODR2R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						CLEAR_BIT(GPIODR4R(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else
					{
						enu_GPIO_status_return = GPIO_OUT_CURRENT_ERROR;
					}
					// check that all cases are passed
					if (enu_GPIO_status_return == GPIO_OKAY)	
					{
							//Set the pin level
							if(ptr_GPIO_configs->enu_pin_level == HIGH_LEVEL)
							{
								SET_BIT(GPIODATA(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
							}
							else if(ptr_GPIO_configs->enu_pin_level == LOW_LEVEL)
							{
								CLEAR_BIT(GPIODATA(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
							}
							else
							{
								enu_GPIO_status_return = GPIO_LEVEL_ERROR;
							}
					}
					else
					{
						//do nothing
					}
					
				}
				else 
				{
				 enu_GPIO_status_return = GPIO_DIRECTION_ERROR;
				}
				 // check that all cases are passed
				if(enu_GPIO_status_return == GPIO_OKAY)
				{
					if(ptr_GPIO_configs->enu_pin_mode == DIGITAL_PIN)
					{
						// select GPIO functionality
						CLEAR_BIT(GPIOAFSEL(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						// config pin as digital
						SET_BIT(GPIODEN(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						// disable analog pin
						CLEAR_BIT(GPIOAMSEL(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						
					}
					else if (ptr_GPIO_configs->enu_pin_mode == ANALOG_PIN)
					{
						// select GPIO functionality
						CLEAR_BIT(GPIOAFSEL(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						// disable digitale pin function
						CLEAR_BIT(GPIODEN(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
						// enable analog pin
						SET_BIT(GPIOAMSEL(ptr_GPIO_configs->enu_port_num),ptr_GPIO_configs->enu_pin_num);
					}
					else
					{
						enu_GPIO_status_return = GPIO_MODE_ERROR;
					}
					
						
				}
				else
				{
					//do nothing
				}

				
			}
			else
			{
				enu_GPIO_status_return = GPIO_PIN_ERROR;
			}
			
		}
		else
		{
			enu_GPIO_status_return = GPIO_PORT_ERROR;
		}
		
	}	

 
  return enu_GPIO_status_return;	
}


enu_GPIO_status_t GPIO_write(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num, enu_GPIO_pin_level_t arg_level)
{
	enu_GPIO_status_t enu_GPIO_status_return = GPIO_OKAY;
	
	if(arg_port_num < INVALID_PORT)
	{
		if(arg_pin_num < INVALID_PIN)
		{
			if(arg_level == HIGH_LEVEL)
			{
				SET_BIT(GPIODATA(arg_port_num),arg_pin_num);
			}
			else if (arg_level == LOW_LEVEL)
			{
				CLEAR_BIT(GPIODATA(arg_port_num),arg_pin_num);
			}
			else
			{
				enu_GPIO_status_return = GPIO_LEVEL_ERROR;
			}
		}
		else
		{
			enu_GPIO_status_return = GPIO_PIN_ERROR;
		}
	}
	else
	{
		enu_GPIO_status_return = GPIO_PORT_ERROR;
	}
	
	return enu_GPIO_status_return;
}

enu_GPIO_status_t GPIO_read(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num, boolean *ptr_value)
{
		enu_GPIO_status_t enu_GPIO_status_return = GPIO_OKAY;
	
	if(arg_port_num < INVALID_PORT)
	{
		if(arg_pin_num < INVALID_PIN)
		{
			if(ptr_value != NULL)
			{
				*ptr_value = GET_BIT(GPIODATA(arg_port_num),arg_pin_num);
			}
			else
			{
				enu_GPIO_status_return = GPIO_NULL_REF;
			}
		}
		else
		{
			enu_GPIO_status_return = GPIO_PIN_ERROR;
		}
	}
	else
	{
		enu_GPIO_status_return = GPIO_PORT_ERROR;
	}
	
	return enu_GPIO_status_return;
}


enu_GPIO_status_t GPIO_toggle(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num)
{
	
	enu_GPIO_status_t enu_GPIO_status_return = GPIO_OKAY;
	
	if(arg_port_num < INVALID_PORT)
	{
		if(arg_pin_num < INVALID_PIN)
		{
			TOGGLE_BIT(GPIODATA(arg_port_num),arg_pin_num);
		}
		else
		{
			enu_GPIO_status_return = GPIO_PIN_ERROR;
		}
	}
	else
	{
		enu_GPIO_status_return = GPIO_PORT_ERROR;
	}
	
	return enu_GPIO_status_return;

}

void GPIO_enable_interrupt(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num)
{
	if(arg_port_num < INVALID_PORT)
	{
		if(arg_pin_num < INVALID_PIN)
		{
			// unmask interrupt for given pin
			SET_BIT(GPIOIM(arg_port_num),arg_pin_num);
			if(gl_bool_is_interrupt_enable[arg_port_num] != TRUE)
			{
				switch(arg_port_num)
				{
					case PORTA:
					{
						NVIC_EnableIRQ(GPIOA_IRQn);
						break;
					}
					case PORTB:
					{
						NVIC_EnableIRQ(GPIOB_IRQn);
						break;
					}
					case PORTC:
					{
						NVIC_EnableIRQ(GPIOC_IRQn);
						break;
					}
					case PORTD:
					{
						NVIC_EnableIRQ(GPIOD_IRQn);
						break;
					}
					case PORTE:
					{
						NVIC_EnableIRQ(GPIOE_IRQn);
						break;
					}
					case PORTF:
					{
						NVIC_EnableIRQ(GPIOF_IRQn);
						break;
					}
					default:
					{
						//do nothing
						break;
					}
				}
				
				// set port index to true to not re enable it again
				gl_bool_is_interrupt_enable[arg_port_num] = TRUE;
				if(gl_bool_is_irq_enable != TRUE)
				{
					__enable_irq();
					gl_bool_is_irq_enable = TRUE;
				}
				else
				{
					//donothing
				}
			}
			else
			{
				//nothing
			}
			
		}
		else
		{
			//NOTHING
		}
	}
	else
	{
		//NOTHING
	}
}
void GPIO_disable_interrupt(enu_GPIO_port_num_t arg_port_num, enu_GPIO_pin_num_t arg_pin_num)
{
	if(arg_port_num < INVALID_PORT)
	{
		if(arg_pin_num < INVALID_PIN)
		{
			CLEAR_BIT(GPIOIM(arg_port_num),arg_pin_num);
		}
		else
		{
			//NOTHING
		}
	}
	else
	{
		//NOTHING
	}
}

void  GPIOA_Handler (void)
{
	uint8_t loc_pin_counter = 0;
	for(loc_pin_counter=0;loc_pin_counter<INVALID_PIN;loc_pin_counter++)
	{
		
		//search for interrupt source pin
		if(GET_BIT(GPIORIS(PORTA),loc_pin_counter)==TRUE)
		{
			  //clear interrupt flag
					SET_BIT(GPIOICR(PORTA),loc_pin_counter);
			  //check on call back to be executed
			  if(gl_arr_pf_gpio_cb[PORTA][loc_pin_counter] != NULL)
				{
					//execute call back
					gl_arr_pf_gpio_cb[PORTA][loc_pin_counter]();
				}
				else
				{
					//do nothing
				}
				break; //terminate loop;
		}
		else
		{
			//do nothing
		}
	}
	
}

void  GPIOB_Handler (void)
{
	uint8_t loc_pin_counter = 0;
	for(loc_pin_counter=0;loc_pin_counter<INVALID_PIN;loc_pin_counter++)
	{
		
		//search for interrupt source pin
		if(GET_BIT(GPIORIS(PORTB),loc_pin_counter)==TRUE)
		{
			  //clear interrupt flag
					SET_BIT(GPIOICR(PORTB),loc_pin_counter);
			  //check on call back to be executed
			  if(gl_arr_pf_gpio_cb[PORTB][loc_pin_counter] != NULL)
				{
					//execute call back
					gl_arr_pf_gpio_cb[PORTB][loc_pin_counter]();
				}
				else
				{
					//do nothing
				}
				break; //terminate loop;
		}
		else
		{
			//do nothing
		}
	}
}
void  GPIOC_Handler (void)
{
	uint8_t loc_pin_counter = 0;
	for(loc_pin_counter=0;loc_pin_counter<INVALID_PIN;loc_pin_counter++)
	{
		
		//search for interrupt source pin
		if(GET_BIT(GPIORIS(PORTC),loc_pin_counter)==TRUE)
		{
			//clear interrupt flag
					SET_BIT(GPIOICR(PORTC),loc_pin_counter);
			  //check on call back to be executed
			  if(gl_arr_pf_gpio_cb[PORTC][loc_pin_counter] != NULL)
				{
					//execute call back
					gl_arr_pf_gpio_cb[PORTC][loc_pin_counter]();
				}
				else
				{
					//do nothing
				}
				break; //terminate loop;
		}
		else
		{
			//do nothing
		}
	}
}

void  GPIOD_Handler (void)
{
	uint8_t loc_pin_counter = 0;
	for(loc_pin_counter=0;loc_pin_counter<INVALID_PIN;loc_pin_counter++)
	{
		
		//search for interrupt source pin
		if(GET_BIT(GPIORIS(PORTD),loc_pin_counter)==TRUE)
		{
			//clear interrupt flag
					SET_BIT(GPIOICR(PORTD),loc_pin_counter);
			  //check on call back to be executed
			  if(gl_arr_pf_gpio_cb[PORTD][loc_pin_counter] != NULL)
				{
					//execute call back
					gl_arr_pf_gpio_cb[PORTD][loc_pin_counter]();
				}
				else
				{
					//do nothing
				}
				break; //terminate loop;
		}
		else
		{
			//do nothing
		}
	}
}
void  GPIOE_Handler (void)
{
		uint8_t loc_pin_counter = 0;
	for(loc_pin_counter=0;loc_pin_counter<INVALID_PIN;loc_pin_counter++)
	{
		
		//search for interrupt source pin
		if(GET_BIT(GPIORIS(PORTE),loc_pin_counter)==TRUE)
		{
			  //clear interrupt flag
					SET_BIT(GPIOICR(PORTE),loc_pin_counter);
			  //check on call back to be executed
			  if(gl_arr_pf_gpio_cb[PORTE][loc_pin_counter] != NULL)
				{
					//execute call back
					gl_arr_pf_gpio_cb[PORTE][loc_pin_counter]();
				}
				else
				{
					//do nothing
				}
				break; //terminate loop;
		}
		else
		{
			//do nothing
		}
	}
}
void  GPIOF_Handler (void)
{
		uint8_t loc_pin_counter = 0;
	for(loc_pin_counter=0;loc_pin_counter<INVALID_PIN;loc_pin_counter++)
	{
		
		//search for interrupt source pin
		if(GET_BIT(GPIORIS(PORTF),loc_pin_counter)==TRUE)
		{
			  //clear interrupt flag
					SET_BIT(GPIOICR(PORTF),loc_pin_counter);
			  //check on call back to be executed
			  if(gl_arr_pf_gpio_cb[PORTF][loc_pin_counter] != NULL)
				{
					//execute call back
					gl_arr_pf_gpio_cb[PORTF][loc_pin_counter]();

				}
				else
				{
					//do nothing
				}
				break; //terminate loop;
		}
		else
		{
			//do nothing
		}
	}
}


