#ifndef QUEUE_H
#define QUEUE_H
#include "states.h"
#include "elev.h"

void add_in_queue(int floor, elev_button_type_t button, int *queue);
void remove_from_queue(States *states, int *queue);
void reset_queue(int *queue);
void queue_prioritize( States *states, int *queue);
void print_queue(int *queue);
int check_empty_queue(int *queue);

#endif