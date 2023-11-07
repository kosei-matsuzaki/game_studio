#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void b_print_block(int c) {
    switch (c) {
    case 1: printf(" ■"); break;
    case 2: printf(" \x1b[35m■\x1b[0m"); break;
    case 3: printf(" \x1b[34m■\x1b[0m"); break;
    case 4: printf(" \x1b[31m■\x1b[0m"); break;
    case 5: printf(" \x1b[91m■\x1b[0m"); break;
    case 6: printf(" \x1b[92m■\x1b[0m"); break;
    case 7: printf(" \x1b[33m■\x1b[0m"); break;
    case 8: printf(" \x1b[96m■\x1b[0m"); break;
    default: printf(" Q"); break;
    }
}

void b_print_status(int point, int level) {
    printf("\n");
    printf("Point: %d  Current Level: %d\n", point, level);
    return;
}