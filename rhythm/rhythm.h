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
    const int id;
    const char* name;
    const double difficulty;
    const int time;
    const int speed;
    const int map[1800][4];
} map_info;

void rhythm(int *in_game);
void r_start(int *in_game); 
int r_select_map(map_status* status, int *in_game);
void r_notes(int map[1800][4], map_info map_info, map_status* status, int count);
void r_input(int map[1800][4], map_status* status, int count, int speed);
void r_map_end(map_info map, map_status* status, int count);
void r_result(map_status* status);
void r_end();

// map
map_info* r_map_selecter(int id);
void r_map_creator(int map_duplicate[1800][4], const int map[1800][4]);
int r_map_list();
int r_map_play_comfirm(int select, map_status* status);

//note
void r_is_hit(int map[1800][4], map_status* status, int hit, int line);
void r_note_missed(int map[1800][4], map_status* status, int position);

//printer
void r_print_note(int n);
void r_print_note_hit(int n, int p, int b1, int b2);
void r_print_score(int point, int combo);

#endif // _RHYTHM_H_
