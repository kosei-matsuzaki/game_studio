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
int wait = 50000;

// main func
void tetris(int *in_game) {
    b_start(in_game);
    info info;
    info.count = 0;
    info.point = 0;
    info.in_game = *in_game;
    if (*in_game == 1) {
        b_initialize(&info);
    }

    while (info.in_game == 1) {
        b_display(&info);
        b_input(&info);
        b_block_processor(&info);
        info.in_game = b_next(&info);
        info.count ++;
        system("clear");
    }
    b_result(&info);
    b_end();
    return;
}

// display startup
void b_start(int *in_game) {
    printf("\n");
    divider("", 'b');
    printf("Welcome to Tetris!\n\n");
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

// initial setting
void b_initialize(info *info) {
    srandom((unsigned)time(NULL));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 12; j++) {
            info->blocks[i][j] = frame[i][j];
        }
    }
    b_new_mino(&info->current_mino, random() % 7 + 1);
    info->next_mino_type = random() % 7 + 1;
    info->level = 0;
}

// detect input
void b_input(info *info) {
    usleep(wait);
    if(kbhit()) {
        switch(getchar()) {
        case 'a': b_shift_left(info->blocks, &info->current_mino); break;
        case 'd': b_shift_right(info->blocks, &info->current_mino); break;
        case 'q': b_shift_rotate(info->blocks, &info->current_mino, 3); break;
        case 'e': b_shift_rotate(info->blocks, &info->current_mino, 1); break;
        case 's': b_shift_fall(info->blocks, &info->current_mino, &info->next_mino_type); break;
        default: break;
        }            
    }
}

// display
void b_display(info *info) {
    b_print_status(info->point, info->level);
    divider("", 'b');
    b_next_mino(info->next_mino_type);
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 12; j++) {
            int x = j - info->current_mino.x;
            int y = i - info->current_mino.y;
            if (0 <= x && x <= 3 && 0 <= y && y <= 3) {
                if (info->current_mino.type[y][x] > 1) {
                    b_print_block(info->current_mino.type[y][x]);
                    continue;
                }
            }
            if (info->blocks[i][j] >= 1) {
                b_print_block(info->blocks[i][j]);
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
void b_block_processor(info *info) {
    // todo faster
    if (info->count % (10 - info->level) == 0) {
        b_shift_fall(info->blocks, &info->current_mino, &info->next_mino_type);
    }
    b_line_remover(info->blocks, &info->point);
    return;
}

// is game end
int b_next(info *info) {
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

void b_result(info *info) {
    divider("RESULT", 'b');
    printf("Final Point: %d\n\n", info->point);
    divider("", 'b');
    return;
}

// end
void b_end() {
    divider("", 'b');
    printf("THANK YOU FOR PLAYING!!!\n");
    printf("Press Enter To Leave\n");
    printf("\n");
    divider("", 'b');
}