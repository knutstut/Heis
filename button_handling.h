#ifndef BUTTON_HANDLING_H
#define BUTTON_HANDLING_H
#include "states.h"
#include "elev.h"

void bh_drive(States* state, int floor_diff);
void bh_stop_button(States* state, int* queue);
int bh_check_button(int floor, elev_button_type_t button);
void bh_poll_all_buttons(int* queue);

#endif