//Initial status (RED LED fading)
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"

#define MIN_INT 0
#define MAX_INT 255
#define INT_DELAY 15
#define INIT_DELTA 5

unsigned int intensity = MIN_INT;
int intensity_delta = INIT_DELTA;

void pulse() {
    analogWrite(LR, intensity);
    intensity += intensity_delta;
    if (intensity == MIN_INT || intensity == MAX_INT) {
        intensity_delta = -intensity_delta;
    }
    delay(INT_DELAY);
}

void reset_pulse() {
    intensity = MIN_INT;
    intensity_delta = INIT_DELTA;
    analogWrite(LR, intensity);
}