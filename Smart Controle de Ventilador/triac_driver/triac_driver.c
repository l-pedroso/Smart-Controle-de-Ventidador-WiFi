/*
 * triac_driver.c
 *
 * Created: 06/12/2022 10:34:42
 *  Author: lpedroso
 */ 

#include "triac_driver.h"
#include "atmel_start_pins.h"

static bool driver_started = 0;
static triac_driver_config driver_config;


void inline static tick_process(){
	
	static bool flag_zero_sync = 0;
	static bool flag_zero_low = 0;
	static bool flag_zero_high = 0;
	static bool flag_triac_off = 0;
    static uint16_t cnt_angle = 0;
	static uint16_t cnt_triac = 0;

	if(driver_config.triac_state == 1 && driver_config.trigger_angle >= 10){
	
			if(driver_config.get_zero_pin_state_func() == 0 && flag_zero_sync == 0){
				flag_zero_sync = 1;
			}
			
			if(driver_config.get_zero_pin_state_func() == 0 && flag_zero_sync == 1){
				
				flag_zero_high = 0;
				
				if(flag_zero_low == 0){
					cnt_angle = ANGLE_TO_TIMEBASE(driver_config.trigger_angle); 
					flag_zero_low = 1;
					cnt_triac = TRIAC_ON_TIME; 
					flag_triac_off = 0;
				}
				if(cnt_angle > 0) cnt_angle--;
				
				if(cnt_angle == 0 && flag_triac_off == 0){
					driver_config.triac_control_func(1);
					if(cnt_triac > 0)cnt_triac--;
					if(cnt_triac == 0){
						driver_config.triac_control_func(0);
						flag_triac_off = 1;
					}
				}
			}
			
			if(driver_config.get_zero_pin_state_func() == 1 && flag_zero_sync == 1){
				
				flag_zero_low = 0;
				
				if(flag_zero_high == 0){
					cnt_angle = ANGLE_TO_TIMEBASE(driver_config.trigger_angle);
					flag_zero_high = 1;
					cnt_triac = TRIAC_ON_TIME; 
					flag_triac_off = 0;
				}
				if(cnt_angle > 0) cnt_angle--;
				
				if(cnt_angle == 0 && flag_triac_off == 0){
					driver_config.triac_control_func(1);
					if(cnt_triac > 0) cnt_triac--;
					if(cnt_triac == 0){
						driver_config.triac_control_func(0);
						flag_triac_off = 1;
					}
				}
			}		
	}else if (driver_config.triac_state == 1 &&  driver_config.trigger_angle < 10){
		driver_config.triac_control_func(1);
	}else{
		driver_config.triac_control_func(0);
	}
	
}

void triac_driver_tick(){
	if(driver_started){
		tick_process();
	}
}

void triac_driver_init(triac_driver_config user_config){
	driver_config = user_config;
	driver_started = 1;
	
}


void triac_set_angle(uint8_t angle){
	if(angle > MAX_ANGLE) angle = MAX_ANGLE;
	if(angle < MIN_ANGLE) angle = MIN_ANGLE;
	driver_config.trigger_angle = angle;
}


uint8_t triac_get_angle(){
	return driver_config.trigger_angle;
}


void triac_set_output_state(output_state state) {
	driver_config.triac_state = state;		
}

output_state triac_get_output_state(){
	return driver_config.triac_state;
}


