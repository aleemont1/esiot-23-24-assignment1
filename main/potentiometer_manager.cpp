/*implementation of potentiometer_manager.h*/
#include "Arduino.h"
#include "constants.h"

extern double F; //moltiplicatore velocità di gioco
int difficulty;

void setDifficulty(const int difficulty)
{
    Serial.begin(9600);
    F = 1.0 + difficulty * 0.1;  
    Serial.print("F: ");
    Serial.print(F);
    Serial.println(" Difficulty: ");
    Serial.println(difficulty);
    Serial.end();
}

void readPotValue()
{
    int newDifficulty = map(analogRead(POT), 0, 1023, 1, MAX_DIFFICULT);
    delay(10);
    if (newDifficulty != difficulty)
    {
        setDifficulty(newDifficulty);
        difficulty = newDifficulty;
    }
}