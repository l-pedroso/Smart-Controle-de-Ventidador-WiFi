/*
 * triac_driver.h
 *
 * Created: 06/12/2022 10:34:25
 *  Author: lpedroso
 */ 


#ifndef TRIAC_DRIVER_H_
#define TRIAC_DRIVER_H_

#include <compiler.h>


#define MIN_ANGLE	     0
#define MAX_ANGLE		 150
#define TRIAC_ON_TIME	 5
#define FREQUENCY        60
#define ANGLE_TO_TIMEBASE(x) (((1.0/(FREQUENCY*2))/0.0001*x)/180) 

typedef enum{
	off,
	on
	}output_state;
	
typedef struct{
	bool(*get_zero_pin_state_func)();
	void(*triac_control_func)(bool);
	uint8_t trigger_angle;
	output_state triac_state;
}triac_driver_config;	


void triac_driver_init(triac_driver_config user_config);
void triac_driver_tick();
void triac_set_angle(uint8_t angle);
uint8_t triac_get_angle();
void triac_set_output_state(output_state state);
output_state triac_get_output_state();



#endif /* TRIAC_DRIVER_H_ */