//Buttons manager, in this module all implementations of buttons_manager.h
#include "Arduino.h"
#include "led_manager.h"
#include "constants.h"
#include <time.h>

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
 * FIX: NON FUNZIONA. Probabilmente un errore di gestione dei puntatori. Per ora ritorna una copia
 *      di leds.
 * Permuta l'array leds. (Fisher-Yates shuffle algorithm)
 * Returns: Una copia dell'array leds, permutata.
*/
uint8_t* generate_led_pattern() {
    srand((unsigned int)time(NULL));
    uint8_t* pattern = (uint8_t*)malloc(N_LED * sizeof(uint8_t));
    pattern = leds;
    /**if (pattern == NULL) {
        // Gestione dell'errore se l'allocazione di memoria fallisce
        #ifdef __DEBUG
        Serial.println("ERROR IN pattern malloc");
        #endif
        return NULL;
    }
    for (int i = N_LED - 1; i > 0; i--) {
        // Genera un indice j tra 0 e i+1
        unsigned int j = rand() % (i + 1);
        pattern[i] = leds[j];
    }
    #ifdef __DEBUG
    for(int i = 0; i < N_LED; i++) {
        Serial.print("PATTERN[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(pattern[i]);
    }
    #endif*/
    return pattern;
}

/**
 * Spegne il LED verde indicato.
*/
void turn_off(const int LED) {
    digitalWrite(LED, LOW);
}

/**
 * Accende il LED verde indicato.
*/
void turn_on(const int LED) {
    digitalWrite(LED, HIGH);
}

/**
 * Spegne tutti i LED verdi.
*/
void reset_board() {
    for (int i = 0; i < N_LED; i++) {
        digitalWrite(leds[i],LOW);
    }
}