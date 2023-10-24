// Buttons manager, in this module all implementations of buttons_manager.h
#include "buttons_manager.h"
#include "game_manager.h"
#include "Arduino.h"
#include "constants.h"

// void waitForClickSleeping()
// {
//   switch_game_state(GAME_STARTED_STATE);
//   detachInterrupt(0);
// }

// void waitForClick()
// {
//   switch_game_state(INITIAL_STATE);
//   detachInterrupt(0);
//   attachInterrupt(0, waitForClickSleeping, CHANGE); // ripristino l'interrupt in modo tale che ripassi all'iniziale
// }

// void interrupt_setup()
// {
//   attachInterrupt(0, waitForClick, CHANGE); // sul pin 2, metto interrupt
// }

void init_buttons()
{
  
  for (int i = 0; i < N_LED; i++)
  {
    pinMode(BTNS[i], INPUT);
    //digitalWrite(BTNS[i], LOW);
  }

  //interrupt_setup(); // abilita il primo comportamento dell'interrupt
}




int button_handler(const int B)
{
  if (B >= 0 && B <= N_LED)
  {
    delay(10);                    //Bouncing delay
    return digitalRead(BTNS[B]);  //Ritorna lo stato del bottone B.
  }
}
