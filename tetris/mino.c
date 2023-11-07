#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int type[4][4];
    int x;
    int y;
} mino;

int mino1[4][4] = {
    {0,0,0,0},
    {0,2,0,0},
    {2,2,2,0},
    {0,0,0,0},
};
int mino2[4][4] = {
    {0,0,0,0},
    {0,0,3,0},
    {3,3,3,0},
    {0,0,0,0},
};
int mino3[4][4] = {
    {0,0,0,0},
    {4,4,4,0},
    {0,0,4,0},
    {0,0,0,0},
};
int mino4[4][4] = {
    {0,0,0,0},
    {5,5,0,0},
    {0,5,5,0},
    {0,0,0,0},
};
int mino5[4][4] = {
    {0,0,0,0},
    {0,6,6,0},
    {6,6,0,0},
    {0,0,0,0},
};
int mino6[4][4] = {
    {0,0,0,0},
    {0,7,7,0},
    {0,7,7,0},
    {0,0,0,0},
};
int mino7[4][4] = {
    {0,0,0,0},
    {8,8,8,8},
    {0,0,0,0},
    {0,0,0,0},
};

void b_set_mino(mino *current_mino, int m[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            current_mino->type[i][j] = m[i][j];
        }
    }
}

void b_new_mino(mino *current_mino, int type) {
    current_mino->x = 4;
    current_mino->y = 0;
    switch (type) {
    case 1: b_set_mino(current_mino, mino1); break;
    case 2: b_set_mino(current_mino, mino2); break;
    case 3: b_set_mino(current_mino, mino3); break;
    case 4: b_set_mino(current_mino, mino4); break;
    case 5: b_set_mino(current_mino, mino5); break;
    case 6: b_set_mino(current_mino, mino6); break;
    case 7: b_set_mino(current_mino, mino7); break;
    default: b_set_mino(current_mino, mino1); break;
    }
}

void b_print_block(int);
void b_print_mino(int mino[4][4]) {
    for (int i = 0; i < 4; i ++){
        if (i == 0) {
            printf("Next: ");
        } else {
            printf("      ");
        }
        for (int j = 0; j < 4; j++) {
            if (mino[i][j] >= 1) {
                b_print_block(mino[i][j]);
            } else {
                printf("  ");
            }
            if (j == 3) {
                printf("\n");
            }
        }
    }
}

void b_next_mino(int type) {
    switch(type) {
        case 1: b_print_mino(mino1); break;
        case 2: b_print_mino(mino2); break;
        case 3: b_print_mino(mino3); break;
        case 4: b_print_mino(mino4); break;
        case 5: b_print_mino(mino5); break;
        case 6: b_print_mino(mino6); break;
        case 7: b_print_mino(mino7); break;
        default: b_print_mino(mino1); break;
    }
}