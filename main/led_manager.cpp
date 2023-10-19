// Buttons manager, in this module all implementations of buttons_manager.h
#include "Arduino.h"
#include "led_manager.h"
#include "constants.h"
#include <time.h>

const uint8_t leds[4] = {L1, L2, L3, L4};

#ifdef __TEST
void test_leds()
{
    for (int i = 0; i < N_LED; i++)
    {
        digitalWrite(leds[i], HIGH);
        delay(300);
        digitalWrite(leds[i], LOW);
    }
    for (int i = 0; i < N_LED; i++)
    {
        digitalWrite(leds[i], HIGH);
    }
    delay(1500);
    for (int i = 0; i < N_LED; i++)
    {
        digitalWrite(leds[i], LOW);
    }
}
#endif

/**
 * Inizializza la board di LED, settando i pin in OUTPUT mode.
 */
void init_board()
{
    for (int i = 0; i < N_LED; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
    pinMode(LR, OUTPUT);
    //pinMode(POT, INPUT);

}

/**
 * FIX: Genera sempre gli stessi pattern (quando resetti Arduino) in quanto Arduino non ha un RTC.
 * Permuta l'array leds. (Fisher-Yates shuffle algorithm modificato)
 * Returns: Una copia dell'array leds, permutata.
 */
uint8_t *generate_led_pattern()
{
    uint8_t *pattern = (uint8_t *)malloc(N_LED * sizeof(uint8_t));
    ;
    uint8_t available[N_LED];

    for (int i = 0; i < N_LED; i++)
    {
        available[i] = i; // Indici disponibili (per evitare ripetizioni)
    }

    for (int i = 0; i < N_LED; i++)
    {
        unsigned int j = random(0, N_LED - i);
        pattern[i] = leds[available[j]];         // Prendi un indice random tra quelli disponibili e assegnane il led corrispondente a pattern.
        available[j] = available[N_LED - i - 1]; // Rimpiazza l'indice usato con l'ultimo indice disponibile.
    }
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("PATTERN: ");
    for (int i = 0; i < N_LED; i++)
    {
        Serial.print(pattern[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.end();
#endif
    return pattern;
}

/**
 * Spegne il LED verde indicato.
 */
void turn_off(const int LED)
{
    digitalWrite(LED, LOW);
}

/**
 * Accende il LED verde indicato.
 */
void turn_on(const int LED)
{
    digitalWrite(LED, HIGH);
}

/**
 * Spegne tutti i LED verdi.
 */
void reset_board()
{
    for (int i = 0; i < N_LED; i++)
    {
        digitalWrite(leds[i], LOW);
    }
}

/**
 * Accende tutti i LED verdi
 */
void turn_on_board()
{
    for (int i = 0; i < N_LED; i++)
    {
        turn_on(leds[i]);
    }
}