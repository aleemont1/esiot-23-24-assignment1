#define MIN_DELAY 10
#define MAX_DELAY 1000
#define N_LED 4
//PIN Pulsanti
#define B1 2
#define B2 3
#define B3 4
#define B4 5
//PIN LED Verdi
#define L1 8
#define L2 9
#define L3 10
#define L4 11
//PIN LED Rosso
#define LR 6
//PIN Potenziometro
#define POT A0 

//Parametri di gioco
int F = 0;  //Moltiplicatore velocità di gioco
unsigned long T1 = random(MIN_DELAY,MAX_DELAY); //Delay random inizio partita
unsigned long T2 250;     //Delay spegnimento singolo LED
unsigned long T3 = N_LED * T2;  //Delay massimo per partita

//DEBUG: Enable for advanced logging and LED testing.
#define __DEBUG