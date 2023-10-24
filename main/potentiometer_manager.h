/*Potentiometer manager*/
#ifndef __POTENTIOMETER_METER__
#define __POTENTIOMETER_METER__

/**
 * Sets the new difficulty level.
*/
void setDifficulty(const int difficulty);
/**
 * Reads the potentiometer value and maps it to 4 levels.
*/
void readPotValue();

#endif
