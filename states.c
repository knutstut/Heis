#include "elev.h"
#include "light_handling.h"
#include "button_handling.h"
#include <stdio.h>
#include <time.h>
#include "states.h"
#include "timer.h"
#include "queue.h"

void st_initialize_elevator(States* state, int* queue){

	elev_set_motor_direction(DIRN_STOP);
	state->motor_direction = 0;
	state->stop = 1;
	state->backround_order = -1;
	state->timer_on = 0;
	reset_queue(queue);
}