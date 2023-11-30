#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include "util.h"

//remove unused char from input
void clear_stream(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
    return;
}
//detect Enter
char get_single_char(void) {
    int input;
    input = getchar();
    if (input != '\n') {
        clear_stream();
    }
    return input;
}

void divider(const char* a, char color) {
    int l = strlen(a);
    switch(color){
        case 'r': printf("\x1b[31m"); break;
        case 'y': printf("\x1b[93m"); break;
        case 'b': printf("\x1b[36m"); break;
        default: break;
    }
    for (int i = 0; i < 25 - (l / 2); i++) {
        printf("=");
    }
    if (l != 0) {
        printf(" %s ", a);
    } else {
        printf("==");
    }
    for (int i = 0; i < 25 - ((l + 1)/ 2); i++) {
        printf("=");
    }
    printf("\x1b[0m\n\n");
    return;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void countdown(int count) {
    for (int i = 0; i < count; i++) {
        printf("%d...\n", count - i);
        sleep(1);
    }
}