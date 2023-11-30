#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "tetris.h"
#include "../util/util.h"

void read_data(int score[5], time_t record_time[5]) {
    FILE* file_reader;
    file_reader = fopen("score.txt", "r");
    if (file_reader == NULL) {
        printf("failed to open file: read\n");
        return;
    }
    fscanf(file_reader, "%d,%d,%d,%d,%d,%ld,%ld,%ld,%ld,%ld", &(score[0]), &(score[1]), &(score[2]), &(score[3]), &(score[4]), &(record_time[0]), &(record_time[1]), &(record_time[2]), &(record_time[3]), &(record_time[4]));
    fclose(file_reader);
}

void register_data(int score[5], time_t record_time[5]) {
    FILE *file_writer;
    file_writer = fopen("score.txt", "w");
    if (file_writer == NULL) {
        printf("failed to open file: write\n");
        return;
    }
    fprintf(file_writer, "%d,%d,%d,%d,%d,%ld,%ld,%ld,%ld,%ld", score[0], score[1], score[2], score[3], score[4], record_time[0], record_time[1], record_time[2], record_time[3], record_time[4]);
    fclose(file_writer);
}

