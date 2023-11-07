#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_
 
//  関数avgのプロトタイプ宣言
void tic_tac_toe(int *in_game);
void t_start(int *in_game);
void t_setting(int *size, int *consecutive, int block[25][25]);
void t_display(int *size, int block[25][25]);
int t_decider(int turn, int *size, int *consecutive, int block[25][25]);
void t_input(int turn, int* size, int block[25][25]);
void t_result(int status, int i, int j, char p, int *consecutive);
void t_end(int *in_game);
 
#endif // _TICTACTOE_H_