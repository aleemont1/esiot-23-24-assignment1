/*Potentiometer manager*/
#include "potentiometer_manager.h"
#include "Arduino.h"
#include "constants.h"

double F; // Game speed multiplier.
int difficulty;

void setDifficulty(const int difficulty);

void readPotValue();

/**Code implementation.**/

void setDifficulty(const int difficulty)
{
    Serial.begin(9600);
    F = 1.0 + difficulty * 0.1;
    Serial.print("Level: ");
    Serial.print(F);
    Serial.println(" Difficulty: ");
    Serial.println(difficulty);
    Serial.end();
}

void readPotValue()
{
    int newDifficulty = map(analogRead(POT), 0, 1023, 1, MAX_DIFFICULTY);
    delay(10);
    if (newDifficulty != difficulty)
    {
        setDifficulty(newDifficulty);
        difficulty = newDifficulty;
    }
}