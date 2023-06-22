#ifndef APP_H_
#define APP_H_

#include "led.h"
#include "button.h"
#include "htimer_interface.h"


#define DEBOUNCING_DELAY     200

typedef enum {
	APP_STATE_ZERO = 0,
	APP_STATE_ONE,
	APP_STATE_TWO,
	APP_STATE_THREE
}en_app_states_t;

#define DUTY_CYCLE_30           30
#define DUTY_CYCLE_60           60
#define DUTY_CYCLE_90           90
#define SIGNAL_DURATION_MS      500

void app_init(void);
void app_start(void);
void switch_cycle_pwm(void);


#endif

