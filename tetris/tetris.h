#ifndef _TETRIS_H_
#define _TETRIS_H_
 
typedef struct {
    int type[4][4];
    int x;
    int y;
} mino;

typedef struct {
    int blocks[20][12];
    mino current_mino;
    int next_mino_type;
    int point;
    int count;
    int level;
    int in_game;
} info;

//  tetris
void tetris(int *in_game);
void b_initialize(info *info);
void b_start(int *in_game);
void b_input(info *info);
void b_display(info *info);
void b_block_processor(info *info);
int b_next(info *info);
void b_result(info *info);
void b_end();

// mino
void b_new_mino(mino*, int type);
void b_next_mino(int type);

// printer
void b_print_block(int);
void b_print_status(int point, int level);

// processor
void b_block_write(int blocks[20][12], mino*);
int b_is_movable(int blocks[20][12], mino*);
void b_line_remover(int blocks[20][12], int *point);
void b_shift_fall(int blocks[20][12], mino *current_mino, int*);
void b_shift_right(int blocks[20][12], mino *current_mino);
void b_shift_left(int blocks[20][12], mino *current_mino);
void b_shift_rotate(int blocks[20][12], mino *current_mino, int direction);


#endif // _TETRIS_H_