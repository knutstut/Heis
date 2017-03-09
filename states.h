#ifndef STATES_H
#define STATES_H

typedef struct{
	int motor_direction;
	int floor;
	int between_floors;
	int stop;
	double time_ref;
	int timer_on;
	int background_order;
} States;

void st_initialize_elevator(States* state, int* queue);

#endif