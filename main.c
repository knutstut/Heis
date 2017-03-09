#include "elev.h"
#include "light_handling.h"
#include "button_handling.h"
#include <stdio.h>
#include <time.h>
#include "states.h"
#include "timer.h"
#include "queue.h"

States current_state;

int main() {
     // Button_commands(0 - 3), Button_call_up(4 - 6), Button_call_down(7 - 9)
    int queue[10]={};
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    // Kjører heisen ned til nærmeste etasje
    while(elev_get_floor_sensor_signal()==-1){
        elev_set_motor_direction(DIRN_DOWN);
    }
    st_initialize_elevator(&current_state, queue);

    while (1) {

        // Sjekker om vi har nådd ny etasje, hvis ja skrus etasjelys og current_state.floor oppdateres
       // Hvis nei, sier vi i fra at heisen er mellom to etasjer, og mellom hvilke
        lh_set_floor_lamp(&current_state);

        // håndterer her når stoppknappen er trykket inn
        if (elev_get_stop_signal()) {
          bh_stop_button(&current_state, queue);
        }
        // Vi har ankommet en etasje, stopper heisen og starter timer
        current_state.
        else if (current_state.stop && !current_state.timer_on){
            bh_drive(&current_state, 0);
            remove_from_queue(&current_state, queue);
            timer_set(&current_state);
        }
        // Sjekker om timeren er på
        while(current_state.timer_on){
            bh_poll_all_buttons(queue);
            timer_update(&current_state);
        }

    // Her håndteres at heisen står stille mellom to etasjer
    //if(current_state.stop || current_state.between_floors != 0){
        // poller alle knapper, adder til queue
        // kjører heisen med queue_prioritize()
        // between floors kan brukes til å si hvilken vei vi skal kjøre heisen.
    
      // Her er timeren skrudd av, og heisen står stille på en etasje
        if(!current_state.timer_on && !current_state.stop){
            //poller alle knapper, adder til queue
            bh_poll_all_buttons(queue);
            // Kjøre heisen med queue_prioritize();
            queue_prioritize(&current_state, queue);
        }
    }
    return 0;
}