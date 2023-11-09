#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "rhythm.h"
#include "../util/util.h"

int r_wait = 50000;

void rhythm(int *in_game) {
    r_start(in_game);
    map_status status;
    while (r_select_map(&status, in_game)) {
        int count = 0;
        int map[1800][4];
        map_info* map_info = r_map_selecter(status.map_id);
        r_map_creator(map, map_info->map);
        while (status.playing == 1) {
            r_notes(map, *map_info, &status, count);
            r_input(map, &status, count, map_info->speed);
            count++;
            usleep(r_wait);
            system("clear");
            r_map_end(*map_info, &status, count);
        }
        r_result(&status);
    }
    system("clear");
    r_end();
    return;
}

void r_start(int* in_game) {
    printf("\n");
    divider("", 'b');
    printf("Welcome to Rhythm Game!\n\n");
    divider("", 'b');
    printf("\x1b[33mPress Enter To Start\x1b[0m\n");
    printf("\x1b[34mPress Q To Quit\x1b[0m\n");
    while (1) {
        char c = get_single_char();
        if (c == '\n') {
            printf("GAME START!\n\n");
            break;
        }
        else if (c == 'q') {
            *in_game = 0;
            return;
        }
    }
    sleep(1);
}

int r_select_map(map_status* status, int *in_game) {
    while (1) {
        int select = r_map_list();
        if (select == -1) {
            *in_game = 0;
            return 0;
        }
        else if (select == 0) {
            continue;
        }
        if (r_map_play_comfirm(select, status)) {
            countdown(3);
            printf("START!!!\n");
            break;
        }
    }
    sleep(1);
    return 1;
}

void r_notes(int map[1800][4], map_info map_info, map_status* status, int count) {
    r_print_score(status->point, status->combo);
    int position = count / map_info.speed;
    printf("    D   F   J   K    \n");
    for (int i = position; i < position + 20; i++) {
        if (i == position + 2) {
            printf("--|");
            for (int j = 0; j < 4; j++) {
                r_print_note_hit(map[i][j], map[i-1][j], map[i + 1][j], map[i + 2][j]);
                printf("|");
            }
            printf("--\n");
        }
        else {
            printf("  |");
            for (int j = 0; j < 4; j++) {
                r_print_note(map[i][j]);
                printf("|");
            }
            printf("  \n");
        }
        
    }
    printf("\n");
    divider("", 'b');
    r_note_missed(map, status, position);
}

void r_input(int map[1800][4], map_status* status, int count, int speed) {
    int hit = count / speed + 2;
    if (kbhit()) {
        switch (getchar()) {
        case 'd':
            r_is_hit(map, status, hit, 0);
            break;
        case 'f': 
            r_is_hit(map, status, hit, 1);
            break;
        case 'j': 
            r_is_hit(map, status, hit, 2);
            break;
        case 'k':
            r_is_hit(map, status, hit, 3);
            break;
        case 'q':
            status->playing = 0;
            break;
        default: break;
        }
    }
}

void r_map_end(map_info map, map_status* status, int count) {
    if (count / map.speed == map.time) {
        status->playing = 0;
    }

}

void r_result(map_status* status) {
    system("clear");
    divider("RESULT", 'b');
    printf("Point: %d\n", status->point);
    printf("Max Combo: %d\n", status->result[4]);
    printf("\n");
    printf("Great: %d | Good: %d | Bad: %d | Miss: %d\n\n", status->result[0], status->result[1], status->result[2], status->result[3] );
    divider("", 'b');
    printf("Press Enter To Go Back To Map List");

    while (get_single_char() != '\n') {}
}

void r_end() {
    divider("", 'b');
    printf("THANK YOU FOR PLAYING!!!\n");
    printf("Press Enter To Leave\n");
    printf("\n");
    divider("", 'b');
    return;
}