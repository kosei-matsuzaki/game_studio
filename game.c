#include <stdio.h>
#include <stdlib.h>
#include "poker/poker.h"
#include "tic_tac_toe/tictactoe.h"
#include "util/util.h"
#include "tetris/tetris.h"
#include "rhythm/rhythm.h"

const int game_poker = 0;
const int game_tic_tac_toe = 1;
const int game_tetris = 2;
const int game_rhythm = 3;

void boot();
int game_selection(int*);

//main function
int main () {
    int in_game = 0;
    boot();
    while(1) {
        int game_mode = game_selection(&in_game);
        system("clear");
        switch (game_mode) {
            case 0:
                poker(&in_game);
                break;
            case 1:
                tic_tac_toe(&in_game);
                break;
            case 2:
                tetris(&in_game);
                break;
            case 3:
                rhythm(&in_game);
                break;
            default: continue;
        }
        while(get_single_char() != '\n');
        system("clear");
    }
    return 0;
}

void boot() {
    system("clear");
    divider("", 'y');
    printf("WELCOME TO GAME STUDIO!\n\n");
    divider("", 'y');
}

int game_selection(int *in_game) {
    divider("GAME LIST", 'b');
    printf("p: Poker\n");
    printf("t: Tic Tac Toe\n");
    printf("b: Tetris\n");
    printf("r: Rhythm Game\n");
    printf("\n");
    printf("Ctrl+C: Shutdown\n\n");
    divider("", 'b');
    printf("Select Game From The List Above: ");

    char game = get_single_char();
    switch (game) {
    case 'p': *in_game = 1; return game_poker;
    case 't': *in_game = 1; return game_tic_tac_toe;
    case 'b': *in_game = 1; return game_tetris;
    case 'r': *in_game = 1; return game_rhythm;
    default: return -1;
    }
}
