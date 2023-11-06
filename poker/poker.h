#ifndef _POKER_H_
#define _POKER_H_
 
typedef struct {
    int game;
    int bb;
    int sb;
    int alive[5];
    int sleep_time;
    int rank[5];
    int chips[5];
    int blind;
    int blind_rank;
} game_info;

typedef struct {
    int turn;
    int join_status[5];
    int cards[5];
    int cards_players[10];
    int need_bet;
    int current_bet[5];
    int total_bet[5];
} round_info;

// poker
void poker(int *in_game, int* remain);
void p_start(int *in_game, int *remain); 
void p_initialize_game_info(game_info *g);
void p_initialize_round_info(round_info *r);
void p_title(game_info *g);
void p_setting(game_info *g, round_info *r);
void p_bet(int situation, game_info *g, round_info *r);
int p_result(int situation, game_info *g, round_info *r);
int p_is_game_end(game_info *g);
void p_update(game_info *g);
void p_next(int *in_game, game_info *g);
void p_end(int *in_game, int *remain, int *rank);

//cauculator
int p_alive_counter(int *alive);
int p_joiner_counter(int *join_status);
int p_current_pot(int *total_bet, int *current_bet);
int p_active_counter(int *join_status);

// strings
const char* p_mark(int);
const char* p_number(int);
const char* p_name(int);
const char* p_hand(int score);
const char* p_round_name(int situation);

// printer
void p_print_bet(int player, char select, int num, int join_status);
void p_print_card(int situation, int *sleep_time, int *cards);
void p_print_hand(int *sleep_time, int *join_status, int *cards_players);
void p_print_bet_info (int *chips, int *join_status, int *need_bet, int *current_bet, int *total_bet);
void p_print_showdown(int *alive, int *sleep_time, int *join_status, int *cards, int *cards_players);

//processor
void p_chip_process(char t, int n, int player, int *chips, int *join_status, int *turn, int *need_bet, int *current_bet);
int p_bet_status(int player, int *chips, int *need_bet, int *current_bet);
int p_hand_distinguisher(int *ns, int *ms);
void p_player_highest_score(int player, int *winner_for_showdown, int *score_for_showdown, int *winner_card, int *cards, int *cards_players);
void p_winner_judgement(int type, int *alive, int *winner_for_showdown, int *score_for_showdown, int *winner_card, int *join_status, int *cards, int *cards_players);

// computer
void p_evaluator(int player, int situation, int *chips, int *blind, int *blind_rank, int *s, int *n, int *cards, int *cards_players, int *need_bet, int *current_bet, int *total_bet);

#endif // _POKER_H_