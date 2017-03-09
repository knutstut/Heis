#include <stdio.h>
#include <time.h>
#include "states.h"
#include "elev.h"

void timer_set(States* state){
	state->timer_on = 1;
	state->time_ref = clock();
	elev_set_door_open_lamp(1);
}

int timer_update(States* state){
	double current_time = clock();
	double time_diff = ((double)(current_time - state->time_ref))/CLOCKS_PER_SEC;

	// Dersom 3 sekunder har gått så skrur vi av timeren og da dørlyset også. Vi setter også stop av sånn at heisen nå kan kjøre
	if (time_diff >= 3){
		state->timer_on = 0;
		state->stop = 0;
		elev_set_door_open_lamp(0);
		return 1;
	}
	return 0;
}
