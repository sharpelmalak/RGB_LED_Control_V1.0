/*
**@file     : systick_interface.h
**@brief    : this is header file to interface with Systick module 
**@author   : sharpel
**@date     : 19 june 2023
**@version  : 0.1
*/


#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/*includes*/

#include "common.h"

/*typdefs*/
typedef void (*ptrf_systick_cb_t)(void);

// error status
typedef enum
{
	SYSTICK_OKAY           = 0,
	INVALID_ARGUMENT_TIME,
	NULL_CB_REF,
	INVALID_OPERATION
}enu_systick_status_t;	





/*
*@name       : SYSTICK_init
*@berif      : this function init Systick Module
*@param[in]  : void
						
					
*@return     :  SYSTICK_OKAY      (In case of successfull operation)
                INVALID_OPERATION (In case of re initialization)
*/
enu_systick_status_t SYSTICK_init (void);

/*
*@name       : SYSTICK_enable_interrupt
*@berif      : this function enable interrupt in Systick Module
*@param[in]  : void
						
					
*@return     :  SYSTICK_OKAY      (In case of successfull operation)
                INVALID_OPERATION (In case of re enable interruot)
*/
enu_systick_status_t SYSTICK_enable_interrupt (void);
/*
*@name       : SYSTICK_disable_interrupt
*@berif      : this function disable interrupt in Systick Module
*@param[in]  : void
						
					
*@return     :  SYSTICK_OKAY      (In case of successfull operation)
                INVALID_OPERATION (In case of re disable interrupt)
*/
enu_systick_status_t SYSTICK_disable_interrupt (void);
/*
*@name       : SYSTICK_synchronous_time_ms
*@berif      : this function generate synchronous delay in milli seconds
*@param[in]  :  - arg_time_ms               : the desired delay in milli second 
						
					
*@return     : SYSTICK_OKAY                  (In case of success operation     )
							 INVALID_ARGUMENT_TIME         (In case of Invalid argument      )
*/
enu_systick_status_t SYSTICK_synchronous_time_ms (uint32_t arg_time_ms);

/*
*@name       : SYSTICK_Asynchronous_time_ms
*@berif      : this function generate Asynchronous delay in milli seconds (using interrupt)
*@param[in]  :  - arg_time_ms               : the desired delay in milli second
                - ptrf_arg_systick_cb       : the call back to be executed when time out
						
					
*@return     : SYSTICK_OKAY                  (In case of success operation     )
							 INVALID_ARGUMENT_TIME         (In case of Invalid argument      )
							 NULL_CB_REF                   (In case of Null CB pointer       )
*/
enu_systick_status_t SYSTICK_Asynchronous_time_ms(uint32_t arg_time_ms,ptrf_systick_cb_t ptrf_arg_systick_cb);

/*
*@name       : SYSTICK_stop
*@berif      : this function reset Systick module to idle (disable interrupt and reset configuration)
*@param[in]  :  void
						
					
*@return     :  SYSTICK_OKAY      (In case of successfull operation)
                INVALID_OPERATION (In case of re stoping systick module)
*/
enu_systick_status_t SYSTICK_stop(void);

#endif



