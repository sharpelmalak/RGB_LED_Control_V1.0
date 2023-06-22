#ifndef APP_H_
#define APP_H_

#include "led.h"
#include "button.h"
#include "gpt_interface.h"


#define MAX_DELAY     100000

typdef enum {
	APP_STATE_ZERO = 0;
	APP_STATE_ONE,
	APP_STATE_TWO,
	APP_STATE_THREE
};

void app_init(void);
void app_start(void);
void switch_cycle_pwm(void);
void debouncing_handler(void);

#endif

