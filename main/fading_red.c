//Initial status (RED LED fading)
#include "fading_red.h"
#include "constants.h"

#define MIN_INT 0
#define MAX_INT 255
#define INT_DELAY 10
#define INIT_DELTA 5

uint8_t intensity = MIN_INT;
uint8_t intensity_delta = INIT_DELTA;

void pulse() {
    analogWrite(LR, intensity);
    inensity += intensity_delta;
    if (intensity_delta == MIN_INT || intensity_delta == MAX_INT) {
        intensity_delta *= -1;
    }
    delay(INT_DELAY);
}

void reset_pulse() {
    intensity = MIN_INT;
    intensity_delta = INIT_DELTA;
    analogWrite(LR, intensity);
}