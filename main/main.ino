#include "constants.h"
#include "game_manager.h"

extern int game_state;
extern int elapsed_time_in_state;

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
#ifdef __DEBUG
      Serial.begin(9600);
      Serial.print("Current state: INIT_GAME. Time in state: ");
      Serial.println(elapsed_time_in_state);
      Serial.end();
#endif
      init_game();
      break;
    case INITIAL_STATE:
#ifdef __DEBUG
      Serial.begin(9600);
      Serial.print("Current state: INITIAL_STATE. Time in state: ");
      Serial.println(elapsed_time_in_state);
      Serial.end();
#endif
      initial_state();
      break;
    case GAME_STARTED_STATE:
#ifdef __DEBUG
      Serial.begin(9600);
      Serial.print("Current state: GAME_STARTED_STATE. Time in state: ");
      Serial.println(elapsed_time_in_state);
      Serial.end();
#endif
      game_started_state();
      break;
    case INGAME_STATE:
#ifdef __DEBUG
      Serial.begin(9600);
      Serial.print("Current state: INGAME_STATE. Time in state: ");
      Serial.println(elapsed_time_in_state);
      Serial.end();
#endif
      in_game_state();
      break;
    case SLEEPING_STATE:
#ifdef __DEBUG
      Serial.begin(9600);
      Serial.print("Current state: SLEEPING_STATE. Time in state: ");
      Serial.println(elapsed_time_in_state);
      Serial.end();
#endif
      sleeping_state();
      break;

    default:
      Serial.begin(9600);
      Serial.println("Illegal state");
      Serial.end();
      break;
  }
}
