// LED manager, in this module all LEDs's function
void init_board();
void reset_board();
void turn_on_board();
void turn_off(const int LED);
void turn_on(const int LED);
void win_animation();
uint8_t *generate_led_pattern();
#ifdef __DEBUG
void test_leds();
#endif