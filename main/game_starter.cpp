// Inizializzazione della partita
#include "game_starter.h"
#include "Arduino.h"
#include "constants.h"
#include "fading_red.h"
#include "led_manager.h"
#include <avr/sleep.h>
#include "buttons_manager.h"

int game_state = INIT_GAME;     // Stato attuale della partita
long initial_time_in_state = 0; // Tempo all'inizio dello stato
long elapsed_time_in_state = 0; // Tempo passato dall'inizio dello stato


// Parametri di gioco
int F = 1;                                       // Moltiplicatore velocità di gioco
int difficulty;
int newDifficult;
int previousDifficult;
unsigned long T1 = random(MIN_DELAY, MAX_DELAY); // Delay random inizio partita
unsigned long T2 = 250;                          // Delay spegnimento singolo LED
unsigned long T3 = N_LED * T2;                   // Delay massimo per partita

/**
 * Testa le varie componenti del sistema nella fase di setup.
 * Da integrare con ulteriori funzioni di test.
 */

static void test()
{
    #ifdef __TEST
    test_leds();
    #endif
}

void setup_wrapper() {
    init_board();
    init_buttons();
    test();
}
/**
 * Cambia lo stato del sistema.
 */
void switch_game_state(const int STATE)
{
    game_state = STATE;
    initial_time_in_state = millis();
}

/**
 * Inizializza la board
 * Spegne tutti i LED
 * Resetta lo stato del LED rosso
 * Stampa il messaggio di intro sul serial monitor
 */

void setDifficulty(const int difficulty) 
{
    Serial.begin(9600);
    F = 1.0 + difficulty*0.1;
    Serial.println("Difficulty: ");
    Serial.println(difficulty);
    Serial.end();
}

void readPotValue() 
{
  int newDifficult = map(analogRead(POT), 0, 1023, 1, MAX_DIFFICULT);
  delay(1);
  if (newDifficult != previousDifficult) {
    setDifficulty(newDifficult);
    previousDifficult = newDifficult;
  }
  
}


void init_game()
{
  Serial.begin(9600);
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Current state: INIT_GAME. Time in state: ");
    Serial.println(elapsed_time_in_state);
    Serial.end();
#endif
    reset_board();
    reset_pulse();
    Serial.begin(9600);
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key B1 to Start");
    Serial.end();
    Serial.begin(9600);

#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: INITIAL_STATE.");
    Serial.end();
#endif
    switch_game_state(INITIAL_STATE);


    
    
}

/**
 * TODO: Completare l'inizializzazione della partita secondo le specifiche
 * Il LED rosso inizia a pulsare (Stato iniziale del gioco)
 */

/*void waitForClick() {
  switch_game_state(GAME_STARTED_STATE);
  detachInterrupt(0); //RIPRISTINO IL COMPORTAMENTO NORMALE DELL INTERRUPT SUL TASTO
}*/


void sleepArduino() {
  switch_game_state(SLEEPING_STATE); 
}

void initial_state()
{
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Current state: INITIAL_STATE. Time in state: ");
    Serial.println(elapsed_time_in_state);
    Serial.end();
#endif
    pulse();
    readPotValue();


    if (elapsed_time_in_state > 10000)
    {
#ifdef __DEBUG
        Serial.begin(9600);
        Serial.println("Switching to state: SLEEPING_STATE.");
        Serial.end();
#endif
        
        sleepArduino();
    }
}

/**
 * Accende i LED verdi seguendo il pattern generato
 */
void game_started_state()
{
    const uint8_t *PATTERN = generate_led_pattern();

#ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Current state: GAME_STARTED_STATE. Time in state: ");
    Serial.println(elapsed_time_in_state);
    Serial.end();
#endif
    delay(2000); //aspetto 2 secondi prima di far partire lo stato alrimenti troppo veloce il passaggio da initial state a game state
    reset_pulse();   // Il LED rosso potrebbe restare acceso.
    reset_board();   // Solo per sicurezza, potrebbe essere rimosso in seguito a test più approfonditi.
    turn_on_board(); // Accendo tutti i LED verdi.
    delay(T1);       // Prima di iniziare a spegnere i LED aspetto un tempo T1.
    for (int i = 0; i < N_LED; i++)
    {
        delay(T2);            // Ogni LED si spegne dopo un tempo T2.
        turn_off(PATTERN[i]); // Spengo i LED secondo il pattern generato.
    }
    free(PATTERN); /** TODO: DA SPOSTARE NELLA FUNZIONE IN CUI SI RISOLVE IL PATTERN (L'UTENTE GIOCA)! */
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: SLEEPING_STATE.");
    Serial.end();
#endif
}
#endif*/
    switch_game_state(INGAME_STATE);

}

void in_game_state() {
  #ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Current state: IN_GAME_STATE. Time in state: ");
    Serial.println(elapsed_time_in_state);
    Serial.end();
  #endif
  //readButtonsStatus();
}




void wakeUp() {
  switch_game_state(INIT_GAME);
}

void sleeping_state()
{
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Current state: SLEEPING_STATE. Time in state: ");
    Serial.println(elapsed_time_in_state);
    Serial.end();
#endif
    detachInterrupt(0);
    reset_pulse();
    reset_board();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(0, wakeUp, RISING); //LO 0 RIFERISCE L'INTERRUPT DEL PIN 2 DOV E ATTACCATO IL BT1
    sleep_mode();
    sleep_disable();
    detachInterrupt(0);
    switch_game_state(INIT_GAME);
    detachInterrupt(0);
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("Switching to state: SLEEPING_STATE.");
    Serial.end();
#endif
}

/**
 * Aggiorna il temmpo ad ogni iterazione del loop.
 */
void update_time()
{
    elapsed_time_in_state = millis() - initial_time_in_state;
}