#ifndef _RHYTHM_H_
#define _RHYTHM_H_

typedef struct 
{
    int playing;
    int music_number;
    int point;
    int combo;
};

void rhythm(int *in_game);
void r_start(int *in_game); 
void r_end();

#endif // _RHYTHM_H_
