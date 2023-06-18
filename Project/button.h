

#ifndef BUTTON_H_
#define BUTTON_H_


#include "button_cfg.h"

// enum definition for Errors types
typedef enum Button_error {
	BUTTON_OK = 0,
	BUTTON_WRONG
}enu_button_error_status_t;


enu_button_error_status_t BUTTON_init(void);
enu_button_error_status_t BUTTON_read(enu_button_id_t button_id,boolean *value);


#endif