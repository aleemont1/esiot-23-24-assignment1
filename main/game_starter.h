//Inizializzazione della partita

//Game states
#define INIT_GAME 0
#define INITIAL_STATE 1
#define WAITING_FOR_START_STATE 2
#define GAME_STARTED_STATE 3
#define SLEEPING_STATE 4 //Verrà modificato il valore, vorrei che fosse lo stato con valore più alto

void init_game();
void initial_state();
void game_started_state();
void sleeping_state();
void switch_game_state(const int STATE);
void update_time();
#ifdef __DEBUG
void test();
#endif