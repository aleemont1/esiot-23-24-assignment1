//Inizializzazione della partita
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"
#include "led_manager.h"

void init_game() {
    init_board();
    reset_board();
    reset_pulse();
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
}

void initial_state() {
    pulse();
}