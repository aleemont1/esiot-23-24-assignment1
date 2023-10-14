//Buttons manager, in this module all implementations of buttons_manager.h
#include "buttons_manager.h"
#include "Arduino.h"
#include "constants.h"

const uint8_t BTNS[] = {B1,B2,B3,B4};

void init_buttons() {
    for(int i = 0; i < N_LED; i++) {
        pinMode(BTNS[i], INPUT);
    }
}


