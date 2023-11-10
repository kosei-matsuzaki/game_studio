#include <stdio.h>
#include "rhythm.h"

void r_is_hit(int map[1800][4], map_status* status, int hit, int line) {
    if (map[hit][line] == 1) {
        status->combo++;
        status->point += 300 * status->combo;
        map[hit][line] = 2;
        status->result[0]++;
        if (status->result[4] < status->combo) {
            status->result[4] = status->combo;
        }
    }
    else if (map[hit + 1][line] == 1) {
        status->combo++;
        status->point += 100 * status->combo;
        map[hit + 1][line] = 3;
        status->result[1]++;
        if (status->result[4] < status->combo) {
            status->result[4] = status->combo;
        }
    }
    else if (map[hit - 1][line] == 1) {
        status->combo++;
        status->point += 100 * status->combo;
        map[hit - 1][line] = 4;
        status->result[1]++;
        if (status->result[4] < status->combo) {
            status->result[4] = status->combo;
        }
    }
    else if (map[hit + 2][line] == 1) {
        status->combo = 0;
        status->point += 50;
        map[hit + 2][line] = 5;
        status->result[2]++;
    }
}

void r_note_missed(int map[1800][4], map_status* status, int position) {
    for (int i = 0; i < 4; i++) {
        if (map[position][i] == 1) {
            map[position][i] = 6;
            status->combo = 0;
            status->point -= 50;
            status->result[3]++;
        }
    }
}

int r_count_note(int result[5]) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        count += result[i];
    }
    if (count == 0) count = 1;
    return count;
}

double r_accuracy(int result[5]) {
    int nc = r_count_note(result);
    double acc = ((double)result[0] + (double)result[1] * 0.85 + (double)result[2] * 0.5) * 100.0 / (double)nc;
    return acc;
}