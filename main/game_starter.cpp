//Inizializzazione della partita
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"
#include "led_manager.h"

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
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
}

/**
 * TODO: Completare l'inizializzazione della partita secondo le specifiche
 * Il LED rosso inizia a pulsare (Stato iniziale del gioco)
*/
void initial_state() {
    pulse();
}