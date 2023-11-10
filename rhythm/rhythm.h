#ifndef _RHYTHM_H_
#define _RHYTHM_H_

typedef struct
{
    int playing;
    int map_id;
    int point;
    int combo;
    int result[5]; //great, good, bad, miss, maxcombo
} map_status;


typedef struct {
    int id;
    char* name;
    double difficulty;
    int bpm;
    int beat;
    int bar_count;
    int map[1800][4];
} map_info;

extern const int r_render;

void rhythm(int *in_game);
void r_start(int *in_game); 
int r_select_map(map_status* status, int *in_game);
void r_notes(int map[1800][4], map_info map_info, map_status* status, int count);
void r_input(int map[1800][4], map_status* status, int count, int speed);
void r_map_end(map_info map, map_status* status, int count);
void r_end();

// map
int r_tempo_calculator(int bpm, int beat);
int r_time_calcutator(int bar_count, int beat, int bpm);
void r_map_initialize();
map_info* r_map_selecter(int id);
void r_map_creator(int map_duplicate[1800][4], const int map[1800][4]);
int r_map_list();
int r_map_play_comfirm(int select, map_status* status);

//note
void r_is_hit(int map[1800][4], map_status* status, int hit, int line);
void r_note_missed(int map[1800][4], map_status* status, int position);
int r_count_note(int result[5]);
double r_accuracy(int result[5]);

//printer
void r_print_note(int n);
void r_print_note_hit(int n, int p, int b1, int b2);
void r_print_score(map_status* status);
void r_print_rank(int result[5]);


#endif // _RHYTHM_H_
