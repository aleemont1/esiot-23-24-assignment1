// Buttons manager, in this module all implementations of buttons_manager.h
#include "buttons_manager.h"
#include "game_starter.h"
#include "Arduino.h"
#include "constants.h"

const uint8_t BTNS[] = {B1, B2, B3, B4};
bool btnClickEvent[] = {false, false, false, false};


void waitForClickSleeping() {
  switch_game_state(GAME_STARTED_STATE);
  detachInterrupt(0);

}


void waitForClick() {
    switch_game_state(INITIAL_STATE);
    detachInterrupt(0);
    attachInterrupt(0, waitForClickSleeping, HIGH); //ripristino l'interrupt in modo tale che ripassi all'iniziale
}

void interrupt_setup() {
  attachInterrupt(0, waitForClick, HIGH); //sul pin 2, metto interrupt
}

void init_buttons()
{
    for (int i = 0; i < N_LED; i++)
    {
        pinMode(BTNS[i], OUTPUT);
        digitalWrite(BTNS[i], LOW); 
    }

    interrupt_setup(); //abilita il primo comportamento dell'interrupt
}

void readButtonsStatus() {
    for (int i = 0; i < N_LED; i++)
    {
        button_handler(BTNS[i]);
    }
}

void button_handler(const int B) {
  
  switch (B) {
    case B1:
      int buttonState = digitalRead(B);

      // Controlla se il pulsante è stato premuto (il valore è LOW quando premuto a causa della resistenza di pull-up)
      if (buttonState == HIGH) {
        Serial.println("Il pulsante è stato premuto! ");
        Serial.begin(9600);
        Serial.println("Il pulsante è stato premuto! ");
        Serial.println(B);
        Serial.print(B);
        // Esegui qui le azioni desiderate quando il pulsante è premuto
        // Puoi aggiungere il tuo codice qui
        delay(1000);  // Aggiungi un ritardo per evitare letture multiple in rapida successione
      }
      break;


    case B2:
      break;
    case B3:
      break;
    case B4:
      break;
  }
  Serial.end();

}

