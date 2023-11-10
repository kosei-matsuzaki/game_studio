#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "poker.h"

//calculate hand value
int p_hand_value_calculator(int player, int situation, int *cards, int *cards_players) {
    srandom((unsigned)time(NULL));
    int numbers[2 + situation];
    int marks[2 + situation];
    for (int i = 0; i < 2; i++) {
        if ((cards_players[player * 2 + i] % 13) == 0) {
            numbers[i] = 14;
        } else {
            numbers[i] = ((cards_players[player * 2 + i] % 13) + 1);
        }
        marks[i] = (cards_players[player * 2 + i] / 13);
    }
    for (int i = 0; i < situation; i++) {
        if ((cards[i] % 13) == 0) {
            numbers[i + 2] = 14;
        } else {
            numbers[i + 2] = ((cards[i] % 13) + 1);
        }
        marks[i + 2] = (cards[i] / 13);
    }

    int value = 0;
    int pair = 0;
    int flush_possibility = 0;
    int straight_possibility = 0;
    //bluf
    if ((random() % (50 / (1 + situation))) == 0) {
        value += (5 + (random() % 10 * situation));
    }
    //high card
    for (int i = 0; i < 2; i++) {
        if (numbers[i] > 12) {
            value += (10 + (random() % 5)) - situation;
        } else if (numbers[i] > 9) {
            value += (5 + (random() % 3)) - situation;
        }
    }
    //flush possibility
    if (marks[0] == marks[1]) {
        value += (5 + (random() % 10)) - 2 * situation;
        flush_possibility = 1;
    }
    //pair in hand
    if (numbers[0] == numbers[1]) {
        value += (15 + (random() % numbers[0]) * (random() % 2)) - situation;
        pair = 1;
    }
    //straight possibility
    if (numbers[0] == (numbers[1] - 1) || numbers[0] == (numbers[1] + 1)) {
        value += (5 + (random() % (numbers[0] / 2)) * (random() % 2)) - 2 * situation;
        straight_possibility = 1;
    }

    //after pre-flop
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < situation; j++) {
            //pair
            if (numbers[i] == numbers[2 + j]) {
                for(int k = j; k < situation; k++) {
                    if (numbers[i] == numbers[2 + k]){
                        value += (3 + 3 * pair + (random() % numbers[i]) * (random() % 2)) - 2 * (situation - 3);
                    }
                }
                value += (7 + 5 * pair + (random() % numbers[i]) * (random() % 2)) - 2 * (situation - 3);
            }
            //straight
            if (numbers[i] == (numbers[2 + j] + 1) || numbers[i] == (numbers[2 + j] - 1) || numbers[i] == (numbers[2 + j] + 2) || numbers[i] == (numbers[2 + j] - 2) || numbers[i] == (numbers[2 + j] + 3) || numbers[i] == (numbers[2 + j] - 3)) {
                value += (2 * straight_possibility + (random() % (numbers[i] / 2)) * (random() % 2)) - (situation - 3);                
            }
            //flush
            if (marks[i] == marks[2 + j]) {
                for(int k = j; k < situation; k++) {
                    if (marks[i] == marks[2 + k]) {
                        value += (5 * flush_possibility + (random() % 5)) - (situation - 3);
                    }
                }
                value += (3 * flush_possibility + (random() % 5)) - (situation - 3);
            }
        }
    }
    return value;
}

//decide option with hand value considering situation
void p_select_with_hand_value(int player, int value, int situation, int *chips, int *blind, int *blind_rank, int *s, int *n, int *need_bet, int *current_bet, int *total_bet) {
    srandom((unsigned)time(NULL));
    int pot = p_current_pot(total_bet, current_bet);
    int possess_bb = chips[player] / *blind + 1;
    int pot_size = chips[player] / pot + 1;
    //int bet_size = chips[player] / (*need_bet + 1) + 1;

    int for_bet = 12 + (random() % (50 / pot_size + 1)) - (random() % (40 / possess_bb + 1)) + situation * 2;
    int for_raise = 20 + (random() % (60 / pot_size + 1)) - (random() % (50 / possess_bb + 1)) + situation * 3;
    int for_call = 8 + (random() % (*need_bet / *blind + 1)) + (random() % (20 / possess_bb + 1));
    int for_all_in = 50 + (random() % 10) + (6 - *blind_rank) * situation - (random() % (50 / possess_bb + 1));
    int for_half_pot = 25 + (random() % (90 / pot_size + 1));
    int for_one_pot = 30 + (random() % (120 / pot_size + 1));
    int for_twice_pot = 35 + (random() % (150 / pot_size + 1));
    int for_one_bet = 15 + (random() % (120 / pot_size + 1));
    int for_twice_bet = 20+ (random() % (150 / pot_size + 1));
    int for_triple_bet = 30 + (random() % (180 / pot_size + 1));    

    if (p_bet_status(player, chips, need_bet, current_bet) == 0) {
        if (value > for_all_in) {
            *s = 'a';
            *n = chips[player];
        } else if (value > for_bet) {
            *s = 'b';
            if (value < for_half_pot) {
                *n = (((pot / 400) + (random() % (pot / 800 + 1)) - (random() % (pot / 800 + 1))) * 100);
            } else if (value < for_one_pot) {
                *n = ((pot / 200 + (random() % (pot / 800 + 1)) - (random() % (pot / 400 + 1))) * 100);
            } else if (value < for_twice_pot) {
                *n = ((pot / 100 + (random() % (pot / 400 + 1)) - (random() % (pot / 200 + 1))) * 100);
            } else {
                *n = (((pot /50 + (random() % (pot / 400 + 1)) - (random() % (pot / 100 + 1)))) * 100);
            }
            if (*n > chips[player]) {
                *s = 'a';
                *n = chips[player];
            }
        } else {
            *s = 'c';
        }
    } else if (p_bet_status(player, chips, need_bet, current_bet) == 1) {
        if (value > for_all_in) {
            *s = 'a';
            *n = chips[player];
        } else {
            *s = 'f';
        }      
    } else {
        if (value > for_all_in) {
            *s = 'a';
            *n = chips[player];
        } else if (value > for_raise) {
            *s = 'r';
            if (value < for_one_bet) {
                *n = (((*need_bet / 200 + 1) + (random() % (*need_bet / 400 + 1)) - (random() % (*need_bet / 400 + 1))) * 100);
            } else if (value < for_twice_bet) {
                *n = ((*need_bet / 100 + (random() % (*need_bet / 800 + 1)) - (random() % (*need_bet / 200 + 1))) * 100);
            } else if (value < for_triple_bet) {
                *n = ((*need_bet / 50 + (random() % (*need_bet / 800 + 1)) - (random() % (*need_bet / 100 + 1))) * 100);
            } else {
                *n = (((*need_bet /25 + (random() % (*need_bet / 800 + 1)) - (random() % (*need_bet / 50 + 1)))) * 100);
            }
            *n += *need_bet;
            if (*n > chips[player]) {
                *s = 'a';
                *n = chips[player];
            }
        } else if (value > for_call) {
            *s = 'c';
        } else {
            *s = 'f';
        }
    }
}

//computer playing system
void p_evaluator(int player, int situation, int *chips, int *blind, int *blind_rank, int *s, int *n, int *cards, int *cards_players, int *need_bet, int *current_bet, int *total_bet) {
    int value = p_hand_value_calculator(player, situation, cards, cards_players);  
    p_select_with_hand_value(player, value, situation, chips, blind, blind_rank, s, n, need_bet, current_bet, total_bet);
}