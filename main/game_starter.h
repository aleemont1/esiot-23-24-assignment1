//Inizializzazione della partita

//Game states
#define INIT_GAME 0
#define INITIAL_STATE 1
#define WAITING_FOR_START_STATE 2


void init_game();
void initial_state();
void switch_game_state(const int STATE);
void update_time();