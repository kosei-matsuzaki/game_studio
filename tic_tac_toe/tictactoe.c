#include <bits/types/timer_t.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./tictactoe.h"
#include "../util/util.h"

void tic_tac_toe(int *in_game) {
    int block[25][25] = {{0}};
    int size = 0;
    int consecutive = 0;
    t_start(in_game);
    if (*in_game == 1) {        
        t_setting(&size, &consecutive, block);
    }
    int turn = 0;
    while(*in_game == 1) {
        system("clear");
        t_display(&size, block);
        turn ++;
        int status = t_decider(turn, &size, &consecutive, block);
        if (status != 0) {
            break;
        }
        t_input(turn, &size, block);
    }
    t_end(in_game);
}

void t_start(int *in_game) {
    printf("\n");
    divider("", 'b');
    printf("Welcome to Tic Tac Toe!\n\n");
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

void t_setting(int *size, int *consecutive, int block[25][25]) {    
    divider("SETTING", 'b');
    while(1) {
        printf("Enter Block Size: ");
        scanf("%d", size);
        clear_stream();
        if (*size > 25 || *size < 3) {
            printf("Size must be larger than 2 and smaller than 21\n");
            continue;
        } else {
            break;
        }
    }
    while(1) {
        printf("Enter Victory Condition: ");
        scanf("%d", consecutive);
        clear_stream();
        if (*consecutive > *size) {
            printf("Victory Condition must be smaller than or equal to block size\n");
            continue;
        } else {
            break;
        }
    }
    printf("\n");
    divider("", 'b');
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            block[i][j] = 0;
        }
    }
}

void t_display(int *size, int block[25][25]) {
    divider("BOARD", 'b');
    for (int i = -1; i < *size; i++) {
        if (i == -1) {
            printf(" \\ ");
            continue;
        }
        printf("%2d ", i);
        if (i == *size - 1) {
            printf("\n");
        }
    }
    for (int i = 0; i < *size; i++) {
        printf("%2d ", i);
        for (int j = 0; j < *size; j++) {
            if (block[i][j] == 0) {
                printf("%2c ", '-');
            }
            if (block[i][j] == 1) {
                printf("\x1b[31m%2c\x1b[0m ", 'o');
            }
            if (block[i][j] == 2) {
                printf("\x1b[36m%2c\x1b[0m ", 'x');
            } 
            if (j == *size - 1) {
                printf("\n");
            }
        }
    }
    return;
}

int t_decider(int turn, int *size, int *consecutive, int block[25][25]) {
    if (turn == (*size * *size + 1)) {
        t_result(0, 0, 0, 'e', consecutive);
        return 1;
    } else {
        //horizontal or vertical
        for (int i = 0; i < *size; i++) {
            for (int j = 0; j < *size - *consecutive + 1; j++) {
                if (block[i][j] != 0) {
                    for (int k = 0; k < *consecutive - 1; k++) {
                        if (block[i][j + k] != block[i][j + k + 1]) {
                            break;
                        }
                        if (k == *consecutive - 2) {
                            t_result(block[i][j], i, j, 'h', consecutive);
                            return 1;
                        }
                    }
                }
                
            }
            for (int j = 0; j < *size - *consecutive + 1; j++) {
                if (block[j][i] != 0) {
                    for (int k = 0; k < *consecutive - 1; k++) {
                        if (block[j + k][i] != block[j + k + 1][i]) {
                            break;
                        }
                        if (k == *consecutive - 2) {
                            t_result(block[i][j], i, j, 'v', consecutive);
                            return 1;
                        }
                    }
                }
            }
        }
        //diagonal right down
        for (int i = 0; i < *size - *consecutive + 1; i++) {
            for (int j = 0; j < *size - *consecutive + 1; j++) {
                if (block[i][j] != 0) {
                    for (int k = 0; k < *consecutive - 1; k++) {
                        if (block[i + k][j + k] != block[i + k + 1][j + k + 1]) {
                            break;
                        }
                        if (k == *consecutive - 2) {
                            t_result(block[i][j], i, j, 'r', consecutive);
                            return 1;
                        }
                    }
                }
            }
        }
        //diagonal left down
        for (int i = 0; i < *size - *consecutive + 1; i++) {
            for (int j = *consecutive - 1; j < *size; j++) {
                if (block[i][j] != 0) {
                    for (int k = 0; k < *consecutive - 1; k++) {
                        if (block[i + k][j - k] != block[i + k + 1][j - k - 1]) {
                            break;
                        }
                        if (k == *consecutive - 2) {
                            t_result(block[i][j], i, j, 'l', consecutive);
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
}

void t_input(int turn, int* size, int block[25][25]) {
    printf("\n");
    divider("", 'b');
    int row, col;
    if (turn == 1 || turn == 2) {
        printf("\x1b[33mExample: 4 6\x1b[0m\n");
    }
    if (turn % 2 == 1) {
        printf("First Player\n");
    } else {
        printf("Second Player\n");
    }
    while(1) {
        while(1) {
            printf("Row Col: ");
            scanf("%d %d", &row, &col);
            clear_stream();
            if (row < 0 || row > *size - 1 || col < 0 || col > *size - 1) {
                printf("Out of range\n");
                continue;
            } else {
                break;
            }
        }
        if (block[row][col] != 0) {
            printf("The box is occupied\n");
            continue;
        } else {
            break;
        }
    }
    printf("\n");
    divider("", 'b');
    if (turn % 2 == 1) {
        block[row][col] = 1;
    } else {
        block[row][col] = 2;
    }
}

void t_result(int status, int i, int j, char p, int *consecutive) {
    printf("\n");
    divider("RESULT", 'b');
    switch (status){
        case 0: printf("Draw\n"); break;
        case 1: printf("\x1b[33mWinner: Player1\x1b[0m\n"); break;
        case 2: printf("\x1b[33mWinner: Player2\x1b[0m\n"); break;
        default: break;
    }
    switch (p) {
        case'h': printf("Horizontal: %d %d to %d %d\n", i, j, i , j + *consecutive - 1); break;
        case'v': printf("Vertical: %d %d to %d %d\n", i, j, i + *consecutive - 1, j); break;
        case'r': printf("Diagonal(decreasing): %d %d to %d %d\n", i, j, i + *consecutive - 1, j + *consecutive - 1); break;
        case'l': printf("Diagonal(increasing): %d %d to %d %d\n", i, j, i - *consecutive + 1, j + *consecutive - 1); break;
        default: break;
    }
    printf("\n");
    divider("", 'b');
    return;
}

void t_end(int *in_game) {
    printf("\n");
    divider("", 'b');
    printf("THANK YOU FOR PLAYING!!!\n");
    printf("Press Enter To Leave\n");
    printf("\n");
    divider("", 'b');
    *in_game = 0;
}
