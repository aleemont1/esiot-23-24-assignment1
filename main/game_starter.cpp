//Inizializzazione della partita
#include "game_starter.h"
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"
#include "led_manager.h"
#include <avr/sleep.h>

int game_state = INIT_GAME;     //Stato attuale della partita
long initial_time_in_state = 0; //Tempo all'inizio dello stato
long elapsed_time_in_state = 0; //Tempo passato dall'inizio dello stato

//Parametri di gioco
int F = 0;  //Moltiplicatore velocità di gioco
unsigned long T1 = random(MIN_DELAY,MAX_DELAY); //Delay random inizio partita
unsigned long T2 = 250;     //Delay spegnimento singolo LED
unsigned long T3 = N_LED * T2;  //Delay massimo per partita

/**
 * Cambia lo stato del sistema.
*/
void switch_game_state(const int STATE) {
    game_state = STATE;
    initial_time_in_state = millis();
}

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
    Serial.begin(9600);
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key B1 to Start");
    Serial.end();
    switch_game_state(INITIAL_STATE);
}

/**
 * TODO: Completare l'inizializzazione della partita secondo le specifiche
 * Il LED rosso inizia a pulsare (Stato iniziale del gioco)
*/
void initial_state() {
    pulse();
    if(elapsed_time_in_state > 10000) {
        switch_game_state(GAME_STARTED_STATE);
    }
    /**
     * switch_game_state(WAITING_TO_START_STATE);
    */
}

 /**
    * function waiting_to_start_state():
    *   if(button_1 is pressed) then:
    *      switch_game_state(START_GAME)
    *
    *   endif
    *   if(elapsed_time > 10 secondi) then:
    *       switch_game_state(SLEEP)
    *   endif
    * end_function
    * 
   */

/**
 * Accende i LED verdi seguendo il pattern generato
*/
void game_started_state() {
    const uint8_t *PATTERN = generate_led_pattern();

    #ifdef __DEBUG
    Serial.println("Starting game...");
    Serial.begin(9600);
    Serial.print("GENERATED PATTERN: ");
    for(int i = 0; i < N_LED; i++) {
        Serial.print(PATTERN[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.end();
    #endif

    reset_pulse();
    reset_board();
    delay(T3);
    for(int i = 0; i < N_LED; i++) {
        turn_on(PATTERN[i]);
        delay(T2);
    }
    switch_game_state(SLEEPING_STATE);
}

/**
 * TODO: Rivedere. Implementato solo a scopo di test.
 * Sleeping state
*/
void sleeping_state() {
    #ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Going to sleep. Time: ");
    Serial.println(elapsed_time_in_state);
    Serial.end();
    #endif
    reset_pulse();
    reset_board();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    switch_game_state(INIT_GAME);
}

/**
 * Aggiorna il temmpo ad ogni iterazione del loop.
*/
void update_time() {
    elapsed_time_in_state = millis() - initial_time_in_state;
}

#ifdef __DEBUG
void test() {
    test_leds();
}
#endif