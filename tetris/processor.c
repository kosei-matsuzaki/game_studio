#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int type[4][4];
    int x;
    int y;
} mino;

void b_new_mino(mino*, int);

void b_block_write(int blocks[20][12], mino *current_mino) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (current_mino->type[i][j] > 1) {
                blocks[current_mino->y + i][current_mino->x + j] = current_mino->type[i][j];
            }
        }
    }
}

int b_is_movable(int blocks[20][12], mino *current_mino) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (current_mino->type[i][j] > 1 && blocks[current_mino->y + i][current_mino->x + j] >= 1) {
                return 0;
            }
        }
    }
    return 1; 
}

void b_line_remover(int blocks[20][12], int *point) {
    int i = 18;
    while (i != 1) {
        int need_delete = 0;
        for (int j = 0; j < 12; j++) {
            if (blocks[i][j] == 0){
                break;
            }
            if (j == 11) {
                need_delete = 1;
                (*point) += 10;
            }
        }
        if (need_delete == 1){
            int k = i;
            while(k != 0) {
                for (int j = 1; j < 11; j++) {
                    blocks[k][j] = blocks[k - 1][j];
                }
                k --;
            } 
        } else {
            i --;
        }    
    }
}

void b_shift_fall(int blocks[20][12], mino *current_mino, int *next_mino_type) {
    (current_mino->y) ++;
    if (b_is_movable(blocks, current_mino) != 1) {
        (current_mino->y) --;
        b_block_write(blocks, current_mino);
        b_new_mino(current_mino, *next_mino_type);
        srandom((unsigned)time(NULL));
        *next_mino_type = random() % 7 + 1;
    }
    return;
}

void b_shift_right(int blocks[20][12], mino *current_mino) {
    (current_mino->x) ++;
    if (b_is_movable(blocks, current_mino) != 1) {
        (current_mino->x) --;
    }
    return;
}

void b_shift_left(int blocks[20][12], mino *current_mino) {
    (current_mino->x) --;
    if (b_is_movable(blocks, current_mino) != 1) {
        (current_mino->x) ++;
    }
    return;
}

void b_rotate(mino *current_mino) {
    mino dummy;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dummy.type[i][j] = current_mino->type[3 - j][i];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            current_mino->type[i][j] = dummy.type[i][j];            
        }
    }
    return; 
}

void b_shift_rotate(int blocks[20][12], mino *current_mino, int n) {
    for(int i = 0; i < n; i++) {
        b_rotate(current_mino);
    }
    if (b_is_movable(blocks, current_mino) != 1) {
        for (int i = 0; i < 4 - n; i++) {
            b_rotate(current_mino);
        }
    }
    return;
}
