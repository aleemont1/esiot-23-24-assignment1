#include "constants.h"
#include "game_starter.h"
#include "buttons_manager.h" //Dovrebbe essere spostato in game_starter.cpp

extern int game_state;

void setup()
{
  setup_wrapper();
  switch_game_state(INIT_GAME);
}

void loop()
{
  
  update_time();
  switch (game_state)
  {
  case INIT_GAME:
    init_game(); /*Sicuro vada qui? l'inizializzazione del gioco dovrebbe essere fatta solo una volta, all'inizio del gioco*/
    break;
  case INITIAL_STATE:
    initial_state();
    break;
  case GAME_STARTED_STATE:
    game_started_state();
    break;
  case INGAME_STATE:
    in_game_state();
    break;
  case SLEEPING_STATE:
    sleeping_state();
    break;
  
  default:
    Serial.begin(9600);
    Serial.println("Illegal state");
    Serial.end();
    break;
  }
}
