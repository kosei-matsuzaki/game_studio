#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../util/util.h"
#include "maps/maps.h"
#include "rhythm.h"

int r_tempo_calculator(int bpm, int beat) {
    // count 60 * (1000000 / r_render) in 1 min
    // dividing tempo =  count / (beat * bpm);
    return 60 * 1000000 / (r_render * beat * bpm);
}

int r_time_calcutator(int bar_count, int beat, int bpm) {
    // beat count = bar_count * beat
    // sec = 60 * (beat count / bpm)
    return 60 * bar_count * beat / bpm;
}

map_info map_list[100];

void r_map_initialize() {
    map_list[0] = pond_rain;
    map_list[1] = doremi;
    map_list[2] = natsumatsuri;
}

map_info* r_map_selecter(int id) {
    for (int i = 0; i < 100; i++) {
        if (id == map_list[i].id) {
            return &map_list[i];
        }
    }
    return NULL;
}

void r_map_creator(int map_duplicate[1800][4], const int map[1800][4]) {
    for (int i = 0; i < 1800; i++) {
        for (int j = 0; j < 4; j++) {
            map_duplicate[i][j] = map[i][j];
        }
    }
}

// music list and quit
int r_map_list() {
    system("clear");
    divider("MUSIC LIST", 'b');
    printf("a: Pond Rain\n");
    printf("b: Do-Re-Mi\n");
    printf("c: Natumaturi\n");
    printf("\n");
    printf("q: Quit\n\n");
    divider("", 'b');
    printf("Select Music From The List Above: ");

    char game = get_single_char();
    switch (game) {
    case 'a': return 1;
    case 'b': return 2;
    case 'c': return 3;
    case 'q': return -1;
    default: return 0;
    }
}

// map info(title, difficulty, time, speed) and confirm to start
int r_map_play_comfirm(int select, map_status* status) {
    system("clear");
    map_info* map = r_map_selecter(select);
    divider("MAP INFO", 'b');
    printf("Title:      %s\n", map->name);
    printf("Difficulty: %.1lf\n", map->difficulty);
    printf("Time:       %d sec\n", r_time_calcutator(map->bar_count, map->beat, map->bpm));
    printf("Speed:      %d bpm\n\n", map->bpm);
    divider("", 'b');
    printf("Press Enter To Start\n");
    printf("Press Q To Go Back To List\n\n");
    divider("", 'b');

    while (1) {
        char selection = get_single_char();
        switch (selection) {
        case '\n':
            status->playing = 1;
            status->map_id = select;
            status->combo = 0;
            status->point = 0;
            for (int i = 0; i < 5; i++) {
                status->result[i] = 0;
            }
            system("clear");
            return 1;
        case 'q': return 0;
        default: break;
        }
    }
}