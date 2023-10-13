#include "constants.h"
#include "game_starter.h"

int buttons[4] =  {B1,B2,B3,B4};
int leds[4] = {L1,L2,L3,L4};

int F = 0;  //Moltiplicatore velocità di gioco
unsigned long T1 = random(MIN_DELAY,MAX_DELAY); //Delay random inizio partita
unsigned long T2 = 250;     //Delay spegnimento singolo LED
unsigned long T3 = N_LED * T2;  //Delay massimo per partita

void setup() {
  Serial.begin(9600);
  pinMode(LR,OUTPUT);   
  for(int i = 0; i < N_LED; i++) {
    pinMode(buttons[i],INPUT);
    pinMode(leds[i],OUTPUT);
  }
}

void loop() {
  initial_state();
}
