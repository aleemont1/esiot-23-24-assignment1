/*Game manager*/
#ifndef __GAME_MANANGER__
#define __GAME_MANAGER__

// Game states
#define INIT_GAME 0
#define INITIAL_STATE 1
#define WAITING_FOR_START_STATE 2
#define GAME_STARTED_STATE 3
#define INGAME_STATE 4
#define SLEEPING_STATE 5

/**
 * Initializes LEDs and buttons.
 */
void setup_wrapper();
/**
 * Changes system's state.
 * @param: STATE: The new System's state.
 */
void switch_game_state(const int STATE);
/**
 * Turns off all green LEDs.
 * Resets red LED state.
 * Prints intro message on Serial monitor.
 */
void init_game();
/**
 * Pulsing red LED, reads difficulty level, if B1 is pressed,
 * the game starts. After 10s it switches to SLEEP_STATE.
 */
void initial_state();
/**
 * Turns on the green LED following the generated Pattern.
 */
void game_started_state();
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
 */
void in_game_state();
/**
 * Sends the board in sleeping mode. Enables interrupts on Button PINS
 * and disables them after wakeup.
 */
void sleeping_state();
/**
 * Updates the time
 */
void update_time();
/**
 * Testa le varie componenti del sistema nella fase di setup.
 */
void test();

#endif