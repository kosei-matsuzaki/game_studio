#include <stdio.h>

typedef struct
{
    int playing;
    int map_id;
    int point;
    int combo;
    int result[5]; //great, good, bad, miss, maxcombo
} map_status;

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