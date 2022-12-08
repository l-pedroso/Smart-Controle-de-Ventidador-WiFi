#include <atmel_start.h>
#include "touch_example.h"
#include "triac_driver/triac_driver.h"
#include "atmel_start_pins.h"

int main(void)
{
	triac_driver_config config;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	config.get_zero_pin_state_func = Zerocross_get_level;
	config.triac_control_func = Triac_set_level;
	config.trigger_angle = 0;
	config.triac_state = off;
	triac_driver_init(config);

	/* Replace with your application code */
	while (1) {
		touch_example();
	
		 	
	}
}
