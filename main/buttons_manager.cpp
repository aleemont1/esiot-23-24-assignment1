// Buttons manager, in this module all implementations of buttons_manager.h
#include "buttons_manager.h"
#include "game_starter.h"
#include "Arduino.h"
#include "constants.h"

const uint8_t BTNS[] = {B1, B2, B3, B4};

void waitForClick() {
    switch_game_state(GAME_STARTED_STATE);
    detachInterrupt(0); 
    //attachInterrupt(0, waitForClick, HIGH);
}

void waitForClickSleeping() {
}

void interrupt_setup() {
  attachInterrupt(0, waitForClick, HIGH); //sul pin 2, metto interrupt
}

void init_buttons()
{
    for (int i = 0; i < N_LED; i++)
    {
        pinMode(BTNS[i], INPUT);
    }

    interrupt_setup(); //abilita il primo comportamento dell'interrupt
}

void button_handler(const int B) {

}

