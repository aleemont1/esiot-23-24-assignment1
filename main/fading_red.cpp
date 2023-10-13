//Initial status (RED LED fading)
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"

#define MIN_INT 0
#define MAX_INT 255
#define INT_DELAY 15
#define INIT_DELTA 2

unsigned int intensity_= MIN_INT;
int intensity_delta_ = INIT_DELTA;

void pulse() {
    analogWrite(LR, intensity_);
    intensity_ += intensity_delta_;
    if (intensity_delta_ == MIN_INT || intensity_delta_ == MAX_INT) {
        intensity_delta_ = -intensity_delta_;
    }
    delay(INT_DELAY);
}

void reset_pulse() {
    intensity_ = MIN_INT;
    intensity_delta_ = INIT_DELTA;
    analogWrite(LR, intensity_);
}