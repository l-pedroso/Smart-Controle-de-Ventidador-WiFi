/*
 * app.h
 *
 * Created: 06/12/2022 11:12:26
 *  Author: lpedroso
 */ 


#ifndef APP_H_
#define APP_H_

#include "triac_driver/triac_driver.h"
#include <compiler.h>

typedef enum {
	up,
	down,
	open
} dir;

#define INITIAL_DIRECTION (dir)down
#define INITIAL_STATE  0
#define INITIAL_ANGLE  0

void set_lamp_output(bool state);
void toggle_lamp_output();
void set_fan_output(output_state state);
void toggle_fan_output();
void set_fan_direction(dir direction);
void process_direction_relay();
void increase_speed();
void decrease_speed();
void set_fan_direction_immediately();

#endif /* APP_H_ */