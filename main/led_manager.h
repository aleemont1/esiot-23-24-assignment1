//Buttons manager, in this module all button's function
void init_board();
void reset_board();
void turn_off(const int LED);
void turn_on(const int LED);
#ifdef __DEBUG
void test_leds();
#endif