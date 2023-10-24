/*LED manager*/
#ifndef __LED_MANAGER__
#define __LED_MANAGER__

/**
 * Initializes the green LEDs, sets the PINs to OUTPUT.
 */
void init_board();

/**
 * Shuffles the LEDs array. (Fisher-Yates shuffle algorithm)
 * @returns: A shuffled copy of the LEDs array.
 */
uint8_t *generate_led_pattern();

/**
 * Turns off the specified green LED.
 * @param LED: LED's PIN to turn off.
 */
void turn_off(const int LED);

/**
 * Turns on the specified green LED.
 * @param LED: LED's PIN to turn on.
 */
void turn_on(const int LED);

/**
 * Turns off all Green LEDs.
 */
void reset_board();

/**
 * Turns on all Green LEDs.
 */
void turn_on_board();

/**
 * Funny pattern :)
 */
void win_animation();

/**
 * Tests green LEDs.
 */
void test_leds();

#endif