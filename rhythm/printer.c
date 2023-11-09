#include <stdio.h>
#include "../util/util.h"

void r_print_note(int n) {
	switch (n) 
	{
	case 0: printf("   "); break;
	case 1: printf(" ♦ "); break;
	case 2: printf(" \x1b[31m*\x1b[0m "); break;
	case 3: printf(" \x1b[33m*\x1b[0m "); break;
	case 4: printf(" \x1b[33m*\x1b[0m "); break;
	case 5: printf(" \x1b[34m*\x1b[0m "); break;
	case 6: printf("   "); break;
	default:
		break;
	}
}

void r_print_note_hit(int n, int p, int b1, int b2) {
	if (n == 1) {
		printf("-♦-");
		return;
	}
	if (n == 2 || p == 2) {
		printf("\x1b[101m---\x1b[0m");
		return;
	}
	if (b1 == 3 || n == 3 || p == 4) {
		printf("\x1b[103m---\x1b[0m");
		return;
	}
	if (b2 == 5 || b1 == 5) {
		printf("\x1b[104m---\x1b[0m");
		return;
	}
	else {
		printf("---");
	}
	return;
}

void r_print_score(int point, int combo) {
	printf("\n");
	divider("", 'b');
	printf("Point: %d\n", point);
	printf("Combo: x%d\n", combo);
	printf("\n");
	divider("", 'b');
}