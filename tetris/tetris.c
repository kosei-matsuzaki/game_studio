#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "tetris.h"
#include "../util/util.h"

int frame[20][12] = {
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1},
};
int render = 50000; //0.05s

// main func
void tetris(int *in_game) {
    start(in_game);
    while (*in_game) {
        info info = { .count = 0, .point = 0, .in_game = *in_game };
        initialize(&info);
        while (1) {
            display(&info);
            input(&info);
            block_processor(&info);
            if (next(&info) == 0) {
                break;
            };
            info.count++;
            usleep(render);
            system("clear");
        }
        if (result(&info, in_game)) {
            start(in_game);
        }
    }
    end();
    return;
}

// display startup
void start(int *in_game) {
    while (1) {
        system("clear");
        printf("\n");
        print_title();
        int score[5] = { 0,0,0,0,0 };
        time_t record_time[5] = { 0 };
        read_data(score, record_time);
        print_ranking(-1, score, record_time);
        printf("\x1b[33mPress Enter To Start\x1b[0m\n");
        printf("Press   D   To Delete Data\n");
        printf("Press   Q   To Quit\n");
        while (1) {
            char c = get_single_char();
            if (c == '\n') {
                system("clear");
                countdown(3);
                printf("GAME START!\n\n");
                sleep(1);
                return;
            }
            else if (c == 'q') {
                *in_game = 0;
                return;
            }
            else if (c == 'd') {
                printf("\x1b[31mDo You Really Want To Delete? y/n\x1b[0m\n");
                if (get_single_char() == 'y') {
                    int dummy[5] = { 0 };
                    time_t dummy2[5] = { 0 };
                    register_data(dummy, dummy2);
                    printf("Data deleted\n");
                    sleep(1);
                }     
                break;
            }
        }
    }
}

// initial setting
void initialize(info *info) {
    srandom((unsigned)time(NULL));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 12; j++) {
            info->blocks[i][j] = frame[i][j];
        }
    }
    info->current_mino_type = random() % 7 + 1;
    new_mino(&info->current_mino, info->current_mino_type);
    info->next_mino_type = circulation(info->current_mino_type);
    info->level = 0;
    info->hold_mino_type = 0;
    info->do_hold = 0;
}

// detect input
void input(info *info) {
    if(kbhit()) {
        switch(getchar()) {
        case 'a': shift_left(info->blocks, &info->current_mino); break;
        case 'd': shift_right(info->blocks, &info->current_mino); break;
        case 'q': shift_rotate(info->blocks, &info->current_mino, 3); break;
        case 'e': shift_rotate(info->blocks, &info->current_mino, 1); break;
        case 's': shift_fall(info->blocks, &info->current_mino, &info->next_mino_type, &info->current_mino_type, &info->hold_mino_type, &info->do_hold); info->point++; break;
        case 'f': shift_hold(&info->current_mino, &info->next_mino_type, &info->current_mino_type, &info->hold_mino_type, &info->do_hold); break;
        case 'w': shift_harddrop(info->blocks, &info->current_mino, &info->next_mino_type, &info->current_mino_type, &info->do_hold, &info->point); break;
        default: break;
        }            
    }
}

// display
void display(info *info) {
    print_status(info->point, info->level);
    divider("", 'b');
    hold_mino(info->hold_mino_type);
    next_mino(info->next_mino_type);
    mino shadow = info->current_mino;
    while (is_movable(info->blocks, &shadow) == 1) {
        (shadow.y) ++;
    }
    (shadow.y) --;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 12; j++) {
            int x = j - info->current_mino.x;
            int y = i - info->current_mino.y;
            int y_shadow = i - shadow.y;
            if (0 <= x && x <= 3 && 0 <= y && y <= 3) {
                if (info->current_mino.type[y][x] > 1) {
                    print_block(info->current_mino.type[y][x]);
                    continue;
                }
            }
            if (0 <= x && x <= 3 && 0 <= y_shadow && y_shadow <= 3) {
                if (shadow.type[y_shadow][x] > 1) {
                    print_shadow(shadow.type[y_shadow][x]);
                    continue;
                }
            }
            if (info->blocks[i][j] >= 1) {
                print_block(info->blocks[i][j]);
            } else {
                printf("  ");
            }
            if (j == 11) {
                printf("\n");
            }
        }
    }
}

// move block
void block_processor(info *info) {
    if (info->count % (10 - info->level) == 0) {
        shift_fall(info->blocks, &info->current_mino, &info->next_mino_type, &info->current_mino_type, &info->hold_mino_type, &info->do_hold);
    }
    line_remover(info->blocks, &info->point);
    return;
}

// is game end
int next(info *info) {
    for(int i = 1; i < 11; i++)  {
        if(info->blocks[1][i] > 1){
            return 0;
        }
    }
    if (info->count % 1800 == 0) {
        info->level ++;
    }
    return 1;
}

int result(info *info, int *in_game) {
    int score[5] = { 0,0,0,0,0 };
    time_t record_time[5] = { 0 };
    int new = 0;
    read_data(score, record_time);
    for (int i = 0; i < 5; i++) {
        if (score[i] < info->point) {
            new = i;
            for (int j = 4; j > i; j--) {
                score[j] = score[j - 1];
                record_time[j] = record_time[j - 1];
            }
            score[i] = info->point;
            record_time[i] = time(NULL);
            break;
        }
    }
    register_data(score, record_time);
    print_result(info->point, new, score, record_time);

    printf("\x1b[33mPress Enter To Retry\x1b[0m\n");
    printf("Press   B   To Go Back To Start Menu\n");
    printf("Press   Q   To End Game\n");
    while (1) {
        char c = get_single_char();
        if (c == '\n') {
            return 0;
        }
        else if (c == 'q') {
            *in_game = 0;
            return 0;
        }
        else if (c == 'b') {
            return 1;
        }
    }
    return 0;
}

// end
void end() {
    system("clear");
    divider("", 'b');
    printf("THANK YOU FOR PLAYING!!!\n");
    printf("Press Enter To Leave\n");
    printf("\n");
    divider("", 'b');
}