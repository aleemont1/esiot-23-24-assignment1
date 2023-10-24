/*Buttons manager*/
#ifndef __BUTTONS_MANAGER__
#define __BUTTONS_MANAGER__

/**
 * Initializes INPUT pins.
 */
void init_buttons();
/**
 * Returns the state of the B-th button
 * @param: B: The index of the BTNS[] array.
 * @returns: The state of BTNS[B];
 */
int button_handler(const int B);

#endif