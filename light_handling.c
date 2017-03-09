#include <stdio.h>
#include "elev.h"
#include "io.h"
#include "states.h"

void lh_set_floor_lamp(States* state){
	int current_floor = elev_get_floor_sensor_signal();
	
	if (current_floor != -1){
		elev_set_floor_indicator(current_floor);
		state->floor = current_floor;
		state->between_floors = 0;
	}

	else{
		switch(state->floor){
			case 1:
			state->between_floors = 1;
			break;
		
			case 2:
			if(state->motor_direction == -1){
			state->between_floors = 1;
			}
			else{
			state->between_floors = 2;
			}
			break;
		
			case 3:
			if(state->motor_direction == -1){
			state->between_floors = 2;
			}
			else{
			state->between_floors = 3;
			}
			break;

			case 4:
			state->between_floors = 3;
			break;
		}
	}
}