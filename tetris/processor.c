#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "tetris.h"

//落下判定（盤面に固定）
void block_write(int blocks[20][12], mino *current_mino) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (current_mino->type[i][j] > 1) {
                blocks[current_mino->y + i][current_mino->x + j] = current_mino->type[i][j];
            }
        }
    }
}

//移動判定
int is_movable(int blocks[20][12], mino *current_mino) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (current_mino->type[i][j] > 1 && blocks[current_mino->y + i][current_mino->x + j] >= 1) {
                return 0;
            }
        }
    }
    return 1; 
}

//列削除
void line_remover(int blocks[20][12], int *point) {
    int i = 18;
    int count = 0;
    while (i != 1) {
        int need_delete = 0;
        for (int j = 0; j < 12; j++) {
            if (blocks[i][j] == 0){
                break;
            }
            if (j == 11) {
                need_delete = 1;
                count++;
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
    switch (count) {
    case 0: return;
    case 1: *point += 100; return;
    case 2: *point += 300; return;
    case 3: *point += 500; return;
    case 4: *point += 800; return;
    default: return;
    }
}

// 周期的なブロック生成
int block_list[7] = {1,2,3,4,5,6,7};
int len_of_block_list = 7;
int next_block;
int circulation(int temp){
    if (len_of_block_list == 1){
        len_of_block_list = 7;
        for (int i=0;i<7;++i){
            block_list[i] = i+1;
        }
        srandom((unsigned)time(NULL));
        next_block = random() % 7;
    }
    else{
        for (int i=0;i<7;++i){
            if (block_list[i] == temp){
                block_list[i] = 0;
                for (int j=i;j<6;++j){
                    block_list[j] = block_list[j+1];
                    block_list[j+1] = 0;
                }
                break;
            }
        }
        --len_of_block_list;
        srandom((unsigned)time(NULL));
        next_block = random() % len_of_block_list;
    }
    return block_list[next_block];
}

//落下
void shift_fall(int blocks[20][12], mino *current_mino, int *next_mino_type, int *current_mino_type, int *hold_mino_type, int *do_hold) {
    (current_mino->y) ++;
    if (is_movable(blocks, current_mino) != 1) {
        (current_mino->y) --;
        block_write(blocks, current_mino);
        new_mino(current_mino, *next_mino_type);
        *current_mino_type = *next_mino_type;
        *next_mino_type = circulation(*next_mino_type);
        *do_hold = 0;
    }
    return;
}

//即時落下
void shift_harddrop(int blocks[20][12], mino *current_mino, int *next_mino_type, int *current_mino_type, int *do_hold, int *point) {
    while (is_movable(blocks, current_mino) == 1) {
        (current_mino->y) ++;
        *point += 2;
    }
    *point -= 2;
    (current_mino->y) --;
    block_write(blocks, current_mino);
    new_mino(current_mino, *next_mino_type);
    *current_mino_type = *next_mino_type;
    *next_mino_type = circulation(*next_mino_type);
    *do_hold = 0;
    return;
}

//右移動
void shift_right(int blocks[20][12], mino *current_mino) {
    (current_mino->x) ++;
    if (is_movable(blocks, current_mino) != 1) {
        (current_mino->x) --;
    }
    return;
}

//左移動
void shift_left(int blocks[20][12], mino *current_mino) {
    (current_mino->x) --;
    if (is_movable(blocks, current_mino) != 1) {
        (current_mino->x) ++;
    }
    return;
}

//回転実行
void rotate(mino *current_mino) {
    int current_mino_type = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            current_mino_type += current_mino->type[i][j];
        }
    }
    current_mino_type /= 4;
    mino dummy;
    if (current_mino_type > 6){
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
    }
    else{
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                dummy.type[i][j] = current_mino->type[2 - j][i];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                current_mino->type[i][j] = dummy.type[i][j];            
            }
        }
    }
    return; 
}

//回転移動
void shift_rotate(int blocks[20][12], mino *current_mino, int n) {
    for(int i = 0; i < n; i++) {
        rotate(current_mino);
    }
    if (is_movable(blocks, current_mino) != 1) {
        for (int i = 0; i < 4 - n; i++) {
            rotate(current_mino);
        }
    }
    return;
}

// ホールドを作る
void shift_hold(mino *current_mino, int *next_mino_type, int *current_mino_type, int *hold_mino_type, int* do_hold){
    if (*do_hold == 0){
        if (*hold_mino_type == 0){
            *hold_mino_type = *current_mino_type;
            new_mino(current_mino, *next_mino_type);
            *current_mino_type = *next_mino_type;
            *next_mino_type = circulation(*next_mino_type);
        }
        else {
            new_mino(current_mino, *hold_mino_type);
            int pre_hold = *hold_mino_type;
            *hold_mino_type = *current_mino_type;
            *current_mino_type = pre_hold;
        }
    *do_hold = 1;
    }
    return;
}
