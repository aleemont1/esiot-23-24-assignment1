/*LED manager*/
#include "Arduino.h"
#include "led_manager.h"
#include "constants.h"
#include <time.h>


void init_board();

uint8_t *generate_led_pattern();

void turn_off(const int LED);

void turn_on(const int LED);

void reset_board();

void turn_on_board();

void win_animation();

void test_leds();

/**Code implementation*/

void init_board()
{
    for (int i = 0; i < N_LED; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
    pinMode(LR, OUTPUT);
}

uint8_t *generate_led_pattern()
{
    uint8_t *pattern = (uint8_t *)malloc(N_LED * sizeof(uint8_t));
    uint8_t available[N_LED];

    for (int i = 0; i < N_LED; i++)
    {
        available[i] = i; // Available indexes (Avoid repetitions).
    }

    for (int i = 0; i < N_LED; i++)
    {
        unsigned int j = random(0, N_LED - i);
        pattern[i] = leds[available[j]];         // Take a random index and assign the corresponding LED.
        available[j] = available[N_LED - i - 1]; // Swap used index with last available.
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

void turn_off(const int LED)
{
    digitalWrite(LED, LOW);
}

void turn_on(const int LED)
{
    digitalWrite(LED, HIGH);
}

void reset_board()
{
    for (int i = 0; i < N_LED; i++)
    {
        turn_off(leds[i]);
    }
}

void turn_on_board()
{
    for (int i = 0; i < N_LED; i++)
    {
        turn_on(leds[i]);
    }
}

void win_animation()
{
    for (int i = 0; i < N_LED; i++)
    {
        turn_off(leds[i]);
    }
    delay(500);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < N_LED; j++)
        {
            turn_on(leds[j]);
            delay(250);
            turn_off(leds[j]);
        }
    }
}

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