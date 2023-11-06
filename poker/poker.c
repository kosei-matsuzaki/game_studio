#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "./poker.h"
#include "../util/util.h"

//main function
void poker(int *in_game) {
    game_info game_info;
    p_start(in_game);
    p_initialize_game_info(&game_info);
    while(*in_game == 1) {
        round_info round_info;
        p_initialize_round_info(&round_info);
        p_title(&game_info);
        p_setting(&game_info, &round_info);
        for (int i = 0; i < 6; i++) {
            if (i == 1 || i == 2) {
                continue;
            } else if (i == 0) {
                //preflop
                p_bet(0, &game_info, &round_info);
                if (p_result(i, &game_info, &round_info) == 1) {
                    break;
                };
            } else {
                //3: flop  4: turn  5: river
                p_print_card(i, &game_info.sleep_time, round_info.cards);
                if (p_active_counter(round_info.join_status) > 1) {
                    p_bet(i, &game_info, &round_info);
                }
                if (p_result(i, &game_info, &round_info) == 1) {
                    break;
                };
            }
        }
        if (p_is_game_end(&game_info) == 1) {
            break;
        }
        p_update(&game_info);
        p_next(in_game, &game_info);
    }
    p_end(in_game, game_info.rank);
}

//display startup
void p_start(int *in_game) {
    printf("\n");
    divider("", 'b');
    printf("Welcome to Texas Hold'em!\n\n");
    divider("", 'b');
    printf("\x1b[33mPress Enter To Start\x1b[0m\n");
    printf("\x1b[34mPress Q To Quit\x1b[0m\n");
    while (1) {
        char c = get_single_char();
        if (c == '\n') {
            printf("GAME START!\n\n");
            break;
        } else if (c == 'q') {
            *in_game = 0;
            break;
        }
    }
    sleep(1);
}

void p_initialize_game_info(game_info *g) {
    g->game = 1;
    g->bb = 1;
    g->sb = 0;
    for (int i = 0; i < 5; i++ ){
        g->alive[i] = 1;
        g->rank[i] = 1;
        g->chips[i] = 30000;        
    }
    g->sleep_time = 1;
    g->blind = 200;
    g->blind_rank = 0;

}

void p_initialize_round_info(round_info *r) {
    r->turn = 0;
    r->need_bet = 0;
    for (int i = 0; i < 5; i++ ){
        r->join_status[i] = 0;
        r->cards[i] = 0;
        r->current_bet[i] = 0;
        r->total_bet[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        r->cards_players[i] = 0;
    }
}

//display game and chips
void p_title(game_info *g) {
    // todo int to const char*
    divider("GAME", 'b');
    for (int i = 0; i < 5; i++) {
        printf("%s: %d ", p_name(i), g->chips[i]);
        if (i == g->bb % 5) {
            printf("(BB)");
        }
        if (i == g->sb % 5) {
            printf("(SB)");
        }
        printf("\n");
    }
    printf("\n");
    printf("BB %d, SB: %d\n\n", g->blind, g->blind / 2);
    sleep(g->sleep_time);
}

//distribute card and set blind
void p_setting(game_info *g, round_info *r) {
    srandom((unsigned)time(NULL));
    for (int i = 0; i < 5; i++) {
        while(1) {
            int ok = 0;            
            int c = (random() % 52);
            for (int j = 0; j < i; j++) {
                if (r->cards[j] == c) {
                    ok = 1;
                }
            }
            if (ok == 0) {
                r->cards[i] = c;
                break;
            }
        }  
    }
    for (int i = 0; i < 10; i++) {
        while(1) {
            int ok = 0;
            int c = (random() % 52);
            for (int j = 0; j < 5; j++) {
                if (r->cards[j] == c) {
                    ok = 1;
                }
            }
            for (int j = 0; j < i; j++) {
                if (r->cards_players[j] == c) {
                    ok = 1;
                }
            }
            if (ok == 0) {
                r->cards_players[i] = c;
                break;
            }
        }         
    }

    int b = g->blind;
    int s = g->blind / 2;
    if (g->chips[g->bb % 5] < b) {
        b = g->chips[g->bb % 5];
        r->join_status[g->bb % 5] = 1;
    }
    if (g->chips[g->sb % 5] < s) {
        s = g->chips[g->sb % 5];
        r->join_status[g->sb % 5] = 1;
    }
    r->need_bet = g->blind;
    r->current_bet[g->bb % 5] += b;
    r->current_bet[g->sb % 5] += s;
    g->chips[g->bb % 5] -= b;
    g->chips[g->sb % 5] -= s;
    r->turn = (g->bb % 5) + 1;
}

//input validator
int p_validate (char select, int number, int player, int *chips, int *need_bet, int *current_bet) {
    switch (select) {
    case 'a': return 0;
    case 'b': 
    if (p_bet_status(player, chips, need_bet, current_bet) == 0) {
        if (number > *need_bet && number < chips[player]) {
            return 0;
        } else {
            printf("bet more than %d and less than %d\n", *need_bet, chips[player]);
            return 1;
        }
    } else {
        printf("invalid operation\n");
        return 1;
    }
    case 'c':
    if (p_bet_status(player, chips, need_bet, current_bet) != 1) {
        return 0;
    } else {
        printf("invalid operation\n");
        return 1;
    }
    case 'f':
    if (p_bet_status(player, chips, need_bet, current_bet) != 0) {
        return 0;        
    } else {
        printf("invalid operation\n");
        return 1;
    }
    case 'r':
    if (p_bet_status(player, chips, need_bet, current_bet) == 2) {
        if (number > *need_bet && number < chips[player]) {
            return 0;
        } else {
            printf("bet more than %d and less than %d\n", *need_bet, chips[player]);
            return 1;
        }
    }
    default: 
    printf("invalid operation\n");
    return 1;
    }
}

//handle bet round
void p_bet(int situation, game_info *g, round_info *r) {
    p_print_hand(&g->sleep_time, r->join_status, r->cards_players);  
    int first = r->turn;
    int end = 1;
    divider("BET", 'b');
    while (end) {
        end = 0;
        int player = (r->turn % 5);
        if (p_active_counter(r->join_status) == 1 && r->current_bet[player] == r->need_bet) {
            break;
        }
        if (player == 0 && r->join_status[player] == 0 && g->alive[0] == 1) {
            p_print_bet_info(g->chips, r->join_status, &r->need_bet, r->current_bet, r->total_bet);
            char s;
            int n;
            while(1) {
                printf("\x1b[33mSelect From Option: \x1b[0m");
                scanf("%c", &s);
                clear_stream();
                if (s == 'b' || s == 'r') {
                    printf("\x1b[33mEnter Bet Price: \x1b[0m");
                    scanf("%d", &n);
                    clear_stream();
                }
                if (s == 'a') {
                    n = g->chips[player];
                }
                if (p_validate(s, n, player, g->chips, &r->need_bet, r->current_bet) == 0) {
                    break;
                }                
            }
            p_print_bet(player, s, n, p_bet_status(player, g->chips, &r->need_bet, r->current_bet));
            p_chip_process(s, n, 0, g->chips, r->join_status, &r->turn, &r->need_bet, r->current_bet);
            sleep(g->sleep_time);
        } else if (r->join_status[player] == 0 && g->alive[player] == 1) {
            int s;
            int n = 0;
            p_evaluator(player, situation, g->chips, &g->blind, &g->blind_rank, &s, &n, r->cards, r->cards_players, &r->need_bet, r->current_bet, r->total_bet);
            p_print_bet(player, s, n, p_bet_status(player, g->chips, &r->need_bet, r->current_bet));
            p_chip_process(s, n, player, g->chips, r->join_status, &r->turn, &r->need_bet, r->current_bet);
            sleep(g->sleep_time);
        } else {
            r->turn++;
        }

        for (int i = 0; i < 5; i++) {
            if ((r->current_bet[i] != r->need_bet && r->join_status[i] == 0 && g->alive[i] == 1) || (r->turn) < (first + 5)) {
                end = 1;
                break;
            }
        }
    }
    printf("\n");
    printf("Current Pot: %d\n\n", p_current_pot(r->total_bet, r->current_bet));
    r->turn = g->sb % 5;
    r->need_bet = 0;
    for (int i = 0; i < 5; i++) {
        r->total_bet[i] += r->current_bet[i];
        r->current_bet[i] = 0;
    }
}

//display_result
void p_show_result(int is_showdown, game_info *g, round_info *r) {
    int winner_card[5] = {0,0,0,0,0};
    int score_for_showdown = 0;
    int winner_for_showdown = 0;
    int dummy[5] = {0,0,0,0,0};    
    divider("RESULT", 'b');
    if (is_showdown == 1) {
        p_winner_judgement(0, g->alive, &winner_for_showdown, &score_for_showdown, winner_card, r->join_status, r->cards, r->cards_players);
        printf("Winner: %s (%d+%d)\n", p_name(winner_for_showdown), g->chips[winner_for_showdown] + r->total_bet[winner_for_showdown], p_current_pot(r->total_bet, dummy) - r->total_bet[winner_for_showdown]);
        divider("", 'w');
        for (int i = 0; i < 5; i++) {
            if (r->join_status[i] == -1) {
                printf("%s (%d-%d)\n", p_name(i), g->chips[i] + r->total_bet[i], r->total_bet[i]);
            }                
        }
        g->chips[winner_for_showdown] += p_current_pot(r->total_bet, dummy);
    } else {
        p_winner_judgement(1, g->alive, &winner_for_showdown, &score_for_showdown, winner_card, r->join_status, r->cards, r->cards_players);
        int winner_count = 0;
        int winners[5] = {0,0,0,0,0};
        for (int i = 0; i < 5; i++) {
            if ((winner_for_showdown / (int)pow(2, (4 - i))) == 0) {
                continue;
            } else {
                if ((winner_for_showdown % (int)pow(2, (4 - i))) == 0) {
                    winner_count ++;
                    winners[4 - i] = 1;
                    break;
                } else {
                    winner_for_showdown -= (int)pow(2, (4 - i));
                    winner_count ++;
                    winners[4 - i] = 1;
                }
            }
        }
        if (winner_count == 1) {
            printf("Winner: ");
        } else {
            printf("Winners: ");
        }
        for (int i = 0; i < 5; i++) {
            if (winners[i] == 1) {
                printf("%s (%d+%d)   ", p_name(i), g->chips[i] + r->total_bet[i], (p_current_pot(r->total_bet, dummy) / winner_count) - r->total_bet[i]);
                g->chips[i] += (p_current_pot(r->total_bet, dummy) / winner_count);
            }                
        }
        printf("\n");
        printf("Hand: %s\n", p_hand(score_for_showdown));
        for (int i = 0; i < 5; i++) {
            printf("|%s %s| ", p_mark(winner_card[i] / 13), p_number(winner_card[i] % 13));
        }
        printf("\n");
        divider("", 'w');
        for (int i = 0; i < 5; i++) {
            if (winners[i] == 0 && g->alive[i] == 1) {
                printf("%s (%d-%d)\n", p_name(i), g->chips[i] + r->total_bet[i], r->total_bet[i]);
            }                
        }
    }
    printf("\n");        
    divider("", 'b');
}

//display hand and winners
//todo distribute chip when all in
int p_result(int situation, game_info *g, round_info *r) {
    if (p_joiner_counter(r->join_status) == 1) {
        p_show_result(1, g, r);
        return 1;
    } else if (situation == 5) {
        p_print_showdown(g->alive, &g->sleep_time, r->join_status, r->cards, r->cards_players);
        p_show_result(0, g, r);
    }  
    return 0;
}

//check remaining player
int p_is_game_end(game_info *g) {
    int count;
    for (int i = 0; i < 5; i++) {
        if (g->chips[i] <= 0 && g->alive[i] == 1) {
            if (i == 0) {
                g->sleep_time = 0;
            }
            count ++;
        }     
    }
    for (int i = 0; i < 5; i++) {
        if (g->chips[i] <= 0 && g->alive[i] == 1) {
            g->rank[i] = p_alive_counter(g->alive) - count + 1;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (g->chips[i] <= 0 && g->alive[i] == 1) {
            g->alive[i] = 0;
        }
    }
    if (p_alive_counter(g->alive) == 1) {
        return 1;
    }
    return 0;
}

//update variables
void p_update(game_info *g) {
    srandom((unsigned)time(NULL));
    g->game ++;
    while(1) {
        g->sb ++;
        if (g->alive[g->sb % 5] == 1) {
            break;
        }        
    }
    while(1) {
        g->bb ++;
        if (g->alive[g->bb % 5] == 1 && (g->bb % 5) != (g->sb % 5)){
            break;
        }
    }
}

//move to next game
void p_next(int *in_game, game_info *g) {
    if (g->game > 5 * (g->blind_rank + 1) + random() % (3)) {
        g->blind_rank ++;
        g->blind *= 2;
        printf("\n");
        printf("\x1b[95mBlind Increased: BB %d, SB: %d\x1b[0m\n", g->blind , g->blind / 2);
    }

    printf("\n");
    printf("\x1b[33mPress Enter To Start Next Game\x1b[0m\n");
    printf("\x1b[34mPress Q To Quit\x1b[0m\n");
    while (1) {
        char c = get_single_char();
        if (c == '\n') {
            break;
        } else if (c == 'q') {           
            *in_game = 0;
            break;
        }
    }
    printf("\n");
}

//display final result
void p_end(int *in_game, int *rank) {
    if (*in_game == 1) {
        printf("\n");
        divider("FINAL RESULT", 'b');
        for (int i = 1; i < 6; i++) {
            printf("Rank%d: ", i);
            for (int j = 0; j < 5; j++) {
                if (rank[j] == i) {
                    printf("%s ", p_name(j));
                }
            }
            printf("\n");
        }
        *in_game = 0;
    }
    printf("\n");
    divider("", 'b');
    printf("THANK YOU FOR PLAYING!!!\n");
    printf("Press Enter To Leave\n");
    printf("\n");
    divider("", 'b');
}

//for save
void memory() {
    
}