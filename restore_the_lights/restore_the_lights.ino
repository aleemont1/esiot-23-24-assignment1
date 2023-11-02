/********************************************************************************************************
 * ######################################   RESTORE THE LIGHTS   ###################################### *
 *                                                                                                      *
 * The game board is based on 4 green leds L1, L2, L3, L4 and red led LS,                               *
 * four tactile buttons B1, B2, B3, B4 and a potentiometer Pot, displaced in the following layout:      *
 *                                                                                                      *
 *                                                                                                      *
 * During a game, the leds L1…L4 are initially all on. Then, after some random time T1,                 *
 * the leds start turning off, one by one in sequence, in some random order, taking some T2 time.       *
 * As soon as the last led is turned off, the player must turn on the leds in the reverse order by      *
 * pressing the corresponding buttons B1…B4, within some time T3. Each button Bi turns on the           *
 * corresponding led Li. So if the order in which the leds were turned off  was for instance 3,1,2,4    *
 * (that is: the first led to be turned off was L3, then L1, etc),  then the leds must be turned on     *
 * again in order 4,2,1,3 (that is: first L4, then L2, etc). If the player restores the leds on time,   *
 * the score - starting from zero - is increased and the game goes on, repeating the sequence,          *
 * but reducing the times T2 and T3 of some factor F.                                                   *
 * If the player does not restore the leds on time in the correct order, the red led Ls is turned on    *
 * for 1 second and the game ends, displaying the score on the serial line.                             *
 * #################################################################################################### *
 ********************************************************************************************************/

/**
 * Authors: Alessandro Monticelli, Davide Di Marco.
 * Title: Restore the lights game.
 * Description: Assignment 01.
 * Course: Embedded Systems and IoT.
 * "Alma Mater Studiorum" - University of Bologna.
 * Professor: Alessandro Ricci.
 * License:  GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
 * GitHub: github.com/aleemont1/esiot-23-24-assignment1
 */

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
