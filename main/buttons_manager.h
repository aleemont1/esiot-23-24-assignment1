// Buttons manager, in this module all button's functions
void init_buttons();
void start_game();
void button_handler(const int B);
void readButtonsStatus();
void interrupt_setup();
void waitForNormalClick();
void wait_for_wake_up();


/*PROVE*/

void pressInterrupt();
void configureCommon();
void configureDistinct();
void press(int button);