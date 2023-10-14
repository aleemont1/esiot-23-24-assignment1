//#define __DEBUG  //Enable for advanced logging of time and game state.

#include "constants.h"
#include "game_starter.h"
#include "buttons_manager.h"

int buttons[4] =  {B1,B2,B3,B4};

int F = 0;  //Moltiplicatore velocità di gioco
unsigned long T1 = random(MIN_DELAY,MAX_DELAY); //Delay random inizio partita
unsigned long T2 = 250;     //Delay spegnimento singolo LED
unsigned long T3 = N_LED * T2;  //Delay massimo per partita

extern long elapsed_time_in_state;
extern int game_state;

void setup() {
  Serial.begin(9600);
}

void loop() {
  update_time();
  #ifdef __DEBUG
    Serial.print("Current time: ");
    Serial.print(elapsed_time_in_state);
    Serial.print(" Current state: ");
    Serial.println(game_state);
    Serial.println("\n\n");
  #endif
  switch(game_state) {
    case INIT_GAME:
      init_game();
      init_buttons();
      break;
    case INITIAL_STATE:
      initial_state();
      break;
    default:
      Serial.println("Illegal state");
      break;
  }
}
