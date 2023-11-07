#ifndef _MAPS_H_
#define _MAPS_H_

typedef struct {
    int id;
    char* name;
    double difficulty;
    int bpm;
    int beat;
    int bar_count;
    int map[1800][4];
} map_info;


extern const map_info pond_rain;
extern const map_info doremi;

#endif
