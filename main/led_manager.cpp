//Buttons manager, in this module all implementations of buttons_manager.h
#include "Arduino.h"
#include "led_manager.h"
#include "constants.h"

const uint8_t leds[4] = {L1,L2,L3,L4};

#ifdef __DEBUG
void test_leds() {
    for(int i = 0; i < N_LED; i++) {
        digitalWrite(leds[i], HIGH);
        delay(300);
        digitalWrite(leds[i], LOW);
    }
    for(int i = 0; i < N_LED; i++) {
        digitalWrite(leds[i], HIGH);
    }
    delay(1500);
    for(int i = 0; i < N_LED; i++) {
        digitalWrite(leds[i], LOW);
    }
}
#endif

/**
 * Inizializza la board di LED, settando i pin in OUTPUT mode.
*/
void init_board() {
    for (int i = 0; i < N_LED; i++) {
        pinMode(leds[i],OUTPUT);
    }
    pinMode(LR,OUTPUT);
}

/**
 * Spegne tutti i LED verdi.
*/
void reset_board() {
    for (int i = 0; i < N_LED; i++) {
        digitalWrite(leds[i],LOW);
    }
}