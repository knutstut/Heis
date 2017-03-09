#include <stdio.h>
#include "elev.h"
#include "io.h"
#include "states.h"
#include "queue.h"
#include "button_handling.h"

const int CALL_UP = 4;
const int CALL_DOWN = 7;

int check_empty_queue(int *queue){
	int sum = 0;
	for(int i = 0; i < 10; i++){
		sum +=queue[i];
	}
	if (sum == 0){
		return 1;
	}
	return 0;
}

void print_queue(int *queue){
	for (int i = 0; i< 10; i++){
		printf(queue[i],"\t");
	}
}

void add_in_queue(int floor, elev_button_type_t button, int *queue){
	if(button == BUTTON_COMMAND){
		queue[floor] = 1;
		elev_set_button_lamp(BUTTON_COMMAND, floor,1);
	}
	else if(button == BUTTON_CALL_UP){
		queue[floor+CALL_UP] = 1;
		elev_set_button_lamp(BUTTON_CALL_UP, floor,1);
	}
	else if(button == BUTTON_CALL_DOWN){
		queue[floor + CALL_DOWN] = 1;
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor,1);
	}
}

void remove_from_queue(States *states, int *queue){

	queue[states->floor] = 0;
	elev_set_button_lamp(BUTTON_COMMAND, states->floor, 0);

	if(states->floor < 1){
		queue[states->floor + CALL_UP]=0;
		elev_set_button_lamp(BUTTON_CALL_UP, states->floor, 0);	

	}
	else if (states->floor > 2){
		queue[states->floor + CALL_DOWN] = 0;
		elev_set_button_lamp(BUTTON_CALL_DOWN, states->floor, 0);
		
	}
	else{
		queue[states->floor + CALL_UP] = 0;
		queue[states->floor + CALL_DOWN-1] = 0;
		elev_set_button_lamp(BUTTON_CALL_DOWN, states->floor, 0);
		elev_set_button_lamp(BUTTON_CALL_UP, states->floor, 0);
	}
	if (check_empty_queue(queue)){
		states->background_order = -1;
	}
}


void reset_queue(int *queue){
	for(int i = 0; i < 10 ; i++){
		queue[i] = 0;
		if(0<=i && i<4){
			elev_set_button_lamp(BUTTON_COMMAND ,i , 0);
			
					}
		else if(i<7){
			elev_set_button_lamp(BUTTON_CALL_UP , i - CALL_UP, 0);
			
			}
		else if (i>6){
			elev_set_button_lamp(BUTTON_CALL_DOWN, i- CALL_DOWN+1, 0);
		}

		

	}

}

void queue_prioritize(States *states, int *queue){
	int floor_diff;
	if ( states->motor_direction == -1){
		if(queue[states->floor]==1 || queue[states->floor +CALL_DOWN -1]==1 ||states->floor ==0){	// Check if the floor under you has an order
			states->stop = 1;
		}
	}
	else if(states->motor_direction == 1){
		if(queue[states->floor]==1 || queue[states->floor+CALL_UP]==1 ||states->floor ==3){	//Check if the floor above you has an order
			states->stop = 1;
		}
	}
	else{
		if(states->background_order == -1){
			for(int i = 0; i < 10; i ++){
				if(queue[i] == 1){
					if(0<=i && i<4){
						floor_diff = states->floor - i;
						states->background_order = i;
					}
					else if(i<7 && i>3){
						floor_diff = states->floor - (i - CALL_UP );
						states->background_order = i - CALL_UP ;
					}
					else if (i>6){
						floor_diff = states->floor - (i - CALL_DOWN + 1);
						states->background_order= i - CALL_DOWN + 1;
					}

					if (floor_diff == 0){
						states->stop = 1;
					}
					bh_drive(states, floor_diff);	
					
				}
			}
		}
		else{
			bh_drive(states, states->floor - states->background_order);
		}
	}
}