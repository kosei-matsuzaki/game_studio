#include <stdio.h>

//count alive player
int p_alive_counter(int *alive) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (alive[i] == 1) {
            count ++;
        }
    }
    return count;
}

//count joining player
int p_joiner_counter(int *join_status) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (join_status[i] >= 0) {
            count++;
        }
    }
    return count;
}

//count active player (exclude all in)
int p_active_counter(int *join_status) {
    int count;
    for (int i = 0; i < 5; i++) {
        if (join_status[i] == 0) {
            count++;
        }
    }
    return count;
}

//calculate the sum of pot
int p_current_pot(int *total_bet, int *current_bet) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += total_bet[i] + current_bet[i];
    }
    return sum;
}