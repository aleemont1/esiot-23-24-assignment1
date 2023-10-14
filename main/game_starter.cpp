//Inizializzazione della partita
#include "game_starter.h"
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"
#include "led_manager.h"

int game_state = INIT_GAME;
long time_in_state = 0;
/**
 * Inizializza la board
 * Spegne tutti i LED
 * Resetta lo stato del LED rosso
 * Stampa il messaggio di intro sul serial monitor
*/
void init_game() {
    init_board();
    reset_board();
    reset_pulse();
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key B1 to Start");
}

void switch_game_state(const int STATE) {
    game_state = STATE;
    time_in_state = millis();
}

/**
 * TODO: Completare l'inizializzazione della partita secondo le specifiche
 * Il LED rosso inizia a pulsare (Stato iniziale del gioco)
*/
void initial_state() {
    pulse();
}

