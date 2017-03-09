#include "elev.h"
#include "light_handling.h"
#include "button_handling.h"
#include <stdio.h>
#include <time.h>
#include "states.h"
#include "timer.h"
#include "io.h"
#include "queue.h"
#include "elev.h"



 void bh_drive(States* state, int floor_diff){
 	if (floor_diff < 0){
		state-> motor_direction = 1;
 		state->stop = 0;
		elev_set_motor_direction(DIRN_UP);
		
 	}

 	else if (floor_diff > 0){
		state->motor_direction = -1;
 		state->stop = 0;
		elev_set_motor_direction(DIRN_DOWN);
		
 	}
 	else{
	state->motor_direction = 0;
	elev_set_motor_direction(DIRN_STOP);
	}
 	
 }

void bh_stop_button(States* state, int* queue){
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	while(elev_get_stop_signal()){
	// her vil vi bare holde programmet på vent til knappen 	er sluppet
            }
	st_initialize_elevator(state, queue);
	elev_set_stop_lamp(0);
}

int bh_check_button(int floor, elev_button_type_t button){
	if (floor == 0 && button == BUTTON_CALL_DOWN){
		return 0;
	}
	else if (floor == 3 && button == BUTTON_CALL_UP){
		return 0;
	}
	else{
		return 1;
	}
}

void bh_poll_all_buttons(int* queue){
	int floor_count;
	int button;
	int TOP_FLOOR=3;
	int BOTTOM_FLOOR = 0;
	for(floor_count = BOTTOM_FLOOR; floor_count <= TOP_FLOOR; floor_count++){
                	for(button = BUTTON_CALL_UP; button <= BUTTON_COMMAND; button++){
                		if (bh_check_button(floor_count, button)){
                			if(elev_get_button_signal(button, floor_count)){
                			add_in_queue(floor_count, button, queue);
           		}
          	}
        }
    }
}