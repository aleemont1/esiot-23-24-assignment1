/*Game manager*/
#include "game_manager.h"
#include "Arduino.h"
#include "constants.h"
#include "pulsing_red.h"
#include "led_manager.h"
#include "buttons_manager.h"
#include "potentiometer_manager.h"

#include <avr/sleep.h>
#include <EnableInterrupt.h>

int game_state = INIT_GAME;     // Current system state.
long initial_time_in_state = 0; // Time at the beginning of the state.
long elapsed_time_in_state = 0; // Elapsed time from the beginning of the state.

// Parametri di gioco
unsigned long T1 = random(MIN_DELAY, MAX_DELAY); // Random delay for game start.
unsigned long T2 = 250;                          // Delay for each LED turned of.
unsigned long T3 = 1500 + N_LED * T2;            // Maximum time for playing (1.5s + turning off LED time)
unsigned int SCORE = 0;
extern double F;

static uint8_t *PATTERN;                                   // Random LED pattern
static uint8_t *sequence;                                  // The sequence if LEDs turned on by user.
static bool pressed[N_LED] = {false, false, false, false}; // To avoid repetition in sequence.

void setup_wrapper();

void switch_game_state(const int STATE);

void init_game();

void initial_state();

void game_started_state();

void in_game_state();

void sleeping_state();

void update_time();

void test();
/**
 * Prints the final score, resets the parameters and turns on Red LED for 1s.
 *
 */
static void game_over();
/**
 * Switches state to INITIAL_STATE. Used for interrupts.
 */
static void wakeUp();
/**
 * Enables interrupts for wakeUp.
 */
static void enable_interrupts();
/**
 * Disable interrupts, restoring the normal buttons behavior.
 */
static void disable_interrupts();
/**
 * Reverses the PATTERN array.
 */
static void reverse_pattern();
/**
 * Checks if the pressed sequence is equal to the (reversed) PATTERN.
 */
static bool check_win();
/**
 * Resets initial game parameters.
 */
static void reset_parameters();

/**Code implementation**/

void setup_wrapper()
{
    init_board();
    init_buttons();
    test();
}

void switch_game_state(const int STATE)
{
    game_state = STATE;
    initial_time_in_state = millis();
}

void init_game()
{
    reset_board();
    reset_pulse();
    init_buttons();
    Serial.begin(9600);
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key B1 to Start");
    Serial.end();

#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: INITIAL_STATE.");
    Serial.end();
#endif
    switch_game_state(INITIAL_STATE);
}

void initial_state()
{
    interrupts();
    pulse();
    readPotValue();
    int start = button_handler(0);
    if (start == HIGH)
    {
        switch_game_state(GAME_STARTED_STATE);
    }
    if (elapsed_time_in_state > MAX_TIMEOUT)
    {
#ifdef __DEBUG
        Serial.begin(9600);
        Serial.println("Switching to state: SLEEPING_STATE.");
        Serial.end();
#endif
        switch_game_state(SLEEPING_STATE);
    }
}

void game_started_state()
{
    reset_pulse(); // Turn off Red LED
    reset_board(); // Turn off green LEDs

    turn_on_board(); // Turn on gred LEDs
    delay(T1);       // Before starting to display pattern, wait T1.
    PATTERN = generate_led_pattern();
    Serial.begin(9600);
    Serial.print("PATTERN: ");
    for (int i = 0; i < N_LED; i++)
    {
        Serial.print(PATTERN[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.end();
    for (int i = 0; i < N_LED; i++)
    {
        delay(T2);            // Ogni LED si spegne dopo un tempo T2.
        turn_off(PATTERN[i]); // Spengo i LED secondo il pattern generato.
    }
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: INGAME_STATE.");
    Serial.end();
#endif
    switch_game_state(INGAME_STATE);
}

void in_game_state()
{
    T3 = 1500 + N_LED * T2; // Update T3.

    Serial.begin(9600);
    Serial.print("Available time: ");
    Serial.print(T3);
    Serial.print(" LED delay: ");
    Serial.print(T2);
    Serial.end();

    int btns_pressed_count = 0;
    sequence = (uint8_t *)malloc(sizeof(PATTERN) / sizeof(PATTERN[0]));

    while (btns_pressed_count < N_LED && elapsed_time_in_state < T3)
    {
        update_time(); // Update timer.
        for (int i = 0; i < N_LED; i++)
        {
            int btn_status = button_handler(i);
            if (btn_status == HIGH && pressed[i] == false)
            {
                pressed[i] = true;
                sequence[btns_pressed_count++] = leds[i];
                turn_on(leds[i]);
            }
        }
    }
    Serial.begin(9600);
    Serial.print("Input sequence: ");
    for (int i = 0; i < N_LED; i++)
    {
        Serial.print(sequence[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.end();
    reverse_pattern();
    Serial.begin(9600);
    if (check_win())
    {
        Serial.println("YOU WON!!!");
        win_animation();
    }
    else
    {
        Serial.println("YOU LOST :(");
        game_over();
    }

    for (int i = 0; i < N_LED; i++) // Reset pressed array for next match.
    {
        pressed[i] = false;
    }

    free(PATTERN);
    free(sequence);

    Serial.println("Starting a new game");
    Serial.end();

    switch_game_state(INIT_GAME);
}

void sleeping_state()
{
    enable_interrupts();
    interrupts();
    reset_pulse();
    reset_board();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    disable_interrupts();
    noInterrupts();
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: SLEEPING_STATE.");
    Serial.end();
#endif
}

void update_time()
{
    elapsed_time_in_state = millis() - initial_time_in_state;
}

static void game_over()
{
    Serial.println("Game Over. Final Score: " + String(SCORE));
    reset_parameters();
    reset_board();
    lose_animation();
}

static void wakeUp()
{
    switch_game_state(INIT_GAME);
}

static void enable_interrupts()
{
    for (int i = 0; i < N_LED; i++)
    {
        enableInterrupt(BTNS[i], wakeUp, CHANGE);
    }
}

static void disable_interrupts()
{
    for (int i = 0; i < N_LED; i++)
    {
        disableInterrupt(BTNS[i]);
    }
}
void test()
{
#ifdef __TEST
    test_leds();
#endif
}

static void reverse_pattern()
{
    int start = 0;
    int end = N_LED - 1;

    while (start < end)
    {
        uint8_t temp;
        temp = PATTERN[start];
        PATTERN[start] = PATTERN[end];
        PATTERN[end] = temp;

        start++;
        end--;
    }
    Serial.begin(9600);
    Serial.print("REVERSED PATTERN: ");
    for (int i = 0; i < N_LED; i++)
    {
        Serial.print(PATTERN[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.end();
}

static bool check_win()
{
    for (int i = 0; i < N_LED; i++)
    {

        if (sequence[i] != PATTERN[i])
        {
            return false;
        }
    }
    SCORE += 10;
    T2 = (int)(T2 / F);
    return true;
}

static void reset_parameters()
{
    T1 = random(MIN_DELAY, MAX_DELAY);
    T2 = 250;
    T3 = 1000 + N_LED * T2;
    SCORE = 0;
}