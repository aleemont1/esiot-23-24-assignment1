// Inizializzazione della partita
#include "game_manager.h"
#include "Arduino.h"
#include "constants.h"
#include "pulsing_red.h"
#include "led_manager.h"
#include "buttons_manager.h"
#include "potentiometer_manager.h"
#include <avr/sleep.h>

int game_state = INIT_GAME;     // Stato attuale della partita
long initial_time_in_state = 0; // Tempo all'inizio dello stato
long elapsed_time_in_state = 0; // Tempo passato dall'inizio dello stato

// Parametri di gioco
unsigned long T1 = random(MIN_DELAY, MAX_DELAY); // Delay random inizio partita
unsigned long T2 = 250;                          // Delay spegnimento singolo LED
unsigned long T3 = 1500 + N_LED * T2;            // Delay massimo per partita (1.5s + il tempo di spegnimento dei LED)
unsigned int SCORE = 0;
extern double F;

static uint8_t *PATTERN;                                   // Random LED pattern
static uint8_t *sequence;                                  // The sequence if LEDs turned on by user.
static bool pressed[N_LED] = {false, false, false, false}; // To avoid repetition in sequence.

/**
 * Testa le varie componenti del sistema nella fase di setup.
 * Da integrare con ulteriori funzioni di test.
 */
static void test();
/**
 * Reverses the PATTERN array.
 */
static void reverse_pattern();
/**
 * Checks if the pressed sequence is equal to the (reversed) PATTERN.
 */
static bool check_win();

static void reset_parameters()
{
    T1 = random(MIN_DELAY, MAX_DELAY); // Delay random inizio partita
    T2 = 250;                          // Delay spegnimento singolo LED
    T3 = 1000 + N_LED * T2;            // Delay massimo per partita (1s + il tempo di spegnimento dei LED)
    SCORE = 0;
}
/**
 * Initializes LEDs and buttons.
 */
void setup_wrapper()
{
    init_board();
    init_buttons();
    test();
}

/**
 * Cambia lo stato del sistema.
 */
void switch_game_state(const int STATE)
{
    game_state = STATE;
    initial_time_in_state = millis();
}

/**
 * Spegne tutti i LED
 * Resetta lo stato del LED rosso
 * Stampa il messaggio di intro sul serial monitor
 */

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

void sleepArduino()
{
    switch_game_state(SLEEPING_STATE);
}

void initial_state()
{
    /**Ristabilire vecchio comportamento dei buttons*/
    PCMSK2 = 0;
    // Disable Pin Change Interrupts
    PCICR = 0;

    // Reconfigure pins as digital inputs
    pinMode(B1, INPUT);
    pinMode(B2, INPUT);
    pinMode(B3, INPUT);
    pinMode(B4, INPUT);
    sei(); // Re-enable global interrupts
    
    pulse();
    readPotValue();

    if (elapsed_time_in_state > 5000)
    {
#ifdef __DEBUG
        Serial.begin(9600);
        Serial.println("Switching to state: SLEEPING_STATE.");
        Serial.end();
#endif
        sleepArduino();
    }
}
/**
 * Accende i LED verdi seguendo il pattern generato
 */
void game_started_state()
{
    reset_pulse(); // Il LED rosso potrebbe restare acceso.
    reset_board(); // Solo per sicurezza, potrebbe essere rimosso in seguito a test più approfonditi.

    turn_on_board(); // Accendo tutti i LED verdi.
    delay(T1);       // Prima di iniziare a spegnere i LED aspetto un tempo T1.
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

/**
 * This function manages the game.
 * It calls the button handlers until all the buttons have
 * been pressed or the time limit is reached.
 * When a button is pressed (status is HIGH), the corresponding
 * position in the pressed array is set to true, the first free
 * position of the sequence array is set to the value of the i-th
 * value in the LEDs array, and the i-th LED is turned on.
 * After the while has exited the PATTERN array is reversed (in place) and
 * winning conditions are verified and the game restarts.
 *
 * TODO: Increase points after win.
 */
void in_game_state()
{
    T3 = 1500 + N_LED * T2; // 1.5s + tempo spegnimento LED

    Serial.begin(9600);
    Serial.print("T3: ");
    Serial.print(T3);
    Serial.print(" T2: ");
    Serial.print(T2);
    Serial.print(" F:");
    Serial.println(F);
    Serial.end();

    int btns_pressed_count = 0;
    sequence = (uint8_t *)malloc(sizeof(PATTERN) / sizeof(PATTERN[0]));

    while (btns_pressed_count < N_LED && elapsed_time_in_state < T3)
    {
        update_time();
        for (int i = 0; i < N_LED && elapsed_time_in_state < T3; i++)
        {
            int btn_status = button_handler(i);
            if (btn_status == HIGH && pressed[i] == false)
            {
                pressed[i] = true;
                sequence[btns_pressed_count++] = leds[i];
                turn_on(leds[i]);
#ifdef __DEBUG
                Serial.begin(9600);
                Serial.print("Pressed: [B");
                Serial.print(i);
                Serial.print("] Tuned on: [L");
                Serial.print(leds[i]);
                Serial.println("]");
                Serial.end();
#endif
            }
        }
    }
    Serial.begin(9600);
    Serial.print("Sequence: ");
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
        Serial.println("YOU LOSE :(");
        reset_board();
        game_over();
        // delay(10000);
    }

    for (int i = 0; i < N_LED; i++) // alla fine azzero i tasti premuti perchè cosi posso premerli alla successiva partita
    {
        pressed[i] = false;
    }

    free(PATTERN);
    free(sequence);
    delay(500);
    Serial.println("Starting a new game");
    Serial.end();

    switch_game_state(INIT_GAME);
}

void game_over()
{
    Serial.println("Game Over. Final Score: " + String(SCORE));
    reset_parameters();
    /**Turn on RED LED for 1.5s*/
    lose_animation();
}

void game_win()
{
    /**

    TODO: vittoria

     */
}

void wakeUp()
{
    switch_game_state(INIT_GAME);
}

void sleeping_state()
{
    // Configure pin change interrupts for pins 2, 3, 4, and 5
    PCMSK2 = (1 << PCINT18);  // Pin 2
    PCMSK2 |= (1 << PCINT19); // Pin 3
    PCMSK2 |= (1 << PCINT20); // Pin 4
    PCMSK2 |= (1 << PCINT21); // Pin 5

    // Enable Pin Change Interrupts
    PCICR = (1 << PCIE2);

    sei();
    reset_pulse();
    reset_board();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: SLEEPING_STATE.");
    Serial.end();
#endif
}

/**
 * Aggiorna il temmpo ad ogni iterazione del loop.
 */
void update_time()
{
    elapsed_time_in_state = millis() - initial_time_in_state;
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
    uint8_t temp;

    while (start < end)
    {
        // Swap the elements at the start and end indices
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