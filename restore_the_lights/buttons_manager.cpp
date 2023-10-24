/*Buttons manager*/
#include "buttons_manager.h"
#include "game_manager.h"
#include "Arduino.h"
#include "constants.h"

void init_buttons();

int button_handler(const int B);

/**Code implementation.**/

void init_buttons()
{
  for (int i = 0; i < N_LED; i++)
  {
    pinMode(BTNS[i], INPUT);
  }
}

int button_handler(const int B)
{
  if (B >= 0 && B < N_LED)
  {
    delay(10); // Bouncing delay
    return digitalRead(BTNS[B]);
  }
  return LOW;
}
