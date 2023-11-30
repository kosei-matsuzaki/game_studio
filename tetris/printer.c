#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../util/util.h"

void print_block(int c) {
    switch (c) {
    case 1: printf(" ■"); break;
    case 2: printf(" \x1b[35m■\x1b[0m"); break; //purple
    case 3: printf(" \x1b[34m■\x1b[0m"); break; //blue
    case 4: printf(" \x1b[38;5;202m■\x1b[0m");  break; //orange
    case 5: printf(" \x1b[31m■\x1b[0m"); break; //red
    case 6: printf(" \x1b[92m■\x1b[0m"); break; //green
    case 7: printf(" \x1b[33m■\x1b[0m"); break; //yellow
    case 8: printf(" \x1b[96m■\x1b[0m"); break; //light blue
    default: printf(" ?"); break;
    }
}

void print_shadow(int c) {
    switch (c) {
    case 1: printf(" □"); break;
    case 2: printf(" \x1b[35m□\x1b[0m"); break;
    case 3: printf(" \x1b[34m□\x1b[0m"); break;
    case 4: printf(" \x1b[38;5;202m□\x1b[0m");  break;
    case 5: printf(" \x1b[31m□\x1b[0m"); break;
    case 6: printf(" \x1b[92m□\x1b[0m"); break;
    case 7: printf(" \x1b[33m□\x1b[0m"); break;
    case 8: printf(" \x1b[96m□\x1b[0m"); break;
    default: printf(" ?"); break;
    }
}

void print_status(int point, int level) {
    printf("\n");
    printf("Point: %d  Level: %d\n", point, level);
    return;
}

void print_title() {
    divider("", 'b');
    printf("       \x1b[41m　　　\x1b[0m \x1b[48;5;202m　　　\x1b[0m \x1b[43m　　　\x1b[0m \x1b[102m　　　\x1b[0m \x1b[46m　\x1b[0m \x1b[45m　　　\x1b[0m\n");
    printf("       　\x1b[41m　\x1b[0m　 \x1b[48;5;202m　\x1b[0m　　 　\x1b[43m　\x1b[0m　 \x1b[102m　\x1b[0m　\x1b[102m　\x1b[0m \x1b[46m　\x1b[0m \x1b[45m　\x1b[0m　　\n");
    printf("       　\x1b[41m　\x1b[0m　 \x1b[48;5;202m　　　\x1b[0m 　\x1b[43m　\x1b[0m　 \x1b[102m　　\x1b[0m　 \x1b[46m　\x1b[0m \x1b[45m　　　\x1b[0m\n");
    printf("       　\x1b[41m　\x1b[0m　 \x1b[48;5;202m　\x1b[0m　　 　\x1b[43m　\x1b[0m　 \x1b[102m　\x1b[0m　\x1b[102m　\x1b[0m \x1b[46m　\x1b[0m 　　\x1b[45m　\x1b[0m\n");
    printf("     　  \x1b[41m　\x1b[0m　 \x1b[48;5;202m　　　\x1b[0m 　\x1b[43m　\x1b[0m　 \x1b[102m　\x1b[0m　\x1b[102m　\x1b[0m \x1b[46m　\x1b[0m \x1b[45m　　　\x1b[0m\n");
    printf("     　  \x1b[0m\n");
    divider("", 'b');
}

void print_ranking(int new, int score[5], time_t record_time[5]) {
    divider("RANKING", 'b');
    for (int i = 0; i < 5; i++) {
        if (record_time[i] == 0) {
            printf("No%d: ------ (----/--/-- --:--:--)", i + 1);
        }
        else {
            struct tm* t = localtime(&record_time[i]);
            printf("No%d: %06d (%4d/%02d/%02d %02d:%02d:%02d)", i + 1, score[i], t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        }
        if (i == new) {
            printf(" <- NEW!!! \n");
        }
        else {
            printf("\n");
        }
    }
    printf("\n");
    divider("", 'b');
}

void print_result(int point, int new, int score[5], time_t record_time[5]) {
    system("clear");
    divider("RESULT", 'b');
    printf("Final Point: %d\n\n", point);
    print_ranking(new, score, record_time);
}