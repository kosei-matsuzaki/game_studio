#include <stdio.h>

void rhythm(int *in_game) {
    r_start(in_game);
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