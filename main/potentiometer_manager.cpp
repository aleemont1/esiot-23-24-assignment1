/*implementation of potentiometer_manager.h*/
#include "Arduino.h"
#include "constants.h"

int F; //moltiplicatore velocità di gioco
int difficulty;
int newDifficult;
int previousDifficult;

void setDifficulty(const int difficulty)
{
    Serial.begin(9600);
    F = 1.0 + difficulty * 0.1;
    Serial.println("Difficulty: ");
    Serial.println(difficulty);
    Serial.end();
}

void readPotValue()
{
    int newDifficult = map(analogRead(POT), 0, 1023, 1, MAX_DIFFICULT);
    delay(1);
    if (newDifficult != previousDifficult)
    {
        setDifficulty(newDifficult);
        previousDifficult = newDifficult;
    }
}