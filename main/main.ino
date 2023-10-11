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

int buttons[4] =  {B1,B2,B3,B4};
int leds[4] = {L1,L2,L3,L4};

int F = 0;  //Moltiplicatore velocità di gioco
unsigned long T1 = random(MIN_DELAY,MAX_DELAY); //Delay random inizio partita
unsigned long T2 = 250;     //Delay spegnimento singolo LED
unsigned long T3 = N_LED * T2;  //Delay massimo per partita

void setup() {
  Serial.begin(9600);
  pinMode(LR,OUTPUT);   
  for(int i = 0; i < N_LED; i++) {
    pinMode(buttons[i],INPUT);
    pinMode(leds[i],OUTPUT);
  }
}

void loop() {
  delay(T1);
  
}
