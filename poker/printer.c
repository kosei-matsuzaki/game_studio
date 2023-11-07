#include <stdio.h>
#include <unistd.h>

const char* p_mark(int);
const char* p_number(int);
const char* p_name(int);
const char* p_hand(int);
const char* p_round_name(int);

int p_current_pot(int*, int*);
int p_bet_status(int, int*, int*, int*);
void divider(const char*, char);

//display player decision
void p_print_bet(int player, char select, int num, int join_status) {
    printf("%s: ", p_name(player));
    switch (select) {
    case 'b':
    printf("Bet %d", num);
    break;
    case 'r':
    printf("Raise %d", num);
    break;
    case 'c':
    if (join_status == 0) {
        printf("Check");
    } else {
        printf("Call");
    }
    break;
    case 'a':
    printf("All In %d", num);
    break;
    case 'f':
    printf("Fold");
    break;
    default: break;
    }
    printf("\n");
}

//display table card with needed number
void p_print_card(int situation, int *sleep_time, int *cards) {
    divider(p_round_name(situation), 'b');
    for (int i = 0; i < situation; i++) {
        printf("|%s %s| ", p_mark(cards[i] / 13), p_number(cards[i] % 13));
    }
    printf("\n\n");
    sleep(*sleep_time);
}

//display player hand
void p_print_hand(int *sleep_time, int *join_status, int *cards_players) {
    if (join_status[0] >= 0) {
        divider("YOUR HAND", 'b');
        for (int i = 0; i < 2; i++) {
            printf("|%s %s| ", p_mark(cards_players[i] / 13), p_number(cards_players[i] % 13));
        }
        printf("\n\n");
        sleep(*sleep_time);
    }
}

//display_player_bet_info
void p_print_bet_info (int *chips, int *join_status, int *need_bet, int *current_bet, int *total_bet) {
    printf("\n");
    divider("INFO", 'w');
    printf("Pot: %d  Bet: %d  To Check: %d\n", p_current_pot(total_bet, current_bet), *need_bet, *need_bet - current_bet[0]);
    for (int i = 0; i < 5; i++) {
        if (join_status[i] >= 0) {
            printf("%s: %d | ", p_name(i), chips[i]);
        }
    }
    printf("\n\n");
    divider("", 'w');
    if (p_bet_status(0, chips, need_bet, current_bet) == 0) {
        printf("\x1b[33mCheck: c | Bet: b | All In: a\x1b[0m\n");            
    } else if (p_bet_status(0, chips, need_bet, current_bet) == 1 ) {
        printf("\x1b[33mAll In: a | Fold: f\x1b[0m\n");
    } else {
        printf("\x1b[33mCall: c | Raise: r | All In: a | Fold: f\x1b[0m\n");
    } 
}

//display showdown
void p_print_showdown(int *alive, int *sleep_time, int *join_status, int *cards, int *cards_players) {
    divider("SHOWDOWN", 'b');
    for (int i = 0; i < 5; i++) {
        printf("|%s %s| ", p_mark(cards[i] / 13), p_number(cards[i] % 13));
    }
    printf("\n");
    divider("", 'w');
    for (int i = 0; i < 5; i++) {
        if (join_status[i] >= 0 && alive[i] == 1) {
            printf("%s : |%s %s| |%s %s|\n", p_name(i), p_mark(cards_players[2 * i] / 13), p_number(cards_players[2 * i] % 13), p_mark(cards_players[2 * i + 1] / 13), p_number(cards_players[2 * i + 1] % 13));
        }
    }
    printf("\n");
    sleep(*sleep_time);
}