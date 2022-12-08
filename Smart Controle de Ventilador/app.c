/*
 * app.c
 *
 * Created: 06/12/2022 11:12:07
 *  Author: lpedroso
 */ 

#include "triac_driver/triac_driver.h"
#include "app.h"
#include "atmel_start_pins.h"


static dir fan_direction = INITIAL_DIRECTION; 
static output_state fan_state = INITIAL_STATE;
static uint8_t angle = INITIAL_ANGLE;
volatile uint16_t cnt_direction  = 0;

/****************************************************** 
* LAMP CONTROL                                        *
*******************************************************/
void set_lamp_output(bool state){
	Rele3_set_level(state);
}

void toggle_lamp_output(){	
	//ToDo zerocross implementation
	Rele3_toggle_level();
}


/******************************************************
* FAN ON/OFF CONTROL                                  *
*******************************************************/
void set_fan_output(output_state state){
	fan_state = state;
	if(fan_state == off){
		set_fan_direction(open);
	}else{
		set_fan_direction_immediately();
	}
	//ToDo -> insert a delay to wait relay on state			
	triac_set_output_state(fan_state);
}

void toggle_fan_output(){
	if(fan_state == on){
		fan_state = off;
		set_fan_direction(open);		
	}else {
		fan_state = on;
		set_fan_direction_immediately();
	}
	//ToDo -> insert a delay to wait relay on state
	triac_set_output_state(fan_state);
}

/******************************************************
* FAN DIRECTION CONTROL                               *
*******************************************************/
void set_fan_direction(dir direction){
	
	if(fan_state == on && direction != fan_direction){
		fan_direction = direction;
		cnt_direction = 30000;
		Rele1_set_level(0);
		Rele2_set_level(0);
	}else if(direction == open){
		Rele1_set_level(0);
		Rele2_set_level(0);
	}	
}

void set_fan_direction_immediately(){
	process_direction_relay();
}


void process_direction_relay(){
	
	if(fan_direction == down){
		Rele1_set_level(1);
		Rele2_set_level(0);
	}
	if(fan_direction == up){
		Rele1_set_level(0);
		Rele2_set_level(1);
	}
}

/******************************************************
* FAN SPEED CONTROL                                   *
*******************************************************/
void increase_speed(){
	if(triac_get_output_state() == on){
		if(angle > 0) angle -= 30;
		triac_set_angle(angle);
	}
}

void decrease_speed(){	
	if(triac_get_output_state() == on){
		if(angle < MAX_ANGLE) angle += 30;
		triac_set_angle(angle);
	}	
}