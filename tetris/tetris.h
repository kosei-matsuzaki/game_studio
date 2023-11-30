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
    int current_mino_type;
    int next_mino_type;
    int hold_mino_type;
    int do_hold;
    int point;
    int count;
    int level;
    int in_game;
} info;

//  tetris
void tetris(int *in_game);
void initialize(info *info);
void start(int *in_game);
void input(info *info);
void display(info *info);
void block_processor(info *info);
int next(info *info);
int result(info *info, int *in_game);
void end();

// mino
void new_mino(mino*, int type);
void next_mino(int type);
void hold_mino(int type);

// printer
void print_block(int);
void print_status(int point, int level);
void print_shadow(int);
void print_title();
void print_ranking(int new, int score[5], time_t record_time[5]);
void print_result(int point, int new, int score[5], time_t time[5]);

// processor
void block_write(int blocks[20][12], mino*);
int is_movable(int blocks[20][12], mino*);
void line_remover(int blocks[20][12], int *point);
int circulation(int temp);
void shift_fall(int blocks[20][12], mino *current_mino, int*, int*, int*, int*);
void shift_harddrop(int blocks[20][12], mino *current_mino, int*, int*, int*, int* point);
void shift_right(int blocks[20][12], mino *current_mino);
void shift_left(int blocks[20][12], mino *current_mino);
void shift_rotate(int blocks[20][12], mino *current_mino, int direction);
void shift_hold(mino *current_mino, int*, int*, int*, int*);

//data
void read_data(int score[5], time_t record_time[5]);
void register_data(int score[5], time_t record_time[5]);

#endif // _TETRIS_H_