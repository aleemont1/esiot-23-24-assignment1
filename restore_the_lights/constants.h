/*Constants*/
#ifndef __CONSTANTS__
#define __CONSTANTS__

// Parameters
#define MIN_DELAY 10
#define MAX_DELAY 1000
#define MAX_TIMEOUT 10000
#define N_LED 4
#define MAX_DIFFICULTY 4
// Buttons PINs
#define B1 2
#define B2 3
#define B3 4
#define B4 5
// Green LEDs PINs
#define L1 8
#define L2 9
#define L3 10
#define L4 11
// Red LED PIN
#define LR 6
// Potentionmeter PIN
#define POT A0

const uint8_t leds[] = {L1, L2, L3, L4};
const uint8_t BTNS[] = {B1, B2, B3, B4};

// DEBUG: Enable for advanced logging (very specific!).
// #define __DEBUG
// TEST: Enable for advanced testing.
// #define __TEST

#endif