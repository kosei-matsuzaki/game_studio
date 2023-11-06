#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//move chips with player decision
void p_chip_process(char t, int n, int player, int *chips, int *join_status, int *turn, int *need_bet, int *current_bet) {
    if (join_status[player] == -1) {
        return;
    }
    switch (t) {
    int move;
    case'b': 
        chips[player] -= n;
        *need_bet += n;
        current_bet[player] += n;
        *turn += 1;
        return;
    case'r': 
        move = (n - current_bet[player]);
        chips[player] -= move;
        *need_bet = n;
        current_bet[player] += move;
        *turn += 1;
        return;
    case 'a':
        if (chips[player] + current_bet[player] > *need_bet) {
            *need_bet = chips[player] + current_bet[player];
        }
        current_bet[player] += chips[player];
        chips[player] = 0;
        *turn += 1;
        join_status[player] = 1;
        return;
    case'c':
        move = (*need_bet - current_bet[player]);
        chips[player] -= move;
        current_bet[player] += move;
        *turn += 1;
        return;
    case'f':
        join_status[player] = -1;
        *turn += 1;
        return;
    default: return;
    }
}

//distinguish bet situation
int p_bet_status(int player, int *chips, int *need_bet, int *current_bet) {
    if (current_bet[player] == *need_bet) {
        return 0;
    } else if (chips[player] <= (*need_bet - current_bet[player])){
        return 1;
    } else {
        return 2;
    }
} 


//distinguish hand score
int p_hand_distinguisher(int *ns, int *ms) {
    int score = 0;
    if (ms[0] == ms[4]) {
        if (ns[0] == (ns[4] + 4)) {
            //royal straight flush
            if (ns[0] == 14) {
                score = 90000000;
            } 
            //straight flush
            else {
                score = 80000000;
                score += (int)pow(2, ns[0]);
            }
            return score;
        }
        // flush 
        else {
            score = 50000000;
            for(int i = 0; i < 5; i++) {
                score += (int)pow(2, ns[i]);   
            }
            return score;
        }
    } else {
        //four of a kind
        for (int i = 0; i < 2; i++) {
            if (ns[i] == ns[i + 3]) {
                score = 70000000;
                score += (ns[i] * 100);
                if (i == 0) {
                    score += ns[4];
                } else {
                    score += ns[0];
                }
                return score;
            }
        }
        //straight
        if (ns[1] == (ns[2] + 1) && ns[1] == (ns[3] + 2) && ns[1] == (ns[4] + 3)) {
            if (ns[0] != 14 && ns[0] == (ns[1] + 1)) {
                score = 40000000;
                score += ns[0];
                return score;
            }
            if (ns[0] == 14 && ns[1] == 2) {
                score = 40000000;
                score += ns[0];
                return score;
            }
        }
        //full house, three of a kind
        for (int i = 0; i < 3; i++) {
            if (ns[i] == ns[i + 2]) {
                if (i == 0) {
                    if (ns[3] == ns[4]) {
                        score = 60000000;
                        score += (ns[i] * 100);
                        score += ns[3];
                    } else {
                        score = 30000000;
                        score += (ns[i] * 100000);
                        score += (int)pow(2, ns[3]);
                        score += (int)pow(2, ns[4]);
                    }
                } else if (i == 2) {
                    if (ns[0] == ns[1]) {
                        score = 60000000;
                        score += (ns[i] * 100);
                        score += ns[0];
                    } else {
                        score = 30000000;
                        score += (ns[i] * 100000);
                        score += (int)pow(2, ns[0]);
                        score += (int)pow(2, ns[1]);
                    }
                } else {
                        score = 30000000;
                        score += (ns[i] * 100000);
                        score += (int)pow(2, ns[0]);
                        score += (int)pow(2, ns[4]);
                }
                return score;
            }
        }
        //two pair, one pair
        for (int i = 0; i < 4; i ++) {
            if (ns[i] == ns[i + 1]) {
                if (i == 0 || i == 1) {
                    if (ns[2] == ns[3]) {
                        score = 20000000;
                        score += ns[i] * 100000;
                        score += ns[2] * 1000;
                        score += ns[4];
                    } else if (ns[3] == ns[4]) {
                        score = 20000000;
                        score += ns[i] * 100000;
                        score += ns[3] * 1000;
                        if (i == 0) {
                            score += ns[2];
                        } else {
                            score += ns[0];
                        }
                    } else {
                        score = 10000000;
                        score += ns[i] * 100000;
                        for(int j = 0; j < 5; j++) {
                            if (j == i || j == i + 1) {
                                continue;
                            } else {
                                score += (int)pow(2, ns[j]);
                            }
                        }
                    }
                } else {
                    score = 10000000;
                    score += ns[i] * 100000;
                    for(int j = 0; j < 5; j++) {
                        if (j == i || j == i + 1) {
                            continue;
                        } else {
                            score += (int)pow(2, ns[j]);
                        }
                    }                   
                }
                return score;
            }
        }
        //high card
        for (int i = 0; i < 5; i++) {
            score += (int)pow(2, ns[i]);
        }
        return score;
    } 
}

//set score of highest hand
void p_player_highest_score(int player, int *winner_for_showdown, int *score_for_showdown, int *winner_card, int *cards, int *cards_players) {
    int numbers[7] = {0, 0, 0, 0, 0, 0, 0};
    int marks[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 2; i++) {
        if ((cards_players[player * 2 + i] % 13) == 0) {
            numbers[i] = 14;
        } else {
            numbers[i] = ((cards_players[player * 2 + i] % 13) + 1);
        }
        marks[i] = (cards_players[player * 2 + i] / 13);
    }
    for (int i = 0; i < 5; i++) {
        if ((cards[i] % 13) == 0) {
            numbers[i + 2] = 14;
        } else {
            numbers[i + 2] = ((cards[i] % 13) + 1);
        }
        marks[i + 2] = (cards[i] / 13);
    }
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < i; j++) {
            int ns[5] = {0,0,0,0,0};
            int ms[5] = {0,0,0,0,0};
            for (int k = 0; k < 7; k++) {
                if (k < j) {
                    ns[k] = numbers[k];
                    ms[k] = marks[k];
                } else if (j < k && k < i){
                    ns[k - 1] = numbers[k];
                    ms[k - 1] = marks[k];
                } else if (i < k) {
                    ns[k - 2] = numbers[k];
                    ms[k - 2] = marks[k];
                }
            }
            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 4; n++) {
                    if (ns[n] < ns[n + 1]) {
                        int temp;
                        temp = ns[n];
                        ns[n] = ns[n + 1];
                        ns[n + 1] = temp;
                    }
                }
            }
            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 4; n++) {
                    if (ms[n] < ms[n + 1]) {
                        int temp;
                        temp = ms[n];
                        ms[n] = ms[n + 1];
                        ms[n + 1] = temp;
                    }
                }
            }
            int s = p_hand_distinguisher(ns, ms);
            if(s > *score_for_showdown) {
                *winner_for_showdown = (int)pow(2, player);
                *score_for_showdown = s;
                for (int k = 0; k < 5; k++) {
                    if (ns[k] == 14){
                        ns[k] = 1;
                    }
                    winner_card[k] = (ms[k] * 13 + ns[k] - 1); 
                }
            } else if (s == *score_for_showdown) {
                (*winner_for_showdown) += (int)pow(2, player);
            }                                   
        }
    }
}

//judge best hand player
void p_winner_judgement(int type, int *alive, int *winner_for_showdown, int *score_for_showdown, int *winner_card, int *join_status, int *cards, int *cards_players) {
    if (type == 0) {
        for (int player = 0; player < 5; player++) {
            if (join_status[player] >= 0 && alive[player] == 1) {
                *winner_for_showdown = player;
            }
        }
    } else {
        for (int player = 0; player < 5; player++) {
            if (join_status[player] == -1 || alive[player] == 0) {
                continue;
            } else {
                p_player_highest_score(player, winner_for_showdown, score_for_showdown, winner_card, cards, cards_players);
            }
        }
    }
}